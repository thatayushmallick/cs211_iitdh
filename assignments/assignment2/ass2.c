#include<stdio.h>
void s(int*a,int*b){
	int t=*a;
	*a=*b;
	*b=t;
}
int q(int a[],int i,int j){
	if(i<j){
        int x=i;
	    for(int y=i;y<j;y++){
		    if(a[y]<a[j]){
			    s(&a[x],&a[y]);
	    		x++;
	    	}
	    }
	    s(&a[x],&a[j]);
        q(a,i,x-1);
        q(a,x+1,j);
    }
}
int main(int argc,char*argv[]){
	FILE *i,*o;
	i=fopen(argv[1],"r");
	o=fopen("quicksort.txt","w");
	if(i==NULL){
		printf("FILE NOT FOUND");
		return 0;
	}
	else{
		int n,l=0;
		while(fscanf(i,"%d",&n)!=EOF){
			l++;
		}
		rewind(i);
		int a[l],b=0;
		while(fscanf(i,"%d",&n)!=EOF){
			a[b]=n;
			b++;
		}
        q(a,0,l-1);
        for(int x=0;x<l;x++){
            fprintf(o,"%d\n",a[x]);
        }
	}
	return 0;
}