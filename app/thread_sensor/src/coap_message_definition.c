#include "coap_message_definition.h"

void gen_chip_temp_msg(uint8_t *msg_buf, struct sensor_value tempature_data)
{
    msg_buf[0] = THREAD_COAP_TEMP_MSG_CMD;
    msg_buf[1] = tempature_data.val1;
    msg_buf[2] = tempature_data.val2 * 0.0001;
}