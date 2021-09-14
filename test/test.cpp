// gtest
#include <gtest/gtest.h>

//romea
#include <romea_gps/GPSReceiver.hpp>
#include <iostream>

TEST(TestGPS, testLatitude)
{
  {
    romea::Latitude latitude = romea::NMEAParsing::stringToLatitude("4533.53366","N");
    EXPECT_NEAR(latitude.toDouble(),0.795153,0.01);
    EXPECT_FALSE(romea::NMEAParsing::latitudeToString(latitude).compare("4533.53366,N"));

    romea::Latitude latitude2(latitude.toDouble());
    EXPECT_EQ(latitude.getDegrees(),latitude2.getDegrees());
    EXPECT_EQ(latitude.getMinutes(),latitude2.getMinutes());
    EXPECT_NEAR(latitude.getSeconds(),latitude2.getSeconds(),0.00001);


  }

  {
    romea::Latitude latitude = romea::NMEAParsing::stringToLatitude("4533.53366","S");
    EXPECT_NEAR(latitude.toDouble(),-0.795153,0.01);
    EXPECT_FALSE(romea::NMEAParsing::latitudeToString(latitude).compare("4533.53366,S"));

    romea::Latitude latitude2(latitude.toDouble());
    EXPECT_EQ(latitude.getDegrees(),latitude2.getDegrees());
    EXPECT_EQ(latitude.getMinutes(),latitude2.getMinutes());
    EXPECT_NEAR(latitude.getSeconds(),latitude2.getSeconds(),0.00001);
  }

}

TEST(TestGPS, testLongitude)
{
  {
    romea::Longitude longitude = romea::NMEAParsing::stringToLongitude("00315.44427","E");
    EXPECT_NEAR(longitude.toDouble(),0.0568524,0.01);
    EXPECT_FALSE(romea::NMEAParsing::longitudeToString(longitude).compare("00315.44427,E"));

    romea::Longitude longitude2(longitude.toDouble());
    EXPECT_EQ(longitude.getDegrees(),longitude2.getDegrees());
    EXPECT_EQ(longitude.getMinutes(),longitude2.getMinutes());
    EXPECT_NEAR(longitude.getSeconds(),longitude2.getSeconds(),0.00001);
  }

  {
    romea::Longitude longitude = romea::NMEAParsing::stringToLongitude("00315.44427","W");
    EXPECT_NEAR(longitude.toDouble(),-0.0568524,0.01);
    EXPECT_FALSE(romea::NMEAParsing::longitudeToString(longitude).compare("00315.44427,W"));

    romea::Longitude longitude2(longitude.toDouble());
    EXPECT_EQ(longitude.getDegrees(),longitude2.getDegrees());
    EXPECT_EQ(longitude.getMinutes(),longitude2.getMinutes());
    EXPECT_NEAR(longitude.getSeconds(),longitude2.getSeconds(),0.00001);

  }
}

TEST(TestGPS, testFixDate)
{
  romea::FixDate fixDate = romea::NMEAParsing::stringToFixDate("111213");
  EXPECT_EQ(fixDate.getDays(),11);
  EXPECT_EQ(fixDate.getMonths(),12);
  EXPECT_EQ(fixDate.getYears(),13);
  EXPECT_FALSE(romea::NMEAParsing::fixDateToString(fixDate).compare("111213"));
}

TEST(TestGPS, testFixTime)
{
  romea::FixTime fixTime = romea::NMEAParsing::stringToFixTime("120648.800");
  EXPECT_EQ(fixTime.getHours(),12);
  EXPECT_EQ(fixTime.getMinutes(),6);
  EXPECT_NEAR(fixTime.getSeconds(),48.800,0.001);
  EXPECT_FALSE(romea::NMEAParsing::fixTimeToString(fixTime).compare("120648.800"));
}


