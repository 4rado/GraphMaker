#pragma once

#define M_PI       3.14159265358979323846

#include <vector> 
#include <math.h>
using namespace std;

// Graph in Points
// ������ ����� ������������ ��� ����������� ������������� ������� � ����������� �� ��������� ���� 
class GP {
public:
	// �������� �� ���� �����, ����� ������� �����, � ���� ��� �������� ����������� ��� �� ��������� � ������������ ��������� ��� X(----->)
	GP( const vector<vector<double>>& inputPoints, double inputLengthOfSection = 1, const vector<double>& inputAnglesOfAxis = { 0, 45, 90 } );
	GP();
	void TurnFromTheTopToDown( int angle = 1 );
	void TurnClockwise();
	// ���������� ��������� ������������� �����
	vector<vector<pair<double, double>>> GetRelativePoints();
	// ���������� ������������ ������ ������ ���� X - 0, Y - 1, Z - 2
	pair<double, double> getAxisVector( int axisNum );
	
private:
	// �������� ��������� ����� ������������ ����
	void CalculateRelativePoints();
	// ����� �����������, � �������� �������� - ���� ����� XY
	vector<vector<double>> points;
	// ���� ��� �������� ����������� ��� �� ��������� � ����������� ��� X
	vector< double > anglesOfAxis;
	// ������������� ����� ��� � 2d, � �������� �������� ����������� ����� X, Y 
	vector<vector<pair<double, double>>> relativePoints;
	// ����� ������� �����
	double lengthOfSection;
};