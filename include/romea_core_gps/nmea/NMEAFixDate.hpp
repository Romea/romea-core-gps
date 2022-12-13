#ifndef ROMEA_CORE_GPS_NMEA_NMEAFIXDATE_HPP_ 
#define ROMEA_CORE_GPS_NMEA_NMEAFIXDATE_HPP_ 

// std
#include <string>

namespace romea
{

class FixDate
{
public:
  FixDate(int years,
          int months,
          int days);

  int getYears()const;

  int getMonths()const;

  double getDays()const;

private :

  int years_;
  int months_;
  double days_;
};

std::ostream& operator<<(std::ostream & os, const FixDate & fixDate);

}  // namespace romea

#endif  // ROMEA_CORE_GPS_NMEA_NMEAFIXDATE_HPP_ 
