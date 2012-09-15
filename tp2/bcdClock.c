/*
 * bcdClock.c
 *
 *  Created on: 10/09/2012
 *      Author: facundo
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SWS_QTY    8
						/*Bits: 7 6 5 4 3 2 1 0 */
#define SWS_NONE	0xFF	 /* 1 1 1 1 1 1 1 1 */
#define SWS_FIRST	0xFE	 /* 1 1 1 1 1 1 1 0 */
#define SWS_SECOND	0xFD	 /* 1 1 1 1 1 1 0 1 */
#define SWS_THIRD	0xFB	 /* 1 1 1 1 1 0 1 1 */
#define SWS_FOURTH	0xF7	 /* 1 1 1 1 0 1 1 1 */
#define SWS_FIFTH	0xEF	 /* 1 1 1 0 1 1 1 1 */
#define SWS_SIXTH	0xDF	 /* 1 1 0 1 1 1 1 1 */
#define SWS_SEVENTH	0xBF	 /* 1 0 1 1 1 1 1 1 */
#define SWS_EIGHT	0x7F	 /* 0 1 1 1 1 1 1 1 */
#define SWS_ALL		0x00	 /* 0 0 0 0 0 0 0 0 */

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

#define forever while(true)
#define SEC_COUNT 100
#undef LEDS_PORT
#undef LEDS_DDR
#undef SWS_PIN
#undef SWS_DDR
#define LEDS_PORT PORTC
#define LEDS_DDR DDRC
#define SWS_PIN PINA
#define SWS_DDR DDRA

typedef enum {
	false, true
} bool;

typedef enum {
	s_sec,
	s_min,
	s_hour,
	s_ssec,
	s_smin,
	s_shour
} state;

volatile int count;
volatile state current_state;
volatile bool time_updated;
volatile unsigned char hs, min, sec;
volatile unsigned char ths, tmin, tsec;

void init();
void down();
void up();
void plot();
void update_time();

void change_leds() {
	LEDS_PORT = led_status;
}
void led_on(unsigned char led){
	led_status = led_status & (~led);
	change_leds();
}

void led_off(unsigned char led){
	led_status = led_status | led;
	change_leds();
}

void leds_on() {
	led_on(LED_ALL);
}

void leds_off() {
	led_off(LED_ALL);
}



void init() {

	time_updated = false;
	current_state = s_sec;
	//Set DDRA as input for switches

	LEDS_DDR = 0xFF;
	SWS_DDR = 0x00;

	//Set OCR1A
	OCR1A = 0x02E1;
	//Set DDRC as output for leds
	//Set timer to CTC1
	TCCR1B |= (1 << WGM12);
	//Set interruption to OCR1A
	TIMSK |= (1 << OCIE1A);
	//Set prescaler to clk/64
	//TCCR1B |= (1 << CS11) | (1<<CS10);

	hs = min = sec = ths = tmin = tsec = count = 0;
	current_state = s_sec;
}

int main() {


	init();
	sei();
	uint8_t sws;
	forever{
//		sws = SWS_PIN;
//		if(sws != SWS_NONE) {
//			if(current_state == s_ssec ||
//					current_state == s_smin ||
//					current_state == s_ssec) {
//				cli();
//				if(sws == SWS_FOURTH) {
//					down();
//				}
//				else if(sws == SWS_FIFTH) {
//					up();
//				}
//				sei();
//			}
//			switch(sws)
//			{
//			case SWS_FIRST:
//				current_state = s_sec;
//				break;
//			case SWS_SECOND:
//				current_state = s_min;
//				break;
//			case SWS_THIRD:
//				current_state = s_hour;
//				break;
//			case SWS_SIXTH:
//				current_state = s_ssec;
//				break;
//			case SWS_SEVENTH:
//				current_state = s_smin;
//				break;
//			case SWS_EIGHT:
//				current_state = s_shour;
//				break;
//			}
//
//		}
//		plot();
		//_delay_ms(100);
	}

	return 0;
}

ISR (TIMER1_COMPA_vect) {
	if(++count == SEC_COUNT) {
		LEDS_PORT = ~LEDS_PORT;
//		update_time();
	}
}

void update_time() {
	time_updated = true;
	tsec++;
	if( (tsec %= 60) == 0) {
		tmin++;
		if((tmin %= 60) == 0) {
			ths++;
			ths %= 24;
			return;
		}
	}
}

void plot() {
	if(time_updated)
	{
		sec = tsec;
		min = tmin;
		hs = ths;
	}
	leds_off();
	switch(current_state)
	{
	case s_sec:
	case s_ssec:
		led_on(sec);
		break;
	case s_min:
	case s_smin:
		led_on(min);
		break;
	case s_hour:
	case s_shour:
		led_on(hs);
		break;
	}
}

void up() {
	sec++;
	if( (sec%=60) == 0)
	{
		min++;
		if((min%=60) == 0)
		{
			hs++;
			hs %= 24;
		}
	}
}

void down() {
	if( sec == 0)
	{
		sec = 59;
		if(min == 0)
		{
			min = 59;
			if (hs == 0)
			{
				hs = 23;
			}
			else
			{
				hs--;
			}
		}
		else
		{
			min--;
		}
	}
	else
	{
		sec--;
	}
}
