// romea
#include "romea_core_gps/nmea/GSVFrame.hpp"
#include "romea_core_gps/nmea/NMEAParsing.hpp"

namespace romea {


//-----------------------------------------------------------------------------
GSVFrame::SatelliteInfo::SatelliteInfo():
  PRNNumber(),
  elevation(),
  azimut(),
  SNR()
{
}

//-----------------------------------------------------------------------------
GSVFrame::GSVFrame():
  talkerID(TalkerId::UNSUPPORTED),
  numberOfSentences(),
  sentenceNumber(),
  numberOfSatellitesInView(),
  satellitesInfo()
{
}

//-----------------------------------------------------------------------------
GSVFrame::GSVFrame(const std::string & nmeaGSVSentence)
{
  assert(NMEAParsing::isNMEASentence(nmeaGSVSentence));
  assert(nmeaGSVSentence.substr(3, 3) =="GSV");

  // Split sentence in fields
  std::setlocale(LC_ALL, "C");
  std::vector<std::string> fields = NMEAParsing::splitInFields(nmeaGSVSentence);

  // Decode GPS prefix ID
  talkerID = NMEAParsing::extractTalkerId(fields[0]);

  // Decode sentence
  if (nmeaGSVSentence.substr(3, 3) == "GSV" &&
     NMEAParsing::computeChecksum(nmeaGSVSentence) == std::stoi(fields.back(), 0, 16))
  {
    // decode number of sentences
    if (!fields[1].empty())
    {
      numberOfSentences = std::stoi(fields[1]);
    }

    // decode sentence number
    if (!fields[2].empty())
    {
      sentenceNumber = std::stoi(fields[2]);
    }

    // decode number of satelitte in view
    if (!fields[3].empty())
    {
      numberOfSatellitesInView = std::stoi(fields[3]);
    }

    // decode satellite data
    size_t start = 4;
    for (size_t n=0; n < (fields.size()-5)/4; ++n, start+=4)
    {
      SatelliteInfo sv;

      if (!fields[start].empty())
        sv.PRNNumber = std::stoi(fields[start]);

      if (!fields[start+1].empty())
         sv.elevation = std::stoi(fields[start+1]);

      if (!fields[start+2].empty())
        sv.azimut = std::stoi(fields[start+2]);

      if (!fields[start+3].empty())
        sv.SNR = std::stoi(fields[start+3]);

      satellitesInfo.push_back(sv);
    }

    if (start+1 != fields.size() && !fields[start].empty())
    {
      signalID = std::stoi(fields[start]);
    }
  }
}

//-----------------------------------------------------------------------------
std::ostream& operator<<(std::ostream & os, const GSVFrame & frame)
{
  os << "GSV frame " << std::endl;

  os << "GPS system = " << description(frame.talkerID) << std::endl;

  os << "number of sentences ";
  if (frame.numberOfSentences)
    os << *frame.numberOfSentences;
  os <<std::endl;

  os << "sentence number ";
  if (frame.sentenceNumber)
    os << *frame.sentenceNumber;
  os <<std::endl;

  os << "number of satellites in view ";
  if (frame.numberOfSatellitesInView)
    os << *frame.numberOfSatellitesInView;
  os <<std::endl;

  os << "Satellites data" << std::endl;
  const std::deque<GSVFrame::SatelliteInfo> & satelliteData = frame.satellitesInfo;
  for (size_t n = 0; n < satelliteData.size(); ++n)
  {
    os << "PRN number ";
    if (satelliteData[n].PRNNumber)
    {
      os << *satelliteData[n].PRNNumber << std::endl;;
    }

    os << "elevation : ";
    if (satelliteData[n].elevation)
    {
      os << *satelliteData[n].elevation << std::endl;
    }

    os << "azimuth : ";
    if (satelliteData[n].azimut)
    {
      os << *satelliteData[n].azimut << std::endl;
    }

    os << "snr ";
    if (satelliteData[n].SNR)
    {
      os << *satelliteData[n].SNR << std::endl;
    }
  }

  os << "signal ID ";
  if (frame.signalID)
    os << *frame.signalID;
  os <<std::endl;

  os <<std::endl;

  return os;
}

}  // namespace romea
