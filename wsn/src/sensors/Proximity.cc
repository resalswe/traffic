//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "FindModule.h"

#include <Proximity.h>


namespace wsn {
namespace sensors {

const std::string Proximity::TYPE_NAME = "Proximity";

const simsignalwrap_t Proximity::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

Define_Module(Proximity)

/**
 */
void Proximity::initialize(int stage) {
    BaseSensor::initialize(stage);

    if (stage == 0) {
        // TODO: read in parameters

        findHost()->subscribe(mobilityStateChangedSignal.initialize(), this);

        const cModule* const mod = getParentModule();
        ownMobility = FindModule<IMobility*>::findSubModule(mod);
        if (ownMobility == NULL) {
            opp_error("Could not find mobility module");
        }
    }
}

/**
 */
void Proximity::handleSelfMsg(cMessage* msg) {
}

/**
 */
void Proximity::handleCtrlMsg(cMessage* msg) {
}

/**
 */
void Proximity::receiveSignal(cComponent* source, simsignal_t signalID,
        cObject* obj) {

    if(signalID == mobilityStateChangedSignal) {
        IMobility* const mobility = check_and_cast<IMobility*>(obj);
        Coord pos = mobility->getCurrentPosition();

        EV << "Position[x, y] = [" << pos.x << ", " << pos.y << "]." << std::endl;
    }
}

std::string Proximity::getSensorTypeName() {
    return Proximity::TYPE_NAME;
}

} // sensors
} // wsn
