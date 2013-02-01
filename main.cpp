#include "AlignmentExtractor.h"
#include "WordExtractor.h"
#include <iterator>
using namespace std;

int main( int argc ,char* argv[])
{
	string input_file = "I:\\TCorpus\\mfdcorpus\\fbispku.A3.final.test";//long.test";
	//fbis.tok.ch.character.long";//fbis.tok.ch.bak
	AlignmentExtractor ae(input_file);
	WordExtractor we;
	string output_file = "I:\\TCorpus\\mfdcorpus\\fbispku.out";
	ofstream fout(output_file.c_str());
	while(true)
	{
		Alignment al;
		if(!ae.extract(al) ) 
			break;
		vector<string> words;
		we.extract_word(al,words);
		copy(words.begin(), words.end(), ostream_iterator<string>(fout,"	"));
		fout<<endl;
	}
	fout.close();
	system("pause");
	return 0 ;
}