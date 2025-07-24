#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class String
{
	char* str;
public:
	String()
	{
		str = NULL;
	}
	String(const char* p)
	{
		str = new char[strlen(p) + 1];
		strcpy(str, p);
	}
	~String()
	{
		delete[]str;
		str = NULL;
	}
	int lenth() { return strlen(str); }

	char& char_at(int i)
	{
		if (i<0 || i>strlen(str))
		{
			cerr << "³¬³ö×Ö·û·¶Î§£¡\n";
			exit(-1);
		}
		return str[i];
	}
	const char* get_str() { return str; }

	String& copy(const char* p)
	{
		delete[]str;
		str = new char[strlen(p) + 1];
		strcpy(str, p);
		return *this;
	}
	String& copy(const String& s) { return copy(s.str); }

	String& append(const char* p)
	{
		char* p1 = new char[strlen(str) + strlen(p) + 1];
		strcpy(p1, str);
		strcat(p1, p);
		delete[]str;
		str = p1;
		return *this;
	}
	String& append(const String& s) { return append(s.str); }

	int compare(const char* p) { return strcmp(str, p); }
	int compare(const String& s) { return strcmp(str, s.str); }

	bool is_substring(const char* sub_str);
	bool is_substring(const String& sub_str);
	String substring(int start, int len);
	int find_place_str(const char* find_str, const char* replace_str);
	void remove_spaces();
	int to_int();
	void to_lower_case();
};

bool String::is_substring(const char* sub_str)
{
	if (lenth() > strlen(sub_str))return false;
	for (int i = 0; i < lenth() - strlen(sub_str);i++)
	{
		for (int j = 0; j < strlen(sub_str); j++)
		{
			if (str[i + j] != sub_str[j])
				return false;
		}
	}
	return true;
}

bool String::is_substring(const String& sub_str)
{
	if (lenth() > strlen(sub_str.str))return false;
	for (int i = 0; i < lenth() - strlen(sub_str.str); i++)
	{
		for (int j = 0; j < strlen(sub_str.str); j++)
		{
			if (str[i + j] != sub_str.str[j])
				return false;
		}
	}
	return true;
}

String String::substring(int start, int len)
{
	char str0[] = { "\0" };
	for (int i = start,j=0; i < start + len; i++,j++)
		str0[j] = char_at(i);
	String::copy(str0);
}

int String::find_place_str(const char* find_str, const char* replace_str)
{
	
}

void String::remove_spaces()
{
	char str0[] = "\0";
	int j = 0;
	for(int i=0;i<lenth();i++)
		if (char_at(i) != ' ')
		{
			str0[j] = char_at(i);
		}
	String::copy(str0);
}
int String::to_int()
{
	int x=0;
	for (int i = 0; i < lenth(); i++)
	{
		str[i] -= '0';
		x = x * 10 + str[i];
	}
	return x;
}

void String::to_lower_case()
{
	for (int i = 0; i < lenth(); i++)
	{
		if (str[i] <= 'Z' && str[i] >= 'A')
			str[i] += ('a' - 'A');
	}
}