TEST(TestGPS, testDecodeGGASentence)
{
  {
    std::string ggaSentence = "$GPGGA,120648.80,4533.53366,N,00315.44427,E,2,08,2.17,382.4,M,47.5,M,,0000*5B";
    romea::GGAFrame frame(ggaSentence);
    EXPECT_NEAR(frame.latitude->toDouble(),0.795153,0.01);
    EXPECT_NEAR(frame.longitude->toDouble(),0.0568524,0.01);

    std::cout << frame.latitude->getDegrees() << std::endl;
    std::cout << frame.latitude->getMinutes() << std::endl;
    std::cout << frame.latitude->getSeconds() << std::endl;

    std::cout << romea::Latitude(0.795153).getDegrees() << std::endl;
    std::cout << romea::Latitude(0.795153).getMinutes() << std::endl;
    std::cout << romea::Latitude(0.795153).getSeconds() << std::endl;

    EXPECT_EQ(*frame.fixQuality,romea::FixQuality::DGPS_FIX);
    EXPECT_EQ(*frame.numberSatellitesUsedToComputeFix,8);
    EXPECT_EQ(*frame.horizontalDilutionOfPrecision,2.17);
    EXPECT_EQ(*frame.geoidHeight,47.5);
    EXPECT_EQ(*frame.altitudeAboveGeoid,382.4);
    EXPECT_EQ(frame.dgpsCorrectionAgeInSecond.has_value(),false);
    EXPECT_EQ(romea::NMEAParsing::extractSentenceId(ggaSentence),romea::NMEAParsing::SentenceID::GGA);
    EXPECT_EQ(romea::GGAFrame(frame.toNMEA()).toNMEA().compare(frame.toNMEA()),0);

    std::cout << ggaSentence << std::endl;
    std::cout << frame.toNMEA() << std::endl;
    std::cout << frame << std::endl;

  }

  {
    std::string ggaSentence = "$GPGGA,085938.00,,,,,0,03,,,M,,M,,*44";
    romea::GGAFrame frame(ggaSentence);
    EXPECT_EQ(frame.latitude.has_value(),false);
    EXPECT_EQ(frame.longitude.has_value(),false);
    EXPECT_EQ(*frame.fixQuality,romea::FixQuality::INVALID_FIX);
    EXPECT_EQ(*frame.numberSatellitesUsedToComputeFix,3);
    EXPECT_EQ(frame.horizontalDilutionOfPrecision.has_value(),false);
    EXPECT_EQ(frame.geoidHeight.has_value(),false);
    EXPECT_EQ(frame.altitudeAboveGeoid.has_value(),false);
    EXPECT_EQ(frame.dgpsCorrectionAgeInSecond.has_value(),false);
    EXPECT_EQ(romea::NMEAParsing::extractSentenceId(ggaSentence),romea::NMEAParsing::SentenceID::GGA);
    EXPECT_EQ(romea::GGAFrame(frame.toNMEA()).toNMEA().compare(frame.toNMEA()),0);

    std::cout << ggaSentence << std::endl;
    std::cout << frame.toNMEA() << std::endl;
    std::cout << frame << std::endl;

  }

  {
    std::string ggaSentence =  "$GPGGA,091641.70,,,,,5,,00.0,,M,,M,01,*5E";
    romea::GGAFrame frame(ggaSentence);

    std::cout << ggaSentence << std::endl;
    std::cout << frame.toNMEA() << std::endl;
    std::cout << frame << std::endl;

    EXPECT_EQ(frame.latitude.has_value(),false);
    EXPECT_EQ(frame.longitude.has_value(),false);
    EXPECT_EQ(*frame.fixQuality,romea::FixQuality::FLOAT_RTK_FIX);
    EXPECT_EQ(frame.numberSatellitesUsedToComputeFix.has_value(),false);
    EXPECT_EQ(frame.horizontalDilutionOfPrecision.has_value(),true);
    EXPECT_EQ(frame.geoidHeight.has_value(),false);
    EXPECT_EQ(frame.altitudeAboveGeoid.has_value(),false);
    EXPECT_EQ(frame.dgpsCorrectionAgeInSecond.has_value(),true);
    EXPECT_EQ(romea::NMEAParsing::extractSentenceId(ggaSentence),romea::NMEAParsing::SentenceID::GGA);
    EXPECT_EQ(romea::GGAFrame(frame.toNMEA()).toNMEA().compare(frame.toNMEA()),0);
 }
}

