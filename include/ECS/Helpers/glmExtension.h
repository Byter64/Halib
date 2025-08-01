#pragma once
#include "glm/glm.hpp"

namespace glm
{
	
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR mat<3, 3, T, Q> translate(mat<3, 3, T, Q> const& m, vec<2, T, Q> const& v)
	{
		mat<3, 3, T, Q> Result(m);
		Result[2] = m[0] * v[0] + m[1] * v[1] + m[2];
		return Result;
	}

	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER mat<3, 3, T, Q> scale(mat<3, 3, T, Q> const& m, vec<2, T, Q> const& v)
	{
		mat<3, 3, T, Q> Result;
		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2];
		return Result;
	}
} // namespace glm
