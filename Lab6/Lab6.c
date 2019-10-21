/**
 * Copyright (C) ����1172-���ӿ� ID��201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * ��Ƭ����ҵ
 */
#include <reg51.h>

// LED��ʾ��ģ
char led_mod[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

char ctime = 0;
char timerIntCount = 0;

// �ӳ�
// �ӳ� time ms ��12MHz�£�
void delay(unsigned int time) {
  unsigned int j = 0;
  for (; time > 0; time--)
    for (j = 0; j < 125; j++)
      ;
}

void PrintTime() {
  delay(10);  //��Ҫ�����̻߳�������ʱ�������ڷ��滷�����޷��������
  P3 = 0x01;
  P2 = led_mod[ctime % 10];
  delay(10);
  P3 = 0x02;
  P2 = led_mod[ctime / 10];
}

timer0() interrupt 1 {
  TH0 = 0x3c;  // ��ֵΪ 15536
  TL0 = 0xb0;
  timerIntCount++;
}

void main() {
  TMOD = 0x01;
  TH0 = 0x3c;  // ��ֵΪ 15536  ��ʱ 50ms��12MHz�£�
  TL0 = 0xb0;
  EA = 1;
  ET0 = 1;
  TR0 = 1;
  PrintTime();
  while (1) {
    if (timerIntCount >=
        20) {  // 20*50ms==1s  ���ַ���������ܷ����ʱ��������������ʱ��ʱ��
      timerIntCount = 0;
      ctime = (ctime + 1) % 60;
    }
    PrintTime();
  }
}
