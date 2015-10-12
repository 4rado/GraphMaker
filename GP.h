#pragma once

#define M_PI       3,1415926535897932384626433

#include <vector> 
#include <math.h>
#include "RotationLib.h"
#include "mathCore.h"


// Graph in Points
// ������ ����� ������������ ��� ����������� ������������� ������� � ����������� �� ��������� ���� 
class GP {
public:
	// �������� �� ���� �����, ����� ������� �����, � ���� ��� �������� ����������� ��� �� ��������� � ������������ ��������� ��� X(----->)
	GP( const MathCore& inputMCore, double inputLengthOfSection = 5, 
		const std::vector<double>& inputAnglesOfAxis = { -30, 40, 90 }, 
		std::pair<double, double> inputWindowSize = std::pair<double, double>(700, 700) );
	// ������� ������ ��� Z
	void turnAroundZ( int angle = 1 );
	// ������� ������ ��� Y
	void turnAroundY( int angle = 1 );
	// ������� ������ ��� X
	void turnAroundX( int angle = 1 );
	// ������� ������ ������������� �������
	void turnRoundVector( int angle, Vector vector );
	// �������� �� ���������
	void moveAlongX( int num );
	// �������� �� �����������
	void moveAlongY( int num );
	// �������� �������
	void changeScale( int num );
	// ���������� ��������� ������������� �����
	std::vector<std::vector<std::pair<double, double>>> getRelativePoints();
	// ���������� ������������ ������ ������ ���� X - 0, Y - 1, Z - 2
	std::pair<double, double> getAxisVector( int axisNum );
	// ���������� ������������ ������ � ������������ ��� ���������� WinApi
	std::pair<double, double> getAxisVectorVisual( int axisNum );
	// ���������� ���������� ����������� ���� � 2d
	std::pair<double, double> getOriginCoordinates();
	// ����������� �������� ������ ���������
private:
	// �������� ��������� ����� ������������ ����
	void calculateRelativePoints();
	// ������� ����� � ����������� �� ������� ������
	void generateGrid();

	void GP::rotateToStartAngle();
	void GP::rotateToCurrentAngle();
	
	
	// ����� �����������, � �������� �������� - ���� ����� XY
	std::vector<std::vector<double>> points;
	// ���� ��� �������� ����������� ��������( ����������� ) ��� �� 2D �� ��������� � ����������� ��� X
	std::vector< double > anglesOfAxis;
	// �������������( ��������� ) ��� ����������� ������ ��� ������� �������
	std::vector< Vector > relativeAxis;
	std::vector< Vector > prevRelativeAxis;
	// ������������� ����� ��� � 2D, � �������� �������� ����������� ����� X, Y 
	std::vector<std::vector<std::pair<double, double>>> relativePoints;
	// ����� ������� �����
	double lengthOfSection;
	// ���������� ����������� ���� � 2D
	std::pair<double, double> origin;
	// ���������� ������ ����
	std::pair<double, double> windowSize;
	// ������������� ���������� � ����������� �� �������� �� ������ ����
	MathCore mCore;
};