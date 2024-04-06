#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct{
element data[MAX_STACK_SIZE];
int top;
}StackType;

void init_stack(StackType *s)
{
    s->top=-1;
}

int is_empty(StackType *s)
{
    return (s->top==-1);
}

int is_full(StackType *s)
{
    return (s->top==(MAX_STACK_SIZE - 1));
}

void push(StackType *s,element item)
{
    if(is_full(s)){
        fprintf(stderr,"스택 포화 에러\n");
        return;
    }
    else s->data[++(s->top)]=item;
}

element pop(StackType *s)
{
   if(is_empty(s)){
        fprintf(stderr,"스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}

element peek(StackType *s)
{
   if(is_empty(s)){
        fprintf(stderr,"스택 공백 에러\n");
        exit(1);
    }
    else return s->data[(s->top)];
}

int prec(char op)   //연산자의 우선순위 설정
{
    switch(op){
    case '(': case ')':case '[': case']': case '{': case '}': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}

void infix_to_postfix(char exp[])
{
    int i=0;
    char ch,top_op;  //입력받은 문자를 하나씩 비교 ,top_op는 스택 제일 위
    int len=strlen(exp);
    StackType s;
    init_stack(&s);
    for(i=0;i<len;i++){
        ch=exp[i];
        switch(ch){
    case '+': case '-': case '*': case '/':  //괄호 연산자가 아닐경우
        while(!is_empty(&s)&&(prec(ch)<=prec(peek(&s))))   //스택이 비어있지 않고 현재연산자가 스택의 제일위 연산자보다 우선순위가 낮다면(ex +<*)
            printf("%c",pop(&s));    //스택의 제일 위 연산자를 꺼내어 출력
        push(&s,ch);    //스택에 현재 연산자를 저장
        break;
    case '(': case'[': case '{': //여는 괄호일 경우
        push(&s,ch);    //스택에 현재 연산자를 저장
        break;
    case ')': case ']': case '}':   //닫는 괄호일 경우
        top_op=pop(&s);               //top_op에 스택의 제일 위 연산자를 꺼내어 저장
        while((ch==')'&&top_op !='(')||(ch==']'&&top_op!='[')||(ch=='}'&&top_op!='{')){  //현재 연산자에 맞는 여는 괄호가 나올때 까지
                printf("%c",top_op);    //top 출력
                top_op=pop(&s);    //스택의 제일 위를 top에 저장
        }
        break;
    default:   //숫자일경우
        printf("%c",ch);   //그냥 출력
        break;
        }
    }
    while(!is_empty(&s))  //스택에 연산자가 남아있는경우 (ex 수식의 마지막이 숫자로 끝날경우 스택에 연산자가 남아있을 수 있음)
        printf("%c",pop(&s));  //남아있는 연산자를 출력
}
int main()
{
    char s[MAX_STACK_SIZE];
    printf("수식입력 :");
    scanf("%[^\n]s",s);
    printf("postfix==>");
    infix_to_postfix(s);
    return 0;
}
