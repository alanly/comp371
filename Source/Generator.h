#ifndef _LSYSTEM_H
#define _LSYSTEM_H
#include <vector>
using namespace std;

template<typename Element, class Sequence> class LSystem
{
	class LSystemRule
	{
		Element head;
		Sequence tail;
	public:
		LSystemRule(Element hd, Sequence tl) {head = hd; tail = tl;}
		bool isMatch(Element hd) {return hd == head;}
		Sequence &getTail() {return tail;}
	};
	Sequence state;
	vector<LSystemRule *> rules;
	vector<Element> heads;
	vector<Sequence> tails;
public:
	LSystem();
	~LSystem();
	void setState(Sequence st) {state = st;}
	Sequence &getState() {return state;}
	void addRule(Element hd, Sequence tl);
	Sequence &replace(Element &hd);
	void iterate();
	
};
std::string DownloadJSON(std::string URL);
void initLSystem();
std::string getLSystemString();
static int writer(char *data, size_t size, size_t nmemb, std::string *buffer_in);
#endif