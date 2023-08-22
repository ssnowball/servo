#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

const uint servoPin = 16;
const uint pwm_channel = 16; // PWM channel to use

const uint32_t pwm_frequency = 20000; // 100 Hz in microseconds

// Map degrees to PWM duty cycle (adjust these values according to your servo's specifications)
int min_angle = 0; // Minimum angle of the servo
int max_angle = 180; // Maximum angle of the servo
int min_duty = 1000; // Minimum duty cycle value
int max_duty = 5000; // Maximum duty cycle value

int angle_to_duty(int angle) {
	return ((angle - min_angle) * (max_duty - min_duty) / (max_angle - min_angle)) + min_duty;
}

int main(void) {
	
	stdio_init_all();
	sleep_ms(2000);
	//pwm_config pwm_cfg = pwm_get_default_config();
	// Set the PWM frequency to 100 Hz (10 ms period)
	
	//pwm_config_set_clkdiv(&pwm_cfg, pwm_clkdiv_int(pwm_frequency));
	
	//pwm_config_set_clkdiv(&pwm_cfg, pwm_clear_irq(pwm_frequency));
	
	//pwm_config_set_wrap(&pwm_cfg, 65535); // 16-bit resolution
	
	pwm_init(pwm_channel, 0);
	
	pwm_set_clkdiv(servoPin, 25);
	
	pwm_set_gpio_level(servoPin, 0);
	
	pwm_set_enabled(servoPin, true);
	
	int desired_angle = 90; // Set the desired angle of the servo (between min\_angle and max\_angle)
	
	int duty_cycle = angle_to_duty(desired_angle);
	
	while (1) {
		// Set the servo angle to the desired_angle

		pwm_set_gpio_level(servoPin, duty_cycle);

		printf("Set servo angle to: %d degrees\n", desired_angle);

		sleep_ms(2000); // Wait for a second
		
		// Change the desired_angle for the next iteration
		desired_angle = (desired_angle + 45) % 181; // Rotate the servo angle
		duty_cycle = angle_to_duty(desired_angle);
	}
	
	/*
	gpio_set_function(servoPin, GPIO_FUNC_PWM);
	
	uint slice_num = pwm_gpio_to_slice_num(servoPin);
	uint channel = pwm_gpio_to_channel(servoPin);
	
	pwm_set_clkdiv(slice_num, 256.0f);
	pwm_set_wrap(slice_num, 9803);
	pwm_set_enabled(slice_num, true);
	
	for (uint i = 0; i < 10; i++) {
		pwm_set_chan_level(slice_num, channel, 244);
		sleep_ms(2000);
		pwm_set_chan_level(slice_num, channel, 732);
		sleep_ms(2000);
		pwm_set_chan_level(slice_num, channel, 1700);
		sleep_ms(2000);
	}
	* 
	* */
	
}
