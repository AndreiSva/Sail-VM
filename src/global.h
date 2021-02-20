#ifndef __global
#define __global

#define bool char
#define true 1
#define false 0

#define RED "\x1B[31m"
#define RESET "\033[0m"

#define parse_int(x) x[3] | (x[2] << 8) | (x[1] << 16) | (x[0] << 24)

#endif
