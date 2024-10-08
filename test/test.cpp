// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


// std
#include <iostream>
#include <limits>
#include <string>
#include <list>

// gtest
#include "gtest/gtest.h"

// romea
#include "romea_core_gps/GPSReceiver.hpp"


TEST(TestGPS, testEUREs)
{
  romea::core::GPSReceiverEUREs EUREs;
  EXPECT_DOUBLE_EQ(EUREs.get(romea::core::FixQuality::GPS_FIX), 3.0);
  EXPECT_DOUBLE_EQ(EUREs.get(romea::core::FixQuality::PPS_FIX), 3.0);
  EXPECT_DOUBLE_EQ(EUREs.get(romea::core::FixQuality::DGPS_FIX), 0.7);
  EXPECT_DOUBLE_EQ(EUREs.get(romea::core::FixQuality::FLOAT_RTK_FIX), 0.25);
  EXPECT_DOUBLE_EQ(EUREs.get(romea::core::FixQuality::RTK_FIX), 0.03);
  EXPECT_DOUBLE_EQ(
    EUREs.get(romea::core::FixQuality::INVALID_FIX),
    std::numeric_limits<double>::max());
  EXPECT_DOUBLE_EQ(EUREs.get(romea::core::FixQuality::SIMULATION_FIX), 0.03);
  EXPECT_ANY_THROW(EUREs.get(romea::core::FixQuality::MANUAL_FIX));
  EXPECT_ANY_THROW(EUREs.get(romea::core::FixQuality::ESTIMATED_FIX));
}

TEST(TestGPS, testLatitude)
{
  {
    romea::core::Latitude latitude =
      romea::core::NMEAParsing::stringToLatitude("4533.53366", "N");
    EXPECT_NEAR(latitude.toDouble(), 0.795153, 0.01);
    EXPECT_FALSE(romea::core::NMEAParsing::latitudeToString(latitude).compare("4533.53366,N"));

    romea::core::Latitude latitude2(latitude.toDouble());
    EXPECT_EQ(latitude.getDegrees(), latitude2.getDegrees());
    EXPECT_EQ(latitude.getMinutes(), latitude2.getMinutes());
    EXPECT_NEAR(latitude.getSeconds(), latitude2.getSeconds(), 0.00001);
  }

  {
    romea::core::Latitude latitude =
      romea::core::NMEAParsing::stringToLatitude("4533.53366", "S");
    EXPECT_NEAR(latitude.toDouble(), -0.795153, 0.01);
    EXPECT_FALSE(romea::core::NMEAParsing::latitudeToString(latitude).compare("4533.53366,S"));

    romea::core::Latitude latitude2(latitude.toDouble());
    EXPECT_EQ(latitude.getDegrees(), latitude2.getDegrees());
    EXPECT_EQ(latitude.getMinutes(), latitude2.getMinutes());
    EXPECT_NEAR(latitude.getSeconds(), latitude2.getSeconds(), 0.00001);
  }
}

TEST(TestGPS, testLongitude)
{
  {
    romea::core::Longitude longitude =
      romea::core::NMEAParsing::stringToLongitude("00315.44427", "E");
    EXPECT_NEAR(longitude.toDouble(), 0.0568524, 0.01);
    EXPECT_FALSE(romea::core::NMEAParsing::longitudeToString(longitude).compare("00315.44427,E"));

    romea::core::Longitude longitude2(longitude.toDouble());
    EXPECT_EQ(longitude.getDegrees(), longitude2.getDegrees());
    EXPECT_EQ(longitude.getMinutes(), longitude2.getMinutes());
    EXPECT_NEAR(longitude.getSeconds(), longitude2.getSeconds(), 0.00001);
  }

  {
    romea::core::Longitude longitude =
      romea::core::NMEAParsing::stringToLongitude("00315.44427", "W");
    EXPECT_NEAR(longitude.toDouble(), -0.0568524, 0.01);
    EXPECT_FALSE(romea::core::NMEAParsing::longitudeToString(longitude).compare("00315.44427,W"));

    romea::core::Longitude longitude2(longitude.toDouble());
    EXPECT_EQ(longitude.getDegrees(), longitude2.getDegrees());
    EXPECT_EQ(longitude.getMinutes(), longitude2.getMinutes());
    EXPECT_NEAR(longitude.getSeconds(), longitude2.getSeconds(), 0.00001);
  }
}

