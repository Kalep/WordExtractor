#include "WordExtractor.h"
#include <iostream>
WordExtractor::WordExtractor()
{
	punc_set.insert(",");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert(":");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert(";");//Ӣ�ĵķֺ�
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("����");
	punc_set.insert("����");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("��");
	punc_set.insert("\"");
	punc_set.insert("(");
	punc_set.insert(")");
}

void WordExtractor::process_punc(Alignment& alignment)
{
	unsigned int word_index = 0;
	for( ; word_index < alignment.words.size() ; word_index++)
	{
		if(alignment.aligns[word_index].size() >1 && this->punc_set.find(alignment.words[word_index])!=this->punc_set.end())
		{
			//����
			set<int>::const_iterator target_iter = alignment.aligns[word_index].begin();
			for(; target_iter != alignment.aligns[word_index].end(); target_iter++)
			{
				 if(*target_iter != word_index)
				 {
					 //ɾ��
					 set<int>& target_set = alignment.aligns[*target_iter];
					 set<int>::iterator source_iter = target_set.find(word_index);//����Դ�˵�id
					 target_set.erase(source_iter);
				 }
			}
			alignment.aligns[word_index].clear();
			alignment.aligns[word_index].insert(word_index);
		}
	}
}
void WordExtractor::extract_word(Alignment& alignment,  vector<string>&  words)
{
	//1,������
	this->process_punc(alignment);
	//���ȳ�ȡ���ִ�
	unsigned int word_index = 0;
	string word= "";
	for( ; word_index < alignment.words.size() ; )
	{       
			if(alignment.aligns[word_index].size() == 1)
			{
				if(word!="") 
				{
					words.push_back(word);
					//cout<<"��ȷ���Ĵ�:"<<word<<endl;
				}
				words.push_back(alignment.words[word_index]);
				//cout<< "���ִ�:\t"<<alignment.words[word_index]<<endl;
				word_index ++;
				word = "";
			}
			else{
				if( word_index + 1 <alignment.words.size() && alignment.aligns[ word_index] == alignment.aligns[word_index+1])
				{
					if(word!="")
					{
						words.push_back(word);
						//cout<<"��ȷ���Ĵ�:"<<word<<endl;
					}
					string bword = alignment.words[word_index]+ alignment.words[ word_index+1];
					word_index+=2;
					//cout<<"˫�ִ�:\t"<< bword << endl;
					words.push_back(bword);
					word = "";
				}
				else {
					//�Ȳ���һ�ִ�Ҳ���Ƕ��ִ�
					if(word_index < alignment.words.size())
						word += alignment.words[word_index];
					word_index++;
				}
			}
	}
	if( word != "") words.push_back(word);
}
