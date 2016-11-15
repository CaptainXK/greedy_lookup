#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

#include "main.h"
#include "nametool.h"
#include "hashtool.h"
using namespace std;


int main(){
	vector<hash_table> ht_group; 
	uint32_t rank_mark[32]={0};
	ifstream fin("names.txt",ios::in);
	char temp_name[1000]="";
	int temp_len=0;
	int temp_block_num=0;
	int temp_face=0;
	uint64_t temp_hash_value=0;
	vector<hash_table>::iterator item; 
	bool is_new;
	srand(time(NULL));
	
	if(!fin.is_open()){
		cout<<"file open err!"<<endl;
		exit(1);
	}	
	
	while(!fin.eof()){
		fin>>temp_name;
		temp_len=strlen(temp_name);
		temp_block_num=get_name_blocks_num(temp_name);
		temp_hash_value=murmurHash64B(temp_name, temp_len, HASH_KEY);
		if(!ht_group.empty()){//容器非空 
			for(item=ht_group.begin(); item!=ht_group.end(); item++){
				if(item->name_blocks_num == temp_block_num){
					item->table[temp_hash_value%10000]=rand()%10;
					item->prefix_num++;
					break;
				}
			}
			if(item == ht_group.end()){
				is_new = true;
			}
			else
				continue;
		}
		if(is_new || ht_group.empty()){//如果容器为空，或者容器中没有和当前name字块数相同的name集合 
			hash_table* ht_temp = new hash_table();
			ht_temp->name_blocks_num = temp_block_num;
			ht_temp->prefix_num = 1;
			ht_temp->table[temp_hash_value%10000]=rand()%10;
		 	ht_group.push_back(*ht_temp);
		 }
	}
	sort(ht_group.begin(), ht_group.end(), cmp_blocks);	
	
	cout<<"done!"<<endl;
	
	for(item=ht_group.begin(); item!=ht_group.end(); item++){
		cout<<"blocks:"<<item->name_blocks_num<<" ";
		cout<<"prefixs:"<<item->prefix_num<<endl;
	}
	
	fin.close(); 
	return 0;
}

bool cmp_blocks(hash_table t1,hash_table t2){//>:降序 <:降序 
	return t1.name_blocks_num < t2.name_blocks_num;
}

bool cmp_prefix_num(hash_table t1,hash_table t2){
	return t1.prefix_num < t2.prefix_num;
}
