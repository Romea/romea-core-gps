//romea
#include "romea_gps/nmea/RMCFrame.hpp"
#include "romea_gps/nmea/NMEAParsing.hpp"
#include <romea_common/math/EulerAngles.hpp>

//std
#include <iostream>
#include <cmath>

namespace {
const double KNOT_TO_METER_PER_SECOND =0.51444444444;
}

namespace romea {

RMCFrame::RMCFrame():
  talkerId(TalkerId::UNSUPPORTED),
  fixTime(),
  status(),
  latitude(),
  longitude(),
  speedOverGroundInMeterPerSecond(),
  trackAngleTrue(),
  fixDate(),
  magneticDeviation(),
  fixQuality()
{

}

//-----------------------------------------------------------------------------
RMCFrame::RMCFrame(const std::string & nmeaRMCSentence)
{

  assert(NMEAParsing::isNMEASentence(nmeaRMCSentence));
  assert(nmeaRMCSentence.substr(3,3) =="RMC");

  //Split sentence in fields
  std::setlocale(LC_ALL, "C");
  std::vector<std::string> fields = NMEAParsing::splitInFields(nmeaRMCSentence);

  //Decode GPS prefix ID
  talkerId=NMEAParsing::extractTalkerId(fields[0]);

  //Decode sentence
  if((fields.size()>=13 || fields.size()<=15) &&
     nmeaRMCSentence.substr(3,3) == "RMC" &&
     NMEAParsing::computeChecksum(nmeaRMCSentence) == std::stoi(fields.back(),0,16)){

    //decode fix date
    if(!fields[1].empty())
    {
      fixTime= NMEAParsing::stringToFixTime(fields[1]);
    }

    //decode status
    if(!fields[2].empty())
    {
      status = fields[2] == "A" ? Status::Active : Status::Void;
    }

    //decode latitude
    if(!fields[3].empty() && !fields[4].empty())
    {
      latitude = NMEAParsing::stringToLatitude(fields[3],fields[4]);
    }

    //decode longitude
    if(!fields[5].empty() && !fields[6].empty())
    {
      longitude =  NMEAParsing::stringToLongitude(fields[5],fields[6]);
    }

    //decode speed over ground
    if(!fields[7].empty())
    {
      speedOverGroundInMeterPerSecond = std::stod(fields[7])*KNOT_TO_METER_PER_SECOND;
    }

    //decode track angle
    if(!fields[8].empty())
    {
      trackAngleTrue = std::stod(fields[8])/180.*M_PI;
    }

    //decode date
    if(!fields[9].empty())
    {
      fixDate = NMEAParsing::stringToFixDate(fields[9]);
    }

    //decode magnetic variation
    if(!fields[10].empty() && !fields[11].empty())
    {
      magneticDeviation = std::stod(fields[10])/180.*M_PI;

      if(fields[11]=="W")
        magneticDeviation = -*magneticDeviation;
    }

    //decode mode indicator NMEA 2.3 and above
    if(fields.size()>=14)
    {
      fixQuality=modeIndicatorToFixQuality(fields[12]);
    }
  }
}

//-----------------------------------------------------------------------------
std::string RMCFrame::toNMEA() const
{
  std::stringstream ss;

  //encode prefix
  ss<<"$"<<NMEAParsing::talkerIdToString(talkerId)<<"RMC"<<",";

  //encode fixtime
  if(fixTime)
  {
    ss<<NMEAParsing::fixTimeToString(*fixTime);
  }
  ss<<",";

  //encode status
  if(status)
  {
    if(*status==Status::Active)
    {
      ss<<"A";
    }
    else
    {
      ss<<"V";
    }
  }
  ss<<",";


  //encode latitude
  if(latitude)
  {
    ss<<NMEAParsing::latitudeToString(*latitude);
  }
  else
  {
    ss<<",";
  }
  ss<<",";


  //encode longitude
  if(longitude)
  {
    ss<<NMEAParsing::longitudeToString(*longitude);
  }
  else
  {
    ss<<",";
  }
  ss<<",";


  //ENcode speed over ground
  if(speedOverGroundInMeterPerSecond)
  {
    ss<<std::setfill('0')<<std::setw(3)<<int(*speedOverGroundInMeterPerSecond/KNOT_TO_METER_PER_SECOND);
    ss<<".";
    ss<<std::setfill('0')<<std::setw(1)<<int(*speedOverGroundInMeterPerSecond/KNOT_TO_METER_PER_SECOND*10)%10;
  }
  ss<<",";

  //Encode track angle
  if(trackAngleTrue)
  {
    ss<<std::setfill('0')<<std::setw(3)<<int(romea::between0And2Pi(*trackAngleTrue)/M_PI*180);
    ss<<".";
    ss<<std::setfill('0')<<std::setw(1)<<int(romea::between0And2Pi(*trackAngleTrue)/M_PI*180*10)%10;
  }
  ss<<",";

  //Encode date
  if(fixDate)
  {
    ss<<NMEAParsing::fixDateToString(*fixDate);
  }
  ss<<",";

  //decode magnetic variation
  if(magneticDeviation)
  {
    ss<<*magneticDeviation*180/M_PI<<",";
    if(*magneticDeviation>=0)

    {
      ss<<"E";
    }
    else
    {
      ss<<"W";

    }
  }
  else
  {
    ss<<",";
  }

  ss.seekp(0, std::ios::end);
  int checksum =NMEAParsing::computeChecksum(ss.str(),1,ss.tellp());
  ss<<"*"<<std::hex<<std::setfill('0')<< std::setw (2)<<checksum;

  return ss.str();

}



//-----------------------------------------------------------------------------
double trackAngleToCourseAngle(const double &trackAngle,
                               const double &vehiclelLinearSpeed)
{
  double courseAngle = M_PI_2 -trackAngle;
  return between0And2Pi(vehiclelLinearSpeed<0 ? courseAngle+M_PI : courseAngle);
}

//-----------------------------------------------------------------------------
std::ostream& operator<<(std::ostream & os, const RMCFrame & frame)
{
  {
    os << "RMC frame " << std::endl;

    os << "GPS system : " << description(frame.talkerId) << std::endl;

    os << "fixTime : ";
    if(frame.fixTime)
      os << *frame.fixTime;
    os <<std::endl;

    os << "status : ";
    if(frame.status)
    {
      if(frame.status==RMCFrame::Status::Active)
      {
        os<< "Active";
      }
      else
      {
        os<< "Void";
      }
    }
    os <<std::endl;

    os << "latitude : ";
    if(frame.latitude)
      os <<*frame.latitude;//*180/PI;
    os <<std::endl;

    os << "longitude : " ;
    if(frame.longitude)
      os <<*frame.longitude;//*180/PI;
    os <<std::endl;

    os << "speed over ground : " ;
    if(frame.speedOverGroundInMeterPerSecond)
      os <<*frame.speedOverGroundInMeterPerSecond;
    os <<std::endl;

    os << "track angle : " ;
    if(frame.trackAngleTrue)
      os <<*frame.trackAngleTrue;//*180/PI;
    os <<std::endl;

    os << "date : " ;
    if(frame.fixDate)
      os <<*frame.fixDate;
    os <<std::endl;

    os << "magnetic deviation : " ;
    if(frame.magneticDeviation)
      os <<*frame.magneticDeviation;
    os <<std::endl;

    os << "fix quality  : " ;
    if(frame.fixQuality)
      os <<static_cast<int>(*frame.fixQuality);
    os <<std::endl;

    return os;
  }

}


}
