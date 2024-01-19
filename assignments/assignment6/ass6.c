#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node*next;
};
struct node*head=NULL;
struct node*enqueue(struct node*p,int a){
    struct node*last=p;
    struct node*newnode=malloc(sizeof(struct node));
    newnode->data=a;
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
int main(int argc,char*argv[]){
    FILE*i,*o;
    i=fopen(argv[1],"r");
    o=fopen("sd.txt","w");
    
    if(i==NULL){
        printf("File not found!");
    }
    else{
        int n,m,p,q;
        fscanf(i,"%d",&n);
        fscanf(i,"%d",&m);
        int table[n][2];
        struct node*adjac[n];
        
        for(int z=0;z<n;z++){
            table[z][0]=0;
            table[z][1]=-1;
            adjac[z]=NULL;
        }
        for(int y=0;y<m;y++){
            fscanf(i,"%d",&p);
            fscanf(i,"%d",&q);
            adjac[p]=enqueue(adjac[p],q);
            adjac[q]=enqueue(adjac[q],p);
        }
        head=enqueue(head,0);
        table[0][0]=1;
        table[0][1]=0;
        while(head!=NULL){
            struct node*trav=adjac[head->data];
            while(trav!=NULL){
                if(table[trav->data][0]==0){
                    head=enqueue(head,trav->data);
                    table[trav->data][0]=1;
                    table[trav->data][1]=table[head->data][1]+1;
                }
                trav=trav->next;
            }
            head=head->next;
        }
        for(int x=0;x<n;x++){
            fprintf(o,"%d\n",table[x][1]);
        }
    }
}