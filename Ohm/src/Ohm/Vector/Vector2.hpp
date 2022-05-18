#pragma once

#include <cassert>

template <class T>
class Vector2
{
public:
	Vector2<T>();
	Vector2<T>(const T& aScalar);

	template<typename U>
	Vector2<T>(const U& aScalar);

	template<typename U>
	Vector2<T>(const U& aX, const U& aY);

	Vector2<T>(const T& aX, const T& aY);
	Vector2<T>(const Vector2<T>& aVector) = default;
	Vector2<T>& operator=(const Vector2<T>& aVector) = default;
	~Vector2<T>() = default;

	T LengthSqr() const;
	T Length() const;
	Vector2<T> GetNormalized() const;
	void Normalize();
	T Dot(const Vector2<T>& aVector) const;

	T x;
	T y;
};

template <class T>
Vector2<T> operator+(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
{
	Vector2<T> newVector;
	newVector.x = aVector0.x + aVector1.x;
	newVector.y = aVector0.y + aVector1.y;
	return newVector;
}

template <class T>
Vector2<T> operator-(const Vector2<T>& aVector0, const Vector2<T>& aVector1)
{
	Vector2<T> newVector;
	newVector.x = aVector0.x - aVector1.x;
	newVector.y = aVector0.y - aVector1.y;
	return newVector;
}

template <class T>
Vector2<T> operator*(const Vector2<T>& aVector, const T& aScalar)
{
	Vector2<T> newVector;
	newVector.x = aVector.x * aScalar;
	newVector.y = aVector.y * aScalar;

	return newVector;
}

template <class T>
Vector2<T> operator*(const T& aScalar, const Vector2<T>& aVector)
{
	Vector2<T> newVector;
	newVector.x = aVector.x * aScalar;
	newVector.y = aVector.y * aScalar;

	return newVector;
}

template <class T, typename U>
Vector2<T> operator*(const Vector2<T>& aVector, const U& aScalar)
{
	Vector2<T> newVector;
	newVector.x = aVector.x * static_cast<T>(aScalar);
	newVector.y = aVector.y * static_cast<T>(aScalar);

	return newVector;
}

template <class T, typename U>
Vector2<T> operator*(const U& aScalar, const Vector2<T>& aVector)
{
	Vector2<T> newVector;
	newVector.x = aVector.x * static_cast<T>(aScalar);
	newVector.y = aVector.y * static_cast<T>(aScalar);

	return newVector;
}

template <class T>
Vector2<T> operator/(const Vector2<T>& aVector, const T& aScalar)
{
	assert(aScalar > static_cast<T>(0) || aScalar < static_cast<T>(0) && "Scalar needs to be non-zero!");

	Vector2<T> newVector;
	newVector.x = aVector.x / aScalar;
	newVector.y = aVector.y / aScalar;
	return newVector;
}

template <class T, typename U>
Vector2<T> operator/(const Vector2<T>& aVector, const U& aScalar)
{
	assert(aScalar > static_cast<U>(0) || aScalar < static_cast<U>(0) && "Scalar needs to be non-zero!");

	Vector2<T> newVector;
	newVector.x = aVector.x / static_cast<T>(aScalar);
	newVector.y = aVector.y / static_cast<T>(aScalar);
	return newVector;
}

template <class T>
void operator+=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
{
	aVector0 = aVector0 + aVector1;
}

template <class T>
void operator-=(Vector2<T>& aVector0, const Vector2<T>& aVector1)
{
	aVector0 = aVector0 - aVector1;
}

template <class T>
void operator*=(Vector2<T>& aVector, const T& aScalar)
{
	aVector = aVector * aScalar;
}

template <class T, typename U>
void operator*=(Vector2<T>& aVector, const U& aScalar)
{
	aVector = aVector * aScalar;
}

template <class T>
void operator/=(Vector2<T>& aVector, const T& aScalar)
{
	aVector = aVector / aScalar;
}

template <class T, typename U>
void operator/=(Vector2<T>& aVector, const U& aScalar)
{
	aVector = aVector / aScalar;
}

template<class T>
inline T Vector2<T>::LengthSqr() const
{
	return (x * x) + (y * y);
}

template<class T>
inline T Vector2<T>::Length() const
{
	return sqrt(LengthSqr());
}

template<class T>
inline Vector2<T> Vector2<T>::GetNormalized() const
{
	T length = Length();

	assert(length > static_cast<T>(0) && "Length must be non zero!");
	return *this / Length();
}

template<class T>
inline void Vector2<T>::Normalize()
{
	T lenght = Length();
	//assert(length > static_cast<T>(0) && "Length must be non zero!");

	x = x / lenght;
	y = y / lenght;
}

template<class T>
inline T Vector2<T>::Dot(const Vector2<T>& aVector) const
{
	return (x * aVector.x) + (y * aVector.y);
}

template<class T>
inline Vector2<T>::Vector2()
	: x(0), y(0)
{
}

template<class T>
inline Vector2<T>::Vector2(const T& aScalar)
	: x(aScalar), y(aScalar)
{
}

template<class T>
template<typename U>
inline Vector2<T>::Vector2(const U& aScalar)
	: x(static_cast<T>(aScalar)), y(static_cast<T>(aScalar))
{
}

template<class T>
template<typename U>
inline Vector2<T>::Vector2(const U& aX, const U& aY)
	: x(static_cast<T>(aX)), y(static_cast<T>(aY))
{
}

template<class T>
inline Vector2<T>::Vector2(const T& aX, const T& aY)
	: x(aX), y(aY)
{
}