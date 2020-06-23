#include"student.h"

Student::Student(int m_num, string m_name, int m_math, int m_eng, int m_chi) {
    this->num = m_num;
    this->name = m_name;
    this->math = m_math;
    this->eng = m_eng;
    this->chi = m_chi;
}

void Student::display() {
    cout << "学号：" << this->num << endl;
    cout << "姓名：" << this->name << endl;
    cout << "数学成绩：" << this->math << endl;
    cout << "英语成绩：" << this->eng << endl;
    cout << "语文成绩：" << this->chi << endl;
}