
## Simultaneous localization and mapping(SLAM)


##### Zephyr OS

This project is built using the Zephyr Operating System.
You can find [here](https://docs.zephyrproject.org/latest/application/index.html#application) a basic overview of how to build an Application using this OS.

***Slam for a robot named “ITSE”:***

Slam is the Estimation and Mapping of the positions of the robot in an Unknown Environment. This is a hard problem because, in order to estimate a good robot position a Map is needed, and for a good Map the robot positions are needed.
This is a very basic approach:
Two 2D Cartesian Coordinate Systems will be used:
For the absolute positions, where Origin punt (0,0) is the Charging Station. Global Coordinates
For the Local positions of the ITSE, where the inertial measurement unit (IMU) axis XY is the ITSE axis local Coordinates.

#### Self Localization
For the determination of the ITSE absolute position, a translation of the local coordinates to global coordinates is needed. This can be achieved by doing a translation and rotation operation. These operations can be done by using “homogeneous coordinates”. For our 2D case a 3×3 Rotation and Translation Matrix are necessary:
 ![image](https://user-images.githubusercontent.com/41654186/170057779-8d9a3c16-e108-440e-b6a7-237f4785ef6d.png)


This example is based on [Embedded Robotics by Thomas Bräuln](https://www.springer.com/gp/book/9783540343196)

#### Path Planning
##### Distance to Charging Station:*
This is done by getting the magnitude of the vector of the Charging Station(0,0) to the actual absolute position. If ISTE is on X or Y axis (X== 0 or Y==0) the distance will be the absolute value of X or Y. Otherwise, the distance will be the result of the Pythagorean theorem operation of X and Y.

##### Direction to Charging Station:
This is done using the absolute position, polar coordinates, arctangent, and right-angled triangle properties.
- Note that IMU has a fixed reference for the angles:
![image](https://user-images.githubusercontent.com/41654186/170058035-66d79c7f-3a8f-48ac-8972-d36b59dc8509.png)

##### Mapping
The mapping approach is the simplest part of the ITSE_SLAM. It is just an Array of Structs where the visited points that are valuable to store will be saved.

