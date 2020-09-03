#ifndef romea_GGAFrame_hpp
#define romea_GGAFrame_hpp

//romea
#include "NMEALatitude.hpp"
#include "NMEALongitude.hpp"
#include "NMEAFixTime.hpp"
#include "NMEAFixQuality.hpp"
#include "NMEATalker.hpp"

//boost to replace by std optional
#include <boost/optional/optional.hpp>

//std
#include <string>
#include <memory>
#include <ostream>

namespace romea {

struct GGAFrame
{

  using Ptr =std::shared_ptr<GGAFrame> ;

  GGAFrame();

  GGAFrame(const std::string &nmeaGGASentence);

  TalkerId talkerId;
  boost::optional<FixTime> fixTime;
  boost::optional<Latitude> latitude;
  boost::optional<Longitude> longitude;
  boost::optional<FixQuality> fixQuality;
  boost::optional<unsigned short> numberSatellitesUsedToComputeFix;
  boost::optional<double> horizontalDilutionOfPrecision;
  boost::optional<double> altitudeAboveGeoid;
  boost::optional<double> geoidHeight;
  boost::optional<double> dgpsCorrectionAgeInSecond;
  boost::optional<unsigned short> dgpsStationIdNumber;

  std::string toNMEA() const;

};

std::ostream& operator<<(std::ostream & os, const GGAFrame & frame);

}

#endif
