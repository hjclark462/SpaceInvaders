#include "Matrix3.h"
#include "math.h"

Matrix3::Matrix3()
{
	m00 = m01 = m02 = m10 = m11 = m12 = m20 = m21 = m22 = 0;
}

Matrix3::Matrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02; 
	this->m10 = m01; this->m11 = m11; this->m12 = m12; 
	this->m20 = m20; this->m21 = m21; this->m22 = m22;
}

Matrix3::Matrix3(Vector3 X, Vector3 Y, Vector3 Z)
{
	this->m00 = X.x; this->m01 = X.y; this->m02 = X.z;
	this->m10 = Y.x; this->m11 = Y.y; this->m12 = Y.z;
	this->m20 = Z.x; this->m21 = Z.y; this->m22 = Z.z;
}

void Matrix3::Set(Matrix3 other)
{
	*this = other;
}

void Matrix3::Set(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
{
	this->m00 = m00; this->m01 = m01; this->m02 = m02;
	this->m10 = m01; this->m11 = m11; this->m12 = m12;
	this->m20 = m20; this->m21 = m21; this->m22 = m22;
}

Matrix3::Matrix3(float uniformScale)
{
	m00 = m11 = m22 = uniformScale;
	m01 = m02 = m10 = m12 = m20 = m21 = 0;
}

void Matrix3::SetScale(float x, float y, float z)
{
	m00 = x; m01 = 0; m02 = 0;
	m10 = 0; m11 = y; m12 = 0;
	m20 = 0; m21 = 0; m22 = z;
}

void Matrix3::SetScale(Vector3 other)
{
	m00 = other.x; m01 = 0; m02 = 0;
	m10 = 0; m11 = other.y; m12 = 0;
	m20 = 0; m21 = 0; m22 = other.z;
}

void Matrix3::Scale(float x, float y, float z)
{
	Matrix3 m;
	m.SetScale(x, y, z);
	Set(*this * m);
}

void Matrix3::Scale(Vector3 other)
{
	Matrix3 m;
	m.SetScale(other.x, other.y, other.z);
	Set(*this * m);
}

void Matrix3::SetRotateX(double radians)
{
	Set(1, 0, 0,
		0, (float)cos(radians), (float)sin(radians),
		0, (float)-sin(radians), (float)cos(radians));
}

void Matrix3::RotateX(double radians)
{
	Matrix3 m;
	m.SetRotateX(radians);
	Set(*this * m);
}

void Matrix3::SetRotateY(double radians)
{
	Set((float)cos(radians), 0, (float)-sin(radians),
		0, 1, 0,
		(float)sin(radians), 0, (float)cos(radians));
}

void Matrix3::RotateY(double radians)
{
	Matrix3 m;
	m.SetRotateY(radians);
	Set(*this * m);
}

void Matrix3::SetRotateZ(double radians)
{
	Set((float)cos(radians), (float)sin(radians), 0,
		(float)-sin(radians), (float)cos(radians), 0,
		0, 0, 1);
}

void Matrix3::RotateZ(double radians)
{
	Matrix3 m;
	m.SetRotateZ(radians);
	Set(*this * m);
}

void Matrix3::SetEuler(float pitch, float yaw, float roll)
{
	Matrix3 x;
	Matrix3 y;
	Matrix3 z;
	x.SetRotateX(pitch);
	y.SetRotateY(yaw);
	z.SetRotateZ(roll);
	Set(z * y * x);
}

Matrix3 Matrix3::operator*(Matrix3 other)
{
	return Matrix3(m00 * other.m00 + m10 * other.m01 + m20 * other.m02, m01 * other.m00 + m11 * other.m01 + m21 * other.m02, m02 * other.m00 + m12 * other.m01 + m22 * other.m02,
		m00 * other.m10 + m10 * other.m11 + m20 * other.m12, m01 * other.m10 + m11 * other.m11 + m21 * other.m12, m02 * other.m10 + m12 * other.m11 + m22 * other.m12,
		m00 * other.m20 + m10 * other.m21 + m20 * other.m22, m01 * other.m20 + m11 * other.m21 + m21 * other.m22, m02 * other.m20 + m12 * other.m21 + m22 * other.m22);
}

void Matrix3::SetTranslation(float x, float y)
{
	m20 = x; m21 = y;
}

void Matrix3::Translate(float x, float y)
{
	m20 += x; m21 += y;
}
