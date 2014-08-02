#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H

#include <vector>
using namespace std;

class CStringUtils
{
public:
	CStringUtils();
	~CStringUtils();
	static void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
};
#endif