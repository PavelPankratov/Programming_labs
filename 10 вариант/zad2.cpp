#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <locale>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//тип данных для информации о лицензии
struct Characteristic {
    char weight[25];
    int power;
    int voltage;
};


//тип данных для машины
struct SolarPanel {
    char model[25];
    int price;
    int year;
    char material[25];
    Characteristic characteristic;
};

//тип данных для имени файла
typedef char TName[25];
//тип данных для файловой переменной
typedef FILE TFile;
//переменная для панели
SolarPanel solarPanel;
//переменная для имени файла
TName NameFile;
//файловая переменная
TFile *f;
//флаг выбора файла для работы
int flag = 0;

//** вывод меню ************************************************************
void menu(void) {
    system("cls");
    cout << "******** М Е Н Ю ********\n\n"
         << "[1]-Создание/открытие типизированного файла\n"
         << "[2]-Добавление в файл записей\n"
         << "[3]-Удаление из файла записей\n"
         << "[4]-Просмотр всего файла\n"
         << "[5]-Обновление записи с заданным номером\n"
         << "[6]-Выполнение задания. Проверить наличие страховки и владельца.\n"
         << "[ ESC ]-Выход\n";
}

//** ввод Солнечной панели **************************************************
void InputSolarPanel(SolarPanel &solarPanel) {
    cin.clear(); //очистить поток и затем выставить позиционирование в 0
    while (!isspace(cin.get())) //Избавиться от результатов неверного ввода
        continue;
    cout << "Добавление солнечной панели:\n";
    cout << "Наименование модели ->";
    cin.getline(solarPanel.model, 25);

    cout << "Год выпуска->";
    cin >> solarPanel.year;

    cout << "Цена панели->";
    cin >> solarPanel.price;

    cout << "Технология материала солнечной панели->";
    cin >> solarPanel.material;

    cout << "\n Технические характеристики:\n";
    cout << "\t Номинальное напряжение->";
    cin >> solarPanel.characteristic.voltage;
    cout << "\t Номинальная мощность->";
    cin >> solarPanel.characteristic.power;
    cin.clear(); 
	while (!isspace(cin.get()))
	      continue;
	cout << "\t Вес панели->";
    gets(solarPanel.characteristic.weight);
    cout << "Конец ввода";
    
    }

//** вывод Солнечной панели на экран ************************************************
void OutputSolarPanel(SolarPanel &solarPanel) {
    cout << "Наименование модели автомобиля: " << solarPanel.model << "\n"
         << "Наличие страховки автомобиля: " << solarPanel.price << "\n"
         << "Год выпуска автомобиля: " << solarPanel.year << "\n"
         << "Технические характеристик панели:\n"
         << "\tВес: " << solarPanel.characteristic.weight << "\n"
         << "\tНоминальное напряжение:" << solarPanel.characteristic.voltage << "\n"
         << "\tНоминальная мощность: " << solarPanel.characteristic.power << "\n";
}

//** создание/открытие файла базы данных ********************************

