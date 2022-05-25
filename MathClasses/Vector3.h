#pragma once
class Vectr3
{
public:
	float x, y, z;
	Vectr3();
	Vectr3(float x, float y, float z);
	Vectr3 operator + (Vectr3 other);
	Vectr3& operator += (Vectr3 other);
	Vectr3 operator - (Vectr3 other);
	Vectr3 operator * (Vectr3 other);
	Vectr3 operator * (float other);
	Vectr3 operator / (Vectr3 other);
	Vectr3 operator / (float other);
	float Magnitude();
	float MagnitudeSqr();
	float Distance(Vectr3 other);
	void Normalize();
	Vectr3 GetNormalised();
	Vectr3 GetPerpendicularRH();
	Vectr3 GetPerpendicularLH();
	float Dot(Vectr3 other);
	Vectr3 Cross(Vectr3 other);
	float AngleBetween(Vectr3 other);
	Vectr3 Min(Vectr3 a, Vectr3 b);
	Vectr3 Max(Vectr3 a, Vectr3 b);
	Vectr3 Clamp(Vectr3 t, Vectr3 a, Vectr3 b);
};