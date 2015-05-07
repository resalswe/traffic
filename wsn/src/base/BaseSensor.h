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

#ifndef BASESENSOR_H_
#define BASESENSOR_H_

#include <string>
#include <MiximBatteryAccess.h>

#include "ISensor.h"
#include "utils/ConstantsWsn.h"

namespace wsn {
namespace base {

class BaseSensor: public MiximBatteryAccess, public ISensor {
protected:
    gateId sensorDataIn;
    gateId sensorControlIn;
    gateId appDataOut;

public:
    enum SensorCtrl {
        SC_INIT,                    // Initialise sensor + return sensor type
        SC_CONFIG,                  // Configuration of sensor node
        SC_START_MEASSURE,          // Start continues measurement
        SC_STOP_MEASSURE,           // Stop continues measurement
        SC_SAMPLE_MEASSURE,         // Obtain one sample measure
        LAST_BASE_SENSOR_CTRL_KIND  // For extensibility
    };

    enum SensorData {
        SD_INIT_COMPLETED,
        SD_CONFIG_COMPLETED,
        SD_OPERATION_NOT_SUPPORTED,
        SD_DATA,
        LAST_BASE_SENSOR_DATA_KIND
    };

    BaseSensor();
    virtual ~BaseSensor();

    /**
     * @see cSimpleModule::initialize(int)
     */
    virtual void initialize(int stage);

    /**
     * @see cSimpleModule::handleMessage(cMessage)
     */
    virtual void handleMessage(cMessage*);

    /**
     * Handle a sensor modules self messages such as timers, etc.
     *
     * This method should be redefined to support timers or other selfmessages
     * needed for the sensors operation.
     *
     * @Note: cMessage needs to be deleted
     */
    virtual void handleSelfMsg(cMessage*);

    /**
     * Handle a sensor modules initialisation message. For a typical sensor this
     * relates to responding with the name.
     *
     * This method should be redefined to support more advanced initialisation
     * behavior.
     *
     * @Note: cMessage needs to be deleted
     */
    virtual void handleInitMsg(cMessage*);

    /**
     * Handle a sensor modules control messages. These message include
     * measurement control, sensor configuration (during runtime).
     *
     * This method should be redefined to support other control messages than
     * the initialisation.
     *
     * @Note: cMessage needs to be deleted
     */
    virtual void handleCtrlMsg(cMessage*);

    /**
     * Obtain the type name of the sensor.
     *
     * @return Type name of the sensor.
     */
    virtual std::string getSensorTypeName() = 0;

    /**
     *
     */
    void sendAppData(cMessage*);
};

} // base
} // wsn

#endif /* BASESENSOR_H_ */
