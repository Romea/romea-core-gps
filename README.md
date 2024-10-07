This package contains tools to parse and emulate NMEA data coming from GPS reveiver. The following NMEA sentence are supported :

 - **GGA (Global Positioning System Fix Data)**: Provides essential fix data such as time, position, and fix quality.
 - **RMC (Recommended Minimum Navigation Information)**: Includes the recommended minimum data for navigation, such as position, speed, and time.
 - **GSV (Satellites in View)**: Reports the number of satellites in view, their ID numbers, elevation, azimuth, and signal-to-noise ratio (SNR).
 - **HDT (Heading True)**: Provides the heading (direction) of the mobile relative to true north.

This library also includes an algorithm to calculate the reliability of the GPS fix. It does this by evaluating data related to satellites in view:

- **Azimuth**: The horizontal angle of the satellite relative to the observer's position.
- **Elevation**: The vertical angle of the satellite above the horizon.
- **SNR (Signal-to-Noise Ratio)**: A measure of signal strength, which influences the quality of the pseudo-range calculations.

The purpose of this algorithm is to assess the accuracy of the GPS fix by considering the overall satellite visibility and quality of satellite data.
