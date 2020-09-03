#ifndef romea_NMEAModeIndicator_hpp
#define romea_NMEAModeIndicator_hpp

//std
#include <string>

namespace romea
{

enum class ModeIndicator
{
  NO_FIX_MODE,
  GPS_MODE,
  DGPD_MODE,
  PRECISE_MODE,
  RTK_MODE,
  FLOAT_RTK_MODE,
  ESTIMATED_MODE,
  MANUAL_MODE,
  SIMULATION_MODE
};

}

#endif
