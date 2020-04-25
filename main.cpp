#include<iostream>
#include<string>
#include "Trie.h"
#include "LZW.h"

using namespace std;

/* Trie is used as a dictionary for compression.Trie
   contains a hashmap to store pointers to its children.
   Decompression uses a dynamic array of strings since the code
   size is fixed.The LZW algorithm uses a 16-bit dictionary, and 
   it is flushed after it is filled up with 2 << bits - 1  or 65535 entries.
*/
int main(){
	clock_t start,end;
	char n;
	string file;
	cout<<"Enter file: ";
	cin>>file;
	cout<<"Press c or d: ";
	cin>>n;
	if(n == 'c'){
		LZW lzc(file,16,1);
		start = clock();
		lzc.compress();
		end = clock();
	}
	else{
		LZW lzd(file,16,1);
		start = clock();
		lzd.decompress();
		end = clock();
	}	
	
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout<<"\nTime taken "<<time_taken<<" secs"<<endl;

}

				

