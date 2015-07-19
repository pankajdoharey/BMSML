#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define POSITIVE 1
#define NEGATIVE -1

//Defining Token types in lisp
typedef enum { NIL, Integer, Fraction, String, Boolean, Symbol, Cons } Type;

typedef union Atom {
    struct { long int val; } integer;
    struct { double val; } fraction;
    struct { bool val; } boolean;
    struct { char *val; } string;
    struct { char *val; } symbol;
    struct { int *val; } nil;
} Atom;


typedef struct ConsCell {
    struct Object *car;
    struct Object *cdr;
} Cell;


typedef struct Object{
    int line_number;
    int char_at;
    Type type;
    union { Atom atom; Cell cell; } Data;
} Object;


Object *createObject(void){
    Object *this = malloc(sizeof(Object));
    assert(this != NULL);
    return this;
}

Object *nullObject(void){
    Object *this = createObject();
    this->type = NIL;
    this->Data.atom.nil.val = NULL;
    return this;
}

Object *createInteger(long int numb) {
    Object *this = createObject();
    this->type = Integer;
    this->Data.atom.integer.val = numb;
    return this;
};

Object *createFraction(double frac) {
    Object *this = createObject();
    this->type = Fraction;
    this->Data.atom.fraction.val = frac;
    return this;
};


Cell *createList(Object *first, Object *rest){
    Cell *this = malloc(sizeof(Cell));
    return this;
}