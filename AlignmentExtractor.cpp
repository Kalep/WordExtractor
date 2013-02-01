#include "AlignmentExtractor.h"
#include <iostream>
#include "../UnspervisedWordSegmentation/StringHelper.h"
#include <algorithm>
#include <iterator>
using namespace std;

#define ERROR_MSG {cerr<<"��ʽ����!!!\t"<<"��"<<count<<"��"<<endl;return false;}

AlignmentExtractor::AlignmentExtractor(const string& giza_output):fin(giza_output.c_str()),count(0){
	if(!fin){
		cerr<<"�ļ�:"<<giza_output.c_str()<<"������"<<endl;
		exit(-1);
	}
}

bool AlignmentExtractor::extract(Alignment& alignment)
{
	if(fin.eof()){ fin.close(); return false;}
	string first_line, second_line, third_line;
	 

		if(!getline(fin,first_line)) ERROR_MSG
		if(!getline(fin,second_line)) ERROR_MSG
		if(!getline(fin,third_line)) ERROR_MSG
		count+= 3;
		//��֤��һ��
		string::size_type  s_index = first_line.find("# Sentence pair");
		if(s_index == string::npos) ERROR_MSG
		//����ڶ���
		token(second_line,alignment.words);
		alignment.aligns.resize(alignment.words.size());
		//���������
		//1��֤
		s_index = third_line.find("NULL ({ ") ;
		if(s_index != 0)  ERROR_MSG

		vector<string> right_brackets;
		split(third_line, "})",right_brackets);
		//NULL ({ 7 14 21 26 31 }) �� ({ 2 }) �� ({ 1 }) �� ({ 4 }) �� ({ 3 }) �� ({ 6 }) �� ({ 5 }) �� ({ }) ȥ ({ 9 }) �� ({ 8 }) �� ({ 11 }) �� ({ 10 }) �� ({ 13 }) ˽ ({ 12 }) �� ({ }) �� ({ 16 }) �� ({ 15 }) , ({ 18 }) �� ({ 17 }) �� ({ 20 }) �� ({ 19 }) �� ({ }) �� ({ 23 }) ģ ({ 22 }) �� ({ 25 }) ˽ ({ 24 }) �� ({ }) �� ({ 28 }) �� ({ 27 }) �� ({ 30 }) �� ({ 29 }) �� ({ }) 
		//����һ������: NULL ({ 7 14 21 26 31
		//cout<<alignment.words.size()<<"\t"<< right_brackets.size()<<endl;
		right_brackets.erase(right_brackets.begin());//ɾ��NULL
		right_brackets.pop_back();//ɾ�����Ŀո�
		//copy(right_brackets.begin(), right_brackets.end(), ostream_iterator<string>(cout,"\n"));
		//����ÿһ������
		vector<string>::iterator  word_iter = right_brackets.begin();
		int word_index = 0;
		for(; word_iter != right_brackets.end() ; word_iter++)
		{
			vector<string> left_brackets;
			split(*word_iter,"({ ",left_brackets);
			//copy(left_brackets.begin(), left_brackets.end(), ostream_iterator<string>(cout,"\t"));
			//cout<<endl;
			if(left_brackets.size() != 2) ERROR_MSG
			istringstream sin(left_brackets[1]);
			int s_index;
			alignment.aligns[word_index].insert(word_index); //�����Լ�
			while( sin>> s_index) //����Ҫ������ʲô�ģ��Ȳ�Ū��
			{
						alignment.aligns[word_index].insert(s_index-1);
						alignment.aligns[s_index-1].insert(word_index);
			}
			word_index++;
		}
		//����һ�£�����Ч��
		/*
		for(word_index = 0; word_index < alignment.words.size() ; word_index++)
		{
			cout<<"��"<<word_index<<"��\t"<< alignment.words[word_index] <<"\t";
			//set<int>::const_iterator index_iter = alignment.aligns[word_index].begin();
			copy(alignment.aligns[word_index].begin(),alignment.aligns[word_index].end(), ostream_iterator<int>(cout,"\t"));
			cout<<endl;
		}*/
		return true;
}

