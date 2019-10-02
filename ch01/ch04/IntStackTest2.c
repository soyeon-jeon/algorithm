#include <stdio.h>
#include "IntStack2.h"

int main(void)
{
	IntStack s;

	if (Initialize(&s, 12) == -1) {
		puts("������ ������ �����߽��ϴ�.");
		return 1;
	}

	while (1) {
		int menu, x;
		int idx;

		printf("���� ������ ���� : A:%d B:%d / %d\n", Size(&s, StackA), Size(&s, StackB), Capacity(&s));
		printf("1) A�� Push 2) A���� Pop 3) A���� Peek 4) A�� ��� 5) A���� �˻� 6) A�� �ʱ�ȭ\n"
			"7) B�� Push 8) B���� Pop 9) B���� Peek 10) B�� ��� 11) B���� �˻� 12) B�� �ʱ�ȭ\n"
			"13) �� ���� / ���� �� ���� 0) ���� : ");
		scanf_s("%d", &menu);

		if (menu == 0) break;

		switch (menu) {
		case 1:
			printf("�����ͣ�");
			scanf_s("%d", &x);
			if (Push(&s, StackA, x) == -1)
				puts("\a���� : Ǫ�ÿ� �����߽��ϴ�.");
			break;

		case 2:
			if (Pop(&s, StackA, &x) == -1)
				puts("\a���� : �˿� �����߽��ϴ�.");
			else
				printf("���� �����ʹ� %d�Դϴ�.\n", x);
			break;

		case 3:
			if (Peek(&s, StackA, &x) == -1)
				puts("\a���� : ��ũ�� �����߽��ϴ�.");
			else
				printf("��ũ�� �����ʹ� %d�Դϴ�.\n", x);
			break;

		case 4:
			Print(&s, StackA);
			break;

		case 5:
			printf("�˻� �����ͣ�");
			scanf_s("%d", &x);
			if ((idx = Search(&s, StackA, x)) == -1)
				puts("\a���� : �˻��� �����߽��ϴ�.");
			else
				printf("�����ʹ� �ε��� %d ��ġ�� �ֽ��ϴ�.\n", idx);
			break;

		case 6:
			Clear(&s, StackA);
			break;

		case 7:
			printf("�����ͣ�");
			scanf_s("%d", &x);
			if (Push(&s, StackB, x) == -1)
				puts("\a���� : Ǫ�ÿ� �����߽��ϴ�.");
			break;

		case 8:
			if (Pop(&s, StackB, &x) == -1)
				puts("\a���� : �˿� �����߽��ϴ�.");
			else

				printf("���� �����ʹ� %d�Դϴ�.\n", x);
			break;

		case 9:
			if (Peek(&s, StackB, &x) == -1)
				puts("\a���� : ��ũ�� �����߽��ϴ�.");
			else
				printf("��ũ�� �����ʹ� %d�Դϴ�.\n", x);
			break;

		case 10:
			Print(&s, StackB);
			break;

		case 11:
			printf("�˻� �����ͣ�");
			scanf_s("%d", &x);
			if ((idx = Search(&s, StackB, x)) == -1)
				puts("\a���� : �˻��� �����߽��ϴ�.");
			else
				printf("�����ʹ� �ε��� %d ��ġ�� �ֽ��ϴ�.\n", idx);
			break;

		case 12:
			Clear(&s, StackB);
			break;

		case 13:
			printf("���� A�� ��� %s.\n", IsEmpty(&s, StackA) ? "�ֽ��ϴ�" : "���� �ʽ��ϴ�");
			printf("���� B�� ��� %s.\n", IsEmpty(&s, StackB) ? "�ֽ��ϴ�" : "���� �ʽ��ϴ�");
			printf("������ ���� %s.\n", IsFull(&s) ? "á���ϴ�" : "���� �ʾҽ��ϴ�");
			break;
		}
	}

	Terminate(&s);

	return 0;
}
