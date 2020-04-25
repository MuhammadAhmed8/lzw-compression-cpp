#include<iostream>
#include<string>
#include<cstring>
#include<stdint.h>
#include "hashmap.h"

using namespace std;

#ifndef Trie_H
#define Trie_H


class TrieNode{
	private:
		uint16_t code;
		bool isWord;
		Hashmap<int,TrieNode*> children; 
		
	public:
		char byte;
		
		TrieNode(char byte = '\0', uint16_t code = 65535, bool isWord = false,int n = 22):children(n){
			
			this->byte = byte;
			this->code = code;
			this->isWord = isWord;
		}
		
		uint16_t getCode() const{
			return code;
		}
		
		
	friend class Trie;	
			 
};

class Trie{
	private:
		TrieNode* root;
	
	public:
		Trie():root{new TrieNode('\0',65535,false,256)}{}
		
		TrieNode* begin(){
			return root;
		}
		void deleteTrie(const TrieNode* root){
			if(root != NULL){
				delete root;
			}	
		}
		void deleteDict(){
			deleteTrie(this->root);
			this->root = new TrieNode('\0',65535,false,256);
		}
		
		void push(TrieNode* root,string word,uint16_t code){
	
			if(word.size() == 0){	
				root->isWord = true;
				root->code = code;
				return;	
			}
			char s = word.at(0);
			
			TrieNode* childNode = root->children[s];
			if(childNode == NULL){
				childNode = new TrieNode(s);										//not found
				root->children.insert(s,childNode);        							//adds a new child node								
			}
			
			push(childNode,word.substr(1),code);
		}
		
		
		
		TrieNode* search(TrieNode* root,string word){

			if(word.size() == 0){
				if(root->isWord)
					return root;
				return NULL;	
			}
			TrieNode* child = root->children[word[0]];
			if(child == NULL){
				return NULL;
			}
			return search(child,word.substr(1));
					
		}
		
		void print(TrieNode* root){
			cout<<root->byte<<endl;
			for(int i=0;i<256;++i){
				TrieNode* child = root->children[i];
				if(child != NULL)
					print(child);
			}
		}
		
		~Trie(){
			deleteTrie(this->root);
		}	
		
		
};





#endif
