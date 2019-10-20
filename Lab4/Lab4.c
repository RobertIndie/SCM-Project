/**
 * Copyright (C) ����1172-���ӿ� ID��201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * ��Ƭ����ҵ
 */
#include <reg51.h>

// LED��ʾ��ģ
char led_mod[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                  0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71};
sbit D1 = P3 ^ 0;
// ��ʱ
void delay(unsigned int time) {
  unsigned char j = 250;
  for (; time > 0; time--) {
    for (; j > 0; j--)
      ;
  }
}
key0() interrupt 0 {  // K0�жϣ��ַ�0-9ѭ��
  unsigned char i;
  D1 = !IE0;
  for (i = 0; i <= 9; i++) {
    P2 = led_mod[i];
    delay(35000);
  }
  P2 = 0X40;
}
key1() interrupt 2 {  // K1�жϣ��ַ�0-9ѭ��
  unsigned char i;
  for (i = 0; i <= 9; i++) {
    D1 = !IE0;  //���K0�ж�״̬�������״̬
    P1 = led_mod[i];
    delay(35000);
  }
  P1 = 0X40;
}
void main() {
  unsigned char i;
  TCON = 0X05;  //����Ϊ���崥����ʽ
  PX0 = 0;      //�����ж����ȼ���ʹ��INT1�ж�����
  PX1 = 1;
  D1 = 1;
  P1 = P2 = 0X40;
  IE = 0X85;
  while (1) {
    for (i = 0; i <= 9; i++) {
      P0 = led_mod[i];
      delay(35000);
    }
  }
}
