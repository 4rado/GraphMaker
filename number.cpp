#include <sstream>
#include "number.h"

const int DIGITS_AFTER_POINT_NUM = 5;
static_assert(DIGITS_AFTER_POINT_NUM <= 7, "too much digits after point");

void Number::init(std::string &token) {
	sign = true;
	bool isFractional = false;

	int startPosition = 0;
	if (token[0] == '-') {
		sign = false;
		startPosition = 1;
	}

	for (size_t position = startPosition; position < token.length(); ++position) {
		if (token[position] == '.') {
			isFractional = true;
			for (int afterPointPosition = 1; afterPointPosition <= numDigitsAfterPoint; ++afterPointPosition) {
				if (position + afterPointPosition < token.length()) {
					digits.push_front(token[position + afterPointPosition] - '0');
				}
				else {
					digits.push_front(0);
				}
			}
			break;
		}
		else {
			digits.push_front(token[position] - '0');
		}
	}

	if (!isFractional) { //���������� ������ ����� �����
		for (int afterPointPosition = 0; afterPointPosition < numDigitsAfterPoint; ++afterPointPosition) {
			digits.push_front(0);
		}
	}
}

//����������� �� ������
Number::Number(std::string &token) :
	numDigitsAfterPoint(DIGITS_AFTER_POINT_NUM)
{
	init(token);
}

//����������� �� double
Number::Number(double value) :
	numDigitsAfterPoint(DIGITS_AFTER_POINT_NUM)
{
	std::ostringstream stringstream;
	stringstream << value;
	std::string str = stringstream.str();
	init(stringstream.str());
}

//�������� �� ���������������
bool Number::lessThanZero() const {
	return !sign;
}

//�������� ������� �����
void Number::delFirstZeros() {
	while ((*digits.rbegin() == 0) && (digits.size() > numDigitsAfterPoint + 1)) {
		digits.pop_back();
	}
}

//��������
Number Number::sum(const Number &secondOperand) const {
	Number result = *this;
	int shift = 0; //������� �������
	std::list<int>::iterator curElement = result.digits.begin(); // �������� �� �������� ����������
	for (std::list<int>::const_iterator plusElement = secondOperand.digits.cbegin(); plusElement != secondOperand.digits.cend(); ++plusElement) {
		if (curElement == result.digits.end()) { //�������� �� ������� ������� ��� ���������� �������
				result.digits.push_back((*plusElement) + shift);
				curElement = --result.digits.end();
			}
		else {
			*curElement = (*curElement) + (*plusElement) + shift;
		}
		shift = *curElement / 10;
		*curElement %= 10;
		++curElement;
	}
	while (shift != 0) { //���������� ���������� ��������� �������
		if (curElement == result.digits.end()) { //�������� �� ������� ������� ��� ���������� �������
			result.digits.push_back(shift);
			curElement = --result.digits.end();
		}
		else {
			*curElement = (*curElement) + shift;
		}
		shift = *curElement / 10;
		*curElement %= 10;
		++curElement;
	}
	result.delFirstZeros();
	return result;
}

//���������
Number Number::diff(const Number &firstOperand, const Number &secondOperand) const {
	Number result = firstOperand;
	int shift = 0; //������� �������
	std::list<int>::iterator curElement = result.digits.begin(); // �������� �� �������� ����������
	for (std::list<int>::const_iterator plusElement = secondOperand.digits.cbegin(); plusElement != secondOperand.digits.cend(); ++plusElement) {
		if (curElement == result.digits.end()) { //�������� �� ������� ������� ��� ���������� �������
			result.digits.push_back((*plusElement) + shift);
			curElement = --result.digits.end();
		}
		else {
			*curElement = (*curElement) - (*plusElement) + shift;
		}
		shift = 0;
		if (*curElement < 0) {
			*curElement += 10;
			shift -= 1;
		}
		++curElement;
	}
	while (shift != 0) { //���������� ���������� ��������� �������
		if (curElement == result.digits.end()) { //�������� �� ������� ������� ��� ���������� �������
			result.digits.push_back(shift);
			curElement = --result.digits.end();
		}
		else {
			*curElement = (*curElement) + shift;
		}
		shift = 0;
		if (*curElement < 0) {
			*curElement += 10;
			shift -= 1;
		}
		++curElement;
	}
	result.delFirstZeros();
	return result;
}

