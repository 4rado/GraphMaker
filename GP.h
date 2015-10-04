#pragma once

#define M_PI       3.14159265358979323846

#include <vector> 
#include <math.h>
#include "RotationLib.h"
using namespace std;

// Graph in Points
// ������ ����� ������������ ��� ����������� ������������� ������� � ����������� �� ��������� ���� 
class GP {
public:
	// �������� �� ���� �����, ����� ������� �����, � ���� ��� �������� ����������� ��� �� ��������� � ������������ ��������� ��� X(----->)
	GP( const vector<vector<double>>& inputPoints, double inputLengthOfSection = 1, const vector<double>& inputAnglesOfAxis = { 0, 45, 90 } );
	GP();
	void turnFromTheTopToDown( int angle = 1 );
	void turnClockwise( int angle = 1 );
	void turnRoundVector( int angle, Vector vector );
	// ���������� ��������� ������������� �����
	vector<vector<pair<double, double>>> GetRelativePoints();
	// ���������� ������������ ������ ������ ���� X - 0, Y - 1, Z - 2
	pair<double, double> getAxisVector( int axisNum );
	// ���������� ���������� ����������� ���� � 2d
	pair<double, double> getOriginCoordinates();
	
private:
	// �������� ��������� ����� ������������ ����
	void calculateRelativePoints();
	
	
	
	// ����� �����������, � �������� �������� - ���� ����� XY
	vector<vector<double>> points;
	// ���� ��� �������� ����������� ��������( ����������� ) ��� �� 2D �� ��������� � ����������� ��� X
	vector< double > anglesOfAxis;
	// �������������( ��������� ) ��� ����������� ������ ��� ������� �������
	vector< Vector > relativeAxis;
	// ������������� ����� ��� � 2D, � �������� �������� ����������� ����� X, Y 
	vector<vector<pair<double, double>>> relativePoints;
	// ����� ������� �����
	double lengthOfSection;
	// ���������� ����������� ���� � 2D
	pair<double, double> origin;
};