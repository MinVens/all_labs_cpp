/*
Варіант 1. Клас «Залікова книжка»
. Закриті дані-члени класу: - Прізвище студента; - Номер залікової книжки. Відкриті функції-члени класу: - Ініціалізація (введення через аргументи функції інформації у дані-члени класу); - Виведення на екран інформації збереженої в даних-членах.
2.Створити структуру «Дисципліна»:
- Дисципліна;
- Оцінка;
- Прізвище викладача.
До закритих даних-членів добавити:
- назва факультету (статичний елемент);
До відкритих функцій-членів добавити:
- функцію яка виводить на екран назву факультету (статичний елемент);
Створити два конструктори, які будуть зчитувати дані для заповнення масиву структур та даних-членів класу з текстового файлу. Перший конструктор без параметрів. В другий конструктор через параметр зчитується назва текстового файлу.
У конструкторі створити динамічний масив, з елементами типу «Дисципліна». Кількість елементів задається з файлу.
Деструктор має виводити на екран вміст об’єкту типу «Залікова книжка».
Приклад текстового файлу (zk.txt):
2
Васаженко
А-111111
АМтаПР
3
Яценюк
Фізика
3
Ющенко
*/

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
	void birth() //виведення дати народження
	{
		cout << "Дата народження : " << date_of_birth << "\n";
	}
	void commentary_set() //включення коментарів у файлі
	{
		commentary_is_written = true;
	}
	void without_commentary_set() //відключення коментарів у файлі
	{
		commentary_is_written = false;
	}
	Record() //видалення будь-яких данних з елементів
	{
		teacher_surname = NULL;
		telephone_number = NULL;
		date_of_birth = NULL;
		commentary = NULL;
	}
	Record(char * teacher_surname, char * telephone_number, char * date_of_birth) //запис у структуру елементів
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
	~Record() //видалення елементів з озу (деструктор)
	{
		delete [] teacher_surname;
		delete [] date_of_birth;
		delete [] telephone_number;
		delete [] commentary;
	}
};

class notebook
{
private: //приватні (тільки в межах класу) записи данних
	char * teacher_surname;
	char * telephone_number;
	int count_of_records;
	Record * record; //об'єкт структури record
public: //публічні записи данних
	notebook(char * f_name) 
	{
		char char_temp[255];
    	FILE * f = fopen(f_name, "r");
		fscanf(f, "%i\n", &count_of_records); //отримання данних про кількість записів
		this->record = new Record[count_of_records]; //створення динамічного масиву структур		
		for (int i = 0; i < count_of_records; i++) //отримання інформації з файлу у структуру record
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
	
	~notebook() //виведення данних, записаних у структуру
	{
		for (int i = 0; i < count_of_records; i++) 
		{
			cout << "Призвіще викладача : " << record[i].teacher_surname << "\n";
			cout << "Телефон : " << record[i].telephone_number << "\n";
			cout << "Дата народження : " << record[i].date_of_birth << "\n\n";
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
	cout << "(1) Прочитати файл\n(2) Вийти з програми\n";
	cin >> command;
	if (command == 1) 
	{
		cout << "Введіть ім'я файла : ";
		cin >> f_name;
		if ((fopen(f_name, "r")) == NULL)
    	{
        cout << "Файл не існує у данному місці, перевірте існування файлу!" << endl;
        goto try_again;
    	}
    	notebook myObject(f_name); //відкриття об'єкту Notebook
	}
	else if (command == 2)
		return 0;
}

void copy(char * text_1, char * text_2) //копіювання данних типу char
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

int length(char * text) //обрахування довжини змінної типу char
{
	int i = 0;
	for ( ; text[i] != '\0'; i++) {}
	return i;
}
