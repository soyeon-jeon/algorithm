#include  <stdio.h>

int main(void)
{
	int a, b, c;
	int max;
	printf("�� ������ �ִ밪�� ���մϴ�.\n");
	printf("a�� �� : "); scanf_s("%d", &a);
	printf("b�� �� : "); scanf_s("%d", &b);
	printf("c�� �� : "); scanf_s("%d", &c);
	max = a;
	if (b > max) max = b;
	if (c > max) max = c;

	printf("�ִ��� %d�Դϴ�.\n", max);

	return 0;
}