void CreateOpenFile(TName &nameFile, int &flag) {
    char ch;
    flag = 0;
    cout << "Введите имя файла для работы-->";
    //scanf("%s",&NameFile);
    gets(nameFile);
    f = fopen(nameFile, "r");
    if (f == NULL)
        do {
            system("cls");
            cout << "ФАЙЛА с именем "
                 << nameFile
                 << " НЕТ.\n\n"
                 << "Создать файл с именем "
                 << nameFile;
            cout << "Нажмите [ Y ] / [ N ]\n";
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                f = fopen(nameFile, "w");
                cout << "Файл с именем " << nameFile << " создан.\n"
                     << "\n\nДля продолжения нажмите любую клавашу\n";
                getch();
                flag = 1;
            }
            if (ch == 'N' || ch == 'n') {
                cout << "Файл не создан.\n"
                     << "\n\nДля продолжения нажмите любую клавашу\n";
                getch();
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
    else {
        flag = 1;
        cout << "Файл успешно открыт\n"
             << "\nДля продолжения нажмите любую клавашу\n";
        getch();
    }
    fclose(f);
}

//** добавление записи (Солнечной панели) в файл (в базу данных) **********
void RecordSolarPanel(TName NameFile, SolarPanel &solarPanel, int flag) {
    if (flag) {
        f = fopen(NameFile, "a");
        InputSolarPanel(solarPanel);
        fwrite(&solarPanel, sizeof(solarPanel), 1, f);
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}

//** вывод файла (базы данных) на экран *****************
void FileOutput() {
    int i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  Вывод файла на экран  ********\n"
             << "****************************************\n";
        while (fread(&solarPanel, sizeof(SolarPanel), 1, f)) {
            //printf("%d",ftell(f));
            cout << "Номер записи = " << i + 1 << "\n\n";
            OutputSolarPanel(solarPanel);
            cout << "****************************************" << "\n";
            i++;
            if (i % 3 == 0)  //вывод по несколько записей (Солнечных панелей)
            {
                getch();
                system("cls");
                cout << "********  Вывод файла на экран  ********\n"
                     << "****************************************\n";
            }
        }
        getch();
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }

}

//** размер файла *****************************
long filesize(TFile *f) {
    long curpos, length;
    curpos = ftell(f);        //запоминаем текущее положение
    fseek(f, 0L, SEEK_END);    //перемещаем на конец файла
    length = ftell(f);        //запоминаем положение в конце файла
    fseek(f, curpos, SEEK_SET);    //перемещаем на старое положение
    return length;
}


//** обновление записи с заданным номером ******
void UpdateSolarPanel(TName NameFile, SolarPanel &solarPanel, int flag) {
    long i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  Обновление записи с заданным номером  ********\n\n"
             << "********************************************************\n\n"
             << "Введите номер записи для обновления "
             << "из "
             << (filesize(f) / sizeof(solarPanel))
             << " --> ";
        cin >> i;
        //long q;
        fpos_t q;
        //перемещаемся на запись с номером i
        fseek(f, (i - 1) * sizeof(solarPanel), SEEK_CUR);
        //запоминаем текущее положение
        fgetpos(f, &q);

        fread(&solarPanel, sizeof(solarPanel), 1, f);
        OutputSolarPanel(solarPanel);
        cout << "****************************************\n";

        char ch;
        cout << "Обновить данные?\nНажмите [ Y ] / [ N ]\n";
        do {
            //clrscr();
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                //вводим новые значения
                InputSolarPanel(solarPanel);
                //переходим на старое место
                fsetpos(f, &q);
                //записываем новые значения
                fwrite(&solarPanel, sizeof(solarPanel), 1, f);
                cout << "Данные обновлены.\n";
            }
            if (ch == 'N' || ch == 'n') {
                cout << "Данные не обновленны.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\nДля продолжения нажмите любую клавашу\n";
        getch();
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}

//** удаление солнечной панели из базы **********************************
void DeleteSolarPanel(TName NameFile, SolarPanel &solarPanel, int flag) {
    long i = 0, k = 0;
    TFile *g;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  Удаление записи с заданным номером  ********\n\n"
             << "********************************************************\n\n"
             << "Введите номер записи для удаления "
             << "из "
             << (filesize(f) / sizeof(solarPanel))
             << " --> ";
        cin >> i;

        //перемещаемся на запись с номером i
        fseek(f, (i - 1) * sizeof(solarPanel), SEEK_CUR);
        fread(&solarPanel, sizeof(solarPanel), 1, f);
        OutputSolarPanel(solarPanel);
        cout << "****************************************\n";

        char ch;
        cout << "Удалить данные?\n"
		<<"Нажмите [ Y ] / [ N ]\n";
        do {
            //clrscr();
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                fseek(f, 0L, SEEK_SET);
                cout << "****" << ftell(f);
                g = fopen("Temp", "w");
                while (fread(&solarPanel, sizeof(solarPanel), 1, f)) {
                    if (k != (i - 1)) fwrite(&solarPanel, sizeof(solarPanel), 1, g);
                    k++;
                }
                cout << "Данные обновлены.\n";
                fclose(g);
                fclose(f);
                remove(NameFile);    //удаляем старый файл
                rename("Temp", NameFile);//переименовываем временный файл
            }
            if (ch == 'N' || ch == 'n') {
                cout << "Данные не обновленны.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\nДля продолжения нажмите любую клавашу\n";
        getch();
        //fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}

//******************** моя функция *****************
void SearchModelByPower() {
    int i = 0;
    if (flag) {
        f = fopen(NameFile, "r");
        int power;
        cout << "Введите мощность солнечной панели для поиска --> ";
        cin >> power;

        cout << "********  Поиск солнечной панели в базе данных  ********\n"
             << "********************************************************\n";
        while (fread(&solarPanel, sizeof(solarPanel), 1, f)) {


            if (solarPanel.characteristic.power == power) {
                cout << "Номер записи = " << i + 1 << "\n\n";
                OutputSolarPanel(solarPanel);
                cout << "********************************************************\n";
                i++;
                if (i % 3 == 0)  //вывод по несколько записей (панелей)
                {
                    getch();
                    system("cls");
                    cout << "********  Поиск Солнечной панели в базе данных  ********\n"
                         << "********************************************************\n";
                }
            }
        }

        getch();
        fclose(f);
    } else {
        cout << "\nВыберите файл для работы.\n"
             << "Нажмите [ 1 ] в разделе М Е Н Ю.";
        getch();
    }
}



//Начало программы

int main() {
    setlocale(0,"");
    char ch;
    system("cls");
    do {
        menu();
        ch = getch();
        switch (ch) {
            case '1':
                system("cls");
                CreateOpenFile(NameFile, flag); //создание и открытие файла базы данных
                break;
            case '2':
                system("cls");
                RecordSolarPanel(NameFile, solarPanel, flag); //запись данных в файл
                //getch();
                break;
            case '3':
                system("cls"); // Удаление солнечной панели из базы данных
                cout << "Удаление солнечной панели из базы данных\n";
                DeleteSolarPanel(NameFile, solarPanel, flag);
                getch();
                break;
            case '4':
                system("cls");    // вывод файла на экран
                FileOutput();
                break;
            case '5':
                system("cls");        //Обновление записи с заданным номером
                //printf("Обновление записи с заданным номером\n");
                UpdateSolarPanel(NameFile, solarPanel, flag);
                //getch();
                break;
            case '6':
                system("cls");
                cout << "Выполнение задания в соответствии с вариантом:\n" 
				<< "Поиск необходимой панели в базе данных\n";
                SearchModelByPower();
                getch();
                break;
            case '8':
                exit(1);
        }
    } while (ch != 27);
    return 0;
}
