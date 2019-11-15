/*
�ۼ���: ����� 20186274
�ۼ���: 18.12.12
*/

#include <stdio.h>
#include <conio.h>
#include "calendar.h"
#include "schedule.h"
#define MAX_SCD_NUM 10000
#pragma warning(disable:4996)

int main() {
	scd s[MAX_SCD_NUM];					// �������� ������ �迭
	yearmonth ym;						// ���� �ܼ��� �⵵�� ���� ������ ����
	char c = 0;						
	s->num = 0;							// num���� �� �������� ������ ������

	load(s);							// ������ ���� �ҷ�����

	ym = calendar(CURRENT_TIME, s);		// ����ð��� �޷��� �ֿܼ� ���, ym�� �ܼ��� �⵵,�� ����

	while (1) {							
		c = getch();					// Ű���� �Է� �޾Ƽ� c�� ����

		switch (c) {
		case ESC:						// ESCŰ ������ ��	
			save(s);					// ������ ���� �� ����
			return 0;

		case LEFT:						// ����Ű ������ ��
			ym = calendar(PRE_MONTH, s);// ����ð��� ���� �� �޷��� �ֿܼ� ���
			break;

		case RIGHT:						// ����Ű ������ ��
			ym = calendar(NEXT_MONTH, s); // ����ð��� ���� �� �޷��� �ֿܼ� ���
			break;

		case DOWN:						// �Ʒ�Ű ������ ��
			ym = calendar(PRE_YEAR, s);	// ����ð��� ���� �⵵ �޷��� �ֿܼ� ���
			break;

		case UP:						// ��Ű ������ ��
			ym = calendar(NEXT_YEAR, s);// ����ð��� ���� �⵵ �޷��� �ֿܼ� ���
			break;

		case 'A':						// AŰ ������ ��
			addscd(s, ym);				// ������ �߰�
			sort(s);					// ����
			ym = calendar(NO_CHANGE, s);
			break;

		case 'D':						// DŰ ������ ��
			del(s);						// ������ ����
			ym = calendar(NO_CHANGE, s);
			break;

		case 'T':						// TŰ ������ ��
			ym = calendar(CURRENT_TIME, s);
			break;
		}
	}
}