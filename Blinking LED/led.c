#include <avr/io.h>
#include <util/delay.h>

int main(){
    // use a button to turn the LED on, input port is PC0 (Port C bit 0) (direction register: DDRC)

    //set output port
    DDRB |= (1 << DDB5);

    //set input port (for the button)
    DDRC &= ~(1 << DDC0);
    
    PORTC |= (1 << PORTC0);

    uint8_t prev_state = 1; // previous state, start assuming button was released
    uint8_t current_state = 0; // current state
    uint8_t led_state = 0; 
    while(1){
        
        // get the current state from port C pin 0, set current state = 1 if high, current state = 0 if low
        current_state = (PINC & (1 << PINC0)) ? 1 : 0;

        // if there is a change in state (button was released and is now pressed)
        if(prev_state == 1 && current_state == 0){
            
            // toggle LED state
            led_state = !led_state;
            
            // if the led state is 1, set the bit
            if(led_state){
                PORTB |= (1 << PORTB5);
            }

            // else, clear the bit
            else{
                PORTB &= ~(1 << PORTB5); 
            }
        }

        prev_state = current_state; // advance the state for next iteration
    }
}