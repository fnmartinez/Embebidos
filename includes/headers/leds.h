/*
 * leds.h
 *
 *  Created on: 10/09/2012
 *      Author: facundo
 */

#ifndef LEDS_H_
#define LEDS_H_
#include <avr/io.h>
#include <util/delay.h>

#if !defined(LEDS_PORT) || !defined(LEDS_DDR)
#define LEDS_PORT PORTC
#define LEDS_DDR DDRC
#endif

#define LEDS_QTY   8
					    /*Bits: 7 6 5 4 3 2 1 0 */
#define LED_NONE 	0x00	 /* 0 0 0 0 0 0 0 0 */
#define LED_FIRST 	0x01	 /* 0 0 0 0 0 0 0 1 */
#define LED_SECOND 	0x02     /* 0 0 0 0 0 0 1 0 */
#define LED_THIRD 	0x04     /* 0 0 0 0 0 1 0 0 */
#define LED_FOURTH 	0x08     /* 0 0 0 0 1 0 0 0 */
#define LED_FIFTH 	0x10     /* 0 0 0 1 0 0 0 0 */
#define LED_SIXTH 	0x20     /* 0 0 1 0 0 0 0 0 */
#define LED_SEVENTH 0x40     /* 0 1 0 0 0 0 0 0 */
#define LED_EIGHT 	0x80     /* 1 0 0 0 0 0 0 0 */
#define LED_ALL		0xFF     /* 1 1 1 1 1 1 1 1 */

unsigned char leds[] = { LED_FIRST,
				LED_SECOND,
				LED_THIRD,
				LED_FOURTH,
				LED_FIFTH,
				LED_SIXTH,
				LED_SEVENTH,
				LED_EIGHT,
				LED_ALL,
				LED_NONE };

volatile char led_status = 0x00;

void change_leds();
void led_on(unsigned char led);
void led_off(unsigned char led);
void leds_on();
void leds_off();

#endif /* LEDS_H_ */
