#pragma once

#include "Ohm/Vector/Vector4.hpp"
#include "Ohm/Vector/Vector3.hpp"

template<typename T>
class Quaternion
{
public:
	Quaternion();
	Quaternion(const T& x, const T& y, const T& z, const T& w);
	Quaternion(const Vector4<T>& vector);
	Quaternion(const Quaternion<T>& quaternion);
	~Quaternion();

	Quaternion<T> Multiply(const Quaternion<T>& rhs);
	T Norm();

	void Normalize();
	Quaternion<T> GetNormalized();

	Quaternion<T> Conjugate();
	Quaternion<T> Inverse();

	void ToUnitNorm();

	const bool operator==(const Quaternion<T>& rhs);
	const bool operator!=(const Quaternion<T>& rhs);

	Quaternion<T>& operator=(const Quaternion<T>& rhs);
	
	void operator+=(const Quaternion<T>& rhs);
	Quaternion<T> operator+(const Quaternion<T>& rhs) const;

	void operator-=(const Quaternion<T>& rhs);
	Quaternion<T> operator-(const Quaternion<T>& rhs) const;

	void operator*=(const Quaternion<T>& rhs);
	Quaternion<T> operator*(const Quaternion<T>& rhs) const;

	void operator*=(const T& rhs);
	Quaternion<T> operator*(const T& rhs) const;

	T x;
	T y;
	T z;
	T w;
};

template<typename T>
inline Quaternion<T>::Quaternion()
{
}

template<typename T>
inline Quaternion<T>::Quaternion(const T& x, const T& y, const T& z, const T& w)
	: x(x), y(y), z(z), w(w)
{
}

template<typename T>
inline Quaternion<T>::Quaternion(const Vector4<T>& vector)
	: x(vector.x), y(vector.y), z(vector.z), w(vector.w)
{
}

template<typename T>
inline Quaternion<T>::Quaternion(const Quaternion<T>& quaternion)
	: x(quaternion.x), y(quaternion.y), z(quaternion.z), w(quaternion.w)
{
}

template<typename T>
inline Quaternion<T>::~Quaternion()
{
}

template<typename T>
inline Quaternion<T> Quaternion<T>::Multiply(const Quaternion<T>& rhs)
{
	Vector3<T> vector{ x, y, z };
	const Vector3<T> rhsVector{ rhs.x, rhs.y, rhs.z };
	const T scalar = w * rhs.w - vector.Dot(rhsVector);
	
	vector = rhsVector * w + w * rhs.w + vector.Cross(rhsVector);

	return Quaternion<T>(vector.x, vector.y, vector.z, scalar);
}

template<typename T>
inline T Quaternion<T>::Norm()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

template<typename T>
inline void Quaternion<T>::Normalize()
{
	const T norm = Norm();
	if (norm != 0)
	{
		T normValue = static_cast<T>(1) / norm;
		
		x *= normValue;
		y *= normValue;
		z *= normValue;
		w *= normValue;
	}
}

template<typename T>
inline Quaternion<T> Quaternion<T>::GetNormalized()
{
	Quaternion<T> result(*this);
	result.Normalize();

	return result;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::Conjugate()
{
	return Quaternion<T>(-x, -y, -z, w);
}

template<typename T>
inline Quaternion<T> Quaternion<T>::Inverse()
{
	T absolute = Norm();
	absolute *= absolute;
	absolute = static_cast<T>(1) / absolute;

	return Conjugate() * absolute;
}

template<typename T>
inline void Quaternion<T>::ToUnitNorm()
{
	T angle = w;
	
	Vector3<T> vector(x, y, z);
	vector.Normalize();
	
	w = static_cast<T>(std::cos(angle * static_cast<T>(0.5)));
	vector = vector * static_cast<T>(std::sin(angle * static_cast<T>(0.5)));

	x = vector.x;
	y = vector.y;
	z = vector.z;
}

template<typename T>
inline const bool Quaternion<T>::operator==(const Quaternion<T>& rhs)
{
	return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
}

template<typename T>
inline const bool Quaternion<T>::operator!=(const Quaternion<T>& rhs)
{
	return !(*this == rhs);
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::operator=(const Quaternion<T>& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	w = rhs.w;

	return *this;
}

template<typename T>
inline void Quaternion<T>::operator+=(const Quaternion<T>& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator+(const Quaternion<T>& rhs) const
{
	return Quaternion<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

template<typename T>
inline void Quaternion<T>::operator-=(const Quaternion<T>& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator-(const Quaternion<T>& rhs) const
{
	return Quaternion<T>(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

template<typename T>
inline void Quaternion<T>::operator*=(const Quaternion<T>& rhs)
{
	(*this) = Multiply(rhs);
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator*(const Quaternion<T>& rhs) const
{
	return Multiply(rhs);
}

template<typename T>
inline void Quaternion<T>::operator*=(const T& rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator*(const T& rhs) const
{
	return Quaternion<T>(x * rhs, y * rhs, z * rhs, w * rhs);
}
