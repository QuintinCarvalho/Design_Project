/*
 * ECE_388_Design_Project.c
 *
 * Created: 11/8/2020 7:32:25 AM
 * Author : Quintin Carvalho
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <util/delay.h>
#define F_CPU 16000000

// GLOBAL VARS and SYMBOLS

uint8_t Accelero;
uint8_t AnalogRead8(uint8_t channel);
uint8_t dice_value;
uint8_t Roll_Dice();
uint8_t random_output;
uint8_t val;
uint8_t temp = 0; 
void DisplayDice(uint8_t what);
uint8_t dicetab[]= {0x0,0x10,0x28,0x92,0xAA,0xBA,0xEE};       // {1, 2, 3, 4, 5, 6}


int main(void)
{
    /* Replace with your application code */
	DDRC = 0b11111110;
	DDRD = 0b11111111;
	PORTD = 0;
	srand(time(NULL));
    while (1) 
    {
		PORTD = dicetab[temp];
		Accelero=AnalogRead8(0);
		if (Accelero >= 150)
		{
			dice_value=Roll_Dice();
			if (dice_value > 0 & dice_value <= 6)
			{
				DisplayDice(dice_value);
				_delay_us(1000000);
				
			}
			
		}
		
		if (Accelero < 150)
		{
			PORTD = 0;
		}
		
    }
}


uint8_t AnalogRead8(uint8_t channel)
{
	ADMUX = (0b01<<REFS0) | (1<<ADLAR) | (channel<<MUX0);
	ADCSRA = (1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIE) | (0b111<<ADPS0);
	ADCSRB = 0b000<<ADTS0;
	ADCSRA |= (1<<ADSC);
	while ((ADCSRA & (1<<ADIF))==0);
	return ADCH;		// High byte of result
}

uint8_t Roll_Dice()
{
	//srand(time(NULL));
	val=rand();
	random_output = val%10;
	temp = random_output;
	return random_output;
}

void DisplayDice(uint8_t what)
{
	PORTD = dicetab[what]; // obtain the desired value d from dicetab
}


