#include <stdbool.h>
#include <ctype.h>
#include "utils.h"

int paren_open = 0;
char *tok;

//Cons
Object *cons(Object *car, Object *cdr){
    Object *obj = createCell();
    RPLACA(obj, car); RPLACD(obj, cdr);
    return obj;
}


Object *make_number(char *ch){
    Array a;
    Array *Arry = create_array(&a, 5, Integer);

    //Check if the char is '-', then set signedness Negative.
    //And move the pointer to the number.
    if( *ch == '-'){
        Arry->signedness = NEGATIVE;
        tok = ++ch;
    };

    do{
        insert_into_array(Arry, *ch);
        tok = ++ch;

        if(*ch == '.'){
            set_array_to_float(Arry);
            insert_into_array(Arry, *ch);
            tok = ++ch;
        }

    }while(isdigit(*ch));

    if(Arry->type == Integer)
        return createInteger(array_to_int(Arry));
    else
        return createFraction(array_to_float(Arry));
}


Object *make_string(char *ch){
    Array a;
    Array *Arry = create_array(&a, 5, String);

    do{
        insert_into_array(Arry, *ch);
        ++ch;
    }while(*ch != '"');

    tok = ++ch;

    return createString(array_to_string(Arry));
}


Object *make_boolean(char *ch){
    //If the char starts with a #, then it is a boolean
    //Create a true or false object. These are singletons or Atomss.
    tok = ++ch;
    switch(*ch){
    case 't': return boolObject(true); break;
    case 'f': return boolObject(false); break;
    default:
        puts("God Knows if it is a Boolean");
        exit(1);
    }
}


Object *make_symbol(char *ch){
    Array a;
    Array *Arry = create_array(&a, 5, Symbol);

    //Skip '('.
    tok = ++ch;

    while(*ch != ')'){
        insert_into_array(Arry, *ch);
        tok = ++ch;
    }

    return createSymbol(array_to_string(Arry));
}


Object *make_list(char *ch){
    if(*ch == '('){ ++ch; tok = ch;}

    while(*ch == ' '){
        tok = ++ch;
    }

    if(*ch == ')') return nullObject();

    Object *car = parse(ch);

    while(*ch == ' '){
        tok = ++ch;
    }

    Object *cdr = make_list(tok);

    return cons(car, cdr);
}


//Generates AST.
Object *parse(char* ch){
    tok = ch;

    while(*ch == ' '){
        tok = ++ch;
    }

    //Return NIL if ')' or EOF is encountered.
    if(*ch == ')' || *ch == '\0') return nullObject();

    if( isdigit(*ch)){
        return make_number(ch);
    }else if( *ch  == '#' ){
        return make_boolean(ch);
    }else if(*ch == '"'){
        return make_string(ch);
    }else if(*ch == '('){
        return make_list(ch);
    }else{
        return parse(++ch);
    }
}


//Evaluation Code.
Object *eval(Object *exprn){
    printf("\nExpression Type : %s\n", type_of_token(exprn->type));
    if(exprn->type == Cons){
        if(CAR(exprn)->type == NIL && CDR(exprn)->type == NIL)
            return nullObject();
    }

    return exprn;
}

void print(Object *result){
    switch(result->type){

    case Integer  : printf("Int is %ld\n", result->Val.integer); break;
    case Fraction : printf("Fraction is %lf\n", result->Val.fraction); break;
    case Boolean  : result->Val.boolean ? puts("#t") : puts("#f"); break;
    case NIL      : puts("\nnil"); break;
    case String   : puts(result->Val.string); break;
    case Cons     :
        print(CAR(result));
        print(CDR(result));
        break;
    default       : puts("\n"); break;
    }

}
