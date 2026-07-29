//types.h

/* types.h */
#ifndef __TYPES_H__
#define __TYPES_H__

// --- 8-Bit Data Types (Unsigned / Signed Byte structures) ---
typedef unsigned char u8;  // 8-bit unsigned integer: Values range from 0 to 255 (Commonly used for registers, flags, and characters)
typedef signed   char s8;  // 8-bit signed integer: Values range from -128 to 127

// --- 16-Bit Data Types (Unsigned / Signed Half-Word structures) ---
typedef unsigned short int  u16; // 16-bit unsigned integer: Values range from 0 to 65,535 (Commonly used for fine counters and ADC readings)
typedef signed   short int  s16; // 16-bit signed integer: Values range from -32,768 to 32,767

// --- 32-Bit Data Types (Unsigned / Signed Word structures) ---
typedef unsigned int  u32; // 32-bit unsigned integer: Values range from 0 to 4,294,967,295 (Standard word size for ARM7/LPC2148 registers)
typedef signed   int  s32; // 32-bit signed integer: Values range from -2,147,483,648 to 2,147,483,647

// --- Floating Point Types (Real Decimal structures) ---
typedef float  f32; // 32-bit single-precision floating point (IEEE 754): Used for raw scaled math (e.g., computed voltage/temperature metrics)
typedef double f64; // 64-bit double-precision floating point: Used for high-precision sensor transformations

#endif