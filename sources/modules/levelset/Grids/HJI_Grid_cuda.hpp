#ifndef __HJI_Grid_cuda_hpp__
#define __HJI_Grid_cuda_hpp__
#include <typedef.hpp>
#include <cuda_macro.hpp>
#include <Core/UVec.hpp>
void HJI_Grid_calc_xs_execute_cuda
(
	beacls::UVec& x_uvec,
	const beacls::UVec& v_uvec,
	const size_t dimension,
	const size_t start_index,
	const size_t loop_length,
	const size_t stride,
	const std::vector<size_t>& Ns
);
void HJI_Grid_repeat_cuda
(
	beacls::UVec& dst,
	const beacls::UVec& src,
	const size_t dimension,
	const size_t start_index,
	const size_t loop_length,
	const size_t stride,
	const size_t dim_length
);
#endif	/* __HJI_Grid_cuda_hpp__ */
