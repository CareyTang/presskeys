#include "sys.h"
#include "main.h"
#include "delay.h"
//������������ͨ��PWM�����ռ�ձȸı��������������
void Single_Press(void)
{
    if(stateNow == StateSinglePress)
        TIM_SetCompare2(TIM3,ValueBright[valueIndex]*100);
    if(stateNow == StateNotPressed)
    {
        TIM_SetCompare2(TIM3,0);
        CLEAR_ALL_PARA();//��ԭ������������ʼ״̬
    }
}

//Ҫ��ÿ5s���һ�����ڵı仯
//PWM��ʼ����ֻ����CNT>CCR1ʱ�Ż�����ߵ�ƽ
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
    stateNow = StateNotPressed;//�����ʼ״̬Ϊδ����״̬

    isExtiEnable = 0;//�Ƿ�ʹ���ⲿ�����ж�
    valuePwm =0;

    flagPwm = 1;//pwmռ�ձ����ӻ��Ǽ��ٵı�־λ
    cnt = 0;
}
