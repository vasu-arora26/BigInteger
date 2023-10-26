#include "BigInteger.h"
#include <stdio.h>
#include <stdlib.h>

struct node *insert(struct node *head, int data) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  if (!temp) {
    exit(1);
  }
  temp->data = data;
  temp->next = head;
  return temp;
}

void insert_tail(struct BigInteger *num, int element) {
  struct node *x = (struct node *)malloc(sizeof(struct node));
  if (x == NULL) {
    return;
  }
  x->data = element;
  x->next = NULL;
  num->length += 1;
  if (num->head == NULL) {
    num->head = temp;
    return;
  }
  struct node *itr = num->head;
  while (itr->next != NULL) {
    itr = itr->next;
  }
  itr->next = temp;
}

long int length(struct node *head) {
  long int count = 0;
  while (head) {
    head = head->next;
    count++;
  }
  return count;
}

void displayLL(struct node *link) {
  if (!link)
    return;
  displayLL(link->next);
  printf("%d", link->data);
}

void display(struct BigInteger b) {
  if (b.head == NULL) {
    printf("0");
    return;
  }
  if (b.sign == '-')
    printf("-");
  displayLL(b.head);
}

struct BigInteger initialize(char *s) {
  struct BigInteger b;
  b.head = NULL;
  if (s[0] == '-')
    b.sign = '-';
  else
    b.sign = '+';
  int i;
  if (b.sign == '-')
    i = 1;
  else
    i = 0;
  for (i; s[i] != '\0'; i++) {
    b.head = insert(b.head, s[i] - '0'); 
  }
  b.length = length(b.head);
  return b;
}

struct node *reverse(struct node *head) {
  struct node *back = NULL, *front = NULL, *current = head;
  while (current != NULL) {
    front = current->next;
    current->next = back;
    back = current;
    current = front;
  }
  return back;
}

int compare(struct BigInteger a, struct BigInteger b) {
  if (b.length > a.length) {
    return -1;
  } else if (b.length == a.length) {
    int return_val = 0;
    a.head = reverse(a.head);
    b.head = reverse(b.head);
    struct node *head1 = a.head, *head2 = b.head;
    while (head1 != NULL && head2 != NULL) {
      if (head2->data > head1->data) {
        return_val = -1; 
        break;
      } else if (head1->data > head2->data) { 
        return_val = 1;
        break;
      }
      head1 = head1->next;
      head2 = head2->next;
    }
    a.head = reverse(a.head);
    b.head = reverse(b.head);
    return return_val;
  }
  return 1;
}

struct BigInteger add(struct BigInteger a, struct BigInteger b) {
  struct BigInteger num1;
  num1.head = NULL;
  num1.sign = '+';
  num1.length = 0;

  if (a.sign == '-' && b.sign == '-') {
    num1.sign = '-';
  } else if (a.sign == '-') {
    a.sign = '+';
    num1 = sub(b, a);
    a.sign = '-';
    return num1;
  } else if (b.sign == '-') {
    b.sign = '+';
    num1 = sub(a, b);
    b.sign = '-';
    return num1;
  }

  struct node *l1 = a.head, *l2 = b.head;
  int sum, carry = 0;

