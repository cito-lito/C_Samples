/**
 * Author : Mario M. , 
 * 
 * This program store selected points in an Array of Structs with X, Y values
 * It is a very simple mapping approach. For scability it need to be improve!
 */

#include "slam_itse.h"

mapped_points_t mapped_points[MAX_MAPPED_POINTS];
u8_t mapped_points_counter;

void map_point(itse_abs_pos_t *pos, s64_t coulomb, float_t angle)
{
	if (mapped_points_counter < MAX_MAPPED_POINTS) {
		/*store the last abs readed X,X values*/
		mapped_points[mapped_points_counter].x = pos->x;
		mapped_points[mapped_points_counter].y = pos->y;
		mapped_points[mapped_points_counter].coulomb = coulomb;
		mapped_points[mapped_points_counter].angle = angle;

		/*set the iterator for the next position*/
		mapped_points_counter++;
	} else {
		printk("ERROR: cant store more points\n");
		return;
	}
}
