#include<bits/stdc++.h>
using namespace std;

#ifndef Hashmap_H
#define Hashmap_H

template<class Key,class T>
class Hashmap{
	public:
		vector<T> table;
		int tableSize;
		int size;
		Hashmap(int capacity = 22) : table(capacity + 1), size(0), tableSize(capacity){}
		
		void insert(Key k,T elem){
			int i = 0;
			int offset = 1;
			int j = hash(k);
			int index = (j + i) % tableSize ;
			while(table[index] != NULL){
				i += offset;
				offset += 2;
				index = (j + i) % tableSize;
			}
			table[index] = elem;
			size++;
			if(size > table.capacity() / 2){
				rehash();
			}
		}
		
		void rehash(){
			vector<T> temp = table;
			table.resize(nextPrime(table.capacity() * 2));
			tableSize = table.capacity();			
		}
		
		int hash(Key k){
			int i = getIndex(k);
			int index = i % tableSize;
			return index;
		}
		
		int getIndex(char s){
			int i = (int)s;
			if(i < 0){
				return abs(i) + 127;
			}
			return i;
		}
		
		T operator[](Key k){
			int i = 0;
			int offset = 1;
			int j = hash(k);
			int index = (j + i) % tableSize;
			while(table[index] != NULL && table[index]->byte != k){
				i += offset;
				offset += 2;
				index = (j + i) % tableSize;
			}
			return table[index];
		}
		
		~Hashmap(){
			for(int i=0;i<table.size();++i){
				if(table[i] != NULL)
					delete table[i];
			}
		}
		
		bool isPrime(int n){  
		    if (n <= 1)  return false;  
		    if (n <= 3)  return true;  
		    
		    if (n%2 == 0 || n%3 == 0) return false;  
		    
		    for (int i=5; i*i<=n; i=i+6)  
		        if (n%i == 0 || n%(i+2) == 0)  
		           return false;  
		    
		    return true;  
		}  
		  
		int nextPrime(int N) { 
		    if (N <= 1) 
		        return 2; 
		  
		    int prime = N; 
		    bool found = false; 
		    
		    while (!found) { 
		        prime++; 
		  
		        if (isPrime(prime)) 
		            found = true; 
		    } 
		  
		    return prime; 
		}
		
};

#endif
