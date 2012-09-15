
#include <avr/io.h>
#include <util/delay.h>

#define forever while(true)

#define LEDS_QTY   8
#define SWS_QTY    8
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

#define SWS_NONE	0xFF
#define SWS_FIRST	0xFE
#define SWS_SECOND	0xFD
#define SWS_THIRD	0xFB
#define SWS_FOURTH	0xF7
#define SWS_FIFTH	0xEF
#define SWS_SIXTH	0xDF
#define SWS_SEVENTH	0xBF
#define SWS_EIGHT	0x7F
#define SWS_ALL		0x00

#define LEDS_PORT PORTB
#define LEDS_ADDR DDRB

#define SWS_PIN  PIND
#define SWS_ADDR DDRD

#define INPUT  0x00
#define OUTPUT 0xFF

#define MS_FAST	100
#define MS_SLOW 1000
#define MS_MID	500

char led_status;
char leds[] = { LED_FIRST,
				LED_SECOND,
				LED_THIRD,
				LED_FOURTH,
				LED_FIFTH,
				LED_SIXTH,
				LED_SEVENTH,
				LED_EIGHT,
				LED_ALL,
				LED_NONE };

typedef enum{
	false, true
} bool;

void change_leds() {
	LEDS_PORT = led_status;
}
void led_on(char led){
	led_status = led_status & (~led);
	change_leds();
}

void led_off(char led){
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
	LEDS_ADDR = OUTPUT;
	SWS_ADDR = INPUT;
	leds_off();
}

void ej1a() {
	led_on(LED_FIRST);

	forever;
}

void ej1b() {
	forever{
		led_on(LED_FIRST);
		_delay_ms(MS_SLOW);
		led_off(LED_FIRST);
		_delay_ms(MS_SLOW);
	}
}

void ej1c() {
	forever{
		led_on(LED_FIRST|LED_SECOND|LED_THIRD|LED_FOURTH);
		_delay_ms(MS_MID);
		leds_off();
		led_on(LED_FIFTH|LED_SIXTH|LED_SEVENTH|LED_EIGHT);
		_delay_ms(MS_MID);
		leds_off();
	}
}

void ej2a() {
	forever{
		LEDS_PORT = SWS_PIN;
		leds_off();
	}
}

void ej2b() {
	int i = 0;
	forever {
		int sws = SWS_PIN;
		if(sws != SWS_NONE) {
			if(i == 0) {
				led_off(LED_EIGHT);
			} else {
				led_off(leds[i-1]);
			}

			led_on(leds[i]);
			i = (i+1) % LEDS_QTY;
		}
	}
}

void ej2c() {
	int i = 0;
	char on = LED_FIRST;
	forever {
		int sws = SWS_PIN;
		if(sws != SWS_NONE) {
			led_on(on);
			i = (i+1) % LEDS_QTY;
			if(i == 0){
				on = LED_NONE;
			} else {
				on = on | leds[i];
			}
			_delay_ms(MS_MID);
		}
		if(i==0) {
			led_on(on);
			_delay_ms(MS_MID);
		}
	}
}

void ej2d() {
	int i = 0;
	forever {
		int sws = SWS_PIN;
		if(sws == SWS_FIRST) {
			if(i == 0) {
				led_off(LED_EIGHT);
			} else {
				led_off(leds[i-1]);
			}

			led_on(leds[i]);
			i = (i+1) % LEDS_QTY;
		}
		if(sws == SWS_EIGHT) {
			i = 0;
			leds_off(LED_ALL);
		}
		_delay_ms(MS_MID);
	}
}

void ej3() {
	int i = 0, j = 0;
	bool back;
	char on;
	led_on(LED_FIRST);
	forever {
		int sws = SWS_PIN;
		switch(sws) {
		case SWS_FIRST:
			if(i > LEDS_QTY - 1) {
				i = 0;
			} else {
				i++;
			}
			leds_off();
			led_on(leds[i]);
			break;
		case SWS_SECOND:
			if(i < 0) {
				i = LEDS_QTY - 1;
			} else {
				i--;
			}
			leds_off();
			led_on(leds[i]);
			break;
		case SWS_THIRD:
			leds_off();
			back = false;
			j = 0;
			do {
				if(back == false) {
					led_on(leds[j]);
					j++;
					if(j > LEDS_QTY-1) {
						back = true;
						j = 0;
					}
				}
				else {
					led_off(leds[j]);
					j++;
					if(j > LEDS_QTY -1) {
						back = false;
						j = 0;
					}
				}
				_delay_ms(MS_FAST);
				sws = SWS_PIN;
			}while(sws == SWS_NONE);
			leds_off();
			led_on(leds[i]);
			break;
		case SWS_FOURTH:
			leds_off();
			back = false;
			j = LEDS_QTY -1;
			do {
				if(back == false) {
					led_on(leds[j]);
					j--;
					if(j < 0) {
						back = true;
						j = LEDS_QTY -1;
					}
				}
				else {
					led_off(leds[j]);
					j--;
					if(j < 0) {
						back = false;
						j = LEDS_QTY -1;
					}
				}
				_delay_ms(MS_FAST);
				sws = SWS_PIN;
			}while(sws == SWS_NONE);
			leds_off();
			led_on(leds[i]);
			break;
		case SWS_FIFTH:
			leds_off();
			back = false;
			j = 0;
			do {
				if(back == false) {
					led_on(leds[j]);
					j++;
					if(j >= LEDS_QTY) {
						back = true;
						j = LEDS_QTY -1;
					}
				}
				else {
					led_off(leds[j]);
					j--;
					if(j < 0) {
						back = false;
						j = 0;
					}
				}
				_delay_ms(MS_FAST);
				sws = SWS_PIN;
			}while(sws == SWS_NONE);
			leds_off();
			led_on(leds[i]);
			break;
		case SWS_SIXTH:
			leds_off();
			back = false;
			j = LEDS_QTY -1;
			do {
				if(back == false) {
					led_on(leds[j]);
					j--;
					if(j < 0) {
						back = true;
						j = 0;
					}
				}
				else {
					led_off(leds[j]);
					j++;
					if(j >= LEDS_QTY) {
						back = false;
						j = LEDS_QTY -1;
					}
				}
				_delay_ms(MS_FAST);
				sws = SWS_PIN;
			} while (sws == SWS_NONE);
			leds_off();
			led_on(leds[i]);
			break;
		case SWS_SEVENTH:
			leds_off();
			back = false;
			j = 0;
			do {
				if(back == false) {
					leds_off();
					led_on(leds[j]);
					j++;
					if(j >= LEDS_QTY) {
						j = LEDS_QTY -1;
						back = true;
					}
				} else {
					leds_off();
					led_on(leds[j]);
					j--;
					if(j < 0) {
						j = 0;
						back = false;
					}
				}
				_delay_ms(MS_FAST);
				sws = SWS_PIN;
			}while(sws == SWS_NONE);
			leds_off();
			led_on(leds[i]);
			break;
		case SWS_EIGHT:
			break;
		}
	}
}

int main() {
	init();
	ej3();
	return 0;
}
