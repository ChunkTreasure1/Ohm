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

	Quaternion<T>& operator=(const Quaternion<T>& rhs);
	
	void operator+=(const Quaternion<T>& rhs);
	Quaternion<T> operator+(const Quaternion<T>& rhs) const;

	void operator-=(const Quaternion<T>& rhs);
	Quaternion<T> operator-(const Quaternion<T>& rhs) const;

	void operator*=(const Quaternion<T>& rhs);
	Quaternion<T> operator*(const Quaternion<T>& rhs) const;

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
	Vector3 vector{ x, y, z };
	const Vector3 rhsVector{ rhs.x, rhs.y, rhs.z };
	const float scalar = w * rhs.w - vector.Dot(rhsVector);
	
	vector = rhsVector * w + w * rhs.w + vector.Cross(rhsVector);

	return Quaternion<T>(vector.x, vector.y, vector.z, scalar);
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
