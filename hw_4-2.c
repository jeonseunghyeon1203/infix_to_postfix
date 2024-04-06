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
        fprintf(stderr,"���� ��ȭ ����\n");
        return;
    }
    else s->data[++(s->top)]=item;
}

element pop(StackType *s)
{
   if(is_empty(s)){
        fprintf(stderr,"���� ���� ����\n");
        exit(1);
    }
    else return s->data[(s->top)--];
}

element peek(StackType *s)
{
   if(is_empty(s)){
        fprintf(stderr,"���� ���� ����\n");
        exit(1);
    }
    else return s->data[(s->top)];
}

int prec(char op)   //�������� �켱���� ����
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
    char ch,top_op;  //�Է¹��� ���ڸ� �ϳ��� �� ,top_op�� ���� ���� ��
    int len=strlen(exp);
    StackType s;
    init_stack(&s);
    for(i=0;i<len;i++){
        ch=exp[i];
        switch(ch){
    case '+': case '-': case '*': case '/':  //��ȣ �����ڰ� �ƴҰ��
        while(!is_empty(&s)&&(prec(ch)<=prec(peek(&s))))   //������ ������� �ʰ� ���翬���ڰ� ������ ������ �����ں��� �켱������ ���ٸ�(ex +<*)
            printf("%c",pop(&s));    //������ ���� �� �����ڸ� ������ ���
        push(&s,ch);    //���ÿ� ���� �����ڸ� ����
        break;
    case '(': case'[': case '{': //���� ��ȣ�� ���
        push(&s,ch);    //���ÿ� ���� �����ڸ� ����
        break;
    case ')': case ']': case '}':   //�ݴ� ��ȣ�� ���
        top_op=pop(&s);               //top_op�� ������ ���� �� �����ڸ� ������ ����
        while((ch==')'&&top_op !='(')||(ch==']'&&top_op!='[')||(ch=='}'&&top_op!='{')){  //���� �����ڿ� �´� ���� ��ȣ�� ���ö� ����
                printf("%c",top_op);    //top ���
                top_op=pop(&s);    //������ ���� ���� top�� ����
        }
        break;
    default:   //�����ϰ��
        printf("%c",ch);   //�׳� ���
        break;
        }
    }
    while(!is_empty(&s))  //���ÿ� �����ڰ� �����ִ°�� (ex ������ �������� ���ڷ� ������� ���ÿ� �����ڰ� �������� �� ����)
        printf("%c",pop(&s));  //�����ִ� �����ڸ� ���
}
int main()
{
    char s[MAX_STACK_SIZE];
    printf("�����Է� :");
    scanf("%[^\n]s",s);
    printf("postfix==>");
    infix_to_postfix(s);
    return 0;
}
