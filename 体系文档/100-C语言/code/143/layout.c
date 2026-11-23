#include <stdio.h>
#include <stddef.h>

struct A { char c; int i; char c2; };
struct B { int i; char c; char c2; };

#pragma pack(push, 4)
struct P4 { int a; double d; char c; };
#pragma pack(pop)
struct N  { int a; double d; char c; };

#pragma pack(push, 1)
struct P1 { char c; int i; char c2; };
#pragma pack(pop)

int main(void)
{
    printf("A: c@%zu i@%zu c2@%zu sizeof=%zu\n",
           offsetof(struct A, c), offsetof(struct A, i), offsetof(struct A, c2), sizeof(struct A));
    printf("B: i@%zu c@%zu c2@%zu sizeof=%zu\n",
           offsetof(struct B, i), offsetof(struct B, c), offsetof(struct B, c2), sizeof(struct B));
    printf("N (natural): sizeof=%zu\n", sizeof(struct N));
    printf("P4 (pack 4): sizeof=%zu\n", sizeof(struct P4));
    printf("P1 (pack 1): sizeof=%zu\n", sizeof(struct P1));
    return 0;
}
