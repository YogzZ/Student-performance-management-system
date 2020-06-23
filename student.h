#pragma once

#include<conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include"fream_name.h"

using namespace std;

class Student {
public:
    Student(int, string, int, int, int);

    void display();

    int num;//学号
    string name;//姓名
    int math;//数学成绩
    int eng;//英语成绩
    int chi;//语文成绩
};