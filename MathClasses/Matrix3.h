#pragma once
#include "Vector3.h"
class Matrix3
{
public:
	float m00, m01, m02;
	float m10, m11, m12;
	float m20, m21, m22;
	Matrix3();
	Matrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);
	Matrix3(Vector3 X, Vector3 Y, Vector3 Z);
	void Set(Matrix3 other);
	void Set(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);
	Matrix3(float uniformScale);
	void SetScale(float x, float y, float z);
	void SetScale(Vector3 other);
	void Scale(float x, float y, float z);
	void Scale(Vector3 other);
	void SetRotateX(double radians);
	void RotateX(double radians);
	void SetRotateY(double radians);
	void RotateY(double radians);
	void SetRotateZ(double radians);
	void RotateZ(double radians);
	void SetEuler(float pitch, float yaw, float roll);
	Matrix3 operator * (Matrix3 other);
	Vector3 operator * (Vector3 other);
	bool operator == (Matrix3 other);
	void SetTranslation(float x, float y);
	void Translate(float x, float y);
};
	
	