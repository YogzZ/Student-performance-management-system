#include"student.h"

Student::Student(int m_num, string m_name, int m_math, int m_eng, int m_chi) {
    this->num = m_num;
    this->name = m_name;
    this->math = m_math;
    this->eng = m_eng;
    this->chi = m_chi;
}

void Student::display() {
    cout << "ѧ�ţ�" << this->num << endl;
    cout << "������" << this->name << endl;
    cout << "��ѧ�ɼ���" << this->math << endl;
    cout << "Ӣ��ɼ���" << this->eng << endl;
    cout << "���ĳɼ���" << this->chi << endl;
}