#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H
#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *next;
};

struct BigInteger {
  struct node *head;
  long int length;
  char sign;
};

struct node *insert(struct node *head, int val);
void insert_tail(struct BigInteger *num, int element);
long int length(struct node *head);
void displayLL(struct node *link);
void display(struct BigInteger b);
struct BigInteger initialize(char *s);
struct node *reverse(struct node *head);
int compare(struct BigInteger a, struct BigInteger b);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);
struct BigInteger mod(struct BigInteger a, struct BigInteger b);
void freeL(struct BigInteger *num);

#endif
