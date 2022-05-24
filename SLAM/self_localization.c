/**
 * Author : Mario M. 
 * 
 * This program get the new absolut pos from: the distance drived, the angle
 * and the old abs pos.Based on homogeneus coordinates.
 */

#include "slam_itse.h"

void init_station_pos(itse_abs_pos_t *pos)
{
	pos->x = 0;
	pos->y = 0;
}

void itse_abs_pos_get(s32_t y_drived, float_t angle, itse_abs_pos_t *pos)
{
	/*translation and rotation*/
	float_t trans_rot_tmp[COORDINATES][COORDINATES] = {
		{ (cos(DEG(angle))), (-sin(DEG(angle))), pos->x },
		{ (sin(DEG(angle))), (cos(DEG(angle))), pos->y },
		{ 0, 0, PLANE_Z }
	};

	double_t absolut_pos_tmp[COORDINATES] = { 0, 0, PLANE_Z };
	s32_t dist_drived_tmp[COORDINATES] = { ITSE_X, y_drived, PLANE_Z };

	/* trans and rotation * distance_drived*/
	for (u8_t i = 0; i < 3; i++) {
		double_t coord_tmp = 0;
		for (u8_t j = 0; j < 3; j++) {
			coord_tmp += trans_rot_tmp[i][j] * dist_drived_tmp[j];
		}

		/*Z is always 1, dont care*/
		if (i < 2) {
			absolut_pos_tmp[i] = coord_tmp;
		}
	}
	/*get the new abs pos, for now it will overwritten, until new solution*/
	pos->x = absolut_pos_tmp[0];
	pos->y = absolut_pos_tmp[1];
}
