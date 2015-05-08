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
#include "base/BaseSensor.h"
#include "utils/ConstantsWsn.h"

namespace wsn {
namespace base {

/** @brief
 *
 */
class BaseSensorAppl: public BaseApplLayer, public ISensorApp {
protected:
    /**
     * Number of available sensors.
     */
    int numberOfSensors;

    /** @brief
     * First gate id of sensor data i.e. the base identification id. The rest
     * are incremented up to number of available sensors i.e.
     * 1..(numberOfSenbsor-1).
     */
    gateId dataGateBaseId;

    /** @brief
     * First gate id of sensor control i.e. the base identification id. The
     * rest are incremented up to number of available sensors i.e.
     * 1..(numberOfSenbsor-1).
     */
    gateId controlGateBaseId;

    /** @brief
     * Self message to start initialization of the sensors.
     */
    cMessage* initSensors;

    enum SelfMessages {
        INIT_SENSORS, LAST_BASE_SELF_MSG_KIND
    };

public:
    BaseSensorAppl();
    virtual ~BaseSensorAppl();

    /** @brief
     * Initialization of the module and some variables
     **/
    virtual void initialize(int);

    /** @brief
     * Called every time a message arrives. It separates the handling of
     * messages into separate method i.e. handleSensorData, handleSelfMsg etc.
     *
     * @note In most cases this method is not needed to be overridden.
     **/
    virtual void handleMessage(cMessage* msg);

protected:

    /** @brief
     * Handle sensor data messages this includes both data and control
     * responses.
     *
     * The basic sensor application layer just silently deletes all messages it
     * receives.
     *
     * @param msg The incoming message to process.
     **/
    virtual void handleSensorData(cMessage* msg);

    /** @brief
     * Handles all self messages for this module.
     *
     * @param msg Incoming selfmessage to process.
     */
    virtual void handleSelfMsg(cMessage* msg);

    /** @brief
     * Initializes the sensors connected to this application. This includes
     * obtaining the type of sensor etc.
     */
    virtual void initialiseSensors();
};

} // base
} // wsn

#endif /* BASESENSORAPPL_H_ */
