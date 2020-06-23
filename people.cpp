#include"people.h"

People_Manager::People_Manager() {
    fstream f;
    f.open(FILENAME1, ios::in);
    if (!f.is_open()) {
        cout << "文件不存在1" << endl;
        Stu_Num = 0;//学生人数
        M_Student = NULL;//数组指针
        f.close();
        return;
    }
    char ch;
    f >> ch;
    if (f.eof() && f.is_open()) {
        cout << "文件存在但是为空" << endl;
        Stu_Num = 0;//学生人数
        M_Student = NULL;//数组指针
        f.close();
        return;
    }
    Stu_Num = stu_num();
    M_Student = new Student *[Stu_Num];//开辟空间
    stu_init();
    f.close();
    ifstream ifo;
    ifo.open(FILENAME2, ios::in);
    if (!ifo.is_open()) {
        cout << "文件不存在2" << endl;
        Acc_Num = 0;//学生人数
        M_Account = NULL;//数组指针
        f.close();
        return;
    }
    f >> ch;
    if (f.eof() && f.is_open()) {
        cout << "文件存在但是为空" << endl;
        Acc_Num = 0;//学生人数
        M_Account = NULL;//数组指针
        f.close();
        return;
    }
    Acc_Num = acc_num();
    M_Account = new Account *[Acc_Num];//开辟空间
    acc_init();
    ifo.close();
}

void People_Manager::stu_init()//初始化
{
    fstream f;
    f.open(FILENAME1, ios::in);
    int m_num;
    string m_name;
    int m_math;
    int m_eng;
    int m_chi;
    int i = 0;
//读取
    while (f >> m_num && f >> m_name && f >> m_math && f >> m_eng && f >> m_chi) {
        Student *stu = NULL;
        stu = new Student(m_num, m_name, m_math, m_eng, m_chi);
        M_Student[i] = stu;
        i++;
    }
    f.close();
}

int People_Manager::stu_num()//初始化数量
{
    fstream f;
    f.open(FILENAME1, ios::in);
    int i = 0;
    int m_num;
    string m_name;
    int m_math;
    int m_eng;
    int m_chi;
    while (f >> m_num && f >> m_name && f >> m_math && f >> m_eng && f >> m_chi) {
        i++;
    }
    f.close();
    return i;
}

void People_Manager::acc_init()//账户初始化
{
    fstream f;
    f.open(FILENAME2, ios::in);
    int account;
    string password;
    int id;
    int i = 0;
    while (f >> account && f >> password && f >> id) {
        Account *Acc = NULL;
        Acc = new Account(account, password, id);
        M_Account[i] = Acc;
        i++;
    }
    f.close();
}

void People_Manager::stu_show()//显示学生
{
    for (int i = 0; i < Stu_Num; i++) {
        M_Student[i]->display();
        cout<<"------------------"<<endl;
    }
    system("pause");
    system("cls");
}

void People_Manager::stu_add()//添加学生
{
    fstream f;
    f.open(FILENAME2, ios::out);
    if (!f.is_open()) {
        cout << "文件不存在" << endl;
        return;
    }
    int j;
    int num;
    cout << "请输入要添加学生的数量：" << endl;
    cin >> num;
    Account **Acc_Manager = new Account *[Acc_Num + num];
    int i;
    for (i = 0; i < Acc_Num; i++) {
        Acc_Manager[i] = M_Account[i];
    }
    j = i;
    int account;
    string password;
//新建一个更大空间的数组
    Student **E_Student;
    E_Student = new Student *[Stu_Num + num];
//复制数组
    for (i = 0; i < Stu_Num; i++) {
        E_Student[i] = M_Student[i];
    }
    int id;
    int m_num;
    string m_name;
    int m_math;
    int m_eng;
    int m_chi;
    for (i = 0; i < num; i++) {
        int flag = 0;
        Account *acc = NULL;
        Student *stu = NULL;
        cout << "请输入第" << i + 1 << "个学生的学号：" << endl;
        cin >> m_num;
        //判断是否存在重复
        for (int jjj = 0; jjj < Stu_Num; jjj++) {
            if (M_Student[jjj]->num == m_num) {
                cout << "已有该同学，请重新输入..." << endl;
                system("pause");
                system("cls");
                flag = 1;
                i--;
                break;
            }
        }
        if (flag == 1) {
            continue;
        }
        cout << "请输入第" << i + 1 << "个学生的姓名：" << endl;
        cin >> m_name;
        cout << "请输入第" << i + 1 << "个学生的数学成绩：" << endl;
        cin >> m_math;
        cout << "请输入第" << i + 1 << "个学生的英语成绩：" << endl;
        cin >> m_eng;
        cout << "请输入第" << i + 1 << "个学生的语文成绩：" << endl;
        cin >> m_chi;
        //默认密码为666666
        acc = new Account(m_num, "666666", 1);
        Acc_Manager[j] = acc;
        stu = new Student(m_num, m_name, m_math, m_eng, m_chi);
        E_Student[i + Stu_Num] = stu;
        j++;
    }
//释放之前所开辟的空间
    delete[] M_Student;
    delete[] M_Account;

    M_Account = Acc_Manager;
    M_Student = E_Student;
//数量加
    Stu_Num += num;
    Acc_Num += num;

    cout << "成功添加" << num << "位学生" << endl;

    f.close();

    stu_save();
    account_save();

    system("pause");
    system("cls");
}

