#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "adc.h"

//浓度转换函数
//来源于参考文献
double convert(double v,double k,double v0)
{
 return (v-v0)/k;
}

 int main(void)
 {		
	 u16 adcx;
	 int t;
	 double temp;
	 char data[8];//用来存储浓度数据字符串，用于串口传输数据
	 delay_init();//延时函数初始化
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	 uart_init(115200);	 	//串口初始化为115200
	 Adc_Init();		  		//ADC初始化
	 
	 while(1)
	{
		 	adcx=Get_Adc_Average(ADC_Channel_1,1);		//得到ADC转换值	  
			temp=(double)adcx*(3.3/4096);			//得到ADC电压值
		  temp=convert(temp,1,5);  //浓度转换
			sprintf(data,"%.3f",temp);  //将double型浓度数据转换为字符串的形式

			for(t=0;t<8;t++)
			{
				USART_SendData(USART1, data[t]);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
		  delay_ms(10);//延时10ms，满足100SPS采样率，采样频率100Hz	
	}
 }
