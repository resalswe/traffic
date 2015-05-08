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

#ifndef PROXIMITY_H_
#define PROXIMITY_H_

#include <string>

#include "base/BaseSensor.h"

namespace wsn {
namespace sensors {

class Proximity: public base::BaseSensor {
private:
    /** @brief Type name of this sensor */
    static const std::string TYPE_NAME;

    /** @brief A signal used to subscribe to mobility state changes. */
    const static simsignalwrap_t mobilityStateChangedSignal;

    IMobility* ownMobility;

public:
    virtual ~Proximity() {};

    /**
     * @see cSimpleModule::initialize(int)
     */
    void initialize(int stage);

    /**
     * @see BaseSensor::handleSelfMsg(cMessage*)
     */
    virtual void handleSelfMsg(cMessage*);

    /**
     * @see BaseSensor::handleCtrlMsg(cMessage*)
     */
    virtual void handleCtrlMsg(cMessage*);

    /**
     * @see BaseModel::receiveSignal(cComponent*, simsignal_t, cObject*)
     */
    virtual void receiveSignal(cComponent *source, simsignal_t signalID,
            cObject *obj);

    /**
     * @see BaseSensor::getSensorTypeName()
     */
    std::string getSensorTypeName();

};

} // sensors
} // wsn

#endif /* PROXIMITY_H_ */
