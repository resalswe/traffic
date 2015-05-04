//
// Copyright (C) 2011 David Eckhoff <eckhoff@cs.fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

/*
 * Based on PhyLayer.cc from Karl Wessel
 * and modifications by Christopher Saloman
 */

#include "PhyLayer80211p.h"

#include "Decider80211p.h"
#include "SimplePathlossModel.h"
#include "BreakpointPathlossModel.h"
#include "LogNormalShadowing.h"
#include "JakesFading.h"
#include "PERModel.h"
#include "SimpleObstacleShadowing.h"
#include "TwoRayInterferenceModel.h"
#include "BaseConnectionManager.h"
#include <Consts80211p.h>
#include "AirFrame11p_m.h"
#include "MacToPhyControlInfo.h"

using Veins::ObstacleControlAccess;

Define_Module(PhyLayer80211p);

/** This is needed to circumvent a bug in MiXiM that allows different header length interpretations for receiving and sending airframes*/
void PhyLayer80211p::initialize(int stage) {
	BasePhyLayer::initialize(stage);
	if (stage == 0) {
		if (par("headerLength").longValue() != PHY_HDR_TOTAL_LENGTH) {
		opp_error("The header length of the 802.11p standard is 46bit, please change your omnetpp.ini accordingly by either setting it to 46bit or removing the entry");
		}
		//erase the RadioStateAnalogueModel
		analogueModels.erase(analogueModels.begin());
	}
}

AnalogueModel* PhyLayer80211p::getAnalogueModelFromName(const std::string& name, ParameterMap& params) const {

	if (name == "SimplePathlossModel") {
	    // FIXME: Temporary fix. Should it be here or not. Should not be multiple places for these parameters.
	    // All should be obtained from the same source
	    const Coord& playground = *(world->getPgs());
 	    params["useTorus"] = world->useTorus();
	    params["PgsX"] = playground.x;
	    params["PgsY"] = playground.y;
	    params["PgsZ"] = playground.z;

	    return createAnalogueModel<SimplePathlossModel>(params);
	}
	else if (name == "LogNormalShadowing")
	{
	    return createAnalogueModel<LogNormalShadowing>(params);
	}
	else if (name == "JakesFading")
	{
		return createAnalogueModel<JakesFading>(params);
	}
	else if(name == "BreakpointPathlossModel")
	{
	    return createAnalogueModel<BreakpointPathlossModel>(params);
	} else if(name == "PERModel")
	{
		return initializePERModel(params);
	}
	else if (name == "SimpleObstacleShadowing")
	{
		return initializeSimpleObstacleShadowing(params);
	}
	else if (name == "TwoRayInterferenceModel")
	{
		if (world->use2D()) error("The TwoRayInterferenceModel uses nodes' z-position as the antenna height over ground. Refusing to work in a 2D world");
		return initializeTwoRayInterferenceModel(params);
	}

	return BasePhyLayer::getAnalogueModelFromName(name, params);
}

AnalogueModel* PhyLayer80211p::initializeTwoRayInterferenceModel(ParameterMap& params) const {
	double dielectricConstant= params["DielectricConstant"].doubleValue();

	return new TwoRayInterferenceModel(dielectricConstant, coreDebug);
}

AnalogueModel* PhyLayer80211p::initializeSimplePathlossModel(ParameterMap& params) const {
	SimplePathlossModel* model = new SimplePathlossModel();
	model->initFromMap(params);

	return model;
}

AnalogueModel* PhyLayer80211p::initializePERModel(ParameterMap& params) const {
	PERModel* model = new PERModel();
	model->initFromMap(params);

	return model;
}

Decider* PhyLayer80211p::getDeciderFromName(const std::string& name, ParameterMap& params) {
	if(name == "Decider80211p") {
		protocolId = IEEE_80211;
		return initializeDecider80211p(params);
	}
	return BasePhyLayer::getDeciderFromName(name, params);
}

AnalogueModel* PhyLayer80211p::initializeSimpleObstacleShadowing(ParameterMap& params) const {

	// init with default value
	double carrierFrequency = 5.890e+9;
	bool useTorus = world->useTorus();
	const Coord& playgroundSize = *(world->getPgs());

	ParameterMap::iterator it;

	// get carrierFrequency from config
	it = params.find("carrierFrequency");

	if ( it != params.end() ) // parameter carrierFrequency has been specified in config.xml
	{
		// set carrierFrequency
		carrierFrequency = it->second.doubleValue();
		coreEV << "initializeSimpleObstacleShadowing(): carrierFrequency set from config.xml to " << carrierFrequency << endl;

		// check whether carrierFrequency is not smaller than specified in ConnectionManager
		if(cc->hasPar("carrierFrequency") && carrierFrequency < cc->par("carrierFrequency").doubleValue())
		{
			// throw error
			opp_error("initializeSimpleObstacleShadowing(): carrierFrequency can't be smaller than specified in ConnectionManager. Please adjust your config.xml file accordingly");
		}
	}
	else // carrierFrequency has not been specified in config.xml
	{
		if (cc->hasPar("carrierFrequency")) // parameter carrierFrequency has been specified in ConnectionManager
		{
			// set carrierFrequency according to ConnectionManager
			carrierFrequency = cc->par("carrierFrequency").doubleValue();
			coreEV << "createPathLossModel(): carrierFrequency set from ConnectionManager to " << carrierFrequency << endl;
		}
		else // carrierFrequency has not been specified in ConnectionManager
		{
			// keep carrierFrequency at default value
			coreEV << "createPathLossModel(): carrierFrequency set from default value to " << carrierFrequency << endl;
		}
	}

	ObstacleControl* obstacleControlP = ObstacleControlAccess().getIfExists();
	if (!obstacleControlP) opp_error("initializeSimpleObstacleShadowing(): cannot find ObstacleControl module");
	return new SimpleObstacleShadowing(*obstacleControlP, carrierFrequency, useTorus, playgroundSize, coreDebug);
}

