/**
 * Copyright (C) 电子1172-杨子棵 ID：201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * 单片机作业
 */
#include <reg51.h>

#define true 1

sbit P3_7 = P3 ^ 7;
//查表法显示数字
unsigned char code table[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66,
                              0x6d, 0x7d, 0x07, 0x7f, 0x6f};
//当前的计数值
unsigned char count;

// 延迟
// 延迟 time ms （12MHz下）
void delay(unsigned int time) {
  unsigned int j = 0;
  for (; time > 0; time--)
    for (j = 0; j < 125; j++)
      ;
}

void main(void) {
  count = 0;
  P0 = table[count / 10];
  P2 = table[count % 10];
  while (true) {
    //检测按键按下
    if (!P3_7) {
      delay(10);//延时10ms放抖动
      if (!P3_7) {
        count++;//计数
        if (count == 100) count = 0;
        P0 = table[count / 10];//显示十位
        P2 = table[count % 10];//显示个位
        while (!P3_7)
          ;
      }
    }
  }
}
