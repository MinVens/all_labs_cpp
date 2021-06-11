/*Варіант 10.
Написати рекурсивну функцію power (base, exponent), яка повертає значення baseexponent
.
Наприклад, power(3, 4) = 3 * 3 * 3 * 3 . Нехай exponent є цілим, більшим або рівним 1.
Підказка: крок рекурсії міг би використати співвідношення baseexponent = base * power(base, exponent)
, а
завершальною умовою буде випадок, коли значення exponent стане рівним 1.*/

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
	cout << "Введіть число та його степінь (через пробіл) : ";
	cin >> base >> exponent;
	if (exponent < 1)
	{
		cout << "Введіть значення степеня >=1 !\n";
		goto another_try;
	}
	power(base, exponent);
	//cout << "Результат : " << result;
	return 0;
}

int power(int base, int exponent)
{
	double result;
	if (exponent == 1)
		return (result);
	result = pow(base, exponent);
	cout << "Результат : " << result << "\n";
	power(base, pow(base, exponent));
}
