#ifndef _WORD_EXTRCTOR_H
#define _WORD_EXTRCTOR_H
#include <vector>
#include <string>
#include <set>
#include "Alignment.h"
using namespace std;

class WordExtractor{
public:
	WordExtractor();
	void extract_word(Alignment& alignment, vector<string>& words);
private:
	//处理标点，标点只能自己对到自己
	 void process_punc(Alignment& alignment);
	 set<string> punc_set;//标点符号集
};
#endif