#include<stdint.h>
#define HASH_KEY 0xEE6B27EB



struct hash_table{
	int name_blocks_num;
	int prefix_num;
	int table[10000];
};

bool cmp_blocks(hash_table t1,hash_table t2);//按字块数排序 
bool cmp_prefix_num(hash_table t1,hash_table t2);//安出频率排序 
