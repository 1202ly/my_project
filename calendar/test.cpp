#define _CRT_SECURE_NO_WARNINGS 1
#include "calendar.h"

void main()
{
	int year = 0;
	int month = 0;
	int action = 0;//获取当前年份与月份
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep);
	year = p->tm_year + 1900;//获取本地当前年份
	month = p->tm_mon + 1;//获取本地当前的月份
	while (1)
	{
		printf("\n             \t\t %d 年 %d 月\n\n", year, month);
		PrintCalendar(year, month);
		action = _getch();
		system("cls");//windows清屏
		switch (action)
		{
		case KEY_UP:
			year--;
			break;
		case KEY_DOWN:
			year++;
			break;
		case KEY_LEFT:
			month--;
			if (month < 1)
			{
				month = 12;
			}
			break;
		case KEY_RIGHT:
			month++;
			if (month > 12)
			{
				month = 1;
			}
			break;
		}
	}
}
