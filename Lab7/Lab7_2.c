/**
 * Copyright (C) 电子1172-杨子棵 ID：201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * 单片机作业
 */
#include <reg51.h>

// LED显示子模
char led_mod[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

char counter = 0;

char recv = 0;

bufio() interrupt 4 {
  if (TI == 1) {
    TI = 0;
    P2 = led_mod[recv];
  }
  if (RI == 1) {
    RI = 0;
    recv = SBUF;
    SBUF = recv;
  }
}

void main() {
  TMOD = 0x20;
  TH1 = TL1 = 0xf4;
  PCON = 0;
  SCON = 0x50;
  TR1 = 1;
  EA = 1;
  ES = 1;
  SBUF = counter;
  while (1)
    ;
}
