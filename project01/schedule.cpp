#include "schedule.h"
#include "screen.h"
#include <stdio.h>
#include <Windows.h>
#pragma warning(disable:4996)

void addscd(scd *s, yearmonth ym) {
	int nowy, buflen, flag = 0;
	char buf[MAX_STR];

	(s->num)++;

	s[s->num].year = ym.year;
	s[s->num].month = ym.month;

	s[s->num].text = (char *)malloc(sizeof(char)*MAX_STR);

	gotoxy((consolx() - 22) / 2, gety()+2);

	printf("### Add a schedule ###\n");

	nowy = gety();
	do {
		flag = 0;
		gotoxy(0, nowy);
		delLine(0);
		printf("\r						Day: ");
		s[s->num].day = getDigit();
	} while (s[s->num].day < 1 || s[s->num].day > calcDayofMonth(ym.year, ym.month));

	nowy = gety();
	do {
		flag = 0;
		gotoxy(0, nowy);
		delLine(0);
		printf("\r						Hour(0~23) : ");
		s[s->num].hour = getDigit();
	} while (s[s->num].hour < 0 || s[s->num].hour > 23);

	nowy = gety();
	do {
		flag = 0;
		gotoxy(0, nowy);
		delLine(0);
		printf("\r						Min(0~59): ");
		s[s->num].min = getDigit();
	} while (s[s->num].min < 0 || s[s->num].min > 59);

	getchar();
	printf("\r						Note: ");
	scanf("%[^\n]", s[s->num].text);
}

void sort(scd *s) {
	int mini = -1, flag = 0;
	scd tmp;

	for (int i = 1; i < s->num; i++)
	{
		if (s[i].year > s[s->num].year)	mini = i;
		else if (s[i].year == s[s->num].year)
		{
			if (s[i].month > s[s->num].month)	mini = i;
			else if (s[i].month == s[s->num].month)
			{
				if (s[i].day > s[s->num].day)	mini = i;
				else if (s[i].day == s[s->num].day)
				{
					if (s[i].hour > s[s->num].hour)	mini = i;
					else if (s[i].hour == s[s->num].hour)
					{
						if (s[i].min > s[s->num].min)	mini = i;
					}
				}
			}
		}

		if (mini == i) {
			flag = 1;
			break;
		}
	}

	if (flag == 1) {
		tmp = s[s->num];

		for (int i = (s->num) - 1; i >= mini; i--)
		{
			s[i + 1] = s[i];
		}

		s[mini] = tmp;
	}
}

void save(scd *s) {
	FILE *f;

	f = fopen("schedule.txt", "w");
	if (!f) {
		printf("File read Error");
		exit(1);
	}

	for (int i = 1; i <= s->num; i++) {
		fprintf(f, "%d/%d/%d/%d/%d/%s\n", s[i].year, s[i].month, s[i].day, s[i].hour, s[i].min, s[i].text);
	}

	fclose(f);
}

void load(scd *s) {
	FILE *f;

	f = fopen("schedule.txt", "a+");
	if (!f) {
		printf("File read Error");
		exit(1);
	}

	char buf[MAX_STR], *ptr;
	int i = 0;

	while (!feof(f)) {
		fgets(buf, MAX_STR, f);
		if (feof(f))	break;

		ptr = strtok(buf, "/");
		s[++i].year = atoi(ptr);
		ptr = strtok(NULL, "/");
		s[i].month = atoi(ptr);
		ptr = strtok(NULL, "/");
		s[i].day = atoi(ptr);
		ptr = strtok(NULL, "/");
		s[i].hour = atoi(ptr);
		ptr = strtok(NULL, "/");
		s[i].min = atoi(ptr);


		s[i].text = (char *)malloc(sizeof(char)*MAX_STR);
		ptr = strtok(NULL, "\n");
		printf("%s", ptr);
		strcpy(s[i].text, ptr);
	}
	s->num = i;

	fclose(f);
}

int del(scd *s) {
	int input;

	system("cls");

	printf(" Schedule\n\n");

	for (int i = 1; i <= (s->num) + 1; i++) {
		if (i != (s->num) + 1) {
			printf("%d. %d. %02d. %02d %cM %02d: %02d - %s\n", i, s[i].year, s[i].month, s[i].day,
				s[i].hour > 12 ? 'P' : 'A', s[i].hour > 12 ? s[i].hour - 12 : s[i].hour,
				s[i].min, s[i].text);
		}
		else printf("%d. Cancel\n\n", i);
	}

	printf("Which schedule do you want to delete? ");
	input = getDigit();

	if (input > (s->num) || input < 1)	return 1;

	for (int i = input; i < s->num; i++) {
		s[i] = s[i + 1];
	}
	(s->num)--;

	printf("Schedule deleted.");

	Sleep(1500);
	
	return 0;
}

int getDigit() {
	char buf[MAX_STR];
	int buflen, flag, nowy, nowx;

	nowx = getx();
	nowy = gety();

	do {
		gotoxy(nowx, nowy);
		delLine(nowx);
		gotoxy(nowx, nowy);
		flag = 0;
		scanf("%s", buf);

		buflen = strlen(buf);

		for (int i = 0; i < buflen; i++) {
			if (!isdigit(buf[i])) {
				flag = 1;
				break;
			}
		}

	} while (flag);

	return atoi(buf);
}