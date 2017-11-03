#ifndef __UpwindFirstWENO5a_cuda_hpp__
#define __UpwindFirstWENO5a_cuda_hpp__
#include <typedef.hpp>
#include <cuda_macro.hpp>

namespace beacls {
	class CudaStream;
};


class Approx4 {
};
class noApprox4 {
};
class StripDD {
};
class noStripDD {
};
class SaveDD {
};
class noSaveDD {
};

template<typename V>
__device__ inline
size_t get_dst_DD0_strip(
	const V stripDD = V());
template<>
__device__ inline
size_t get_dst_DD0_strip(
	const StripDD) {
	return 2;
}
template<>
__device__ inline
size_t get_dst_DD0_strip(
	const noStripDD) {
	return 0;
}

template<typename V>
__device__ inline
size_t get_dst_DD1_strip(
	const V stripDD = V());
template<>
__device__ inline
size_t get_dst_DD1_strip(
	const StripDD) {
	return 2;
}
template<>
__device__ inline
size_t get_dst_DD1_strip(
	const noStripDD) {
	return 1;
}

template<typename T, typename S> inline
__device__
void storeDD(
	T* dst_DD_ptr,
	const T d_0,
	const T d_1,
	const size_t dst_index,
	const S stripDD
);

template<typename T> inline
__device__
void storeDD(
	T* dst_DD_ptr,
	const T d_0,
	const T,
	const size_t dst_index,
	StripDD
) {
	dst_DD_ptr[dst_index] = d_0;
}

template<typename T> inline
__device__
void storeDD(
	T* dst_DD_ptr,
	const T,
	const T d_1,
	const size_t dst_index,
	noStripDD
) {
	dst_DD_ptr[dst_index] = d_1;
}
template<typename T, typename S> inline
__device__
void storeDDorNot(
	T* dst_DD_ptr,
	const T d,
	const size_t fdl_index,
	const size_t shifted_index,
	const size_t first_dimension_loop_size,
	const size_t dst_strip,
	const size_t dst_upperlimit,
	const S saveDD
);

template<typename T> inline
__device__
void storeDDorNot(
	T* dst_DD_ptr,
	const T d,
	const size_t fdl_index,
	const size_t shifted_index,
	const size_t first_dimension_loop_size,
	const size_t dst_strip,
	const size_t dst_upperlimit,
	SaveDD
) {
	if (shifted_index >= dst_strip) {
		size_t dst_offset = (shifted_index - dst_strip) * first_dimension_loop_size;
		size_t dst_index = fdl_index + dst_offset;
		if (dst_index < dst_upperlimit)
			dst_DD_ptr[dst_index] = d;
	}
}

template<typename T> inline
__device__
void storeDDorNot(
	T*,
	const T,
	const size_t,
	const size_t,
	const size_t,
	const size_t,
	const size_t,
	noSaveDD
) {

}

template<typename T> inline
__device__
void calcApprox4(
	T* dst_d33,
	const T d1,
	const T dx_d2,
	const T alpha_d3,
	const size_t dst_index
) {
	T d3 = d1 + dx_d2;
	T d33 = d3 + alpha_d3;
	dst_d33[dst_index] = d33;
}

template<typename T, typename S> inline
__device__
void calcApprox4s(
	T* dst_dL3_ptr,
	T* dst_dR3_ptr,
	const T d1_m3,
	const T d1_m2,
	const T d2_m2,
	const T d2_m1,
	const T d3_m2,
	const T d3_m1,
	const T dx,
	const T dx_square,
	const T x2_dx_square,
	const size_t dst_index,
	const S approx4 = S()
);

template<typename T> inline
__device__
void calcApprox4s(
	T* dst_dL3_ptr,
	T* dst_dR3_ptr,
	const T d1_m3,
	const T d1_m2,
	const T d2_m2,
	const T d2_m1,
	const T d3_m2,
	const T d3_m1,
	const T dx,
	const T dx_square,
	const T x2_dx_square,
	const size_t dst_index,
	const Approx4
) {
	calcApprox4(dst_dL3_ptr, d1_m3, dx * d2_m2, -dx_square * d3_m2, dst_index);
	calcApprox4(dst_dR3_ptr, d1_m2, -dx * d2_m1, x2_dx_square * d3_m1, dst_index);
}

template<typename T> inline
__device__
void calcApprox4s(
	T*,
	T*,
	const T,
	const T,
	const T,
	const T,
	const T,
	const T,
	const T,
	const T,
	const T,
	const size_t,
	const noApprox4
) {

}

template<typename T, typename S> inline
__device__
void saveDD0(
	T* dst_DD0_ptr,
	const T d1_m0,
	const size_t target_dimension_loop_index,
	const size_t dst_DD0_offset,
	const size_t dst_DD0_strip,
	const size_t dst_DD0_line_length,
	const S saveDD = S()
);

template<typename T> inline
__device__
void saveDD0(
	T* dst_DD0_ptr,
	const T d1_m0,
	const size_t target_dimension_loop_index,
	const size_t dst_DD0_offset,
	const size_t dst_DD0_strip,
	const size_t dst_DD0_line_length,
	const SaveDD

) {
	if ((target_dimension_loop_index >= dst_DD0_strip) && (target_dimension_loop_index  < dst_DD0_line_length + dst_DD0_strip))
		dst_DD0_ptr[target_dimension_loop_index + dst_DD0_offset - dst_DD0_strip] = d1_m0;
}

template<typename T> inline
__device__
void saveDD0(
	T*,
	const T,
	const size_t,
	const size_t,
	const size_t,
	const size_t,
	const noSaveDD
) {

}


template<typename T, typename S> inline
__device__
void saveDD1(
	T* dst_DD1_ptr,
	const T d2_m0,
	const size_t target_dimension_loop_index,
	const size_t dst_DD1_offset,
	const size_t dst_DD1_strip,
	const size_t dst_DD1_line_length,
	const S saveDD = S()
);

template<typename T> inline
__device__
void saveDD1(
	T* dst_DD1_ptr,
	const T d2_m0,
	const size_t target_dimension_loop_index,
	const size_t dst_DD1_offset,
	const size_t dst_DD1_strip,
	const size_t dst_DD1_line_length,
	const SaveDD

) {
	if ((target_dimension_loop_index >= dst_DD1_strip) && (target_dimension_loop_index  < dst_DD1_line_length + dst_DD1_strip))
		dst_DD1_ptr[target_dimension_loop_index + dst_DD1_offset - dst_DD1_strip] = d2_m0;
}

template<typename T> inline
__device__
void saveDD1(
	T*,
	const T,
	const size_t,
	const size_t,
	const size_t,
	const size_t,
	const noSaveDD
) {

}


template<typename T, typename S> inline
__device__
void saveDD2(
	T* dst_DD2_ptr,
	const T d3_m0,
	const size_t target_dimension_loop_index,
	const size_t dst_DD2_offset,
	const size_t dst_DD2_strip,
	const size_t dst_DD2_line_length,
	const S saveDD = S()
);

template<typename T> inline
__device__
void saveDD2(
	T* dst_DD2_ptr,
	const T d3_m0,
	const size_t target_dimension_loop_index,
	const size_t dst_DD2_offset,
	const size_t dst_DD2_strip,
	const size_t dst_DD2_line_length,
	const SaveDD

) {
	if (target_dimension_loop_index  < dst_DD2_line_length + dst_DD2_strip)
		dst_DD2_ptr[target_dimension_loop_index + dst_DD2_offset - dst_DD2_strip] = d3_m0;
}

template<typename T> inline
__device__
void saveDD2(
	T*,
	const T,
	const size_t,
	const size_t,
	const size_t,
	const size_t,
	const noSaveDD
) {

}

template<typename T> inline
__device__
void calcApprox1to3(
	T* dst_dL0,
	T* dst_dL1,
	T* dst_dL2,
	T* dst_dR0,
	T* dst_dR1,
	T* dst_dR2,
	const T d1_m2,
	const T d1_m3,
	const T d2_m1,
	const T d2_m2,
	const T d2_m3,
	const T d3_m0,
	const T d3_m1,
	const T d3_m2,
	const T d3_m3,
	const T dx,
	const T x2_dx_square,
	const T dx_square,
	const size_t dst_index
) {
	T dx_d2_m3 = dx * d2_m3;
	T dx_d2_m2 = dx * d2_m2;
	T dx_d2_m1 = dx * d2_m1;

	T dL0 = d1_m3 + dx_d2_m3;
	T dL1 = d1_m3 + dx_d2_m3;
	T dL2 = d1_m3 + dx_d2_m2;

	T dR0 = d1_m2 - dx_d2_m2;
	T dR1 = d1_m2 - dx_d2_m2;
	T dR2 = d1_m2 - dx_d2_m1;

	T dLL0 = dL0 + x2_dx_square * d3_m3;
	T dLL1 = dL1 + x2_dx_square * d3_m2;
	T dLL2 = dL2 - dx_square * d3_m1;

	T dRR0 = dR0 - dx_square * d3_m2;
	T dRR1 = dR1 - dx_square * d3_m1;
	T dRR2 = dR2 + x2_dx_square * d3_m0;

	dst_dL0[dst_index] = dLL0;
	dst_dL1[dst_index] = dLL1;
	dst_dL2[dst_index] = dLL2;
	dst_dR0[dst_index] = dRR0;
	dst_dR1[dst_index] = dRR1;
	dst_dR2[dst_index] = dRR2;
}


template<typename T> inline
__device__
void calcD1toD3_dim0(
	T &d0_m0, T &d0_m1,
	T &d1_m0, T &d1_m1, T &d1_m2, T &d1_m3,
	T &d2_m0, T &d2_m1, T &d2_m2, T &d2_m3,
	T &d3_m0, T &d3_m1, T &d3_m2, T &d3_m3,
	const T* boundedSrc,
	const T dxInv,
	const T dxInv_2,
	const T dxInv_3,
	const size_t target_dimension_loop_index) {
	d3_m3 = d3_m2; d3_m2 = d3_m1; d3_m1 = d3_m0;
	d2_m3 = d2_m2; d2_m2 = d2_m1; d2_m1 = d2_m0;
	d1_m3 = d1_m2; d1_m2 = d1_m1; d1_m1 = d1_m0;
	d0_m1 = d0_m0;
	d0_m0 = boundedSrc[target_dimension_loop_index + 1];
	d1_m0 = dxInv * (d0_m0 - d0_m1);
	d2_m0 = dxInv_2 * (d1_m0 - d1_m1);
	d3_m0 = dxInv_3 * (d2_m0 - d2_m1);
}

template<typename T> inline
__device__
void calcD1toD3_dim1(
	T &d1_m0, T &d1_m1, T &d1_m2, T &d1_m3,
	T &d2_m0, T &d2_m1, T &d2_m2, T &d2_m3,
	T &d3_m0, T &d3_m1, T &d3_m2, T &d3_m3,
	const T* d1s_ms1,
	const T* d1s_ms2,
	const T* d1s_ms3,
	const T* d2s_ms1,
	const T* d2s_ms2,
	const T* d2s_ms3,
	const T* d3s_ms1,
	const T* d3s_ms2,
	const T* d3s_ms3,
	const T* last_boundedSrc_ptr,
	const T* current_boundedSrc_ptr,
	const T dxInv,
	const T dxInv_2,
	const T dxInv_3,
	const size_t first_dimension_loop_index
) {
	T this_src = current_boundedSrc_ptr[first_dimension_loop_index];
	T last_src = last_boundedSrc_ptr[first_dimension_loop_index];
	d1_m0 = dxInv * (this_src - last_src);
	d1_m1 = d1s_ms1[first_dimension_loop_index];
	d1_m2 = d1s_ms2[first_dimension_loop_index];
	d1_m3 = d1s_ms3[first_dimension_loop_index];
	d2_m0 = dxInv_2 * (d1_m0 - d1_m1);
	d2_m1 = d2s_ms1[first_dimension_loop_index];
	d2_m2 = d2s_ms2[first_dimension_loop_index];
	d2_m3 = d2s_ms3[first_dimension_loop_index];
	d3_m0 = dxInv_3 * (d2_m0 - d2_m1);
	d3_m1 = d3s_ms1[first_dimension_loop_index];
	d3_m2 = d3s_ms2[first_dimension_loop_index];
	d3_m3 = d3s_ms3[first_dimension_loop_index];
}

