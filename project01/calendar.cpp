#include "calendar.h"
#include "screen.h"
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)

yearmonth calendar(int keyflag, scd *s) {

	time_t curr_t;
	yearmonth ym;
	struct tm *curr_time;
	static int year, month, nowyear,nowmonth,nowday;
	int DayofMonth, day1, key = 0;
	const char *monthname[] = { "","January","February","March","April","May",
		"June","July","August","September","October","November","December" };

	system("cls");

	if (keyflag == CURRENT_TIME)
	{
		time(&curr_t);
		curr_time = localtime(&curr_t);
		year = curr_time->tm_year + 1900;
		month = curr_time->tm_mon + 1;

		nowyear = year;
		nowmonth = month;
		nowday = curr_time->tm_mday;
	}
	else
	{
		switch (keyflag)
		{
		case 1:
			month--;
			if (month == 0) {
				month = 12;
				year--;
			}

			break;

		case 2:
			month++;
			if (month == 13) {
				month = 1;
				year++;
			}
			break;

		case 3:
			year--;
			break;

		case 4:
			year++;
			break;

		default:
			break;
		}
	}

	DayofMonth = calcDayofMonth(year, month);
	day1 = calcday(year, month, 1);
	
	gotoxy((consolx() - 12) / 2, gety());
	printf("%d %s\n\n", year, monthname[month]);
	gotoxy((consolx() - 33) / 2, gety());
	printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

	gotoxy((consolx() - 33) / 2, gety());
	for (int i = 0; i < day1; i++) {
		printf("     ");
	}
	for (int i = 1; i <= DayofMonth; i++) {
		for (int j = 1; j <= s->num; j++)
		{
			if (s[j].year == year && s[j].month == month && s[j].day == i) {
				red();
				break;
			}
		}

		if (year == nowyear && month == nowmonth && i == nowday) blue();

		printf("%3d  ", i);
		white();
		if (7 - day1 == i % 7 || (i % 7 == 0) && day1 == 0) {
			printf("\n");
			gotoxy((consolx() - 33) / 2, gety());
		}

	}

	gotoxy((consolx() - 8) / 2, 11);
	printf("Schedule\n\n");



	if (s->num == 0) {
		gotoxy((consolx() - 13) / 2, gety());
		printf("[No Schedule]");
	}
	else {
		for (int i = 1; i <= s->num; i++)
		{
			if (s[i].year == year && s[i].month == month)	red();
			if(s[i].year == nowyear && s[i].month == nowmonth && s[i].day== nowday) blue();
			
			printf("				%d. %d.%02d.%02d %cM %02d:%02d - %s\n", i, s[i].year, s[i].month, s[i].day,
				s[i].hour > 11 ? 'P' : 'A', s[i].hour > 12 ? s[i].hour - 12 : s[i].hour,
				s[i].min, s[i].text);
			white();
		}
	}

	gotoxy((consolx() - 72) / 2, gety() + 2);
	printf("[ A: add a schedule, D: delete a schedule, T: move to today	        ]\n");
	gotoxy((consolx() - 72) / 2, gety());
	printf("[ LEFT:month--, RIGHT : month++, DOWN : year--, UP : year++, ESC : exit ]");
	
	ym.year = year;
	ym.month = month;

	return ym;
}

int calcday(int y, int m, int q)
{
	if (m < 3) {
		y -= 1;
		m += 12;
	}

	return (q + (26 * (m + 1)) / 10 + y + y / 4 + 6 * (y / 100) + y / 400 + 6) % 7;
}

int calcDayofMonth(int year, int month) {
	int DayofMonth;

	if (month == 2)
	{
		if (year % 4 == 0)	DayofMonth = 29;
		if (year % 100 == 0)	DayofMonth = 28;
		if (year % 400 == 0)		DayofMonth = 29;
		else DayofMonth = 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)	DayofMonth = 30;
	else DayofMonth = 31;

	return DayofMonth;
}