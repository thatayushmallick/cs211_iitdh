#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
    struct node*left;
    int data;
    struct node*right;
};
struct node*root=NULL;
int search(struct node*t,int a){
    if(t==NULL){
        return 0;
    }
    else{
        if(a<t->data){
            search(t->left,a);
        }
        else if(a==t->data){
            return 1;
        }
        else if(a>t->data){
            search(t->right,a);
        }
    }
}
void insert(int a){
    if(search(root,a)==0){
        struct node*n=malloc(sizeof(struct node));
        n->left=NULL;
        n->data=a;
        n->right=NULL;
        if(root==NULL){
            root=n;
        }
        else{
            struct node*c=root,*p;
            while(c!=NULL){
                p=c;
                if(a<c->data){
                    c=c->left;
                }
                else{
                    c=c->right;
                }
            }
            if(a<p->data){
                p->left=n;
            }
            else{
                p->right=n;
            }
        }
    }
}
void preorder(FILE*f,struct node*t){
    if(t!=NULL){
        fprintf(f,"%d ",t->data);
        preorder(f,t->left);
        preorder(f,t->right);
    }
}
void inorder(FILE*f,struct node*t){
    if(t!=NULL){
        inorder(f,t->left);
        fprintf(f,"%d ",t->data);
        inorder(f,t->right);
    }
}
void postorder(FILE*f,struct node*t){
    if(t!=NULL){
        postorder(f,t->left);
        postorder(f,t->right);
        fprintf(f,"%d ",t->data);
    }
}
int minimum(struct node*t){
    while(t->left!=NULL){
        t=t->left;
    }
    return t->data;
}
int maximum(struct node*t){
    while(t->right!=NULL){
        t=t->right;
    }
    return t->data;
}
void predecessor(FILE*f,int a){
    if(root==NULL){
        fprintf(f,"Tree is empty\n");
    }
    else{
        if(search(root,a)==0){
            fprintf(f,"%d does not exist\n",a);
        }
        else{
            if(minimum(root)==a){
                fprintf(f,"predecessor of %d does not exist\n",a);
            }
            else{
                struct node*c=root,*p=root;
                while(c->data!=a){
                    if(a<c->data){
                        c=c->left;
                    }
                    else{
                        p=c;
                        c=c->right;
                    }
                }
                if(c->left==NULL){
                    fprintf(f,"%d\n",p->data);
                }
                else{
                    fprintf(f,"%d\n",maximum(c->left));
                }
            }
        }
    }
}
void successor(FILE*f,int a){
    if(root==NULL){
        fprintf(f,"Tree is empty\n");
    }
    else{
        if(search(root,a)==0){
            fprintf(f,"%d does not exist\n",a);
        }
        else{
            if(maximum(root)==a){
                fprintf(f,"successor of %d does not exist\n",a);
            }
            else{
                struct node*c=root,*p=root;
                while(c->data!=a){
                    if(a<c->data){
                        p=c;
                        c=c->left;
                    }
                    else{
                        c=c->right;
                    }
                }
                if(c->right==NULL){
                    fprintf(f,"%d\n",p->data);
                }
                else{
                    fprintf(f,"%d\n",minimum(c->right));
                }
            }
        }
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
        char c[20];
        int se=0,in=0,pr=0,su=0;
        while(fscanf(i,"%s",c)!=EOF){
            if(se==1){
                if(search(root,atoi(c))==0){
                    fprintf(o,"%d not found\n",atoi(c));
                }
                else{
                    fprintf(o,"%d found\n",atoi(c));
                }
                se=0;
            }
            if(!strcmp(c,"search")){
                se=1;
            }
            if(in==1){
                insert(atoi(c));
                fprintf(o,"%d inserted\n",atoi(c));
                in=0;
            }
            if(!strcmp(c,"insert")){
                in=1;
            }
            if(!strcmp(c,"preorder")){
                preorder(o,root);
                fprintf(o,"\n");
            }
            if(!strcmp(c,"inorder")){
                inorder(o,root);
                fprintf(o,"\n");
            }
            if(!strcmp(c,"postorder")){
                postorder(o,root);
                fprintf(o,"\n");
            }
            if(!strcmp(c,"minimum")){
                if(root==NULL){
                    fprintf(o,"\n");
                }
                else{
                    fprintf(o,"%d\n",minimum(root));
                }
            }
            if(!strcmp(c,"maximum")){
                if(root==NULL){
                    fprintf(o,"\n");
                }
                else{
                    fprintf(o,"%d\n",maximum(root));
                }
            }
            if(pr==1){
                predecessor(o,atoi(c));
                pr=0;
            }
            if(!strcmp(c,"predecessor")){
                pr=1;
            }
            if(su==1){
                successor(o,atoi(c));
                su=0;
            }
            if(!strcmp(c,"successor")){
                su=1;
            }
        }
    }
}