//���������
Number Number::mult(const Number &firstOperand, const Number &secondOperand) const {
	Number result(std::string("0"));
	std::list<int>::iterator resFirstElement = result.digits.begin();
	for (std::list<int>::const_iterator multElement = secondOperand.digits.cbegin(); multElement != secondOperand.digits.cend(); ++multElement) {
		int shift = 0; //������� �������
		std::list<int>::iterator resElement = resFirstElement; // �������� �� �������� ����������
		for (std::list<int>::const_iterator curElement = firstOperand.digits.cbegin(); curElement != firstOperand.digits.cend(); ++curElement) {
			if (resElement == result.digits.end()) { //�������� �� ������� ������� ��� ���������� �������
				result.digits.push_back((*multElement) * (*curElement) + shift);
				resElement = --result.digits.end();
			}
			else {
				*resElement = (*resElement) + (*multElement) * (*curElement) + shift;
			}
			shift = *resElement / 10;
			*resElement %= 10;
			++resElement;
		}
		while (shift != 0) { //���������� ���������� ��������� �������
			if (resElement == result.digits.end()) { //�������� �� ������� ������� ��� ���������� �������
				result.digits.push_back(shift);
				resElement = --result.digits.end();
			}
			else {
				*resElement = (*resElement) + shift;
			}
			shift = *resElement / 10;
			*resElement %= 10;
			++resElement;
		}
		++resFirstElement;
	}
	result.delFirstZeros();
	return result;
}

//��������� �� ������
bool Number::absoluteLess(const Number &secondOperand) const {
	if (secondOperand.digits.size() > (*this).digits.size()) {
		return true;
	}
	if (secondOperand.digits.size() < (*this).digits.size()) {
		return false;
	}
	std::list<int>::const_reverse_iterator firstElement = digits.crbegin();
	for (std::list<int>::const_reverse_iterator secondElement = secondOperand.digits.crbegin(); secondElement != secondOperand.digits.crend(); ++secondElement) {
		if (*firstElement < *secondElement) {
			return true;
		}
		if (*firstElement > *secondElement) {
			return false;
		}
		++firstElement;
	}
	return false;
}

//�������� �� �������������
bool Number::isNatural() const {
	std::list<int>::const_iterator element = digits.cbegin();
	for (int position = 0; position < numDigitsAfterPoint; ++position) {
		if (*element != 0) {
			return false;
		}
		++element;
	}
	return true;
}

//��������� � �����
bool Number::equalsZero() const {
	for (std::list<int>::const_iterator curElement = digits.cbegin(); curElement != digits.cend(); ++curElement) {
		if (*curElement != 0) {
			return false;
		}
	}
	return true;
}

//������ ����� � ������
void Number::serialize(std::string &serialized) const {
	serialized = "";
	if ((!(*this).sign) && (!equalsZero())) { //�������� ���������������
		serialized += '-';
	}
	int count = 0;
	for (std::list<int>::const_reverse_iterator curElement = digits.crbegin(); curElement != digits.crend(); ++curElement) {
		if (digits.size() - count == numDigitsAfterPoint) { //�������� ������� ��� �����
			serialized += '.';
		}
		serialized += ('0' + *curElement);
		++count;
	}
}

//���������� ��������� �������� ������
Number Number::operator-() const {
	Number result = *this;
	result.sign = !result.sign;
	return result;
}

