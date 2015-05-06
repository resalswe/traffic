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

#include "ISensor.h"

namespace wsn {
namespace sensors {

class Proximity: public ISensor {

private:
    static const std::string TYPE_NAME;

public:
    virtual ~Proximity() {};

    std::string getSensorTypeName();
};

} // sensors
} // wsn

#endif /* PROXIMITY_H_ */
