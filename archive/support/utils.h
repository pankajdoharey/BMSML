#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "primitive.h"

Object *read(char* input);

char *type_of_token(Type t){
    char *type;

    switch( t ){
    case NIL:
        type = "NIL";
        break;
    case Integer:
        type = "Integer";
        break;
    case Fraction:
        type = "Fraction";
        break;
    case String:
        type = "String";
        break;
    case Boolean:
        type = "Boolean";
        break;
    case Symbol:
        type = "Symbol";
        break;
    case Cons:
        type = "Cons";
        break;
    }

    return type;
};

//Dynamic Character Array.
typedef struct {
    int size;
    int capacity;
    int signedness;
    int _expand_capacity;
    Type type;
    char *char_array;
}Array;

Array *create_array(Array *this, int capacity, Type type){
    this->size = 0;
    this->capacity = capacity;
    this->_expand_capacity = capacity;
    this->char_array = calloc(this->capacity, sizeof(char) );

    this->type = type;
    if(type == Integer) this->signedness = POSITIVE;

    return this;
}

void expand_array(Array *array){
    array->capacity = array->capacity + array->_expand_capacity;
    array->char_array = realloc(array->char_array, sizeof(char) * array->capacity);
}


void free_array(Array *array){
    free(array->char_array);
    array = NULL;
    assert(array == NULL);
}

Array *insert_into_array(Array *this, char elem){
    if(this->size >= this->capacity){ expand_array(this); }

    this->char_array[this->size] = elem;
    this->size++;
    return this;
}

Array *set_value_at_array(Array *arry, int *pos , char *val){
    arry->char_array[(int)pos] = (int)val;
    return arry;
}

void set_array_to_float(Array *arry){
    arry->type = Fraction;
}

long int array_to_int(Array *arry){
    long int number = 0;
    int sign = arry->signedness;
    for(int i=0; i <= (arry->size)-1; i++){
        number = (number * 10) + (arry->char_array[i] - '0');
    }

    free_array(arry);
    return sign * number;
}

double array_to_float(Array *arry){
    int sign = arry->signedness;
    //TODO: atof is Not accurate, precision is lost write your own.
    double fraction = atof(arry->char_array);
    free_array(arry);
    return (double)sign * fraction;
}

char *array_to_string(Array *arry){
    char *str = malloc(sizeof(char)*arry->size + 2);

    int i = 0;
    while(i <= arry->size-1){
        str[i] = arry->char_array[i];
        i++;
    }

    if(arry->type == String){
        str[arry->size] = '"';
        str[arry->size+1] = '\0';
    }

    free_array(arry);
    return str;
}