template<typename T> inline
__device__
void calc_d0_dimLET2(
	T &d0_0,
	const T* tmpBoundedSrc_ptrs0,
	const size_t first_dimension_loop_index
) {
	d0_0 = tmpBoundedSrc_ptrs0[first_dimension_loop_index];
}

template<typename T> inline
__device__
void calc_d0d1_dimLET2(
	const T d0_0, T &d0_1,
	T &d1_0,
	const T* tmpBoundedSrc_ptrs1,
	const T dxInv,
	const size_t first_dimension_loop_index
) {
	d0_1 = tmpBoundedSrc_ptrs1[first_dimension_loop_index];
	d1_0 = dxInv * (d0_1 - d0_0);
}

template<typename T> inline
__device__
void calc_d0d1d2_dimLET2(
	const T d0_1, T &d0_2,
	const T d1_0, T &d1_1,
	T &d2_0,
	const T* tmpBoundedSrc_ptrs2,
	const T dxInv,
	const T dxInv_2,
	const size_t first_dimension_loop_index
) {
	d0_2 = tmpBoundedSrc_ptrs2[first_dimension_loop_index];
	d1_1 = dxInv * (d0_2 - d0_1);
	d2_0 = dxInv_2 * (d1_1 - d1_0);
}

template<typename T> inline
__device__
void calc_d0d1d2d3_dimLET2(
	const T d0_2, T &d0_3,
	const T d1_1, T &d1_2,
	const T d2_0, T &d2_1,
	T &d3_0,
	const T* tmpBoundedSrc_ptrs3,
	const T dxInv,
	const T dxInv_2,
	const T dxInv_3,
	const size_t first_dimension_loop_index
) {
	d0_3 = tmpBoundedSrc_ptrs3[first_dimension_loop_index];
	d1_2 = dxInv * (d0_3 - d0_2);
	d2_1 = dxInv_2 * (d1_2 - d1_1);
	d3_0 = dxInv_3 * (d2_1 - d2_0);
}

template<typename T> inline
__device__
void calcD1toD3_dimLET2(
	T &d0_0, T &d0_1, T &d0_2, T &d0_3,
	T &d1_0, T &d1_1, T &d1_2,
	T &d2_0, T &d2_1,
	T &d3_0,
	const T* tmpBoundedSrc_ptrs0,
	const T* tmpBoundedSrc_ptrs1,
	const T* tmpBoundedSrc_ptrs2,
	const T* tmpBoundedSrc_ptrs3,
	const T dxInv,
	const T dxInv_2,
	const T dxInv_3,
	const size_t first_dimension_loop_index
) {

	d0_0 = tmpBoundedSrc_ptrs0[first_dimension_loop_index];
	d0_1 = tmpBoundedSrc_ptrs1[first_dimension_loop_index];
	d1_0 = dxInv * (d0_1 - d0_0);

	d0_2 = tmpBoundedSrc_ptrs2[first_dimension_loop_index];
	d1_1 = dxInv*(d0_2 - d0_1);
	d2_0 = dxInv_2 * (d1_1 - d1_0);

	d0_3 = tmpBoundedSrc_ptrs3[first_dimension_loop_index];
	d1_2 = dxInv*(d0_3 - d0_2);
	d2_1 = dxInv_2 * (d1_2 - d1_1);
	d3_0 = dxInv_3 * (d2_1 - d2_0);
}

template<typename T> inline
__device__
void calcD1toD3_dimLET2(
	T &d0_0, T &d0_1, T &d0_2, T &d0_3, T &d0_4, T &d0_5, T &d0_6,
	T &d1_0, T &d1_1, T &d1_2, T &d1_3, T &d1_4, T &d1_5,
	T &d2_0, T &d2_1, T &d2_2, T &d2_3, T &d2_4,
	T &d3_0, T &d3_1, T &d3_2, T &d3_3,
	const T* tmpBoundedSrc_ptrs0,
	const T* tmpBoundedSrc_ptrs1,
	const T* tmpBoundedSrc_ptrs2,
	const T* tmpBoundedSrc_ptrs3,
	const T* tmpBoundedSrc_ptrs4,
	const T* tmpBoundedSrc_ptrs5,
	const T* tmpBoundedSrc_ptrs6,
	const T dxInv,
	const T dxInv_2,
	const T dxInv_3,
	const size_t first_dimension_loop_index
) {
	calcD1toD3_dimLET2(d0_0, d0_1, d0_2, d0_3, d1_0, d1_1, d1_2, d2_0, d2_1, d3_0,
		tmpBoundedSrc_ptrs0, tmpBoundedSrc_ptrs1, tmpBoundedSrc_ptrs2, tmpBoundedSrc_ptrs3,
		dxInv, dxInv_2, dxInv_3, first_dimension_loop_index);

	d0_4 = tmpBoundedSrc_ptrs4[first_dimension_loop_index];
	d1_3 = dxInv*(d0_4 - d0_3);
	d2_2 = dxInv_2 * (d1_3 - d1_2);
	d3_1 = dxInv_3 * (d2_2 - d2_1);

	d0_5 = tmpBoundedSrc_ptrs5[first_dimension_loop_index];
	d1_4 = dxInv*(d0_5 - d0_4);
	d2_3 = dxInv_2 * (d1_4 - d1_3);
	d3_2 = dxInv_3 * (d2_3 - d2_2);

	d0_6 = tmpBoundedSrc_ptrs6[first_dimension_loop_index];
	d1_5 = dxInv*(d0_6 - d0_5);
	d2_4 = dxInv_2 * (d1_5 - d1_4);
	d3_3 = dxInv_3 * (d2_4 - d2_3);
}

template<typename V>
__device__ inline
size_t get_dst_DD0_offset(
	const size_t index,
	const size_t first_dimension_loop_size,
	const V stripDD = V());
template<>
__device__ inline
size_t get_dst_DD0_offset(
	const size_t index,
	const size_t first_dimension_loop_size,
	const StripDD) {
	return index * (first_dimension_loop_size + 1);
}
template<>
__device__ inline
size_t get_dst_DD0_offset(
	const size_t index,
	const size_t first_dimension_loop_size,
	const noStripDD) {
	return index * (first_dimension_loop_size + 5);
}

template<typename V>
__device__ inline
size_t get_dst_DD1_offset(
	const size_t index,
	const size_t first_dimension_loop_size,
	const V stripDD = V());
template<>
__device__ inline
size_t get_dst_DD1_offset(
	const size_t index,
	const size_t first_dimension_loop_size,
	const StripDD) {
	return index * (first_dimension_loop_size + 2);
}
template<>
__device__ inline
size_t get_dst_DD1_offset(
	const size_t index,
	const size_t first_dimension_loop_size,
	const noStripDD) {
	return index * (first_dimension_loop_size + 4);
}

template<typename T, typename S, typename U, typename V>
__device__ inline
void calc_D1toD3andDD_dim0_inline(
	T* dst_dL0_ptr,
	T* dst_dL1_ptr,
	T* dst_dL2_ptr,
	T* dst_dL3_ptr,
	T* dst_dR0_ptr,
	T* dst_dR1_ptr,
	T* dst_dR2_ptr,
	T* dst_dR3_ptr,
	T* dst_DD0_ptr,
	const T* boundedSrc_base_ptr,
	const T dxInv,
	const T dxInv_2,
	const T dxInv_3,
	const T dx,
	const T x2_dx_square,
	const T dx_square,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t target_dimension_loop_size,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t stencil,
	const size_t dst_DD0_line_length,
	const size_t thread_length_z,
	const size_t thread_length_y,
	const size_t thread_length_x,
	const size_t blockIdx_y,
	const size_t blockIdx_x,
	const size_t blockDim_y,
	const size_t blockDim_x,
	const size_t threadIdx_z,
	const size_t threadIdx_y,
	const size_t threadIdx_x,
	const S saveDD = S(),
	const U approx4 = U(),
	const V stripDD = V()
) {
	const size_t global_thraed_index_z = threadIdx_z;
	const size_t loop_index_z_base = global_thraed_index_z*thread_length_z;
	const size_t actual_thread_length_z = get_actual_length(num_of_slices, thread_length_z, loop_index_z_base);
	for (size_t loop_index_z = loop_index_z_base; loop_index_z < actual_thread_length_z + loop_index_z_base; ++loop_index_z) {
		const size_t dst_slice_offset = loop_index_z * slice_length;
		const size_t slice_loop_offset = loop_index_z * loop_length;
		const size_t global_thraed_index_y = blockIdx_y * blockDim_y + threadIdx_y;
		const size_t loop_index_y_base = global_thraed_index_y*thread_length_y;
		const size_t actual_thread_length_y = get_actual_length(loop_length, thread_length_y, loop_index_y_base);
		for (size_t loop_index_y = loop_index_y_base; loop_index_y < actual_thread_length_y + loop_index_y_base; ++loop_index_y) {
			const size_t global_thread_index_x = blockIdx_x * blockDim_x + threadIdx_x;
			const size_t loop_index_x_base = global_thread_index_x * thread_length_x;
			if (loop_index_x_base < target_dimension_loop_size - stencil + 1) {
				//! Target dimension is first loop
				const T* boundedSrc_ptr = boundedSrc_base_ptr + (first_dimension_loop_size + stencil * 2) * (slice_loop_offset + global_thraed_index_y);

				T d0_m0 = boundedSrc_ptr[loop_index_x_base];
				T d0_m1 = 0;
				T d1_m0 = 0;
				T d1_m1 = 0;
				T d1_m2 = 0;
				T d1_m3 = 0;
				T d2_m0 = 0;
				T d2_m1 = 0;
				T d2_m2 = 0;
				T d2_m3 = 0;
				T d3_m0 = 0;
				T d3_m1 = 0;
				T d3_m2 = 0;
				T d3_m3 = 0;

				const size_t dst_dLdR_offset = global_thraed_index_y * first_dimension_loop_size + dst_slice_offset;
				const size_t dst_DD0_offset = get_dst_DD0_offset(slice_loop_offset + global_thraed_index_y, first_dimension_loop_size, stripDD);
				const size_t dst_DD1_offset = get_dst_DD1_offset(slice_loop_offset + global_thraed_index_y, first_dimension_loop_size, stripDD);
				const size_t dst_DD2_offset = (slice_loop_offset + global_thraed_index_y) * (first_dimension_loop_size + 3);
				const size_t dst_DD0_strip = get_dst_DD0_strip(stripDD);
				const size_t dst_DD1_strip = get_dst_DD0_strip(stripDD);
				const size_t dst_DD2_strip = 2;
				const size_t actual_thread_length_x = get_actual_length(target_dimension_loop_size - 1, thread_length_x, loop_index_x_base);
				for (size_t loop_index_x = 0; loop_index_x < actual_thread_length_x + stencil + 2; ++loop_index_x) {
					const size_t target_dimension_loop_index = loop_index_x + loop_index_x_base;
					if (target_dimension_loop_index < target_dimension_loop_size - 1) {
						const size_t src_index = target_dimension_loop_index;
						d0_m1 = d0_m0;
						d0_m0 = boundedSrc_ptr[src_index + 1];
						d1_m3 = d1_m2;
						d1_m2 = d1_m1;
						d1_m1 = d1_m0;
						d1_m0 = dxInv * (d0_m0 - d0_m1);
						if (loop_index_x >= 1) {
							d2_m3 = d2_m2;
							d2_m2 = d2_m1;
							d2_m1 = d2_m0;
							d2_m0 = dxInv_2 * (d1_m0 - d1_m1);
							if (loop_index_x >= 2) {
								d3_m3 = d3_m2;
								d3_m2 = d3_m1;
								d3_m1 = d3_m0;
								d3_m0 = dxInv_3 * (d2_m0 - d2_m1);
							}
						}
						saveDD0(
							dst_DD0_ptr,
							d1_m0,
							target_dimension_loop_index,
							dst_DD0_offset, dst_DD0_strip, dst_DD0_line_length, saveDD);
						if (loop_index_x >= stencil + 2) {
							const size_t target_dimension_loop_index_stencil = target_dimension_loop_index - stencil - 1;
							const size_t dst_index = target_dimension_loop_index_stencil + dst_dLdR_offset - 1;
							calcApprox1to3(dst_dL0_ptr, dst_dL1_ptr, dst_dL2_ptr, dst_dR0_ptr, dst_dR1_ptr, dst_dR2_ptr, d1_m2, d1_m3, d2_m1, d2_m2, d2_m3, d3_m0, d3_m1, d3_m2, d3_m3, dx, x2_dx_square, dx_square, dst_index);
							calcApprox4s(dst_dL3_ptr, dst_dR3_ptr, d1_m3, d1_m2, d2_m2, d2_m1, d3_m2, d3_m1, dx, dx_square, x2_dx_square, dst_index, approx4);
						}
					}
				}
			}
		}
	}
}

