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
        cout << "\t学生学号：" << account << endl;
        cout << "\t密码：" << password << endl;
    }
    else
    if (id == 2)
    {
        cout << "\t教师职工号：" << account << endl;
        cout << "\t密码：" << password << endl;
    }
    else
    if (id == 3)
    {
        cout << "\t管理员账号：" << account << endl;
        cout << "\t密码：" << password << endl;
    }
}