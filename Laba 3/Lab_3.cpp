/*
������ 9.
1. �������� �������, �� ������ ������� �������, ���������� ��� �� ���� ���������,
�������� ������ ���'��� �� ����� �������� ���������� ������ � �������� ���� ������ �
����� ������ (� ���������).
2. �������� �������, �� ������ ����� ����� � ����������� ��������� ����. ���� ����
������� ����� 200, �� ��� ��� ��� ������ � ���� �� �����������. ���������� ��� ���� �������
�������� � �������� ����, ��� ���� �������� �������� ��� ��� �� �������, ��'� ����
���������� � ��������� �����, � ���� � �� ��������.
3. �������� ������� ��������, �� ������� ���� �� ������ ��� ������� � ������� ���� ��
������� ����� ��� ���������� ����� (��� ���, ��� �� ������).
4. �� �������� ��� ��� ������� ������ ������������ �� �� ���������. ������������
���������� ������ � �������� �� �����������.
*/

#include <iostream>
#include <Windows.h>

using namespace std;

int command, scanners_count = 4;
bool specific_number;

struct scan_info
{
    char model[25]; //������������ �����
    int price; // ����
    double x_size; // ������ ���������� �������������� �����
    double y_size; // ������ ���������� ������������ �����
    int optr; // �������� �����
    int grey; // ����� �������� �����
};

void write_file(scan_info scanners[]);
void read_file(scan_info scanners[]);

int main()
{
	SetConsoleCP(1251); //���� 1251-����������
    SetConsoleOutputCP(1251); //���� 1251-����������
   	cout << "��� �� �� ������ ��������?\n";
   	cout << "(1) �������� ����� ���� �� ��������� ���� ������� ��� �������\n";
   	cout << "(2) �������� �������� ���� �� ���������� ��� ������� � �����\n";
 	scan_info *scanners = new scan_info[scanners_count]; //�������� ���������
   	cin >> command;
   	if (command == 1)
   		write_file(scanners);
   	else if (command == 2)
   	{
   		cout << "(3) �������� �� ������ ��� �������\n";
   		cout << "(4) �������� ������ ����� ��� ������, �� ���� �������\n";
   		cin >> command;
   		if (command == 3)
   			read_file(scanners);
   		else if (command == 4)
   		{
   			try_scanner_numba:
   			cout << "������ ����� ����������� ������� ��� ������ (�� 1)\n";
   			cin >> command;
   			if (command < 1)
   			{
				cout << "������� �����!";	 
				goto try_scanner_numba;  
			}	
   			specific_number = true;
   			read_file(scanners);
   		}
   	}
   	else
   	{
		cout << "������� ����� �������!";	   
	}		
	return 0;
}

