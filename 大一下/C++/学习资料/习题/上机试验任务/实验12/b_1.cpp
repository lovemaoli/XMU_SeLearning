#include <iostream>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

class is_english
{
public:
	bool operator()(pair<int, string> single)
	{
		return single.second == "english";
	}
};

int main()
{
	std::map<int, std::string> my_map;
	my_map.insert(std::make_pair(10, "china"));
	my_map.insert(std::make_pair(20, "usa"));
	my_map.insert(std::make_pair(30, "english"));
	my_map.insert(std::make_pair(40, "hongkong"));

	map<int, std::string>::iterator it;
	it = find_if(my_map.begin(), my_map.end(), is_english());

	cout << it->first;
	return 0;
}