#include "board.h"
#include <rtthread.h>
#include "led.h"

int main()
{
    LED_RED_thread_init();
    LED_YELLOW_thread_init();

    LED_RED_thread_startup();
    LED_YELLOW_thread_startup();
}
