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

#ifndef ISENSOR_H_
#define ISENSOR_H_

#include <string>

#include "utils/ConstantsWsn.h"

namespace wsn {
namespace sensors {

/**
 * Interface for the different types of sensors available to a sensor node
 * application. <br>
 *
 * All implemented sensors should implement and adhere to this interface.
 */
class ISensor {
public:
    enum SensorCtrl {
        GET_TYPE_NAME,
        START_MEASSURE,
        STOP_MEASSURE,
        LAST_BASE_SENSOR_KIND = 500
    };

    virtual ~ISensor() {};

    /**
     * Obtain the type name of the sensor.
     *
     * @return Type name of the sensor.
     */
    virtual std::string getSensorTypeName() = 0;

    /**
     * Obtain the control gate identification for this sensor.
     *
     * @return control gate id for this sensor.
     */
    virtual gateId getSensorControlGateId() = 0;

    /**
     * Obtain the data input gate identification for this sensor.
     *
     * @return Data input gate id for this sensor.
     */
    virtual gateId getSensorDataInId() = 0;

    /**
     * Obtain the application data output gate identification for this sensor.
     *
     * @return Application data gate id for this sensor.
     */
    virtual gateId getAppDataOutId() = 0;
};

}
}

#endif /* ISENSOR_H_ */