TEST(TestGPS, testDecodeRMCSentence)
{
  std::string rmcSentence = "$GPRMC,090433.00,A,4546.4918963,N,00308.7532503,E,0.0,0.0,111213,0.3,E,D*3A";
  romea::RMCFrame frame(rmcSentence);
  EXPECT_NEAR(frame.latitude->toDouble(),0.798922,0.01);
  EXPECT_NEAR(frame.longitude->toDouble(),0.0549061,0.01);
  EXPECT_NEAR(*frame.speedOverGroundInMeterPerSecond,0,0.01);
  EXPECT_NEAR(*frame.trackAngleTrue,0,0.01);
  EXPECT_NEAR(*frame.magneticDeviation,0.00523599,0.0001);
  EXPECT_EQ(romea::NMEAParsing::extractSentenceId(rmcSentence),romea::NMEAParsing::SentenceID::RMC);
  EXPECT_EQ(romea::RMCFrame(frame.toNMEA()).toNMEA().compare(frame.toNMEA()),0);

  std::cout << rmcSentence << std::endl;
  std::cout << frame.toNMEA() << std::endl;
  std::cout << frame << std::endl;

  romea::TimePoint t = std::chrono::high_resolution_clock::now();
  std::cout <<"Fix date " << romea::NMEAParsing::timePointToFixDate(t) << std::endl;
  std::cout <<"Fix time " << romea::NMEAParsing::timePointToFixTime(t) << std::endl;

}

