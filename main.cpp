#include"all.h"
#include"fream_name.h"
#include"people.h"
#include<Windows.h>
using namespace std;
//�ɾֲ���ɫ�仯
void color(unsigned short color_index)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index);
}

void menu()
{
    color(6);
    cout << "\t\t-------------------------" << endl;
    cout << "\t\t| |" << endl;;
    cout << "\t\t| ��1��ѧ����¼ �� |" << endl;
    cout << "\t\t| |" << endl;;
    cout << "\t\t| ��2����ʦ��¼ �� |" << endl;
    cout << "\t\t| |" << endl;;
    cout << "\t\t| ��3������Ա��¼ �� |" << endl;
    cout << "\t\t| |" << endl;;
    cout << "\t\t| ��0���˳�ϵͳ �� |" << endl;
    cout << "\t\t| |" << endl;;
    cout << "\t\t-------------------------" << endl;
    cout << "���������ѡ��" << endl;
}

int main()
{
    People_Manager peo;
    int ch;
    while (true)
    {
        menu();
        cin >> ch;
        switch (ch)
        {
            case 1:
                peo.stu_oper();//ѧ��
                break;
            case 2:
                peo.tea_oper();//��ʦ
                break;
            case 3:
                peo.man_oper();//����Ա
                break;
            case 0:
                system("cls");
                cout << "\n\n\n\t��ӭ�´�ʹ��" << endl << endl;
                system("pause");
                exit(0);
                break;
            default:
                cout << "�޴�ѡ��" << "��";
                cout << "���������롭" << endl;
                system("pause");
                system("cls");
                break;
        }
    }
    _getch();
    return 0;
}