void UpwindFirstWENO5aHelper_execute_dim0_cuda
(
	FLOAT_TYPE* dst_dL0_ptr,
	FLOAT_TYPE* dst_dL1_ptr,
	FLOAT_TYPE* dst_dL2_ptr,
	FLOAT_TYPE* dst_dL3_ptr,
	FLOAT_TYPE* dst_dR0_ptr,
	FLOAT_TYPE* dst_dR1_ptr,
	FLOAT_TYPE* dst_dR2_ptr,
	FLOAT_TYPE* dst_dR3_ptr,
	FLOAT_TYPE* dst_DD0_ptr,
	const FLOAT_TYPE* boundedSrc_base_ptr,
	const FLOAT_TYPE dxInv,
	const FLOAT_TYPE dxInv_2,
	const FLOAT_TYPE dxInv_3,
	const FLOAT_TYPE dx,
	const FLOAT_TYPE x2_dx_square,
	const FLOAT_TYPE dx_square,
	const size_t num_of_slices,
	const size_t outer_dimensions_loop_length,
	const size_t target_dimension_loop_size,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t stencil,
	const bool saveDD,
	const bool approx4,
	const bool stripDD,
	const size_t dst_DD0_line_length,
	beacls::CudaStream* cudaStream
);

template<typename V>
__device__ inline
size_t get_dst_DD0_strip_dim1(
	const V stripDD = V());
template<>
__device__ inline
size_t get_dst_DD0_strip_dim1(
	const StripDD) {
	return 3;
}
template<>
__device__ inline
size_t get_dst_DD0_strip_dim1(
	const noStripDD) {
	return 1;
}

template<typename V>
__device__ inline
size_t get_dst_DD1_strip_dim1(
	const V stripDD = V());
template<>
__device__ inline
size_t get_dst_DD1_strip_dim1(
	const StripDD) {
	return 3;
}
template<>
__device__ inline
size_t get_dst_DD1_strip_dim1(
	const noStripDD) {
	return 2;
}

template<typename V>
__device__ inline
size_t get_dst_DD2_strip_dim1(
	const V stripDD = V());
template<>
__device__ inline
size_t get_dst_DD2_strip_dim1(
	const StripDD) {
	return 3;
}
template<>
__device__ inline
size_t get_dst_DD2_strip_dim1(
	const noStripDD) {
	return 3;
}

template<typename T, typename S, typename U, typename V>
__device__ inline
void calc_D1toD3andDD_dim1_inline(
	T* dst_dL0_ptr,
	T* dst_dL1_ptr,
	T* dst_dL2_ptr,
	T* dst_dL3_ptr,
	T* dst_dR0_ptr,
	T* dst_dR1_ptr,
	T* dst_dR2_ptr,
	T* dst_dR3_ptr,
	T* dst_DD0_ptr,
	const T* boundedSrc_base_ptr,
	const T dxInv,
	const T dxInv_2,
	const T dxInv_3,
	const T dx,
	const T x2_dx_square,
	const T dx_square,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t stencil,
	const size_t dst_DD0_slice_size,
	const size_t thread_length_z,
	const size_t thread_length_y,
	const size_t thread_length_x,
	const size_t blockIdx_y,
	const size_t blockIdx_x,
	const size_t blockDim_y,
	const size_t blockDim_x,
	const size_t threadIdx_z,
	const size_t threadIdx_y,
	const size_t threadIdx_x,
	const S saveDD = S(),
	const U approx4 = U(),
	const V stripDD = V()
)
{
	const size_t global_thraed_index_z = threadIdx_z;
	const size_t loop_index_z_base = global_thraed_index_z*thread_length_z;
	const size_t actual_thread_length_z = get_actual_length(num_of_slices, thread_length_z, loop_index_z_base);
	const size_t prologue_length = stencil * 2;
	const size_t src_loop_length = (loop_length + prologue_length);
	for (size_t loop_index_z = loop_index_z_base; loop_index_z < actual_thread_length_z + loop_index_z_base; ++loop_index_z) {
		const size_t slice_offset = loop_index_z * slice_length;
		const size_t dst_DD0_slice_offset = loop_index_z * dst_DD0_slice_size;
		const size_t dst_DD0_slice_upperlimit = dst_DD0_slice_offset + dst_DD0_slice_size;

		const size_t global_thraed_index_y = blockIdx_y * blockDim_y + threadIdx_y;
		const size_t loop_index_y_base = global_thraed_index_y*thread_length_y;
		const size_t dst_loop_y_base_offset = loop_index_y_base * first_dimension_loop_size;
		const size_t actual_thread_length_y = get_actual_length(loop_length, thread_length_y, loop_index_y_base);
		if (actual_thread_length_y > 0) {
			const size_t global_thread_index_x = blockIdx_x * blockDim_x + threadIdx_x;
			const size_t loop_index_x_base = global_thread_index_x * thread_length_x;


			const size_t actual_thread_length_x = get_actual_length(first_dimension_loop_size, thread_length_x, loop_index_x_base);
			for (size_t fdl_index_in_thread = 0; fdl_index_in_thread < actual_thread_length_x; ++fdl_index_in_thread) {
				const size_t fdl_index = fdl_index_in_thread + loop_index_x_base;
				T d0_m0 = -1;
				T d0_m1 = -1;
				T d1_m0 = -1;
				T d1_m1 = -1;
				T d1_m2 = -1;
				T d2_m0 = -1;
				T d2_m1 = -1;
				T d2_m2 = -1;
				T d3_m0 = -1;
				T d3_m1 = -1;
				T d3_m2 = -1;

				//Prologue
				if (loop_index_y_base == 0) {
					for (size_t prologue_index = 0; prologue_index < prologue_length; ++prologue_index) {
						const T* tmpBoundedSrc_ptrs0 = boundedSrc_base_ptr +
							(loop_index_z*src_loop_length + prologue_index + loop_index_y_base)*first_dimension_loop_size;
						d0_m1 = d0_m0;
						d0_m0 = tmpBoundedSrc_ptrs0[fdl_index];
						if (prologue_index >= 1) {
							d1_m2 = d1_m1;
							d1_m1 = d1_m0;
							d1_m0 = dxInv * (d0_m0 - d0_m1);
							storeDDorNot(dst_DD0_ptr, d1_m0, fdl_index + dst_loop_y_base_offset + dst_DD0_slice_offset, prologue_index, first_dimension_loop_size, get_dst_DD0_strip_dim1(stripDD), dst_DD0_slice_upperlimit, saveDD);
							if (prologue_index >= 2) {
								d2_m2 = d2_m1;
								d2_m1 = d2_m0;
								d2_m0 = dxInv_2 * (d1_m0 - d1_m1);
								if (prologue_index >= 3) {
									d3_m2 = d3_m1;
									d3_m1 = d3_m0;
									d3_m0 = dxInv_3 * (d2_m0 - d2_m1);
								}
							}
						}
					}
				}
				else {
					for (size_t prologue_index = 0; prologue_index < prologue_length; ++prologue_index) {
						const T* tmpBoundedSrc_ptrs0 = boundedSrc_base_ptr +
							(loop_index_z*src_loop_length + prologue_index + loop_index_y_base)*first_dimension_loop_size;
						d0_m1 = d0_m0;
						d0_m0 = tmpBoundedSrc_ptrs0[fdl_index];
						d1_m2 = d1_m1;
						d1_m1 = d1_m0;
						d1_m0 = dxInv * (d0_m0 - d0_m1);
						d2_m2 = d2_m1;
						d2_m1 = d2_m0;
						d2_m0 = dxInv_2 * (d1_m0 - d1_m1);
						d3_m2 = d3_m1;
						d3_m1 = d3_m0;
						d3_m0 = dxInv_3 * (d2_m0 - d2_m1);
					}
				}
				for (size_t loop_index = 0; loop_index < actual_thread_length_y; ++loop_index) {
					const size_t shifted_index = (loop_index + prologue_length + loop_index_y_base);
					const size_t dst_dLdR_offset = (loop_index + loop_index_y_base) * first_dimension_loop_size + slice_offset;
					const T* tmpBoundedSrc_ptrs0 = boundedSrc_base_ptr +
						(loop_index_z*src_loop_length + shifted_index)*first_dimension_loop_size;
					const size_t dst_dLdR_index = fdl_index + dst_dLdR_offset;
					const T d3_m3 = d3_m2;
					d3_m2 = d3_m1;
					d3_m1 = d3_m0;
					const T d2_m3 = d2_m2;
					d2_m2 = d2_m1;
					d2_m1 = d2_m0;
					const T d1_m3 = d1_m2;
					d1_m2 = d1_m1;
					d1_m1 = d1_m0;
					d0_m1 = d0_m0;

					d0_m0 = tmpBoundedSrc_ptrs0[fdl_index];
					d1_m0 = dxInv * (d0_m0 - d0_m1);
					d2_m0 = dxInv_2 * (d1_m0 - d1_m1);
					d3_m0 = dxInv_3 * (d2_m0 - d2_m1);
					calcApprox1to3<T>(dst_dL0_ptr, dst_dL1_ptr, dst_dL2_ptr, dst_dR0_ptr, dst_dR1_ptr, dst_dR2_ptr,
						d1_m2, d1_m3, d2_m1, d2_m2, d2_m3, d3_m0, d3_m1, d3_m2, d3_m3, dx, x2_dx_square, dx_square, dst_dLdR_index);
					calcApprox4s(dst_dL3_ptr, dst_dR3_ptr, d1_m3, d1_m2, d2_m2, d2_m1, d3_m2, d3_m1, dx, dx_square, x2_dx_square, dst_dLdR_index, approx4);
					storeDDorNot(dst_DD0_ptr, d1_m0, fdl_index + dst_DD0_slice_offset, shifted_index, first_dimension_loop_size, get_dst_DD0_strip_dim1(stripDD), dst_DD0_slice_upperlimit, saveDD);
				}
			}
		}
	}
}


void UpwindFirstWENO5aHelper_execute_dim1_cuda
(
	FLOAT_TYPE* dst_dL0_ptr,
	FLOAT_TYPE* dst_dL1_ptr,
	FLOAT_TYPE* dst_dL2_ptr,
	FLOAT_TYPE* dst_dL3_ptr,
	FLOAT_TYPE* dst_dR0_ptr,
	FLOAT_TYPE* dst_dR1_ptr,
	FLOAT_TYPE* dst_dR2_ptr,
	FLOAT_TYPE* dst_dR3_ptr,
	FLOAT_TYPE* dst_DD0_ptr,
	const FLOAT_TYPE* tmpBoundedSrc_ptr,
	const FLOAT_TYPE dxInv,
	const FLOAT_TYPE dxInv_2,
	const FLOAT_TYPE dxInv_3,
	const FLOAT_TYPE dx,
	const FLOAT_TYPE x2_dx_square,
	const FLOAT_TYPE dx_square,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t stencil,
	const size_t dst_DD0_size,
	const bool saveDD,
	const bool approx4,
	const bool stripDD,
	beacls::CudaStream* cudaStream
);

