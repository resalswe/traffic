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

#include <BaseSensorAppl.h>

namespace wsn {
namespace base {

// Constructor
BaseSensorAppl::BaseSensorAppl() :
        numberOfSensors(-1), dataGateBaseId(-1), controlGateBaseId(-1) {
}

/**
 */
void BaseSensorAppl::initialize(int stage) {
    BaseApplLayer::initialize(stage);

    // Initialization stage 0: not all components exists i.e. all registrations and
    // lookup of components should be done in stage 1. Component configuration from
    // ned files and ini files should be set in stage 0.
    if (stage == 0) {
        numberOfSensors = par("numberOfSensors");

        dataGateBaseId = gateBaseId("sensorData");
        controlGateBaseId = gateBaseId("sensorControl");
    }

    if (stage == 1) {
        initSensors = new cMessage("InitSensors", INIT_SENSORS);
        scheduleAt(simTime(), initSensors);
    }
}

/**
 */
void BaseSensorAppl::initialiseSensors() {

    for (int i = 0; i < numberOfSensors; ++i) {
        cMessage* typeNameMsg = new cMessage("typeName", BaseSensor::SC_INIT);
        send(typeNameMsg, controlGateBaseId + i);
    }
}

/**
 */
void BaseSensorAppl::handleMessage(cMessage* msg) {

    if ((msg->getArrivalGateId() >= dataGateBaseId)
            && (msg->getArrivalGateId() < dataGateBaseId + numberOfSensors)) {
        handleSensorData(msg);
        return;
    }

    BaseApplLayer::handleMessage(msg);
}

/**
 */
void BaseSensorAppl::handleSensorData(cMessage* msg) {
    EV << "BaseApplLayer: handleSensorData not redefined; delete msg\n";
    delete msg;
}

/**
 */
void BaseSensorAppl::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
    case INIT_SENSORS:
        initialiseSensors();
        break;
    default:
        EV << "Unknown self message! -> delete, kind: " << msg->getKind()
                  << endl;
        break;
    }

    delete msg;
}

// Destructor
BaseSensorAppl::~BaseSensorAppl() {
}

} // base
} // wsn
