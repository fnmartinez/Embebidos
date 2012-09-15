/*
 * switches.h
 *
 *  Created on: 10/09/2012
 *      Author: facundo
 */

#ifndef SWITCHES_H_
#define SWITCHES_H_
#include <avr/io.h>

#ifndef forever
#define forever while(true)
#endif
#if !defined(SWS_PIN) || !defined(SWS_DDR)
#define SWS_PIN PINA
#define SWS_DDR DDRA
#endif
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

#endif /* SWITCHES_H_ */
