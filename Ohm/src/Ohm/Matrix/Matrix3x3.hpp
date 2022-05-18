#pragma once
#include "Ohm/Vector/Vector3.hpp"
#include "Ohm/Matrix/Matrix4x4.hpp"

#include <cmath>

template<typename T>
class Matrix3x3
{
public:
	Matrix3x3<T>();
	Matrix3x3<T>(Vector3<T> rowOne, Vector3<T> rowTwo, Vector3<T> rowThree);

	// Copy Constructor.
	Matrix3x3<T>(const Matrix3x3<T>& aMatrix);
	Matrix3x3<T>(const Matrix4x4<T>& aMatrix);

	T& operator()(const int aRow, const int aColumn);
	const T& operator()(const int aRow, const int aColumn) const;
	const Vector3<T>& operator()(const int aRow) const;

	void operator+=(const Matrix3x3<T>& aMat);
	void operator-=(const Matrix3x3<T>& aMat);
	void operator*=(const Matrix3x3<T>& aMat);
	void operator=(const Matrix3x3<T>& aOther);

	static Matrix3x3<T> CreateRotationAroundX(T aAngleInRadians);
	static Matrix3x3<T> CreateRotationAroundY(T aAngleInRadians);
	static Matrix3x3<T> CreateRotationAroundZ(T aAngleInRadians);

	static Matrix3x3<T> Rotate(T aXAngle, T aYAngle, T aZAngle);

	static Matrix3x3<T> Transpose(const Matrix3x3<T>& aMatrixToTranspose);

private:
	Vector3<T> myData[3];
};

template<typename T>
inline Matrix3x3<T>::Matrix3x3()
{
	myData[0].x = static_cast<T>(1);
	myData[1].y = static_cast<T>(1);
	myData[2].z = static_cast<T>(1);
}

template<typename T>
inline Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& aMatrix)
{
	myData[0] = aMatrix.myData[0];
	myData[1] = aMatrix.myData[1];
	myData[2] = aMatrix.myData[2];
}

template<typename T>
inline Matrix3x3<T>::Matrix3x3(Vector3<T> rowOne, Vector3<T> rowTwo, Vector3<T> rowThree)
{
	myData[0] = rowOne;
	myData[1] = rowTwo;
	myData[2] = rowThree;
}

template<typename T>
inline Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& aMatrix)
{
	myData[0] = { aMatrix(1, 1), aMatrix(1, 2), aMatrix(1, 3) };
	myData[1] = { aMatrix(2, 1), aMatrix(2, 2), aMatrix(2, 3) };
	myData[2] = { aMatrix(3, 1), aMatrix(3, 2), aMatrix(3, 3) };
}

template<typename T>
inline T& Matrix3x3<T>::operator()(const int aRow, const int aColumn)
{
	assert(aRow > 0 && aRow < 4 && "Index out of bounds!");
	assert(aColumn > 0 && aColumn < 4 && "Index out of bounds!");

	return myData[aRow - 1][aColumn - 1];
}

template<typename T>
inline const T& Matrix3x3<T>::operator()(const int aRow, const int aColumn) const
{
	assert(aRow > 0 && aRow < 4 && "Index out of bounds!");
	assert(aColumn > 0 && aColumn < 4 && "Index out of bounds!");

	return myData[aRow - 1][aColumn - 1];
}

template<typename T>
inline const Vector3<T>& Matrix3x3<T>::operator()(const int aRow) const
{
	assert(aRow > 0 && aRow < 4 && "Index out of bounds!");

	return myData[aRow - 1];
}

template<typename T>
inline void Matrix3x3<T>::operator+=(const Matrix3x3<T>& aMat)
{
	myData[0] += aMat.myData[0];
	myData[1] += aMat.myData[1];
	myData[2] += aMat.myData[2];
}

template<typename T>
inline void Matrix3x3<T>::operator-=(const Matrix3x3<T>& aMat)
{
	myData[0] -= aMat.myData[0];
	myData[1] -= aMat.myData[1];
	myData[2] -= aMat.myData[2];
}

template<typename T>
inline Matrix3x3<T> operator+(Matrix3x3<T>& aMatOne, const Matrix3x3<T>& aMatTwo)
{
	Matrix3x3<T> mat =
	{
		aMatOne(1) + aMatTwo(1),
		aMatOne(2) + aMatTwo(2),
		aMatOne(3) + aMatTwo(3),
	};

	return mat;
}

template<typename T>
inline Matrix3x3<T> operator-(Matrix3x3<T>& aMatOne, const Matrix3x3<T>& aMatTwo)
{
	Matrix3x3<T> mat =
	{
		aMatOne(1) - aMatTwo(1),
		aMatOne(2) - aMatTwo(2),
		aMatOne(3) - aMatTwo(3),
	};

	return mat;
}

