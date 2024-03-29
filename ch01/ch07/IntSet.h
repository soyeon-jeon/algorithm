#ifndef ___IntSet
#define ___IntSet


typedef struct {
	int max;
	int num;
	int *set;

} IntSet;


int Initialize(IntSet *s, int max);

int IsMember(const IntSet *s, int n);

void Add(InstSet *s, int n);

void Remove(IntSet *s. int n);

int Capacity(const IntSet *s);


int Size(const IntSet *s);

void Assign(IntSet *s1, const IntSet *s2);

int Equal(const IntSet *s1, const IntSet *s2);

IntSet *Union(IntSet *s1, const IntSet *s2, const IntSet *s3);

IntSet *Diffrence(IntSet *s1, const IntSet *s2, const IntSet *s3);

void Print(const IntSet *s);

void PrintLN(const IntSet *s);

void Terminate(IntSet *s);
#endif
