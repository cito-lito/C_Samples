/* ps2_mouse.h */

/**
 * @file
 * Author : Mario M.
 * 
 * @brief Public API for PS2 Mouse Sensor. Use it to get
 * the position of X and Y by calling the mouse_pos_get() function.
 * For the ITSE only Y is needed, get ut by calling the mouse_y_pos_get().
 */

#ifndef PS2_MOUSE_H
#define PS2_MOUSE_H

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/printk.h>
#include <string.h>
#include "dataPassing.h"

/* Acording to the specs of the mouse, it has 800dpi or 800cpi. 
Therefore every mouse count should be: (25,4mm / 8000) = 0,0317mm
but it did not macht with the actual readed values. After some
checks agains some physical values, a division by 9 showed the most 
accurate measurement in mm.. Use this macro after getting 
the values from mouse_pos_get */
#define COUNTS_TO_MM(x) ((x) / 9)

/**
 * @brief Struct to store X and Y pos.
 * Dont use it for the ITSE, becase it only needs the Y values.
 */
typedef struct mouse_position {
	s64_t abs_x;
	s64_t abs_y;
	s64_t delta_x;
	s64_t delta_y;
} mouse_position_t;

/**
 * @brief Since the ITSE will only use the Y
 * postions, this Struct only store the Y  values.
 */
typedef struct mouse_y_postion {
	s64_t abs_y;
} mouse_y_position_t;

/**
 * @brief Init the mouse sensor
 * @return 0 if successful, 1 on failure.
 */
u8_t mouse_sensor_init();

/**
 * @brief Get the  position of X and Y
 * @param m_pos Struct to save x and y pos.
 */
void mouse_pos_get(mouse_position_t *m_pos);

/**
 * @brief Since the ITSE will only use the Y
 * postions, this function only gets the Y abs. value.
 * @param m_pos Struct that store y abs. pos.
 */
void mouse_y_pos_get(mouse_y_position_t *m_pos);

/**
 *** Thread Communication ***
*/

/*ps2mouse mail box*/
extern struct k_mbox ps2mouse_mailbox;

/*Thread creator can use this, or create a new one*/
extern k_tid_t ps2mouse_thread_pid;
/*Thread creator can use this, or create a new one*/
extern k_tid_t ps2mouse_thread_pid_test;

/**
 * @brief Entry thread function.
 * @param not used, all NULL.
 */
void entry_ps2mouse(void *unused, void *unused1, void *unused2);



/**
 * @brief Mouse test entry thread function.
 * @param not used, all NULL.
 */
void entry_ps2mouse_test(void *unused, void *unused1, void *unused2);


#endif /* PS2_MOUSE_H */