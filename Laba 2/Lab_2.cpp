/*
1. Створити програму на мові С згідно варіанту використавши середовище
програмування Dev-C++ 4.0:
*за допомогою текстового редактора створити файл, що містить текст, довжина
якого не перевищує 1000 символів (довжина рядка тексту не повинна
перевищувати 70 символів);
*ім'я файлу повинне мати розширення dat.
2. Відкомпілювати та відлагодити програму. 

Варіант 10.
Написати програму, яка виводить на екран символ, який зустрічається у файлі
максимальне число разів.
*/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <stdio.h>

using namespace std;

char mostUsed(string str);
 
int main(int argc, char** argv)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string str;
    char path[BUFSIZ];
    f_back:
    cout << "Введіть шлях до файлу (Приклад : D:\\\\КТП\\\\l2.dat) :\n";
    cin >> path;
    if ((fopen(path, "r")) == NULL)
    {
        cout << "Файл не існує у данному місці, перевірте правильність шляху" << endl;
        goto f_back;
    }
    cout << "Текст в файлі " << path << " :\n\n"; 
    ifstream read_n_check(path, std::ios::app);
    str.assign( (std::istreambuf_iterator<char>(read_n_check) ), (std::istreambuf_iterator<char>()  ) );
    if (str == "")
    {
    	cout << "Файл не містить будь-яких данних, це не задовільняє умовам задачі" << endl;
        goto f_back;
	}
    cout << str << std::endl;
    cout << "\nСимвол, що зустрічається максмальну кількість разів : " << mostUsed(str);
    read_n_check.close();
    return 0;
}

char mostUsed(string str) 
{
    vector<char> letters;
    for (int i = 0; i < str.size(); i++) 
    {
        if (i == 0) 
        {
            letters.push_back(str[i]);
            continue;
        }
        int count = 0;
        for (int j = 0; j < letters.size(); j++) 
        {
            if (str[i] == letters[j])
                break;
            else 
            {
                for (int k = 0; k < letters.size(); k++) 
                {
                    if (str[i] != letters[k])
                        count++;
                }
            }
            if (count == letters.size())
                letters.push_back(str[i]);
        }
    }
    vector<int> occur(letters.size());
    for (int i = 0; i < str.size(); i++) 
    {
        for (int j = 0; j < letters.size(); j++) 
        {
            if (str[i] == letters[j])
                occur[j]++;
        }
    }
    int maxAmount = -1, maxIndex = -1;
    for (int i = 0; i < letters.size(); i++) 
    {
        if (occur[i] > maxAmount) 
        {
            maxAmount = occur[i];
            maxIndex = i;
        }
    }
    return letters[maxIndex];
}
