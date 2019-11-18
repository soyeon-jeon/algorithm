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
	printf("문자열 : ");
	scanf_s("%s", str);
	printf("이 문자열의 길이는 %d입니다. \n ", str_len(str));

	return 0;
}