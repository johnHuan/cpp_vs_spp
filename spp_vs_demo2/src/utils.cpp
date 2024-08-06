#include "utils.h"

#include <list>


int string_split(const string& str, string sep, vector<string>& ret) {
	if (str.empty())
		return 0;
	string tmp;

	string::size_type pos_begin = 0; // str.find_first_of(sep);
	string::size_type comma_pos = 0;

	ret.clear();
	while (pos_begin != string::npos)
	{
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != string::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else {
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}
		if (!tmp.empty())
		{
			ret.push_back(tmp);
			tmp.clear();
		}
	}
	return 0;
}