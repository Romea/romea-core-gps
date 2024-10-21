# romea_core_gps #

This project is a C++ library that provides tools to parse and emulate NMEA data coming from GPS reveiver. The following NMEA sentence are supported :

 - **GGA (Global Positioning System Fix Data)**: Provides essential fix data such as time, position, and fix quality.
 - **RMC (Recommended Minimum Navigation Information)**: Includes the recommended minimum data for navigation, such as position, speed, and time.
 - **GSV (Satellites in View)**: Reports the number of satellites in view, their ID numbers, elevation, azimuth, and signal-to-noise ratio (SNR).
 - **HDT (Heading True)**: Provides the heading (direction) of the mobile relative to true north.

This library also includes an algorithm to calculate the reliability of the GPS fix. It does this by evaluating data related to satellites in view:

- **Azimuth**: The horizontal angle of the satellite relative to the observer's position.
- **Elevation**: The vertical angle of the satellite above the horizon.
- **SNR (Signal-to-Noise Ratio)**: A measure of signal strength, which influences the quality of the pseudo-range calculations.

The purpose of this algorithm is to assess the accuracy of the GPS fix by considering the overall satellite visibility and quality of satellite data.


## **Usage**

1. create a ROS workspace
2. cd worskpace
3. mkdir src
4. wget https://raw.githubusercontent.com/Romea/romea-core-gps/refs/heads/main/romea_gps_public.repos
5. vcs import src < romea_gps_public.repos
6. build packages
   - catkin build for ROS1
   - colcon build for ROS2
7. create your application using this library

## **Contributing**

If you'd like to contribute to this project, here are some guidelines:

1. Fork the repository.
2. Create a new branch for your changes.
3. Make your changes.
4. Write tests to cover your changes.
5. Run the tests to ensure they pass.
6. Commit your changes.
7. Push your changes to your forked repository.
8. Submit a pull request.

## **License**

This project is released under the Apache License 2.0. See the LICENSE file for details.

## **Authors**

The romea_core_gps library was developed by **Jean Laneurit** in the context of various research projects carried out at INRAE.

## **Contact**

If you have any questions or comments about romea_core_gps library, please contact **[Jean Laneurit](mailto:jean.laneurit@inrae.fr)** 