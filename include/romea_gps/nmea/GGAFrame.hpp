#ifndef romea_GGAFrame_hpp
#define romea_GGAFrame_hpp

//romea
#include "NMEALatitude.hpp"
#include "NMEALongitude.hpp"
#include "NMEAFixTime.hpp"
#include "NMEAFixQuality.hpp"
#include "NMEATalker.hpp"

//std
#include <optional>
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
  std::optional<FixTime> fixTime;
  std::optional<Latitude> latitude;
  std::optional<Longitude> longitude;
  std::optional<FixQuality> fixQuality;
  std::optional<unsigned short> numberSatellitesUsedToComputeFix;
  std::optional<double> horizontalDilutionOfPrecision;
  std::optional<double> altitudeAboveGeoid;
  std::optional<double> geoidHeight;
  std::optional<double> dgpsCorrectionAgeInSecond;
  std::optional<unsigned short> dgpsStationIdNumber;

  std::string toNMEA() const;

};

std::ostream& operator<<(std::ostream & os, const GGAFrame & frame);

}

#endif
