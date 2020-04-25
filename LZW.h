#include<iostream>
#include<string>
#include<stdint.h>
#include<fstream>
#include<bits/stdc++.h>
#include "Trie.h"
#include "encStream.h"

using namespace std;

#ifndef LZW_H
#define LZW_H

#define FLUSH_CODE 257
class LZW{
	private:
		string filename;
		ifstream infile;
		ofstream outfile;
		static uint16_t code;
		unsigned int maxCodeSize;
		unsigned int maxBitLen;
		int next_code_size;
		int current_code_bits;
		
		void InitializeDict(Trie& dictionary){
			for(int i=0;i<256;++i){
				string word = "";
				word += (char)i;
				dictionary.push(dictionary.begin(),word,i);
			}
		}
		
	public:
	
		LZW(string file,int maxBitLen = 16,bool bin = 0){
		
			this->maxBitLen = maxBitLen;
	
			this->maxCodeSize = (unsigned int) 1 << this->maxBitLen;
			
			if(!openFile(file,bin)){
				cerr<<"File doesn't open.";
			}	
			
		}
		
		bool openFile(string file,bool bin){
			if(infile.is_open()){
				infile.close();
			}
			if(!infile.is_open()){
				bin == 0 ? infile.open(file,ios::in) : infile.open(file,ios::in | ios::binary);	
			}
			filename = file;
			return infile.is_open();
		}
		
		
		void compress(){
			
			if(!infile.is_open())
				return;
			int pos = filename.find('.');
			string compFile = filename.substr(0,pos);
			compFile += ".bin";
			outfile.open(compFile,ios::binary | ios::out);
			if(!outfile.is_open()){
				return;	
			}
			
			Trie dict;
			InitializeDict(dict);
		    bool isFull = false;
			char byte = '\0';	
			string oldWord = "";
			string newWord = "";
			TrieNode* image = NULL;
			output_code_stream* fout = new output_code_stream(outfile,maxCodeSize);

			while(infile.get(byte)){
				newWord = oldWord + byte;
				if(dict.search(dict.begin(),newWord) != NULL){
					oldWord = newWord;
				}
				else{
					image = dict.search(dict.begin(),oldWord);
					*fout<< image->getCode();
				//	outfile.put(image->getCode() >> 8 & 0xff);
				//	outfile.put(image->getCode() & 0xff);
				
					if (code < maxCodeSize)
		            {
		                dict.push(dict.begin(),newWord,code);
		                if (code != (maxCodeSize - 1))
		                    code++;
		                else{
							*fout << FLUSH_CODE;					//Flush code
							dict.deleteDict();
							InitializeDict(dict);
							delete fout;
							fout = new output_code_stream(outfile,maxCodeSize);
							code = 258;
						}
						
		             
		            }
		          
					
					oldWord = byte;
				}
			}
			image = dict.search(dict.begin(),oldWord);
			*fout<<image->getCode();

			*fout<<END_OF_FILE;
			infile.close();
				
		}
		
		void decompress(){
			bool isFull = false;
			if(!infile.is_open())
				return;
			int pos = filename.find('.');
			string newFile = filename.substr(0,pos);
			newFile += "(1).txt";	
			outfile.open(newFile,ios::binary | ios::out | ios::trunc);
			
			while(true){
				input_code_stream fin(infile,maxCodeSize);
				unsigned int savedCode;
				char byte;
				vector<string> dict(65536);					//a simple string array or vector is enough for decompression
															//since the dictionary wont contain more than 65535 code entries.
				for(int i=0;i<256;++i){
					string pattern = "";
					pattern += (char)i;
					dict[i] = pattern;
				}
				string word = "";
				string newWord = "";
				int i = 0;
	
				while(fin >> savedCode){
					if(i == 0){
						word = dict[savedCode];
						i++;
						outfile<<word;
						continue;
					}	
					if(savedCode == FLUSH_CODE){
						code = 258;
						break;
					}
					
					if(dict[savedCode].empty()){
						newWord = word + word[0];
					}
					else{
						newWord = dict[savedCode];
					}
					outfile << newWord;
					
					if (code < maxCodeSize)
			        {
			            dict[code] = word + newWord[0];
			            if (code != (maxCodeSize-1))
			                code++;
			        }
					
					word = newWord;
				}
				
				if(savedCode == END_OF_FILE){
					return;
				}
				
			}
			
			
		}
		
		~LZW(){
			outfile.close();
			infile.close();
		}
		
};

uint16_t LZW::code = 258;


#endif
