#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "main.h"
#include "stdio.h"

int     valueNow               =                 0;//�������Ϊδ����״̬��0=δ���£�1=����
int     valueBefore            =                 0;//�������Ϊδ����״̬��0=δ���£�1=����

int     timePressed            =                 0;//�������������ʱ��Ϊ0
int     timeBreak              =                 0;//������ΰ������ʱ��Ϊ0
        
int     stateNow               =                 StateNotPressed;//��ʼ״̬Ϊδ����״̬

int     isExtiEnable           =                 0;//��ʼ״̬δ�����ⲿ�ж�
int     isPwmEnable            =                 0;//��ʼ״̬δ����PWM���
int     isIntHappen            =                 0;//�ⲿEXTI�ж�δ����
int     valueIndex             =                 0;//��ʼ״̬�±�Ϊ0
int     valuePwm               =                 0;//��ʼ״̬PWM��CCRxֵΪ0
int     flagPwm                =                 1;//��ʼ״̬PWM����
int     ValueBright[4]         =                 { 1,3,5,0 };
int     flagQuit               =                 0;//��ʼ״̬�²��˳���ǰ�Ķ���
int     cnt                    =                 0;//��ʼ״̬��0��TIM����


int main(void)
{
    delay_init();              
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    
    KEY_Init(); 
    LED_Init();    
    CLEAR_ALL_PARA();
    //ͨ������arr��pscʹTIM3ÿ10ms����һ���ж�
    //Tout = (arr+1)*(pcc+1)/72 = 100*7200/72=10000us=10ms    
    TIM4_Int_Init(99,7199);
    TIM3_PWM_Init(899,0);

    while(1)
    {
        switch(stateNow)
        {
            case StateSinglePress:
                if(!isExtiEnable && !flagQuit)
                {
                    EXTIX_Init();
                    isExtiEnable = 1;
                }
                
                Single_Press();
                flagQuit = 0;
            break;
            
            case StateDoublePress:
                if(GPIO_ReadInputDataBit(KEY_PORT,KEY_PIN) == 0)
                {
                    if(!isExtiEnable && !flagQuit)
                    {
                        EXTIX_Init();
                        isExtiEnable = 1;
                    }
                    Double_Press();
                    flagQuit = 0;
                }
            break;
            
            case StateLongPress:
                if(!isExtiEnable && !flagQuit)
                {
                    EXTIX_Init();
                    isExtiEnable = 1;
                }
            break;
        }
    }

}


