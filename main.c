/*
 * main.c
 *
 *  Created on: 13 Jun 2022
 *      Author: Laptop1
 */


#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#define A1 (1 << PD0)
#define A2 (1 << PD1)
#define B1 (1 << PD2)
#define B2 (1 << PD3)

#define STEP1 PORTD |= A1|B1; PORTD &= ~(A2|B2)
#define STEP2 PORTD |= A2|B1; PORTD &= ~(A1|B2)
#define STEP3 PORTD |= A2|B2; PORTD &= ~(A1|B1)
#define STEP4 PORTD |= A1|B2; PORTD &= ~(A2|B1)

int main()
{
	DDRD = 0x0f;

	// Init timer0 CTC, prescaller = 1024, ticks every 10ms
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS02) | (1 << CS00);
	TIMSK0 |= (1 << OCIE0A);
	OCR0A = 200;

	sei();

	while(1)
	{

	}
}

ISR(TIMER0_COMPA_vect)
{
	static uint8_t k;

	if(k == 0){
		STEP1;
		k++;
	}
	else if(k == 1){
		STEP2;
		k++;
	}
	else if(k == 2){
		STEP3;
		k++;
	}
	else if(k == 3){
		STEP4;
		k = 0;
	}
}
