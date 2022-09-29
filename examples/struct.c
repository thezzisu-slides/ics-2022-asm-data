#include <stdio.h>
#include <math.h>

typedef struct Example
{
  int a;
  char b;
  float c;
} Example;

void print_example(Example e)
{
  printf("a: %d, b: %c, c: %f\n", e.a, e.b, e.c);
}

void struct_layout()
{
  Example e;
  e.a = 1;
  e.b = 'a';
  e.c = 1.0;
  print_example(e);
}

typedef struct Header
{
  char version : 3;
  char compressed : 1;
  char encrypted : 1;
  char reversed : 3;
} Header;

void print_header(Header h)
{
  printf("%x\n", *(unsigned char *)&h);
}

void bit_field()
{
  Header h;
  h.version = 0b001;
  h.compressed = 0b1;
  h.encrypted = 0b0;
  h.reversed = 0b111;
  print_header(h);
}

typedef union float_unsigned_converter
{
  float f;
  unsigned int u;
} float_unsigned_converter;

unsigned convert_float_to_unsigned()
{
  float_unsigned_converter c;
  c.f = 1.0;
  return c.u;
}

int main()
{
  struct_layout();
  bit_field();
  return 0;
}