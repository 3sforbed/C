#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define INIT_SIZE 20
#define INCREMENT_SIZE 5

typedef int Status;
typedef int SElemType;

typedef struct{
    SElemType *base;
    SElemType *top;
    int size;
} SqStack;

Status InitStack(SqStack *s);
Status DestroyStack(SqStack *s);
Status ClearStack(SqStack *s);
Status IsEmpty(SqStack s);
Status GetLength(SqStack s);
Status GetTop(SqStack s, SElemType *e);
Status TraverseStack(SqStack s);
Status Push(SqStack *s,SElemType e);
Status Pop(SqStack *s,SElemType *e);

int main(){
    SqStack S;
    if (InitStack(&S)){
        SElemType e;
        int i;

        printf("init_success\n");

        if (IsEmpty(S)){
            printf("Stack is empty\n");
        }

        for (i = 0; i < 10; i++){
            Push(&S, i);
        }

        GetTop(S, &e);
        printf("The first element is %d\n", e);

        printf("length is %d\n", GetLength(S));

        Pop(&S, &e);
        printf("Pop element is %d\n", e);

        //判断是拷贝传参还是指针传参
        printf("outter:%p\tbase:%p\n",&S,&S.base);
        TraverseStack(S);

        if (DestroyStack(&S)){
            printf("\ndestroy_success\n");
        }
    }
}

Status InitStack(SqStack *s){
    s->base = (SElemType *) malloc(INIT_SIZE * sizeof(SElemType));
    if(!s->base){
        exit(OVERFLOW);
    }
    s->top = s->base;
    s->size = INIT_SIZE;
    return OK;
}
Status DestroyStack(SqStack *s){
    free(s->base);
    s->base = NULL;
    s->top = NULL;
    s->size = 0;
    return OK;
}
Status ClearStack(SqStack *s){
    s->top = s->base;
    return OK;
}
Status IsEmpty(SqStack s){
    if(s.top == s.base){
        return TRUE;
    }else{
        return FALSE;
    }
}
Status GetLength(SqStack s){
    return s.top - s.base;
}
Status GetTop(SqStack s, SElemType *e){
    if(s.top > s.base){
        *e = *(--s.top);
        return OK;
    }else{
        return ERROR;
    }
}
Status TraverseStack(SqStack s){
    printf("inner:%p\tbase:%p\n",&s,&s.base);
    while(s.top > s.base){
        printf("%d",*s.base);
        s.base++;
    }
    return OK;
}
Status Push(SqStack *s,SElemType e){
    if((s->top - s->base) / sizeof(SElemType) >= s->size){
        s->base = (SElemType *) realloc(s->base,(s->size + INCREMENT_SIZE) * sizeof(SElemType));
        if(!s->base){
            exit(OVERFLOW);
        }
        s->top = s->base + s->size;
        s->size += INCREMENT_SIZE;
    }
    *s->top = e;
    s->top++;
    return OK;
}
Status Pop(SqStack *s,SElemType *e){
    if(s->top == s->base){
        return ERROR;
    }
    s->top--;
    *e = *s->top;
    return OK;
}
