/**
 * Copyright (C) 电子1172-杨子棵 ID：201711611231
 * Project repo: https://github.com/RobertIndie/SCM-Project
 * 单片机作业
 * 代码已严格按照CPPLint(Clang-format)官方风格标准进行组织编排
*/
#include <reg51.h>

#define true 1

sbit P3_7 = P3 ^ 7;
unsigned char code table[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
unsigned char count;

void delay(unsigned int time)
{
    unsigned int j = 0;
    for (; time > 0; time--)
        for (j = 0; j < 125; j++)
            ;
}

void main(void)
{
    count = 0;
    P0 = table[count / 10];
    P2 = table[count % 10];
    while (true)
    {
        if (!P3_7)
        {
            delay(10);
            if (!P3_7)
            {
                count++;
                if (count == 100)
                    count = 0;
                P0 = table[count / 10];
                P2 = table[count % 10];
                while (!P3_7)
                    ;
            }
        }
    }
}
