#pragma once
#ifndef ___IntQueue
#define ___IntQueue


typpedef struct {
	int max;
	int num;
	int front;
	int rear;
	int *que;
} IntQueue;


int Initialize(IntQueue *q, int max);

int Enque(IntQueue *q, int *x);

int Deque(IntQueue *q, int *x);

int Peek(const IntQueue *q, int *x);

void clear(IntQueue *q);

int Capacity(const IntQueue *q);

int Size(const IntQueue *q);

int InEmpty(const IntQueue *q);

int IsFull(Const IntQueue *q);

int Search(const IntQueue *q, int x);

void Print(const IntQueue *q);

void Terminate(IntQueue *q);
#endif