void write_file(scan_info scanners[]) 
{
	FILE * f;
	char f_name[BUFSIZ];
	int temp_count = scanners_count;
	cout << "������ ��'� ����� : ";
	cin >> f_name;
	f = fopen(f_name, "wb");
	for (int i = 0; i < scanners_count; i++) 
	{
		cout << "\n������ ��������� " << i + 1 << "-�� ������� :\n";	
		cout << "������������ ����� : ";
		cin >> scanners[i].model;
		cout << "ֳ�� : ";
		cin >> scanners[i].price;
		cout << "�������������� ����� ������ ���������� : ";
		cin >> scanners[i].x_size;
		cout << "������������ ����� ������ ���������� : ";
		cin >> scanners[i].y_size;
		cout << "�������� ����� : ";
		cin >> scanners[i].optr;
		cout << "����� �������� ����� : ";
		cin >> scanners[i].grey;
	}	
	for (int i = 0; i < scanners_count-1; ++i) //������
	{
		int lowest = i;
		for (int j = i+1; j < scanners_count; ++j)
		{
			if (strcmp(scanners[i].model, scanners[j].model) > 0)
				lowest = j;
		}
		swap(scanners[i].model, scanners[lowest].model);
		swap(scanners[i].price, scanners[lowest].price);
		swap(scanners[i].x_size, scanners[lowest].x_size);
		swap(scanners[i].y_size, scanners[lowest].y_size);
		swap(scanners[i].optr, scanners[lowest].optr);
		swap(scanners[i].grey, scanners[lowest].grey);
	} 
	for (int i = 0; i < scanners_count-1; ++i) //��������� ��� ��� ��������
	{
		int lowest = i;
		for (int j = i+1; j < scanners_count; ++j)
		{
			if (strcmp(scanners[i].model, scanners[j].model) > 0)
				lowest = j;
		}
		swap(scanners[i].model, scanners[lowest].model);
		swap(scanners[i].price, scanners[lowest].price);
		swap(scanners[i].x_size, scanners[lowest].x_size);
		swap(scanners[i].y_size, scanners[lowest].y_size);
		swap(scanners[i].optr, scanners[lowest].optr);
		swap(scanners[i].grey, scanners[lowest].grey);
	} 
	for (int i = 0; i < scanners_count; i++) //������� �� ��-� �������, �, �� 200+ � ���
	{
		if (scanners[i].price < 200)
			temp_count--;
	}		
	fprintf(f, "%i;", temp_count);
	for (int i = 0; i < scanners_count; i++)
	{
		if (scanners[i].price < 200) //�, �� 200+ � ���, �� �����������
			continue;
		else
		{
			fprintf(f, "%s,", scanners[i].model);	
			fprintf(f, "%i,", scanners[i].price);
			fprintf(f, "%lf,", scanners[i].x_size);
			fprintf(f, "%lf,", scanners[i].y_size);
			fprintf(f, "%i,", scanners[i].optr);
			fprintf(f, "%i;", scanners[i].grey);	
		}
	}	
	fclose(f);
}

void read_file(scan_info scanners[]) 
{
	another_try:
	FILE * f;
	char f_name[50];
	cout << "������ ��'� ����� : ";
	cin >> f_name;
	f = fopen(f_name, "rb");	
	if (f == NULL) 
	{
		cout << "��������� ������� ����\n";
		goto another_try;
	}
	cout << "���� � ���� : \n\n";
	fscanf(f, "%i;", &scanners_count);
	if (specific_number != true)
		cout << "������ ������ � ���� : " << scanners_count << "\n\n";
	for (int i = 0; i < scanners_count; i++) 
	{
		for (int j = 0; j < 99; j++) //���������� ����������� char (�� 99 �������)
		{
			fscanf(f, "%c", &scanners[i].model[j]);
			if (scanners[i].model[j] == ',')
			{
		    	scanners[i].model[j] = '\0';
		    	break;
			}
		}
		fscanf(f, "%i,", &scanners[i].price);
		fscanf(f, "%lf,", &scanners[i].x_size);
		fscanf(f, "%lf,", &scanners[i].y_size);
		fscanf(f, "%i,", &scanners[i].optr);
		fscanf(f, "%i;", &scanners[i].grey);
		if (specific_number == true) //���� ���� ������� ������� 4 - ���������� ��� ��� ��� ���� ������
		{
			if (i == command-1)
			{
				cout << "������������ ����� : " << scanners[i].model << "\n";
				cout << "ֳ�� : " << scanners[i].price << "\n";
				cout << "�������������� ����� ������ ���������� : " << scanners[i].x_size << "\n";
				cout << "������������ ����� ������ ���������� : " << scanners[i].y_size << "\n";
				cout << "�������� ����� : " <<  scanners[i].optr << "\n";
				cout << "����� �������� ����� : " <<  scanners[i].grey << "\n\n";
			}	
		}
		else //���� 3 - ���������� �� ���
		{
			cout << "������������ ����� : " << scanners[i].model << "\n";
			cout << "ֳ�� : " << scanners[i].price << "\n";
			cout << "�������������� ����� ������ ���������� : " << scanners[i].x_size << "\n";
			cout << "������������ ����� ������ ���������� : " << scanners[i].y_size << "\n";
			cout << "�������� ����� : " <<  scanners[i].optr << "\n";
			cout << "����� �������� ����� : " <<  scanners[i].grey << "\n\n";
		}
	}	
	fclose(f);
}
