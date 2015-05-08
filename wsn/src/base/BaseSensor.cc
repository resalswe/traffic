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

#include <FindModule.h>

#include "BaseSensor.h"

namespace wsn {
namespace base {

BaseSensor::BaseSensor() :
        sensorDataIn(-1), sensorControlIn(-1), appDataOut(-1) {
}

void BaseSensor::initialize(int stage) {
    if (stage == 0) {
        sensorControlIn = findGate("sensorControlIn");
        sensorDataIn = findGate("sensorDataIn");
        appDataOut = findGate("appDataOut");
    }
}

/**
 */
void BaseSensor::handleMessage(cMessage* msg) {
    // Self message
    if (msg->isSelfMessage()) {
        handleSelfMsg(msg);
        return;
    }

    // Sensor control in
    if (msg->getArrivalGateId() == sensorControlIn) {
        if (msg->getKind() == SC_INIT) {
            // TODO: Record msg; check baseSensor
            handleInitMsg(msg);
        } else {
            // TODO: Record msg; check baseSensor
            handleCtrlMsg(msg);
        }
        return;
    }

    // Sensor data in
    if (msg->getArrivalGateId() == sensorDataIn) {
        // TODO: Record msg; check baseSensor
        EV << "BaseSensor: handleMessage currently not implemented;"
                  << " delete msg\n";
        delete msg;
        return;
    }

    EV << "BaseSensor: handleMessage arrival gate not handled; delete msg\n";
    delete msg;
}

/**
 */
void BaseSensor::handleSelfMsg(cMessage* msg) {
    EV << "BaseSensor: handleSelfMsg not redefined; delete msg\n";
    delete msg;
}

/**
 */
void BaseSensor::handleInitMsg(cMessage* msg) {
    // TODO: Record outMsg; check baseSensor
    cMessage* outMsg = new cMessage(getSensorTypeName().c_str(),
            SD_INIT_COMPLETED);
    sendAppData(outMsg);
    delete msg;
}

/**
 */
void BaseSensor::handleCtrlMsg(cMessage* msg) {
    EV << "BaseSensor: handleCtrlMsg not redefined; delete msg\n";
    delete msg;
}

/**
 */
void BaseSensor::sendAppData(cMessage* msg) {
    // TODO: Record data check baseSensor
    send(msg, appDataOut);
}

BaseSensor::~BaseSensor() {
}

}
}
