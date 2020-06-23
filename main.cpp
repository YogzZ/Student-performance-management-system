#include"all.h"
#include"fream_name.h"
#include"people.h"
#include<Windows.h>
using namespace std;
//可局部颜色变化
void color(unsigned short color_index)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index);
}

void menu()
{
    color(6);
    cout << "\t\t-------------------------" << endl;
    cout << "\t\t| |" << endl;;
    cout << "\t\t| 《1、学生登录 》 |" << endl;
    cout << "\t\t| |" << endl;;
    cout << "\t\t| 《2、教师登录 》 |" << endl;
    cout << "\t\t| |" << endl;;
    cout << "\t\t| 《3、管理员登录 》 |" << endl;
    cout << "\t\t| |" << endl;;
    cout << "\t\t| 《0、退出系统 》 |" << endl;
    cout << "\t\t| |" << endl;;
    cout << "\t\t-------------------------" << endl;
    cout << "请输入你的选择：" << endl;
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
                peo.stu_oper();//学生
                break;
            case 2:
                peo.tea_oper();//教师
                break;
            case 3:
                peo.man_oper();//管理员
                break;
            case 0:
                system("cls");
                cout << "\n\n\n\t欢迎下次使用" << endl << endl;
                system("pause");
                exit(0);
                break;
            default:
                cout << "无此选项" << "，";
                cout << "请重新输入…" << endl;
                system("pause");
                system("cls");
                break;
        }
    }
    _getch();
    return 0;
}