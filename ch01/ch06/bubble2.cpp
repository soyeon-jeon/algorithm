#include <stdio.h>
#include <stdlib.h>
#define swap(type, x, y) do { type t = x; x = y; y = t; } while (0)


void bubble(int a[], int n)
{
	int i, j;

	for (i = 0; i < n - 1; i++) {
		int i, j;
		for (i = 0; i < n - 1; i++) {
			int exchg = 0;
				for(j = n-1; j>i; j--)
					if (a[j - 1] > a[j]) {
						swap(int, a[j-1], a[j]);
							exchg++;
					}
			if(exchg == 0) break;
		}
	}


