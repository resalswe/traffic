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

package com.dektech.wsn.base;

moduleinterface ISensor {
    parameters:
        int applicationId;
        string sensorTypeName;
            
    gates:
        input sensorDataIn;     // Input data recieved from stimuli. This can for example be a Mobility or Channel model.
        input sensorControlIn;  // Input data recieved from the controller. This can for example be an application.
        output appDataOut;      // Output data obtained by processing input data. This is usually conntected to an application.
}