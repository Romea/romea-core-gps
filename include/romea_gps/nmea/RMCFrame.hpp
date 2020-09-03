#ifndef romea_RMCFrame_hpp
#define romea_RMCFrame_hpp

//romea
#include "NMEALatitude.hpp"
#include "NMEALongitude.hpp"
#include "NMEAFixQuality.hpp"
#include "NMEAFixTime.hpp"
#include "NMEAFixDate.hpp"
#include "NMEATalker.hpp"

//boost to replace by std optional
#include <boost/optional/optional.hpp>

//std
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
  boost::optional<FixTime> fixTime;
  boost::optional<Status> status;
  boost::optional<Latitude> latitude;
  boost::optional<Longitude> longitude;
  boost::optional<double> speedOverGroundInMeterPerSecond;
  boost::optional<double> trackAngleTrue;
  boost::optional<FixDate> fixDate;
  boost::optional<double> magneticDeviation;
  boost::optional<FixQuality> fixQuality;

  std::string toNMEA() const;

};

std::ostream& operator<<(std::ostream & os, const RMCFrame & frame);


double trackAngleToCourseAngle(const double &trackAngle,
                               const double &vehiclelLinearSpeed);


}

#endif
