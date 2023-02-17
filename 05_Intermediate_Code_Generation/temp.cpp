#include <cstdio>
int main(){
 
	int i,j,k,ll;
 
	for(i=0;i<6;i++){
		printf("%d\n",i);
	}
 
	k = 4;
	ll = 6;
	while(k>0){
		ll = ll + 3;
		k--;
	}
 
	printf("%d\n",ll);
	printf("%d\n",k);
	
	k = 4;
	ll = 6;
	
	while(k--){
		ll = ll + 3;
	}
 
	printf("%d\n",ll);
	printf("%d\n",k);
 
 
	return 0;
}
