#include <zephyr.h>
#include <sys/printk.h>
#include <usb/usb_device.h>
#include <logging/log.h>

#include <pb_encode.h>
#include <pb_decode.h>
#include "wsn.pb.h"

#include <stdio.h>
#include <string.h>


#define LOG_MODULE_NAME protobuf
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

#define MSG_SIZE 128

void some_handler();
int proto_encode(uint8_t *msg);
void decode_to_console(uint8_t *msg, uint8_t size);
void bin2str(uint8_t *data, size_t size, char *buffer);


void main(void)
{
	if (usb_enable(NULL)) {
		return;
	}
	k_sleep(K_SECONDS(1));
	
	while (1) {
		k_sleep(K_SECONDS(2));

        some_handler();
	}
}

void some_handler()
{
    uint8_t buffer[128];
    int msg_size = proto_encode(buffer);
    printk("Message encoded successfully with a size: %d \n", msg_size);
    decode_to_console(buffer, msg_size);
}

int proto_encode(uint8_t *msg)
{
    wsn_SensorData message = wsn_SensorData_init_zero;
    pb_ostream_t stream = pb_ostream_from_buffer(msg, MSG_SIZE);
        
	message.temperature = 25;
	message.humidity = 17;
    strcpy(message.sensor_id,"S01");
        
    if (!pb_encode(&stream, wsn_SensorData_fields, &message))
    {
        printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
        return 1;
    }
    return stream.bytes_written;
}

void decode_to_console(uint8_t *msg, uint8_t size) 
{
    wsn_SensorData message = wsn_SensorData_init_zero;
    pb_istream_t stream = pb_istream_from_buffer(msg, size);
    if (!pb_decode(&stream, wsn_SensorData_fields, &message))
    {
        printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
        return;
    }

    char raw_buffer[100] = {};
    bin2str(msg, size, raw_buffer);

    LOG_INF("raw: %s", log_strdup(raw_buffer));
    LOG_INF("decoded: type %d, id %s, temp %d, humi %d", wsn_MessageType_SENSOR_DATA, log_strdup(message.sensor_id), message.temperature, message.humidity);
}

void bin2str(uint8_t *data, size_t size, char *buffer)
{
    for (int i=0; i<size; ++i){
        char tmp[4];
        sprintf(tmp, "%d ", data[i]);
        strcat(buffer, tmp);
    }
}
