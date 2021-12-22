#include <zephyr.h>
#include <sys/printk.h>
#include <usb/usb_device.h>
#include <logging/log.h>

#include <pb_encode.h>
#include <pb_decode.h>
#include "wsn.pb.h"

#define LOG_MODULE_NAME usb_print_example
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

#define MSG_SIZE 128

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
        
	message.temperature = 25.0;
	message.humidity = 17.77;
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
    printf("Sensor ID: %s\n", message.sensor_id);
    printf("Temperature: %d\n", (int)message.temperature);
    printf("Humidity: %d\n\n", (int)message.humidity);
}
