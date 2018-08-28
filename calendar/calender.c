#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

#define KEY_UP 72   //宏定义键盘的键值↑
#define KEY_DOWN 80  //宏定义键盘的键值↓
#define KEY_LEFT 75   //宏定义键盘的键值←
#define KEY_RIGHT 77  //宏定义键盘的键值→
const int isleap(int year);	//判断闰年
const int GetMonthDays(int year, int month);//计算year年month月的天数
const int YearDays(int year);//计算year年的天数
const int isWeek(int year, int month, int day);//计算year年month月day天为星期几
void PrintCalendar(int year, int month);	//打印某年某月的日历
