#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    int weight;
    struct node*next;
};
struct node*enqueue(struct node*p,int a,int b){
    struct node*last=p;
    struct node*newnode=malloc(sizeof(struct node));
    newnode->data=a;
    newnode->weight=b;
    newnode->next=NULL;
    if(p==NULL){
        p=newnode;
    }
    else{
        while(last->next!=NULL){
            last=last->next;
        }
        last->next=newnode;
    }
    last=newnode;
    return p;
}
int min(int **t,int s){
    int m=-1;
    for(int i=0;i<s;i++){
        if(t[i][0]==0){
            if(t[i][1]!=-1){
                if(m==-1){
                    m=i;
                }
                else{
                    if(t[i][1]<t[m][1]){
                        m=i;
                    }
                }
            }
        }
    }
    return m;
}
int main(int argc,char*argv[]){
    FILE*i,*o;
    i=fopen(argv[1],"r");
    o=fopen("dijkstra.txt","w");
    
    if(i==NULL){
        printf("File not found!");
    }
    else{
        int x=0,y=0,w,l=0,h=0;
        while(fscanf(i,"%d %d %d",&x,&y,&w)!=EOF){
            l++;
            if(h<x){
                h=x;
            }
            if(h<y){
                h=y;
            }
        }
        rewind(i);
        int *table[h+1];
        struct node*a[h+1];
        for(int z=0;z<=h;z++){
            table[z]=malloc(2*sizeof(int));
            table[z][0]=0;
            table[z][1]=-1;
            a[z]=NULL;
        }
        for(int z=0;z<l;z++){
            fscanf(i,"%d %d %d",&x,&y,&w);
            a[x]=enqueue(a[x],y,w);
        }
        table[atoi(argv[2])][1]=0;
        while(min(table,h+1)!=-1){
            struct node*p=a[min(table,h+1)];
            while(p!=NULL){
                if(table[p->data][1]==-1||table[p->data][1]>table[min(table,h+1)][1]+p->weight){
                    table[p->data][1]=table[min(table,h+1)][1]+p->weight;
                }
                p=p->next;
            }
            table[min(table,h+1)][0]=1;
        }
        for(int z=0;z<=h;z++){
            fprintf(o,"%d %d\n",z,table[z][1]);
        }
    }
}