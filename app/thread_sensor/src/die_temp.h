#ifndef DIE_TEMP_H
#define DIE_TEMP_H

#include <drivers/sensor.h>
#include <logging/log.h>

void setup_chip_temp_sensor(void);
struct sensor_value get_chip_temp();

#endif // DIE_TEMP_H