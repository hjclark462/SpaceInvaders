#pragma once
class Vector3
{
public:
	float x, y, z;
	Vector3();
	Vector3(float x, float y, float z);
	Vector3 operator + (Vector3 other);
	Vector3& operator += (Vector3 other);
	Vector3 operator - (Vector3 other);
	Vector3 operator * (Vector3 other);
	Vector3 operator * (float other);
	Vector3 operator / (Vector3 other);
	Vector3 operator / (float other);
	float Magnitude();
	float MagnitudeSqr();
	float Distance(Vector3 other);
	void Normalize();
	Vector3 GetNormalised();
	Vector3 GetPerpendicularRH();
	Vector3 GetPerpendicularLH();
	float Dot(Vector3 other);
	Vector3 Cross(Vector3 other);
	float AngleBetween(Vector3 other);
	Vector3 Min(Vector3 a, Vector3 b);
	Vector3 Max(Vector3 a, Vector3 b);
	Vector3 Clamp(Vector3 t, Vector3 a, Vector3 b);
};