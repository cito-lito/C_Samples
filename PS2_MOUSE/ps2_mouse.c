/* ps2_mouse.c */

/**
 * Author : Mario M. 
 *
 * This program reads the X and Y values from
 * a PS2 optical mouse. 
 * 
 */

#include "ps2_mouse.h"

/* this defines are not in header because they are only used here*/
#define GPIO_DRIVER_0 "GPIO_0" /*nRF52 binding port for pins : 0.02 ... 0.31*/
#define CLK 3 /*P 0.03*/
#define DTA 4 /*P 0.04*/
#define AUXCLK 20 /*P 0.20*/ /*DFU, use it with a pullup resistor!!*/
#define AUXDTA 7 /*P 0.07*/

#define HIGH 1 /*logic hihg ~2.5V to ~5V*/
#define LOW 0 /*logic low ~0V to ~1V*/

#define PRIVATE static

/*device ptr, for binding the gpio_driver_0 port*/
PRIVATE struct device *port_0;

/* Private Functions*/

/**
 * @brief init configuration of port and pins
 * @return 0 if successful, 1 on failure.
 */
PRIVATE u8_t init_setup()
{
	u8_t ret;
	port_0 = device_get_binding(GPIO_DRIVER_0);
	if (!port_0) {
		printk("Cannot find %s!\n", GPIO_DRIVER_0);
		return 1; // return error
	}
	ret = gpio_pin_configure(port_0, CLK, (GPIO_DIR_IN | GPIO_PUD_PULL_UP));
	if (ret) {
		printk("Error configuring pin %d!\n", CLK);
		return 1; // return error
	}
	ret = gpio_pin_configure(port_0, DTA, (GPIO_DIR_IN | GPIO_PUD_PULL_UP));
	if (ret) {
		printk("Error configuring pin %d!\n", DTA);
		return 1; // return error
	}
	ret = gpio_pin_configure(port_0, AUXCLK, GPIO_DIR_OUT);
	if (ret) {
		printk("Error configuring pin %d!\n", AUXCLK);
		return 1; // return error
	}
	ret = gpio_pin_configure(port_0, AUXDTA, GPIO_DIR_OUT);
	if (ret) {
		printk("Error configuring pin %d!\n", AUXDTA);
		return 1; // return error
	}
	return ret;
}

/**
 * @brief Check if mouse is connected. Mouse clk idle mode is HIGH
*/
PRIVATE u8_t check_if_connected()
{
	u32_t s = 0;
	k_sleep(50);
	gpio_pin_read(port_0, CLK, &s);
	return s;
}

/**
 * @brief Set the pin bus to logic hihg
 */
PRIVATE void release_pin(u8_t pin)
{
	s8_t ret = -1;
	ret = gpio_pin_write(port_0, pin, HIGH);
	if (ret) {
		printk("Error set pin %d!\n", pin);
	}
}

/**
 * @brief Set the pin bus to logic low
 */
PRIVATE void pulldown_pin(u8_t pin)
{
	s8_t ret = -1;
	ret = gpio_pin_write(port_0, pin, LOW);
	if (ret) {
		printk("Error set pin %d!\n", pin);
	}
}

/**
 * @brief Wait for mouse to change the signal.
 * @param pin Pin number where the signal is.
 * @param signal Signal value set on the pin.
 */
PRIVATE void wait_signal(u8_t pin, u8_t signal)
{
	u32_t s = 2;
	do {
		gpio_pin_read(port_0, pin, &s);
	} while (s == signal);
}

/**
 * @brief generate clock pulses from the mouse.
 */
PRIVATE void request_to_send()
{
	pulldown_pin(AUXCLK);
	k_usleep(100);
	pulldown_pin(AUXDTA);
	k_usleep(80);
	release_pin(AUXCLK); /*start bit*/
}

/**
 * @brief Write/Send  a command to the mouse.
 * @param command to be writen.
 */
PRIVATE void write_to_mouse(u8_t command)
{
	u8_t parity = 1;
	request_to_send();
	wait_signal(CLK, HIGH);

	for (u8_t i = 0; i < 8; i++) {
		/*wrtite command byte, bit by bit at falling edge of clock*/
		if (command & 0x01) {
			release_pin(AUXDTA);
		} else {
			pulldown_pin(AUXDTA);
		}
		/*wait for clock cycle*/
		wait_signal(CLK, LOW);
		wait_signal(CLK, HIGH);

		parity = parity ^ (command & 0x01); /*set parity bit*/
		command = command >> 1; /*next bit command*/
	}

	/*parity bit*/
	if (parity) {
		release_pin(AUXDTA);
	} else {
		pulldown_pin(AUXDTA);
	}
	/*wait for clock cycle*/
	wait_signal(CLK, LOW);
	wait_signal(CLK, HIGH);
	release_pin(AUXDTA); /*stop bit*/

	/*The resolution of the nRF52 is 32 KiHz (32768 Hz).
	* so the smallest theoretical sleep is about 30 us.
	* but k_usleep did not worked for values <60us. This is why busy_wait is used*/
	k_busy_wait(50); /* for ack bit*/
	wait_signal(CLK, HIGH);

	/*wait for clk or data signal*/
	u32_t c = 2;
	u32_t d = 2;
	do {
		gpio_pin_read(port_0, CLK, &c);
		gpio_pin_read(port_0, DTA, &d);
	} while ((c == 0) || (d == 0));
	pulldown_pin(AUXCLK);
}

