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

	printf("정수를 입력하세요：");
	scanf_s("%d", &x);
	printf("%d의 factorial은 %d입니다.\n", x, factorial(x));

	return 0;
}


