#define MAX_STR 1000
#define CURRENT_TIME 0
#define PRE_MONTH 1
#define NEXT_MONTH 2
#define PRE_YEAR 3
#define NEXT_YEAR 4
#define ESC 27
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define UP 72
#define NO_CHANGE 5

#ifndef cal_h
#define cal_h
typedef struct _scd {
	int year;
	int month;
	int day;
	int hour;
	int min;
	int num;
	char *text;
}scd;

typedef struct _yearmonth {
	int year;
	int month;
}yearmonth;

#endif

yearmonth calendar(int flag, scd *s);
int calcday(int y, int m, int q);
int calcDayofMonth(int year, int month);