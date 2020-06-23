#pragma once

#include<conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include"fream_name.h"

using namespace std;

class Account {
public:
    Account(int, string, int);

    void display();

    int account;//账号
    string password;//密码
    int id;//身份
};