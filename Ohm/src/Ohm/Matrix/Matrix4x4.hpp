#pragma once

#include "Ohm/Vector/Vector4.hpp"
#include "Ohm/Vector/Vector3.hpp"

#include <cmath>
#include <limits>

template<typename T>
class Matrix4x4
{
public:
	Matrix4x4<T>();
	Matrix4x4<T>(Vector4<T> rowOne, Vector4<T> rowTwo, Vector4<T> rowThree, Vector4<T> rowFour);

	// Copy Constructor.
	Matrix4x4<T>(const Matrix4x4<T>& aMatrix);

	T& operator()(const int aRow, const int aColumn);
	Vector4<T>& operator()(const int aRow);

	const T& operator()(const int aRow, const int aColumn) const;
	const Vector4<T>& operator()(const int aRow) const;

	void operator+=(const Matrix4x4<T>& aMat);
	void operator-=(const Matrix4x4<T>& aMat);
	void operator*=(const Matrix4x4<T>& aMat);
	void operator=(const Matrix4x4<T>& aOther);

	static Matrix4x4<T> CreateRotationAroundX(T aAngleInRadians);
	static Matrix4x4<T> CreateRotationAroundY(T aAngleInRadians);
	static Matrix4x4<T> CreateRotationAroundZ(T aAngleInRadians);

	static Matrix4x4<T> CreateRotation(T aXAngle, T aYAngle, T aZAngle);
	static Matrix4x4<T> CreateTranslation(const Vector3<T>& aPos);

	static Matrix4x4<T> Transpose(const Matrix4x4<T>& aMatrixToTranspose);

	// Assumes aTransform is made up of nothing but rotations and translations.
	static Matrix4x4<T> GetFastInverse(const Matrix4x4<T>& aTransform);
	static Matrix4x4<T> CreateLookAt(const Vector3<T>& aEye, const Vector3<T>& aCenter, const Vector3<T>& aUp);
	static Matrix4x4<T> CreatePerspective(T aFOV, T aAspect, T aNear, T aFar);

private:
	friend class Vector4<T>;

	Vector4<T> m_data[4];
};

template<typename T>
inline Matrix4x4<T>::Matrix4x4()
{
	m_data[0].x = static_cast<T>(1);
	m_data[1].y = static_cast<T>(1);
	m_data[2].z = static_cast<T>(1);
	m_data[3].w = static_cast<T>(1);
}

template<typename T>
inline Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& aMatrix)
{
	m_data[0] = aMatrix.myData[0];
	m_data[1] = aMatrix.myData[1];
	m_data[2] = aMatrix.myData[2];
	m_data[3] = aMatrix.myData[3];
}

template<typename T>
inline Matrix4x4<T>::Matrix4x4(Vector4<T> rowOne, Vector4<T> rowTwo, Vector4<T> rowThree, Vector4<T> rowFour)
{
	m_data[0] = rowOne;
	m_data[1] = rowTwo;
	m_data[2] = rowThree;
	m_data[3] = rowFour;
}

template<typename T>
inline T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
{
	assert(aRow > 0 && aRow <= 5 && "Index out of bounds!");
	assert(aColumn > 0 && aColumn <= 5 && "Index out of bounds!");

	return m_data[aRow - 1][aColumn - 1];
}

template<typename T>
inline Vector4<T>& Matrix4x4<T>::operator()(const int aRow)
{
	return m_data[aRow - 1];
}

template<typename T>
inline const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
{
	assert(aRow > 0 && aRow <= 5 && "Index out of bounds!");
	assert(aColumn > 0 && aColumn <= 5 && "Index out of bounds!");

	return m_data[aRow - 1][aColumn - 1];
}

template<typename T>
inline const Vector4<T>& Matrix4x4<T>::operator()(const int aRow) const
{
	return m_data[aRow - 1];
}

template<typename T>
inline Matrix4x4<T> operator+(Matrix4x4<T>& aMatOne, const Matrix4x4<T>& aMatTwo)
{
	Matrix4x4<T> mat =
	{
		aMatOne(1) + aMatTwo(1),
		aMatOne(2) + aMatTwo(2),
		aMatOne(3) + aMatTwo(3),
		aMatOne(4) + aMatTwo(4),
	};

	return mat;
}

