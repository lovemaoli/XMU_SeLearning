#include<iostream>
using namespace std;

//基类People
class People{
protected:
    char *m_name;
    int m_age;
};

//派生类Student
class Student: public People{
private:
    float m_score;
public:
    Student(float score);
    void display();
};
Student::Student(float score): People(),m_score(score){ }
void Student::display(){
    cout<<"无名氏的成绩是"<<m_score<<"。"<<endl;
}

int main(){
    Student stu(90.5);
    stu.display();
    return 0;
}
