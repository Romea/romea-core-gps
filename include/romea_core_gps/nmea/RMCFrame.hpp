#ifndef romea_RMCFrame_hpp
#define romea_RMCFrame_hpp

//romea
#include "NMEALatitude.hpp"
#include "NMEALongitude.hpp"
#include "NMEAFixQuality.hpp"
#include "NMEAFixTime.hpp"
#include "NMEAFixDate.hpp"
#include "NMEATalker.hpp"

//std
#include <optional>
#include <string>
#include <memory>
#include <ostream>

namespace romea {

struct RMCFrame
{

  enum class Status {
    Active=0,
    Void
  };


  using Ptr =std::shared_ptr<RMCFrame> ;

  RMCFrame();

  RMCFrame(const std::string & nmeaRMCSentence);

  TalkerId talkerId;
  std::optional<FixTime> fixTime;
  std::optional<Status> status;
  std::optional<Latitude> latitude;
  std::optional<Longitude> longitude;
  std::optional<double> speedOverGroundInMeterPerSecond;
  std::optional<double> trackAngleTrue;
  std::optional<FixDate> fixDate;
  std::optional<double> magneticDeviation;
  std::optional<FixQuality> fixQuality;

  std::string toNMEA() const;

};

std::ostream& operator<<(std::ostream & os, const RMCFrame & frame);


double trackAngleToCourseAngle(const double &trackAngle,
                               const double &vehiclelLinearSpeed);


}

#endif