void People_Manager::stu_save()//保存学生
{
    fstream f;
    f.open(FILENAME1, ios::out);
    for (int i = 0; i < Stu_Num; i++) {
        f << M_Student[i]->num << " "
          << M_Student[i]->name << " "
          << M_Student[i]->math << " "
          << M_Student[i]->eng << " "
          << M_Student[i]->chi << endl;
    }
    f.close();
}

void People_Manager::stu_del()//删除学生
{
    int num;
    string name;
    int id;
    cout << "输入删除的学生学号和姓名" << endl;
    cin >> num;
    cin >> name;
    for (int i = 0; i < Stu_Num; i++) {
        if (M_Student[i]->num == num && M_Student[i]->name == name) {
            for (int j = i; j < Stu_Num; j++) {
                M_Student[j] = M_Student[j + 1];
            }
            cout << "删除成功" << endl;
            Stu_Num--;

            break;
        }
    }
    for (int k = 0; k < Acc_Num; k++) {
        if (M_Account[k]->account == num) {
            for (int j = k; j < Acc_Num; j++) {
                M_Account[k] = M_Account[k + 1];
            }
        }
    }
//数量减一
    Acc_Num--;
    stu_save();
    account_save();
    system("pause");
    system("cls");
}

void People_Manager::stu_mod()//修改学生
{
    int num;
    string name;
    int id;
    int j;
    int i = 0;
    cout << "输入修改的学生学号和姓名" << endl;
    cin >> num;
    cin >> name;
    for (; i < Stu_Num; i++) {
        if (M_Student[i]->num == num && M_Student[i]->name == name) {
            j = i;
            break;
        }
    }
    if (i == Stu_Num) {
        cout << "查无此人" << endl;
        return;
    }
    int k;
    int m_num;
    string m_name;
    int m_math;
    int m_eng;
    int m_chi;

    while (true) {
        int ch;
        cout << "1、学号" << endl;
        cout << "2、姓名" << endl;
        cout << "3、数学成绩" << endl;
        cout << "4、英语成绩" << endl;
        cout << "5、语文成绩" << endl;
        cout << "6、所有" << endl;
        cout << "0、返回" << endl;
        cout << "请输入要修改的部分：" << endl;
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "输入新学号：" << endl;
                for (int i = 0; i < Acc_Num; i++) {
                    if (M_Account[i]->account == m_num) {
                        k = i;
                        break;
                    }
                }
                cin >> m_num;
                M_Student[j]->num = m_num;
                M_Account[k]->account = m_num;
                cout << "修改成功" << endl;
                system("pause");
                system("cls");
                break;
            case 2:
                cout << "输入新姓名：" << endl;
                cin >> m_name;
                M_Student[j]->name = m_name;
                cout << "修改成功" << endl;
                system("pause");
                system("cls");
                break;
            case 3:
                cout << "输入新数学成绩：" << endl;
                cin >> m_math;
                M_Student[j]->math = m_math;
                cout << "修改成功" << endl;
                system("pause");
                system("cls");
                break;
            case 4:
                cout << "输入新英语成绩：" << endl;
                cin >> m_eng;
                M_Student[j]->eng = m_eng;
                cout << "修改成功" << endl;
                system("pause");
                system("cls");
                break;
            case 5:
                cout << "输入新语文成绩：" << endl;
                cin >> m_chi;
                M_Student[j]->chi = m_chi;
                cout << "修改成功" << endl;
                system("pause");
                system("cls");
                break;
            case 6:
                for (int i = 0; i < Acc_Num; i++) {
                    if (M_Account[i]->account == m_num) {
                        k = i;
                        break;
                    }
                }
                cout << "输入新学号：" << endl;
                cin >> m_num;
                M_Student[j]->num = m_num;
                M_Account[k]->account = m_num;
                cout << "输入新姓名：" << endl;
                cin >> m_name;
                M_Student[j]->name = m_name;
                cout << "输入新数学成绩：" << endl;
                cin >> m_math;
                M_Student[j]->math = m_math;
                cout << "输入新英语成绩：" << endl;
                cin >> m_eng;
                M_Student[j]->eng = m_eng;
                cout << "输入新语文成绩：" << endl;
                cin >> m_chi;
                M_Student[j]->chi = m_chi;
                cout << "修改成功" << endl;
                system("pause");
                system("cls");
                break;
            case 0:
                system("cls");
                stu_save();
                return;
                break;
        }
    }
}

