/*
������ 10. 
�������� ��������, ��� ���������� ����� ����� �����, 
��� �������� ���������������
�� ��������, ������ ���� �� �������� 1, � ���� �� ����. 
*/

#include <iostream>
#include <Windows.h>

using namespace std;

void sort_array(int * array, int size_array);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int * array;
	int size_array;
	int numbers[99];
	cout << "������ �� ���� �������� � ����� ? : ";
	cin >> size_array;	
	array = new int[size_array];
	for (int i = 0; i < size_array; i++)
	{
		cout << "������ ������� �" << i + 1 << " : ";
		cin >> array[i]; 
	}
	sort_array(array, size_array);
	cout << "������� ����� : ";
	for (int i = 0; i < size_array; i++)
	{
		cout << array[i] << ", ";
	}
	return 0;
}

void sort_array(int * array, int size_array)
{
	int * temp_array = new int[size_array];
	int * helpme = new int[size_array];
	int element_number = 0;
	for (int i = 0; i < size_array; i++)
	{
		if (array[i] == 1 || array[i] == 0 || array[i] == -1)
		{
			temp_array[element_number] = array[i];
			element_number++;
			helpme[i] = 1;
		}
		else
			helpme[i] = 0;
	}
	for (int i = 0; i < size_array; i++)
	{
		if (helpme[i] == 0)
		{
			temp_array[element_number] = array[i];
			element_number++;
		}
	}
	for (int i = 0; i < size_array; i++)
	{
		array[i] = temp_array[i];
	}
}
