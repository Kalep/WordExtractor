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
	//�����㣬���ֻ���Լ��Ե��Լ�
	 void process_punc(Alignment& alignment);
	 set<string> punc_set;//�����ż�
};
#endif