#include<stdio.h>
#include<stdlib.h>
struct s{
    int data;
    struct s*next;
};
struct d{
    int data;
    struct d*prev,*next;
};
int c=0;
struct s*stack=NULL,*head=NULL,*tail=NULL;
struct d*list=NULL;
int main(int agrc,char*argv[]){
    FILE*i,*s,*q,*l;
    i=fopen(argv[1],"r");
    s=fopen("stack.txt","w");
    q=fopen("queue.txt","w");
    l=fopen("dll.txt","w");
    if(i==NULL){
        printf("File not found!");
    }
    else{
        char x;
        int y;
        while((x=fgetc(i))!=EOF){
            if(x=='+'){
                fscanf(i,"%d",&y);
                if(c>=atoi(argv[2])){
                    fprintf(s,"overflow\n");
                    fprintf(q,"overflow\n");
                }
                else{
                    struct s*n1=malloc(sizeof(struct s));
                    n1->data=y;
                    n1->next=stack;
                    stack=n1;
                    fprintf(s,"pushed %d\n",y);
                    struct s*n2=malloc(sizeof(struct s));
                    n2->data=y;
                    if(head==NULL){
                        head=n2;
                    }
                    else{
                        tail->next=n2;
                    }
                    n2->next=head;
                    tail=n2;
                    fprintf(q,"enqueued %d\n",y);
                    c++;
                }
                struct d*n3=malloc(sizeof(struct d));
                n3->data=y;
                n3->prev=NULL;
                n3->next=list;
                if(list!=NULL){
                    list->prev=n3;
                }
                list=n3;
                fprintf(l,"inserted %d\n",y);
            }
            else if(x=='-'){
                fscanf(i,"%d",&y);
                if(c<=0){
                    fprintf(s,"underflow\n");
                    fprintf(q,"underflow\n");
                }
                else{
                    struct s*d=malloc(sizeof(struct s));
                    d=stack;
                    stack=d->next;
                    fprintf(s,"popped %d\n",d->data);
                    d=head;
                    if(head==tail){
                        head=NULL;
                        tail=NULL;
                    }
                    else{
                        tail->next=head->next;
                        head=head->next;
                    }
                    fprintf(q,"dequeued %d\n",d->data);
                    free(d);
                    c--;
                }
                struct d*dl=malloc(sizeof(struct d));
                dl=list;
                while(dl!=NULL){
                    if(y==dl->data){
                        break;
                    }
                    dl=dl->next;
                }
                if(dl==NULL){
                    fprintf(l,"cannot delete %d\n",y);
                }
                else{
                    if(dl->prev==NULL){
                        if(dl->next==NULL){
                            list=NULL;
                        }
                        else{
                            dl->next->prev=NULL;
                            list=dl->next;
                        }
                    }
                    else if(dl->next==NULL){
                        dl->prev->next=NULL;
                    }
                    else{
                        dl->prev->next=dl->next;
                        dl->next->prev=dl->prev;
                    }
                    fprintf(l,"deleted %d\n",dl->data);
                    free(dl);
                }
            }
            else if(x=='?'){
                fscanf(i,"%d",&y);
                int f=0;
                struct s*t=malloc(sizeof(struct s));
                t=stack;
                while(t!=NULL){
                    if(y==t->data){
                        fprintf(s,"found %d\n",y);
                        f=1;
                        break;
                    }
                    t=t->next;
                }
                if(f==0){
                    fprintf(s,"not found %d\n",y);
                }
                else{
                    f=0;
                }
                if(head==NULL){
                    fprintf(q,"not found %d\n",y);
                }
                else{
                    t=head;
                    while(t!=tail){
                        if(y==t->data){
                            fprintf(q,"found %d\n",y);
                            f=1;
                            break;
                        }
                        t=t->next;
                    }
                    if(f==0){
                        if(y==t->data){
                            fprintf(q,"found %d\n",y);
                            f=1;
                        }
                        if(f==0){
                            fprintf(q,"not found %d\n",y);
                        }
                        else{
                            f=0;
                        }
                    }
                    else{
                        f=0;
                    }
                }
                struct d*p=malloc(sizeof(struct d));
                p=list;
                while(p!=NULL){
                    if(y==p->data){
                        fprintf(l,"found %d\n",y);
                        f=1;
                        break;
                    }
                    p=p->next;
                }
                if(f==0){
                    fprintf(l,"not found %d\n",y);
                }
            }
            else if(x=='!'){
                struct s*t=malloc(sizeof(struct s));
                t=stack;
                while(t!=NULL){
                    fprintf(s,"%d ",t->data);
                    t=t->next;
                }
                fprintf(s,"\n");
                if(head==NULL){
                    fprintf(q,"\n");
                }
                else{
                    t=head;
                    while(t->next!=head){
                        fprintf(q,"%d ",t->data);
                        t=t->next;
                    }
                    fprintf(q,"%d \n",t->data);
                }
                struct d*p=malloc(sizeof(struct d));
                p=list;
                while(p!=NULL){
                    fprintf(l,"%d ",p->data);
                    p=p->next;
                }
                fprintf(l,"\n");
            }
        }
    }
}