template<typename T, typename S, typename U> inline
__device__
void calc_D1toD3andDD_dimLET2_inline(
	T* dst_dL0_ptr,
	T* dst_dL1_ptr,
	T* dst_dL2_ptr,
	T* dst_dL3_ptr,
	T* dst_dR0_ptr,
	T* dst_dR1_ptr,
	T* dst_dR2_ptr,
	T* dst_dR3_ptr,
	T* dst_DD0_ptr_base,
	const T* tmpBoundedSrc_ptr,
	const T dxInv,
	const T dxInv_2,
	const T dxInv_3,
	const T dx,
	const T x2_dx_square,
	const T dx_square,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t first_dimension_loop_size,
	const size_t num_of_strides,
	const size_t num_of_dLdR_in_slice,
	const size_t slice_length,
	const size_t thread_length_z,
	const size_t thread_length_y,
	const size_t thread_length_x,
	const size_t blockIdx_y,
	const size_t blockIdx_x,
	const size_t blockDim_y,
	const size_t blockDim_x,
	const size_t threadIdx_z,
	const size_t threadIdx_y,
	const size_t threadIdx_x,
	const S approx4 = S(),
	const U stripDD = U()
)
{
	const size_t num_of_loops_in_slices = loop_length*num_of_slices;
	const size_t global_thraed_index_z = threadIdx_z;
	const size_t loop_index_z_base = global_thraed_index_z*thread_length_z;
	const size_t actual_thread_length_z = get_actual_length(num_of_slices, thread_length_z, loop_index_z_base);
	for (size_t loop_index_z = loop_index_z_base; loop_index_z < actual_thread_length_z + loop_index_z_base; ++loop_index_z) {
		const size_t dst_slice_offset = loop_index_z * slice_length;
		const size_t global_thraed_index_y = blockIdx_y * blockDim_y + threadIdx_y;
		const size_t loop_index_y_base = global_thraed_index_y*thread_length_y;
		const size_t actual_thread_length_y = get_actual_length(loop_length, thread_length_y, loop_index_y_base);
		for (size_t loop_index_y = loop_index_y_base; loop_index_y < actual_thread_length_y + loop_index_y_base; ++loop_index_y) {
			const size_t global_thread_index_x = blockIdx_x * blockDim_x + threadIdx_x;
			const size_t loop_index_x_base = global_thread_index_x * thread_length_x;
			const size_t actual_thread_length_x = get_actual_length(first_dimension_loop_size, thread_length_x, loop_index_x_base);
			const size_t dst_loop_offset = global_thraed_index_y * first_dimension_loop_size + dst_slice_offset;
			for (size_t loop_index_x = loop_index_x_base; loop_index_x < actual_thread_length_x + loop_index_x_base; ++loop_index_x) {
				T d2_m1;
				T d1_m1, d1_m2;
				T d0_m1;
				const size_t base_offset = loop_index_z*loop_length + loop_index_y;
				//! Prologue
				{
					const T* tmpBoundedSrc_ptrs0 = tmpBoundedSrc_ptr + (base_offset)*first_dimension_loop_size;
					const T* tmpBoundedSrc_ptrs1 = tmpBoundedSrc_ptr + (base_offset + num_of_loops_in_slices)*first_dimension_loop_size;
					const T* tmpBoundedSrc_ptrs2 = tmpBoundedSrc_ptr + (base_offset + 2 * num_of_loops_in_slices)*first_dimension_loop_size;
					const T d0_m0 = tmpBoundedSrc_ptrs2[loop_index_x];
					d0_m1 = tmpBoundedSrc_ptrs1[loop_index_x];
					const T d0_m2 = tmpBoundedSrc_ptrs0[loop_index_x];
					const T d1_m0 = dxInv * (d0_m0 - d0_m1);
					d1_m1 = dxInv * (d0_m1 - d0_m2);
					d2_m1 = dxInv_2 * (d1_m0 - d1_m1);
					d1_m2 = d1_m1;
					d1_m1 = d1_m0;
					d0_m1 = d0_m0;
				}
				T d1_m3 = 0;
				T d2_m2 = 0, d2_m3 = 0;
				T d3_m1 = 0, d3_m2 = 0, d3_m3 = 0;

				for (size_t stride_index = 0; stride_index < num_of_strides; ++stride_index) {
					const size_t dst_stride_offset = stride_index * loop_length * num_of_slices * first_dimension_loop_size;
					const size_t dst_DD_index = loop_index_x + dst_loop_offset + dst_stride_offset;
					const size_t stride_offset = (stride_index + 3) * num_of_loops_in_slices;

					const T* tmpBoundedSrc_ptrs3 = tmpBoundedSrc_ptr + (base_offset + stride_offset)*first_dimension_loop_size;
					T d0_m0, d1_m0;
					calc_d0d1_dimLET2<T>(d0_m1, d0_m0, d1_m0, tmpBoundedSrc_ptrs3, dxInv, loop_index_x);
					const T d2_m0 = dxInv_2 * (d1_m0 - d1_m1);
					const T d3_m0 = dxInv_3 * (d2_m0 - d2_m1);
					if ((stride_index >= 3) && (stride_index <= 3 + num_of_dLdR_in_slice - 1)) {
						const size_t dst_dLdR_slice_offset = (stride_index - 3) * slice_length;
						size_t dst_dLdR_index = loop_index_x + dst_loop_offset + dst_dLdR_slice_offset;
						calcApprox1to3<T>(dst_dL0_ptr, dst_dL1_ptr, dst_dL2_ptr, dst_dR0_ptr, dst_dR1_ptr, dst_dR2_ptr,
							d1_m2, d1_m3, d2_m1, d2_m2, d2_m3, d3_m0, d3_m1, d3_m2, d3_m3, dx, x2_dx_square, dx_square, dst_dLdR_index);
						calcApprox4s(dst_dL3_ptr, dst_dR3_ptr, d1_m3, d1_m2, d2_m2, d2_m1, d3_m2, d3_m1, dx, dx_square, x2_dx_square, dst_dLdR_index, approx4);
					}
					storeDD(dst_DD0_ptr_base, d1_m0, d1_m2, dst_DD_index, stripDD);
					d3_m3 = d3_m2;
					d3_m2 = d3_m1;
					d3_m1 = d3_m0;
					d2_m3 = d2_m2;
					d2_m2 = d2_m1;
					d2_m1 = d2_m0;
					d1_m3 = d1_m2;
					d1_m2 = d1_m1;
					d1_m1 = d1_m0;
					d0_m1 = d0_m0;
				}
			}
		}
	}
}
template<typename T, typename S> inline
__device__
void calc_D1toD3_dimLET2_inline(
	T* dst_dL0_ptr,
	T* dst_dL1_ptr,
	T* dst_dL2_ptr,
	T* dst_dL3_ptr,
	T* dst_dR0_ptr,
	T* dst_dR1_ptr,
	T* dst_dR2_ptr,
	T* dst_dR3_ptr,
	const T* tmpBoundedSrc_ptr,
	const T dxInv,
	const T dxInv_2,
	const T dxInv_3,
	const T dx,
	const T x2_dx_square,
	const T dx_square,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t thread_length_z,
	const size_t thread_length_y,
	const size_t thread_length_x,
	const size_t blockIdx_y,
	const size_t blockIdx_x,
	const size_t blockDim_y,
	const size_t blockDim_x,
	const size_t threadIdx_z,
	const size_t threadIdx_y,
	const size_t threadIdx_x,
	const S approx4 = S()
)
{
	const size_t num_of_loops_in_slices = loop_length*num_of_slices;
	const size_t global_thraed_index_z = threadIdx_z;
	const size_t loop_index_z_base = global_thraed_index_z*thread_length_z;
	const size_t actual_thread_length_z = get_actual_length(num_of_slices, thread_length_z, loop_index_z_base);
	for (size_t loop_index_z = loop_index_z_base; loop_index_z < actual_thread_length_z + loop_index_z_base; ++loop_index_z) {
		const size_t dst_slice_offset = loop_index_z * slice_length;
		const size_t global_thraed_index_y = blockIdx_y * blockDim_y + threadIdx_y;
		const size_t loop_index_y_base = global_thraed_index_y*thread_length_y;
		const size_t actual_thread_length_y = get_actual_length(loop_length, thread_length_y, loop_index_y_base);
		for (size_t loop_index_y = loop_index_y_base; loop_index_y < actual_thread_length_y + loop_index_y_base; ++loop_index_y) {
			size_t global_thread_index_x = blockIdx_x * blockDim_x + threadIdx_x;
			size_t loop_index_x_base = global_thread_index_x * thread_length_x;
			const size_t actual_thread_length_x = get_actual_length(first_dimension_loop_size, thread_length_x, loop_index_x_base);
			const size_t dst_loop_offset = global_thraed_index_y * first_dimension_loop_size + dst_slice_offset;
			const size_t base_offset = loop_index_z*loop_length + loop_index_y;

			const T* tmpBoundedSrc_ptrs0 = tmpBoundedSrc_ptr + (base_offset)*first_dimension_loop_size;
			const T* tmpBoundedSrc_ptrs1 = tmpBoundedSrc_ptr + (base_offset + num_of_loops_in_slices)*first_dimension_loop_size;
			const T* tmpBoundedSrc_ptrs2 = tmpBoundedSrc_ptr + (base_offset + 2 * num_of_loops_in_slices)*first_dimension_loop_size;
			const T* tmpBoundedSrc_ptrs3 = tmpBoundedSrc_ptr + (base_offset + 3 * num_of_loops_in_slices)*first_dimension_loop_size;
			const T* tmpBoundedSrc_ptrs4 = tmpBoundedSrc_ptr + (base_offset + 4 * num_of_loops_in_slices)*first_dimension_loop_size;
			const T* tmpBoundedSrc_ptrs5 = tmpBoundedSrc_ptr + (base_offset + 5 * num_of_loops_in_slices)*first_dimension_loop_size;
			const T* tmpBoundedSrc_ptrs6 = tmpBoundedSrc_ptr + (base_offset + 6 * num_of_loops_in_slices)*first_dimension_loop_size;

			for (size_t loop_index_x = loop_index_x_base; loop_index_x < actual_thread_length_x + loop_index_x_base; ++loop_index_x) {
				T d0_0, d0_1, d0_2, d0_3, d0_4, d0_5, d0_6, d1_0, d1_1, d1_2, d1_3, d1_4, d1_5, d2_0, d2_1, d2_2, d2_3, d2_4, d3_0, d3_1, d3_2, d3_3;
				calcD1toD3_dimLET2<T>(
					d0_0, d0_1, d0_2, d0_3, d0_4, d0_5, d0_6, d1_0, d1_1, d1_2, d1_3, d1_4, d1_5, d2_0, d2_1, d2_2, d2_3, d2_4, d3_0, d3_1, d3_2, d3_3,
					tmpBoundedSrc_ptrs0, tmpBoundedSrc_ptrs1, tmpBoundedSrc_ptrs2, tmpBoundedSrc_ptrs3, tmpBoundedSrc_ptrs4, tmpBoundedSrc_ptrs5, tmpBoundedSrc_ptrs6,
					dxInv, dxInv_2, dxInv_3, loop_index_x
					);
				const size_t dst_dLdR_slice_offset = 0;
				const size_t dst_dLdR_index = loop_index_x + dst_loop_offset + dst_dLdR_slice_offset;
				calcApprox1to3<T>(dst_dL0_ptr, dst_dL1_ptr, dst_dL2_ptr, dst_dR0_ptr, dst_dR1_ptr, dst_dR2_ptr,
					d1_3, d1_2, d2_3, d2_2, d2_1, d3_3, d3_2, d3_1, d3_0, dx, x2_dx_square, dx_square, dst_dLdR_index);
				calcApprox4s(dst_dL3_ptr, dst_dR3_ptr, d1_2, d1_3, d2_2, d2_3, d3_1, d3_2, dx, dx_square, x2_dx_square, dst_dLdR_index, approx4);
			}
		}
	}
}

