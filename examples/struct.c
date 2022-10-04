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

typedef union different_size
{
  int a;
  long long b;
} different_size;

void test_different_size()
{
  different_size d;
  d.b = 0x1234567821436587;
  printf("%ld %x %llx\n", sizeof(d), d.a, d.b);
}

typedef struct UncleMai
{
  double priceOfKingOldLucky;
  int countOfKingOldLucky;
} UncleMai;

typedef struct BuildingLee
{
  UncleMai store;
  int studentCount;
} BuildingLee;

typedef struct
{
  unsigned bit0 : 1;
  unsigned bit1 : 1;
  unsigned bit2 : 1;
  unsigned bit3 : 1;
  unsigned bit4 : 1;
  unsigned bit5 : 1;
  unsigned bit6 : 1;
  unsigned bit7 : 1;
  unsigned bit8 : 1;
  unsigned bit9 : 1;
  unsigned bit10 : 1;
  unsigned bit11 : 1;
  unsigned bit12 : 1;
  unsigned bit13 : 1;
  unsigned bit14 : 1;
  unsigned bit15 : 1;
  unsigned bit16 : 1;
  unsigned bit17 : 1;
  unsigned bit18 : 1;
  unsigned bit19 : 1;
  unsigned bit20 : 1;
  unsigned bit21 : 1;
  unsigned bit22 : 1;
  unsigned bit23 : 1;
  unsigned bit24 : 1;
  unsigned bit25 : 1;
  unsigned bit26 : 1;
  unsigned bit27 : 1;
  unsigned bit28 : 1;
  unsigned bit29 : 1;
  unsigned bit30 : 1;
  unsigned bit31 : 1;
} ZUnsigned;

typedef union
{
  ZUnsigned bits;
  unsigned value;
} ZUnsignedUnion;

typedef union U1
{
  int i;
  float f;
} U1;

typedef struct S1
{
  U1 u;
  long long ll;
} S1;

void union_in_struct()
{
  S1 s;
  s.u.i = 1;
  s.u.f = 1.0;
  s.ll = 1;
  printf("%ld %x %f %lld\n", sizeof(s), s.u.i, s.u.f, s.ll);
}

typedef union U2
{
  U1 u;
  long long ll;
} U2;

void nested_union()
{
  U2 u2;
  u2.u.f = 1.0;
  printf("%x %f %llx\n", u2.u.i, u2.u.f, u2.ll);
}

int main()
{
  struct_layout();
  bit_field();
  test_different_size();
  printf("%ld %ld\n", sizeof(UncleMai), sizeof(BuildingLee));
  union_in_struct();
  nested_union();
  return 0;
}