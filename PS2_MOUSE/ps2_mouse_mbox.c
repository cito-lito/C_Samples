/**
 *  Author: Mario M, based on "sendingThread.c" from Sasha-Boy.
 * 
 * This program creates and make public a Mail Box, 
 * in where the mouse data will be available to every thread.
 * 
 * "this program should be invoked as a thread from 
 * a main and puts in periods a struture and string into the mailbox"
 */

#include "ps2_mouse.h"
#include "dataPassing.h"
#include "threadInformations.h"
#include <string.h>

/*mail box*/
struct k_mbox ps2mouse_mailbox;

void entry_ps2mouse(void *unused, void *unused1, void *unused2)
{
	/* init the mailbox */
	initMBox(&ps2mouse_mailbox);

	/*struct where mouse data will be saved*/
	mouse_y_position_t mouse_data;
	memset(&mouse_data, 0, sizeof(mouse_y_position_t)); /*init to 0*/
	printk("befre mouse init\n");
	/*init the mouse*/
	if (0 == mouse_sensor_init()) {
		/*if init went fine start getting and publishing data */
		while (1) {
			/*get mouse data*/
			mouse_y_pos_get(&mouse_data);

			/*publish data to every thread*/
			putData(&mouse_data, sizeof(mouse_y_position_t),
				&ps2mouse_mailbox, NULL);
			k_sleep(200);
		}
	}
	printk("ERROR: mouse init\n");
}

void entry_ps2mouse_test(void *unused, void *unused1, void *unused2)
{
	mouse_y_position_t data_readed;
	while (1) {
		getData(&ps2mouse_mailbox, &data_readed,
			sizeof(mouse_y_position_t));
		printk("Y =  ");
		printk("%lld ", COUNTS_TO_MM(data_readed.abs_y));
		printk("\n");
		k_sleep(200);
	}
}