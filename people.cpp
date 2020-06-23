#include"people.h"

People_Manager::People_Manager() {
    fstream f;
    f.open(FILENAME1, ios::in);
    if (!f.is_open()) {
        cout << "�ļ�������1" << endl;
        Stu_Num = 0;//ѧ������
        M_Student = NULL;//����ָ��
        f.close();
        return;
    }
    char ch;
    f >> ch;
    if (f.eof() && f.is_open()) {
        cout << "�ļ����ڵ���Ϊ��" << endl;
        Stu_Num = 0;//ѧ������
        M_Student = NULL;//����ָ��
        f.close();
        return;
    }
    Stu_Num = stu_num();
    M_Student = new Student *[Stu_Num];//���ٿռ�
    stu_init();
    f.close();
    ifstream ifo;
    ifo.open(FILENAME2, ios::in);
    if (!ifo.is_open()) {
        cout << "�ļ�������2" << endl;
        Acc_Num = 0;//ѧ������
        M_Account = NULL;//����ָ��
        f.close();
        return;
    }
    f >> ch;
    if (f.eof() && f.is_open()) {
        cout << "�ļ����ڵ���Ϊ��" << endl;
        Acc_Num = 0;//ѧ������
        M_Account = NULL;//����ָ��
        f.close();
        return;
    }
    Acc_Num = acc_num();
    M_Account = new Account *[Acc_Num];//���ٿռ�
    acc_init();
    ifo.close();
}

void People_Manager::stu_init()//��ʼ��
{
    fstream f;
    f.open(FILENAME1, ios::in);
    int m_num;
    string m_name;
    int m_math;
    int m_eng;
    int m_chi;
    int i = 0;
//��ȡ
    while (f >> m_num && f >> m_name && f >> m_math && f >> m_eng && f >> m_chi) {
        Student *stu = NULL;
        stu = new Student(m_num, m_name, m_math, m_eng, m_chi);
        M_Student[i] = stu;
        i++;
    }
    f.close();
}

int People_Manager::stu_num()//��ʼ������
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

void People_Manager::acc_init()//�˻���ʼ��
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

void People_Manager::stu_show()//��ʾѧ��
{
    for (int i = 0; i < Stu_Num; i++) {
        M_Student[i]->display();
        cout<<"------------------"<<endl;
    }
    system("pause");
    system("cls");
}

