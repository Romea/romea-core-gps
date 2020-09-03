#ifndef romea_NMEAFixQuality_hpp
#define romea_NMEAFixQuality_hpp

//std
#include <string>

namespace romea {

enum class FixQuality {
  INVALID_FIX = 0,
  GPS_FIX,
  DGPS_FIX,
  PPS_FIX,
  RTK_FIX,
  FLOAT_RTK_FIX,
  ESTIMATED_FIX,
  MANUAL_FIX,
  SIMULATION_FIX
};

FixQuality modeIndicatorToFixQuality(const std::string & modeIndicator);

std::string description(const FixQuality & FixQuality);

bool operator>=(FixQuality fixQuality1 ,FixQuality fixQuality2);

}
#endif