void UpwindFirstWENO5aHelper_execute_dimLET2_cuda
(
	FLOAT_TYPE* dst_dL0_ptr,
	FLOAT_TYPE* dst_dL1_ptr,
	FLOAT_TYPE* dst_dL2_ptr,
	FLOAT_TYPE* dst_dL3_ptr,
	FLOAT_TYPE* dst_dR0_ptr,
	FLOAT_TYPE* dst_dR1_ptr,
	FLOAT_TYPE* dst_dR2_ptr,
	FLOAT_TYPE* dst_dR3_ptr,
	FLOAT_TYPE* dst_DD0_ptr,
	const FLOAT_TYPE* tmpBoundedSrc_ptr,
	const FLOAT_TYPE dxInv,
	const FLOAT_TYPE dxInv_2,
	const FLOAT_TYPE dxInv_3,
	const FLOAT_TYPE dx,
	const FLOAT_TYPE x2_dx_square,
	const FLOAT_TYPE dx_square,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t first_dimension_loop_size,
	const size_t num_of_strides,
	const size_t num_of_dLdR_in_slice,
	const size_t slice_length,
	const bool saveDD,
	const bool approx4,
	const bool stripDD,
	beacls::CudaStream* cudaStream
);

template<typename T>
__device__
inline T get_epsilon_base(T a = 0);
template<>
__device__
inline double get_epsilon_base(double) {
	return (double)1e-99;
}
template<>
__device__
inline float get_epsilon_base(float) {
	return (float)1e-15;	//!< T.B.D. It should be larger than sqrt(FLT_MIN)
}

template<typename T> inline
__device__
T calcSmooth(
	const T src_1,
	const T src_2,
	const T src_3,
	const int b1,
	const int b2,
	const int b3
) {
	T a = src_1 - 2 * src_2 + src_3;
	T b = b1 * src_1 + b2 * src_2 + b3 * src_3;
	return (T)((13. / 12.) * (a * a)
		+ (1. / 4.) * (b * b));
}
template<typename T> inline
__device__
T calcSmooth0(
	const T src_1,
	const T src_2,
	const T src_3
) {
	return calcSmooth(src_1, src_2, src_3, 1, -4, 3);
}
template<typename T> inline
__device__
T calcSmooth1(
	const T src_1,
	const T src_2,
	const T src_3
) {
	return calcSmooth(src_1, src_2, src_3, 1, 0, -1);
}
template<typename T> inline
__device__
T calcSmooth2(
	const T src_1,
	const T src_2,
	const T src_3
) {
	return calcSmooth(src_1, src_2, src_3, 3, -4, 1);
}
template<typename T> inline
__device__
T weightWENO(
	const T d0,
	const T d1,
	const T d2,
	const T s0,
	const T s1,
	const T s2,
	const T w0,
	const T w1,
	const T w2,
	const T epsilon
) {
	T s0_epsilon = s0 + epsilon;
	T s1_epsilon = s1 + epsilon;
	T s2_epsilon = s2 + epsilon;
	T alpha1 = w0 / (s0_epsilon * s0_epsilon);
	T alpha2 = w1 / (s1_epsilon * s1_epsilon);
	T alpha3 = w2 / (s2_epsilon * s2_epsilon);
	T sum = alpha1 + alpha2 + alpha3;
	T alpha1_d0 = alpha1 * d0;
	T alpha2_d1 = alpha2 * d1;
	T alpha3_d2 = alpha3 * d2;
	T alpha_d = alpha1_d0 + alpha2_d1 + alpha3_d2;
	T result = alpha_d / sum;
	return result;
}
__device__ inline
void kernel_dim0_EpsilonCalculationMethod_Constant_inline(
	FLOAT_TYPE* dst_deriv_l_ptr,
	FLOAT_TYPE* dst_deriv_r_ptr,
	const FLOAT_TYPE* DD0_ptr,
	const FLOAT_TYPE* dL0_ptr,
	const FLOAT_TYPE* dL1_ptr,
	const FLOAT_TYPE* dL2_ptr,
	const FLOAT_TYPE* dR0_ptr,
	const FLOAT_TYPE* dR1_ptr,
	const FLOAT_TYPE* dR2_ptr,
	const FLOAT_TYPE weightL0,
	const FLOAT_TYPE weightL1,
	const FLOAT_TYPE weightL2,
	const FLOAT_TYPE weightR0,
	const FLOAT_TYPE weightR1,
	const FLOAT_TYPE weightR2,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t src_target_dimension_loop_size,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t thread_length_z,
	const size_t thread_length_y,
	const size_t thread_length_x,
	const size_t blockIdx_y,
	const size_t blockIdx_x,
	const size_t blockDim_y,
	const size_t blockDim_x,
	const size_t threadIdx_z,
	const size_t threadIdx_y,
	const size_t threadIdx_x) {
	const size_t global_thraed_index_z = threadIdx_z;
	const size_t loop_index_z_base = global_thraed_index_z*thread_length_z;
	const size_t actual_thread_length_z = get_actual_length(num_of_slices, thread_length_z, loop_index_z_base);
	for (size_t loop_index_z = loop_index_z_base; loop_index_z < actual_thread_length_z + loop_index_z_base; ++loop_index_z) {
		const size_t dst_slice_offset = loop_index_z * slice_length;
		const size_t dst_slice_upperlimit = dst_slice_offset + slice_length;
		const size_t src_DD0_slice_offset = loop_index_z * loop_length * (first_dimension_loop_size + 5);
		const size_t global_thraed_index_y = blockIdx_y * blockDim_y + threadIdx_y;
		const size_t loop_index_y_base = global_thraed_index_y*thread_length_y;
		const size_t actual_thread_length_y = get_actual_length(loop_length, thread_length_y, loop_index_y_base);
		for (size_t loop_index_y = loop_index_y_base; loop_index_y < actual_thread_length_y + loop_index_y_base; ++loop_index_y) {
			const size_t global_thread_index_x = blockIdx_x * blockDim_x + threadIdx_x;
			const size_t loop_index_x_base = global_thread_index_x * thread_length_x;
			const size_t actual_thread_length_x = get_actual_length(src_target_dimension_loop_size, thread_length_x, loop_index_x_base);
			if (actual_thread_length_x > 0) {
				const size_t dst_offset = loop_index_y * first_dimension_loop_size + dst_slice_offset;
				const size_t src_D1_offset = loop_index_y * (first_dimension_loop_size + 5) + src_DD0_slice_offset;
				FLOAT_TYPE smooth_m1_0;
				FLOAT_TYPE smooth_m1_1;
				FLOAT_TYPE smooth_m1_2;
				FLOAT_TYPE D1_src_1;
				FLOAT_TYPE D1_src_2;
				FLOAT_TYPE D1_src_3;
				FLOAT_TYPE D1_src_4;
				//Prologue
				{
					const size_t loop_index_x = loop_index_x_base;
					const size_t src_D1_index = loop_index_x + src_D1_offset;
					const FLOAT_TYPE D1_src_0 = DD0_ptr[src_D1_index];
					D1_src_1 = DD0_ptr[src_D1_index + 1];
					D1_src_2 = DD0_ptr[src_D1_index + 2];
					D1_src_3 = DD0_ptr[src_D1_index + 3];
					D1_src_4 = DD0_ptr[src_D1_index + 4];
					smooth_m1_0 = calcSmooth0(D1_src_0, D1_src_1, D1_src_2);
					smooth_m1_1 = calcSmooth1(D1_src_1, D1_src_2, D1_src_3);
					smooth_m1_2 = calcSmooth2(D1_src_2, D1_src_3, D1_src_4);
				}
				for (size_t loop_index_x = loop_index_x_base; loop_index_x < actual_thread_length_x + loop_index_x_base; ++loop_index_x) {
					const size_t src_D1_index = loop_index_x + src_D1_offset;
					const size_t dst_index = loop_index_x + dst_offset;
					const FLOAT_TYPE D1_src_5 = DD0_ptr[src_D1_index + 5];
					const FLOAT_TYPE smooth_m0_0 = calcSmooth0(D1_src_1, D1_src_2, D1_src_3);
					const FLOAT_TYPE smooth_m0_1 = calcSmooth1(D1_src_2, D1_src_3, D1_src_4);
					const FLOAT_TYPE smooth_m0_2 = calcSmooth2(D1_src_3, D1_src_4, D1_src_5);
					const FLOAT_TYPE epsilon = (FLOAT_TYPE)1e-6;
					const size_t src_index = dst_index;
					if (dst_index < dst_slice_upperlimit) {
						dst_deriv_l_ptr[dst_index] = weightWENO(dL0_ptr[src_index], dL1_ptr[src_index], dL2_ptr[src_index], smooth_m1_0, smooth_m1_1, smooth_m1_2, weightL0, weightL1, weightL2, epsilon);
						dst_deriv_r_ptr[dst_index] = weightWENO(dR0_ptr[src_index], dR1_ptr[src_index], dR2_ptr[src_index], smooth_m0_0, smooth_m0_1, smooth_m0_2, weightR0, weightR1, weightR2, epsilon);
					}
					smooth_m1_0 = smooth_m0_0;
					smooth_m1_1 = smooth_m0_1;
					smooth_m1_2 = smooth_m0_2;
					D1_src_1 = D1_src_2;
					D1_src_2 = D1_src_3;
					D1_src_3 = D1_src_4;
					D1_src_4 = D1_src_5;
				}
			}
		}
	}
}

