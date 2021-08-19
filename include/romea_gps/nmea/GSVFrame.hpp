#ifndef romea_GSVFrame_hpp
#define romea_GSVFrame_hpp

//romea
#include "NMEATalker.hpp"

//boost to replace by std optional
#include <boost/optional/optional.hpp>

//std
#include <string>
#include <memory>
#include <deque>
#include <ostream>

namespace romea {


struct GSVFrame
{
  struct SatelliteInfo {
    SatelliteInfo();
    boost::optional<unsigned short> PRNNumber;
    boost::optional<unsigned short> elevation;
    boost::optional<unsigned short> azimut;
    boost::optional<unsigned short> SNR;
  };


  using Ptr =std::shared_ptr<GSVFrame> ;

  GSVFrame();

  GSVFrame(const std::string & nmeaGSVSentence);

  TalkerId talkerID;
  boost::optional<unsigned short> numberOfSentences;
  boost::optional<unsigned short> sentenceNumber;
  boost::optional<unsigned short> numberOfSatellitesInView;
  boost::optional<unsigned short> signalID;
  std::deque<SatelliteInfo> satellitesInfo;

};

std::ostream& operator<<(std::ostream & os, const GSVFrame & frame);

}

#endif
