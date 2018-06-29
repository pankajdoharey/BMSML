#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define POSITIVE 1
#define NEGATIVE -1

//Defining Token types in lisp
typedef enum { NIL, Integer, Fraction, String, Boolean, Symbol, Cons } Type;

typedef struct Object{
    int line_number;
    int char_at;
    Type type;
    union {
        long int integer;
        double fraction;
        bool boolean;
        char *string;
        char *symbol;
        int *nil;
        struct {
            struct Object *car;
            struct Object *cdr;
        } Cell;
    } Val;
} Object;

/* CAR , CDR, RPLACA, RPLACD */
#define CAR(O) O->Val.Cell.car
#define CDR(O) O->Val.Cell.cdr
//http://www.lispworks.com/documentation/HyperSpec/Body/f_rplaca.htm
#define RPLACA(O, A) CAR(O) = A //replace CAR
#define RPLACD(O, D) CDR(O) = D //replace CDR

Object *createObject(void){
    Object *this = malloc(sizeof(Object));
    assert(this != NULL);
    return this;
}

//Creates Empty Cell is a Object with car-cdr initialized.
Object *nullObject(void){
    Object *this = createObject();
    this->type = NIL;
    this->Val.Cell.car = malloc(sizeof(Object));
    this->Val.Cell.cdr = malloc(sizeof(Object));
    this->Val.Cell.car->type = NIL;
    this->Val.Cell.cdr->type = NIL;
    this->Val.Cell.car->Val.nil = NULL;
    this->Val.Cell.cdr->Val.nil = NULL;

    return this;
}

Object *createNIL(void){
    Object *this = createObject();
    this->type = NIL;
    this->Val.nil = NULL;
    return this;
}

//Empty Cell
Object *createCell(void) {
    Object *this = nullObject();
    this->type = Cons;
    return this;
};

//Creates an empty list which containing a null pointing cell.
Object *createInteger(long int numb) {
    Object *this = createObject();
    this->type = Integer;
    this->Val.integer = numb;
    return this;
};

Object *createFraction(double frac) {
    Object *this = createObject();
    this->type = Fraction;
    this->Val.fraction = frac;
    return this;
};

Object *boolObject(bool val){
    Object *this = createObject();
    this->type = Boolean;
    this->Val.boolean = val;
    return this;
}

Object *createString(char *str){
    Object *this = createCell();
    this->type = String;
    this->Val.string = str;
    return this;
}

Object *createSymbol(char *sym){
    Object *this = createCell();
    this->type = Symbol;
    this->Val.symbol = sym;
    return this;
}

Object *createQuote(void){
    Object *this = createSymbol("quote");
    return this;
}