template<typename T>
inline void Matrix4x4<T>::operator+=(const Matrix4x4<T>& aMat)
{
	m_data[0] += aMat.myData[0];
	m_data[1] += aMat.myData[1];
	m_data[2] += aMat.myData[2];
	m_data[3] += aMat.myData[3];
}

template<typename T>
inline void Matrix4x4<T>::operator-=(const Matrix4x4<T>& aMat)
{
	m_data[0] -= aMat.myData[0];
	m_data[1] -= aMat.myData[1];
	m_data[2] -= aMat.myData[2];
	m_data[3] -= aMat.myData[3];
}

template<typename T>
inline Matrix4x4<T> operator-(Matrix4x4<T>& aMatOne, const Matrix4x4<T>& aMatTwo)
{
	Matrix4x4<T> mat =
	{
		aMatOne(1) - aMatTwo(1),
		aMatOne(2) - aMatTwo(2),
		aMatOne(3) - aMatTwo(3),
		aMatOne(4) - aMatTwo(4),
	};

	return mat;
}

template<typename T>
inline Matrix4x4<T> operator*(const Matrix4x4<T>& aMatOne, const Matrix4x4<T>& aMatTwo)
{
	Matrix4x4<T> result;
	result(1, 1) = aMatOne(1, 1) * aMatTwo(1, 1) + aMatOne(1, 2) * aMatTwo(2, 1) + aMatOne(1, 3) * aMatTwo(3, 1) + aMatOne(1, 4) * aMatTwo(4, 1);
	result(1, 2) = aMatOne(1, 1) * aMatTwo(1, 2) + aMatOne(1, 2) * aMatTwo(2, 2) + aMatOne(1, 3) * aMatTwo(3, 2) + aMatOne(1, 4) * aMatTwo(4, 2);
	result(1, 3) = aMatOne(1, 1) * aMatTwo(1, 3) + aMatOne(1, 2) * aMatTwo(2, 3) + aMatOne(1, 3) * aMatTwo(3, 3) + aMatOne(1, 4) * aMatTwo(4, 3);
	result(1, 4) = aMatOne(1, 1) * aMatTwo(1, 4) + aMatOne(1, 2) * aMatTwo(2, 4) + aMatOne(1, 3) * aMatTwo(3, 4) + aMatOne(1, 4) * aMatTwo(4, 4);

	result(2, 1) = aMatOne(2, 1) * aMatTwo(1, 1) + aMatOne(2, 2) * aMatTwo(2, 1) + aMatOne(2, 3) * aMatTwo(3, 1) + aMatOne(2, 4) * aMatTwo(4, 1);
	result(2, 2) = aMatOne(2, 1) * aMatTwo(1, 2) + aMatOne(2, 2) * aMatTwo(2, 2) + aMatOne(2, 3) * aMatTwo(3, 2) + aMatOne(2, 4) * aMatTwo(4, 2);
	result(2, 3) = aMatOne(2, 1) * aMatTwo(1, 3) + aMatOne(2, 2) * aMatTwo(2, 3) + aMatOne(2, 3) * aMatTwo(3, 3) + aMatOne(2, 4) * aMatTwo(4, 3);
	result(2, 4) = aMatOne(2, 1) * aMatTwo(1, 4) + aMatOne(2, 2) * aMatTwo(2, 4) + aMatOne(2, 3) * aMatTwo(3, 4) + aMatOne(2, 4) * aMatTwo(4, 4);

	result(3, 1) = aMatOne(3, 1) * aMatTwo(1, 1) + aMatOne(3, 2) * aMatTwo(2, 1) + aMatOne(3, 3) * aMatTwo(3, 1) + aMatOne(3, 4) * aMatTwo(4, 1);
	result(3, 2) = aMatOne(3, 1) * aMatTwo(1, 2) + aMatOne(3, 2) * aMatTwo(2, 2) + aMatOne(3, 3) * aMatTwo(3, 2) + aMatOne(3, 4) * aMatTwo(4, 2);
	result(3, 3) = aMatOne(3, 1) * aMatTwo(1, 3) + aMatOne(3, 2) * aMatTwo(2, 3) + aMatOne(3, 3) * aMatTwo(3, 3) + aMatOne(3, 4) * aMatTwo(4, 3);
	result(3, 4) = aMatOne(3, 1) * aMatTwo(1, 4) + aMatOne(3, 2) * aMatTwo(2, 4) + aMatOne(3, 3) * aMatTwo(3, 4) + aMatOne(3, 4) * aMatTwo(4, 4);

	result(4, 1) = aMatOne(4, 1) * aMatTwo(1, 1) + aMatOne(4, 2) * aMatTwo(2, 1) + aMatOne(4, 3) * aMatTwo(3, 1) + aMatOne(4, 4) * aMatTwo(4, 1);
	result(4, 2) = aMatOne(4, 1) * aMatTwo(1, 2) + aMatOne(4, 2) * aMatTwo(2, 2) + aMatOne(4, 3) * aMatTwo(3, 2) + aMatOne(4, 4) * aMatTwo(4, 2);
	result(4, 3) = aMatOne(4, 1) * aMatTwo(1, 3) + aMatOne(4, 2) * aMatTwo(2, 3) + aMatOne(4, 3) * aMatTwo(3, 3) + aMatOne(4, 4) * aMatTwo(4, 3);
	result(4, 4) = aMatOne(4, 1) * aMatTwo(1, 4) + aMatOne(4, 2) * aMatTwo(2, 4) + aMatOne(4, 3) * aMatTwo(3, 4) + aMatOne(4, 4) * aMatTwo(4, 4);

	return result;
}

