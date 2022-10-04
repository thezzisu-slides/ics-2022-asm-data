#include <stdio.h>
#include <math.h>

void print(float y)
{
  printf("%f\n", y);
}

void move_ins(float *p)
{
  register float y asm("xmm0") = 1.0, z asm("xmm1");
  z = *p;
  *p = y;
  y = z;
  print(y);
}

void arg_mapping(int a, float b, long long c, double d)
{
  printf("%d %f %lld %lf", a, b, c, d);
}

float fmul(register float a, register float b)
{
  return a * b + 1.0;
}

int main()
{
  register double x = 1.0;
  register double y = 2.0;
  register double z;
  z = x + y;
  printf("z = %f", z);
  z = x - y;
  printf("z = %f", z);
  z = x * y;
  printf("z = %f", z);
  z = x / y;
  printf("z = %f", z);
  z = sqrt(x);
  printf("z = %f", z);
  z = fmax(x, y);
  printf("z = %f", z);
  z = fmin(x, y);
  printf("z = %f", z);
  return 0;
}