/**
 * @brief Read Data Byte from the mouse.
 * @return Data Byte
 */
PRIVATE u8_t read_from_mouse()
{
	u32_t d = 2;
	u8_t data = 0x00;
	u8_t bit = 0x01;
	release_pin(AUXCLK);
	release_pin(AUXDTA);
	/*Clock line must be high for at least 50us before the device can begin to
	transmit its data*/
	k_busy_wait(50);
	wait_signal(CLK, HIGH);
	/*data transition to the falling edge of a clock pulse must be at least 5us*/
	k_busy_wait(5);
	wait_signal(CLK, LOW); /*ignore start bit*/

	for (u8_t i = 0; i < 8; i++) {
		/*Read Data bit at falling edge of clock signal*/
		wait_signal(CLK, HIGH);
		if (0 != (gpio_pin_read(port_0, DTA, &d))) {
			/*error*/
		}
		if (d == HIGH) {
			data = (data | bit);
		}
		wait_signal(CLK, LOW);
		bit = bit << 1; /*next data bit*/
	}
	/*ignore parity and stop bit*/
	wait_signal(CLK, HIGH);
	wait_signal(CLK, LOW);
	wait_signal(CLK, HIGH);
	wait_signal(CLK, LOW);
	pulldown_pin(AUXCLK);
	return data;
}

/**
 * @brief init configuration of the mouse:
 * reset the mouse(0xff) for default configuration
 * and set it to remote mode(0xf0)
 * @return 0 if successful, 1 on failure.
 */
PRIVATE s8_t init_mouse()
{
	s8_t ret = 0; // no error
	release_pin(AUXCLK);
	release_pin(DTA);
	write_to_mouse(0xFF);
	read_from_mouse(); /*ack (0xFA)*/
	u8_t bat = read_from_mouse(); /*BAT completion code*/
	if (bat != 0xAA) {
		/*error*/
		printk("Error, cant set the mouse to reset mode\n");
		ret = 1; //error
	}
	read_from_mouse(); /*device ID (0x00)*/
	write_to_mouse(0xF0);
	read_from_mouse(); /*ack*/
	k_usleep(100);
	return ret;
}

/* Public Functions */

u8_t mouse_sensor_init()
{
	u8_t ret = 0;
	ret |= init_setup();
	ret |= init_mouse();
	return ret;
}

void mouse_pos_get(mouse_position_t *m_pos)
{
	write_to_mouse(0xEB); /*request data*/
	read_from_mouse(); /* ignore ack byte*/
	read_from_mouse(); /* ignore flag byte*/

	m_pos->delta_x = read_from_mouse(); /*get delta X*/
	m_pos->delta_y = read_from_mouse(); /*get delta Y*/

	m_pos->abs_x += m_pos->delta_x;
	m_pos->abs_y += m_pos->delta_y;
}

PRIVATE s8_t dy; /*store the delta y positions*/

void mouse_y_pos_get(mouse_y_position_t *m_pos)
{
	write_to_mouse(0xEB); /*request data*/
	read_from_mouse(); /* ignore ack byte*/
	read_from_mouse(); /* ignore flag byte*/

	read_from_mouse(); /*ignore delta X*/
	dy = read_from_mouse(); /*get delta Y*/

	m_pos->abs_y += dy;
}

// void main(void)
// {
// 	printk("starting...\n");

// 	if (mouse_sensor_init()) {
// 		// error
// 	}
// 	/* struct to save x and y pos*/
// 	mouse_position_t position;
// 	memset(&position, 0, sizeof(mouse_position_t)); /*init to 0*/
// 	for (;;) {
// 		mouse_pos_get(&position);
// 		printk("X =  ");
// 		printk("%lld", COUNTS_TO_MM(position.abs_x));
// 		printk("\tY =  ");
// 		printk("%lld ", COUNTS_TO_MM(position.abs_y));
// 		printk("\t");

// 		printk("x =  ");
// 		printk("%d", COUNTS_TO_MM(position.delta_x));
// 		printk("\ty =  ");
// 		printk("%d ", COUNTS_TO_MM(position.delta_y));
// 		printk("\n");
// 		k_sleep(200);
// 	}
// }