void People_Manager::stu_add()//���ѧ��
{
    fstream f;
    f.open(FILENAME2, ios::out);
    if (!f.is_open()) {
        cout << "�ļ�������" << endl;
        return;
    }
    int j;
    int num;
    cout << "������Ҫ���ѧ����������" << endl;
    cin >> num;
    Account **Acc_Manager = new Account *[Acc_Num + num];
    int i;
    for (i = 0; i < Acc_Num; i++) {
        Acc_Manager[i] = M_Account[i];
    }
    j = i;
    int account;
    string password;
//�½�һ������ռ������
    Student **E_Student;
    E_Student = new Student *[Stu_Num + num];
//��������
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
        cout << "�������" << i + 1 << "��ѧ����ѧ�ţ�" << endl;
        cin >> m_num;
        //�ж��Ƿ�����ظ�
        for (int jjj = 0; jjj < Stu_Num; jjj++) {
            if (M_Student[jjj]->num == m_num) {
                cout << "���и�ͬѧ������������..." << endl;
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
        cout << "�������" << i + 1 << "��ѧ����������" << endl;
        cin >> m_name;
        cout << "�������" << i + 1 << "��ѧ������ѧ�ɼ���" << endl;
        cin >> m_math;
        cout << "�������" << i + 1 << "��ѧ����Ӣ��ɼ���" << endl;
        cin >> m_eng;
        cout << "�������" << i + 1 << "��ѧ�������ĳɼ���" << endl;
        cin >> m_chi;
        //Ĭ������Ϊ666666
        acc = new Account(m_num, "666666", 1);
        Acc_Manager[j] = acc;
        stu = new Student(m_num, m_name, m_math, m_eng, m_chi);
        E_Student[i + Stu_Num] = stu;
        j++;
    }
//�ͷ�֮ǰ�����ٵĿռ�
    delete[] M_Student;
    delete[] M_Account;

    M_Account = Acc_Manager;
    M_Student = E_Student;
//������
    Stu_Num += num;
    Acc_Num += num;

    cout << "�ɹ����" << num << "λѧ��" << endl;

    f.close();

    stu_save();
    account_save();

    system("pause");
    system("cls");
}

void People_Manager::stu_save()//����ѧ��
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

void People_Manager::stu_del()//ɾ��ѧ��
{
    int num;
    string name;
    int id;
    cout << "����ɾ����ѧ��ѧ�ź�����" << endl;
    cin >> num;
    cin >> name;
    for (int i = 0; i < Stu_Num; i++) {
        if (M_Student[i]->num == num && M_Student[i]->name == name) {
            for (int j = i; j < Stu_Num; j++) {
                M_Student[j] = M_Student[j + 1];
            }
            cout << "ɾ���ɹ�" << endl;
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
//������һ
    Acc_Num--;
    stu_save();
    account_save();
    system("pause");
    system("cls");
}

void People_Manager::stu_mod()//�޸�ѧ��
{
    int num;
    string name;
    int id;
    int j;
    int i = 0;
    cout << "�����޸ĵ�ѧ��ѧ�ź�����" << endl;
    cin >> num;
    cin >> name;
    for (; i < Stu_Num; i++) {
        if (M_Student[i]->num == num && M_Student[i]->name == name) {
            j = i;
            break;
        }
    }
    if (i == Stu_Num) {
        cout << "���޴���" << endl;
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
        cout << "1��ѧ��" << endl;
        cout << "2������" << endl;
        cout << "3����ѧ�ɼ�" << endl;
        cout << "4��Ӣ��ɼ�" << endl;
        cout << "5�����ĳɼ�" << endl;
        cout << "6������" << endl;
        cout << "0������" << endl;
        cout << "������Ҫ�޸ĵĲ��֣�" << endl;
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "������ѧ�ţ�" << endl;
                for (int i = 0; i < Acc_Num; i++) {
                    if (M_Account[i]->account == m_num) {
                        k = i;
                        break;
                    }
                }
                cin >> m_num;
                M_Student[j]->num = m_num;
                M_Account[k]->account = m_num;
                cout << "�޸ĳɹ�" << endl;
                system("pause");
                system("cls");
                break;
            case 2:
                cout << "������������" << endl;
                cin >> m_name;
                M_Student[j]->name = m_name;
                cout << "�޸ĳɹ�" << endl;
                system("pause");
                system("cls");
                break;
            case 3:
                cout << "��������ѧ�ɼ���" << endl;
                cin >> m_math;
                M_Student[j]->math = m_math;
                cout << "�޸ĳɹ�" << endl;
                system("pause");
                system("cls");
                break;
            case 4:
                cout << "������Ӣ��ɼ���" << endl;
                cin >> m_eng;
                M_Student[j]->eng = m_eng;
                cout << "�޸ĳɹ�" << endl;
                system("pause");
                system("cls");
                break;
            case 5:
                cout << "���������ĳɼ���" << endl;
                cin >> m_chi;
                M_Student[j]->chi = m_chi;
                cout << "�޸ĳɹ�" << endl;
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
                cout << "������ѧ�ţ�" << endl;
                cin >> m_num;
                M_Student[j]->num = m_num;
                M_Account[k]->account = m_num;
                cout << "������������" << endl;
                cin >> m_name;
                M_Student[j]->name = m_name;
                cout << "��������ѧ�ɼ���" << endl;
                cin >> m_math;
                M_Student[j]->math = m_math;
                cout << "������Ӣ��ɼ���" << endl;
                cin >> m_eng;
                M_Student[j]->eng = m_eng;
                cout << "���������ĳɼ���" << endl;
                cin >> m_chi;
                M_Student[j]->chi = m_chi;
                cout << "�޸ĳɹ�" << endl;
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

void People_Manager::stu_find()//����ѧ��
{
    int num;
    string name;
    int j, i;
    cout << "������ҵ�ѧ��ѧ�ź�����" << endl;
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
        cout << "���޴���" << endl;
    }
    system("pause");
    system("cls");
}

void People_Manager::stu_oper()//����
{
    int account;
    string password;
    while (true) {
        cout << "����ѧ�ţ�" << endl;
        cin >> account;
        cout << "�������룺" << endl;
        pass_au(password);
        int flag = 0;
        int j;
        char b;
        for (int k = 0; k < Acc_Num; k++) {
            if (M_Account[k]->account == account && M_Account[k]->password == password && M_Account[k]->id == 1) {
                flag = 1;
                j = k;
                cout << "��¼�ɹ�" << endl;
                system("pause");
                system("cls");
                break;
            }
        }
        if (flag) {
            int c;
            while (true) {
                cout << "\t\t-- -- -- -- -- -- -- -- -" << endl;
                cout << "\t\t | 1���鿴������Ϣ |" << endl;
                cout << "\t\t-- -- -- -- -- -- -- -- -" << endl;
                cout << "\t\t | 2�� �޸����� |" << endl;
                cout << "\t\t-- -- -- -- -- -- -- -- -" << endl;
                cout << "\t\t | 0�� ���� |" << endl;
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
                        cout << "���������룺" << endl;
                        cin >> password;
                        M_Account[j]->password = password;
                        account_save();
                        cout << "�޸ĳɹ�" << endl;
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
            cout << "�������" << endl;
            cout << "�Ƿ��������롭(y / n)" << endl;
            cin >> b;
            if (b == 'n') {
                system("cls");
                return;
            }
            system("cls");
        }
    }
}

void People_Manager::tea_oper()//��ʦ����
{
    int account;
    string password;
    while (true) {
        cout << "����ְ���ţ�" << endl;
        cin >> account;
        cout << "�������룺" << endl;
//        cin >> password;
        int flag = 0;
        pass_au(password);
        int j;
        for (int k = 0; k < Acc_Num; k++) {
            if (M_Account[k]->id == 2 && M_Account[k]->account == account && M_Account[k]->password == password) {
                flag = 1;
                j = k;
                cout << "��¼�ɹ�" << endl;
                system("pause");
                system("cls");
                break;
            }
        }
        if (flag) {
            int c;
            while (true) {
                cout << "\t\t-- -- -- -- -- -- -- -- -- -- --" << endl;
                cout << "\t\t | 1��ѧ����Ϣ�Ĳ���  |" << endl;
                cout << "\t\t-- -- -- -- -- -- -- -- -- -- --" << endl;
                cout << "\t\t | 2�� �޸����� | " << endl;
                cout << "\t\t-- -- -- -- -- -- -- -- -- -- --" << endl;
                cout << "\t\t | 0�� ���� |" << endl;
                cout << "\t\t-- -- -- -- -- -- -- -- -- -- --" << endl;
                cin >> c;
                int flag2 = 0;
                switch (c) {
                    case 1:
                        while (true) {
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|1�� ����ѧ��   |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|2�� ɾ��ѧ��   |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|3���޸�ѧ����Ϣ|" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|4��  ����ѧ��  |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|5����ʾѧ����Ϣ|" << endl;
                            cout << "\t\t  ---------------" << endl;
                            cout << "\t\t|0��  ����      |" << endl;
                            cout << "\t\t  ---------------" << endl;
                            cout << "�������ѡ��" << endl;
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
                                break;//�˳�ѭ��
                            }
                        }
                        system("cls");
                        //
                        break;
                    case 2:
                        cout << "���������룺" << endl;
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
            cout << "�������" << endl;
            cout << "�Ƿ���������....(y/n)" << endl;
            cin >> b;
            if (b == 'n') {
                system("cls");
                return;
            }
            system("cls");
        }
    }
}

void People_Manager::account_save()//�˻�����
{
    fstream f;
    f.open(FILENAME2, ios::out);
    if (!f.is_open()) {
        cout << "�ļ�������3" << endl;
        return;
    }
    for (int i = 0; i < Acc_Num; i++) {
        f << M_Account[i]->account << " " <<
          M_Account[i]->password << " " <<
          M_Account[i]->id << " " << endl;
    }
    f.close();
}

void People_Manager::man_oper()//����Ա����
{
    int number = 3;
    int ACCOUNT;
    string PASSWORD;
    string password;
    int id;
    int account;
    while (true) {

        if (number == 3) {
            cout << "�������˺ţ�" << endl;
            cin >> ACCOUNT;
        }
        cout << "���������룺" << endl;
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
            cout << "��¼�ɹ�...." << endl;
            system("pause");
            system("cls");
            //
            int ch;
            int f;
            while (true) {

                int flag = 0;
                cout << "\t\t --------------------" << endl;
                cout << "\t\t|1��ѧ����Ϣ�Ĳ���  |" << endl;
                cout << "\t\t --------------------" << endl;
                cout << "\t\t|2��   �˺Ų���     |" << endl;
                cout << "\t\t --------------------" << endl;
                cout << "\t\t|0��   �˳���¼     |" << endl;
                cout << "\t\t --------------------" << endl;
                cout << "�������ѡ��" << endl;
                cin >> ch;
                system("cls");
                switch (ch) {
                    case 1:
                        //
                        while (true) {
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|1�� ����ѧ��   |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|2�� ɾ��ѧ��   |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|3���޸�ѧ����Ϣ|" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|4��  ����ѧ��  |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|5����ʾѧ����Ϣ|" << endl;
                            cout << "\t\t  ---------------" << endl;
                            cout << "\t\t|0��  ����      |" << endl;
                            cout << "\t\t  ---------------" << endl;
                            cout << "�������ѡ��" << endl;
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
                                break;//�˳�ѭ��
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
                            cout << "\t\t|1����ӽ�ʦ�˺�|" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|2��ɾ����ʦ�˺�|" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|3���鿴�����˺�|" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|4���޸�����    |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "\t\t|0���˳�        |" << endl;
                            cout << "\t\t-----------------" << endl;
                            cout << "�������ѡ��" << endl;
                            cin >> ch;
                            switch (ch) {
                                case 1:
                                    while (true) {
                                        f = 0;

                                        cout << "�����ʦ��ְ���ţ�" << endl;
                                        cin >> account;
                                        for (int iii = 0; iii < Stu_Num; iii++) {
                                            if (M_Account[iii]->account == account && M_Account[iii]->id == 2) {
                                                cout << "�ý�ʦ�Ѿ����ڣ�����������..." << endl;
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
                                    cout << "��ӳɹ�.." << endl;
                                    system("pause");
                                    system("cls");
                                    break;
                                case 2:
                                    cout << "�����ʦ��ְ���ţ�" << endl;
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
                                    cout << "ɾ���ɹ�.." << endl;
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
                                            cout << "�����޸ĺ�����룺" << endl;
                                            cin >> password;
                                            M_Account[ii]->password = password;
                                            break;
                                        }
                                    }
                                    account_save();
                                    cout << "�޸ĳɹ�.." << endl;
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
            cout << "�������Σ���ʣ" << number << "��";
            cout << "��������Ƿ���������. . .(y/n) " << endl;
            cin >> c;
            if (number == 0) {
                cout << "������󣬽���������" << endl;
                cout << "�޷��ٴ���������" << endl;
                _getch();
                system("cls");
                break;
            }
            //cout << "�������Σ���ʣ" << number << "��";
            system("pause");
            if (c == 'n') {
                system("cls");
                return;
            }
            system("cls");

        }
    }
}


int People_Manager::acc_num()//��ʼ������
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

int People_Manager::pass_au(string &pass)//������֤
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