#include<stdio.h>
int t=-1;
char push(char a[],char b){
    t+=1;
    a[t]=b;
}
char pop(char a[]){
    t-=1;
    return a[t+1];
}
int precedence(char a){
	switch (a){
		case'+':
		case'-':
		return 1;
		case'*':
		case'/':
		case'%':
		return 2;
		case'^':
		return 3;
		case'(':
		case')':
		return 4;
	}
}
int main(int argc,char*argv[]){
	FILE *i,*o;
	i=fopen(argv[1],"r");
    o=fopen("output.txt","w");
	if(i==NULL){
		printf("File Not Found");
	}
	else{
		char x;
        int l=0,b=0,d=0;
        int e=-1;
		while((x=fgetc(i))!=EOF){
			if(x>='a'&&x<='z'){
                if(e==0||e==3){
                    fprintf(o,"Invalid Expression");
                    return 0;
                }
                else{
                    e=0;
                }
			}
			else if(x=='+'||x=='-'||x=='*'||x=='/'||x=='%'||x=='^'){
				if(e==1||e==2){
                    fprintf(o,"Invalid Expression");
                    return 0;
                }
                else{
                    e=1;
                }
			}
            else if(x=='('){
                if(e==0){
                    fprintf(o,"Invalid Expression");
                    return 0;
                }
                else{
                    e=2;
                }
                b++;
                d++;
            }
            else if(x==')'){
                if(e==1){
                    fprintf(o,"Invalid Expression");
                    return 0;
                }
                else{
                    e=3;
                }
                d--;
            }
            if(d<0){
                fprintf(o,"Unequal Parentheses");
                return 0;
            }
            l++;
		}
        if(d!=0){
            fprintf(o,"Unequal Parentheses");
            return 0;
        }
        rewind(i);
        char p[l],s[4*b+3];
        int q=0,f=0;
        while((x=fgetc(i))!=EOF){
            if(x>='a'&&x<='z'){
                p[q]=x;
                q++;
            }
            else if(x=='('){
                push(s,x);
                fprintf(o,"( is pushed into stack\n");
                f=0;
            }
            else if(x==')'){
                while(s[t]!='('){
                    p[q]=pop(s);
                    fprintf(o,"%c is popped from stack\n",p[q]);
                    q++;
                    f=precedence(s[t]);
                }
                pop(s);
                fprintf(o,"( is popped from stack\n");
                f=precedence(s[t]);
            }
            else if(x=='+'||x=='-'||x=='*'||x=='/'||x=='%'||x=='^'){
                if(precedence(x)>f){
                    push(s,x);
                    fprintf(o,"%c is pushed into stack\n",x);
                    f=precedence(x);
                }
                else{
                    while(precedence(x)<=f){
                        p[q]=pop(s);
                        fprintf(o,"%c is popped from stack\n",p[q]);
                        q++;
                        f=precedence(s[t]);
                    }
                    push(s,x);
                    fprintf(o,"%c is pushed into stack\n",x);
                    f=precedence(x);
                }
            }
        }
        while(t!=-1){
            p[q]=pop(s);
            fprintf(o,"%c is popped from stack\n",p[q]);
            q++;
        }
        p[q]='\0';
        fprintf(o,"Postfix expression is: %s",p);
	}
	return 0;
}