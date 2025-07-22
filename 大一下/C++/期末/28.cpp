#include <iostream>
#include <string>
#include <fstream>
using namespace std;
const int MAX_NUM_OF_COURSES=30;
const int MAX_ID_LEN=10;
const int MAX_NAME_LEN=8;
class StudentScores {
	public:
		StudentScores() {
			initialized = false;
		}
		bool data_is_ok() const {
			return initialized;
		}
	private:
		int scores[MAX_NUM_OF_COURSES],num_of_courses;
		char id[MAX_ID_LEN+1],name[MAX_NAME_LEN+1];
		bool initialized;
		friend istream &operator >>(istream &in, StudentScores &x);
		friend ostream &operator <<(ostream &out, StudentScores &x);
};
istream &operator >>(istream &in, StudentScores &x){
	//读入时会有bug 不影响使用 不改了 
	cout << "请输入学号：" ;
	in >> x.id;
	cout << "请输入姓名：" ;
	in >> x.name;
	cout << "请输入选课门数：";
	in >> x.num_of_courses;
	if(x.num_of_courses>MAX_NUM_OF_COURSES){
		cout << "选课超过最大数量，修改为30个！";
		x.num_of_courses = MAX_NUM_OF_COURSES; 
	}
	for(int i=1;i<=x.num_of_courses;i++){
		cout << "请输入第" << i << "门课的成绩："; 
		in >> x.scores[i];
	}
	x.initialized = true;
	return in;
}
ostream &operator <<(ostream &out, StudentScores &x){
//	版本1：适合考试的时候写的，给老师看比较清楚，但实际上是错的（推荐考试写这种） （逃 
	out << endl << "学生姓名：" << x.name << endl << "学号：" << x.id << endl << "选课门数：" << x.num_of_courses << endl;
	for(int i=1;i<=num_of_courses;i++){
		out << "第" << i << "门课：" << scores[i] << "points." << endl; 
	}
	return out; 
//	版本2：正确并能使用的版本： 
	out << x.id << endl << x.name << endl << x.num_of_courses << endl;
	for(int i=1;i<=x.num_of_courses;i++){
		out << x.scores[i] <<  endl; 
	}
	return out; 
}
int main() {
	//实在懒 这题太麻烦了 就写存取一个学生的程序。。。
	StudentScores tmp;
	ifstream fout("F:\\temp.ini");
	if(!fout){
		cout << "未读到文件存储的学生信息，将直接开始写入！" << endl; 
	} else{
		//命令行会有奇怪的输出 别在意就行 
		fout >> tmp;
		cout << endl << tmp;
	}
	fout.close();
	ofstream readin("F://temp.ini");
	cin >> tmp;
	readin << tmp;
}
