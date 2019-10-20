/**
 * Copyright (C) 电子1172-杨子棵 ID：201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * 单片机作业
 */
#include <reg51.h>

// LED显示子模，因为题目要求后面的LED数字循环是从1开始，故删去1的字模
char led_mod[] = {0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f,
                  0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71};
sbit D1 = P0 ^ 4;
unsigned char led_num = 0;        //存放LED的数值
key0() interrupt 0 { D1 = !D1; }  // D1的状态取反
key1() interrupt 2 {
  P2 = led_mod[led_num];
  led_num = (led_num + 1) % 15;  //自增并限定范围
}
void main() {
  TCON = 0X05;
  D1 = 1;
  P2 = 0x3f;  //最开始置0（题目无要求）
  IE = 0X85;
  while (1)
    ;
}
