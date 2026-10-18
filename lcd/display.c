#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


/*
LCD pin	    Arduino pin	    AVR pin
RS	        3	            PD3
Enable	    4	            PD4
D0	        5	            PD5
D1	        6	            PD6
D2	        7	            PD7
D3	        8	            PB0
D4	        9	            PB1
D5	        10	            PB2
D6	        11	            PB3
D7	        12	            PB4
R/W	        GND	            Always write
*/

void lcd_enable_pulse() {
    PORTD |= (1 << PD4);    // Enable HIGH
    _delay_us(1);

    PORTD &= ~(1 << PD4);   // Enable LOW
    _delay_us(50);
}

void lcd_send_byte(uint8_t data, uint8_t is_data){
    if(is_data != 0){
        PORTD |= 1 << PD3;
    }
    else{
        PORTD &= ~(1 << PD3);
    }

    if (data & (1 << 0)) {
        PORTD |= (1 << PD5);   // Set PD5 high
    } else {
        PORTD &= ~(1 << PD5);  // Set PD5 low
    }

    if (data & (1 << 1)) {
        PORTD |= (1 << PD6);   // Set PD6 high
    } else {
        PORTD &= ~(1 << PD6);  // Set PD6 low
    }

    if (data & (1 << 2)) {
        PORTD |= (1 << PD7);   // Set PD7 high
    } else {
        PORTD &= ~(1 << PD7);  // Set PD7 low
    }
    
    if (data & (1 << 3)) {
        PORTB |= (1 << PB0);   // Set PB0 high
    } else {
        PORTB &= ~(1 << PB0);  // Set PB0 low
    }

    if (data & (1 << 4)) {
        PORTB |= (1 << PB1);   // Set PB1 high
    } else {
        PORTB &= ~(1 << PB1);  // Set PB1 low
    }
    
    if (data & (1 << 5)) {
        PORTB |= (1 << PB2);   // Set PB2 high
    } else {
        PORTB &= ~(1 << PB2);  // Set PB2 low
    }

    if (data & (1 << 6)) {
        PORTB |= (1 << PB3);   // Set PB3 high
    } else {
        PORTB &= ~(1 << PB3);  // Set PB3 low
    }

    if (data & (1 << 7)) {
        PORTB |= (1 << PB4);   // Set PB4 high
    } else {
        PORTB &= ~(1 << PB4);  // Set PB4 low
    }

    lcd_enable_pulse();
}

void lcd_init(void) {
    _delay_ms(50);  // Wait for LCD power-up

    lcd_send_byte(0x38, 0);  // 8-bit mode, 2 lines, 5x8 font
    _delay_ms(5);

    lcd_send_byte(0x0C, 0);  // Display ON, cursor OFF
    _delay_ms(1);

    lcd_send_byte(0x06, 0);  // Cursor moves right after each character
    _delay_ms(1);

    lcd_send_byte(0x01, 0);  // Clear display
    _delay_ms(2);
}

int main(){
    // data pins are connected to pins 5-12
    DDRD |= (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
    DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4);

    lcd_init();
    
    lcd_send_byte(0x4C, 1);
    lcd_send_byte(0x4F, 1);
    lcd_send_byte(0x43, 1);
    lcd_send_byte(0x4B, 1);
    lcd_send_byte(0x20, 1);
    lcd_send_byte(0x49, 1);
    lcd_send_byte(0x4E, 1);
    lcd_send_byte(0x21, 1);


    while(1){

    }
}