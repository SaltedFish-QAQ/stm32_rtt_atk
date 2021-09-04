#include <rtthread.h>
#include "stm32f10x.h"
#include "delay.h"

static rt_uint8_t  fac_us=0;							//us延时倍乘数			   
static rt_uint16_t fac_ms=0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数

void delay_init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //选择外部时钟  HCLK/8
    fac_us = SystemCoreClock / 8000000;                   //为系统时钟的1/8

    fac_ms = (u16)fac_us * 1000; //非OS下,代表每个ms需要的systick时钟数

}

void us_delay(rt_uint32_t us)
{
    rt_uint32_t temp;
    SysTick->LOAD = us * fac_us;              //时间加载
    SysTick->VAL = 0x00;                      //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始倒数
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16))); //等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;      //关闭计数器
    SysTick->VAL = 0X00;                            //清空计数器
}

void ms_delay(rt_uint32_t ms)
{
    rt_uint32_t temp;
    SysTick->LOAD = (rt_uint32_t)ms * fac_ms; //时间加载(SysTick->LOAD为24bit)
    SysTick->VAL = 0x00;                      //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始倒数
    do
    {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16))); //等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;      //关闭计数器
    SysTick->VAL = 0X00;                            //清空计数器
}
