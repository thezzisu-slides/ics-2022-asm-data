#include <stdio.h>
#include <math.h>

void print_two_ptrs(void *p, void *q)
{
  printf("%p %p\n", p, q);
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

void array_pass_by_ref(int a[2])
{
  int z = a[0];
  a[0] = a[1];
  a[1] = z;
}

int main()
{
  two_d_array_fake_deref();
  multi_level_array();
  int a[2] = {1, 2};
  array_pass_by_ref(a);
  printf("%d %d", a[0], a[1]);
}