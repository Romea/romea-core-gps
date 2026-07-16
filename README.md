# romea_core_gps

## Overview

`romea_core_gps` is a C++ library for parsing, generating and analysing GPS/GNSS NMEA data.

It provides typed C++ representations of common NMEA sentences, helpers to convert between NMEA fields and numeric values, a `GPSReceiver` facade and a reliability estimator based on satellites in view.

The package is framework-independent C++ code. Middleware-specific drivers, messages and launch files are intentionally kept outside this library.

## GPS receiver model

`GPSReceiver` is the central model used by the package. It groups the most common operations needed by higher-level GPS processing code:

* parse `GGA`, `RMC` and `HDT` sentences into typed frames;
* update visible satellite information from `GSV` sentences;
* store the GPS antenna position in the vehicle body frame;
* associate each fix quality with an equivalent user range error;
* compute a reliability score from the current satellites in view.

---

## Sensor characteristics

`GPSReceiver` stores receiver-level configuration used by algorithms that consume GPS data:

| Scope | Quantities | Meaning |
| ----- | ---------- | ------- |
| Receiver setup | `antennaBodyPosition` | Position of the GPS antenna in the vehicle body frame. |
| Fix uncertainty model | `GPSReceiverEUREs` | Equivalent user range error associated with each supported NMEA fix quality. |

The facade keeps these values close to the parsed NMEA frames and exposes the helpers needed by algorithms that estimate position uncertainty or receiver reliability.

---

## Data frames

| Sentence | Frame | Main content |
| -------- | ----- | ------------ |
| `GGA` | `GGAFrame` | Fix time, latitude, longitude, fix quality, number of satellites used, HDOP, altitude and geoid information. |
| `RMC` | `RMCFrame` | Fix time, status, latitude, longitude, speed over ground, track angle, date, magnetic deviation and fix quality. |
| `GSV` | `GSVFrame` | Satellites in view, including PRN number, elevation, azimuth and SNR. |
| `HDT` | `HDTFrame` | Heading relative to true north. |
| Aggregated satellites | `SatellitesInView` | Current visible satellites grouped by GNSS talker after aggregating `GSV` messages. |

Each frame can be built from a raw NMEA sentence. Some frames, such as `GGAFrame`, `RMCFrame` and `HDTFrame`, can also be converted back to a NMEA sentence with `toNMEA()`. `GSVFrameAggregator` collects multi-sentence `GSV` messages, and `SatellitesInView` stores the visible satellites grouped by GNSS talker.

---

## Algorithms

The package provides two reusable algorithmic blocks:

| Component | Role |
| --------- | ---- |
| `GSVFrameAggregator` | Aggregates multi-sentence `GSV` messages to recover the current visible satellite constellation. |
| `GPSReliability` | Computes a reliability score from the visible satellite constellation and SNR distributions. |

The reliability estimator uses information from `GSV` sentences. For each visible satellite, it takes into account:

* the GNSS talker;
* the satellite elevation;
* the satellite SNR.

`GSVFrameAggregator` collects the multi-sentence `GSV` stream, `SatellitesInView` stores the satellites per talker, and `GPSReliability` computes a confidence value from configured SNR distributions.

This reliability score is complementary to the fix quality. The fix quality describes the type of position solution reported by the receiver, such as standard GPS, DGPS, RTK float or RTK fixed. This solution is computed from satellite measurements, while its horizontal accuracy is influenced by the constellation geometry, commonly represented by `HDOP` in `GGA` data. The reliability score complements this information by using satellite visibility and SNR from `GSV` data.



## Section Position uncertainty 

Unlike IMU or lidar uncertainties, GPS position uncertainty is not only a fixed receiver characteristic. It must be estimated from the current fix quality and from the current satellite constellation geometry as seen by the receiver. This geometric effect is commonly represented by the `HDOP` (Horizontal Dilution Of Precision) value provided by `GGA` sentences: satellites well distributed across the sky generally lead to a low `HDOP`, while satellites clustered in the same region of the sky lead to a higher `HDOP`.

`GPSReceiverEUREs` associates each supported fix quality with an equivalent user range error value. This receiver-dependent value can be combined with `HDOP` to estimate the horizontal position uncertainty:

```text
horizontal_position_std = HDOP * UERE(fix_quality)
```

UERE values depend on the receiver, antenna and correction source used in the field. They should be characterised for each supported fix quality of a given receiver/antenna setup. The defaults provided by this package are convenient nominal values and can be overridden when constructing `GPSReceiver` or `GPSReceiverEUREs`.

The default mapping covers:

| Fix quality | Meaning |
| ----------- | ------- |
| `INVALID_FIX` | No valid fix. |
| `GPS_FIX` | Standard GPS fix. |
| `DGPS_FIX` | Differential GPS fix. |
| `RTK_FIX` | RTK fixed solution. |
| `FLOAT_RTK_FIX` | RTK float solution. |
| `SIMULATION_FIX` | Simulated fix. |
| `MANUAL_FIX` | Manually provided fix. |



---

## Minimal usage

```cpp
#include <romea_core_gps/GPSReceiver.hpp>

romea::core::GPSReceiver receiver;

auto gga = receiver.createFrameGGA(
  "$GPGGA,120648.80,4533.53366,N,00315.44427,E,2,08,2.17,382.4,M,47.5,M,,0000*5B");

auto rmc = receiver.createFrameRMC(
  "$GPRMC,090433.00,A,4546.4918963,N,00308.7532503,E,0.0,0.0,111213,0.3,E,D*3A");

receiver.updateSatellitesViews(
  "$GPGSV,3,1,11,01,40,083,46,02,17,308,41,03,22,135,43,04,13,259,39*70");

auto satellites_in_view = receiver.getSatellitesInView();
auto reliability = receiver.getReliability();
```

---

## Related packages

| Package | Role |
| ------- | ---- |
| `romea_core_common` | Shared core types used for time, diagnostics and common utilities. |
| `romea_core_localisation_gps` | Builds localisation observations from parsed GPS data. |

---

## License

This project is released under the Apache License 2.0. See the `LICENSE` file for details.

## Authors

This library was developed by **Jean Laneurit** in the context of several research projects carried out at INRAE.
