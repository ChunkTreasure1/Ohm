#pragma once

#include "Ohm/Vector/Vector3.hpp"

#include <cassert>
#include <cstdint>

template <class T>
class Vector4
{
public:
	Vector4<T>();
	Vector4<T>(const T& aScalar);
	Vector4<T>(const Vector3<T>& aVector, const T& aW);
	Vector4<T>(const Vector2<T>& aVectorOne, const Vector2<T>& aVectorTwo);
	Vector4<T>(const Vector2<T>& aVector, const T& aZ, const T& aW);

	template<typename U>
	Vector4<T>(const U& aScalar);

	template<typename U>
	Vector4<T>(const U& aX, const U& aY, const U& aZ, const U& aW);
	Vector4<T>(const T& aX, const T& aY, const T& aZ, const T& aW);

	Vector4<T>(const Vector4<T>& aVector) = default;
	Vector4<T>& operator=(const Vector4<T>& aVector3) = default;
	~Vector4<T>() = default;

	T& operator[](int index);
	const T& operator[](int index) const;

	T& At(int index);
	T LengthSqr() const;
	T Length() const;
	Vector4<T> GetNormalized() const;
	void Normalize();
	T Dot(const Vector4<T>& aVector) const;

	T x;
	T y;
	T z;
	T w;
};

template<class T>
T& Vector4<T>::operator[](int index)
{
	assert(index >= 0 && index < 4 && "Index out of bounds!");

	switch (index)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}

	return x;
}

template<class T> inline const T& Vector4<T>::operator[](int index) const
{
	assert(index >= 0 && index < 4 && "Index out of bounds!");

	switch (index)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}

	return x;
}