void People_Manager::stu_find()//查找学生
{
    int num;
    string name;
    int j, i;
    cout << "输入查找的学生学号和姓名" << endl;
    cin >> num;
    cin >> name;
    for (i = 0; i < Stu_Num; i++) {
        if (M_Student[i]->num == num && M_Student[i]->name == name) {
            j = i;
            cout << M_Student[j]->num << " " <<
                 M_Student[j]->name << " " <<
                 M_Student[j]->math << " " <<
                 M_Student[j]->eng << " " <<
                 M_Student[j]->chi << endl;
            break;
        }
    }
    if (i == Stu_Num) {
        cout << "查无此人" << endl;
    }
    system("pause");
    system("cls");
}

void People_Manager::stu_oper()//操作
{
    int account;
    string password;
    while (true) {
        cout << "输入学号：" << endl;
        cin >> account;
        cout << "输入密码：" << endl;
        pass_au(password);
        int flag = 0;
        int j;
        char b;
        for (int k = 0; k < Acc_Num; k++) {
            if (M_Account[k]->account == account && M_Account[k]->password == password && M_Account[k]->id == 1) {
                flag = 1;
                j = k;
                cout << "登录成功" << endl;
                system("pause");
                system("cls");
                break;
            }
        }
        if (flag) {
            int c;
            while (true) {
                cout << "\t\t-- -- -- -- -- -- -- -- -" << endl;
                cout << "\t\t | 1、查看自身信息 |" << endl;
                cout << "\t\t-- -- -- -- -- -- -- -- -" << endl;
                cout << "\t\t | 2、 修改密码 |" << endl;
                cout << "\t\t-- -- -- -- -- -- -- -- -" << endl;
                cout << "\t\t | 0、 返回 |" << endl;
                cout << "\t\t-- -- -- -- -- -- -- -- -" << endl;
                cin >> c;
                switch (c) {
                    case 1:
                        for (int k = 0; k < Stu_Num; k++) {
                            if (M_Student[k]->num == account) {
                                M_Student[k]->display();
                                system("pause");
                                system("cls");
                                break;
                            }
                        }
                        break;
                    case 2:
                        cout << "输入新密码：" << endl;
                        cin >> password;
                        M_Account[j]->password = password;
                        account_save();
                        cout << "修改成功" << endl;
                        system("pause");
                        system("cls");
                        break;
                    case 0:
                        system("cls");
                        return;
                        break;
                }
            }
        } else {
            cout << "密码错误" << endl;
            cout << "是否重新输入…(y / n)" << endl;
            cin >> b;
            if (b == 'n') {
                system("cls");
                return;
            }
            system("cls");
        }
    }
}

