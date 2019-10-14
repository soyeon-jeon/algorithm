#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <io.h>
#define MyScore 'A' ///Reality
char c[27] = "mode con: cols=   lines=  ";          ///Window Size
int a; ///number of line
int** plt; ///Player location table
int** llt; ///Laser location table
int* vert; ///Vertical Laser Line
int* horz; ///Horizontal Laser Line
short px, py; ///Aiming-Past x,Past y
double brd[6][2]; ///Best Record
void gotoxy(short x, short y) {                     ///move Cursor
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { x, y });
}
void color(short bgc, short fc) {                   ///Set Color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bgc * 16 + fc);
}
void AvoidLaser() { ///Start Set
	plt = (int**)malloc(sizeof(int*)*a);
	llt = (int**)malloc(sizeof(int*)*a);
	vert = (int*)malloc(sizeof(int)*a);
	horz = (int*)malloc(sizeof(int)*a);
	int cols = a * 2 + 8, lines = a + 4;
	for (int i = 0; i < a; i++) {
		plt[i] = (int*)malloc(sizeof(int)*a);
		llt[i] = (int*)malloc(sizeof(int)*a);
	}
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < a; j++) {
			llt[i][j] = plt[i][j] = 0;
		}
	}
	c[16] = cols % 10 + 0x30;
	c[15] = cols / 10 + 0x30;
	c[25] = lines % 10 + 0x30;
	c[24] = lines / 10 + 0x30;
	const char* garpointer = c;
	system(garpointer);
}
void frame(int _x = 0, int _y = 0) {                     ///Print frame
	for (int i = 0; i < a + 2; i++) {
		for (int j = 1; a + 1 - i && j <= a; j++) {
			gotoxy(i * 2 + _x, j + _y);
			color((i + j) % 2 * 15, 0);
			printf("　");
		}
		color(7, 0);
		gotoxy(0 + _x, i + _y);
		printf("　");
		gotoxy(2 * a + 2 + _x, i + _y);
		printf("　");
		gotoxy(i * 2 + _x, 0 + _y);
		printf("　");
		gotoxy(i * 2 + _x, a + 1 + _y);
		printf("　");
	}
	color(0, 9);
	gotoxy((a + 1) / 2 * 2 + _x, (a + 1) / 2 + _y);
	printf("★");
}
void ppos(short x, short y, int del = 0, int clr = 9) { ///Painting Position
	if (llt[x - 1][y - 1] & plt[x - 1][y - 1]) {
		if (del) {
			plt[x - 1][y - 1] = 0;
			gotoxy(x * 2, y);
			color(12, 0);
			printf("  ");
			return;
		}
		plt[x - 1][y - 1] = 1;
		gotoxy(x * 2, y);
		color(12, clr);
		printf("★");
		return;
	}
	if (del) {
		plt[x - 1][y - 1] = 0;
		gotoxy(x * 2, y);
		color((x + y) % 2 * 15, !((x + y) % 2) * 15);
		printf("　");
		return;
	}
	plt[x - 1][y - 1] = 1;
	gotoxy(x * 2, y);
	color((x + y) % 2 * 15, clr);
	printf("★");
}
int ltime(int l, int limit) {                       ///Laser Time
	if (l == 40) {
		if (limit > (a - 1) * 5 / 4 + 1) limit = (a - 1) * 5 / 4 + 1;
		int ver = limit / 2, hor = limit - ver;
		for (int i = 0; i < a; i++)vert[i] = horz[i] = 0;
		int wline;
		for (int i = 0; i < ver; i++) {
		verticalReIn:
			wline = (int)((double)rand() / (RAND_MAX + 1)*a);
			if (vert[wline] == 1)goto verticalReIn;
			vert[wline] = 1;
			gotoxy(wline * 2 + 2, 0);
			color(7, 12);
			printf("▼");
			gotoxy(wline * 2 + 2, a + 1);
			printf("▲");
		}
		for (int j = 0; j < hor; j++) {
		horizinalReIn:
			wline = (int)((double)rand() / (RAND_MAX + 1) * a);
			if (horz[wline] == 1)goto horizinalReIn;
			horz[wline] = 1;
			gotoxy(0, wline + 1);
			color(7, 12);
			printf("▶");
			gotoxy(a * 2 + 2, wline + 1);
			printf("◀");
		}
	}
	if (l == 80 && printf("\a")) {
		for (int i = 0; i < a; i++) {
			if (vert[i])for (int j = 0; j < a; j++) llt[i][j] = 1;
		}
		for (int j = 0; j < a; j++) {
			if (horz[j])for (int i = 0; i < a; i++)llt[i][j] = 1;
		}
		for (int i = 0; i < a; i++)
			for (int j = 0; j < a; j++) {
				if (llt[i][j] == 1) {
					gotoxy(i * 2 + 2, j + 1);
					color(12, 0);
					if ((vert[i] | horz[j]) == 0) {
						color(14, 0);
					}
					printf("　");
				}
			}
		for (int i = 0; i < a + 2; i++) {
			color(7, 0);
			gotoxy(0, i);
			printf("　");
			gotoxy(2 * a + 2, i);
			printf("　");
			gotoxy(i * 2, 0);
			printf("　");
			gotoxy(i * 2, a + 1);
			printf("　");
		}
		return 0;
	}
	return l + 1;
}
void aiming(int l, short x, short y) {                ///Aiming Mode Laser
	if (l == 20) {
		color(0, 0);
		gotoxy(a * 2 + 4, a + 2);
		printf("　　");
		gotoxy(a * 2 + 4, a + 3);
		printf("　　");
		if ((!(vert[px - 1] || horz[py - 1]))) {
			llt[px - 1][py - 1] = 0;
			ppos(px, py, 1);
		}
	}
	if (l == 60) {
		color(14, 0);
		gotoxy(a * 2 + 4, a + 2);
		printf("　　");
		gotoxy(a * 2 + 4, a + 3);
		printf("　　");
		px = x;
		py = y;
	}
	if (l == 80) {
		color(14, 0);
		gotoxy(px * 2, py);
		printf("　");
		llt[px - 1][py - 1] = 1;
		color(12, 0);
		gotoxy(a * 2 + 4, a + 2);
		printf("　　");
		gotoxy(a * 2 + 4, a + 3);
		printf("　　");
		return;
	}
}
int avla(int anum, int n) { ///Avoid Laser Game!
	AvoidLaser();
	int limit = 1;
	int shootcount = 0;
	srand(GetTickCount());
	int lcount = 0;
	int x = (a + 1) / 2, y = (a + 1) / 2;
	frame(x, y);
	ppos(x, y);
	px = x; py = y;
	gotoxy(0, 20);
	int flg = 2;
	while (1) {
		double gap = (double)clock() / CLOCKS_PER_SEC;
		if (kbhit()) {
			char dir = _getch();
			if (flg&&dir == -32 && (dir = _getch())) {
				ppos(x, y, 1);
				if (dir == 72 && y > 1 && flg)y--;
				else if (dir == 75 && x > 1 && flg)x--;
				else if (dir == 77 && x < a&&flg)x++;
				else if (dir == 80 && y < a&&flg)y++;
				flg = 1;
				ppos(x, y);
			}
			else if (flg - 1 && (dir == 0x44 || dir == 0x64) && x < a) { ppos(x, y, 1); ppos(++x, y); flg = 0; }
			else if (flg - 1 && (dir == 0x41 || dir == 0x61) && x > 1) { ppos(x, y, 1); ppos(--x, y); flg = 0; }
			else if (flg - 1 && (dir == 0x57 || dir == 0x77) && y > 1) { ppos(x, y, 1); ppos(x, --y); flg = 0; }
			else if (flg - 1 && (dir == 0x53 || dir == 0x73) && y < a) { ppos(x, y, 1); ppos(x, ++y); flg = 0; }
		}
		Sleep(16);
		if (anum == 1 && limit > 1)
			aiming(lcount, x, y);
		lcount = ltime(lcount, limit);
		if (lcount == 40) {
			for (int i = 0; i < a; i++)
				for (int j = 0; j < a; j++) {
					llt[i][j] = 0;
					ppos(i + 1, j + 1, 1);
				}
			if (limit == shootcount) {
				limit++; shootcount = 0;
			}
			ppos(x, y);
			shootcount++;
		}
		gap = (double)clock() / CLOCKS_PER_SEC - gap;
		if (gap > 0.2)return 1;
		if (llt[x - 1][y - 1] & plt[x - 1][y - 1]) {
			ppos(x, y);
			break;
		}
	}
	for (int i = 0; i < 9; i++) {
		Sleep(50);
		ppos(x, y, 0, i);
	}
	for (int i = 15; i > 9; i--) {
		Sleep(50);
		ppos(x, y, 0, i);
	}
	Sleep(50);
	ppos(x, y, 1);
	gotoxy(0, 15);
	color(0, 15);
	return 0;
}
void visualCursor(int n) { ///Hide Cursor
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 10;
	cursorInfo.bVisible = n;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void inputSize(int* size) { ///Get Table Size
	gotoxy(0, 0);
	printf("If press 0, game offed\n 판의 크기 입력(7~12)\n");
	*size = 10;
	char *str[6] = { "７","８","９","10","11","12" };
	while (1) {
		for (int i = 0; i < 6; i++) {
			color(0, 15);
			if (i + 7 == *size)color(15, 0);
			gotoxy(i * 7 % 21 + 1, 2 + i / 3 * 3);
			printf("┌─┐");
			gotoxy(i * 7 % 21 + 1, 3 + i / 3 * 3);
			printf("│%s│", str[i]);
			gotoxy(i * 7 % 21 + 1, 4 + i / 3 * 3);
			printf("└─┘");
		}
		a = *size;
		frame(34 - (a + 1) / 2 * 2, 14 - (a + 1) / 2);
		char dir = _getch();
		for (int i = 8; i < 22; i++) {
			color(0, 15);
			gotoxy(22, i);
			printf("　　　　　　　　　　　　　　");
		}
		if (dir == -32) {
			dir = _getch();
			if (dir == 75)(*size)--;
			else if (dir == 77)(*size)++;
			else if (dir == 72)*size += 3;
			else if (dir == 80)*size -= 3;
		}
		else if (dir == 0x44 || dir == 0x64)(*size)++;
		else if (dir == 0x41 || dir == 0x61)(*size)--;
		else if (dir == 0x57 || dir == 0x77)*size += 3;
		else if (dir == 0x53 || dir == 0x73)*size -= 3;
		else if (dir == 0x37)*size = 7;
		else if (dir == 0x38)*size = 8;
		else if (dir == 0x39)*size = 9;
		else if (dir == 0x34)*size = 10;
		else if (dir == 0x35)*size = 11;
		else if (dir == 0x36)*size = 12;
		else if (dir == 48) { *size = 0; break; }
		else if (dir == 13 || dir == 10)
			break;
		if (*size < 7)*size += 6;
		else if (*size > 12)*size -= 6;
	}
	color(0, 7);
	system("cls");
}
void inputMode(int* mode) { ///Get Game Mode
	char *str[2] = { "1.classic mode","2.aiming mode" };
	*mode = 1;
	int i;
	color(0, 7);
	gotoxy(0, 0);
	printf("Back Space : Prev Set\n\n\n\n\n원하는 모드 선택");
	frame(34 - (a + 1) / 2 * 2, 14 - (a + 1) / 2);
	color(12, 0);
	for (int i = 1; i <= a; i++) {
		gotoxy(32, 14 - (a + 1) / 2 + i); printf("　");
		gotoxy(30, 14 - (a + 1) / 2 + i); printf("　");
		gotoxy(36, 14 - (a + 1) / 2 + i); printf("　");
		gotoxy(40, 14 - (a + 1) / 2 + i); printf("　");
		if (a > 8) {
			gotoxy(26, 14 - (a + 1) / 2 + i); printf("　");
			gotoxy(34 - (a + 1) / 2 * 2 + i * 2, 10); printf("　");
		}
		if (a > 9) {
			gotoxy(44, 14 - (a + 1) / 2 + i); printf("　");
		}
		if (a > 11) {
			gotoxy(42, 14 - (a + 1) / 2 + i); printf("　");
		}
		gotoxy(34 - (a + 1) / 2 * 2 + i * 2, 13); printf("　");
		gotoxy(34 - (a + 1) / 2 * 2 + i * 2, 11); printf("　");
		gotoxy(34 - (a + 1) / 2 * 2 + i * 2, 15); printf("　");
		gotoxy(34 - (a + 1) / 2 * 2 + i * 2, 16); printf("　");
		if (a > 7) {
			gotoxy(34 - (a + 1) / 2 * 2 + i * 2, 18); printf("　");
		}
		if (a > 10) {
			gotoxy(34 - (a + 1) / 2 * 2 + i * 2, 19); printf("　");
		}
	}
	while (1) {
		for (i = 1; i <= 2; i++) {
			color(0, 15);
			if (*mode == i)color(15, 0);
			gotoxy(0, i * 2);
			printf(str[i - 1]);
		}
		if (*mode == 1) {
			color(0, 0);
			gotoxy(38 + a / 2 * 2, 16 + a / 2);
			printf("　　");
			gotoxy(38 + a / 2 * 2, 17 + a / 2);
			printf("　　");
			gotoxy(34, 12);
			printf("　");
		}
		if (*mode == 2) {
			color(12, 0);
			gotoxy(38 + a / 2 * 2, 16 + a / 2);
			printf("　　");
			gotoxy(38 + a / 2 * 2, 17 + a / 2);
			printf("　　");
			color(14, 0);
			gotoxy(34, 12);
			printf("　");
		}
		char dir = _getch();
		if (dir == -32) {
			dir = _getch();
			if (dir == 72)(*mode)--;
			else if (dir == 80)(*mode)++;
		}
		else if (dir == 0x57 || dir == 0x77)(*mode)--;
		else if (dir == 0x53 || dir == 0x73)(*mode)++;
		else if (dir == 8) { *mode = 0; break; }
		else if (dir == 0x31) { *mode = 1; break; }
		else if (dir == 0x32) { *mode = 2; break; }
		else if (dir == 13 || dir == 10)break;
		if (*mode > 2)*mode -= 2;
		if (*mode < 1)*mode += 2;
	}
	color(0, 7);
	system("cls");
}
int input(int* size, int *mode) {                     ///Get Size&Mode
nottosize:
	system("mode con: cols=54 lines=24");
	inputSize(size);
	if (*size == 0) { system("mode con: cols=26 lines=2"); return *size; }
	system("mode con: cols=54 lines=24");
thereisnotmodescode:
	inputMode(mode);
	if (*mode == 0)
		goto nottosize;
	return *size;
}
void specialEffect(int i, int y, char* str) {          ///Flash Effect
	Sleep(25);
	color(15 - i, i);
	gotoxy(0, y);
	printf(str);
}
void checkFile() { ///Found Save File
	FILE *record;
	if (_access("C:\\AvoidLaser", 0) == -1)
		mkdir("C:\\AvoidLaser");
	if (_access("C:\\AvoidLaser\\avoiding Laser.txt", 0) == -1) {
		record = fopen("C:\\AvoidLaser\\avoiding Laser.txt", "w");
		for (int i = 0; i < 6; i++)
			fprintf(record, "0.000\t\t0.000\n");
		fclose(record);
	}
}
void getBestRecord() { ///Get Best Record to Save File
	FILE *record;
	record = fopen("C:\\AvoidLaser\\avoiding Laser.txt", "r");
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 2; j++)
			fscanf(record, "%lf", &brd[i][j]);
	}
	fclose(record);
}
void setBestRecord(int size, int mode, double gap) {   ///Set Best Record to Game Result
	FILE *record;
	system("mode con: cols=26 lines=5");
	color(0, 7);
	char *modename[2] = { "Classic mode","Aiming mode" };
	if (gap > brd[size - 7][mode - 1]) { color(0, 14); printf("%15s record\n        in %d lines\n     New      Record!\n", modename[mode - 1], size, brd[size - 7][mode - 1] = gap); }
	else printf("%15s record\n        in %d lines\n\n", modename[mode - 1], size);
	printf("Best Record : %.3lf sec\nYour Record : %.3lf sec", brd[size - 7][mode - 1], gap);
	record = fopen("C:\\AvoidLaser\\avoiding Laser.txt", "w");
	for (int i = 0; i < 6; i++)
		fprintf(record, "%.3lf\t\t%.3lf\n", brd[i][0], brd[i][1]);
	fclose(record);
	system("pause>>NULL");
}
void catchbug() { ///Catch Player Use Bug
	system("mode con: cols=16 lines=2");
	printf("\a");
	int j = 2;
	while (j--) {
		for (int i = 0; i < 9; i++)
			specialEffect(i, 0, "Don't Use Bug XD\nDon't Use Bug XD");
		for (int i = 14; i > 8; i--)
			specialEffect(i, 0, "Don't Use Bug XD\nDon't Use Bug XD");
	}
	specialEffect(15, 0, "Don't Use Bug XD\nDon't Use Bug XD");
	Sleep(2000);
	specialEffect(15, 0, "Press Any Key :D\nReturn To Game!!");
	system("pause>>NULL");
}
int main() { ///Main
	system("title 레이저 피하기");
	checkFile();                //Check File
	double gap;                 //Record(Time)
	visualCursor(0);            //Hide Cursor
	while (1) {                   //Repeat Game
		getBestRecord();        //Get Best Record
		system("cls");          //When repeat clean the Screen
		color(0, 7);             //Set Color Gray
		int size, mode;          //Table Size, Game Mode
		if (!input(&size, &mode))break;    //Get Table Size and Game Mode
		gap = (double)clock() / CLOCKS_PER_SEC; //Set Starting Time
		if (avla(mode - 1, size)) {              //If player used Bug
			catchbug();                     //Show the Bug massage
			continue;                       //Not Save the Record
		}
		gap = (double)clock() / CLOCKS_PER_SEC - gap; //Get Survive Time
		gotoxy(0, size + 3);                   //GotoBottom
		int j = 2; //Repeat
		while (j--) { //Special effect : Press Any Key
			for (int i = 0; i < 9; i++)
				specialEffect(i, size + 3, "Press Any Key");
			for (int i = 14; i > 8; i--)
				specialEffect(i, size + 3, "Press Any Key");
		}
		specialEffect(15, size + 3, "Press Any Key");
		system("pause>>NULL");              //pause
		setBestRecord(size, mode, gap);       //Show and Set Best Record
	}
	return 0;