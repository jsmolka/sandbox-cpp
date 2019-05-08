#define F_CPU 8000000

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "integer.h"
#include "sine.h"
#include "utility.h"

// Notes frequencies (MHz)
typedef enum note_t
{
	NOTE_P    =   0,  // Pause
	NOTE_C3   = 261,
	NOTE_D3   = 293,
	NOTE_E3   = 329,
	NOTE_F3   = 349,
	NOTE_FIS3 = 370,
	NOTE_G3   = 391,
	NOTE_GIS3 = 415,
	NOTE_A3   = 440,
	NOTE_B3   = 466,
	NOTE_H3   = 493,
	NOTE_C4   = 523,
	NOTE_D4   = 587,
	NOTE_E4   = 659,
	NOTE_F4   = 698,
	NOTE_FIS4 = 740,
	NOTE_G4   = 783,
	NOTE_A4   = 880,
	NOTE_H4   = 986,
	NOTE_C5   = 1047
} Note;

const Note mario[191] =
{
	NOTE_E4,   NOTE_E4,   NOTE_E4,   NOTE_C4,   NOTE_E4,   NOTE_G4,   NOTE_G3,   NOTE_C4, 
	NOTE_G3,   NOTE_E3,   NOTE_A3,   NOTE_H3,   NOTE_B3,   NOTE_A3,   NOTE_G3,   NOTE_E4, 
	NOTE_G4,   NOTE_A4,   NOTE_F4,   NOTE_G4,   NOTE_E4,   NOTE_C4,   NOTE_D4,   NOTE_H3,
	NOTE_C4,   NOTE_G3,   NOTE_E3,   NOTE_A3,   NOTE_H3,   NOTE_B3,   NOTE_A3,   NOTE_G3, 
	NOTE_E4,   NOTE_G4,   NOTE_A4,   NOTE_F4,   NOTE_G4,   NOTE_E4,   NOTE_C4,   NOTE_D4, 
	NOTE_H3,   NOTE_G4,   NOTE_FIS4, NOTE_F4,   NOTE_D4,   NOTE_E4,   NOTE_G3,   NOTE_A3, 
	NOTE_C4,   NOTE_A3,   NOTE_C4,   NOTE_D4,   NOTE_G4,   NOTE_FIS4, NOTE_F4,   NOTE_D4, 
	NOTE_E4,   NOTE_C5,   NOTE_C5,   NOTE_C5,   NOTE_G4,   NOTE_FIS4, NOTE_F4,   NOTE_D4, 
	NOTE_E4,   NOTE_G3,   NOTE_A3,   NOTE_C4,   NOTE_A3,   NOTE_C4,   NOTE_D4,   NOTE_D4,
	NOTE_D4,   NOTE_C4,   NOTE_C4,   NOTE_C4,   NOTE_C4,   NOTE_C4,   NOTE_D4,   NOTE_E4, 
	NOTE_C4,   NOTE_A3,   NOTE_G3,   NOTE_C4,   NOTE_C4,   NOTE_C4,   NOTE_C4,   NOTE_D4, 
	NOTE_E4,   NOTE_C4,   NOTE_C4,   NOTE_C4,   NOTE_C4,   NOTE_D4,   NOTE_E4,   NOTE_C4, 
	NOTE_A3,   NOTE_G3,   NOTE_E4,   NOTE_E4,   NOTE_E4,   NOTE_C4,   NOTE_E4,   NOTE_G4,
	NOTE_G3,   NOTE_C4,   NOTE_G3,   NOTE_E3,   NOTE_A3,   NOTE_H3,   NOTE_B3,   NOTE_A3,
	NOTE_G3,   NOTE_E4,   NOTE_G4,   NOTE_A4,   NOTE_F4,   NOTE_G4,   NOTE_E4,   NOTE_C4, 
	NOTE_D4,   NOTE_H3,   NOTE_C4,   NOTE_G3,   NOTE_E3,   NOTE_A3,   NOTE_H3,   NOTE_B3, 
	NOTE_A3,   NOTE_G3,   NOTE_E4,   NOTE_G4,   NOTE_A4,   NOTE_F4,   NOTE_G4,   NOTE_E4, 
	NOTE_C4,   NOTE_D4,   NOTE_H3,   NOTE_E4,   NOTE_P,    NOTE_C4,   NOTE_G3,   NOTE_G3, 
	NOTE_A3,   NOTE_F4,   NOTE_F4,   NOTE_A3,   NOTE_H3,   NOTE_A4,   NOTE_A4,   NOTE_A4, 
	NOTE_G4,   NOTE_F4,   NOTE_E4,   NOTE_C4,   NOTE_A3,   NOTE_G3,   NOTE_E4,   NOTE_P,
	NOTE_C4,   NOTE_G3,   NOTE_G3,   NOTE_A3,   NOTE_F4,   NOTE_F4,   NOTE_A3,   NOTE_H3, 
	NOTE_F4,   NOTE_F4,   NOTE_F4,   NOTE_E4,   NOTE_D4,   NOTE_C4,   NOTE_G3,   NOTE_E3, 
	NOTE_C3,   NOTE_C4,   NOTE_G3,   NOTE_E3,   NOTE_A3,   NOTE_H3,   NOTE_A3,   NOTE_GIS3, 
	NOTE_B3,   NOTE_GIS3, NOTE_G3,   NOTE_P,    NOTE_FIS3, NOTE_P,    NOTE_G3
};

