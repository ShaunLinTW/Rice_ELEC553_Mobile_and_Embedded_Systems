///////////////////////////////////////
// COMP/ELEC 424/553
// Assignment 2
// Authors: Shaun Lin(hl116)
//////////////////////////////////////

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

unsigned long measure_press_duration(struct gpiod_line *button);

int main()
{
    // Define the GPIO chip and line variables
    const char *chip_title = "gpiochip0";
    struct gpiod_chip *chip;
    struct gpiod_line *led;
    struct gpiod_line *button;

    // Define the variables for the LED state, counter and time
    int state, counter;
    unsigned long blink_rate = 500000; // in microseconds (0.5 s)

    // Setup the GPIO Chip struct...
    chip = gpiod_chip_open_by_name(chip_title);
    // Setup the GPIO "line"  (pin 5)
    led = gpiod_chip_get_line(chip, 5);
    // Setup the GPIO "line"  (pin 6)
    button = gpiod_chip_get_line(chip, 6);
    // Set the LED "line" for output
    gpiod_line_request_output(led, "GPIO 5 Output", 0);
    // Set the button "line" for input
    gpiod_line_request_input(button, "GPIO 6 Input");

    // Initialize the LED state
    state = 0;

    // instructions
    printf("\nQuickly press the button to change the blink rate.\n");
    printf("Press and hold the button for more than 1 second to reset the blink rate.\n");
    printf("(Press Ctrl+C to exit.)\n");

    while (1)
    {
        // Button is not pressed
        if (gpiod_line_get_value(button) == 1)
        {
            gpiod_line_set_value(led, state);
            usleep(blink_rate);
            state = !state;
        }
        // Button is pressed
        else
        {
            // Measure the duration of the button press
            unsigned long press_duration = measure_press_duration(button);
            // Debugging
            // printf("Button is pressed for %lu microseconds\n", press_duration);

            // If button is pressed for less than 1 s
            if (press_duration < 1000000)
            {
                blink_rate /= 2; // Double the blink rate
                printf(">> Doubled the blink rate...\n");
            }
            else
            {
                blink_rate = 500000; // Reset to original rate
                printf(">> Reset the blink rate...\n");
            }
            usleep(20000); // Sleep for 20 ms to prevent bouncing
        }
    }

    // Release lines and chip & exit
    gpiod_line_release(led);
    gpiod_line_release(button);
    gpiod_chip_close(chip);
    return 0;
}

// Function to measure button press duration
unsigned long measure_press_duration(struct gpiod_line *button)
{
    unsigned long duration = 0;
    const struct timespec delay = {0, 100}; // 100 nanoseconds

    // Wait for button to be pressed if not already pressed
    while (gpiod_line_get_value(button) == 1)
    {
        nanosleep(&delay, NULL);
    }

    // Measure the duration of the button press
    while (gpiod_line_get_value(button) == 0)
    {
        nanosleep(&delay, NULL);
        duration += 100; // Add 100 nanoseconds to duration
    }

    return duration;
}