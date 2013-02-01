#include "AlignmentExtractor.h"
#include <iostream>
#include "../UnspervisedWordSegmentation/StringHelper.h"
#include <algorithm>
#include <iterator>
using namespace std;

#define ERROR_MSG {cerr<<"格式错误!!!\t"<<"第"<<count<<"行"<<endl;return false;}

AlignmentExtractor::AlignmentExtractor(const string& giza_output):fin(giza_output.c_str()),count(0){
	if(!fin){
		cerr<<"文件:"<<giza_output.c_str()<<"不存在"<<endl;
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
		//验证第一行
		string::size_type  s_index = first_line.find("# Sentence pair");
		if(s_index == string::npos) ERROR_MSG
		//处理第二行
		token(second_line,alignment.words);
		alignment.aligns.resize(alignment.words.size());
		//处理第三行
		//1验证
		s_index = third_line.find("NULL ({ ") ;
		if(s_index != 0)  ERROR_MSG

		vector<string> right_brackets;
		split(third_line, "})",right_brackets);
		//NULL ({ 7 14 21 26 31 }) 中 ({ 2 }) 国 ({ 1 }) 今 ({ 4 }) 天 ({ 3 }) 公 ({ 6 }) 布 ({ 5 }) 了 ({ }) 去 ({ 9 }) 年 ({ 8 }) 打 ({ 11 }) 击 ({ 10 }) 走 ({ 13 }) 私 ({ 12 }) 的 ({ }) 成 ({ 16 }) 果 ({ 15 }) , ({ 18 }) 并 ({ 17 }) 宣 ({ 20 }) 布 ({ 19 }) 大 ({ }) 规 ({ 23 }) 模 ({ 22 }) 走 ({ 25 }) 私 ({ 24 }) 被 ({ }) 基 ({ 28 }) 本 ({ 27 }) 控 ({ 30 }) 制 ({ 29 }) 。 ({ }) 
		//处理一个数组: NULL ({ 7 14 21 26 31
		//cout<<alignment.words.size()<<"\t"<< right_brackets.size()<<endl;
		right_brackets.erase(right_brackets.begin());//删掉NULL
		right_brackets.pop_back();//删掉最后的空格
		//copy(right_brackets.begin(), right_brackets.end(), ostream_iterator<string>(cout,"\n"));
		//处理每一个分组
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
			alignment.aligns[word_index].insert(word_index); //覆盖自己
			while( sin>> s_index) //还需要处理标点什么的，先不弄吧
			{
						alignment.aligns[word_index].insert(s_index-1);
						alignment.aligns[s_index-1].insert(word_index);
			}
			word_index++;
		}
		//遍历一下，看下效果
		/*
		for(word_index = 0; word_index < alignment.words.size() ; word_index++)
		{
			cout<<"第"<<word_index<<"个\t"<< alignment.words[word_index] <<"\t";
			//set<int>::const_iterator index_iter = alignment.aligns[word_index].begin();
			copy(alignment.aligns[word_index].begin(),alignment.aligns[word_index].end(), ostream_iterator<int>(cout,"\t"));
			cout<<endl;
		}*/
		return true;
}

