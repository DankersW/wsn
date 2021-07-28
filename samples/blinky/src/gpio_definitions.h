// RED LED GPIO 
#define LED_R_NODE DT_PATH(leds, led_1)
#define LED_R	DT_GPIO_LABEL(LED_R_NODE, gpios)
#define PIN_R	DT_GPIO_PIN(LED_R_NODE, gpios)
#define FLAGS_R	DT_GPIO_FLAGS(LED_R_NODE, gpios)
