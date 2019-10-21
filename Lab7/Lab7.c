/**
 * Copyright (C) 电子1172-杨子棵 ID：201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * 单片机作业
 */
#include <reg51.h>

// LED显示子模
char led_mod[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

char counter = 0;

char timerCount = 0;
timer() interrupt 1 {  //在仿真软件下，启动前一段时间会出现运行缓慢的情况
  timerCount++;
  if (timerCount >= 10) {
    timerCount = 0;
    TR0 = 0;  //一次性计时
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
      TR0 = 1;  //发送接收完数据，启动计时器，等待500ms再发送下一个数据
    } else
      SBUF = counter;  //发送失败则马上重传（不考虑通信拥塞情况）
  }
}

void main() {
  TMOD = 0x21;
  TH1 = TL1 = 0xf4;
  TH0 = 0x3c;  // 初值为 15536  计时 50ms（12MHz下）
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
