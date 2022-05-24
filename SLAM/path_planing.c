/**
 * Author : Mario M. 
 * 
 * This program get the distance and direction that ITSE needs to go
 * to the charging station
 */

#include "slam_itse.h"


double_t distance_to_station_get(itse_abs_pos_t *pos)
{
	/*local vars, for better readability*/
	double_t x = pos->x;
	double_t y = pos->y;

	/* ITSE is in  XY axis*/
	if (x != 0 && y != 0) {
		return (sqrt(((x * x) + (y * y))));
	}

	/* ITSE is in  X axis*/
	else if (x != 0 && y == 0) {
		return fabs(x);
	}
	/* ITSE is in  Y axis*/
	else if (x == 0 && y != 0) {
		return fabs(y);
	}
	/* ITSE is in  station */
	else {
		return 0;
	}
}

float_t direction_to_station_get(itse_abs_pos_t *pos)
{
	/*local vars, for better readability*/
	double_t x = pos->x;
	double_t y = pos->y;

	/* ITSE is in 0 to 90 zone*/
	if (x > 0 && y > 0) {

		/*right-angled triangle*/
		float_t x_to_vector_angle = DEG_ATAN((y / x));
		float_t y_to_vector_angle =
			RIGHT_ANGLE_TRIANGLE(x_to_vector_angle);

		/* ITSE to satation angle*/
		return 180.0f - y_to_vector_angle;
	}
	/* ITSE is in 90 to 180 zone*/
	else if (x < 0 && y > 0) {
		/*right-angled triangle*/
		float_t aux = DEG_ATAN((y / x));
		float_t x_to_vector_angle = fabs(aux);
		float_t y_to_vector_angle =
			RIGHT_ANGLE_TRIANGLE(x_to_vector_angle);

		/* ITSE to satation angle*/
		return 180.0f + y_to_vector_angle;
	}
	/* ITSE is in 180 to 270 zone*/
	else if (x < 0 && y < 0) {
		/*right-angled triangle*/
		float_t x_to_vector_angle = DEG_ATAN((y / x));
		float_t y_to_vector_angle =
			RIGHT_ANGLE_TRIANGLE(x_to_vector_angle);

		/* ITSE to satation angle*/
		return 360.0f - y_to_vector_angle;

	}
	/* ITSE is in 270 to 360 zone*/
	else if (x > 0 && y < 0) {
		/*right-angled triangle*/
		float_t aux = DEG_ATAN((y / x));
		float_t x_to_vector_angle = fabs(aux);
		float_t y_to_vector_angle =
			RIGHT_ANGLE_TRIANGLE(x_to_vector_angle);

		/* ITSE to satation angle*/
		return y_to_vector_angle;
	}
	/* ITSE is in  +Y axis*/
	else if (x == 0 && y > 0) {
		return 180.0f;
	}
	/* ITSE is in  -Y axis*/
	else if (x == 0 && y < 0) {
		return 0.0f;
	}
	/* ITSE is in  +X axis*/
	else if (x > 0 && y == 0) {
		return 90.0f;
	}
	/* ITSE is in  -X axis*/
	else if (x < 0 && y == 0) {
		return 270.0f;
	}
	/* ITSE is alredy in station*/
	else {
		return 0.0f;
	}
}


		//total distance
		// double_t hyptothenuse = distance_to_station_get(pos);
		// //printk("Hypothenuse = %i \n", (int)hyptothenuse);


		// //calculate angle
		// //printk("X: %i, \t Y%i", (int)x,(int)y);
		// double_t alpha = (x /hyptothenuse)*100;
		// double_t beta = 90 - alpha;
		// //printk("Winkel alpha = %i \t Winkel beta = %i\n", (int)alpha, (int)beta);

		// //calculate outer-angle
		// double_t o_angle = 180- beta;
		// //printk("Außenwinkel = %i \n", (int)o_angle);
		
		// return o_angle;
