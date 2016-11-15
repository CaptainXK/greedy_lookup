#include "nametool.h"

int get_name_blocks_num(char name[]){
	int i=0;
	int res=0;
	for(i=0; i<strlen(name); i++){
		if(name[i]=='/')
			res++;
	}
	return res;
}
