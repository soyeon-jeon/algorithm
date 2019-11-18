#include <stdio.h>

int str_cmp(const char *s1, const char *s2)
{
	while (*s1 == *s2) {
		if (*s1 == '\0')
			return 0;
		s1++;
		s2++;
	}
	return (unsigned char)*s1 - (unsigned char)*s2;

}

int main(void)
{
	char st[128];
	puts("\"ABCD\"와 비교합니다.");
	puts("\"XXXX\"면 종료합니다.");
	while (1) {
		printf("문자열 st : ");
		scanf_s("%s", st);
		if (str_cmp("XXXX", st) == 0)
			break;
		printf("str_cmp)
	}
}