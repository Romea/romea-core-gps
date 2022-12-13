#ifndef ROMEA_CORE_GPS_NMEA_NMEAFIXTIME_HPP_
#define ROMEA_CORE_GPS_NMEA_NMEAFIXTIME_HPP_

// std
#include <string>

namespace romea
{

class FixTime
{
public:
  FixTime(int hours,
          int minutes,
          double seconds);

  FixTime(int seconds,
          int nanoseconds);

  int getHours()const;

  int getMinutes()const;

  double getSeconds()const;

  std::string toString()const;

private :

  int hours_;
  int minutes_;
  double seconds_;
};

std::ostream& operator<<(std::ostream & os, const FixTime & FixTime);

}  // namespace romea

#endif  // ROMEA_CORE_GPS_NMEA_NMEAFIXTIME_HPP_
