#include <stdio.h>


int str_len(const char *s)
{
	int len = 0;
	while (s[len])
		len++;
	return len;

}

int main(void)
{
	char str[256];
	printf("���ڿ� : ");
	scanf_s("%s", str);
	printf("�� ���ڿ��� ���̴� %d�Դϴ�. \n ", str_len(str));

	return 0;
}