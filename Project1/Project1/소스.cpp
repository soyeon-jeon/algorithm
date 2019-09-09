int min3(int a, int b, int c)
{
	int min = a;
	if (b < min) min = b;
	if (c < min) min = c;
	return min;
}

int main(void)
{
	printf("min(%d,%d,%d = %d\n", 3, 2, 1, min3(3, 2, 1));
	return 0;
}


