/**
 * Copyright (C) 电子1172-杨子棵 ID：201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * 单片机作业
 * 总共有4种样式，通过按按钮可改变样式
 */
#include <reg51.h>

#define true 1

sbit P3_7 = P3 ^ 7;
unsigned char count;

/* 带有软件方式按键中断的延时
 */
char delay(unsigned int time) {
  unsigned char j = 0;
  for (; time > 0; time--) {
    for (j = 0; j < 125; j++)
      ;
    if (!P3_7) {
      unsigned int k = 0;
      for (; k < 1250; k++)
        ;
      if (!P3_7) {
        return 1;
      }
    }
  }
  return 0;
}

//以下分为四种样式显示函数

unsigned char code style1Code[] = {0x01, 0x02, 0x04, 0x08,
                                   0x10, 0x20, 0x40, 0x80};
// 从上至下，从下至上的流水灯样式
void style1() {
  while (true) {
    char i = 0;
    for (; i < 8; i++) {
      P0 = ~style1Code[i];
      if (delay(500)) return;  //当检测到按键，则将发起中断，终止样式运行
    }
    for (i = 7; i >= 0; i--) {
      P0 = ~style1Code[i];
      if (delay(500)) return;
    }
  }
}

unsigned char code style2Code[] = {0x01, 0x04, 0x10, 0x40,
                                   0x02, 0x08, 0x20, 0x80};
// 从上至下的间隔流水灯显示样式
void style2() {
  while (true) {
    char i = 0;
    for (; i < 8; i++) {
      P0 = ~style2Code[i];
      if (delay(1000)) return;
    }
  }
}

unsigned char code style3Code[] = {0x01, 0x03, 0x07, 0x0f,
                                   0x1f, 0x3f, 0x7f, 0xff};
// 从上至下的瀑布式流水灯样式
void style3() {
  while (true) {
    char i = 0;
    for (; i < 8; i++) {
      P0 = ~style3Code[i];
      if (delay(1000)) return;
    }
  }
}

// 全部灯一亮一灭
void style4() {
  while (true) {
    P0 = 0x00;
    if (delay(1000)) return;
    P0 = 0xff;
    if (delay(1000)) return;
  }
}

void main(void) {
  unsigned char styleCode = 0;
  while (true) {
    switch (styleCode) {  //当产生按键中断时，将跳出样式函数
      case 0:
        style1();
        break;
      case 1:
        style2();
        break;
      case 2:
        style3();
        break;
      case 3:
        style4();
        break;
    }
    styleCode = (styleCode + 1) % 4;  //样式码循环自增
  }
}
