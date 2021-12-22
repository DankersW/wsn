#include <zephyr.h>
#include <sys/printk.h>
#include <usb/usb_device.h>
#include <logging/log.h>

#include <pb_encode.h>
#include <pb_decode.h>
#include "wsn.pb.h"

#define LOG_MODULE_NAME usb_print_example
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

void main(void)
{
	if (usb_enable(NULL)) {
		return;
	}
	k_sleep(K_SECONDS(1));
	
	while (1) {
		k_sleep(K_SECONDS(2));
		proto_magic();
	}
}

int proto_magic()
{
	/* This is the buffer where we will store our message. */
    uint8_t buffer[128];
    size_t message_length;
    bool status;
    
    /* Encode our message */
    {
        wsn_SensorData message = wsn_SensorData_init_zero;
        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
        
		message.temperature = 25.0;
		message.humidity = 17.77;
        strcpy(message.sensor_id,"S01");
        
        status = pb_encode(&stream, wsn_SensorData_fields, &message);
        message_length = stream.bytes_written;
        if (!status)
        {
            printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }
    }

    /* 
	Now we could transmit the message over network, store it in a file or
    wrap it to a pigeon's leg.
    But because we are lazy, we will just decode it immediately. 
	*/
    
    {
        wsn_SensorData message = wsn_SensorData_init_zero;
        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);
        
        /* Now we are ready to decode the message. */
        status = pb_decode(&stream, wsn_SensorData_fields, &message);
        if (!status)
        {
            printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }
        
        /* Print the data contained in the message. */
        printf("Sensor ID: %s\n", message.sensor_id);
        printf("Message lenght: %d\n", message_length);
        printf("Temperature: %d\n", (int)message.temperature);
        printf("Humidity: %d\n\n", (int)message.humidity);
    }
    
    return 0;
}
