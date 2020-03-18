//Albert Paez
//CPSC 223C
//Midterm Coding Question
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


//(1)
void count() {
    printf("Enter lines of text here: .../n");
    int c, nc = 0, nl = 0, nt = 0, nbackslash = 0;
    while ((c = getchar()) != EOF) {
    if (c == '\n') { ++nl;
    } else if (c == '\t') { ++nt;
    } else if (c == '\\') { nbackslash += 1;
    } else if (isspace(c)) { ++nc; }
    printf("lines: %d\n", nl);
    printf("tabs: %d\n", nt);
    printf("backslashes: %d\n", nbackslash);
    printf("alphanumeric: %d\n", nc);
    }
}

/// The C Standard Library: Identify the standard library functions that do the following…

//2) Find the first character c in a const char *s :                                                char *strchr (const char *s, char c);
//3) Find the length of the prefix of const char *s that has the characters in const char *t:       size_t strspn(const char *s, const char *t);
//4) Terminate a program immediately:                                                               exit(1);
//5) Open the file “midterm.txt” in read mode:                                                      FILE *fin = fopen("midterm.txt", "r"); 

//(6)
char *strcpy_(char *s, const char *t){
    char *p = s;
    while ((*s++ = *t++) != '\0'){}
    return p;
}

//(7)
char *strncat_(char *s, const char *t, size_t n){
  while ((*s != '\0'))      {++s        ;}
  while (n-- > 0 && *t != 0){*s++ = *t++;}
  *s = '\0';
  return s;
}

//(8)
int strcmp_(const char *s, const char *t){
    while ((*s == *t) && (*s != '\0') && (*t != '\0')) {
        ++s;
        ++t;
    }
    return *s - *t;
}

// (9)

typedef struct point point;
struct point { double x, y; };
//------ SQUARE -----------------------------------------------------------------
typedef struct square square;

struct square { point ul; size_t side; };

square* square_init(double ulx, double uly, double side){
    square *pt = (square*)malloc(sizeof(square));
    pt->ul.x = ulx;
    pt->ul.y = uly;
    pt->side = side;
    return pt;
} // TODO

void square_delete(square* sq){
    free(sq);
} // TODO

void square_move(square* sq, double x, double y){
    sq->ul.x += x;
    sq->ul.y += y;
    

} // TODO

void square_expandby(square* sq, double expandby){
    sq->ul.x += expandby;
    sq->ul.y += expandby;
    sq->side += expandby;

} // TODO
double square_area(square* sq){
    return sq->ul.x * sq->side;

} // TODO

double square_perimeter(square* r){ 
    return 2* (r->ul.x+ r->side);
} // TODO

// print location, side, area and perimeter
void square_print(const char* msg, square* sq){
    printf("%s\n" , msg);
    printf("\tSide: %zu\n\tul: %.1lf\n" , sq->side, sq->ul.x);
    printf("\tArea: %.1lf\n\tPerimeter: %.1lf\n", square_area(sq), square_perimeter(sq));
} // TODO

void test_square(double ulx, double uly, double side) {
    square* sq = square_init(ulx, uly, side);
    square_print("sq is: ", sq);
    square_move(sq, 2, 2);
    square_print("sq is now: ", sq);
    square_expandby(sq, 10);
    square_print("sq has expanded to: ", sq);
    square_delete(sq);
    printf("\n\n");
}
void tests_square() {
 test_square(0, 0, 10);
 test_square(1, 1, 5);
 // add other tests if you wish // TODO (optional)
}



int main(int argc, const char* argv[]) {
 tests_square();
 count();
 return 0;
} 


