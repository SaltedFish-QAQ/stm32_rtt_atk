#ifndef _LED_H_
#define _LED_H_

void LED_GPIO_Config(void);

void LED_RED_thread_init(void);
void LED_RED_thread_startup(void);
void LED_YELLOW_thread_init(void);
void LED_YELLOW_thread_startup(void);

#endif
