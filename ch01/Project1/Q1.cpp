#include <stdio.h>



int factorial(int n)
{
	int i = 0;
	int result = 1;
	for (i = n; i > 0; i--)
	{
		result *= i;

	}
	return result;
}


int main(void)
{
	int x;

	printf("������ �Է��ϼ��䣺");
	scanf_s("%d", &x);
	printf("%d�� factorial�� %d�Դϴ�.\n", x, factorial(x));

	return 0;
}


