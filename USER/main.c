#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "main.h"
#include "stdio.h"

int     valueNow               =                 0;//最初按键为未按下状态，0=未按下，1=按下
int     valueBefore            =                 0;//最初按键为未按下状态，0=未按下，1=按下

int     timePressed            =                 0;//最初按键被按下时长为0
int     timeBreak              =                 0;//最初两次按键间隔时长为0
        
int     stateNow               =                 StateNotPressed;//初始状态为未按键状态

int     isExtiEnable           =                 0;//初始状态未开启外部中断
int     isPwmEnable            =                 0;//初始状态未开启PWM输出
int     isIntHappen            =                 0;//外部EXTI中断未进入
int     valueIndex             =                 0;//初始状态下标为0
int     valuePwm               =                 0;//初始状态PWM的CCRx值为0
int     flagPwm                =                 1;//初始状态PWM增加
int     ValueBright[4]         =                 { 1,3,5,0 };
int     flagQuit               =                 0;//初始状态下不退出当前的动作
int     cnt                    =                 0;//初始状态下0次TIM进入


int main(void)
{
    delay_init();              
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    
    KEY_Init(); 
    LED_Init();    
    CLEAR_ALL_PARA();
    //通过配置arr和psc使TIM3每10ms触发一次中断
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


