#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	char data[50];
	struct node*next;
};
int sum(char a[]){
	int s=0;
	for(int x=0;x<strlen(a);x++){
        s+=a[x];
	}
	return s;
}
int anagram(char p[],char q[]){
    if(strlen(p)!=strlen(q)){
        return 0;
    }
    else{
        int f[128]={0};
        for(int x=0;x<strlen(p);x++){
            f[p[x]]++;
            f[q[x]]--;
        }
        for(int y=0;y<128;y++){
            if(f[y]!=0){
                return 0;
            }
        }
        return 1;
    }
}
int main(int argc,char*argv[]){
	FILE*w,*q,*a;
	w=fopen(argv[1],"r");
	q=fopen(argv[3],"r");
	a=fopen("anagrams.txt","w");
	if(w==NULL||q==NULL){
		printf("File(s) not found!");
	}
	else{
		char c[50];
        struct node*hash[atoi(argv[2])];
        for(int x=0;x<atoi(argv[2]);x++){
            hash[x]=NULL;
        }
		while(fscanf(w,"%s",c)!=EOF){
            int i=sum(c)%atoi(argv[2]);
            struct node*new=malloc(sizeof(struct node));
            strcpy(new->data,c);
            new->next=hash[i];
            hash[i]=new;
		}
        int n=0;
        while(fscanf(q,"%s",c)!=EOF){
            if(n==1){
                fprintf(a,"\n");
            }
            n=0;
            struct node*t=hash[sum(c)%atoi(argv[2])];
            while(t!=NULL){
                if(anagram(c,t->data)==1){
                    fprintf(a,"%s",t->data);
                    n=1;
                    break;
                }
                t=t->next;
            }
            if(t!=NULL){
                t=t->next;
            }
            while(t!=NULL){
                if(anagram(c,t->data)==1){
                    fprintf(a," %s",t->data);
                }
                t=t->next;
            }
            if(n==0){
                fprintf(a,"\n");
            }
        }
	}
}