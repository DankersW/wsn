// LED 1 GREEN 
#define LED1_G_NODE DT_PATH(leds, led_0)
#define LED1	DT_GPIO_LABEL(LED1_G_NODE, gpios)
#define LED1_PIN	DT_GPIO_PIN(LED1_G_NODE, gpios)
#define LED1_FLAG	DT_GPIO_FLAGS(LED1_G_NODE, gpios)

// LED 2 RED 
#define LED2_R_NODE DT_PATH(leds, led_1)
#define LED2_R	DT_GPIO_LABEL(LED2_R_NODE, gpios)
#define LED2_PIN_R	DT_GPIO_PIN(LED2_R_NODE, gpios)
#define LED2_FLAG_R	DT_GPIO_FLAGS(LED2_R_NODE, gpios)

// LED 2 GREEN 
#define LED2_G_NODE DT_PATH(leds, led_2)
#define LED2_G	DT_GPIO_LABEL(LED2_G_NODE, gpios)
#define LED2_PIN_G	DT_GPIO_PIN(LED2_G_NODE, gpios)
#define LED2_FLAG_G	DT_GPIO_FLAGS(LED2_G_NODE, gpios)

// LED 2 BLUE 
#define LED2_B_NODE DT_PATH(leds, led_3)
#define LED2_B	DT_GPIO_LABEL(LED2_B_NODE, gpios)
#define LED2_PIN_B	DT_GPIO_PIN(LED2_B_NODE, gpios)
#define LED2_FLAG_B	DT_GPIO_FLAGS(LED2_B_NODE, gpios)
