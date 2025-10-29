#include "gemm.h"
#include <stdio.h>
#include <riscv_vector.h>

void print_vector(vint32m4_t vec, size_t vl) {
    int32_t buffer[100];  // 确保足够大
    __riscv_vse32_v_i32m4(buffer, vec, vl);  // 存储到内存

    printf("Vector content (vl=%zu): ", vl);
    for (size_t i = 0; i < vl; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}
void optimized_gemm(uint8_t* A, int8_t* B, int32_t* C, int m, int n, int k) {
    size_t vl_max = __riscv_vsetvlmax_e8m1();
    int stride = 4;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int32_t sum = 0;
            for (int kk = 0; kk < k * stride; kk += vl_max) {
                size_t current_vl = __riscv_vsetvl_e8m1(k * stride - kk);
                // 跳步加载
                //vuint8m1_t va = __riscv_vlse8_v_u8m1(&A[i * k * stride + kk], 1, current_vl);
                //vint8m1_t vb = __riscv_vlse8_v_i8m1(&B[j * k * stride + kk], 1, current_vl);

		// 直接加载
		vuint8m1_t va = __riscv_vle8_v_u8m1(&A[i * k * stride + kk], current_vl);
                vint8m1_t vb = __riscv_vle8_v_i8m1(&B[j * k * stride + kk], current_vl);
		vint16m2_t vprod_ext1 = 	__riscv_vwmulsu_vv_i16m2(vb, va, current_vl);
		vint32m4_t vprod_ext = 	__riscv_vsext_vf2_i32m4(vprod_ext1, current_vl);
		// 此处注意，为了测试时间所以外层有1000次循环，如果需要printf的话需要修改打印次数
//		if(i == 0 && j == 0) {
//			printf("%d\n", vl_max);
//		 print_vector(vprod_ext, current_vl);
//		}
                // 规约求和
                vint32m1_t v_zero = __riscv_vmv_v_x_i32m1(0, current_vl);
                vint32m1_t v_sum = __riscv_vredsum_vs_i32m4_i32m1(vprod_ext, v_zero, current_vl);
                sum += __riscv_vmv_x_s_i32m1_i32(v_sum);
            }
            C[i * n + j] = sum;
        }
    }
}
