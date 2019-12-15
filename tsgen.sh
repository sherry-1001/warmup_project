as -o cpufp_kernel_x86_avx512f.o cpufp_kernel_x86_avx512f.s
as -o cpufp_kernel_x86_avx512_vnni.o cpufp_kernel_x86_avx512_vnni.s
gcc -D_AVX512_ -c test.c
gcc -o test test.o cpufp_kernel_x86_avx512f.o cpufp_kernel_x86_avx512_vnni.o
