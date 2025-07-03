#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>

namespace Halib
{
	typedef glm::ivec2 VecI2; //A typedef for glm::ivec2 (OpenGL Mathematics)
	typedef glm::ivec3 VecI3; //A typedef for glm::ivec3 (OpenGL Mathematics)
	typedef glm::ivec4 VecI4; //A typedef for glm::ivec4 (OpenGL Mathematics)
	
	typedef glm::vec2 Vec2;   //A typedef for glm::vec2 (OpenGL Mathematics)
	typedef glm::vec3 Vec3;   //A typedef for glm::vec3 (OpenGL Mathematics)
	typedef glm::vec4 Vec4;   //A typedef for glm::vec4 (OpenGL Mathematics)


	//A wrapper for glm::cross (OpenGL Mathematics)
	template<class T>
	T Cross(T vec) { return glm::cross(vec); }

	//A wrapper for glm::distance (OpenGL Mathematics)
	template<class T>
	float Distance(T vec1, T vec2) { return glm::distance(vec1, vec2); }

	//A wrapper for glm::dot (OpenGL Mathematics)
	template<class T>
	float Dot(T vec) { return glm::dot(vec); }

	//A wrapper for glm::faceforward (OpenGL Mathematics)
	template<class T>
	T FaceForward(T vec) { return glm::faceforward(vec); }

	//A wrapper for glm::length (OpenGL Mathematics)
	template<class T>
	float Magnitude(T vec) { return glm::length(vec); }

	//A wrapper for glm::normalize (OpenGL Mathematics)
	template<class T>
	T Normalize(T vec) { return glm::normalize(vec); }

	//A wrapper for glm::reflect (OpenGL Mathematics)
	template<class T>
	T Reflect(T vec) { return glm::reflect(vec); }

	//A wrapper for glm::refract (OpenGL Mathematics)
	template<class T>
	T Refract(T vec) { return glm::refract(vec); }
} //Halib