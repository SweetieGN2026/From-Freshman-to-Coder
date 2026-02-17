#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>//纯粹是为了contnttype
typedef int ElemType;

typedef enum {
    LEFT_PAREN, RIGHT_PAREN,//数学
    ADD, SUB, MUL, DIV, MOD,
    EOS, NUM
} contentType;
typedef struct {
    ElemType *data;
    int top;
} Stack;
void initStack(Stack *s) {
    s->data = (ElemType*)malloc(100 * sizeof(ElemType));
    s->top = -1;
}
void push(Stack *s, ElemType val) {
    s->top++;
    s->data[s->top] = val;
}
ElemType pop(Stack *s) {
    ElemType val = s->data[s->top];
    s->top--;
    return val;
}
contentType get_token(char c) {
    switch (c) {
        case '+':
            return ADD;
        case '-':
            return SUB;
        case '*':
            return MUL;
        case '/':
            return DIV;
        case '%':
            return MOD;
        default:
            if (isdigit(c))
                return NUM;
            else
                return EOS;
    }
}
int main() {
    char expr[] = "82/2+56*-";//这个是后缀  很简单  但是这个不能写中缀 程序识别不了
    Stack s;
    initStack(&s);

    int i = 0;
    char ch;
    while ((ch = expr[i++]) != '\0') {
        contentType token = get_token(ch);

        if (token == NUM) {
            push(&s, ch - '0');
        }
        else if (token == ADD || token == SUB ||
                 token == MUL || token == DIV || token == MOD) {
            ElemType op2 = pop(&s);
            ElemType op1 = pop(&s);
            switch (token) {
                case ADD:
                    push(&s, op1 + op2);
                    break;
                case SUB:
                    push(&s, op1 - op2);
                    break;
                case MUL:
                    push(&s, op1 * op2);
                    break;
                case DIV:
                    if (op2 == 0) {//保证数学成立
                        printf("数学错误\n");
                        free(s.data);
                        return 1;
                    }
                    else
                        push(&s, op1 / op2);
                    break;
                case MOD:
                    if (op2 == 0) {
                        printf("数学错误\n");
                        free(s.data);
                        return 1;
                    }
                    else
                        push(&s, op1 % op2);
                    break;
            }
                 }
    }
    ElemType result = pop(&s);//得出结果  调出栈顶
    printf("计算结果: %d\n", result);
    free(s.data);//释放
    return 0;
}