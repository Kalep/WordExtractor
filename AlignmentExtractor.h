#ifndef _AlignmentExtractor_h
#define _AlignmentExtractor_h
#include "Alignment.h"
#include <string>
#include <fstream>
using namespace std;
/**抽取GIZA++对齐的结果*/
class AlignmentExtractor{
public:
	/**
	   @param giza_output 传入giza_output的输出文件
	*/
	AlignmentExtractor(const string& giza_output);
	/**是否能抽取下一个对齐*/
	bool extract(Alignment& alignment);
private:
	//输入流
	 ifstream fin;
	 int count ;
};
#endif