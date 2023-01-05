// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// std
#include <cassert>
#include <iomanip>
#include <sstream>

// romea
#include "romea_core_gps/nmea/NMEAFixDate.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
FixDate::FixDate(
  int years,
  int months,
  int days)
: years_(years),
  months_(months),
  days_(days)
{
  assert(years_ < 100);
}

//-----------------------------------------------------------------------------
int FixDate::getYears()const
{
  return years_;
}

//-----------------------------------------------------------------------------
int FixDate::getMonths()const
{
  return months_;
}

//-----------------------------------------------------------------------------
double FixDate::getDays()const
{
  return days_;
}

//-----------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const FixDate & fixDate)
{
  int years = fixDate.getYears();
  int month = fixDate.getMonths();
  int days = fixDate.getDays();

  os << std::setfill('0');
  os << std::setw(2) << days << "/";
  os << std::setw(2) << month << "/";
  os << std::setw(2) << years;
  return os;
}

}  // namespace romea
