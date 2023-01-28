#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "adc.h"

//Ũ��ת������
//��Դ�ڲο�����
double convert(double v,double k,double v0)
{
 return (v-v0)/k;
}

 int main(void)
 {		
	 u16 adcx;
	 int t;
	 double temp;
	 char data[8];//�����洢Ũ�������ַ��������ڴ��ڴ�������
	 delay_init();//��ʱ������ʼ��
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	 uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	 Adc_Init();		  		//ADC��ʼ��
	 
	 while(1)
	{
		 	adcx=Get_Adc_Average(ADC_Channel_1,1);		//�õ�ADCת��ֵ	  
			temp=(double)adcx*(3.3/4096);			//�õ�ADC��ѹֵ
		  temp=convert(temp,1,5);  //Ũ��ת��
			sprintf(data,"%.3f",temp);  //��double��Ũ������ת��Ϊ�ַ�������ʽ

			for(t=0;t<8;t++)
			{
				USART_SendData(USART1, data[t]);//�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
		  delay_ms(10);//��ʱ10ms������100SPS�����ʣ�����Ƶ��100Hz	
	}
 }
