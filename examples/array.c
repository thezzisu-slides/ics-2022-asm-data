#include <stdio.h>
#include <math.h>

void print_two_ptrs(void *p, void *q)
{
  printf("%p %p", p, q);
}

void two_d_array_fake_deref()
{
  int a[2][2];
  register int **p = a;
  register int *q = *a;
  print_two_ptrs(p, q);
}

void multi_level_array()
{
  int a1[2], a2[2];
  int *a[2] = {a1, a2};
  register int **p = a;
  register int *q = *a;
  print_two_ptrs(p, q);
}

int main()
{
  // two_d_array_fake_deref();
  multi_level_array();
}