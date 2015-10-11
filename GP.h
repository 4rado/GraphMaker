#pragma once

#define M_PI       3,1415926535897932384626433

#include <vector> 
#include <math.h>
#include "RotationLib.h"
#include "mathCore.h"
using namespace std;

// Graph in Points
// ������ ����� ������������ ��� ����������� ������������� ������� � ����������� �� ��������� ���� 
class GP {
public:
	// �������� �� ���� �����, ����� ������� �����, � ���� ��� �������� ����������� ��� �� ��������� � ������������ ��������� ��� X(----->)
	GP( const MathCore& inputMCore, double inputLengthOfSection = 5, 
		const vector<double>& inputAnglesOfAxis = { -30, 40, 90 }, 
		pair<double, double> inputWindowSize = pair<double, double>(700, 700) );
	// ������� ������ ��� Z
	void turnAroundZ( int angle = 1 );
	// ������� ������ ��� Y
	void turnAroundY( int angle = 1 );
	// ������� ������ ��� X
	void turnAroundX( int angle = 1 );
	// ������� ������ ������������� �������
	void turnRoundVector( int angle, Vector vector );
	// �������� �� ���������
	void moveOverX( int num );
	// �������� �� �����������
	void moveOverY( int num );
	// �������� �������
	void changeScale( int num );
	// ���������� ��������� ������������� �����
	vector<vector<pair<double, double>>> getRelativePoints();
	// ���������� ������������ ������ ������ ���� X - 0, Y - 1, Z - 2
	pair<double, double> getAxisVector( int axisNum );
	// ���������� ������������ ������ � ������������ ��� ���������� WinApi
	pair<double, double> getAxisVectorVisual( int axisNum );
	// ���������� ���������� ����������� ���� � 2d
	pair<double, double> getOriginCoordinates();
	// ����������� �������� ������ ���������
private:
	// �������� ��������� ����� ������������ ����
	void calculateRelativePoints();
	// ������� ����� � ����������� �� ������� ������
	void generateNet();
	
	
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
	// ���������� ������ ����
	pair<double, double> windowSize;
	// ������������� ���������� � ����������� �� �������� �� ������ ����
	MathCore mCore;
};