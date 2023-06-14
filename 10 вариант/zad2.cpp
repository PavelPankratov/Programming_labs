#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <locale>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//��� ������ ��� ���������� � ��������
struct Characteristic {
    char weight[25];
    int power;
    int voltage;
};


//��� ������ ��� ������
struct SolarPanel {
    char model[25];
    int price;
    int year;
    char material[25];
    Characteristic characteristic;
};

//��� ������ ��� ����� �����
typedef char TName[25];
//��� ������ ��� �������� ����������
typedef FILE TFile;
//���������� ��� ������
SolarPanel solarPanel;
//���������� ��� ����� �����
TName NameFile;
//�������� ����������
TFile *f;
//���� ������ ����� ��� ������
int flag = 0;

//** ����� ���� ************************************************************
void menu(void) {
    system("cls");
    cout << "******** � � � � ********\n\n"
         << "[1]-��������/�������� ��������������� �����\n"
         << "[2]-���������� � ���� �������\n"
         << "[3]-�������� �� ����� �������\n"
         << "[4]-�������� ����� �����\n"
         << "[5]-���������� ������ � �������� �������\n"
         << "[6]-���������� �������. ��������� ������� ��������� � ���������.\n"
         << "[ ESC ]-�����\n";
}

//** ���� ��������� ������ **************************************************
void InputSolarPanel(SolarPanel &solarPanel) {
    cin.clear(); //�������� ����� � ����� ��������� ���������������� � 0
    while (!isspace(cin.get())) //���������� �� ����������� ��������� �����
        continue;
    cout << "���������� ��������� ������:\n";
    cout << "������������ ������ ->";
    cin.getline(solarPanel.model, 25);

    cout << "��� �������->";
    cin >> solarPanel.year;

    cout << "���� ������->";
    cin >> solarPanel.price;

    cout << "���������� ��������� ��������� ������->";
    cin >> solarPanel.material;

    cout << "\n ����������� ��������������:\n";
    cout << "\t ����������� ����������->";
    cin >> solarPanel.characteristic.voltage;
    cout << "\t ����������� ��������->";
    cin >> solarPanel.characteristic.power;
    cin.clear(); 
	while (!isspace(cin.get()))
	      continue;
	cout << "\t ��� ������->";
    gets(solarPanel.characteristic.weight);
    cout << "����� �����";
    
    }

//** ����� ��������� ������ �� ����� ************************************************
void OutputSolarPanel(SolarPanel &solarPanel) {
    cout << "������������ ������ ����������: " << solarPanel.model << "\n"
         << "������� ��������� ����������: " << solarPanel.price << "\n"
         << "��� ������� ����������: " << solarPanel.year << "\n"
         << "����������� ������������� ������:\n"
         << "\t���: " << solarPanel.characteristic.weight << "\n"
         << "\t����������� ����������:" << solarPanel.characteristic.voltage << "\n"
         << "\t����������� ��������: " << solarPanel.characteristic.power << "\n";
}

//** ��������/�������� ����� ���� ������ ********************************