template<typename T>
inline void Matrix4x4<T>::operator*=(const Matrix4x4<T>& aMat)
{
	*this = *this * aMat;
}

template<typename T>
inline Vector4<T> operator*(const Vector4<T>& aVec, const Matrix4x4<T>& aMat)
{
	Vector4<T> vec =
	{
		aVec.x * aMat(1, 1) + aVec.y * aMat(2, 1) + aVec.z * aMat(3, 1) + aVec.w * aMat(4, 1),
		aVec.x * aMat(1, 2) + aVec.y * aMat(2, 2) + aVec.z * aMat(3, 2) + aVec.w * aMat(4, 2),
		aVec.x * aMat(1, 3) + aVec.y * aMat(2, 3) + aVec.z * aMat(3, 3) + aVec.w * aMat(4, 3),
		aVec.x * aMat(1, 4) + aVec.y * aMat(2, 4) + aVec.z * aMat(3, 4) + aVec.w * aMat(4, 4),
	};

	return vec;
}

template<typename T>
inline void Matrix4x4<T>::operator=(const Matrix4x4<T>& aOther)
{
	m_data[0] = aOther.myData[0];
	m_data[1] = aOther.myData[1];
	m_data[2] = aOther.myData[2];
	m_data[3] = aOther.myData[3];
}

