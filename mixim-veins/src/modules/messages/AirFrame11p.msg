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

cplusplus {{
#include "base/messages/MiximAirFrame_m.h"
}}
class MiximAirFrame;

//
// Extension of base AirFrame message to have the underSensitivity field
//
message AirFrame11p extends MiximAirFrame {
    bool underSensitivity = false;
    bool wasTransmitting = false;
}
