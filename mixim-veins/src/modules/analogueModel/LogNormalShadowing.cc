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

#include "LogNormalShadowing.h"

#include "Mapping.h"
#include "MiximAirFrame_m.h"

LogNormalShadowing::LogNormalShadowing() :
        mean(0), stdDev(1), interval(0) {
}

double LogNormalShadowing::randomLogNormalGain() const {
    return FWMath::dBm2mW(-1.0 * normal(mean, stdDev));
}

void LogNormalShadowing::filterSignal(MiximAirFrame *frame,
        const Coord& /*sendersPos*/, const Coord& /*receiverPos*/) {
    Signal& signal = frame->getSignal();
    simtime_t start = signal.getReceptionStart();
    simtime_t end = signal.getReceptionEnd();
    Mapping* att = MappingUtils::createMapping(DimensionSet::timeDomain,
            Mapping::LINEAR);

    Argument pos;

    for (simtime_t t = start; t <= end; t += interval) {
        pos.setTime(t);
        att->appendValue(pos, randomLogNormalGain());
    }

    signal.addAttenuation(att);
}

bool LogNormalShadowing::initFromMap(const ParameterMap& params) {
    ParameterMap::const_iterator it;

    if ((it = params.find("mean")) != params.end()) {
        mean = ParameterMap::mapped_type(it->second).doubleValue();
    }
    if ((it = params.find("stdDev")) != params.end()) {
        stdDev = ParameterMap::mapped_type(it->second).doubleValue();
    }
    if ((it = params.find("interval")) != params.end()) {
        interval = ParameterMap::mapped_type(it->second).doubleValue();
    }

    return AnalogueModel::initFromMap(params);
}

LogNormalShadowing::~LogNormalShadowing() {
}
