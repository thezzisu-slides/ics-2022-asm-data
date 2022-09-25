---
routerMode: hash
favicon: https://asset.zisu.dev/svg/logo.svg
theme: seriph
background: ./img/94463658_p0.jpg
class: 'text-center'
highlighter: shiki
lineNumbers: true
info: |
  ## ICS2022 Review for Machine Programs: Data
  Presented by [thezzisu](github.com/thezzisu)
drawings:
  persist: false
css: unocss
---

# ICS2022 Review

Machine Programs: Data

<div class="pt-12">
  <span @click="$slidev.nav.next" class="px-2 py-1 rounded cursor-pointer" hover="bg-white bg-opacity-10">
    Press Space for next page <carbon:arrow-right class="inline"/>
  </span>
</div>

<div class="abs-br m-6 flex gap-2">
  <a href="https://github.com/thezzisu-slides/ics-2022-asm-data" target="_blank" alt="GitHub"
    class="text-xl icon-btn opacity-50 !border-none !hover:text-white">
    <carbon-logo-github />
  </a>
</div>

---

# Overview

Data structures stored in memory, and more

Since the **Float** section is independent of the rest, I will cover it first.

- **Float**
- **Array** - Continuously stored data of the same type
- **Structures**
  - **Struct** - Syntax sugar for continuously stored data of (maybe) different types
  - **Union** - Syntax sugar for type casting
- Combining data and control - **Attack** flawed programs

---
layout: image-right
image: ./img/section-1.jpg
---

<div class="abs-bl m-12">
  <div class="text-2xl font-bold">Section 1</div>
  <h1 class="text-8xl!">Float</h1>
</div>

---

# History: FP Support in x86
Section 1. Float

## 8086
- No floating point hardware
- Software emulation

## 8087 (x87)
- The standard math coprocessor for the 8086 and 8088, operating on 80-bit numbers.

<div class="abs-tr m-6">
 <img src="https://www.mynikko.com/CPU/img/P8088-2-a.jpg" width="280">
 <div class="w-full text-center text-sm">A 8087 chip</div>
</div>

---

# History: FP Support in x86
Section 1. Float

## 80386
- CPU + FPU together on one chip
- Some 80386 chips had FP support while some didn't
- Being used in 'Tomahawk Cruise Missile'

## 80486
- FP support always available

<div class="abs-tr m-6">
 <img src="https://www.mynikko.com/CPU/img/MG80386-a.jpg" width="280">
 <div class="w-full text-center text-sm">A 80386 chip</div>
</div>

---

# History: FP Support in x86
Section 1. Float

## 80386
- CPU + FPU together on one chip
- Some 80386 chips had FP support while some didn't
- Being used in 'Tomahawk Cruise Missile'

## 80486
- FP support always available

<div class="abs-tr m-6">
 <img src="https://www.mynikko.com/CPU/img/MG80386-a.jpg" width="280">
 <div class="w-full text-center text-sm">A 80386 chip</div>
</div>

---

# History: FP Support in x86
Section 1. Float

## The x87 FPU Architecture
- The FPU has 8 general purpose 80-bit (double extended-precision) registers.
- They are labeled st(0), st(1), …, st(7).
- They are organized as a stack, with st(0) on top.
- Typically, floating-point operations pop values off the stack and push results onto the stack.
- Many instructions allow us to access any position in the stack.

