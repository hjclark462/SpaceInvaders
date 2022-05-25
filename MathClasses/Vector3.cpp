#include "Vector3.h"
#include <math.h>
#include <algorithm>

Vectr3::Vectr3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vectr3::Vectr3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vectr3 Vectr3::operator+(Vectr3 other)
{
	return Vectr3(x + other.x, y + other.y, z + other.z);
}

Vectr3& Vectr3::operator+=(Vectr3 other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vectr3 Vectr3::operator-(Vectr3 other)
{
	return Vectr3(x - other.x, y - other.y, z - other.z);
}

Vectr3 Vectr3::operator*(Vectr3 other)
{
	return Vectr3(x * other.x, y * other.y, z * other.z);
}

Vectr3 Vectr3::operator*(float other)
{
	return Vectr3(x * other, y * other, z * other);
}

Vectr3 Vectr3::operator/(Vectr3 other)
{
	return Vectr3(x / other.x, y / other.y, z / other.z);
}

Vectr3 Vectr3::operator/(float other)
{
	return Vectr3(x / other, y / other, z / other);
}

float Vectr3::Magnitude()
{
	return (float)sqrt((double)x * x + y * y + z * z);
}

float Vectr3::MagnitudeSqr()
{
	return x * x + y * y + z * z;
}

float Vectr3::Distance(Vectr3 other)
{
	Vectr3 diff = *this - other;
	return (float)sqrt((double)diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
}

void Vectr3::Normalize()
{
	float m = Magnitude();
	x /= m;
	y /= m;
	z /= m;
}

Vectr3 Vectr3::GetNormalised()
{
	return (*this / Magnitude());
}

Vectr3 Vectr3::GetPerpendicularRH()
{
	return Vectr3(-y, x, 0);
}

Vectr3 Vectr3::GetPerpendicularLH()
{
	return Vectr3(y, -x, 0);
}

float Vectr3::Dot(Vectr3 other)
{
	return x * other.x + y* other.y + z* other.z;
}

Vectr3 Vectr3::Cross(Vectr3 other)
{
	return Vectr3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

float Vectr3::AngleBetween(Vectr3 other)
{
	Vectr3 a = GetNormalised();
	Vectr3 b = other.GetNormalised();
	float d = a.x * b.x + a.y * b.y + a.z * b.z;
	return (float)acos(d);
}


Vectr3 Vectr3::Min(Vectr3 a, Vectr3 b)
{
	return Vectr3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Vectr3 Vectr3::Max(Vectr3 a, Vectr3 b)
{
	return Vectr3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

Vectr3 Vectr3::Clamp(Vectr3 t, Vectr3 a, Vectr3 b)
{
	return Max(a, Min(b, t));
}
