#include"account.h"
Account::Account(int m_account, string m_password,int m_id)
{
    account = m_account;
    password = m_password;
    id = m_id;
}
void Account::display()
{
    if (id == 1)
    {
        cout << "\tѧ��ѧ�ţ�" << account << endl;
        cout << "\t���룺" << password << endl;
    }
    else
    if (id == 2)
    {
        cout << "\t��ʦְ���ţ�" << account << endl;
        cout << "\t���룺" << password << endl;
    }
    else
    if (id == 3)
    {
        cout << "\t����Ա�˺ţ�" << account << endl;
        cout << "\t���룺" << password << endl;
    }
}