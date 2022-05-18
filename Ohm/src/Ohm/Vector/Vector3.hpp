#pragma once

#include "Ohm/Vector/Vector2.hpp"

#include <cassert>
#include <cstdint>

template <class T>
class Vector3
{
public:
	Vector3<T>();
	Vector3<T>(const T& aScalar);
	Vector3<T>(const Vector2<T>& aVector, const T& aZ);

	template<typename U>
	Vector3<T>(U aScalar);

	template<typename U>
	Vector3<T>(const U& aX, const U& aY, const U& aZ);

	Vector3<T>(const T& aX, const T& aY, const T& aZ);
	Vector3<T>(const Vector3<T>& aVector) = default;
	Vector3<T>& operator=(const Vector3<T>& aVector3) = default;
	~Vector3<T>() = default;

	T& operator[](int index);
	const T& operator[](int index) const;
	T& At(int index);

	T LengthSqr() const;
	T Length() const;
	Vector3<T> GetNormalized() const;
	void Normalize();
	T Dot(const Vector3<T>& aVector) const;
	Vector3<T> Cross(const Vector3<T>& aVector) const;

	T x;
	T y;
	T z;
};

template <class T> Vector3<T> operator+(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
{
	Vector3<T> newVector;
	newVector.x = aVector0.x + aVector1.x;
	newVector.y = aVector0.y + aVector1.y;
	newVector.z = aVector0.z + aVector1.z;
	return newVector;
}

template <class T> T& Vector3<T>::operator[](int index)
{
	assert(index >= 0 && index < 3 && "Index out of bounds!");

	switch (index)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
	}

	return x;
}

template<class T> inline const T& Vector3<T>::operator[](int index) const
{
	assert(index >= 0 && index < 3 && "Index out of bounds!");

	switch (index)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
	}

	return x;
}

template<class T>
inline T& Vector3<T>::At(int index)
{
	assert(index >= 0 && index < 3 && "Index out of bounds!");

	switch (index)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
	}

	return x;
}

template <class T> Vector3<T> operator-(const Vector3<T>& aVector0, const Vector3<T>& aVector1)
{
	Vector3<T> newVector;
	newVector.x = aVector0.x - aVector1.x;
	newVector.y = aVector0.y - aVector1.y;
	newVector.z = aVector0.z - aVector1.z;
	return newVector;
}

template <class T> Vector3<T> operator*(const Vector3<T>& aVector, const T& aScalar)
{
	Vector3<T> newVector;
	newVector.x = aVector.x * aScalar;
	newVector.y = aVector.y * aScalar;
	newVector.z = aVector.z * aScalar;

	return newVector;
}

template <class T> Vector3<T> operator*(const Vector3<T>& aVector, const Vector3<T>& aSecond)
{
	Vector3<T> newVector;
	newVector.x = aVector.x * aSecond.x;
	newVector.y = aVector.y * aSecond.y;
	newVector.z = aVector.z * aSecond.z;

	return newVector;
}


template <class T> Vector3<T> operator*(const T& aScalar, const Vector3<T>& aVector)
{
	Vector3<T> newVector;
	newVector.x = aVector.x * aScalar;
	newVector.y = aVector.y * aScalar;
	newVector.z = aVector.z * aScalar;

	return newVector;
}

template <class T, typename U> Vector3<T> operator*(const Vector3<T>& aVector, const U& aScalar)
{
	Vector3<T> newVector;
	newVector.x = aVector.x * static_cast<T>(aScalar);
	newVector.y = aVector.y * static_cast<T>(aScalar);
	newVector.z = aVector.z * static_cast<T>(aScalar);

	return newVector;
}

template <class T, typename U> Vector3<T> operator*(const U& aScalar, const Vector3<T>& aVector)
{
	Vector3<T> newVector;
	newVector.x = aVector.x * static_cast<T>(aScalar);
	newVector.y = aVector.y * static_cast<T>(aScalar);
	newVector.z = aVector.z * static_cast<T>(aScalar);

	return newVector;
}

