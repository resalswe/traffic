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

#ifndef ISENSORAPP_H_
#define ISENSORAPP_H_

namespace wsn {
namespace base {

/**
 * Interface for the different types of sensor applications available to a
 * sensor node. <br>
 *
 * All implemented sensor applications should implement and adhere to this
 * interface.
 */
class ISensorApp {
public:
    virtual ~ISensorApp() {};

};

} // base
} // wsn

#endif /* ISENSORAPP_H_ */
