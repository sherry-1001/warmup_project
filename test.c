#define _GNU_SOURCE
#include "cpufp_kernel_x86.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


static double get_time(struct timespec *start,
	struct timespec *end)
{
	return end->tv_sec - start->tv_sec + 
 		(end->tv_nsec - start->tv_nsec) * 1e-9;
}

#ifdef _AVX512_
#define AVX512F_FP32_COMP (0x20000000L * 320)
#define AVX512F_FP64_COMP (0x20000000L * 160)
#define AVX512F_VNNI_INT8_COMP (0x20000000L * 1280)

void cpufp_x86_avx512()
{
	int i;
	struct timespec start, end;
	double time_used, perf;

       	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        cpufp_kernel_x86_avx512f_fp32();
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        time_used = get_time(&start, &end);
	perf = AVX512F_FP32_COMP / time_used * 1e-9;
        
        printf("avx512f fp32 perf: %.4lf gflops.\n", perf);
	
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	cpufp_kernel_x86_avx512f_fp64();
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	time_used = get_time(&start, &end);
	perf = AVX512F_FP64_COMP / time_used * 1e-9;

	printf("avx512f fp64 per: %.4lf gflops.\n", perf);

	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	cpufp_kernel_x86_avx512_vnni_8b();
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	time_used = get_time(&start, &end);
	perf = AVX512F_VNNI_INT8_COMP / time_used * 1e-9;

	printf("avx512_vnni int8 perf: %.4lf gops.\n", perf);
}
#endif  

int main()
{
#ifdef _AVX512_
	cpufp_x86_avx512();
#endif 
	return 0;
}
