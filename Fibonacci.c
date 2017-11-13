/* ************************************************************************** */
/*                                                                            */
/*                                                            |\              */
/*   Fibonacci.c                                        ------| \----         */
/*                                                      |    \`  \  |  p      */
/*   By: cshepard6055 <cshepard6055@floridapoly.edu>    |  \`-\   \ |  o      */
/*                                                      |---\  \   `|  l      */
/*   Created: 2017/11/12 19:53:30 by cshepard6055       | ` .\  \   |  y      */
/*   Updated: 2017/11/13 14:03:32 by cshepard6055       -------------         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Fibonacci.h"

unsigned int *toUnsignedInt(HugeInteger *p);
void huge_print(struct HugeInteger *num);
void ic_print(int n);
char *huge_int_to_str(int *intra);
int num_length(struct HugeInteger *a, struct HugeInteger *b);
int lesser_length(struct HugeInteger *a, struct HugeInteger *b);
int *str_to_int(char *str);
int *str_to_int(char *str);

HugeInteger *hugeDestroyer(HugeInteger *p);
HugeInteger *parseString(char *str);
HugeInteger *hugeAdd(struct HugeInteger *a, struct HugeInteger *b);
HugeInteger *fib(int n);

void ic_print(int n){
    if(n > 9 || n < 0)
        printf("Number range error, cs_print\n");
    n += 48;
    write(1, &n, 1);
}

HugeInteger *parseString(char *str){
    HugeInteger *hugo = (HugeInteger *) malloc( sizeof(HugeInteger) );
    hugo->digits = str_to_int(str);
    hugo->length = strlen(str);

    return hugo;
}

HugeInteger *parseInt(unsigned int n){
    unsigned int length = log10(n);
    HugeInteger *hugo = (HugeInteger *) malloc( sizeof(HugeInteger) );
    int *digits = calloc(n, sizeof(int));

    while(n){
        *digits = n % 10;
        n /= 10;
        digits++;
    }

    hugo->digits = digits;
    hugo->length = length;

    return hugo;
}

HugeInteger *hugeDestroyer(HugeInteger *p){
    p->digits=0;
    p->length=0;
    free(p);

    return 0;
}

char *huge_int_to_str(int *intra){

    char *str;

    int i;
    i = (int)( sizeof(intra) / sizeof(intra[0]) );
    // +1 for null terminator
    str = (char*) malloc((i)*sizeof(char)+1);

    // add null terminator
    str[i] = 0;
    // decrement into the contents
    i--;

    int j;
    j = 0;
    while(i > -1){
        str[j] = str[i] - 48;
        j++;
        i--;
    }

    return str;
}

int *str_to_int(char *str){

    int *list;

    int i;
    i = strlen(str);
    list = (int*) malloc((i)*sizeof(int));

    // start at end of string
    i--;
    int j;
    j = 0;
    while(i > -1){
        list[j] = str[i] - 48;
        j++;
        i--;
    }

    return list;
}

unsigned int *toUnsignedInt(HugeInteger *p){
    if(!p)
        return 0;

    int i;
    unsigned int returnMe;

    i = p->length - 1;
    while(i < p->length){
        if(returnMe > 294967295)
            if(p->digits[i] >= 4)
                return 0;

        if(returnMe == 294967295)
            if(p->digits[i] > 4)
                return 0;

        returnMe += pow(10, i) * p->digits[i];
        i++;
    }

    unsigned int *r = (unsigned int*) malloc(sizeof(unsigned int));
    *r = returnMe;

    return r;
}

int num_length(struct HugeInteger *a, struct HugeInteger *b){
    int length;
    if(a->length > b->length)
        length = a->length;
    else
        length = b->length;
    // account for 9999+1
    length++;
    return length;
}

int lesser_length(struct HugeInteger *a, struct HugeInteger *b){
    int length;
    if(a->length > b->length)
        length = b->length;
    else
        length = a->length;
    return length;
}

void huge_print(struct HugeInteger *num){
    int i;

    i = num->length - 1;
    while(i > -1){
        ic_print(num->digits[i]);
        i--;
    }
    printf("\n");
}

// return a version of *digits
HugeInteger *hugeAdd(struct HugeInteger *a, struct HugeInteger *b){

    if(!a || !b)
        return 0;

    if(!a->digits || !b->digits)
        return 0;

    int length;
    length = num_length(a, b);

    int less_length;
    less_length = lesser_length(a, b);

    int *sum = (int *) malloc( length * sizeof(int) );

    if(!sum)
        return 0;

    int overflow;
    overflow = 0;

    int i;
    i = 0;

    while(i < length){
        if(i < less_length){
            // add in overflow, if any
            sum[i] = a->digits[i] + b->digits[i] + overflow;
            // set overflow
            overflow = sum[i] / 10;
            if(overflow != 0)
                overflow = 1;
            // take off the overflow from the single digit placeholder
            sum[i] = sum[i] % 10;
            // increment through higher powers
        }

        else{
            if(a->length > b->length)
                sum[i] = a->digits[i] + overflow;
            else
                sum[i] = b->digits[i] + overflow;
            // set overflow
            overflow = sum[i] / 10;
            if(overflow != 0)
                overflow = 1;
            // take off the overflow from the single digit placeholder
            sum[i] = sum[i] % 10;
        }

        i++;
    }

    if(overflow > 0)
        printf("INTEGER OVERFLOW ERROR %d\n", overflow);

    sum[i] = overflow;

    HugeInteger *hugo = (HugeInteger *) malloc( sizeof(HugeInteger) );
    hugo->digits = sum;
    hugo->length = length;

    return hugo;
}

HugeInteger *fib(int n){
    HugeInteger *sum = (HugeInteger *) malloc( sizeof(HugeInteger) );

    struct HugeInteger *fibs[n+1];
    fibs[0] = parseString("0");
    fibs[1] = parseString("1");

    int i;
    i = 2;
    while(i <= n){
        fibs[i] = hugeAdd(fibs[i - 1], fibs[i - 2]);
        i++;
    }

    sum->digits = fibs[n]->digits;
    sum->length = fibs[n]->length;

    return sum;
}
