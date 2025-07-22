#include <cstring>
const int NAME_LEN = 20;
const int TABLE_LEN = 100;
using namespace std;
struct TableItem
{
	char name[NAME_LEN];
	TableItem* next;
};

int binary_research(char key[], TableItem t[], int first_location,int num_of_items)
{
	int index,first,last;
	first = first_location;
	last = num_of_items;
	index = (first + last) / 2;

	if (strcmp(key, t[index].name) == 0)
		return index;
	if (strcmp(key, t[index].name) > 0)
		binary_research(key, t, index + 1, last);
	else
		binary_research(key, t, first, index - 1);

}