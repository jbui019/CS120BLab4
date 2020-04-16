/*	Author: jbui019
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
enum States{Start, standBy, increment, decrement, reset}state;
unsigned char count, tempA;
#endif


void tick(){
	switch(state){//transitions
		case Start:
			state = standBy;
			break;

		default:
			state = Start;
			break;

		case standBy:
			if(tempA == 0x03){
				state = reset;
			}
			else if(tempA == 0x01 && count < 9){
				state = increment;
			}
			else if(tempA == 0x02 && count > 0){
				state = decrement;
			}
			break;

		case reset:
			state = standBy;
			break;

		case increment:
			state = standBy;
			break;

		case decrement:
			state = standBy; 
			break;
	}

	switch(state){//actions
		default:
			break;

		case Start:
			count = 7;
			break;

		case standBy:
			break;

		case reset:
			count = 0;
			break;

		case increment:
			count++;
			break;

		case decrement:
			count--;
			break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	state = Start;
    while (1) {
	tempA = PINA;
	tick();	
	PORTC = count;
    }
    return 1;
}
