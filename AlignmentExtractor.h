#ifndef _AlignmentExtractor_h
#define _AlignmentExtractor_h
#include "Alignment.h"
#include <string>
#include <fstream>
using namespace std;
/**��ȡGIZA++����Ľ��*/
class AlignmentExtractor{
public:
	/**
	   @param giza_output ����giza_output������ļ�
	*/
	AlignmentExtractor(const string& giza_output);
	/**�Ƿ��ܳ�ȡ��һ������*/
	bool extract(Alignment& alignment);
private:
	//������
	 ifstream fin;
	 int count ;
};
#endif