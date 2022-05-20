#include "Vector3.h"
#include <math.h>
#include <algorithm>

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator+(Vector3 other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator+=(Vector3 other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(Vector3 other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(Vector3 other)
{
	return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator*(float other)
{
	return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::operator/(Vector3 other)
{
	return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator/(float other)
{
	return Vector3(x / other, y / other, z / other);
}

float Vector3::Magnitude()
{
	return (float)sqrt((double)x * x + y * y + z * z);
}

float Vector3::MagnitudeSqr()
{
	return x * x + y * y + z * z;
}

float Vector3::Distance(Vector3 other)
{
	Vector3 diff = *this - other;
	return (float)sqrt((double)diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}

void Vector3::Normalize()
{
	float m = Magnitude();
	x /= m;
	y /= m;
	z /= m;
}

Vector3 Vector3::GetNormalised()
{
	return (*this / Magnitude());
}

Vector3 Vector3::GetPerpendicularRH()
{
	return Vector3(-y, x, 0);
}

Vector3 Vector3::GetPerpendicularLH()
{
	return Vector3(y, -x, 0);
}

float Vector3::Dot(Vector3 other)
{
	return x * other.x + y* other.y + z* other.z;
}

Vector3 Vector3::Cross(Vector3 other)
{
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

float Vector3::AngleBetween(Vector3 other)
{
	Vector3 a = GetNormalised();
	Vector3 b = other.GetNormalised();
	float d = a.x * b.x + a.y * b.y + a.z * b.z;
	return (float)acos(d);
}


Vector3 Vector3::Min(Vector3 a, Vector3 b)
{
	return Vector3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Vector3 Vector3::Max(Vector3 a, Vector3 b)
{
	return Vector3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

Vector3 Vector3::Clamp(Vector3 t, Vector3 a, Vector3 b)
{
	return Max(a, Min(b, t));
}
