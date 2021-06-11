#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

void copy(char * text_1, char * text_2);
int length(char * text);

struct Record
{
public:
	char * teacher_surname;
	char * telephone_number;
	char * date_of_birth;
	char * commentary;
	bool commentary_is_written = false;
	void birth() //��������� ���� ����������
	{
		cout << "���� ���������� : " << date_of_birth << "\n";
	}
	void commentary_set() //��������� ��������� � ����
	{
		commentary_is_written = true;
	}
	void without_commentary_set() //���������� ��������� � ����
	{
		commentary_is_written = false;
	}
	Record() //��������� ����-���� ������ � ��������
	{
		teacher_surname = NULL;
		telephone_number = NULL;
		date_of_birth = NULL;
		commentary = NULL;
	}
	Record(char * teacher_surname, char * telephone_number, char * date_of_birth) //����� � ��������� ��������
	{
		this->teacher_surname = new char[length(teacher_surname)];
		this->date_of_birth = new char[length(date_of_birth)];
		this->telephone_number = new char[length(telephone_number)];
		this->commentary = new char[length(commentary)];		
		copy(teacher_surname, this->teacher_surname);
		copy(date_of_birth, this->date_of_birth);
		copy(telephone_number, this->telephone_number);
		copy(commentary, this->commentary);
	}
	~Record() //��������� �������� � ��� (����������)
	{
		delete [] teacher_surname;
		delete [] date_of_birth;
		delete [] telephone_number;
		delete [] commentary;
	}
};

class notebook
{
private: //������� (����� � ����� �����) ������ ������
	char * teacher_surname;
	char * telephone_number;
	int count_of_records;
	Record * record; //��'��� ��������� record
public: //������ ������ ������
	notebook(char * f_name) 
	{
		char char_temp[255];
    	FILE * f = fopen(f_name, "r");
		fscanf(f, "%i\n", &count_of_records); //��������� ������ ��� ������� ������
		this->record = new Record[count_of_records]; //��������� ���������� ������ ��������		
		for (int i = 0; i < count_of_records; i++) //��������� ���������� � ����� � ��������� record
		{
			fscanf(f, "%s\n", char_temp);
			record[i].teacher_surname = new char[strlen(char_temp)];
			strcpy(record[i].teacher_surname, char_temp);	
			fscanf(f, "%s\n", char_temp);
			record[i].telephone_number = new char[strlen(char_temp)];
			strcpy(record[i].telephone_number, char_temp);	
			fscanf(f, "%s\n", char_temp);
			record[i].date_of_birth = new char[strlen(char_temp)];
			strcpy(record[i].date_of_birth, char_temp);
		}
		fclose(f);
	}
	
	~notebook() //��������� ������, ��������� � ���������
	{
		for (int i = 0; i < count_of_records; i++) 
		{
			cout << "������� ��������� : " << record[i].teacher_surname << "\n";
			cout << "������� : " << record[i].telephone_number << "\n";
			cout << "���� ���������� : " << record[i].date_of_birth << "\n\n";
		}
	}
};

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//notebook myObject("as.txt"); 
	int command;
	char f_name[255];
	try_again:
	cout << "(1) ��������� ����\n(2) ����� � ��������\n";
	cin >> command;
	if (command == 1) 
	{
		cout << "������ ��'� ����� : ";
		cin >> f_name;
		if ((fopen(f_name, "r")) == NULL)
    	{
        cout << "���� �� ���� � ������� ����, �������� ��������� �����!" << endl;
        goto try_again;
    	}
    	notebook myObject(f_name); //�������� ��'���� Notebook
	}
	else if (command == 2)
		return 0;
}

void copy(char * text_1, char * text_2) //��������� ������ ���� char
{
	for (int i = 0 ; text_1[i] != '\0'; i++) 
	{
		text_2[i] = text_1[i];
	}
	for (int i = 0 ; text_2[i] != '\0'; i++) 
	{
		text_2[i] = '\0';
	}
}

int length(char * text) //����������� ������� ����� ���� char
{
	int i = 0;
	for ( ; text[i] != '\0'; i++) {}
	return i;
}
