#include "proto_serializer.h"

uint8_t serialize_sensor_data(uint8_t *msg_buf, struct sensor_value *tempature_data) 
{
    wsn_SensorData message = wsn_SensorData_init_zero;
    pb_ostream_t stream = pb_ostream_from_buffer(msg_buf, PROTO_MSG_MAX_SIZE);

    float temperature = tempature_data->val1 + tempature_data->val2 * 0.000001;
        
	message.temperature = (int)(temperature*10);
	message.humidity = 0;
    strcpy(message.sensor_id, SENSOR_ID);

    if (!pb_encode(&stream, wsn_SensorData_fields, &message))
    {
        printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
        return 0;
    }
    return stream.bytes_written;;
}