#include <avr/io.h>
#include <util/delay.h>

#define SERVO PB1

#define F_CPU 1000000UL

void ADC_init(){
	ADMUX|=(1<<REFS0); // Setting the voltage reference (AREF) to VCC

	ADCSRA|=(1<<ADEN); // Enable ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // divider 128

}

uint16_t ADC_read(uint8_t channel){
	// Select analog channel (0-7)
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

	// Run a single conversion
	ADCSRA |= (1 << ADSC);

	// Waiting for the conversion to complete
	while (ADCSRA & (1 << ADSC));

	// Returning a result
	return ADC;
}

int main()
{
	ADC_init();

	DDRB |= (1<<SERVO);
	PORTB = (1 << SERVO);
	_delay_ms(1);
	PORTB=0b00000000;
	_delay_ms(500);

	uint8_t channel = 0;

	while(1){
		uint16_t photoValue = ADC_read(channel);
		if (photoValue>600){
			PORTB = (1 << SERVO);
			_delay_ms(2);
			PORTB=0b00000000;
			_delay_ms(1000);
		}
		else{
			PORTB = (1 << SERVO);
			_delay_ms(1);
			PORTB=0b00000000;
			_delay_ms(1000);
		}
	}
}
