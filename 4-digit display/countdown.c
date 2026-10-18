#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
    using multiplexing to display each digit
    multiplexing is the idea of having each digit rapidly turn on and off which happens so fast that it creates the illusion
    that all of the digits are on at the same time, when slowing down the process via _delay_ms() you can actually see each digit 
    light up, turn off, and repeated for the next digit
*/

// stop using _delay_ms() and use the timer registers
//   

static const uint8_t segment_patterns[10] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

static uint8_t display_buffer[4] = {9, 9, 9, 9};

static volatile uint16_t elapsed_ms = 0;

static volatile uint8_t current_digit = 0;

void set_segments(uint8_t pattern){
    // look at each bit in pattern
    // and set/clear the corresponding GPIO
    // 0 g f e d c b a

    // A
    if(pattern & (1 << 0)){
        PORTD |= (1 << PORTD7);
    }
    else{
        PORTD &= ~(1 << PORTD7);
    }

    // B
    if(pattern & (1 << 1)){
        PORTB |= (1 << PORTB1);
    }
    else{
        PORTB &= ~(1 << PORTB1);
    }

    // C
    if(pattern & (1 << 2)){
        PORTD |= (1 << PORTD5);
    }
    else{
        PORTD &= ~(1 << PORTD5);
    }

    // D
    if(pattern & (1 << 3)){
        PORTD |= (1 << PORTD3);
    }
    else{
        PORTD &= ~(1 << PORTD3);
    }

    // E
    if(pattern & (1 << 4)){
        PORTD |= (1 << PORTD2);
    }
    else{
        PORTD &= ~(1 << PORTD2);
    }

    // F
    if(pattern & (1 << 5)){
        PORTB |= (1 << PORTB0);
    }
    else{
        PORTB &= ~(1 << PORTB0);
    }

    // G
    if(pattern & (1 << 6)){
        PORTD |= (1 << PORTD6);
    }
    else{
        PORTD &= ~(1 << PORTD6);
    }
}

void select_digit(uint8_t digit){
    // blank all digits first
    PORTC |= (1 << PORTC0) | (1 << PORTC1) | (1 << PORTC2) | (1 << PORTC3);
    if(digit < 4){
        PORTC &= ~(1 << digit);
    }
    // digit == 4 (or anything >=4) just leaves everything blanked
}

ISR(TIMER1_COMPA_vect)
{
    // code executed every 1 ms
    select_digit(4);
    
    set_segments(segment_patterns[display_buffer[current_digit]]);

    select_digit(current_digit);

    current_digit++;

    if(current_digit >= 4)
        current_digit = 0;
    
    elapsed_ms ++;

}

int main(){


    DDRD |= (1 << DDD2) | (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
    DDRB |= (1 << DDB0) | (1 << DDB1);
    DDRC |= (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3);

    //set input port (for the button)
    DDRB &= ~(1 << DDB2);
    
    PORTB |= (1 << PORTB2);

    TCCR1B = (1 << WGM12);
    OCR1A = 249;

    TIMSK1 = (1 << OCIE1A);

    TCCR1B |= (1 << CS11) | (1 << CS10);

    uint8_t is_running = 1; // 1 is running, 0 is paused
    uint8_t button_was_pressed = 0; // Tracks if button was held down in previous loop
    sei();

    uint16_t countdown = 9999;
    
    while(1){
        if (!(PINB & (1 << PINB2))) {
            _delay_ms(50); // Software debounce to ignore mechanical button noise
            
            if (!(PINB & (1 << PINB2))) { // Double check it's still pressed
                if (!button_was_pressed) {
                    is_running ^= 1;          //  XOR toggle flips between 1 and 0
                    button_was_pressed = 1;   // Prevents it from rapidly toggling while held
                }
            }
        }
        else {
            button_was_pressed = 0; // Reset tracking when you let go of the button
        }


        if(is_running){
            if(elapsed_ms >= 1000){
                elapsed_ms = 0;
                display_buffer[3 - current_digit] -= 1;

                countdown--;

                display_buffer[0] = countdown / 1000;
                display_buffer[1] = (countdown / 100) % 10;
                display_buffer[2] = (countdown / 10) % 10;
                display_buffer[3] = countdown % 10;
            }

        }   
    
    }
}