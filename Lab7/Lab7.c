/**
 * Copyright (C) ����1172-���ӿ� ID��201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * ��Ƭ����ҵ
 */
#include <reg51.h>

// LED��ʾ��ģ
char led_mod[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

char counter = 0;

char timerCount = 0;
timer() interrupt 1 {  //�ڷ�������£�����ǰһ��ʱ���������л��������
  timerCount++;
  if (timerCount >= 10) {
    timerCount = 0;
    TR0 = 0;  //һ���Լ�ʱ
    SBUF = counter;
  }
}

bufio() interrupt 4 {
  if (TI == 1) {
    TI = 0;
  }
  if (RI == 1) {
    RI = 0;
    if (SBUF == counter) {
      P2 = led_mod[counter];
      counter = (counter + 1) % 10;
      TR0 = 1;  //���ͽ��������ݣ�������ʱ�����ȴ�500ms�ٷ�����һ������
    } else
      SBUF = counter;  //����ʧ���������ش���������ͨ��ӵ�������
  }
}

void main() {
  TMOD = 0x21;
  TH1 = TL1 = 0xf4;
  TH0 = 0x3c;  // ��ֵΪ 15536  ��ʱ 50ms��12MHz�£�
  TL0 = 0xb0;
  PCON = 0;
  SCON = 0x50;
  TR1 = 1;
  EA = 1;
  ES = 1;
  ET0 = 1;
  SBUF = counter;
  while (1)
    ;
}
