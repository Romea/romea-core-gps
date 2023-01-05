// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// std
#include <cassert>
#include <iomanip>
#include <sstream>

// romea
#include "romea_core_gps/nmea/NMEAFixTime.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
FixTime::FixTime(
  int hours,
  int minutes,
  double seconds)
: hours_(hours),
  minutes_(minutes),
  seconds_(seconds)
{
  assert(hours < 24);
  assert(minutes < 60);
  assert(seconds < 60);
}

//-----------------------------------------------------------------------------
FixTime::FixTime(
  int seconds,
  int nanoseconds)
: hours_(0),
  minutes_(0),
  seconds_(0)
{
  seconds = seconds % (24 * 60 * 60);
  hours_ = seconds / 3600;
  seconds -= hours_ * 3600;
  minutes_ = seconds / 60;
  seconds -= minutes_ * 60;
  seconds_ = seconds + nanoseconds / 1000000000.;

  assert(hours_ < 24);
  assert(minutes_ < 60);
  assert(seconds_ < 60);
}


//-----------------------------------------------------------------------------
int FixTime::getHours()const
{
  return hours_;
}

//-----------------------------------------------------------------------------
int FixTime::getMinutes()const
{
  return minutes_;
}

//-----------------------------------------------------------------------------
double FixTime::getSeconds()const
{
  return seconds_;
}

//-----------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const FixTime & fixTime)
{
  int hours = fixTime.getHours();
  int minutes = fixTime.getMinutes();
  int seconds = fixTime.getSeconds();
  int milliseconds = (fixTime.getSeconds() - seconds) * 1000;

  os << std::setfill('0');
  os << std::setw(2) << hours << ":";
  os << std::setw(2) << minutes << ":";
  os << std::setw(2) << seconds << ".";
  os << std::setw(3) << milliseconds;
  return os;
}

}  // namespace romea
