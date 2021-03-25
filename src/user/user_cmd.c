#include <rtthread.h>
#include <math.h>

//静态函数声明
static void hello_world(void);
static float f(float x, float y, float z);
static float h(float x, float z);
static void printf_func(rt_uint8_t i);
static void printf_xin(void);

//静态函数定义
static void hello_world(void)
{
    rt_kprintf("hello world!\n");
}

FINSH_FUNCTION_EXPORT_ALIAS(hello_world, __cmd_hello_world, RT-Thread say hello world!);

static float f(float x, float y, float z) {
    float a;
    a = x * x + 9.0f / 4.0f * y * y + z * z - 1;
    return a * a * a - x * x * z * z * z - 9.0f / 80.0f * y * y * z * z * z;
}

static float h(float x, float z) {
    float y;
    for ( y = 1.0f; y >= 0.0f; y -= 0.001f)
        if (f(x, y, z) <= 0.0f)
            return y;
    return 0.0f;
}

static void printf_func(rt_uint8_t i)
{
    switch (i)
    {
    case 0:
        rt_kprintf(".");
        break;
    
    case 1:
        rt_kprintf(":");
        break;
    
    case 2:
        rt_kprintf("-");
        break;
    
    case 3:
        rt_kprintf("=");
        break;
    
    case 4:
        rt_kprintf("+");
        break;
    
    case 5:
        rt_kprintf("*");
        break;
    
    case 6:
        rt_kprintf("#");
        break;
    
    case 7:
        rt_kprintf("%");
        break;
    
    case 8:
        rt_kprintf("@");
        break;
    
    default:
        break;
    }
}

static void printf_xin() {
    float z,x,v,y0,ny,nx,nz,nd,d;
    rt_uint8_t index;

    for ( z = 1.5f; z > -1.5f; z -= 0.05f) {
        for ( x = -1.5f; x < 1.5f; x += 0.025f) {
             v = f(x, 0.0f, z);
            if (v <= 0.0f) {
                 y0 = h(x, z);
                 ny = 0.01f;
                 nx = h(x + ny, z) - y0;
                 nz = h(x, z + ny) - y0;
                 nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
                 d = (nx + ny - nz) * nd * 0.5f + 0.5f;
                 index = (int)(d * 5.0f);
                 printf_func(index);
            }
            else
                rt_kprintf(" ");
        }
        rt_kprintf("\n");
    }
}

FINSH_FUNCTION_EXPORT_ALIAS(printf_xin, __cmd_xin, RT-Thread display a beautiful heart!);
