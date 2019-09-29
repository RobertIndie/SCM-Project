/**
 * Copyright (C) ����1172-���ӿ� ID��201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * ��Ƭ����ҵ
 */
#include <reg51.h>

// LED��ʾ��ģ
char led_mod[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                  0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71};
//�ֲ���ģ
char rkey_buf[] = {0x0e, 0x0d, 0x0b, 0x07};
//��ȡ��������Կα��ķ�����������12byte��ȫ��RAM�������жϴ���
char getKey() {
  char key_scan[] = {0xef, 0xdf, 0xbf, 0x7f};  //��ɨ����
  char i = 0, j = 0;
  for (i = 0; i < 4; i++) {
    P2 = key_scan[i];
    if ((P2 & 0x0f) != 0x0f)   //��ȡP2
      for (j = 0; j < 4; j++)  //ѭ���������ҳ�P2��Ӧ�ľֲ���ֵ
        if (rkey_buf[j] == (P2 & 0x0f)) return i + 4 * j;  //���ؼ�ֵ
  }
  return -1;
}
void main() {
  char key = 0;
  P0 = 0x00;
  while (1) {
    key = getKey();                    //��ȡ����
    if (key != -1) P0 = led_mod[key];  //���ݰ�����ʾ����
  }
}
