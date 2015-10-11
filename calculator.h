#pragma once
#include <string>
#include <stack>

class Calculator {
public:
	//����������� ������������
	Calculator(const std::string &_formula);

	//������� �������� ���������
	double countExpression(double xArgument, double yArgument);
	
private:
	const std::string formula;
	std::stack<double> numbers; //���� ��� �����
	std::stack<std::string> operations; //���� ��� ��������

	//��������� ����� ��� ���������� ��������
	double getOperand();

	//������� ������� � ����� ��������
	void countOperation();

	//��������� ���������� ��������
	int getPriority(std::string &operation);
};