TEST(TestGPS, testFixDate)
{
  romea::core::FixDate fixDate = romea::core::NMEAParsing::stringToFixDate("111213");
  EXPECT_EQ(fixDate.getDays(), 11);
  EXPECT_EQ(fixDate.getMonths(), 12);
  EXPECT_EQ(fixDate.getYears(), 13);
  EXPECT_FALSE(romea::core::NMEAParsing::fixDateToString(fixDate).compare("111213"));
}

TEST(TestGPS, testFixTime)
{
  romea::core::FixTime fixTime = romea::core::NMEAParsing::stringToFixTime("120648.800");
  EXPECT_EQ(fixTime.getHours(), 12);
  EXPECT_EQ(fixTime.getMinutes(), 6);
  EXPECT_NEAR(fixTime.getSeconds(), 48.800, 0.001);
  EXPECT_FALSE(romea::core::NMEAParsing::fixTimeToString(fixTime).compare("120648.800"));
}

TEST(TestGPS, testDecodeGGASentence)
{
  {
    std::string ggaSentence =
      "$GPGGA,120648.80,4533.53366,N,00315.44427,E,2,08,2.17,382.4,M,47.5,M,,0000*5B";
    romea::core::GGAFrame frame(ggaSentence);
    EXPECT_NEAR(frame.latitude->toDouble(), 0.795153, 0.01);
    EXPECT_NEAR(frame.longitude->toDouble(), 0.0568524, 0.01);

    std::cout << frame.latitude->getDegrees() << std::endl;
    std::cout << frame.latitude->getMinutes() << std::endl;
    std::cout << frame.latitude->getSeconds() << std::endl;

    std::cout << romea::core::Latitude(0.795153).getDegrees() << std::endl;
    std::cout << romea::core::Latitude(0.795153).getMinutes() << std::endl;
    std::cout << romea::core::Latitude(0.795153).getSeconds() << std::endl;

    EXPECT_EQ(*frame.fixQuality, romea::core::FixQuality::DGPS_FIX);
    EXPECT_EQ(*frame.numberSatellitesUsedToComputeFix, 8);
    EXPECT_EQ(*frame.horizontalDilutionOfPrecision, 2.17);
    EXPECT_EQ(*frame.geoidHeight, 47.5);
    EXPECT_EQ(*frame.altitudeAboveGeoid, 382.4);
    EXPECT_EQ(frame.dgpsCorrectionAgeInSecond.has_value(), false);
    EXPECT_EQ(
      romea::core::NMEAParsing::extractSentenceId(ggaSentence),
      romea::core::NMEAParsing::SentenceID::GGA);
    EXPECT_EQ(romea::core::GGAFrame(frame.toNMEA()).toNMEA().compare(frame.toNMEA()), 0);

    std::cout << ggaSentence << std::endl;
    std::cout << frame.toNMEA() << std::endl;
    std::cout << frame << std::endl;
  }

  {
    std::string ggaSentence = "$GPGGA,085938.00,,,,,0,03,,,M,,M,,*44";
    romea::core::GGAFrame frame(ggaSentence);
    EXPECT_EQ(frame.latitude.has_value(), false);
    EXPECT_EQ(frame.longitude.has_value(), false);
    EXPECT_EQ(*frame.fixQuality, romea::core::FixQuality::INVALID_FIX);
    EXPECT_EQ(*frame.numberSatellitesUsedToComputeFix, 3);
    EXPECT_EQ(frame.horizontalDilutionOfPrecision.has_value(), false);
    EXPECT_EQ(frame.geoidHeight.has_value(), false);
    EXPECT_EQ(frame.altitudeAboveGeoid.has_value(), false);
    EXPECT_EQ(frame.dgpsCorrectionAgeInSecond.has_value(), false);
    EXPECT_EQ(
      romea::core::NMEAParsing::extractSentenceId(ggaSentence),
      romea::core::NMEAParsing::SentenceID::GGA);
    EXPECT_EQ(romea::core::GGAFrame(frame.toNMEA()).toNMEA().compare(frame.toNMEA()), 0);

    std::cout << ggaSentence << std::endl;
    std::cout << frame.toNMEA() << std::endl;
    std::cout << frame << std::endl;
  }

  {
    std::string ggaSentence = "$GPGGA,091641.70,,,,,5,,00.0,,M,,M,01,*5E";
    romea::core::GGAFrame frame(ggaSentence);

    std::cout << ggaSentence << std::endl;
    std::cout << frame.toNMEA() << std::endl;
    std::cout << frame << std::endl;

    EXPECT_EQ(frame.latitude.has_value(), false);
    EXPECT_EQ(frame.longitude.has_value(), false);
    EXPECT_EQ(*frame.fixQuality, romea::core::FixQuality::FLOAT_RTK_FIX);
    EXPECT_EQ(frame.numberSatellitesUsedToComputeFix.has_value(), false);
    EXPECT_EQ(frame.horizontalDilutionOfPrecision.has_value(), true);
    EXPECT_EQ(frame.geoidHeight.has_value(), false);
    EXPECT_EQ(frame.altitudeAboveGeoid.has_value(), false);
    EXPECT_EQ(frame.dgpsCorrectionAgeInSecond.has_value(), true);
    EXPECT_EQ(
      romea::core::NMEAParsing::extractSentenceId(ggaSentence),
      romea::core::NMEAParsing::SentenceID::GGA);
    EXPECT_EQ(romea::core::GGAFrame(frame.toNMEA()).toNMEA().compare(frame.toNMEA()), 0);
  }
}

