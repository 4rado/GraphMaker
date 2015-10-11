#pragma once
#define M_PI       3.1415926535897932384

class Vector{
public:	
	Vector();
	Vector( double inputX, double inputY, double inputZ );
	void initialize( double inputX, double inputY, double inputZ );
	void operator =( const Vector& vect );
	void normalize();
	double x;
	double y;
	double z;
};

// ��� ����������� ���������������
class Quaternion {
public:
	Quaternion();
	Quaternion( double inputW, const Vector& vect );
	Quaternion( double inputW, double inputAngle, double inputY, double inputZ );
	Quaternion getInversedQuaternion();
	// �������� ������ ������� ����� ��������� �� ���� � ������ ��� ���������� ������������ 
	Vector makeRotation( const Vector& vect );
	void initialize( double inputW, const Vector& vect );
	void Quaternion::initialize( double inputAngle, double inputX, double inputY, double inputZ );
	void operator =( const Quaternion& quat );
	Quaternion operator *( const Quaternion& quat );
	double w;
	double x;
	double y;
	double z;
};
