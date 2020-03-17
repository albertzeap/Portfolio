//
//  main.c
//  rpn
//
//  Created by William McCarthy on 192//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h> //Exercise 4-5
#include <string.h>

#define MAXOP   100    /* max size of operand/operator */
#define NUMBER '0'     /* signal that a number was found */
#define MATH '1'

#define MAXVAL  100
#define VARIABLE '3'
#define ENGLISH 26

size_t sp = 0;   // aka unsigned long -- printf using %zu
double val[MAXVAL];   // stack of values
double variables[ENGLISH];

char buf[BUFSIZ];
size_t bufp = 0;

int getch_(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }
void ungetch_(int c) {
  if (bufp >= BUFSIZ) { fprintf(stderr, "ungetch: too many characters\n");  return; }
  buf[bufp++] = c;
}

int getop(char* s) {
  int i, c;
  while ((s[0] = c = getch_()) == ' ' || c == '\t') { }  // skip whitespace
  s[1] = '\0';


  if ((c == '=') || (c == '?')){ return VARIABLE; }

  //if (isalpha(c)) {return MATH;}

  if (!isdigit(c) && c != '.') { return c; }  // if not a digit, return

  i = 0;
  if (isdigit(c)) {  // get digits before '.'
    while (isdigit(s[++i] = c = getch_())) { }
  }
  if (c == '.') {    // get digits after decimal (if any)
    while (isdigit(s[++i] = c = getch_())) { }
  }
  s[i] = '\0';
  if (c != EOF) { ungetch_(c); }
  return NUMBER;      // return type is NUMBER, number stored in s
}

double pop(void) {
  if (sp == 0) { fprintf(stderr, "stack underflow\n");  return 0.0; }
  return val[--sp];
}

void push(double f) {
  if (sp == MAXVAL) { fprintf(stderr, "stack overflow -- can't push %g\n", f);  return; }
  val[sp++] = f;
}

/*
void stack(char * s){
  ++s; //skip over leading '@' symbol
  if strcmp(s, "duplicate" == 0);{

} else if (strcmp (s, "peek")==0)

}

*/

void printTop(void){
  double top = pop();
  printf("%g is the top of the stack\n", top );
}

void duplicate(void){
  double temp = pop();

  push(temp);
  push(temp);
}

void swap(void){
  double one = pop();
  double two = pop();

  push(two);
  push(one);
}

void clear(void){
  sp = 0;

}


void variable(char * s){
  if(*[s+1] == '=') { variables[*s - 'A'] = pop();}
  if(*[s+1] == '?') { push(variables[*s - 'A']);  }

}




void rpn(void) {
  int type;
  double op2;
  char s[BUFSIZ];

  while ((type = getop(s)) != EOF) {
    switch(type) {
      case '\n':      printf("\t%.8g\n", pop());  break;
      case NUMBER:    push(atof(s));              break;
      case VARIABLE:  variable(s);                break;
      case '+':       push(pop() + pop());        break;
      case '*':       push(pop() * pop());        break;
      case '-':       push(-(pop() - pop()));     break;

      //Exercise 4-4
      case '~':       printTop();                 break;
      case '!':       duplicate();                break;
      case '@':       swap();                     break;
      case '#':       clear();                    break;

      //Exercise 4-3
      case '%':
        op2 = pop();
        push(fmod(pop(), op2));
        break;

      // Exercise 4-5
      case '^':
        if ((op2 = pop()) < 0) {fprintf(stderr, "pow must be > 0\n");}
        push(pow(pop(),op2));
        break;
      case 's':
        push(sin(pop()));
        break;
      case 'e':
        push(exp(pop()));
        break;
      case '/':
        if ((op2 = pop()) == 0.0) { fprintf(stderr, "divide by zero\n");  break; }
        push(pop() / op2);
        break;
      default:      fprintf(stderr, "unknown command %s\n", s);  break;
    }
  }
}

int main(int argc, const char * argv[]) {
  rpn();

  return 0;
}