// Global variables
u8 sine_counter = 0;
u8 pwm_paused = 0;
u8 volume = 4;

// Sine value with adjusted amplitude
u8 get_sine(u8 position)
{
	return volume * sine_lut[position];
}

// Set note by modifying the timer counter
void set_note(Note note)
{
	OCR1A = (u32)160000 / note - 1;
}

void init_timer(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	
	// Set prescaling to 1
	TCCR1B |= (1 << CS10);
	// Set CTC OCRA mode
	TCCR1B |= (1 << WGM12);
	// Set OCR1A start value
	OCR1A = 0xFF;
	// Enable OCRA interrupt
	TIMSK |= (1 << OCIE1A);
}

void init_pwm(void)
{
	TCCR0 = 0;
	
	// Set fast PWM
	TCCR0 |= (1 << WGM01) | (1 << WGM00);
	// Clear OC0 on compare match
	TCCR0 |= (1 << COM01);
	// Set prescaling to 1
	TCCR0 |= (1 << CS00);
	// Set OCR0 start value
	OCR0 = 0xFF;
}

// 4kHz timer interrupt
ISR(TIMER1_COMPA_vect)
{
	// Voltage changes cause sound
	if (pwm_paused)
		return;
		
	// Continue to the next sine value
	OCR0 = get_sine(sine_counter++);
	if (sine_counter == 50)
		sine_counter = 0;
}

ISR(INT0_vect)	
{
	volume = min(volume + 1, 8);
}

ISR(INT1_vect)	
{
	volume = max(volume - 1, 1);
}

int main(void)
{
	TIMSK = 0;
	// Port B output
	DDRB = 0xFF;

	// Enable button interrupts
	GICR  |=  (1 << INT0) | (1 << INT1);	
	MCUCR |=  (1 << ISC01);
	MCUCR &= ~(1 << ISC00);
	MCUCR |=  (1 << ISC11);
	MCUCR &= ~(1 << ISC10);
	
	sei();
	
	init_pwm();
	init_timer();
	
	while (1)
	{
		for (u8 i = 0; i < sizeof(mario); ++i)
		{
			Note note = mario[i];
			
			if (note == NOTE_P)
			{
				pwm_paused = 1;
				__builtin_avr_delay_cycles(F_CPU / 20);
				pwm_paused = 0;
			}
			else
			{
				set_note(note);
				__builtin_avr_delay_cycles((double)F_CPU / (double)5.5);
			}
		}
	}	
}
