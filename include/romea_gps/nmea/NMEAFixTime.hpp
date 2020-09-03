#ifndef romea_NMEAFixTime_hpp
#define romea_NMEAFixTime_hpp

//std
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

}


#endif