void CreateOpenFile(TName &nameFile, int &flag) {
    char ch;
    flag = 0;
    cout << "������� ��� ����� ��� ������-->";
    //scanf("%s",&NameFile);
    gets(nameFile);
    f = fopen(nameFile, "r");
    if (f == NULL)
        do {
            system("cls");
            cout << "����� � ������ "
                 << nameFile
                 << " ���.\n\n"
                 << "������� ���� � ������ "
                 << nameFile;
            cout << "������� [ Y ] / [ N ]\n";
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                f = fopen(nameFile, "w");
                cout << "���� � ������ " << nameFile << " ������.\n"
                     << "\n\n��� ����������� ������� ����� �������\n";
                getch();
                flag = 1;
            }
            if (ch == 'N' || ch == 'n') {
                cout << "���� �� ������.\n"
                     << "\n\n��� ����������� ������� ����� �������\n";
                getch();
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
    else {
        flag = 1;
        cout << "���� ������� ������\n"
             << "\n��� ����������� ������� ����� �������\n";
        getch();
    }
    fclose(f);
}

//** ���������� ������ (��������� ������) � ���� (� ���� ������) **********
void RecordSolarPanel(TName NameFile, SolarPanel &solarPanel, int flag) {
    if (flag) {
        f = fopen(NameFile, "a");
        InputSolarPanel(solarPanel);
        fwrite(&solarPanel, sizeof(solarPanel), 1, f);
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}

//** ����� ����� (���� ������) �� ����� *****************
void FileOutput() {
    int i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  ����� ����� �� �����  ********\n"
             << "****************************************\n";
        while (fread(&solarPanel, sizeof(SolarPanel), 1, f)) {
            //printf("%d",ftell(f));
            cout << "����� ������ = " << i + 1 << "\n\n";
            OutputSolarPanel(solarPanel);
            cout << "****************************************" << "\n";
            i++;
            if (i % 3 == 0)  //����� �� ��������� ������� (��������� �������)
            {
                getch();
                system("cls");
                cout << "********  ����� ����� �� �����  ********\n"
                     << "****************************************\n";
            }
        }
        getch();
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }

}

//** ������ ����� *****************************
long filesize(TFile *f) {
    long curpos, length;
    curpos = ftell(f);        //���������� ������� ���������
    fseek(f, 0L, SEEK_END);    //���������� �� ����� �����
    length = ftell(f);        //���������� ��������� � ����� �����
    fseek(f, curpos, SEEK_SET);    //���������� �� ������ ���������
    return length;
}


//** ���������� ������ � �������� ������� ******
void UpdateSolarPanel(TName NameFile, SolarPanel &solarPanel, int flag) {
    long i = 0;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  ���������� ������ � �������� �������  ********\n\n"
             << "********************************************************\n\n"
             << "������� ����� ������ ��� ���������� "
             << "�� "
             << (filesize(f) / sizeof(solarPanel))
             << " --> ";
        cin >> i;
        //long q;
        fpos_t q;
        //������������ �� ������ � ������� i
        fseek(f, (i - 1) * sizeof(solarPanel), SEEK_CUR);
        //���������� ������� ���������
        fgetpos(f, &q);

        fread(&solarPanel, sizeof(solarPanel), 1, f);
        OutputSolarPanel(solarPanel);
        cout << "****************************************\n";

        char ch;
        cout << "�������� ������?\n������� [ Y ] / [ N ]\n";
        do {
            //clrscr();
            ch = getch();
            if (ch == 'Y' || ch == 'y') {
                //������ ����� ��������
                InputSolarPanel(solarPanel);
                //��������� �� ������ �����
                fsetpos(f, &q);
                //���������� ����� ��������
                fwrite(&solarPanel, sizeof(solarPanel), 1, f);
                cout << "������ ���������.\n";
            }
            if (ch == 'N' || ch == 'n') {
                cout << "������ �� ����������.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\n��� ����������� ������� ����� �������\n";
        getch();
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}

//** �������� ��������� ������ �� ���� **********************************
void DeleteSolarPanel(TName NameFile, SolarPanel &solarPanel, int flag) {
    long i = 0, k = 0;
    TFile *g;
    if (flag) {
        f = fopen(NameFile, "r+");

        cout << "********  �������� ������ � �������� �������  ********\n\n"
             << "********************************************************\n\n"
             << "������� ����� ������ ��� �������� "
             << "�� "
             << (filesize(f) / sizeof(solarPanel))
             << " --> ";
        cin >> i;

        //������������ �� ������ � ������� i
        fseek(f, (i - 1) * sizeof(solarPanel), SEEK_CUR);
        fread(&solarPanel, sizeof(solarPanel), 1, f);
        OutputSolarPanel(solarPanel);
        cout << "****************************************\n";

        char ch;
        cout << "������� ������?\n"
		<<"������� [ Y ] / [ N ]\n";
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
                cout << "������ ���������.\n";
                fclose(g);
                fclose(f);
                remove(NameFile);    //������� ������ ����
                rename("Temp", NameFile);//��������������� ��������� ����
            }
            if (ch == 'N' || ch == 'n') {
                cout << "������ �� ����������.\n";
            }
        } while (!(ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n'));
        cout << "\n��� ����������� ������� ����� �������\n";
        getch();
        //fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}

//******************** ��� ������� *****************
void SearchModelByPower() {
    int i = 0;
    if (flag) {
        f = fopen(NameFile, "r");
        int power;
        cout << "������� �������� ��������� ������ ��� ������ --> ";
        cin >> power;

        cout << "********  ����� ��������� ������ � ���� ������  ********\n"
             << "********************************************************\n";
        while (fread(&solarPanel, sizeof(solarPanel), 1, f)) {


            if (solarPanel.characteristic.power == power) {
                cout << "����� ������ = " << i + 1 << "\n\n";
                OutputSolarPanel(solarPanel);
                cout << "********************************************************\n";
                i++;
                if (i % 3 == 0)  //����� �� ��������� ������� (�������)
                {
                    getch();
                    system("cls");
                    cout << "********  ����� ��������� ������ � ���� ������  ********\n"
                         << "********************************************************\n";
                }
            }
        }

        getch();
        fclose(f);
    } else {
        cout << "\n�������� ���� ��� ������.\n"
             << "������� [ 1 ] � ������� � � � �.";
        getch();
    }
}



//������ ���������

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
                CreateOpenFile(NameFile, flag); //�������� � �������� ����� ���� ������
                break;
            case '2':
                system("cls");
                RecordSolarPanel(NameFile, solarPanel, flag); //������ ������ � ����
                //getch();
                break;
            case '3':
                system("cls"); // �������� ��������� ������ �� ���� ������
                cout << "�������� ��������� ������ �� ���� ������\n";
                DeleteSolarPanel(NameFile, solarPanel, flag);
                getch();
                break;
            case '4':
                system("cls");    // ����� ����� �� �����
                FileOutput();
                break;
            case '5':
                system("cls");        //���������� ������ � �������� �������
                //printf("���������� ������ � �������� �������\n");
                UpdateSolarPanel(NameFile, solarPanel, flag);
                //getch();
                break;
            case '6':
                system("cls");
                cout << "���������� ������� � ������������ � ���������:\n" 
				<< "����� ����������� ������ � ���� ������\n";
                SearchModelByPower();
                getch();
                break;
            case '8':
                exit(1);
        }
    } while (ch != 27);
    return 0;
}
