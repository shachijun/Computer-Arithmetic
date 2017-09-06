//
//  format.h
//  format
//
//  Created by Chijun Sha on 2016/10/20.
//  Copyright © 2016年 Chijun Sha. All rights reserved.
//

#ifndef format_h
#define format_h

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

struct Arr{
    int a;
    struct Arr *next;
};
typedef struct Arr Array;
int printm(Array *b);
Array* ChangeSameSize(Array * number1, Array* number2);
int Findsize(Array * number1, Array* number2);
Array *Dec(Array * bin);
Array *Times(Array * number1, Array* number2,int base);
Array *Plus(Array * number1, Array* number2,int base);
Array *help(Array * number1,int num2,int base,int zero);
Array *ChangeCal(Array * bin, int num,int times);
Array *Calculation(Array * number1, Array* number2,char cal,char num1,char num2,int base);
Array* ChangeSign(Array * number,char sign);
Array *ChangeFromBinary(Array * bin);
Array *DecHelp(int sizeChange,Array *one,Array *two);
Array *ChangeToBinary(char *num,int length,int start);
void escape(char c);
char* FindNumber(const char* string, int loca,int length);

#endif /* format_h */