__device__ inline
void kernel_dim0_EpsilonCalculationMethod_maxOverNeighbor_inline(
	FLOAT_TYPE* dst_deriv_l_ptr,
	FLOAT_TYPE* dst_deriv_r_ptr,
	const FLOAT_TYPE* DD0_ptr,
	const FLOAT_TYPE* dL0_ptr,
	const FLOAT_TYPE* dL1_ptr,
	const FLOAT_TYPE* dL2_ptr,
	const FLOAT_TYPE* dR0_ptr,
	const FLOAT_TYPE* dR1_ptr,
	const FLOAT_TYPE* dR2_ptr,
	const FLOAT_TYPE weightL0,
	const FLOAT_TYPE weightL1,
	const FLOAT_TYPE weightL2,
	const FLOAT_TYPE weightR0,
	const FLOAT_TYPE weightR1,
	const FLOAT_TYPE weightR2,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t src_target_dimension_loop_size,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t thread_length_z,
	const size_t thread_length_y,
	const size_t thread_length_x,
	const size_t blockIdx_y,
	const size_t blockIdx_x,
	const size_t blockDim_y,
	const size_t blockDim_x,
	const size_t threadIdx_z,
	const size_t threadIdx_y,
	const size_t threadIdx_x) {
	const size_t global_thraed_index_z = threadIdx_z;
	const size_t loop_index_z_base = global_thraed_index_z*thread_length_z;
	const size_t actual_thread_length_z = get_actual_length(num_of_slices, thread_length_z, loop_index_z_base);
	for (size_t loop_index_z = loop_index_z_base; loop_index_z < actual_thread_length_z + loop_index_z_base; ++loop_index_z) {
		const size_t dst_slice_offset = loop_index_z * slice_length;
		const size_t dst_slice_upperlimit = dst_slice_offset + slice_length;
		const size_t src_DD0_slice_offset = loop_index_z * loop_length * (first_dimension_loop_size+5);
		const size_t global_thraed_index_y = blockIdx_y * blockDim_y + threadIdx_y;
		const size_t loop_index_y_base = global_thraed_index_y*thread_length_y;
		const size_t actual_thread_length_y = get_actual_length(loop_length, thread_length_y, loop_index_y_base);
		for (size_t loop_index_y = loop_index_y_base; loop_index_y < actual_thread_length_y + loop_index_y_base; ++loop_index_y) {
			const size_t global_thread_index_x = blockIdx_x * blockDim_x + threadIdx_x;
			const size_t loop_index_x_base = global_thread_index_x * thread_length_x;
			const size_t actual_thread_length_x = get_actual_length(src_target_dimension_loop_size, thread_length_x, loop_index_x_base);
			if (actual_thread_length_x > 0) {
				const size_t dst_offset = loop_index_y * first_dimension_loop_size + dst_slice_offset;
				const size_t src_D1_offset = loop_index_y * (first_dimension_loop_size + 5) + src_DD0_slice_offset;
				FLOAT_TYPE smooth_m1_0;
				FLOAT_TYPE smooth_m1_1;
				FLOAT_TYPE smooth_m1_2;
				FLOAT_TYPE D1_src_1;
				FLOAT_TYPE D1_src_2;
				FLOAT_TYPE D1_src_3;
				FLOAT_TYPE D1_src_4;
				FLOAT_TYPE pow_D1_src_0;
				FLOAT_TYPE pow_D1_src_1;
				FLOAT_TYPE pow_D1_src_2;
				FLOAT_TYPE pow_D1_src_3;
				FLOAT_TYPE pow_D1_src_4;
				//Prologue
				{
					const size_t loop_index_x = loop_index_x_base;
					const size_t src_D1_index = loop_index_x + src_D1_offset;
					const FLOAT_TYPE D1_src_0 = DD0_ptr[src_D1_index];
					D1_src_1 = DD0_ptr[src_D1_index + 1];
					D1_src_2 = DD0_ptr[src_D1_index + 2];
					D1_src_3 = DD0_ptr[src_D1_index + 3];
					D1_src_4 = DD0_ptr[src_D1_index + 4];
					smooth_m1_0 = calcSmooth0(D1_src_0, D1_src_1, D1_src_2);
					smooth_m1_1 = calcSmooth1(D1_src_1, D1_src_2, D1_src_3);
					smooth_m1_2 = calcSmooth2(D1_src_2, D1_src_3, D1_src_4);
					pow_D1_src_0 = D1_src_0 * D1_src_0;
					pow_D1_src_1 = D1_src_1 * D1_src_1;
					pow_D1_src_2 = D1_src_2 * D1_src_2;
					pow_D1_src_3 = D1_src_3 * D1_src_3;
					pow_D1_src_4 = D1_src_4 * D1_src_4;
				}
				for (size_t loop_index_x = loop_index_x_base; loop_index_x < actual_thread_length_x + loop_index_x_base; ++loop_index_x) {
					const size_t src_D1_index = loop_index_x + src_D1_offset;
					const size_t dst_index = loop_index_x + dst_offset;
					const FLOAT_TYPE D1_src_5 = DD0_ptr[src_D1_index + 5];
					const FLOAT_TYPE smooth_m0_0 = calcSmooth0(D1_src_1, D1_src_2, D1_src_3);
					const FLOAT_TYPE smooth_m0_1 = calcSmooth1(D1_src_2, D1_src_3, D1_src_4);
					const FLOAT_TYPE smooth_m0_2 = calcSmooth2(D1_src_3, D1_src_4, D1_src_5);
					const FLOAT_TYPE pow_D1_src_5 = D1_src_5 * D1_src_5;
					const FLOAT_TYPE max_1_2 = max_float_type(pow_D1_src_1, pow_D1_src_2);
					const FLOAT_TYPE max_3_4 = max_float_type(pow_D1_src_3, pow_D1_src_4);
					const FLOAT_TYPE max_1_2_3_4 = max_float_type(max_1_2, max_3_4);
					const FLOAT_TYPE maxOverNeighborD1squaredL = max_float_type(max_1_2_3_4, pow_D1_src_0);
					const FLOAT_TYPE maxOverNeighborD1squaredR = max_float_type(max_1_2_3_4, pow_D1_src_5);
					const FLOAT_TYPE epsilonL = (FLOAT_TYPE)(1e-6 * maxOverNeighborD1squaredL + get_epsilon_base<FLOAT_TYPE>());
					const FLOAT_TYPE epsilonR = (FLOAT_TYPE)(1e-6 * maxOverNeighborD1squaredR + get_epsilon_base<FLOAT_TYPE>());
					const size_t src_index = dst_index;
					if (dst_index < dst_slice_upperlimit) {
						dst_deriv_l_ptr[dst_index] = weightWENO(dL0_ptr[src_index], dL1_ptr[src_index], dL2_ptr[src_index], smooth_m1_0, smooth_m1_1, smooth_m1_2, weightL0, weightL1, weightL2, epsilonL);
						dst_deriv_r_ptr[dst_index] = weightWENO(dR0_ptr[src_index], dR1_ptr[src_index], dR2_ptr[src_index], smooth_m0_0, smooth_m0_1, smooth_m0_2, weightR0, weightR1, weightR2, epsilonR);
					}
					smooth_m1_0 = smooth_m0_0;
					smooth_m1_1 = smooth_m0_1;
					smooth_m1_2 = smooth_m0_2;
					D1_src_1 = D1_src_2;
					D1_src_2 = D1_src_3;
					D1_src_3 = D1_src_4;
					D1_src_4 = D1_src_5;
					pow_D1_src_0 = pow_D1_src_1;
					pow_D1_src_1 = pow_D1_src_2;
					pow_D1_src_2 = pow_D1_src_3;
					pow_D1_src_3 = pow_D1_src_4;
					pow_D1_src_4 = pow_D1_src_5;
				}
			}
		}
	}
}

void UpwindFirstWENO5a_execute_dim0_cuda
(
	FLOAT_TYPE* dst_deriv_l_ptr,
	FLOAT_TYPE* dst_deriv_r_ptr,
	const FLOAT_TYPE* DD0_0_ptr,
	const FLOAT_TYPE* dL0_ptr,
	const FLOAT_TYPE* dL1_ptr,
	const FLOAT_TYPE* dL2_ptr,
	const FLOAT_TYPE* dR0_ptr,
	const FLOAT_TYPE* dR1_ptr,
	const FLOAT_TYPE* dR2_ptr,
	const FLOAT_TYPE weightL0,
	const FLOAT_TYPE weightL1,
	const FLOAT_TYPE weightL2,
	const FLOAT_TYPE weightR0,
	const FLOAT_TYPE weightR1,
	const FLOAT_TYPE weightR2,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t src_target_dimension_loop_size,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const levelset::EpsilonCalculationMethod_Type epsilonCalculationMethod_Type,
	beacls::CudaStream* cudaStream
);

__device__ inline
void kernel_dim1_EpsilonCalculationMethod_Constant_inline(
	FLOAT_TYPE* dst_deriv_l_ptr,
	FLOAT_TYPE* dst_deriv_r_ptr,
	const FLOAT_TYPE* DD0_ptr,
	const FLOAT_TYPE* dL0_ptr,
	const FLOAT_TYPE* dL1_ptr,
	const FLOAT_TYPE* dL2_ptr,
	const FLOAT_TYPE* dR0_ptr,
	const FLOAT_TYPE* dR1_ptr,
	const FLOAT_TYPE* dR2_ptr,
	const FLOAT_TYPE weightL0,
	const FLOAT_TYPE weightL1,
	const FLOAT_TYPE weightL2,
	const FLOAT_TYPE weightR0,
	const FLOAT_TYPE weightR1,
	const FLOAT_TYPE weightR2,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t DD0_slice_size,
	const size_t thread_length_z,
	const size_t thread_length_y,
	const size_t thread_length_x,
	const size_t blockIdx_y,
	const size_t blockIdx_x,
	const size_t blockDim_y,
	const size_t blockDim_x,
	const size_t threadIdx_z,
	const size_t threadIdx_y,
	const size_t threadIdx_x) {
	const size_t global_thraed_index_z = threadIdx_z;
	const size_t loop_index_z_base = global_thraed_index_z*thread_length_z;
	const size_t actual_thread_length_z = get_actual_length(num_of_slices, thread_length_z, loop_index_z_base);
	for (size_t loop_index_z = loop_index_z_base; loop_index_z < actual_thread_length_z + loop_index_z_base; ++loop_index_z) {
		const size_t dst_slice_offset = loop_index_z * slice_length;
		const size_t src_dLdR_slice_offset = dst_slice_offset;
		const size_t src_DD0_slice_offset = loop_index_z * DD0_slice_size;
		const size_t dst_slice_upperlimit = dst_slice_offset + slice_length;
		const size_t global_thraed_index_y = blockIdx_y * blockDim_y + threadIdx_y;
		const size_t loop_index_y_base = global_thraed_index_y*thread_length_y;
		const size_t actual_thread_length_y = get_actual_length(loop_length, thread_length_y, loop_index_y_base);
		if (actual_thread_length_y > 0) {
			const size_t global_thread_index_x = blockIdx_x * blockDim_x + threadIdx_x;
			const size_t loop_index_x_base = global_thread_index_x * thread_length_x;
			const size_t actual_thread_length_x = get_actual_length(first_dimension_loop_size, thread_length_x, loop_index_x_base);
			const size_t loop_base_offset = loop_index_y_base*first_dimension_loop_size;
			for (size_t fdl_index = loop_index_x_base; fdl_index < actual_thread_length_x+ loop_index_x_base; ++fdl_index) {
				// Need to figure out which approximation has the least oscillation.
				// Note that L and R in this section refer to neighboring divided
				// difference entries, not to left and right approximations.
				FLOAT_TYPE smooth_m1_0;
				FLOAT_TYPE smooth_m1_1;
				FLOAT_TYPE smooth_m1_2;
				FLOAT_TYPE D1_src_1;
				FLOAT_TYPE D1_src_2;
				FLOAT_TYPE D1_src_3;
				FLOAT_TYPE D1_src_4;
				//Prologue
				{
					size_t src_DD0_offset = loop_base_offset + src_DD0_slice_offset;
					size_t src_DD0_index = fdl_index + src_DD0_offset;
					FLOAT_TYPE D1_src_0 = DD0_ptr[src_DD0_index];
					D1_src_1 = DD0_ptr[src_DD0_index + first_dimension_loop_size * 1];
					D1_src_2 = DD0_ptr[src_DD0_index + first_dimension_loop_size * 2];
					D1_src_3 = DD0_ptr[src_DD0_index + first_dimension_loop_size * 3];
					D1_src_4 = DD0_ptr[src_DD0_index + first_dimension_loop_size * 4];
					smooth_m1_0 = calcSmooth0(D1_src_0, D1_src_1, D1_src_2);
					smooth_m1_1 = calcSmooth1(D1_src_1, D1_src_2, D1_src_3);
					smooth_m1_2 = calcSmooth2(D1_src_2, D1_src_3, D1_src_4);
				}
				for (size_t loop_index_y = loop_index_y_base; loop_index_y < actual_thread_length_y + loop_index_y_base; ++loop_index_y) {
					size_t dst_offset = loop_index_y * first_dimension_loop_size + dst_slice_offset;
					size_t src_DD0_offset = loop_index_y * first_dimension_loop_size + src_DD0_slice_offset;
					size_t src_dLdR_offset = loop_index_y * first_dimension_loop_size + src_dLdR_slice_offset;
					size_t src_DD0_index = fdl_index + src_DD0_offset;
					size_t src_dLdR_index = fdl_index + src_dLdR_offset;
					FLOAT_TYPE D1_src_5 = DD0_ptr[src_DD0_index + first_dimension_loop_size * 5];
					FLOAT_TYPE smooth_m0_0 = calcSmooth0(D1_src_1, D1_src_2, D1_src_3);
					FLOAT_TYPE smooth_m0_1 = calcSmooth1(D1_src_2, D1_src_3, D1_src_4);
					FLOAT_TYPE smooth_m0_2 = calcSmooth2(D1_src_3, D1_src_4, D1_src_5);
					FLOAT_TYPE epsilon = (FLOAT_TYPE)1e-6;
					size_t dst_index = fdl_index + dst_offset;
					if (dst_index < dst_slice_upperlimit) {
						dst_deriv_l_ptr[dst_index] = weightWENO(dL0_ptr[src_dLdR_index], dL1_ptr[src_dLdR_index], dL2_ptr[src_dLdR_index], smooth_m1_0, smooth_m1_1, smooth_m1_2, weightL0, weightL1, weightL2, epsilon);
						dst_deriv_r_ptr[dst_index] = weightWENO(dR0_ptr[src_dLdR_index], dR1_ptr[src_dLdR_index], dR2_ptr[src_dLdR_index], smooth_m0_0, smooth_m0_1, smooth_m0_2, weightR0, weightR1, weightR2, epsilon);
					}
					smooth_m1_0 = smooth_m0_0;
					smooth_m1_1 = smooth_m0_1;
					smooth_m1_2 = smooth_m0_2;
					D1_src_1 = D1_src_2;
					D1_src_2 = D1_src_3;
					D1_src_3 = D1_src_4;
					D1_src_4 = D1_src_5;
				}
			}
		}
	}
}

