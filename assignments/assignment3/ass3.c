#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
    int data;
    struct node*next;
};
struct node*head=NULL;
struct node*tail=NULL;
void display(FILE*f){
    if(head==NULL){
        fprintf(f,"Queue is Empty\n");
        return;
    }
    else{
        struct node*p=malloc(sizeof(struct node));
        p=head;
        fprintf(f,"Elements of the queue: ");
        while(p->next!=head){
            fprintf(f,"%d ",p->data);
            p=p->next;
        }
        fprintf(f,"%d\n",p->data);
    }
}
void enqueue(FILE*f,int a){
    struct node*newnode=malloc(sizeof(struct node));
    newnode->data=a;
    if(head==NULL){
        head=newnode;
    }
    else{
        tail->next=newnode;
    }
    newnode->next=head;
    tail=newnode;
    fprintf(f,"Inserted value: %d\n",a);
}
void dequeue(FILE*f){
    if(head==NULL){
        fprintf(f,"Queue is Empty\n");
    }
    else{
        struct node*d=head;
        if(head==tail){
            head=NULL;
            tail=NULL;
        }
        else{
            tail->next=head->next;
            head=head->next;
        }
        fprintf(f,"deleted value: %d\n" ,d->data);
        free(d);
    }
}
int main(int argc,char*argv[]){
    FILE*i,*o;
    i=fopen(argv[1],"r");
    o=fopen("output.txt","w");
    if(i==NULL){
        printf("File not found!");
    }
    else{
        char c[10];
        int e=0;
        while(fscanf(i,"%s",c)!=EOF){
            if(!strcmp(c,"display")){
                display(o);
            }
            if(e==1){
                enqueue(o,atoi(c));
                e=0;
            }
            if(!strcmp(c,"enqueue")){
                e=1;
            }
            if(!strcmp(c,"dequeue")){
                dequeue(o);
            }
        }
    }
    return 0;
}