void People_Manager::tea_oper()//教师操作
{
    int account;
    string password;
    while (true) {
        cout << "输入职工号：" << endl;
        cin >> account;
        cout << "输入密码：" << endl;
//        cin >> password;
        int flag = 0;
        pass_au(password);
        int j;
        for (int k = 0; k < Acc_Num; k++) {
            if (M_Account[k]->id == 2 && M_Account[k]->account == account && M_Account[k]->password == password) {
                flag = 1;
                j = k;
                cout << "登录成功" << endl;
                system("pause");
                system("cls");
                break;
            }
        }
        if (flag) {
            int c;
            while (true) {
                cout << "\t\t-- -- -- -- -- -- -- -- -- -- --" << endl;
                cout << "\t\t | 1、学生信息的操作  |" << endl;
                cout << "\t\t-- -- -- -- -- -- -- -- -- -- --" << endl;
                cout << "\t\t | 2、 修改密码 | " << endl;
                cout << "\t\t-- -- -- -- -- -- -- -- -- -- --" << endl;
                cout << "\t\t | 0、 返回 |" << endl;
                cout << "\t\t-- -- -- -- -- -- -- -- -- -- --" << endl;
                cin >> c;
                int flag2 = 0;
                switch (c) {
                    case 1:
                        while (true) {
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|1、 增添学生   |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|2、 删除学生   |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|3、修改学生信息|" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|4、  查找学生  |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|5、显示学生信息|" << endl;
                            cout << "\t\t  ---------------" << endl;
                            cout << "\t\t|0、  返回      |" << endl;
                            cout << "\t\t  ---------------" << endl;
                            cout << "输入你的选择：" << endl;
                            int ch;
                            cin >> ch;
                            switch (ch) {
                                case 1:
                                    stu_add();
                                    break;
                                case 2:
                                    stu_del();
                                    break;
                                case 3:
                                    stu_mod();
                                    break;
                                case 4:
                                    stu_find();
                                    break;
                                case 5:
                                    stu_show();
                                    break;
                                case 0:
                                    flag = 1;
                                    break;

                            }
                            if (flag) {
                                break;//退出循环
                            }
                        }
                        system("cls");
                        //
                        break;
                    case 2:
                        cout << "输入新密码：" << endl;
                        cin >> password;
                        M_Account[j]->password = password;
                        account_save();
                        break;
                    case 0:
                        system("cls");
                        return;
                        break;
                }
                system("cls");
            }
        } else {
            char b;
            cout << "密码错误" << endl;
            cout << "是否重新输入....(y/n)" << endl;
            cin >> b;
            if (b == 'n') {
                system("cls");
                return;
            }
            system("cls");
        }
    }
}

void People_Manager::account_save()//账户保存
{
    fstream f;
    f.open(FILENAME2, ios::out);
    if (!f.is_open()) {
        cout << "文件不存在3" << endl;
        return;
    }
    for (int i = 0; i < Acc_Num; i++) {
        f << M_Account[i]->account << " " <<
          M_Account[i]->password << " " <<
          M_Account[i]->id << " " << endl;
    }
    f.close();
}

