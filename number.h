#pragma once
#include <list>
#include <string>

//���������� ������� ������� ����� 
class Number {
public:
	//����������� �� double
	Number(double value);

	//����������� �� ������
	Number(std::string &token);

	void init(std::string &token);

	//��������� � �����
	bool equalsZero() const;

	//������ ����� � ������
	void serialize(std::string &serialized) const;

	//���������� ��������� �������� ������
	Number operator-() const;

	//���������� ��������� ��������
	Number operator+(const Number &secondOperand) const;

	//���������� ��������� ���������
	Number operator-(const Number &secondOperand) const;

	//���������� ��������� ���������
	Number operator*(const Number &secondOperand) const;

	//���������� ��������� �������
	Number operator/(const Number &secondOperand) const;

	//������� ����������
	Number getFactorial() const;

	friend Number;

private:
	int numDigitsAfterPoint;
	bool sign;
	std::list<int> digits;

	//�������� �� ���������������
	bool lessThanZero() const;

	//�������� ������� �����
	void delFirstZeros();

	//��������
	Number sum(const Number &secondOperand) const;

	//���������
	Number diff(const Number &firstOperand, const Number &secondOperand) const;

	//���������
	Number mult(const Number &firstOperand, const Number &secondOperand) const;

	//��������� �� ������
	bool absoluteLess(const Number &secondOperand) const;

	//�������� �� �������������
	bool isNatural() const;
};