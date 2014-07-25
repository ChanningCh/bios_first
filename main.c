/* 
 * xiahouzuoxin@163.com
 * 2014.7.25
 */


#include "bios_firstcfg.h"
#include <csl.h>
#include <csl_gpio.h>

static GPIO_Handle hGpio;

int main(void)
{
    CSL_init();

	hGpio = GPIO_open(GPIO_DEV0,GPIO_OPEN_RESET);
	GPIO_reset(hGpio);
	GPIO_pinEnable(hGpio,GPIO_PIN3);
	GPIO_pinDirection(hGpio,GPIO_PIN3,GPIO_OUTPUT);
	GPIO_pinWrite(hGpio,GPIO_PIN3,0);

    LOG_enable(&trace);
    LOG_printf(&trace, "Hello DSP/BIOS %d.", 0); 

	return 0;
} 

void func_task0(void)  // 对应刚才的_func_task0
{
	static Uint16 TSK0 = 0;

	while (1) {   // 任务一般都有死循环，只执行一次的任务意义不大l	
	    SEM_pend(&SEM_cnt, SYS_FOREVER);  // 消息邮箱值-1，不为0则直接返回，否则阻塞
	    
        LOG_printf(&trace, "TSK0=%u", TSK0++);
		TSK_yield();
	}		
}

void func_task1(void)  // 对应刚才的_func_task1
{
	static Uint16 TSK1 = 0;

	while (1) {
        LOG_printf(&trace, "TSK1=%u", TSK1++);
		SWI_dec(&ADC_swi);  // 软中断邮箱计数值递减
		TSK_yield();
	}		
}

void swi_adc(void)
{
    static Uint16 adc_cnt = 0;

    LOG_printf(&trace, "SWI_ADC=%u", adc_cnt++);
	SEM_post(&SEM_cnt);  // 消息邮箱计数值+1
    
	// 一次执行完后，邮箱值恢复为初始值2
}

void LedLink(void)
{
	static Uint16 i =0;

	i = (i + 1) & 0x01;
	GPIO_pinWrite(hGpio,GPIO_PIN3, i);
}

