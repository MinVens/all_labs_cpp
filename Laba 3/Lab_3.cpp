/*
Варіант 9.
1. Написати функцію, що запитує кількість сканерів, інформація про які буде вводитися,
динамічно виділяє пам'ять під масив структур відповідного розміру і заповнює його даними в
режимі діалогу (з клавіатури).
2. Написати функцію, що записує даний масив у створюваний текстовий файл. Якщо ціна
сканера менше 200, то дані про цей сканер у файл не записуються. Інформація про інші сканери
міститься в бінарному файлі, при чому спочатку пишуться дані про всі сканери, ім'я яких
починається з заголовної букви, а потім – із прописної.
3. Привести приклад програми, що створює файл із даними про сканери і здійснює вивід на
дисплей даних про необхідний запис (або всіх, або по номеру).
4. Усі необхідні дані для функцій повинні передаватися їм як параметри. Використання
глобальних змінних в функціях не допускається.
*/

#include <iostream>
#include <Windows.h>

using namespace std;

int command, scanners_count = 4;
bool specific_number;

struct scan_info
{
    char model[25]; //найменування моделі
    int price; // ціна
    double x_size; // області сканування горизонтальний розмір
    double y_size; // області сканування вертикальний розмір
    int optr; // оптичний дозвіл
    int grey; // число градацій сірого
};

void write_file(scan_info scanners[]);
void read_file(scan_info scanners[]);

int main()
{
	SetConsoleCP(1251); //Ввод 1251-Киррилицею
    SetConsoleOutputCP(1251); //Вивід 1251-Киррилицею
   	cout << "Яку дію ви бажаєте виконати?\n";
   	cout << "(1) Створити новий файл та заповнити його данними про сканери\n";
   	cout << "(2) Показати існуючий файл та інформацію про сканери в ньому\n";
 	scan_info *scanners = new scan_info[scanners_count]; //динамічна структура
   	cin >> command;
   	if (command == 1)
   		write_file(scanners);
   	else if (command == 2)
   	{
   		cout << "(3) Показати всі записи про сканери\n";
   		cout << "(4) Показати певний запис про сканер, за його номером\n";
   		cin >> command;
   		if (command == 3)
   			read_file(scanners);
   		else if (command == 4)
   		{
   			try_scanner_numba:
   			cout << "Введіть номер необхідного сканера для показу (від 1)\n";
   			cin >> command;
   			if (command < 1)
   			{
				cout << "Невірний номер!";	 
				goto try_scanner_numba;  
			}	
   			specific_number = true;
   			read_file(scanners);
   		}
   	}
   	else
   	{
		cout << "Невірний номер команди!";	   
	}		
	return 0;
}

void write_file(scan_info scanners[]) 
{
	FILE * f;
	char f_name[50];
	int temp_count = scanners_count;
	cout << "Введіть ім'я файлу : ";
	cin >> f_name;
	f = fopen(f_name, "wb");
	for (int i = 0; i < scanners_count; i++) 
	{
		cout << "\nВведіть параметри " << i + 1 << "-го сканера :\n";	
		cout << "Найменування моделі : ";
		cin >> scanners[i].model;
		cout << "Ціна : ";
		cin >> scanners[i].price;
		cout << "Горизонтальний розмір області сканування : ";
		cin >> scanners[i].x_size;
		cout << "Вертикальний розмір області сканування : ";
		cin >> scanners[i].y_size;
		cout << "Оптичний дозвіл : ";
		cin >> scanners[i].optr;
		cout << "Число градацій сірого : ";
		cin >> scanners[i].grey;
	}	
	for (int i = 0; i < scanners_count-1; ++i) //сортую
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
	for (int i = 0; i < scanners_count-1; ++i) //повторний раз для надійнсоті
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
	for (int i = 0; i < scanners_count; i++) //віднімаємо від кіл-ті сканерів, ті, які 200+ в ціні
	{
		if (scanners[i].price < 200)
			temp_count--;
	}		
	fprintf(f, "%i;", temp_count);
	for (int i = 0; i < scanners_count; i++)
	{
		if (scanners[i].price < 200) //ті, які 200+ в ціні, не записуються
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
	cout << "Введіть ім'я файлу : ";
	cin >> f_name;
	f = fopen(f_name, "rb");	
	if (f == NULL) 
	{
		cout << "Неможливо відкрити файл\n";
		goto another_try;
	}
	cout << "Данні у файлі : \n\n";
	fscanf(f, "%i;", &scanners_count);
	if (specific_number != true)
		cout << "Всього записів у файлі : " << scanners_count << "\n\n";
	for (int i = 0; i < scanners_count; i++) 
	{
		for (int j = 0; j < 99; j++) //зчитування посимвольно char (до 99 символів)
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
		if (specific_number == true) //якщо була вибрана команда 4 - показувати дані лиш про один сканер
		{
			if (i == command-1)
			{
				cout << "Найменування моделі : " << scanners[i].model << "\n";
				cout << "Ціна : " << scanners[i].price << "\n";
				cout << "Горизонтальний розмір області сканування : " << scanners[i].x_size << "\n";
				cout << "Вертикальний розмір області сканування : " << scanners[i].y_size << "\n";
				cout << "Оптичний дозвіл : " <<  scanners[i].optr << "\n";
				cout << "Число градацій сірого : " <<  scanners[i].grey << "\n\n";
			}	
		}
		else //якщо 3 - показувати всі дані
		{
			cout << "Найменування моделі : " << scanners[i].model << "\n";
			cout << "Ціна : " << scanners[i].price << "\n";
			cout << "Горизонтальний розмір області сканування : " << scanners[i].x_size << "\n";
			cout << "Вертикальний розмір області сканування : " << scanners[i].y_size << "\n";
			cout << "Оптичний дозвіл : " <<  scanners[i].optr << "\n";
			cout << "Число градацій сірого : " <<  scanners[i].grey << "\n\n";
		}
	}	
	fclose(f);
}
