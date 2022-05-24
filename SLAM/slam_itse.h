/* slam_itse.h */

/**
 * @file
 * Author : Mario M., 
 * 
 * @brief Public API for the very basic "SLAM" approach for the ITSE.
 */

#ifndef SLAM_ITSE_H
#define SLAM_ITSE_H

#include <zephyr.h>
#include <zsl/zsl.h>


/*********** COMMON **************/

#define M_PI 3.14159f
#define COORDINATES 3
#define PLANE_Z 1
/*ITSE only drives in Y direction, x is always 0*/
#define ITSE_X 0

/**
 * radians to degrees: sin(), cos() from "math.h" returns radians, use this macro
 * to get degrees within the use of the sin(), cos() functions. Example: sin(DEG(angle)); 
 */
#define DEG(angle) ((angle * (M_PI / 180)))

/**
 * radians to degrees: atan from "math.h" returns radians, use this macro
 * to get degrees within the use of the atan function. 
 */
#define DEG_ATAN(angle) ((atan((double)angle) * (180 / M_PI)))

/**
 * Given an acute Angle in a right-angled triangle: Get the other
 * acute Angle.  
 */
#define RIGHT_ANGLE_TRIANGLE(angle) (180.0f - 90.0f - angle)


/******** LOCALIZATION *********/

/**
 * Store here itse abs positions
 */
typedef struct {
	double_t x;
	double_t y;
} itse_abs_pos_t;

/*Gloval struct where the abs pos of itse will be store
declare and init to 0 in 0,0 start point*/
extern itse_abs_pos_t itse_abs_pos;

/**
 * @brief init position to X = 0, Y = 0.
 * Call this function once at the beginning, before itse
 * leaves the charging station.
 * @param pos Struct where X and Y are stored.
 */
void init_station_pos(itse_abs_pos_t *pos);

/**
 * @brief Get the new absolut posittion by doing
 * a translation and rotation matrix:
 * absolut_pos = (translation * rotation * distance_drived)
 * @param y_drived The Y distance drived.
 * @param angle The angle of the ITSE
 * @param pos Struct where X and Y are stored.
 * New abs pos will be in the pos Struct written.
 */
void itse_abs_pos_get(s32_t y_drived, float_t angle, itse_abs_pos_t *pos);

/********* PATH PLANING *******/

/**
 *  @brief get the magnitude of the vector: the distance to the 0.0
 *  using Pythagorean  theorem.
 *  @param pos Struct where X and Y are stored.
*/
double_t distance_to_station_get(itse_abs_pos_t *pos);

/**
 * @brief get the drive rirection of ITSE to charging station using
 * the absolut positions, polar coordinates, arctangent
 * and right-angled triangle properties.
 * @param pos Struct where X and Y are stored.
*/
float_t direction_to_station_get(itse_abs_pos_t *pos);

/********* MAPPING *******/

#define MAX_MAPPED_POINTS 100

typedef struct{
	double_t x;
	double_t y;
	s64_t coulomb;
	float_t angle;
}mapped_points_t;

/*Array of Structs that store X,Y points and othe mapping values*/
extern mapped_points_t mapped_points[MAX_MAPPED_POINTS];

/*This var tracks the stored points, use to acces the
mapped points avoiding the empty points*/
extern u8_t mapped_points_counter;

/**
 * @brief Store the last visited point if its mapping relevant. 
 * @param pos Struct with the actual abs posiotn.
 * @param coulomb: Energie  at Point
 * @param angle: Angle of the ITSE at the stored point
 * Add other parameters with relevant values for mapping if needed.
 */
void map_point(itse_abs_pos_t *pos, s64_t coulomb, float_t angle);


#endif /*SLAM_ITSE_H*/