void People_Manager::man_oper()//管理员操作
{
    int number = 3;
    int ACCOUNT;
    string PASSWORD;
    string password;
    int id;
    int account;
    while (true) {

        if (number == 3) {
            cout << "请输入账号：" << endl;
            cin >> ACCOUNT;
        }
        cout << "请输入密码：" << endl;
//        cin >> PASSWORD;
        pass_au(PASSWORD);
        int FLAG = 0;
        for (int ii = 0; ii < Acc_Num; ii++) {
            if (M_Account[ii]->account == ACCOUNT && M_Account[ii]->id == 3 && M_Account[ii]->password == PASSWORD) {
                FLAG = 1;
                break;
            }
        }
        if (FLAG) {
            cout << "登录成功...." << endl;
            system("pause");
            system("cls");
            //
            int ch;
            int f;
            while (true) {

                int flag = 0;
                cout << "\t\t --------------------" << endl;
                cout << "\t\t|1、学生信息的操作  |" << endl;
                cout << "\t\t --------------------" << endl;
                cout << "\t\t|2、   账号操作     |" << endl;
                cout << "\t\t --------------------" << endl;
                cout << "\t\t|0、   退出登录     |" << endl;
                cout << "\t\t --------------------" << endl;
                cout << "输入你的选择：" << endl;
                cin >> ch;
                system("cls");
                switch (ch) {
                    case 1:
                        //
                        while (true) {
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|1、 增添学生   |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|2、 删除学生   |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|3、修改学生信息|" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|4、  查找学生  |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|5、显示学生信息|" << endl;
                            cout << "\t\t  ---------------" << endl;
                            cout << "\t\t|0、  返回      |" << endl;
                            cout << "\t\t  ---------------" << endl;
                            cout << "输入你的选择：" << endl;
                            cin >> ch;
                            switch (ch) {
                                case 1:
                                    stu_add();
                                    break;
                                case 2:
                                    stu_del();
                                    break;
                                case 3:
                                    stu_mod();
                                    break;
                                case 4:
                                    stu_find();
                                    break;
                                case 5:
                                    stu_show();
                                    break;
                                case 0:
                                    flag = 1;
                                    break;

                            }
                            if (flag) {
                                break;//退出循环
                            }
                        }
                        system("cls");
                        //
                        break;
                    case 2:
                        //
                        int as;

                        while (true) {
                            Account **Acc_M = new Account *[Acc_Num + 1];
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|1、添加教师账号|" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|2、删除教师账号|" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|3、查看所有账号|" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|4、修改密码    |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|0、退出        |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "输入你的选择：" << endl;
                            cin >> ch;
                            switch (ch) {
                                case 1:
                                    while (true) {
                                        f = 0;

                                        cout << "输入教师的职工号：" << endl;
                                        cin >> account;
                                        for (int iii = 0; iii < Stu_Num; iii++) {
                                            if (M_Account[iii]->account == account && M_Account[iii]->id == 2) {
                                                cout << "该教师已经存在，请重新输入..." << endl;
                                                f = 1;
                                                break;
                                            }
                                        }
                                        if (!f) {
                                            break;
                                        }
                                    }
                                    for (int xi = 0; xi < Acc_Num; xi++) {
                                        Acc_M[xi] = M_Account[xi];
                                    }
                                    Account *acc_m;
                                    acc_m = new Account(account, "111111", 2);
                                    Acc_M[Acc_Num] = acc_m;
                                    delete[]M_Account;
                                    M_Account = Acc_M;
                                    Acc_Num++;
                                    account_save();
                                    cout << "添加成功.." << endl;
                                    system("pause");
                                    system("cls");
                                    break;
                                case 2:
                                    cout << "输入教师的职工号：" << endl;
                                    cin >> account;
                                    for (int ii = 0; ii < Acc_Num; ii++) {
                                        if (M_Account[ii]->account == account && M_Account[ii]->id == 2) {
                                            for (int jj = ii; jj < Acc_Num; jj++) {
                                                M_Account[jj] = M_Account[jj + 1];
                                            }
                                            break;
                                        }
                                    }
                                    Acc_Num--;
                                    account_save();
                                    cout << "删除成功.." << endl;
                                    system("pause");
                                    system("cls");
                                    break;
                                case 3:
                                    for (int i = 0; i < Acc_Num; i++) {
                                        M_Account[i]->display();
                                    }
                                    system("pause");
                                    system("cls");
                                    break;
                                case 4:
                                    for (int ii = 0; ii < Acc_Num; ii++) {
                                        if (M_Account[ii]->account == ACCOUNT && M_Account[ii]->id == 3) {
                                            cout << "输入修改后的密码：" << endl;
                                            cin >> password;
                                            M_Account[ii]->password = password;
                                            break;
                                        }
                                    }
                                    account_save();
                                    cout << "修改成功.." << endl;
                                    system("pause");
                                    system("cls");
                                    break;
                                case 0:
                                    flag = 1;
                                    break;
                            }
                            if (flag) {
                                system("cls");
                                break;
                            }
                        }
                        system("cls");
                        //
                        break;
                    case 0:
                        system("cls");
                        return;
                        break;
                }
            }
            //
            return;

        } else {
            char c;
            number--;
            cout << "共有三次，还剩" << number << "次";
            cout << "密码错误，是否重新输入. . .(y/n) " << endl;
            cin >> c;
            if (number == 0) {
                cout << "密码错误，进行锁定。" << endl;
                cout << "无法再次输入密码" << endl;
                _getch();
                system("cls");
                break;
            }
            //cout << "共有三次，还剩" << number << "次";
            system("pause");
            if (c == 'n') {
                system("cls");
                return;
            }
            system("cls");

        }
    }
}


int People_Manager::acc_num()//初始化数量
{
    fstream f;
    f.open(FILENAME2, ios::in);
    int i = 0;
    int account;
    string password;
    int id;
    while (f >> account && f >> password && f >> id) {
        i++;
    }
    f.close();
    return i;
}

int People_Manager::pass_au(string &pass)//密码验证
{
    char password[1024];
    int index = 0;
    while (true) {
        char ch;
        ch = _getch();
        if (ch == 8) {
            if (index > 0) {
                index--;
                cout << char(8) << " " << char(8);
            }
        } else if (ch == '\r') {
            password[index] = '\0';
            cout << endl;
            break;
        } else {
            password[index++] = ch;
        }
    }
    for (int i = 0; i < index; i++) {
        pass += password[i];
    }
}