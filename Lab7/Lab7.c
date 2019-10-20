/**
 * Copyright (C) 电子1172-杨子棵 ID：201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * 单片机作业
 */
#include <reg51.h>

// LED显示子模
char led_mod[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

uchar counter = 0;

// 延迟
// 延迟 time ms （12MHz下）
void delay(unsigned int time) {
  unsigned int j = 0;
  for (; time > 0; time--)
    for (j = 0; j < 125; j++)
      ;
}

void PrintTime() {
  delay(10);  //需要延时，否则在仿真环境下无法正常输出
  P3 = 0x01;
  P2 = led_mod[ctime % 10];
  delay(10);
  P3 = 0x02;
  P2 = led_mod[ctime / 10];
}

bufio() interrupt 4 {
  if (TI == 1) {
    TI = 0;
  }
  if (RI == 1) {
    RI = 0;
    if (SBUF == counter) {
      P2 = led_mod[counter];
      if(++counter)
    }
  }
}

void main() {
  TMOD = 0x20;
  TH1 = TL1 = 0xf4;
  PCON = 0;
  SCON = 0x50;
  TR1 = 1;
  while (1) {
    SBUF = counter;
  }
}
