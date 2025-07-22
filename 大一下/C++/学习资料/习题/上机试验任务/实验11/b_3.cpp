#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	double average=0;
	map<string, double> m;
	double cul_average(map<string,double> &x);
	void display_unpass(map<string, double>::iterator &x);
	void display(map<string, double>::iterator & x);
	bool score_higher(map<string, double>::iterator & it1, map<string, double>::iterator & it2);

	m["ZhangSan"] = 59;
	m["LiSi"] = 65;
	m["WangWu"] = 85;
	m["DaMing"] = 70;
	m["XiaoLu"] = 90;

	cout << "not passed:" << endl;
	for_each(m.begin(), m.end(), display_unpass);

	average = cul_average(m);
	cout << "average score:" << average << endl;

	sort(m.begin(), m.end(), score_higher);

	for_each(m.begin(), m.end(), display);
}

void display(map<string,double>::iterator &x)
{
	cout << x->first << ":" << x->second << endl;
}

bool score_higher(map<string, double>::iterator& it1, map<string, double>::iterator& it2)
{
	return it1->second > it2->second;
}

double cul_average(map<string, double> &x)
{
	double aver=0;
	map<string, double>::iterator it;
	it = x.begin();

	for (size_t i = 0; i < x.size(); it++)
	{
		aver += (it->second / x.size());
	}

	return aver;

}

void display_unpass(map<string,double>::iterator &x)
{
	if (x->second >= 60)return;
	else cout << x->first << "  ";
}