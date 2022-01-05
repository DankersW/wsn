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

    char raw_buffer[50] = {};
    for (int i=0; i<size; ++i) {
        printf("%d ", msg[i]);
        raw_buffer[i] = msg[i] + '0';
    }
    printf("\n");
    printf("0: %d - %c \n", msg[0], raw_buffer[0]);
    printf("5: %d - %c \n", msg[5], raw_buffer[5]);
    printf("10: %d - %c \n", msg[10], raw_buffer[10]);

    size_t result = bin2hex(msg, size, raw_buffer, size);

    //size_t bin2hex(const uint8_t *buf, size_t buflen, char *hex, size_t hexlen)

    printf("Sensor ID: %s\n", message.sensor_id);
    printf("Temperature: %d\n", (int)message.temperature);
    printf("Humidity: %d\n\n", (int)message.humidity);
}
