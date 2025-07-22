#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

class Intset
{
	vector<int> vec;
public:
	Intset() {}

	Intset(const Intset& s) {
		vec = s.vec;
	}

	~Intset() {
		fill(vec.begin(), vec.end(), '\0');
	}

	bool is_empty(){
		return vec.empty();
	}

	int size()const{
		return vec.size();
	}

	bool is_element(int e)const {
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i] == e)return true;
		}
		return false;
	}

	bool is_subset(const Intset& s)const {
		if (search(vec.begin(), vec.end(), s.vec.begin(), s.vec.end()) == vec.end())return false;
		return true;
	}
	bool is_equal(const Intset& s)const {
		return vec == s.vec;
	}

	bool insert(int e) {
		vec.push_back(e);
		return true;
	}

	bool remove(int e) {
		if (std::remove(vec.begin(), vec.end(), e) != vec.end())return true;
		return false;
	}

	void display()const {
		cout << "所有元素为：" << endl;
		for (int i = 0; i < vec.size(); i++)
			cout << vec[i] << " ";
	}
	Intset union2(const Intset& s)const {
		Intset i;
		set_union(vec.begin(), vec.end(), s.vec.begin(), s.vec.end(), i.vec);
		return i;
	}
	Intset intersection2(const Intset& s)const {
		Intset i;
		set_intersection(vec.begin(), vec.end(), s.vec.begin(), s.vec.end(), i.vec);
		return i;
	}
	Intset difference2(const Intset& s)const {
		Intset i;
		set_symmetric_difference(vec.begin(), vec.end(), s.vec.begin(), s.vec.end(), i.vec);
		return i;
	}
};