TEST(TestGPS, testDecodeGSVSentence)
{
  {
    std::string gsvSentence = "$GPGSV,6,3,21,15,00,021,,16,29,187,41,18,27,050,,19,66,309,*74";
    romea::GSVFrame frame(gsvSentence);
    EXPECT_EQ(*frame.numberOfSentences,6);
    EXPECT_EQ(*frame.sentenceNumber,3);
    EXPECT_EQ(*frame.numberOfSatellitesInView,21);
    EXPECT_EQ(*frame.satellitesInfo[0].PRNNumber,15);
    EXPECT_EQ(*frame.satellitesInfo[0].elevation,0);
    EXPECT_EQ(*frame.satellitesInfo[0].azimut,21);
    EXPECT_EQ(frame.satellitesInfo[0].SNR.has_value(),false);
    EXPECT_EQ(*frame.satellitesInfo[1].PRNNumber,16);
    EXPECT_EQ(*frame.satellitesInfo[1].elevation,29);
    EXPECT_EQ(*frame.satellitesInfo[1].azimut,187);
    EXPECT_EQ(*frame.satellitesInfo[1].SNR,41);
    EXPECT_EQ(*frame.satellitesInfo[2].PRNNumber,18);
    EXPECT_EQ(*frame.satellitesInfo[2].elevation,27);
    EXPECT_EQ(*frame.satellitesInfo[2].azimut,50);
    EXPECT_EQ(frame.satellitesInfo[2].SNR.has_value(),false);
    EXPECT_EQ(*frame.satellitesInfo[3].PRNNumber,19);
    EXPECT_EQ(*frame.satellitesInfo[3].elevation,66);
    EXPECT_EQ(*frame.satellitesInfo[3].azimut,309);
    EXPECT_EQ(frame.satellitesInfo[3].SNR.has_value(),false);
    EXPECT_EQ(frame.signalID.has_value(),false);
    EXPECT_EQ(romea::NMEAParsing::extractSentenceId(gsvSentence),romea::NMEAParsing::SentenceID::GSV);
  }

  {
    std::string gsvSentence = "$GPGSV,6,6,21,40,17,119,*41";
    romea::GSVFrame frame(gsvSentence);
    EXPECT_EQ(*frame.numberOfSentences,6);
    EXPECT_EQ(*frame.sentenceNumber,6);
    EXPECT_EQ(*frame.numberOfSatellitesInView,21);
    EXPECT_EQ(*frame.satellitesInfo[0].PRNNumber,40);
    EXPECT_EQ(*frame.satellitesInfo[0].elevation,17);
    EXPECT_EQ(*frame.satellitesInfo[0].azimut,119);
    EXPECT_EQ(frame.satellitesInfo[0].SNR.has_value(),false);
    EXPECT_EQ(frame.signalID.has_value(),false);
    EXPECT_EQ(romea::NMEAParsing::extractSentenceId(gsvSentence),romea::NMEAParsing::SentenceID::GSV);
  }

  {
    std::string gsvSentence = "$GLGSV,3,3,10,83,01,300,,88,05,112,*6A";
    romea::GSVFrame frame(gsvSentence);
    EXPECT_EQ(*frame.numberOfSentences,3);
    EXPECT_EQ(*frame.sentenceNumber,3);
    EXPECT_EQ(*frame.numberOfSatellitesInView,10);
    EXPECT_EQ(*frame.satellitesInfo[0].PRNNumber,83);
    EXPECT_EQ(*frame.satellitesInfo[0].elevation,1);
    EXPECT_EQ(*frame.satellitesInfo[0].azimut,300);
    EXPECT_EQ(frame.satellitesInfo[0].SNR.has_value(),false);
    EXPECT_EQ(*frame.satellitesInfo[1].PRNNumber,88);
    EXPECT_EQ(*frame.satellitesInfo[1].elevation,05);
    EXPECT_EQ(*frame.satellitesInfo[1].azimut,112);
    EXPECT_EQ(frame.satellitesInfo[1].SNR.has_value(),false);
    EXPECT_EQ(frame.signalID.has_value(),false);
    EXPECT_EQ(romea::NMEAParsing::extractSentenceId(gsvSentence),romea::NMEAParsing::SentenceID::GSV);
  }

  {
    std::string gsvSentence="$GAGSV,3,1,09,03,01,036,18,07,61,158,37,08,46,059,38,13,47,117,38,2*7B";
    romea::GSVFrame frame(gsvSentence);
    EXPECT_EQ(*frame.numberOfSentences,3);
    EXPECT_EQ(*frame.sentenceNumber,1);
    EXPECT_EQ(*frame.numberOfSatellitesInView,9);
    EXPECT_EQ(*frame.signalID,2);
    EXPECT_EQ(romea::NMEAParsing::extractSentenceId(gsvSentence),romea::NMEAParsing::SentenceID::GSV);

  }
}