See also [this slide](https://slideplayer.com/slide/15539625/).

---

# History: FP Support in x86
Section 1. Float

However, float operations are slow, and most of them are working on a large amount of data.

To speed up the process, **S**ingle **I**nstruction **M**ultiple **D**ata instructions are introduced.

- **M**atrix **M**ath e**X**tensions: introduced by Intel in 1997; Pentium P5.
- **S**treaming **S**IMD **E**xtensions: introduced by Intel in 1999; Pentium III.
- **A**dvanced **V**ector **E**xtensions: introduced by Intel in 2008; Intel Sandy Bridge and AMD Bulldozer.
  - **AVX2**: introduced by Intel in 2013; Intel Haswell.
  - **AVX-512**: introduced by Intel in 2017; Intel Skylake-X.

Our course is using **AVX2**. Using following command to make GCC emit AVX2 instructions:

```sh
gcc float.c -mavx2 -Wall -S
```

Please refer to examples folder for the example code.

<!-- 
AVX-512 expands AVX to 512-bit support using a new EVEX prefix encoding proposed by Intel in July 2013 and first supported by Intel with the Knights Landing co-processor, which shipped in 2016. In conventional processors, AVX-512 was introduced with Skylake server and HEDT processors in 2017.
-->

---
layout: image-left
image: https://web.archive.org/web/20170216110456im_/https://software.intel.com/sites/default/files/37206.gif
---
# AVX2: Basics
Section 1. Float

The hardware supporting Intel® AVX (and FMA) consists of the 16 256-bit YMM registers YMM0-YMM15 and a 32-bit control/status register called MXCSR. The YMM registers are aliased over the older 128-bit XMM registers used for Intel SSE, treating the XMM registers as the lower half of the corresponding YMM register, as shown in the Figure.

<style>
div[layout="image-left"] :first-child {
  background-size: auto !important;
}
</style>

---

# AVX2: Basics
Section 1. Float

This figure illustrates the data types used in the Intel® SSE and Intel® AVX instructions. Roughly, for Intel AVX, any multiple of 32-bit or 64-bit floating-point type that adds to 128 or 256 bits is allowed as well as multiples of any integer type that adds to 128 bits.

![](https://web.archive.org/web/20170216110411im_/https://software.intel.com/sites/default/files/37207.gif)

---

# AVX2: Move and Conversion
Section 1. Float

## Floating-Point Movement and Conversion Operations

| Instruction | Source & Destination | Description |
| --- | --- | --- |
| `vmovss` | Memory <=> XMM | Move **S**calar **S**ingle-Precision Floating-Point Value |
| `vmovsd` | Memory <=> XMM | Move **S**calar **D**ouble-Precision Floating-Point Value |
| `vmovaps` | XMM <=> XMM | Move **A**ligned **P**acked **S**ingle-Precision Floating-Point Values |
| `vmovapd` | XMM <=> XMM | Move **A**ligned **P**acked **D**ouble-Precision Floating-Point Values |

---

# AVX2: Move and Conversion
Section 1. Float

<div class="grid grid-cols-2">
  <div>

```c
void move_ins()
{
  float x;
  float *p = &x; // p in %rax
  register float y, z; // y in %xmm0
  y = *p; // vmovss	(%rax), %xmm0
  *p = y; // vmovss	%xmm0, (%rax)
  y = z;  // vmovaps	%xmm2, %xmm1
}
```

  </div>
  <div>

```asm
move_ins: ; redacted
	subq	$32, %rsp
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-20(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	vmovss	(%rax), %xmm0
	movq	-16(%rbp), %rax
	vmovss	%xmm0, (%rax)
	vmovaps	%xmm2, %xmm1
```

  </div>
</div>

Why `y = z` emits `vmovaps %xmm2, %xmm1`?

---

# AVX2: Code in Procedures
Section 1. Float

## Floating-Point Code in Procedures

With x86-64, the XMM registers are used for passing floating-point arguments to functions and for returning floating-point values from them, with following conventions:
- %xmm0-%xmm7 are used for passing (up to 8) arguments to functions. Additional FP arguments should be passed on the stack.
- %xmm0 is used for returning a floating-point value from a function.
- All XMM registers are caller-saved.

Thus, when a function accepts mixed floating-point and integer/pointer arguments, the mapping of arguments to registers depends on the order in which they are declared in the function prototype.

---

# AVX2: Code in Procedures
Section 1. Float

<div class="grid grid-cols-2">
  <div>

```c
void arg_mapping(int a, float b, long long c, double d)
{
  // a in %edi, b in %xmm0, c in %rsi, d in %xmm1
  printf("%d %f %lld %lf", a, b, c, d);
}
```

FP arguments and INT/PTR arguments are independently mapped to their own registers.

  </div>
  <div>

```asm
arg_mapping:
	subq	$32, %rsp
	movl	%edi, -4(%rbp)
	vmovss	%xmm0, -8(%rbp)
	movq	%rsi, -16(%rbp)
	vmovsd	%xmm1, -24(%rbp)
	vcvtss2sd	-8(%rbp), %xmm0, %xmm0
	vmovsd	-24(%rbp), %xmm1
	movq	-16(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$2, %eax
	call	printf@PLT
```

  </div>
</div>

---

# AVX2: Arithmetic Operations
Section 1. Float

## Floating-Point Arithmetic Operations

Instruction: `(v(add|sub|mul|div|max|min)|sqrt)s(s|d)`.

Operand: `S1 S2 D` or `S1 D` for sqrt.

`S1` can be XMM register or Memory location; `S2` and `D` must be XMM registers.

**Note**: There is **no** immediate values. You should use `vmovss` to load immediate values into XMM register. See the following example for more details.

---

# AVX2: Arithmetic Operations
Section 1. Float

<div class="grid grid-cols-2">
  <div>

```c
float fmul(register float a, register float b)
{
  return a * b + 1.0;
}
```

The constant `1.0` is loaded into XMM register by `vmovss`.

  </div>
  <div>

```asm
.LC1:
	.long	1065353216
	.align 8
fmul:
	pushq	%rbp
	movq	%rsp, %rbp
	vmulss	%xmm1, %xmm0, %xmm1
	vmovss	.LC1(%rip), %xmm0
	vaddss	%xmm0, %xmm1, %xmm0
	popq	%rbp
	ret
```

  </div>
</div>

---

# AVX2: Bitwise Operations
Section 1. Float

## Floating-Point Bitwise Operations

Instruction: `v(xor|and)p(s|d)`.

Operand: `S1 S2 D`, all of them are XMM registers.

- vxorp*: D = S1 ^ S2
- vandp*: D = S1 & S2

These instructions will operate on all 128 bits of the XMM register.

---

# AVX2: Comparison
Section 1. Float

## Floating-Point Comparison

- Instruction: `vucomis(s|d)`.
- Operand: `S1 S2`, both of them are XMM registers.
- These instructions are based on the result of S2 - S1, and will set 3 conditional flags: CF, ZF, PF.

| Order | CF | ZF | PF |
| --- | --- | --- | --- |
| S2 < S1 | 1 | 0 | 0 |
| S2 = S1 | 0 | 1 | 0 |
| S2 > S1 | 0 | 0 | 0 |
| Unordered | 1 | 1 | 1 |

---
layout: image-right
image: ./img/section-2.jpg
---

<div class="abs-bl m-12">
  <div class="text-2xl font-bold">Section 2</div>
  <h1 class="text-8xl!">Array</h1>
</div>

---

# Array: Basics
Section 2. Array

```c
T a[N];
```

- Declare an array of type T with N elements.
- The array is stored in a contiguous memory region, with total size of `N * sizeof(T)`.
- What's the type of `a`?
  - `T [N]` since GCC will attach size information to the type during compilation.
  - Actually it's `T*` (pointer to T)

```
T e = a[i];
```

- We can access array elements using `[]` operator.
- For C arrays, `[]` is a syntactic sugar for pointer arithmetic:
  - `a[i]` is equivalent to `*(a + (i))`.

---

# Array: Basics
Section 2. Array

Thus, array accessing is simple:
```c
   a[i]
=> *(a + (i))
=> *(T*)((long)a + (i) * sizeof(T))
```
For
```c
int a[4], i = 2; // a in %rdi, i in %esi
int b = a[i];    // b in %eax
```
We get:
```asm
movl (%rdi, %rsi, 4), %eax ; sizeof(int) = 4
```

---

# Array: Nested Array
Section 2. Array

We only need to consider 2d array which is the essential case.

```c
T a[N][M];
```

Is equivalent to:

```c
typedef T row[M]; // This syntax is somehow weird though
row a[N];
```

And `a[i][j]` is equivalent to `(a[i])[j]`. Thus we have:

```c
   a[i][j]
=> (a[i])[j]
=> (*(a + (i)))[j] // Notice this asterisk is not a dereference!
=> *((*(a + (i))) + (j))
=> *(T*)((long)a + (i) * sizeof(row) + (j) * sizeof(T))
=> *(T*)((long)a + ((i) * M + (j)) * sizeof(T))
```

Notice the difference between `T[N][M]` and `T**`. We'll discuss this later.

---

# Array: Nested Array
Section 2. Array

<div class="grid grid-cols-2">
  <div>

```c
void two_d_array_fake_deref() {
  int a[2][2];
  register int **p = a; // leaq	-48(%rbp), %rbx
  register int *q = *a; // leaq	-48(%rbp), %r12
  printf("%p %p", p, q);
}
```

Outputs:

```
0x7ffc820f60d0 0x7ffc820f60d0
```

  </div>
  <div>

```asm
two_d_array_fake_deref:
	subq	$32, %rsp
	leaq	-48(%rbp), %rbx
	leaq	-48(%rbp), %r12
	movq	%r12, %rsi
	movq	%rbx, %rdi
	call	print_two_ptrs
  ret
```

  </div>
</div>

Compiler warning:

```
array.c: In function ‘two_d_array_fake_deref’:
array.c:7:22: warning: initialization of ‘int **’ from incompatible pointer type ‘int (*)[2]’ [-Wincompatible-pointer-types]
    7 |   register int **p = a
```

Do not confuse with **Multi-Level Array**!

---

# Array: Multi-Level Array
Section 2. Array

```c
int a_0[M], a_1[M];
int* a[N] = {a_0, a_1}; // Let's assume N = 2
```

Since `a[i][j]` is equivalent to `(a[i])[j]`:

```c
   a[i][j]
=> (a[i])[j]
=> (*(a + (i)))[j] // Notice this asterisk is a dereference!
=> *((*(a + (i))) + (j)) // We have 2 dereferences in total!
```

In fact, `a` can hold arrays of **different sizes** because `a[i]` is just a pointer to `int`.

---

# Array: Multi-Level Array
Section 2. Array

<div class="grid grid-cols-2">
  <div>

```c
void multi_level_array() {
  int a1[2], a2[2];
  int *a[2] = {a1, a2};
  register int **p = a;
  register int *q = *a;
  printf("%p %p", p, q);
}
```

Outputs:

```
0x7ffd4663fa90 0x7ffd4663fa80
```

  </div>
  <div>

```asm
multi_level_array:
	subq	$48, %rsp
	leaq	-64(%rbp), %rax
	movq	%rax, -48(%rbp)
	leaq	-56(%rbp), %rax
	movq	%rax, -40(%rbp)
	leaq	-48(%rbp), %rbx ; p
	movq	-48(%rbp), %r12 ; q, dereferencing
	movq	%r12, %rsi
	movq	%rbx, %rdi
	call	print_two_ptrs
	ret
```

  </div>
</div>

There is no warning for this case. Why?

---
layout: image-right
image: ./img/section-3.jpg
---

<div class="abs-bl m-12">
  <div class="text-2xl font-bold">Section 3</div>
  <h1 class="text-8xl!">Structure</h1>
</div>

---
layout: image-right
image: ./img/section-4.jpg
---

<div class="abs-bl m-12">
  <div class="text-2xl font-bold">Section 4</div>
  <h1 class="text-8xl!">Attack</h1>
</div>

---
layout: cover
background: ./img/86429302_p0.jpg
---

# Thanks for watching!
## Review presented by [thezzisu](github.com/thezzisu)

<div class="abs-bl w-full flex justify-center">
  <div class="text-sm font-mono">
    <div>Copyright @thezzisu, MIT Licence.</div>
    <div>See repository README.md for used images' copyright info.</div>
  </div>
</div>