#include "sys.h"
#include "main.h"
#include "delay.h"
//单击按键可以通过PWM输出的占空比改变来输出三种亮度
void Single_Press(void)
{
    if(stateNow == StateSinglePress)
        TIM_SetCompare2(TIM3,ValueBright[valueIndex]*100);
    if(stateNow == StateNotPressed)
    {
        TIM_SetCompare2(TIM3,0);
        CLEAR_ALL_PARA();//还原所有数据至初始状态
    }
}

//要求每5s完成一个周期的变化
//PWM初始化后，只有在CNT>CCR1时才会输出高电平
void Double_Press(void) 
{
    if(stateNow == StateDoublePress)
    {
        delay_ms(10);
        if(flagPwm) valuePwm += 2;
        else valuePwm -= 2;
        
        if(valuePwm > 500) flagPwm = 0;
        if(valuePwm == 0) flagPwm = 1;
        
        TIM_SetCompare2(TIM3,valuePwm);
    }
}

void CLEAR_ALL_PARA(void)
{
    timePressed            =                 0;
    timeBreak              =                 0;
    valueIndex = 0;
    stateNow = StateNotPressed;//定义初始状态为未按键状态

    isExtiEnable = 0;//是否使能外部按键中断
    valuePwm =0;

    flagPwm = 1;//pwm占空比增加还是减少的标志位
    cnt = 0;
}