  while (l1 != NULL || l2 != NULL || carry != 0) {
    int d1 = (l1 != NULL) ? l1->data : 0;
    int d2 = (l2 != NULL) ? l2->data : 0;

    sum = d1 + d2 + carry;
    carry = sum / 10;
    insert_tail(&num1, sum % 10);

    if (l1 != NULL)
      l1 = l1->next;
    if (l2 != NULL)
      l2 = l2->next;
  }
  num1.length = length(num1.head);
  return num1;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b) {
  struct BigInteger num1;
  num1.head = NULL;
  num1.sign = '+';
  num1.length = 0;

  if (a.sign == '-' && b.sign == '+') {
    a.sign = '+';
    num1 = add(a, b);
    a.sign = '-';
    num1.sign = '-';
    return num1;
  } else if (a.sign == '+' && b.sign == '-') {
    b.sign = '+';
    num1 = add(a, b);
    b.sign = '-';
    return num1;
  } else if (a.sign == '-' && b.sign == '-') {
    b.sign = '+';
    a.sign = '+';
    num1 = sub(b, a);
    b.sign = '-';
    a.sign = '-';
    return num1;
  } else if (compare(a, b) == -1) {
    struct BigInteger temp = a;
    a = b;
    b = temp;
  }

  struct node *l1 = a.head, *l2 = b.head;
  int diff, borrow = 0;

  while (l1 != NULL || l2 != NULL) {
    int d1 = (l1 != NULL) ? l1->data : 0;
    int d2 = (l2 != NULL) ? l2->data : 0;

    diff = d1 - d2 - borrow;

    if (diff < 0) {
      diff += 10;
      borrow = 1;
    } else {
      borrow = 0;
    }

    insert_tail(&num1, diff);

    if (l1 != NULL)
      l1 = l1->next;
    if (l2 != NULL)
      l2 = l2->next;
  }
  num1.head = reverse(num1.head);
  while (num1.head != NULL && num1.head->data == 0) {
    struct node *temp = num1.head;
    num1.head = num1.head->next;
    free(temp);
  }
  num1.head = reverse(num1.head);
  num1.length = length(num1.head);
  return num1;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b) {
  struct node *n1 = a.head, *n2 = b.head;
  struct BigInteger num1 = initialize(""); 
  num1.length = 0;
  if (n1 == NULL || n2 == NULL) {
    return num1;
  }
  struct BigInteger mid, result = initialize("");
  int carry = 0, product = 0, i = 0;
  while (n2 != NULL) {
    n1 = a.head;
    carry = 0;
    mid = initialize("");
    for (int j = 0; j < i; j++) {
      insert_tail(&mid, 0);
    }
    while (n1 != NULL) {
      product = (n1->data) * (n2->data) + carry;
      insert_tail(&mid, product % 10);
      carry = product / 10;
      n1 = n1->next;
    }

    if (carry > 0) {
      insert_tail(&mid, carry);
    }

    result = add(mid, result);
    struct node *current = mid.head;
    while (current != NULL) {
      struct node *temp = current;
      current = current->next;
      free(temp);
    }

    n2 = n2->next;
    i++;
  }
  if (a.sign != b.sign) {
    result.sign = '-';
  }
  return result;
}

struct BigInteger div1(struct BigInteger a, struct BigInteger b) {
  struct BigInteger num1 = initialize("0");
  num1.length = 0;
  num1.sign = '+';
  char sig = '+';
  int flag = 0;
  if (b.length == 1 && b.head->data == 0) {
    printf("Error! Division by zero");
    return num1;
  }
  if (a.sign != b.sign)
    sig = '-';
  char t1 = a.sign;
  char t2 = b.sign;
  a.sign = '+';
  b.sign = '+';
  struct BigInteger temp = add(b, initialize("0"));
  while (compare(a, temp) >= 0) {
    temp = add(temp, b);
    num1 = add(num1, initialize("1"));
    flag = 1;
  }
  struct BigInteger zero = initialize("0");
  if (flag)
    num1.sign = sig;
  a.sign = t1;
  b.sign = t2;
  return num1;
}

struct BigInteger mod(struct BigInteger a, struct BigInteger b) {
  struct BigInteger num1 = initialize("0");
  num1.length = 0;
  num1.sign = '+';
  char sig = '+';
  int flag = 0;
  if (b.length == 1 && b.head->data == 0) {
    return num1;
  }
  if (a.sign != b.sign)
    sig = '-';
  char t1 = a.sign;
  char t2 = b.sign;
  a.sign = '+';
  b.sign = '+';
  struct BigInteger temp = add(b, initialize("0"));
  while (compare(a, temp) >= 0) {
    temp = add(temp, b);
    num1 = add(num1, initialize("1"));
  }
  struct BigInteger temp2 = sub(temp, b);
  struct BigInteger modulus = sub(a, temp2);
  a.sign = t1;
  b.sign = t2;
  return modulus;
}