TEST(TestGPS, testSattellitesInView)
{
  {
    romea::GPSReceiver gps;

    gps.updateSatellitesViews("$GPGSV,4,1,14,03,31,286,48,06,54,291,53,07,03,335,35,16,70,294,49*76");
    gps.updateSatellitesViews("$GPGSV,4,2,14,18,35,121,33,19,11,273,40,21,63,064,47,22,19,157,*71");
    gps.updateSatellitesViews("$GPGSV,4,3,14,27,43,285,47,29,10,086,36,30,30,089,45,31,06,195,*7D");
    gps.updateSatellitesViews("$GPGSV,4,4,14,33,34,205,,39,33,150,*72");

    const romea::SatellitesInView &satellites = gps.getSatellitesInView();
    const std::list<romea::TalkerId> talkerIds = satellites.getTalkerIds();

    EXPECT_EQ(talkerIds.size(),1);
    EXPECT_EQ(satellites.getSatellitesInfo(romea::TalkerId::GP).size(),14);
    //EXPECT_EQ(ublox.getGPSEnvironment().getSatellitesViewAnalysis().numberOfVisibleSatellites,10);
    //EXPECT_EQ(ublox.getGPSEnvironment().getSatellitesViewAnalysis().numberOfHiddenSatellites,4);
  }

  {
    romea::GPSReceiver gps;

    gps.updateSatellitesViews("$GPGSV,4,1,16, 03,31,288,44, 06,54,292,48, 07,03,336,28, 16,70,294,49*70");
    gps.updateSatellitesViews("$GPGSV,4,2,16, 18,35,122,27, 19,11,274,39, 21,63,066,47, 22,19,158,00*71");
    gps.updateSatellitesViews("$GPGSV,4,3,16, 27,43,286,46, 29,10,086,40, 30,30,090,42, 31,06,196,00*70");
    gps.updateSatellitesViews("$GPGSV,4,4,16, 33,34,206,00, 37,35,156,00, 39,33,152,00, 44,10,112,00*72");
    gps.updateSatellitesViews("$GLGSV,3,1,10, 65,03,010,00, 66,28,052,44, 67,25,112,25, 73,45,300,46*6D");
    gps.updateSatellitesViews("$GLGSV,3,2,10, 74,09,340,41, 79,04,186,00, 80,42,222,31, 81,19,066,42*61");
    gps.updateSatellitesViews("$GLGSV,3,3,10, 82,61,022,51, 83,32,276,45*65");

    const romea::SatellitesInView &satellites = gps.getSatellitesInView();
    const std::list<romea::TalkerId> GPSIds = satellites.getTalkerIds();

    EXPECT_EQ(GPSIds.size(),2);
    EXPECT_EQ(std::binary_search(std::cbegin(GPSIds),std::cend(GPSIds),romea::TalkerId::GP),1);
    EXPECT_EQ(std::binary_search(std::cbegin(GPSIds),std::cend(GPSIds),romea::TalkerId::GL),1);
    EXPECT_EQ(satellites.getSatellitesInfo(romea::TalkerId::GP).size(),16);
    EXPECT_EQ(satellites.getSatellitesInfo(romea::TalkerId::GL).size(),10);

    //BOOST_CHECK_CLOSE(proFlex800.getGPSEnvironment().getsatellitesViewAnalysis().hdop,hdop,0.01);
    //EXPECT_EQ(proFlex800.getGPSEnvironment().getSatellitesViewAnalysis().numberOfVisibleSatellites,18);
    //EXPECT_EQ(proFlex800.getGPSEnvironment().getSatellitesViewAnalysis().numberOfHiddenSatellites,8);

  }
}

TEST(TestGPS, testFixQualityToDescription)
{
  EXPECT_STREQ(romea::description(romea::FixQuality::INVALID_FIX).c_str(),"invalid fix (0)");
  EXPECT_STREQ(romea::description(romea::FixQuality::GPS_FIX).c_str(),"gps fix (1)");
  EXPECT_STREQ(romea::description(romea::FixQuality::DGPS_FIX).c_str(),"dgps fix (2)");
  EXPECT_STREQ(romea::description(romea::FixQuality::PPS_FIX).c_str(),"pps fix (3)");
  EXPECT_STREQ(romea::description(romea::FixQuality::RTK_FIX).c_str(),"rtk fix (4)");
  EXPECT_STREQ(romea::description(romea::FixQuality::FLOAT_RTK_FIX).c_str(),"float rtk fix (5)");
  EXPECT_STREQ(romea::description(romea::FixQuality::ESTIMATED_FIX).c_str(),"estimated fix (6)");
  EXPECT_STREQ(romea::description(romea::FixQuality::MANUAL_FIX).c_str(),"manual fix (7)");
  EXPECT_STREQ(romea::description(romea::FixQuality::SIMULATION_FIX).c_str(),"simulation fix (8)");
}

TEST(TestGPS, testFixQualityComparison)
{
  EXPECT_TRUE(romea::FixQuality::RTK_FIX>=romea::FixQuality::FLOAT_RTK_FIX);
  EXPECT_TRUE(romea::FixQuality::FLOAT_RTK_FIX>=romea::FixQuality::DGPS_FIX);
  EXPECT_TRUE(romea::FixQuality::DGPS_FIX>=romea::FixQuality::GPS_FIX);
  EXPECT_TRUE(romea::FixQuality::GPS_FIX>=romea::FixQuality::PPS_FIX);
}