template <class T>
Vector4<T> operator+(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
{
	Vector4<T> newVector;
	newVector.x = aVector0.x + aVector1.x;
	newVector.y = aVector0.y + aVector1.y;
	newVector.z = aVector0.z + aVector1.z;
	newVector.w = aVector0.w + aVector1.w;
	return newVector;
}

template <class T>
Vector4<T> operator-(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
{
	Vector4<T> newVector;
	newVector.x = aVector0.x - aVector1.x;
	newVector.y = aVector0.y - aVector1.y;
	newVector.z = aVector0.z - aVector1.z;
	newVector.w = aVector0.w - aVector1.w;
	return newVector;
}

template <class T>
Vector4<T> operator*(const Vector4<T>& aVector, const T& aScalar)
{
	Vector4<T> newVector;
	newVector.x = aVector.x * aScalar;
	newVector.y = aVector.y * aScalar;
	newVector.z = aVector.z * aScalar;
	newVector.w = aVector.w * aScalar;

	return newVector;
}

template <class T>
Vector4<T> operator*(const T& aScalar, const Vector4<T>& aVector)
{
	Vector4<T> newVector;
	newVector.x = aVector.x * aScalar;
	newVector.y = aVector.y * aScalar;
	newVector.z = aVector.z * aScalar;
	newVector.w = aVector.w * aScalar;

	return newVector;
}

template <class T, typename U>
Vector4<T> operator*(const Vector4<T>& aVector, const U& aScalar)
{
	Vector4<T> newVector;
	newVector.x = aVector.x * static_cast<T>(aScalar);
	newVector.y = aVector.y * static_cast<T>(aScalar);
	newVector.z = aVector.z * static_cast<T>(aScalar);
	newVector.w = aVector.w * static_cast<T>(aScalar);

	return newVector;
}

template <class T, typename U>
Vector4<T> operator*(const U& aScalar, const Vector4<T>& aVector)
{
	Vector4<T> newVector;
	newVector.x = aVector.x * static_cast<T>(aScalar);
	newVector.y = aVector.y * static_cast<T>(aScalar);
	newVector.z = aVector.z * static_cast<T>(aScalar);
	newVector.w = aVector.w * static_cast<T>(aScalar);

	return newVector;
}

template<class T>
Vector4<T> operator*(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
{
	Vector4<T> newVec;
	newVec.x = aVector0.x * aVector1.x;
	newVec.y = aVector0.y * aVector1.y;
	newVec.z = aVector0.z * aVector1.z;
	newVec.w = aVector0.w * aVector1.w;

	return newVec;
}

template <class T> Vector4<T> operator/(const Vector4<T>& aVector, const T& aScalar)
{
	assert(aScalar > static_cast<T>(0) || aScalar < static_cast<T>(0) && "Scalar needs to be non-zero!");

	Vector4<T> newVector;
	newVector.x = aVector.x / aScalar;
	newVector.y = aVector.y / aScalar;
	newVector.z = aVector.z / aScalar;
	newVector.w = aVector.w / aScalar;
	return newVector;
}

template <class T, typename U> Vector4<T> operator/(const Vector4<T>& aVector, const U& aScalar)
{
	assert(aScalar > static_cast<U>(0) || aScalar < static_cast<U>(0) && "Scalar needs to be non-zero!");

	Vector4<T> newVector;
	newVector.x = aVector.x / static_cast<T>(aScalar);
	newVector.y = aVector.y / static_cast<T>(aScalar);
	newVector.z = aVector.z / static_cast<T>(aScalar);
	newVector.w = aVector.w / static_cast<T>(aScalar);
	return newVector;
}

template <class T>
void operator+=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
{
	aVector0 = aVector0 + aVector1;
}

template <class T>
void operator-=(Vector4<T>& aVector0, const Vector4<T>& aVector1)
{
	aVector0 = aVector0 - aVector1;
}

template <class T>
void operator*=(Vector4<T>& aVector, const T& aScalar)
{
	aVector = aVector * aScalar;
}

template <class T, typename U>
void operator*=(Vector4<T>& aVector, const U& aScalar)
{
	aVector = aVector * aScalar;
}

template <class T>
void operator/=(Vector4<T>& aVector, const T& aScalar)
{
	aVector = aVector / aScalar;
}

template <class T, typename U>
void operator/=(Vector4<T>& aVector, const U& aScalar)
{
	aVector = aVector / aScalar;
}

template<typename T>
bool operator==(const Vector4<T>& aVector0, const Vector4<T>& aVector1)
{
	return aVector0.x == aVector1.x &&
		aVector0.y == aVector1.y &&
		aVector0.z == aVector1.z &&
		aVector0.w == aVector1.w;
}

template<class T>
inline T& Vector4<T>::At(int index)
{
	assert(index >= 0 && index < 4 && "Index out of bounds!");

	switch (index)
	{
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}

	return T();
}

template<class T>
inline T Vector4<T>::LengthSqr() const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

template<class T>
inline T Vector4<T>::Length() const
{
	return sqrt(LengthSqr());
}

template<class T>
inline Vector4<T> Vector4<T>::GetNormalized() const
{
	T length = Length();
	assert(length > static_cast<T>(0) && "Length must be non zero!");

	return *this / length;
}

template<class T>
inline void Vector4<T>::Normalize()
{
	T lenght = Length();
	assert(Length() > static_cast<T>(0) && "Length must be non zero!");

	x = x / lenght;
	y = y / lenght;
	z = z / lenght;
	w = w / lenght;
}

template<class T>
inline T Vector4<T>::Dot(const Vector4<T>& aVector) const
{
	return (x * aVector.x) + (y * aVector.y) + (z * aVector.z) + (w * aVector.w);
}

template<class T>
inline Vector4<T>::Vector4()
	: x(0), y(0), z(0), w(0)
{
}

template<class T>
inline Vector4<T>::Vector4(const T& aScalar)
	: x(aScalar), y(aScalar), z(aScalar), w(aScalar)
{
}

template<class T>
inline Vector4<T>::Vector4(const Vector3<T>& aVector, const T& aW)
{
	x = aVector.x;
	y = aVector.y;
	z = aVector.z;

	w = aW;
}

template<class T>
inline Vector4<T>::Vector4(const Vector2<T>& aVectorOne, const Vector2<T>& aVectorTwo)
{
	x = aVectorOne.x;
	y = aVectorOne.y;

	z = aVectorTwo.x;
	w = aVectorTwo.y;
}

template<class T>
inline Vector4<T>::Vector4(const Vector2<T>& aVector, const T& aZ, const T& aW)
{
	x = aVector.x;
	y = aVector.y;

	z = aZ;
	w = aW;
}

template<class T>
template<typename U>
inline Vector4<T>::Vector4(const U& aScalar)
	: x(static_cast<T>(aScalar)), y(static_cast<T>(aScalar)), z(static_cast<T>(aScalar)), w(static_cast<T>(aScalar))
{
}

template<class T>
template<typename U>
inline Vector4<T>::Vector4(const U& aX, const U& aY, const U& aZ, const U& aW)
	: x(static_cast<T>(aX)), y(static_cast<T>(aY)), z(static_cast<T>(aZ)), w(static_cast<T>(aW))
{
}

template<class T>
inline Vector4<T>::Vector4(const T& aX, const T& aY, const T& aZ, const T& aW)
	: x(aX), y(aY), z(aZ), w(aW)
{
}