__device__ inline
void kernel_dim1_EpsilonCalculationMethod_maxOverNeighbor_inline(
	FLOAT_TYPE* dst_deriv_l_ptr,
	FLOAT_TYPE* dst_deriv_r_ptr,
	const FLOAT_TYPE* DD0_ptr,
	const FLOAT_TYPE* dL0_ptr,
	const FLOAT_TYPE* dL1_ptr,
	const FLOAT_TYPE* dL2_ptr,
	const FLOAT_TYPE* dR0_ptr,
	const FLOAT_TYPE* dR1_ptr,
	const FLOAT_TYPE* dR2_ptr,
	const FLOAT_TYPE weightL0,
	const FLOAT_TYPE weightL1,
	const FLOAT_TYPE weightL2,
	const FLOAT_TYPE weightR0,
	const FLOAT_TYPE weightR1,
	const FLOAT_TYPE weightR2,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t DD0_slice_size,
	const size_t thread_length_z,
	const size_t thread_length_y,
	const size_t thread_length_x,
	const size_t blockIdx_y,
	const size_t blockIdx_x,
	const size_t blockDim_y,
	const size_t blockDim_x,
	const size_t threadIdx_z,
	const size_t threadIdx_y,
	const size_t threadIdx_x) {
	const size_t global_thraed_index_z = threadIdx_z;
	const size_t loop_index_z_base = global_thraed_index_z*thread_length_z;
	const size_t actual_thread_length_z = get_actual_length(num_of_slices, thread_length_z, loop_index_z_base);
	for (size_t loop_index_z = loop_index_z_base; loop_index_z < actual_thread_length_z + loop_index_z_base; ++loop_index_z) {
		const size_t dst_slice_offset = loop_index_z * slice_length;
		const size_t src_dLdR_slice_offset = dst_slice_offset;
		const size_t src_DD0_slice_offset = loop_index_z * DD0_slice_size;
		const size_t dst_slice_upperlimit = dst_slice_offset + slice_length;
		const size_t global_thraed_index_y = blockIdx_y * blockDim_y + threadIdx_y;
		const size_t loop_index_y_base = global_thraed_index_y*thread_length_y;
		const size_t actual_thread_length_y = get_actual_length(loop_length, thread_length_y, loop_index_y_base);
		if (actual_thread_length_y > 0) {
			const size_t global_thread_index_x = blockIdx_x * blockDim_x + threadIdx_x;
			const size_t loop_index_x_base = global_thread_index_x * thread_length_x;
			const size_t actual_thread_length_x = get_actual_length(first_dimension_loop_size, thread_length_x, loop_index_x_base);
			const size_t loop_base_offset = loop_index_y_base*first_dimension_loop_size;
			for (size_t fdl_index = loop_index_x_base; fdl_index < actual_thread_length_x + loop_index_x_base; ++fdl_index) {
				// Need to figure out which approximation has the least oscillation.
				// Note that L and R in this section refer to neighboring divided
				// difference entries, not to left and right approximations.
				FLOAT_TYPE smooth_m1_0;
				FLOAT_TYPE smooth_m1_1;
				FLOAT_TYPE smooth_m1_2;
				FLOAT_TYPE D1_src_1;
				FLOAT_TYPE D1_src_2;
				FLOAT_TYPE D1_src_3;
				FLOAT_TYPE D1_src_4;
				FLOAT_TYPE pow_D1_src_0;
				FLOAT_TYPE pow_D1_src_1;
				FLOAT_TYPE pow_D1_src_2;
				FLOAT_TYPE pow_D1_src_3;
				FLOAT_TYPE pow_D1_src_4;
				//Prologue
				{
					size_t src_DD0_offset = loop_base_offset + src_DD0_slice_offset;
					size_t src_DD0_index = fdl_index + src_DD0_offset;
					FLOAT_TYPE D1_src_0 = DD0_ptr[src_DD0_index];
					D1_src_1 = DD0_ptr[src_DD0_index + first_dimension_loop_size * 1];
					D1_src_2 = DD0_ptr[src_DD0_index + first_dimension_loop_size * 2];
					D1_src_3 = DD0_ptr[src_DD0_index + first_dimension_loop_size * 3];
					D1_src_4 = DD0_ptr[src_DD0_index + first_dimension_loop_size * 4];
					smooth_m1_0 = calcSmooth0(D1_src_0, D1_src_1, D1_src_2);
					smooth_m1_1 = calcSmooth1(D1_src_1, D1_src_2, D1_src_3);
					smooth_m1_2 = calcSmooth2(D1_src_2, D1_src_3, D1_src_4);
					pow_D1_src_0 = D1_src_0 * D1_src_0;
					pow_D1_src_1 = D1_src_1 * D1_src_1;
					pow_D1_src_2 = D1_src_2 * D1_src_2;
					pow_D1_src_3 = D1_src_3 * D1_src_3;
					pow_D1_src_4 = D1_src_4 * D1_src_4;
				}
				for (size_t loop_index_y = loop_index_y_base; loop_index_y < actual_thread_length_y+ loop_index_y_base; ++loop_index_y) {
					size_t dst_offset = loop_index_y * first_dimension_loop_size + dst_slice_offset;
					size_t src_DD0_offset = loop_index_y * first_dimension_loop_size + src_DD0_slice_offset;
					size_t src_dLdR_offset = loop_index_y * first_dimension_loop_size + src_dLdR_slice_offset;
					size_t src_DD0_index = fdl_index + src_DD0_offset;
					size_t src_dLdR_index = fdl_index + src_dLdR_offset;
					FLOAT_TYPE D1_src_5 = DD0_ptr[src_DD0_index + first_dimension_loop_size * 5];
					FLOAT_TYPE smooth_m0_0 = calcSmooth0(D1_src_1, D1_src_2, D1_src_3);
					FLOAT_TYPE smooth_m0_1 = calcSmooth1(D1_src_2, D1_src_3, D1_src_4);
					FLOAT_TYPE smooth_m0_2 = calcSmooth2(D1_src_3, D1_src_4, D1_src_5);
					FLOAT_TYPE pow_D1_src_5 = D1_src_5 * D1_src_5;
					FLOAT_TYPE max_1_2 = max_float_type(pow_D1_src_1, pow_D1_src_2);
					FLOAT_TYPE max_3_4 = max_float_type(pow_D1_src_3, pow_D1_src_4);
					FLOAT_TYPE max_1_2_3_4 = max_float_type(max_1_2, max_3_4);
					FLOAT_TYPE maxOverNeighborD1squaredL = max_float_type(max_1_2_3_4, pow_D1_src_0);
					FLOAT_TYPE maxOverNeighborD1squaredR = max_float_type(max_1_2_3_4, pow_D1_src_5);
					FLOAT_TYPE epsilonL = (FLOAT_TYPE)(1e-6 * maxOverNeighborD1squaredL + get_epsilon_base<FLOAT_TYPE>());
					FLOAT_TYPE epsilonR = (FLOAT_TYPE)(1e-6 * maxOverNeighborD1squaredR + get_epsilon_base<FLOAT_TYPE>());
					size_t dst_index = fdl_index + dst_offset;
					if (dst_index < dst_slice_upperlimit) {
						dst_deriv_l_ptr[dst_index] = weightWENO(dL0_ptr[src_dLdR_index], dL1_ptr[src_dLdR_index], dL2_ptr[src_dLdR_index], smooth_m1_0, smooth_m1_1, smooth_m1_2, weightL0, weightL1, weightL2, epsilonL);
						dst_deriv_r_ptr[dst_index] = weightWENO(dR0_ptr[src_dLdR_index], dR1_ptr[src_dLdR_index], dR2_ptr[src_dLdR_index], smooth_m0_0, smooth_m0_1, smooth_m0_2, weightR0, weightR1, weightR2, epsilonR);
					}
					smooth_m1_0 = smooth_m0_0;
					smooth_m1_1 = smooth_m0_1;
					smooth_m1_2 = smooth_m0_2;
					D1_src_1 = D1_src_2;
					D1_src_2 = D1_src_3;
					D1_src_3 = D1_src_4;
					D1_src_4 = D1_src_5;
					pow_D1_src_0 = pow_D1_src_1;
					pow_D1_src_1 = pow_D1_src_2;
					pow_D1_src_2 = pow_D1_src_3;
					pow_D1_src_3 = pow_D1_src_4;
					pow_D1_src_4 = pow_D1_src_5;
				}
			}
		}
	}
}

void UpwindFirstWENO5a_execute_dim1_cuda
(
	FLOAT_TYPE* dst_deriv_l_ptr,
	FLOAT_TYPE* dst_deriv_r_ptr,
	const FLOAT_TYPE* DD0_0_ptr,
	const FLOAT_TYPE* dL0_ptr,
	const FLOAT_TYPE* dL1_ptr,
	const FLOAT_TYPE* dL2_ptr,
	const FLOAT_TYPE* dR0_ptr,
	const FLOAT_TYPE* dR1_ptr,
	const FLOAT_TYPE* dR2_ptr,
	const FLOAT_TYPE weightL0,
	const FLOAT_TYPE weightL1,
	const FLOAT_TYPE weightL2,
	const FLOAT_TYPE weightR0,
	const FLOAT_TYPE weightR1,
	const FLOAT_TYPE weightR2,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t DD0_slice_size,
	const levelset::EpsilonCalculationMethod_Type epsilonCalculationMethod_Type,
	beacls::CudaStream* cudaStream

);