TEST(TestGPS, testDecodeRMCSentence)
{
  std::string rmcSentence =
    "$GPRMC,090433.00,A,4546.4918963,N,00308.7532503,E,0.0,0.0,111213,0.3,E,D*3A";
  romea::core::RMCFrame frame(rmcSentence);
  EXPECT_NEAR(frame.latitude->toDouble(), 0.798922, 0.01);
  EXPECT_NEAR(frame.longitude->toDouble(), 0.0549061, 0.01);
  EXPECT_NEAR(*frame.speedOverGroundInMeterPerSecond, 0, 0.01);
  EXPECT_NEAR(*frame.trackAngleTrue, 0, 0.01);
  EXPECT_NEAR(*frame.magneticDeviation, 0.00523599, 0.0001);
  EXPECT_EQ(
    romea::core::NMEAParsing::extractSentenceId(rmcSentence),
    romea::core::NMEAParsing::SentenceID::RMC);
  EXPECT_EQ(romea::core::RMCFrame(frame.toNMEA()).toNMEA().compare(frame.toNMEA()), 0);

  std::cout << rmcSentence << std::endl;
  std::cout << frame.toNMEA() << std::endl;
  std::cout << frame << std::endl;

  romea::core::TimePoint t = std::chrono::high_resolution_clock::now();
  std::cout << "Fix date " << romea::core::NMEAParsing::timePointToFixDate(t) << std::endl;
  std::cout << "Fix time " << romea::core::NMEAParsing::timePointToFixTime(t) << std::endl;
}

