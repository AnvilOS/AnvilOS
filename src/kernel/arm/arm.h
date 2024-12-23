
#ifndef ARM_H_INCLUDED
#define ARM_H_INCLUDED

struct regpack
{
    // These 8 are pushed onto the by the processor
    unsigned long r0;
    unsigned long r1;
    unsigned long r2;
    unsigned long r3;
    unsigned long r12;
    unsigned long lr;
    unsigned long pc;
    unsigned long psr;
} __attribute__ ((packed)) __attribute__ ((aligned(4)));

struct regpack_fpext
{
    unsigned long s0;
    unsigned long s1;
    unsigned long s2;
    unsigned long s3;
    unsigned long s4;
    unsigned long s5;
    unsigned long s6;
    unsigned long s7;
    unsigned long s8;
    unsigned long s9;
    unsigned long s10;
    unsigned long s11;
    unsigned long s12;
    unsigned long s13;
    unsigned long s14;
    unsigned long s15;
    unsigned long fpscr;
    unsigned long _Res;
} __attribute__ ((packed)) __attribute__ ((aligned(4)));

struct regpack_manual
{
    // These will need to be pushed manually
    unsigned long r4;
    unsigned long r5;
    unsigned long r6;
    unsigned long r7;
    unsigned long r8;
    unsigned long r9;
    unsigned long r10;
    unsigned long r11;
    unsigned long lr;
} __attribute__ ((packed)) __attribute__ ((aligned(4)));

struct all_regs
{
    struct regpack_manual regpack_manual;
    struct regpack regpack;
    struct regpack_fpext regpack_fpext;
} __attribute__ ((packed)) __attribute__ ((aligned(4)));

struct syscall_regs
{
    struct regpack regpack;
    struct regpack_fpext regpack_fpext;
} __attribute__ ((packed)) __attribute__ ((aligned(4)));

#endif // ARM_H_INCLUDED