__device__ inline
void kernel_dimLET2_EpsilonCalculationMethod_Constant_inline(
	FLOAT_TYPE* dst_deriv_l_ptr,
	FLOAT_TYPE* dst_deriv_r_ptr,
	const FLOAT_TYPE* DD0_0_ptr,
	const FLOAT_TYPE* DD1_0_ptr,
	const FLOAT_TYPE* DD2_0_ptr,
	const FLOAT_TYPE* DD3_0_ptr,
	const FLOAT_TYPE* DD4_0_ptr,
	const FLOAT_TYPE* DD5_0_ptr,
	const FLOAT_TYPE* dL0_ptr,
	const FLOAT_TYPE* dL1_ptr,
	const FLOAT_TYPE* dL2_ptr,
	const FLOAT_TYPE* dR0_ptr,
	const FLOAT_TYPE* dR1_ptr,
	const FLOAT_TYPE* dR2_ptr,
	const FLOAT_TYPE weightL0,
	const FLOAT_TYPE weightL1,
	const FLOAT_TYPE weightL2,
	const FLOAT_TYPE weightR0,
	const FLOAT_TYPE weightR1,
	const FLOAT_TYPE weightR2,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t thread_length_z,
	const size_t thread_length_y,
	const size_t thread_length_x,
	const size_t blockIdx_y,
	const size_t blockIdx_x,
	const size_t blockDim_y,
	const size_t blockDim_x,
	const size_t threadIdx_z,
	const size_t threadIdx_y,
	const size_t threadIdx_x) {
	const size_t global_thraed_index_z = threadIdx_z;
	const size_t loop_index_z_base = global_thraed_index_z*thread_length_z;
	const size_t actual_thread_length_z = get_actual_length(num_of_slices, thread_length_z, loop_index_z_base);
	for (size_t loop_index_z = loop_index_z_base; loop_index_z < actual_thread_length_z + loop_index_z_base; ++loop_index_z) {
		const size_t dst_slice_offset = loop_index_z * slice_length;
		const size_t global_thraed_index_y = blockIdx_y * blockDim_y + threadIdx_y;
		const size_t loop_index_y_base = global_thraed_index_y*thread_length_y;
		const size_t actual_thread_length_y = get_actual_length(loop_length, thread_length_y, loop_index_y_base);
		for (size_t loop_index_y = loop_index_y_base; loop_index_y < actual_thread_length_y + loop_index_y_base; ++loop_index_y) {
			const size_t dst_offset = loop_index_y * first_dimension_loop_size + dst_slice_offset;
			const size_t global_thread_index_x = blockIdx_x * blockDim_x + threadIdx_x;
			const size_t loop_index_x_base = global_thread_index_x * thread_length_x;
			const size_t actual_thread_length_x = get_actual_length(first_dimension_loop_size, thread_length_x, loop_index_x_base);
			for (size_t loop_index = 0; loop_index < actual_thread_length_x; ++loop_index) {
				const size_t first_dimension_loop_index = loop_index + loop_index_x_base;
				const size_t src_index = first_dimension_loop_index + dst_offset;
				const FLOAT_TYPE D1_src_0 = DD0_0_ptr[src_index];
				const FLOAT_TYPE D1_src_1 = DD1_0_ptr[src_index];
				const FLOAT_TYPE D1_src_2 = DD2_0_ptr[src_index];
				const FLOAT_TYPE D1_src_3 = DD3_0_ptr[src_index];
				const FLOAT_TYPE D1_src_4 = DD4_0_ptr[src_index];
				const FLOAT_TYPE D1_src_5 = DD5_0_ptr[src_index];
				const FLOAT_TYPE smoothL_0 = calcSmooth0(D1_src_0, D1_src_1, D1_src_2);
				const FLOAT_TYPE smoothL_1 = calcSmooth1(D1_src_1, D1_src_2, D1_src_3);
				const FLOAT_TYPE smoothL_2 = calcSmooth2(D1_src_2, D1_src_3, D1_src_4);
				const FLOAT_TYPE smoothR_0 = calcSmooth0(D1_src_1, D1_src_2, D1_src_3);
				const FLOAT_TYPE smoothR_1 = calcSmooth1(D1_src_2, D1_src_3, D1_src_4);
				const FLOAT_TYPE smoothR_2 = calcSmooth2(D1_src_3, D1_src_4, D1_src_5);
				const FLOAT_TYPE epsilon = (FLOAT_TYPE)1e-6;
				const size_t dst_index = src_index;
				dst_deriv_l_ptr[dst_index] = weightWENO(dL0_ptr[src_index], dL1_ptr[src_index], dL2_ptr[src_index], smoothL_0, smoothL_1, smoothL_2, weightL0, weightL1, weightL2, epsilon);
				dst_deriv_r_ptr[dst_index] = weightWENO(dR0_ptr[src_index], dR1_ptr[src_index], dR2_ptr[src_index], smoothR_0, smoothR_1, smoothR_2, weightR0, weightR1, weightR2, epsilon);
			}
		}
	}
}

__device__ inline
void kernel_dimLET2_EpsilonCalculationMethod_maxOverNeighbor_inline(
	FLOAT_TYPE* dst_deriv_l_ptr,
	FLOAT_TYPE* dst_deriv_r_ptr,
	const FLOAT_TYPE* DD0_0_ptr,
	const FLOAT_TYPE* DD1_0_ptr,
	const FLOAT_TYPE* DD2_0_ptr,
	const FLOAT_TYPE* DD3_0_ptr,
	const FLOAT_TYPE* DD4_0_ptr,
	const FLOAT_TYPE* DD5_0_ptr,
	const FLOAT_TYPE* dL0_ptr,
	const FLOAT_TYPE* dL1_ptr,
	const FLOAT_TYPE* dL2_ptr,
	const FLOAT_TYPE* dR0_ptr,
	const FLOAT_TYPE* dR1_ptr,
	const FLOAT_TYPE* dR2_ptr,
	const FLOAT_TYPE weightL0,
	const FLOAT_TYPE weightL1,
	const FLOAT_TYPE weightL2,
	const FLOAT_TYPE weightR0,
	const FLOAT_TYPE weightR1,
	const FLOAT_TYPE weightR2,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const size_t thread_length_z,
	const size_t thread_length_y,
	const size_t thread_length_x,
	const size_t blockIdx_y,
	const size_t blockIdx_x,
	const size_t blockDim_y,
	const size_t blockDim_x,
	const size_t threadIdx_z,
	const size_t threadIdx_y,
	const size_t threadIdx_x) {
	const size_t global_thraed_index_z = threadIdx_z;
	const size_t loop_index_z_base = global_thraed_index_z*thread_length_z;
	const size_t actual_thread_length_z = get_actual_length(num_of_slices, thread_length_z, loop_index_z_base);
	for (size_t loop_index_z = loop_index_z_base; loop_index_z < actual_thread_length_z + loop_index_z_base; ++loop_index_z) {
		const size_t dst_slice_offset = loop_index_z * slice_length;
		const size_t global_thraed_index_y = blockIdx_y * blockDim_y + threadIdx_y;
		const size_t loop_index_y_base = global_thraed_index_y*thread_length_y;
		const size_t actual_thread_length_y = get_actual_length(loop_length, thread_length_y, loop_index_y_base);
		for (size_t loop_index_y = loop_index_y_base; loop_index_y < actual_thread_length_y + loop_index_y_base; ++loop_index_y) {
			const size_t dst_offset = loop_index_y * first_dimension_loop_size + dst_slice_offset;
			const size_t global_thread_index_x = blockIdx_x * blockDim_x + threadIdx_x;
			const size_t loop_index_x_base = global_thread_index_x * thread_length_x;
			const size_t actual_thread_length_x = get_actual_length(first_dimension_loop_size, thread_length_x, loop_index_x_base);
			for (size_t loop_index = 0; loop_index < actual_thread_length_x; ++loop_index) {
				const size_t first_dimension_loop_index = loop_index + loop_index_x_base;
				const size_t src_index = first_dimension_loop_index + dst_offset;
				const FLOAT_TYPE D1_src_0 = DD0_0_ptr[src_index];
				const FLOAT_TYPE D1_src_1 = DD1_0_ptr[src_index];
				const FLOAT_TYPE D1_src_2 = DD2_0_ptr[src_index];
				const FLOAT_TYPE D1_src_3 = DD3_0_ptr[src_index];
				const FLOAT_TYPE D1_src_4 = DD4_0_ptr[src_index];
				const FLOAT_TYPE D1_src_5 = DD5_0_ptr[src_index];
				const FLOAT_TYPE smoothL_0 = calcSmooth0(D1_src_0, D1_src_1, D1_src_2);
				const FLOAT_TYPE smoothL_1 = calcSmooth1(D1_src_1, D1_src_2, D1_src_3);
				const FLOAT_TYPE smoothL_2 = calcSmooth2(D1_src_2, D1_src_3, D1_src_4);
				const FLOAT_TYPE smoothR_0 = calcSmooth0(D1_src_1, D1_src_2, D1_src_3);
				const FLOAT_TYPE smoothR_1 = calcSmooth1(D1_src_2, D1_src_3, D1_src_4);
				const FLOAT_TYPE smoothR_2 = calcSmooth2(D1_src_3, D1_src_4, D1_src_5);
				const FLOAT_TYPE pow_D1_src_0 = D1_src_0 * D1_src_0;
				const FLOAT_TYPE pow_D1_src_1 = D1_src_1 * D1_src_1;
				const FLOAT_TYPE pow_D1_src_2 = D1_src_2 * D1_src_2;
				const FLOAT_TYPE pow_D1_src_3 = D1_src_3 * D1_src_3;
				const FLOAT_TYPE pow_D1_src_4 = D1_src_4 * D1_src_4;
				const FLOAT_TYPE pow_D1_src_5 = D1_src_5 * D1_src_5;
				const FLOAT_TYPE max_1_2 = max_float_type(pow_D1_src_1, pow_D1_src_2);
				const FLOAT_TYPE max_3_4 = max_float_type(pow_D1_src_3, pow_D1_src_4);
				const FLOAT_TYPE max_1_2_3_4 = max_float_type(max_1_2, max_3_4);
				const FLOAT_TYPE maxOverNeighborD1squaredL = max_float_type(max_1_2_3_4, pow_D1_src_0);
				const FLOAT_TYPE maxOverNeighborD1squaredR = max_float_type(max_1_2_3_4, pow_D1_src_5);
				const FLOAT_TYPE epsilonL = (FLOAT_TYPE)(1e-6 * maxOverNeighborD1squaredL + get_epsilon_base<FLOAT_TYPE>());
				const FLOAT_TYPE epsilonR = (FLOAT_TYPE)(1e-6 * maxOverNeighborD1squaredR + get_epsilon_base<FLOAT_TYPE>());
				const size_t dst_index = src_index;
				dst_deriv_l_ptr[dst_index] = weightWENO(dL0_ptr[src_index], dL1_ptr[src_index], dL2_ptr[src_index], smoothL_0, smoothL_1, smoothL_2, weightL0, weightL1, weightL2, epsilonL);
				dst_deriv_r_ptr[dst_index] = weightWENO(dR0_ptr[src_index], dR1_ptr[src_index], dR2_ptr[src_index], smoothR_0, smoothR_1, smoothR_2, weightR0, weightR1, weightR2, epsilonR);
			}
		}
	}
}

void UpwindFirstWENO5a_execute_dimLET2_cuda
(
	FLOAT_TYPE* dst_deriv_l_ptr,
	FLOAT_TYPE* dst_deriv_r_ptr,
	const FLOAT_TYPE* DD0_0_ptr,
	const FLOAT_TYPE* DD1_0_ptr,
	const FLOAT_TYPE* DD2_0_ptr,
	const FLOAT_TYPE* DD3_0_ptr,
	const FLOAT_TYPE* DD4_0_ptr,
	const FLOAT_TYPE* DD5_0_ptr,
	const FLOAT_TYPE* dL0_ptr,
	const FLOAT_TYPE* dL1_ptr,
	const FLOAT_TYPE* dL2_ptr,
	const FLOAT_TYPE* dR0_ptr,
	const FLOAT_TYPE* dR1_ptr,
	const FLOAT_TYPE* dR2_ptr,
	const FLOAT_TYPE weightL0,
	const FLOAT_TYPE weightL1,
	const FLOAT_TYPE weightL2,
	const FLOAT_TYPE weightR0,
	const FLOAT_TYPE weightR1,
	const FLOAT_TYPE weightR2,
	const size_t num_of_slices,
	const size_t loop_length,
	const size_t first_dimension_loop_size,
	const size_t slice_length,
	const levelset::EpsilonCalculationMethod_Type epsilonCalculationMethod_Type,
	beacls::CudaStream* cudaStream
																		      
     );




#endif	/* __UpwindFirstWENO5a_cuda_hpp__ */
