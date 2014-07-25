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

void func_task0(void)  // ��Ӧ�ղŵ�_func_task0
{
	static Uint16 TSK0 = 0;

	while (1) {   // ����һ�㶼����ѭ����ִֻ��һ�ε��������岻��l	
	    SEM_pend(&SEM_cnt, SYS_FOREVER);  // ��Ϣ����ֵ-1����Ϊ0��ֱ�ӷ��أ���������
	    
        LOG_printf(&trace, "TSK0=%u", TSK0++);
		TSK_yield();
	}		
}

void func_task1(void)  // ��Ӧ�ղŵ�_func_task1
{
	static Uint16 TSK1 = 0;

	while (1) {
        LOG_printf(&trace, "TSK1=%u", TSK1++);
		SWI_dec(&ADC_swi);  // ���ж��������ֵ�ݼ�
		TSK_yield();
	}		
}

void swi_adc(void)
{
    static Uint16 adc_cnt = 0;

    LOG_printf(&trace, "SWI_ADC=%u", adc_cnt++);
	SEM_post(&SEM_cnt);  // ��Ϣ�������ֵ+1
    
	// һ��ִ���������ֵ�ָ�Ϊ��ʼֵ2
}

void LedLink(void)
{
	static Uint16 i =0;

	i = (i + 1) & 0x01;
	GPIO_pinWrite(hGpio,GPIO_PIN3, i);
}

