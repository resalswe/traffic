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

package com.dektech.wsn.nodes;

import org.mixim.modules.node.Host802154_2400MHz;
import com.dektech.wsn.base.ISensor;
import com.dektech.wsn.base.ISensorApp;

module SensorNode extends Host802154_2400MHz
{
    parameters:
        string sensorType = default("Proximity, Proximity");
        int numOfSensors = 1;

        @display("bgb=315,429");
    submodules:
        sensors[numOfSensors]: <sensorType> like ISensor {
            @display("p=220,310");
            applicationId = index;
        }

        sensorAppl: <applicationType> like ISensorApp if applicationType != "" {
            @display("p=220,170");
            numberOfSensors = numOfSensors;
        }

    connections:
        for i=0..numOfSensors - 1 {
            sensorAppl.sensorControl[i] --> sensors[i].sensorControlIn;
            sensors[i].appDataOut --> sensorAppl.sensorData[i];
        }
}