template<typename T>
inline bool operator==(const Matrix4x4<T>& aFirst, const Matrix4x4<T>& aSecond)
{
	return aFirst(1) == aSecond(1) &&
		aFirst(2) == aSecond(2) &&
		aFirst(3) == aSecond(3) &&
		aFirst(4) == aSecond(4);
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(T aAngleInRadians)
{
	Matrix4x4<T> mat =
	{
		Vector4<T>{ 1, 0, 0, 0},
		Vector4<T>{ 0, std::cos(aAngleInRadians), std::sin(aAngleInRadians), 0 },
		Vector4<T>{ 0, -std::sin(aAngleInRadians), std::cos(aAngleInRadians), 0 },
		Vector4<T>{ 0, 0, 0, 1 }
	};

	return mat;
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(T aAngleInRadians)
{
	Matrix4x4<T> mat =
	{
		Vector4<T>{ std::cos(aAngleInRadians), 0, -std::sin(aAngleInRadians), 0 },
		Vector4<T>{ 0, 1, 0, 0 },
		Vector4<T>{ std::sin(aAngleInRadians), 0, std::cos(aAngleInRadians), 0 },
		Vector4<T>{ 0, 0, 0, 1 }
	};

	return mat;
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(T aAngleInRadians)
{
	Matrix4x4<T> mat =
	{
		Vector4<T>{ std::cos(aAngleInRadians), std::sin(aAngleInRadians), 0, 0 },
		Vector4<T>{ -std::sin(aAngleInRadians), std::cos(aAngleInRadians), 0, 0 },
		Vector4<T>{ 0, 0, 1, 0 },
		Vector4<T>{ 0, 0, 0, 1 }
	};

	return mat;
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreateRotation(T aXAngle, T aYAngle, T aZAngle)
{
	return CreateRotationAroundX(aXAngle) * CreateRotationAroundY(aYAngle) * CreateRotationAroundZ(aZAngle);
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::Transpose(const Matrix4x4<T>& aMat)
{
	Matrix4x4<T> mat
	{
		Vector4<T>{ aMat(1, 1), aMat(2, 1), aMat(3, 1), aMat(4, 1) },
		Vector4<T>{ aMat(1, 2), aMat(2, 2), aMat(3, 2), aMat(4, 2) },
		Vector4<T>{ aMat(1, 3), aMat(2, 3), aMat(3, 3), aMat(4, 3) },
		Vector4<T>{ aMat(1, 4), aMat(2, 4), aMat(3, 4), aMat(4, 4) }
	};

	return mat;
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse(const Matrix4x4<T>& aTransform)
{
	Matrix3x3<T> rotMat;
	rotMat(1, 1) = aTransform(1, 1);
	rotMat(1, 2) = aTransform(1, 2);
	rotMat(1, 3) = aTransform(1, 3);

	rotMat(2, 1) = aTransform(2, 1);
	rotMat(2, 2) = aTransform(2, 2);
	rotMat(2, 3) = aTransform(2, 3);

	rotMat(3, 1) = aTransform(3, 1);
	rotMat(3, 2) = aTransform(3, 2);
	rotMat(3, 3) = aTransform(3, 3);

	rotMat = Matrix3x3<T>::Transpose(rotMat);

	Vector3<T> translation{ -aTransform(4, 1), -aTransform(4, 2), -aTransform(4, 3) };
	translation = translation * rotMat;

	Matrix4x4<T> inverse
	{
		Vector4<T>{ rotMat(1, 1), rotMat(1, 2), rotMat(1, 3), static_cast<T>(0) },
		Vector4<T>{ rotMat(2, 1), rotMat(2, 2), rotMat(2, 3), static_cast<T>(0) },
		Vector4<T>{ rotMat(3, 1), rotMat(3, 2), rotMat(3, 3), static_cast<T>(0) },
		Vector4<T>{ translation.x, translation.y, translation.z, static_cast<T>(1) }
	};

	return inverse;
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreateLookAt(const Vector3<T>& aEye, const Vector3<T>& aCenter, const Vector3<T>& aUp)
{
	Vector3<T> const forward = (aCenter - aEye).GetNormalized();
	Vector3<T> const right = aUp.Cross(forward).GetNormalized();
	Vector3<T> const up = forward.Cross(right);

	Matrix4x4<T> result =
	{
		Vector4<T>{ right.x, right.y, right.z, static_cast<T>(0) },
		Vector4<T>{ up.x, up.y, up.z, static_cast<T>(0) },
		Vector4<T>{ forward.x, forward.y, forward.z, static_cast<T>(0) },
		Vector4<T>{ aEye.x, aEye.y, aEye.z, static_cast<T>(1) }
	};

	return result;
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreatePerspective(T aFOV, T aAspect, T aNear, T aFar)
{
	assert(std::abs(aAspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));
	T const tanHalfFOV = tan(aFOV / static_cast<T>(2));

	Matrix4x4<T> result =
	{
		Vector4<T> {(static_cast<T>(1) / tanHalfFOV), 0, 0, 0},
		Vector4<T> {0, aAspect* (static_cast<T>(1) / tanHalfFOV), 0, 0},
		Vector4<T> {0, 0, (aFar / (aFar - aNear)), static_cast<T>(1)},
		Vector4<T> {0, 0, (-(aNear * aFar) / (aFar - aNear)), 0},
	};

	return result;
}

template<typename T>
inline Matrix4x4<T> Matrix4x4<T>::CreateTranslation(const Vector3<T>& aPos)
{
	Matrix4x4<T> result;

	result(4) = aPos.x * result(1) + result(2) * aPos.y + result(3) * aPos.z + result(4);

	return result;
}
