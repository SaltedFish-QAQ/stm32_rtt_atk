#include "led.h"
#include "stm32f10x.h"
#include <rtthread.h>

//the thread function declaration
static void LED_RED_thread_entry(void* parameter);
static void LED_YELLOW_thread_entry(void* parameter);

//the thread stack declaration
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t rt_LED_RED_thread_stack[256];
static rt_uint8_t rt_LED_YELLOW_thread_stack[256];

//the thread stack control model
static struct rt_thread LED_RED_thread;
static struct rt_thread LED_YELLOW_thread;

//the thread function function implementation
static void LED_RED_thread_entry(void* parameter)
{
    for (;;)
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
        rt_thread_delay(500);

        GPIO_SetBits(GPIOB, GPIO_Pin_5);
        rt_thread_delay(500);
    }
    
}
static void LED_YELLOW_thread_entry(void* parameter)
{
    for (;;)
    {
        rt_thread_delay(500);
        GPIO_ResetBits(GPIOE, GPIO_Pin_5);

        rt_thread_delay(500);
        GPIO_SetBits(GPIOE, GPIO_Pin_5);
    }
}

//the led borad periph config
void LED_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructrue;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);
    
    GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructrue);
    GPIO_SetBits(GPIOB, GPIO_Pin_5);

    GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOE, &GPIO_InitStructrue);
    GPIO_SetBits(GPIOE, GPIO_Pin_5);

}


void LED_RED_thread_init(void)
{
    rt_thread_init(
        &LED_RED_thread,
        "LED_RED",
        LED_RED_thread_entry,
        RT_NULL,
        &rt_LED_RED_thread_stack[0],
        sizeof(rt_LED_RED_thread_stack),
        3,
        20
    );
}

void LED_RED_thread_startup(void)
{
    rt_thread_startup(&LED_RED_thread);
}

void LED_YELLOW_thread_init(void)
{
    rt_thread_init(
        &LED_YELLOW_thread,
        "LED_YELLOW",
        LED_YELLOW_thread_entry,
        RT_NULL,
        &rt_LED_YELLOW_thread_stack[0],
        sizeof(rt_LED_YELLOW_thread_stack),
        3,
        20
    );
}

void LED_YELLOW_thread_startup(void)
{
    rt_thread_startup(&LED_YELLOW_thread);
}
