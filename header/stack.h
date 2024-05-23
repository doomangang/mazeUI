//
// Created by 정지현 on 5/21/24.
//

#ifndef UNTITLED_STACK_H
#define UNTITLED_STACK_H

#include <stdio.h>
#define MAX_STACK 100

typedef struct t_Stack
{
	int s[MAX_STACK];
	int top;
}   Stack;

Stack create()
{
	Stack p;
	p.top = -1;
	return p;
}

int is_full(Stack *p)
{
	return ( p->top == MAX_STACK -1);
}

int is_empty(Stack *p)
{
	return (p->top == -1);
}

void push(Stack *p, int data)
{
	if(is_full(p))
	{
		printf("스택이 꽉찼습니다\n");
		return ;
	}
	else
	{
		p->top++;
		p->s[p->top] = data;
	}
}

int pop(Stack *p)
{
	if(is_empty(p))
	{
		printf("스택이 비어있습니다\n");
	}

	return p->s[(p->top)--];
}

int peek(Stack *p)
{
	if(is_empty(p))
		return 1;
	return p->s[p->top];
}
#endif //UNTITLED_STACK_H
