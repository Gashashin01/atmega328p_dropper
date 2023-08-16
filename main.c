#include <avr/io.h>
#include <util/delay.h>

void ADC_init(){
	ADMUX|=(1<<REFS0); // Настройка опорного напряжения (AREF) на VCC

	ADCSRA|=(1<<ADEN); // Разрешить работу АЦП
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // делитель 128

}

uint16_t ADC_read(uint8_t channel){
	// Выбор аналогового канала (0-7)
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

	// Запуск однократного преобразования
	ADCSRA |= (1 << ADSC);

	// Ожидание завершения преобразования
	while (ADCSRA & (1 << ADSC));

	// Возврат результата
	return ADC;
}

int main()
{
	ADC_init();

	DDRB |= (1<<PB1);
	PORTB = (1 << PB1);
	_delay_ms(1);
	PORTB=0b00000000;
	_delay_ms(500);

	uint8_t channel = 0;

	DDRB |= (1 << PB0);

	uint8_t mask = 0b00000000;

	while(1){
		uint16_t photoValue = ADC_read(channel);
		if (photoValue>600){
			PORTB = (1 << PB1);
			_delay_ms(2);
			PORTB=0b00000000;
			_delay_ms(1000);
		}
		else{
			PORTB = (1 << PB1);
			_delay_ms(1);
			PORTB=0b00000000;
			_delay_ms(1000);
		}
	}
}
