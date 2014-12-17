#include <AP_Common.h>
#include <AP_Math.h>
#include <AP_Param.h>
#include <AP_Progmem.h>
#include <AP_ADC.h>
#include <AP_InertialSensor.h>

#include <AP_HAL.h>
#include <AP_HAL_AVR.h>

const AP_HAL::HAL& hal = AP_HAL_AVR_APM2;  // Hardware abstraction layer

#define SERVO   1    // servo

void setup() 
{
hal.rcout->set_freq(0xF, 50);
hal.rcout->enable_mask(0xFF);
}

void loop() 
{
  uint16_t channels[8];  // array for raw channel values
  
  // Read RC channels and store in channels array
  hal.rcin->read(channels, 8);
  
  // Copy from channels array to something human readable - array entry 0 = input 1, etc.
  uint16_t rcservo;   // Variables to store rc input
  rcservo = channels[0];
  
  hal.rcout->write(SERVO, rcservo);

}

AP_HAL_MAIN();    // special macro that replace's one of Arduino's to setup the code (e.g. ensure loop() is called in a loop).