template<typename T>
inline Matrix3x3<T> operator*(const Matrix3x3<T>& aMatOne, const Matrix3x3<T>& aMatTwo)
{
	Matrix3x3<T> result;
	result(1, 1) = aMatOne(1, 1) * aMatTwo(1, 1) + aMatOne(1, 2) * aMatTwo(2, 1) + aMatOne(1, 3) * aMatTwo(3, 1);
	result(1, 2) = aMatOne(1, 1) * aMatTwo(1, 2) + aMatOne(1, 2) * aMatTwo(2, 2) + aMatOne(1, 3) * aMatTwo(3, 2);
	result(1, 3) = aMatOne(1, 1) * aMatTwo(1, 3) + aMatOne(1, 2) * aMatTwo(2, 3) + aMatOne(1, 3) * aMatTwo(3, 3);

	result(2, 1) = aMatOne(2, 1) * aMatTwo(1, 1) + aMatOne(2, 2) * aMatTwo(2, 1) + aMatOne(2, 3) * aMatTwo(3, 1);
	result(2, 2) = aMatOne(2, 1) * aMatTwo(1, 2) + aMatOne(2, 2) * aMatTwo(2, 2) + aMatOne(2, 3) * aMatTwo(3, 2);
	result(2, 3) = aMatOne(2, 1) * aMatTwo(1, 3) + aMatOne(2, 2) * aMatTwo(2, 3) + aMatOne(2, 3) * aMatTwo(3, 3);

	result(3, 1) = aMatOne(3, 1) * aMatTwo(1, 1) + aMatOne(3, 2) * aMatTwo(2, 1) + aMatOne(3, 3) * aMatTwo(3, 1);
	result(3, 2) = aMatOne(3, 1) * aMatTwo(1, 2) + aMatOne(3, 2) * aMatTwo(2, 2) + aMatOne(3, 3) * aMatTwo(3, 2);
	result(3, 3) = aMatOne(3, 1) * aMatTwo(1, 3) + aMatOne(3, 2) * aMatTwo(2, 3) + aMatOne(3, 3) * aMatTwo(3, 3);

	return result;
}

template<typename T>
inline void Matrix3x3<T>::operator*=(const Matrix3x3<T>& aMat)
{
	*this = *this * aMat;
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T>& aVec, const Matrix3x3<T>& aMat)
{
	Vector3<T> vec =
	{
		aVec.x * aMat(1, 1) + aVec.y * aMat(2, 1) + aVec.z * aMat(3, 1),
		aVec.x * aMat(1, 2) + aVec.y * aMat(2, 2) + aVec.z * aMat(3, 2),
		aVec.x * aMat(1, 3) + aVec.y * aMat(2, 3) + aVec.z * aMat(3, 3),
	};

	return vec;
}

template<typename T>
inline void Matrix3x3<T>::operator=(const Matrix3x3<T>& aOther)
{
	myData[0] = aOther.myData[0];
	myData[1] = aOther.myData[1];
	myData[2] = aOther.myData[2];
}

template<typename T>
inline bool operator==(const Matrix3x3<T>& aFirst, const Matrix3x3<T>& aSecond)
{
	return aFirst(1) == aSecond(1) &&
		aFirst(2) == aSecond(2) &&
		aFirst(3) == aSecond(3);
}

template<typename T>
inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(T aAngleInRadians)
{
	Matrix3x3<T> mat =
	{
		Vector3<T>{ 1, 0, 0 },
		Vector3<T>{ 0, std::cos(aAngleInRadians), std::sin(aAngleInRadians) },
		Vector3<T>{ 0, -std::sin(aAngleInRadians), std::cos(aAngleInRadians) }
	};

	return mat;
}

template<typename T>
inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(T aAngleInRadians)
{
	Matrix3x3<T> mat =
	{
		Vector3<T>{ std::cos(aAngleInRadians), 0, -std::sin(aAngleInRadians) },
		Vector3<T>{ 0, 1, 0 },
		Vector3<T>{ std::sin(aAngleInRadians), 0, std::cos(aAngleInRadians) }
	};

	return mat;
}

template<typename T>
inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(T aAngleInRadians)
{
	Matrix3x3<T> mat =
	{
		Vector3<T>{ std::cos(aAngleInRadians), std::sin(aAngleInRadians), 0 },
		Vector3<T>{ -std::sin(aAngleInRadians), std::cos(aAngleInRadians), 0 },
		Vector3<T>{ 0, 0, 1 }
	};

	return mat;
}

template<typename T>
inline Matrix3x3<T> Matrix3x3<T>::Rotate(T aXAngle, T aYAngle, T aZAngle)
{
	return CreateRotationAroundX(aXAngle) * CreateRotationAroundY(aYAngle) * CreateRotationAroundZ(aZAngle);
}

template<typename T>
inline Matrix3x3<T> Matrix3x3<T>::Transpose(const Matrix3x3<T>& aMat)
{
	Matrix3x3<T> mat
	{
		Vector3<T>{ aMat(1, 1), aMat(2, 1), aMat(3, 1) },
		Vector3<T>{ aMat(1, 2), aMat(2, 2), aMat(3, 2) },
		Vector3<T>{ aMat(1, 3), aMat(2, 3), aMat(3, 3) }
	};

	return mat;
}