TEST(TestGPS, testDecodeGSVSentence)
{
  {
    std::string gsvSentence = "$GPGSV,6,3,21,15,00,021,,16,29,187,41,18,27,050,,19,66,309,*74";
    romea::core::GSVFrame frame(gsvSentence);
    EXPECT_EQ(*frame.numberOfSentences, 6);
    EXPECT_EQ(*frame.sentenceNumber, 3);
    EXPECT_EQ(*frame.numberOfSatellitesInView, 21);
    EXPECT_EQ(*frame.satellitesInfo[0].PRNNumber, 15);
    EXPECT_EQ(*frame.satellitesInfo[0].elevation, 0);
    EXPECT_EQ(*frame.satellitesInfo[0].azimut, 21);
    EXPECT_EQ(frame.satellitesInfo[0].SNR.has_value(), false);
    EXPECT_EQ(*frame.satellitesInfo[1].PRNNumber, 16);
    EXPECT_EQ(*frame.satellitesInfo[1].elevation, 29);
    EXPECT_EQ(*frame.satellitesInfo[1].azimut, 187);
    EXPECT_EQ(*frame.satellitesInfo[1].SNR, 41);
    EXPECT_EQ(*frame.satellitesInfo[2].PRNNumber, 18);
    EXPECT_EQ(*frame.satellitesInfo[2].elevation, 27);
    EXPECT_EQ(*frame.satellitesInfo[2].azimut, 50);
    EXPECT_EQ(frame.satellitesInfo[2].SNR.has_value(), false);
    EXPECT_EQ(*frame.satellitesInfo[3].PRNNumber, 19);
    EXPECT_EQ(*frame.satellitesInfo[3].elevation, 66);
    EXPECT_EQ(*frame.satellitesInfo[3].azimut, 309);
    EXPECT_EQ(frame.satellitesInfo[3].SNR.has_value(), false);
    EXPECT_EQ(frame.signalID.has_value(), false);
    EXPECT_EQ(
      romea::core::NMEAParsing::extractSentenceId(gsvSentence),
      romea::core::NMEAParsing::SentenceID::GSV);
  }

  {
    std::string gsvSentence = "$GPGSV,6,6,21,40,17,119,*41";
    romea::core::GSVFrame frame(gsvSentence);
    EXPECT_EQ(*frame.numberOfSentences, 6);
    EXPECT_EQ(*frame.sentenceNumber, 6);
    EXPECT_EQ(*frame.numberOfSatellitesInView, 21);
    EXPECT_EQ(*frame.satellitesInfo[0].PRNNumber, 40);
    EXPECT_EQ(*frame.satellitesInfo[0].elevation, 17);
    EXPECT_EQ(*frame.satellitesInfo[0].azimut, 119);
    EXPECT_EQ(frame.satellitesInfo[0].SNR.has_value(), false);
    EXPECT_EQ(frame.signalID.has_value(), false);
    EXPECT_EQ(
      romea::core::NMEAParsing::extractSentenceId(gsvSentence),
      romea::core::NMEAParsing::SentenceID::GSV);
  }

  {
    std::string gsvSentence = "$GLGSV,3,3,10,83,01,300,,88,05,112,*6A";
    romea::core::GSVFrame frame(gsvSentence);
    EXPECT_EQ(*frame.numberOfSentences, 3);
    EXPECT_EQ(*frame.sentenceNumber, 3);
    EXPECT_EQ(*frame.numberOfSatellitesInView, 10);
    EXPECT_EQ(*frame.satellitesInfo[0].PRNNumber, 83);
    EXPECT_EQ(*frame.satellitesInfo[0].elevation, 1);
    EXPECT_EQ(*frame.satellitesInfo[0].azimut, 300);
    EXPECT_EQ(frame.satellitesInfo[0].SNR.has_value(), false);
    EXPECT_EQ(*frame.satellitesInfo[1].PRNNumber, 88);
    EXPECT_EQ(*frame.satellitesInfo[1].elevation, 05);
    EXPECT_EQ(*frame.satellitesInfo[1].azimut, 112);
    EXPECT_EQ(frame.satellitesInfo[1].SNR.has_value(), false);
    EXPECT_EQ(frame.signalID.has_value(), false);
    EXPECT_EQ(
      romea::core::NMEAParsing::extractSentenceId(gsvSentence),
      romea::core::NMEAParsing::SentenceID::GSV);
  }

  {
    std::string gsvSentence =
      "$GAGSV,3,1,09,03,01,036,18,07,61,158,37,08,46,059,38,13,47,117,38,2*7B";
    romea::core::GSVFrame frame(gsvSentence);
    EXPECT_EQ(*frame.numberOfSentences, 3);
    EXPECT_EQ(*frame.sentenceNumber, 1);
    EXPECT_EQ(*frame.numberOfSatellitesInView, 9);
    EXPECT_EQ(*frame.signalID, 2);
    EXPECT_EQ(
      romea::core::NMEAParsing::extractSentenceId(gsvSentence),
      romea::core::NMEAParsing::SentenceID::GSV);
  }
}


