/*������ 10.
�������� ���������� ������� power (base, exponent), ��� ������� �������� baseexponent
.
���������, power(3, 4) = 3 * 3 * 3 * 3 . ����� exponent � �����, ������ ��� ����� 1.
ϳ������: ���� ������ �� �� ����������� ������������ baseexponent = base * baseexponent
, �
������������ ������ ���� �������, ���� �������� exponent ����� ����� 1.*/

#include <iostream>
#include <Windows.h>
#include <cmath>

using namespace std;

int power(int base, int exponent);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int base, exponent;
	another_try:
	cout << "������ ����� �� ���� ������ (����� �����) : ";
	cin >> base >> exponent;
	if (exponent < 1)
	{
		cout << "������ �������� ������� >=1 !\n";
		goto another_try;
	}
	power(base, exponent);
	//cout << "��������� : " << result;
	return 0;
}

int power(int base, int exponent)
{
	int result;
	if (exponent == 1)
		return (result);
	result = pow(base, exponent);
	cout << "��������� : " << result << "\n" << "base'n'exp : " << base << ", " << exponent << "\n";
	power(base, pow(base, exponent));
}
