#pragma once

#include <cassert>

namespace jm
{
	template<typename T>
	class Vector3
	{
	public:
		union {
			struct { T x, y, z; };
			struct { T v0, v1, v2; };
			struct { T r, g, b; };
			T data[3];
			T rgb[3];
		};

	public:
		Vector3()
		{}

		Vector3(const T & _x, const T & _y, const T & _z)
			: x(_x), y(_y), z(_z)
		{}

		~Vector3()
		{}

		void operator += (const Vector3<T>& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}

		void operator -= (const Vector3<T>& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		void operator *= (const T& s)
		{
			x *= s;
			y *= s;
		}

		void operator /= (const T& s)
		{
			const T one_over_s = T(1) / s;
			x *= one_over_s;
			y *= one_over_s;
		}

		Vector3<T> operator + (const Vector3<T>& v) const
		{
			return Vector3<T>(x + v.x, y + v.y, z + v.z);
		}

		Vector3<T> operator - (const Vector3<T>& v) const
		{
			return Vector3<T>(x - v.x, y - v.y, z - v.z);
		}

		Vector3<T> operator * (const T& a) const
		{
			return Vector3<T>(x * a, y * a, z * a);
		}

		Vector3<T> operator / (const T& a) const
		{
			const T one_over_a = T(1) / a;
			return Vector3<T>(x * one_over_a, y * one_over_a, z * one_over_a);
		}

		T & operator [] (const int & ix)
		{
			assert(ix >= 0);
			assert(ix < 3);

			return data[ix];
		}

		const T & operator [] (const int & ix) const
		{
			assert(ix >= 0);
			assert(ix < 3);

			return data[ix];
		}
	};
}
