/*
 * File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-16     armink       first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>

//#define LED_PIN	3

//动态线程
#define THREAD_PRIORITY 25
#define THREAD_STACK_SIZE 512
#define THREAD_TIMESLICE 5
static rt_thread_t tid_1= RT_NULL;

static void thread1_entry(void *parameter)
{
	rt_uint32_t count=0;
	
	while(1)
	{
		rt_kprintf("thread1 count : %d\n",count);
		count++;
		rt_thread_mdelay(500);
	}
}

//静态线程
static char thread2_stack[1024];
static struct rt_thread thread2;
static void thread2_entry(void *param)
{
	rt_uint32_t count=0;

	for(count=0;count<10;count++)
	{
		rt_kprintf("thread2 count : %d\n",count);
	}
	rt_kprintf("thread2 exit\n");
}


int main(void)
{	
	
	
    return 0;
}

//int led(void)
//{
//    rt_uint8_t count;

//    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);  
//    
//    for(count = 0 ; count < 10 ;count++)
//    {       
//        rt_pin_write(LED_PIN, PIN_HIGH);
//        rt_kprintf("led on, count : %d\r\n", count);
//        rt_thread_mdelay(500);
//        
//        rt_pin_write(LED_PIN, PIN_LOW);
//        rt_kprintf("led off\r\n");
//        rt_thread_mdelay(500);
//    }
//    return 0;
//}


int thread_sample1(void)
{
	//创建动态线程1
	tid_1 = rt_thread_create("thread1",thread1_entry,RT_NULL,THREAD_STACK_SIZE,THREAD_PRIORITY,THREAD_TIMESLICE);
	//如果创建成功，则启动这个动态线程
	if(tid_1 != RT_NULL)
	{
		rt_thread_startup(tid_1);
	}
	
	
	//创建静态线程2
	rt_thread_init(&thread2,"thread2",thread2_entry,RT_NULL,&thread2_stack[0],sizeof(thread2_stack),24,THREAD_TIMESLICE);
	rt_thread_startup(&thread2);
	
	return 0;
}

MSH_CMD_EXPORT(thread_sample1, thread sample1);
//MSH_CMD_EXPORT(thread_sample, RT-Thread first kprintf sample);
