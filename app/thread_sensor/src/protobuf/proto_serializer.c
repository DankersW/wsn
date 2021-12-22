#include "proto_serializer.h"

uint8_t serialize_sensor_data_msg(uint8_t *msg_buf, struct sensor_value *tempature_data) 
{
    msg_buf[0] = 51;
    msg_buf[1] = tempature_data->val1;
    msg_buf[2] = tempature_data->val2 * 0.0001;
}