TEST(TestGPS, testTalkerIdToAcrnonym)
{
  EXPECT_STREQ(romea::acronym(romea::TalkerId::GN).c_str(),"GNSS");
  EXPECT_STREQ(romea::acronym(romea::TalkerId::GA).c_str(),"GALILEO");
  EXPECT_STREQ(romea::acronym(romea::TalkerId::GP).c_str(),"NAVSTAR");
  EXPECT_STREQ(romea::acronym(romea::TalkerId::GB).c_str(),"BEIDOU");
  EXPECT_STREQ(romea::acronym(romea::TalkerId::BD).c_str(),"BEIDOU");
  EXPECT_STREQ(romea::acronym(romea::TalkerId::GL).c_str(),"GLONASS");
}

//[ERROR] [1629290064.921145948]: $GPGSV,4,1,13,01,78,066,48,03,73,267,47,04,23,183,40,08,14,167,22,1*60
//[ERROR] [1629290064.921911275]: $GPGSV,4,2,13,14,13,264,27,17,41,304,45,19,18,318,41,21,59,108,46,1*6D
//[ERROR] [1629290064.922709891]: $GPGSV,4,3,13,22,80,032,48,28,,,32,32,16,041,36,36,30,143,39,1*53
//[ERROR] [1629290064.923188603]: $GPGSV,4,4,13,49,37,177,44,1*5E
//[ERROR] [1629290064.923978187]: $GPGSV,2,1,07,01,78,066,38,03,73,267,32,04,23,183,32,08,14,167,12,6*67
//[ERROR] [1629290064.924690757]: $GPGSV,2,2,07,14,13,264,19,17,41,304,30,32,16,041,28,6*55
//[ERROR] [1629290064.925037122]: $GPGSV,1,1,01,31,08,091,,0*56
//[ERROR] [1629290064.925863931]: $GLGSV,3,1,09,65,07,037,31,66,67,042,46,67,54,212,47,73,02,318,22,1*7A
//[ERROR] [1629290064.926688118]: $GLGSV,3,2,09,74,06,001,38,81,63,129,47,82,60,329,42,83,14,320,32,1*76
//[ERROR] [1629290064.927146465]: $GLGSV,3,3,09,88,11,136,26,1*41
//[ERROR] [1629290064.927946901]: $GLGSV,2,1,08,65,07,037,29,66,67,042,39,67,54,212,40,73,02,318,24,3*78
//[ERROR] [1629290064.928742971]: $GLGSV,2,2,08,81,63,129,42,82,60,329,40,83,14,320,37,88,11,136,16,3*7A
//[ERROR] [1629290064.929216208]: $GLGSV,1,1,01,68,04,215,,0*44
//[ERROR] [1629290064.930066992]: $GAGSV,3,1,09,03,01,036,18,07,61,158,37,08,46,059,38,13,47,117,38,2*7B
//[ERROR] [1629290064.930883203]: $GAGSV,3,2,09,18,21,165,25,24,01,347,21,26,74,317,35,31,08,303,28,2*71
//[ERROR] [1629290064.931509929]: $GAGSV,3,3,09,33,24,305,31,2*4D
//[ERROR] [1629290064.932336341]: $GAGSV,2,1,08,03,01,036,25,07,61,158,46,08,46,059,41,13,47,117,45,7*72
//[ERROR] [1629290064.933146845]: $GAGSV,2,2,08,18,21,165,26,26,74,317,44,31,08,303,34,33,24,305,42,7*7E
//[ERROR] [1629290064.933510958]: $GAGSV,1,1,01,01,02,254,,0*45
//[ERROR] [1629290064.934294555]: $GBGSV,2,1,08,09,34,059,40,11,63,163,46,14,58,220,46,16,21,039,33,1*7C
//[ERROR] [1629290064.935089278]: $GBGSV,2,2,08,21,39,053,45,28,29,311,45,33,29,226,46,34,39,153,48,1*7A
//[ERROR] [1629290064.935920783]: $GBGSV,1,1,04,09,34,059,33,11,63,163,38,14,58,220,38,16,21,039,26,3*71
//[ERROR] [1629290064.936830399]: $GBGSV,1,1,03,05,16,115,,06,23,043,,12,13,145,,0*42

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
