/**
 * Copyright (C) ����1172-���ӿ� ID��201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * ��Ƭ����ҵ
 */
#include <reg51.h>

// LED��ʾ��ģ����Ϊ��ĿҪ������LED����ѭ���Ǵ�1��ʼ����ɾȥ1����ģ
char led_mod[] = {0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f,
                  0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71};
sbit D1 = P0 ^ 4;
unsigned char led_num = 0;        //���LED����ֵ
key0() interrupt 0 { D1 = !D1; }  // D1��״̬ȡ��
key1() interrupt 2 {
  P2 = led_mod[led_num];
  led_num = (led_num + 1) % 15;  //�������޶���Χ
}
void main() {
  TCON = 0X05;
  D1 = 1;
  P2 = 0x3f;  //�ʼ��0����Ŀ��Ҫ��
  IE = 0X85;
  while (1)
    ;
}