Decider* PhyLayer80211p::initializeDecider80211p(ParameterMap& params) {
	double centerFreq = params["centerFrequency"];

	bool collectCollisionStatistics = false;
	{
		ParameterMap::iterator it = params.find("collectCollisionStatistics");
		if (it != params.end()) {
			collectCollisionStatistics = it->second.doubleValue();
		}
	}

	Decider80211p* dec = new Decider80211p(this, sensitivity, centerFreq, findHost()->getIndex(), collectCollisionStatistics, coreDebug);
	dec->setPath(getParentModule()->getFullPath());
	return dec;
}

void PhyLayer80211p::changeListeningFrequency(double freq) {
	Decider80211p* dec = dynamic_cast<Decider80211p*>(decider);
	assert(dec);
	dec->changeFrequency(freq);
}
void PhyLayer80211p::handleSelfMessage(cMessage* msg) {

	switch(msg->getKind()) {
	//transmission overBasePhyLayer::
	case TX_OVER: {
		assert(msg == txOverTimer);
		sendControlMsgToMac(new cMessage("Transmission over", TX_OVER));
		//check if there is another packet on the chan, and change the chan-state to idle
		Decider80211p* dec = dynamic_cast<Decider80211p*>(decider);
		assert(dec);
		if (dec->cca(simTime(),NULL)) {
			//chan is idle
			DBG << "Channel idle after transmit!\n";
//			dec->setChannelIdleStatus(true); TODO: is this needed seDecider80211p.cc file

		}
		else {
			DBG << "Channel not yet idle after transmit!\n";
		}
		break;
	}
	//radio switch over
	case RADIO_SWITCHING_OVER:
		assert(msg == radioSwitchingOverTimer);
		BasePhyLayer::finishRadioSwitching();
		break;

	//AirFrame
	case AIR_FRAME:
		BasePhyLayer::handleAirFrame(static_cast<MiximAirFrame*>(msg));
		break;

	//ChannelSenseRequest
	case CHANNEL_SENSE_REQUEST:
		BasePhyLayer::handleChannelSenseRequest(msg);
		break;

	default:
		break;
	}
}
MiximAirFrame *PhyLayer80211p::encapsMsg(cPacket *macPkt)
{
	// the cMessage passed must be a MacPacket... but no cast needed here
	// MacPkt* pkt = static_cast<MacPkt*>(msg);

	// ...and must always have a ControlInfo attached (contains Signal)
	cObject* ctrlInfo = macPkt->removeControlInfo();
	assert(ctrlInfo);

	// create the new AirFrame
	MiximAirFrame* frame = new AirFrame11p(macPkt->getName(), AIR_FRAME);

	// Retrieve the pointer to the Signal-instance from the ControlInfo-instance.
	// We are now the new owner of this instance.
	Signal* s = MacToPhyControlInfo::getSignalFromControlInfo(ctrlInfo);
	// make sure we really obtained a pointer to an instance
	assert(s);

	// set the members
	assert(s->getDuration() > 0);
	frame->setDuration(s->getDuration());
	// copy the signal into the AirFrame
	frame->setSignal(*s);
	//set priority of AirFrames above the normal priority to ensure
	//channel consistency (before any thing else happens at a time
	//point t make sure that the channel has removed every AirFrame
	//ended at t and added every AirFrame started at t)
	frame->setSchedulingPriority(airFramePriority);
	frame->setProtocolId(myProtocolId());
	frame->setBitLength(headerLength);
	frame->setId(world->getUniqueAirFrameId());
	frame->setChannel(radio->getCurrentChannel());


	// pointer and Signal not needed anymore
	delete s;
	s = 0;

	// delete the Control info
	delete ctrlInfo;
	ctrlInfo = 0;

	frame->encapsulate(macPkt);

	// --- from here on, the AirFrame is the owner of the MacPacket ---
	macPkt = 0;
	coreEV <<"AirFrame encapsulated, length: " << frame->getBitLength() << "\n";

	return frame;
}

int PhyLayer80211p::getRadioState() const {
    return BasePhyLayer::getRadioState();
};