template <class T> Vector3<T> operator/(const Vector3<T>& aVector, const T& aScalar)
{
	assert(aScalar > static_cast<T>(0) || aScalar < static_cast<T>(0) && "Scalar needs to be non-zero!");

	Vector3<T> newVector;
	newVector.x = aVector.x / aScalar;
	newVector.y = aVector.y / aScalar;
	newVector.z = aVector.z / aScalar;
	return newVector;
}

template <class T, typename U> Vector3<T> operator/(const Vector3<T>& aVector, const U& aScalar)
{
	assert(aScalar > static_cast<U>(0) || aScalar < static_cast<U>(0) && "Scalar needs to be non-zero!");

	Vector3<T> newVector;
	newVector.x = aVector.x / static_cast<T>(aScalar);
	newVector.y = aVector.y / static_cast<T>(aScalar);
	newVector.z = aVector.z / static_cast<T>(aScalar);
	return newVector;
}

template <class T> void operator+=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
{
	aVector0 = aVector0 + aVector1;
}

template <class T> void operator-=(Vector3<T>& aVector0, const Vector3<T>& aVector1)
{
	aVector0 = aVector0 - aVector1;
}

template <class T> void operator*=(Vector3<T>& aVector, const T& aScalar)
{
	aVector = aVector * aScalar;
}

template <class T, typename U> void operator*=(Vector3<T>& aVector, const U& aScalar)
{
	aVector = aVector * aScalar;
}

template <class T> void operator/=(Vector3<T>& aVector, const T& aScalar)
{
	aVector = aVector / aScalar;
}

template <class T, typename U> void operator/=(Vector3<T>& aVector, const U& aScalar)
{
	aVector = aVector / aScalar;
}

template <class T> bool operator==(const Vector3<T>& aVector, const Vector3<T>& aVector1)
{
	return aVector.x == aVector1.x && aVector.y == aVector1.y && aVector.z == aVector1.z;
}

template<class T>
inline T Vector3<T>::LengthSqr() const
{
	return (x * x) + (y * y) + (z * z);
}

template<class T>
inline T Vector3<T>::Length() const
{
	return sqrt(LengthSqr());
}

template<class T>
inline Vector3<T> Vector3<T>::GetNormalized() const
{
	T length = Length();

	assert(length > static_cast<T>(0) && "Length must be non zero!");
	return *this / Length();
}

template<class T>
inline void Vector3<T>::Normalize()
{
	T lenght = Length();
	//assert(length > static_cast<T>(0) && "Length must be non zero!");

	x = x / lenght;
	y = y / lenght;
	z = z / lenght;
}

template<class T>
inline T Vector3<T>::Dot(const Vector3<T>& aVector) const
{
	return (x * aVector.x) + (y * aVector.y) + (z * aVector.z);
}

template<class T>
inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& aVector) const
{
	Vector3<T> newVector;
	newVector.x = y * aVector.z - z * aVector.y;
	newVector.y = z * aVector.x - x * aVector.z;
	newVector.z = x * aVector.y - y * aVector.x;
	return newVector;

}

template<class T>
inline Vector3<T>::Vector3()
	: x(0), y(0), z(0)
{
}

template<class T>
inline Vector3<T>::Vector3(const T& aScalar)
	: x(aScalar), y(aScalar), z(aScalar)
{
}

template<class T>
inline Vector3<T>::Vector3(const Vector2<T>& aVector, const T& aZ)
{
	x = aVector.x;
	y = aVector.y;
	z = z;
}

template<class T>
template<typename U>
inline Vector3<T>::Vector3(U aScalar)
	: x(static_cast<T>(aScalar)), y(static_cast<T>(aScalar)), z(static_cast<T>(aScalar))
{
}

template<class T>
template<typename U>
inline Vector3<T>::Vector3(const U& aX, const U& aY, const U& aZ)
	: x(static_cast<T>(aX)), y(static_cast<T>(aY)), z(static_cast<T>(aZ))
{
}

template<class T>
inline Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
	: x(aX), y(aY), z(aZ)
{
}