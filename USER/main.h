/******************************define********************************/
#define KEY_PORT                             GPIOE
#define KEY_PIN                              GPIO_Pin_4
#define LED_PORT                             GPIOB
#define LED_PIN                              GPIO_Pin_5
#define ValuePressed                         0
#define ValueNotPressed                      1
#define TimeLongPress                        200
#define TimeDoublePress                      100
#define StateNotPressed                      0x11
#define StatePressed                         0x22
#define StateLongPress                       0x33
#define StateDoublePress                     0x44
#define StateSinglePress                     0x55
#define StateNextState                       0x66

/*******************************����********************************/
extern int valueNow, //��¼��һ��TIM�ж�ʱ��ȡ�İ���״̬
           valueBefore;//��¼��ǰTIM�ж�ʱ��ȡ�İ���״̬

extern int timePressed,//������һ�α����µ�̧���ʱ��
           timeBreak;//���ΰ������ʱ��
extern int cnt;//�������㷢���˶��ٴ�TIM
extern int stateNow;//�����ʼ״̬Ϊδ����״̬

extern int isExtiEnable;//�Ƿ�ʹ���ⲿ�����ж�
extern int isPwmEnable;//�Ƿ�ʹ��PWM���
extern int isIntHappen;//�ⲿEXTI�ж��Ƿ���룬�൱��ucos���ٽ�Σ���ֹ�жϱ����
extern int valuePwm;//˫������ʱ�����PWM�Ƚ�ֵ
extern int flagPwm ;//pwmռ�ձ����ӻ��Ǽ��ٵı�־λ
extern int ValueBright[];//��������ʱ�����PWM�������ȵ�ֵ
extern int valueIndex;//��������ʱ�����PWM�������ȵ�ֵ���±�
extern int flagQuit;//��ʼ״̬�²��˳���ǰ�Ķ���

/*************************��������********************/
void Single_Press(void);//������������
void Double_Press(void);//˫����������
void TIM3_Handler(void);//��ʱ��TIM3�жϴ�����
void EXTIX_Init(void);//�ⲿ�жϴ�����
void CLEAR_ALL_PARA(void);//��ԭ���б�������ʼ������
