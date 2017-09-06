//
//  calc.h
//  Assignment 2
//
//  Created by Chijun Sha on 2016/10/20.
//  Copyright © 2016年 Chijun Sha. All rights reserved.
//

#ifndef calc_h
#define calc_h

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "calc.h"
struct Arr{
    int a;
    struct Arr *next;
};
typedef struct Arr Array;
int main(int argc, const char * argv[]) ;
/*my main mathod*/
int Findber(Array *b);
/*this method will findthe size of the array*/
Array *ChangeToBinary(char type, char *num,int length);
/*this method is the method we need call at the beginning, it will return a binary Array pointer*/
Array *ChangeFromBinary(Array * bin,char type);
/*this method is a main method that will help us find the number interms of what we want
 *consider if the first num is 1, the number will be negative, and we need to find the first node and move to
 *next node and make a new node suit for the type of the return type.In this case it will does not matter if
 *the input type is octal and outout type is a hex, and this will not include the binary*/
Array *FromCal(Array * bin,int bas);
/*this method will return a Array pointer which is already been calculated for binary octal and hex, just
 *left the dec*/
Array *Dec(Array * bin);
/*this method will help us get a number (Array type) in dec type*/
Array *Calculation(Array * number1, Array* number2,char cal,char num1,char num2,int base);
/*this metho is my main method, which will contain both plus and time minus is actually
 *(number)+(negative number)*/
Array *Times(Array * number1, Array* number2,int base);
/* this method is for when to number is times and right now, I will not consider the sign, after I finished the
 *calculate I will consider the sign in the caculation method because consier 101*101 will equal to 11001
 *and consider that 101 is a negative number, I will still get a negative number when I square them, so I will
 *consider the sign after this
 **For this method, I am thinking that if I can find the number2 right most and go to left most and after I find the number I will be able to find the times */
/*?? think about the number that is not left most, what should I do? For example, if number is 10's number, the final answer will addd A zero to the end, and last calculation will or will not add the other zero to the left most(origional numer), so I think I will need the Same size method to comupte for the original number and just simply add zero[s] to the now's number
 first think about the add the zero to the right now's first
 */
Array *help(Array * number1,int num2,int base,int zero);
/* this method is a help method that will return a number(array*) that times the single number*/
Array * ChangeSameSize(Array * number1, Array* number2);
/*this method will return a Array pointer which will be have the same size with number 1 if and
 *only if when number1's size is bigger than number 2*/
int Findsize(Array * number1, Array* number2);
/*find if number 2 bigger than number 1 see how much bigger*/
Array *Plus(Array * number1, Array* number2,int base);
//this base will be undecided
/*consider now number 1 and number 2 have the same size
 *also, since I already change the sign and the size and the sign, so minus will also calculate by this method
 * and considering I will use recursal that will return the number node for the next node so it will consider that
 *if the number is bigger than the base, so it will have the carry, and the carry will add to right now's
 *node(number)*/
// now number 1 and number 2 will have the same size
//this time will not consider the sign, just the number, that's it
/* now consider the number left most node might have the number that bigger than 1 so I will consider
 *if it is like 1-1, if it like 1-1, the carry is not zero, the number will be 0, elso I will add a node for left
 *most to make the carry 0, because consider 1= 000......1 and -1=111...1, right now I add them together,
 *it will be .....000.....0 and it will goes to infinity when carry is always 1;
 * and the carry will not bigger than 2 for the next node for example 11...1+11.....1 will equal to 111...0*/
int ChangeSignHelper(Array * number);//great! flip change a bit!!!!!
/*this method is a helper method that will help to change from 0 to 1 or from 1 to 0
 * considering this function, the changesign function will only for changing the binary's sign, so I will say
 *that the base will always be 0*/
/*it will change the number inside, but will not change the form, also considering it will not exceed the left
 *most number node if it exceed, in the other word when carry !=0, return 0 because it will be 0, becasue
 *when the number is not zero, there must be some where that number is 1 and when you flip, the number will
 *be 0 and it will not carry*/

#endif /* calc_h */