TEST(TestGPS, testSattellitesInView)
{
  {
    romea::core::GPSReceiver gps;

    gps.updateSatellitesViews("$GPGSV,4,1,14,03,31,286,48,06,54,291,53,07,03,335,35,16,70,294,49*76");  //NOLINT
    gps.updateSatellitesViews("$GPGSV,4,2,14,18,35,121,33,19,11,273,40,21,63,064,47,22,19,157,*71");
    gps.updateSatellitesViews("$GPGSV,4,3,14,27,43,285,47,29,10,086,36,30,30,089,45,31,06,195,*7D");
    gps.updateSatellitesViews("$GPGSV,4,4,14,33,34,205,,39,33,150,*72");

    const romea::core::SatellitesInView & satellites = gps.getSatellitesInView();
    const std::list<romea::core::TalkerId> talkerIds = satellites.getTalkerIds();

    EXPECT_EQ(talkerIds.size(), 1);
    EXPECT_EQ(satellites.getSatellitesInfo(romea::core::TalkerId::GP).size(), 14);
    // EXPECT_EQ(ublox.getGPSEnvironment().getSatellitesViewAnalysis().numberOfVisibleSatellites,10);
    // EXPECT_EQ(ublox.getGPSEnvironment().getSatellitesViewAnalysis().numberOfHiddenSatellites,4);
  }

  {
    romea::core::GPSReceiver gps;

    gps.updateSatellitesViews(
      "$GPGSV,4,1,16, 03,31,288,44, 06,54,292,48, 07,03,336,28, 16,70,294,49*70");
    gps.updateSatellitesViews(
      "$GPGSV,4,2,16, 18,35,122,27, 19,11,274,39, 21,63,066,47, 22,19,158,00*71");
    gps.updateSatellitesViews(
      "$GPGSV,4,3,16, 27,43,286,46, 29,10,086,40, 30,30,090,42, 31,06,196,00*70");
    gps.updateSatellitesViews(
      "$GPGSV,4,4,16, 33,34,206,00, 37,35,156,00, 39,33,152,00, 44,10,112,00*72");
    gps.updateSatellitesViews(
      "$GLGSV,3,1,10, 65,03,010,00, 66,28,052,44, 67,25,112,25, 73,45,300,46*6D");
    gps.updateSatellitesViews(
      "$GLGSV,3,2,10, 74,09,340,41, 79,04,186,00, 80,42,222,31, 81,19,066,42*61");
    gps.updateSatellitesViews("$GLGSV,3,3,10, 82,61,022,51, 83,32,276,45*65");

    const romea::core::SatellitesInView & satellites = gps.getSatellitesInView();
    const std::list<romea::core::TalkerId> GPSIds = satellites.getTalkerIds();

    EXPECT_EQ(GPSIds.size(), 2);
    EXPECT_EQ(
      std::binary_search(
        std::cbegin(GPSIds), std::cend(GPSIds), romea::core::TalkerId::GP), 1);
    EXPECT_EQ(
      std::binary_search(
        std::cbegin(GPSIds), std::cend(GPSIds), romea::core::TalkerId::GL), 1);
    EXPECT_EQ(satellites.getSatellitesInfo(romea::core::TalkerId::GP).size(), 16);
    EXPECT_EQ(satellites.getSatellitesInfo(romea::core::TalkerId::GL).size(), 10);
  }
}

TEST(TestGPS, testFixQualityToDescription)
{
  EXPECT_STREQ(
    romea::core::description(romea::core::FixQuality::INVALID_FIX).c_str(), "invalid fix (0)");
  EXPECT_STREQ(
    romea::core::description(romea::core::FixQuality::GPS_FIX).c_str(), "gps fix (1)");
  EXPECT_STREQ(
    romea::core::description(romea::core::FixQuality::DGPS_FIX).c_str(), "dgps fix (2)");
  EXPECT_STREQ(
    romea::core::description(romea::core::FixQuality::PPS_FIX).c_str(), "pps fix (3)");
  EXPECT_STREQ(
    romea::core::description(romea::core::FixQuality::RTK_FIX).c_str(), "rtk fix (4)");
  EXPECT_STREQ(
    romea::core::description(romea::core::FixQuality::FLOAT_RTK_FIX).c_str(), "float rtk fix (5)");
  EXPECT_STREQ(
    romea::core::description(romea::core::FixQuality::ESTIMATED_FIX).c_str(), "estimated fix (6)");
  EXPECT_STREQ(
    romea::core::description(romea::core::FixQuality::MANUAL_FIX).c_str(), "manual fix (7)");
  EXPECT_STREQ(
    romea::core::description(romea::core::FixQuality::SIMULATION_FIX).c_str(),
    "simulation fix (8)");
}

TEST(TestGPS, testFixQualityComparison)
{
  EXPECT_TRUE(romea::core::FixQuality::RTK_FIX >= romea::core::FixQuality::FLOAT_RTK_FIX);
  EXPECT_TRUE(romea::core::FixQuality::FLOAT_RTK_FIX >= romea::core::FixQuality::DGPS_FIX);
  EXPECT_TRUE(romea::core::FixQuality::DGPS_FIX >= romea::core::FixQuality::GPS_FIX);
  EXPECT_TRUE(romea::core::FixQuality::GPS_FIX >= romea::core::FixQuality::PPS_FIX);
}

TEST(TestGPS, testTalkerIdToAcrnonym)
{
  EXPECT_STREQ(romea::core::acronym(romea::core::TalkerId::GN).c_str(), "GNSS");
  EXPECT_STREQ(romea::core::acronym(romea::core::TalkerId::GA).c_str(), "GALILEO");
  EXPECT_STREQ(romea::core::acronym(romea::core::TalkerId::GP).c_str(), "NAVSTAR");
  EXPECT_STREQ(romea::core::acronym(romea::core::TalkerId::GB).c_str(), "BEIDOU");
  EXPECT_STREQ(romea::core::acronym(romea::core::TalkerId::BD).c_str(), "BEIDOU");
  EXPECT_STREQ(romea::core::acronym(romea::core::TalkerId::GL).c_str(), "GLONASS");
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
