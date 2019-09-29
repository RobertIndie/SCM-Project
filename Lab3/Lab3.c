/**
 * Copyright (C) 电子1172-杨子棵 ID：201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * 单片机作业
 */
#include <reg51.h>

// LED显示子模
char led_mod[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                  0x7f, 0x6f, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71};
//局部键模
char rkey_buf[] = {0x0e, 0x0d, 0x0b, 0x07};
//获取按键，相对课本的方法，减少了12byte的全局RAM，减少判断次数
char getKey() {
  char key_scan[] = {0xef, 0xdf, 0xbf, 0x7f};  //键扫描码
  char i = 0, j = 0;
  for (i = 0; i < 4; i++) {
    P2 = key_scan[i];
    if ((P2 & 0x0f) != 0x0f)   //获取P2
      for (j = 0; j < 4; j++)  //循环遍历，找出P2对应的局部键值
        if (rkey_buf[j] == (P2 & 0x0f)) return i + 4 * j;  //返回键值
  }
  return -1;
}
void main() {
  char key = 0;
  P0 = 0x00;
  while (1) {
    key = getKey();                    //获取按键
    if (key != -1) P0 = led_mod[key];  //根据按键显示数字
  }
}