//���������� ��������� ��������
Number Number::operator+(const Number &secondOperand) const {
	if (!(secondOperand.sign ^ (*this).sign)) { //�������� �� ���������� �����
		return sum(secondOperand);
	}
		else {
			if (absoluteLess(secondOperand)) {
				return diff(secondOperand, *this);
			}
			else {
				return diff(*this, secondOperand);
			}
		}
	}

//���������� ��������� ���������
Number Number::operator-(const Number &secondOperand) const {
	return *this + (-secondOperand);
}

//���������� ��������� ���������
Number Number::operator*(const Number &secondOperand) const {
	int resultDigitsAfterPoint = numDigitsAfterPoint + numDigitsAfterPoint;

	Number result(std::string("0"));
	Number positiveFirstOperand = *this;
	Number positiveSecondOperand = secondOperand;
	Number one(resultDigitsAfterPoint);

	positiveFirstOperand.numDigitsAfterPoint = resultDigitsAfterPoint;
	positiveSecondOperand.numDigitsAfterPoint = resultDigitsAfterPoint;
	one.numDigitsAfterPoint = resultDigitsAfterPoint;

	for (int position = 0; position < numDigitsAfterPoint; ++position) {
		positiveFirstOperand.digits.push_back(0);
		positiveSecondOperand.digits.push_back(0);
	}

	result.sign = true;
	positiveFirstOperand.sign = true;
	positiveSecondOperand.sign = true;

	if (positiveFirstOperand.absoluteLess(positiveSecondOperand)) {
		result = mult(positiveSecondOperand, positiveFirstOperand);
	}
	else {
		result = mult(positiveFirstOperand, positiveSecondOperand);
	}

	for (int position = 1; position < numDigitsAfterPoint; ++position) { //�������� ������ �������� ����� �������
		result.digits.pop_front();
	}

	if (numDigitsAfterPoint > 0) {
		if (*result.digits.begin() >= 5) { //���������� �� ������ ��������
			*(++result.digits.begin()) += 1;
		}
		result.digits.pop_front();
	}

	result.numDigitsAfterPoint = numDigitsAfterPoint;
	result.sign = !((*this).sign ^ secondOperand.sign); //����������� ����� ���������
	return result;
}

//���������� ��������� �������
Number Number::operator/(const Number &secondOperand) const {
	if (secondOperand.equalsZero()) {
		throw std::logic_error("/ by zero");
	}

	Number result(std::string("0"));
	Number theLeast(std::string("1"));

	Number positiveFirstOperand = (*this);
	positiveFirstOperand.sign = true;

	Number previousFirstOperand(std::string("0"));
	Number previousResult(std::string("0"));
	Number positiveSecondOperand = secondOperand;
	positiveSecondOperand.sign = true;

	for (int position = 0; position <= numDigitsAfterPoint; ++position) {
		while (!positiveFirstOperand.lessThanZero()) {   //��������� ������� ������
			positiveFirstOperand = positiveFirstOperand - positiveSecondOperand;
			result = result + theLeast;
		}

		previousFirstOperand = positiveFirstOperand;
		previousResult = result;

		positiveFirstOperand = positiveFirstOperand + positiveSecondOperand;
		result = result - theLeast;

		//�������� �� ���� ������
		theLeast.digits.push_back(0);
		theLeast.digits.pop_front();
		positiveSecondOperand = secondOperand * theLeast;
		positiveSecondOperand.sign = true;
	}

	if (positiveFirstOperand.absoluteLess(previousFirstOperand)) {
		return result;
	}
	else {
		return previousResult;
	}
}

//������� ����������
Number Number::getFactorial() const {
	if (!isNatural()) {
		throw std::logic_error("wrong expression");
	}

	Number result(std::string("1"));
	Number operand(std::string("1"));
	Number one(std::string("1"));

	while (operand.absoluteLess(*this)) {
		operand = operand + one;
		result = result * operand;
	}

	return result;
}