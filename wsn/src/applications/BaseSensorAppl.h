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

#ifndef BASESENSORAPPL_H_
#define BASESENSORAPPL_H_

#include <map>
#include <BaseApplLayer.h>

#include "ISensorApp.h"
#include "sensors/ISensor.h"
#include "utils/ConstantsWsn.h"

namespace wsn {
namespace applications {

class BaseSensorAppl: public BaseApplLayer, public ISensorApp {
protected:
    int numberOfSensors;

    gateId dataGateBaseId;
    gateId controlGateBaseId;

    cMessage* initSensors;

    enum SelfMessages {
        INIT_SENSORS, LAST_BASE_SELF_MSG_KIND = 10
    };

public:
    BaseSensorAppl();
    virtual ~BaseSensorAppl();

    /** @brief Initialization of the module and some variables*/
    virtual void initialize(int);

protected:
    /** @brief Called every time a message arrives*/
    virtual void handleMessage(cMessage* msg);

    /**
     * @brief Handle sensor data messages both data and control responses.
     *
     * The basic sensor application layer just silently deletes all messages it
     * receives.
     **/
    virtual void handleSensorData(cMessage* msg);

    /**
     *
     */
    virtual void handleSelfMsg(cMessage * msg);

    /**
     *
     */
    virtual void initialiseSensors();
};

} // applications
} // wsn

#endif /* BASESENSORAPPL_H_ */
