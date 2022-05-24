/**
 *  Author: Mario M, based on "testSender.c" and SysArch/main.c from Sasha-Boy.
 * 
 * This is a test_program, it  creates 2 threads: One that publish data
 * and other who gets the data.
 */

#include "threadInformations.h"
#include "dataPassing.h"

void entry_ps2mouse_test_local(void *unused, void *unused1, void *unused2);

K_THREAD_STACK_DEFINE(thread_ps2mouse_sym_test, STACK_SIZE);
K_THREAD_STACK_DEFINE(thread_ps2mouse_sym, STACK_SIZE);

struct k_thread ps2mouse_thread_data_test;
k_tid_t ps2mouse_thread_pid_test_local;

struct k_thread ps2mouse_thread_data;
k_tid_t ps2mouse_thread_pid;

void main(void)
{
    /* Thread that publish the mail box with the data*/
	ps2mouse_thread_pid =
		k_thread_create(&ps2mouse_thread_data, thread_ps2mouse_sym,
				K_THREAD_STACK_SIZEOF(thread_ps2mouse_sym),
				entry_ps2mouse, NULL, NULL, NULL, PRIO, 0,
				K_NO_WAIT);

    /*thread to test the "data reading" from the mail box*/
	ps2mouse_thread_pid_test_local =
		k_thread_create(&ps2mouse_thread_data_test, thread_ps2mouse_sym_test,
				K_THREAD_STACK_SIZEOF(thread_ps2mouse_sym_test),
				entry_ps2mouse_test, NULL, NULL, NULL, PRIO, 0,
				K_NO_WAIT);
}

void entry_ps2mouse_test_local(void *unused, void *unused1, void *unused2)
{
	mouse_y_position_t data_readed;
	while (1) {
		getData(&ps2mouse_mailbox, &data_readed,
			sizeof(mouse_y_position_t));
		printk("Y =  ");
		printk("%lld ", COUNTS_TO_MM(data_readed.abs_y));
		printk("\n");
		k_sleep(70);
	}
}
