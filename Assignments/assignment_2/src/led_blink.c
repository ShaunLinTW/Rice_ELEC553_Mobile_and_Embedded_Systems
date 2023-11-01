// Reference: https://www.auctoris.co.uk/2023/08/18/how-not-to-use-sysfs-for-gpio-on-a-raspberry-pi-how-you-should-do-it-in-2023/

#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
  // Define the GPIO chip and line variables
  const char *chip_title = "gpiochip0";
  struct gpiod_chip *chip;
  struct gpiod_line *led;
  struct gpiod_line *button;

  // Define the variables for the LED state and counter
  int state, counter;

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

  state = 0;
  // Now we'll blink the LED for a bit...
  for (counter=0;counter<10;counter++)
  {
    gpiod_line_set_value(led, state);
    state = !(state);
    // With a sleep of 100000 microseconds === 0.1 seconds
    usleep(100000);
  }
  // Release lines and chip & exit
  gpiod_line_set_value(led, 0);
  gpiod_line_release(led);
  gpiod_line_release(button);
  gpiod_chip_close(chip);
  return 0;
}