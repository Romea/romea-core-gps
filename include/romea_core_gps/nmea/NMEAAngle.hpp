#ifndef romea_NMEAAngle_hpp
#define romea_NMEAAngle_hpp

//std
#include <string>
#include <ostream>
#include <iomanip>

namespace romea
{


template <class CardinalDirections>
class NmeaAngle
{


public:

  NmeaAngle(const double & angle);

  NmeaAngle(const int & degrees,
            const int & minutes,
            const double & microSeconds,
            const CardinalDirections &direction);

  virtual ~NmeaAngle()=default;

  const int & getDegrees()const;

  const int & getMinutes()const;

  const double & getSeconds()const;

  const CardinalDirections & getDirection()const;

  double toDouble()const;



protected :

  int degrees_;
  int minutes_;
  double seconds_;
  CardinalDirections direction_;

};

//-----------------------------------------------------------------------------
template <class CardinalDirections>
std::ostream& operator<<(std::ostream & os, const NmeaAngle<CardinalDirections> & mmeaAngle)
{
  int degrees = mmeaAngle.getDegrees();
  int minutes  = mmeaAngle.getMinutes();
  double seconds = mmeaAngle.getSeconds();
  std::string direction = toString(mmeaAngle.getDirection());

  os <<std::setfill('0');
  os <<degrees<<"d";
  os <<std::setw(2)<<minutes<<"m";
  os <<std::setw(2)<<seconds<<"s "<< direction;
  return os;
}

}

#endif
