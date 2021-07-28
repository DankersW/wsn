// RED LED GPIO 
#define LED_R_NODE DT_PATH(leds, led_r)
#define LED_R	DT_GPIO_LABEL(LED_R_NODE, gpios)
#define PIN_R	DT_GPIO_PIN(LED_R_NODE, gpios)
#define FLAGS_R	DT_GPIO_FLAGS(LED_R_NODE, gpios)

// GREEN LED GPIO
#define LED_G_NODE DT_PATH(leds, led_g)
#define LED_G	DT_GPIO_LABEL(LED_G_NODE, gpios)
#define PIN_G	DT_GPIO_PIN(LED_G_NODE, gpios)
#define FLAGS_G	DT_GPIO_FLAGS(LED_G_NODE, gpios)

// BLUE LED GPIO
#define LED_B_NODE DT_PATH(leds, led_b)
#define LED_B	DT_GPIO_LABEL(LED_B_NODE, gpios)
#define PIN_B	DT_GPIO_PIN(LED_B_NODE, gpios)
#define FLAGS_B	DT_GPIO_FLAGS(LED_B_NODE, gpios)
