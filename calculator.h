#pragma once
#include "number.h"
#include <string>
#include <stack>

class Calculator {
public:
	//����������� ������������
	Calculator(const std::string &_formula);

	//������� �������� ���������
	Number countExpression(Number &xArgument, Number &yArgument);
	
private:
	const std::string formula;
	std::stack<Number> numbers; //���� ��� �����
	std::stack<std::string> operations; //���� ��� ��������

	//��������� ����� ��� ���������� ��������
	Number getOperand();

	//������� ������� � ����� ��������
	void countOperation();

	//��������� ���������� ��������
	int getPriority(const std::string &operation);
};