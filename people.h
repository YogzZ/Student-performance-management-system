#pragma once
#include"student.h"
#include"account.h"
#include <iostream>
#include <fstream>
#include <string>
#include<conio.h>
#include"fream_name.h"
using namespace std;
class People_Manager
{
public:
    People_Manager();
    int Stu_Num;//学生人数
    Student **M_Student;//学生数组指针

    void stu_init();//初始化
    int stu_num();//初始化数量

    int Acc_Num;//账户人数
    Account **M_Account;//账户数组指针

    void acc_init();//初始化
    int acc_num();//初始化数量


    void account_save();//账户保存
    void stu_add();//添加学生
    void stu_sort();//排序学生
    void stu_del();//删除学生
    void stu_mod();//修改学生
    void stu_find();//查找学生
    void stu_save();//保存学生
    void stu_show();//显示学生
    void stu_oper();//学生操作
    void tea_oper();//教师操作
    void man_oper();//管理员操作
    int pass_au(string&);//密码验证
};
