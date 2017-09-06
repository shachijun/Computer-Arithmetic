//
//  CalForm.c
//  Assignment 2
//
//  Created by Chijun Sha on 2016/10/11.
//  Copyright © 2016年 Chijun Sha. All rights reserved.
//

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "calc.h"

int Findber(Array *b);
Array* ChangeSameSize(Array * number1, Array* number2);
int Findsize(Array * number1, Array* number2);
Array *Dec(Array * bin);
Array *Times(Array * number1, Array* number2,int base);
Array *Plus(Array * number1, Array* number2,int base);
Array *help(Array * number1,int num2,int base,int zero);
Array *ChangeCal(Array * bin, int num,int times);
Array *Calculation(Array * number1, Array* number2,char cal,char num1,char num2,int base);
Array* ChangeSign(Array * number,char sign);
Array *ChangeFromBinary(Array * bin,char type);
Array *FromCal(Array * bin,int bas);
Array *DecHelp(int sizeChange,Array *one,Array *two);
Array *ChangeToBinary(char type, char *num,int length);
int based(int times);
void escape(char c);
//void DestoryArry(Array * arr);
char* FindNumber(const char* string, int loca,int length);
int zero=0, power=0, size=0;
int main(int argc, const char * argv[]) {
    /*my main mathod*/
    char *number1 = NULL,*number2=NULL, sign = '\0',returnType = '\0',num1sign = '+',num2sign = '+',num1type = '\0',num2type = '\0';
    Array*Num1=NULL,*Num2=NULL;
    if ((argv[1][0]=='+')||(argv[1][0]=='-')||(argv[1][0]=='*')) {
        sign=argv[1][0];
    }else{
        int a=0;
        escape(argv[1][a]);
        return 0;
    }
    if (argv[2][0]=='-'){
        num1sign='-';
        if((argv[2][1]=='d')||(argv[2][1]=='b')||(argv[2][1]=='x')||(argv[2][1]=='o')){
            num1type=argv[2][1];
            int len=(int)strlen(argv[2])-1;
            number1=FindNumber(argv[2], 2,len);
            int length=(int)strlen(number1)-1;
            Num1=ChangeToBinary(num1type, number1,length);
            
        }else{
            int a=1;
            escape(argv[1][a]);
            return 0;
        }
    }else if((argv[2][0]=='d')||(argv[2][0]=='b')||(argv[2][0]=='x')||(argv[2][0]=='o')){
        num1type=argv[2][0];
        int len=(int)strlen(argv[2]);
        number1=FindNumber(argv[2], 1,len);
        int length=(int)strlen(number1)-1;
        Num1=ChangeToBinary(num1type, number1,length);
        
    }else{
        int a=0;
        escape(argv[2][a]);
    }
    
    if (argv[3][0]=='-'){
        num2sign='-';
        if((argv[3][1]=='d')||(argv[3][1]=='b')||(argv[3][1]=='x')||(argv[3][1]=='o')){
            num2type=argv[3][1];
            int len=(int)strlen(argv[3])-1;
            number2=FindNumber(argv[3], 2,len);
            int length=(int)strlen(number2)-1;
            Num2=ChangeToBinary(num2type, number2,length);
            
        }else{
            int a=1;
            escape(argv[3][a]);
            return 0;
        }
    }else if((argv[3][0]=='d')||(argv[3][0]=='b')||(argv[3][0]=='x')||(argv[3][0]=='o')){
        num2type=argv[3][0];
        int len=(int)strlen(argv[3]);
        number2=FindNumber(argv[3], 1,len);
        int length=(int)strlen(number2)-1;
        Num2=ChangeToBinary(num2type, number2,length);
    }else{
        int a=0;
        escape(argv[3][a]);
        return 0;
    }
    if ((argv[4][0]=='d')||(argv[4][0]=='x')||(argv[4][0]=='b')||(argv[4][0]=='o')) {
        returnType=argv[4][0];
    }else{
        int a=0;
        escape(argv[4][a]);
        return 0;
    }
    if ((Num1!=NULL)&&(Num2!=NULL)) {
        Array*Cal=Calculation(Num1, Num2, sign, num1sign, num2sign, 2);
        Array* Final=ChangeFromBinary(Cal, returnType);
        int a=Findber(Final),b=0;
        printf("%c: ",returnType);
        char final[a+1];
        char ret = '\0';
        do{
            if (returnType=='x'){
                if (Final!=NULL) {
                    if (Final->a==10) {
                        ret='A';
                    }else if (Final->a==11) {
                        ret='B';
                    }else if (Final->a==12) {
                        ret='C';
                    }else if (Final->a==13) {
                        ret='D';
                    }else if (Final->a==14) {
                        ret='E';
                    }else if (Final->a==15) {
                        ret='F';
                    }else{
                        ret=(Final->a)+'0';
                    }
                }
            }else{
                ret=(Final->a)+'0';
            }
            Final=Final->next;
            final[b]=ret;
            b++;
        }while (Final!=NULL);
        if (b==a) {
            final[b]='\0';
        }
        printf("%s\n",final);
    }else{
        printf("BAD INPUT\n");
    }
    return 0;
}

char* FindNumber(const char* string, int loca,int length){
    int i=0;
    char *Number = (char*) malloc(sizeof(char)*length);
    for (; i<length; i++) {
        if (i==(length-1)) {
            Number[i]='\0';
        }else{
            Number[i]=string[loca];
        }
        loca++;
    }
    return Number;
}
int Findber(Array *b){
    /*this method will print out everything*/
    int a=0;
    do{
        a++;
        b=b->next;
    }while (b!=NULL);
    return a;
}



Array *ChangeToBinary(char type, char *num,int length){
    /*this method is the method we need call at the beginning, it will return a binary Array pointer*/
    Array *bin=NULL;
    bool error=false;
    
    int number=0;
    if (num==NULL) {
        printf("No input has been found");
        error=true;
    }
    if (type=='o') {
        for ( ;length>=0; length--) {
            if ((num[length]>='0')&&(num[length]<='7')) {
                number=num[length]-'0';
                bin=ChangeCal(bin, number,3);
            }else{
                escape(num[length]);
                error=true;
            }
        }
    }else if (type=='x') {
        for ( ;length>=0; length--) {
            if ((num[length]>='0')&&(num[length]<='9')) {
                number=num[length]-'0';
            }else{
                if ((num[length]=='A')||(num[length]=='a')) {
                    number=10;
                }else if ((num[length]=='B')||(num[length]=='b')){
                    number=11;
                }else if ((num[length]=='C')||(num[length]=='c')){
                    number=12;
                }else if ((num[length]=='D')||(num[length]=='d')){
                    number=13;
                }else if ((num[length]=='E')||(num[length]=='e')){
                    number=14;
                }else if ((num[length]=='F')||(num[length]=='f')){
                    number=15;
                }else{
                    escape(num[length]);
                    error=true;
                }
            }
            bin=ChangeCal(bin, number,4);
        }
    }else  if (type=='b') {
        for ( ;length>=0; length--) {
            if ((num[length]=='0')||(num[length]=='1') ){
                number=num[length]-'0';
                bin=ChangeCal(bin, number,1);
            }else{
                escape(num[length]);
                error=true;
            }
        }
    }else  if (type=='d') {
        for ( ;length>=0; length--) {
            char a=num[length];
            if ((a>='0')&&(a<='9') ){
                Array *new=(Array *)malloc(sizeof(Array));//I will not free until I already finish used this one, this one is actually belongs to the linked list of binary;
                new->a=(a-'0');
                if (bin==NULL){
                    bin=new;
                    bin->next=NULL;
                }else{
                    new->next=bin;
                    bin=new;
                }
            }else{
                escape(a);
                error=true;
            }
        }
        if (!error) {
            Array* new=NULL;
            do{
                Array* ptr=bin;
                int i;
                do{
                    i=(ptr->a)%2;
                    if (i==1){
                        if((ptr->next)!=NULL) {
                            ptr->next->a+=10;
                            i=0;
                        }
                    }
                    ptr->a=(ptr->a)/2;
                    ptr=ptr->next;
                    
                }while (ptr!=NULL);
                new=ChangeCal(new, i, 1);
                if ((bin->a)==0) {
                    bin=bin->next;
                }
            }while (bin!=NULL);
            bin=new;
        }
    }else{
        printf("Wrong type");
        escape(type);
        error=true;
    }
    if (error) {
        return NULL;
    }
    return bin;
}

Array *ChangeCal(Array * bin, int num,int times){
    int i;
    do {
        Array *new=(Array *)malloc(sizeof(Array));//I will not free until I already finish used this one, this one is actually belongs to the linked list of binary;
        i=num%2;
        num=num/2;
        new->a=i;
        if (bin==NULL){
            bin=new;
            bin->next=NULL;
            size=0;
        }else{
            new->next=bin;
            bin=new;
        }
        size++;
        times--;
    }while (times!=0);
    return bin;
}
void escape(char c){
    char a;
    a = toascii(c);
    printf("%c is an error: [%#2x]\n",c,a);
    return;
}










Array *ChangeFromBinary(Array * bin,char type){
    /*this method is a main method that will help us find the number interms of what we want
     *consider if the first num is 1, the number will be negative, and we need to find the first node and move to
     *next node and make a new node suit for the type of the return type.In this case it will does not matter if
     *the input type is octal and outout type is a hex, and this will not include the binary*/
    Array * new=NULL;
    if (bin->next!=NULL) {
        new=bin;
        bin=bin->next;
    }
    Array*sig=(Array *)malloc(sizeof(Array));
    Array *num=NULL;
    if (type=='b') {
        power=0;
        num=FromCal(bin, 1);
        if (new->a==1) {
            sig->a=1;
        }else{
            sig->a=0;
        }
        sig->next=num;
        num=sig;
    }else if (type=='o'){
        power=0;
        num=FromCal(bin, 3);
        if (new->a==1) {
            sig->a=8;//because if it is negative, it will be 111 so when it flip back it will be 000
        }else{
            sig->a=0;
        }
        sig->next=num;
        num=sig;
    }else if (type=='x'){
        power=0;
        num=FromCal(bin, 4);
        if (new->a==1) {
            sig->a=15;//because if it is negative, it will be 1111 so when it flip back it will be 0000
        }else{
            sig->a=0;
        }
        sig->next=num;
        num=sig;
    }else if (type=='d'){//does not matter
        power=0;
        int sign=1;
        if (new!=NULL) {
            if (new->a==1) {
                ChangeSign(new, '-');
                sign=-1;
            }
        }
        num=Dec(bin);
        while ((num->a==0)&&(num->next!=NULL)) {
            num=num->next;
        }
        num->a*=sign;
    }
    return num;
}

Array *FromCal(Array * bin,int bas){
    /*this method will return a Array pointer which is already been calculated for binary octal and hex, just
     *left the dec*/
    Array *new=NULL;
    if (bas==1) {// will just return the number dont need to waste time for compile others
        return bin;
    }
    if (bin==NULL) {
        return new;
    }
    Array*ptr=FromCal(bin->next, bas);//find the right most node
    if (power==0) {//if it is the right most
        new=(Array *)malloc(sizeof(Array));
        if (bin->a==1) {
            int n=based(power);
            new->a=n;
        }else{
            new->a=0;
        }
    }else  if (bin->a==1) {
        int n=based(power);
        ptr->a+=n;
    }
    power++;
    if (new!=NULL) {
        new->next=ptr;
    }else{
        new=ptr;
    }
    if (power>=bas) {// should not exceed
        power=0;
    }
    return new;
}

int based(int times){
    //this method will just for oct and hex, will not conder if it bigger than int size
    int num=1;
    while (times>0) {
        num*=2;
        times--;
    }
    return num;
}



Array *Dec(Array * bin){
    /*this method will help us get a number (Array type) in dec type*/
    Array *one=(Array *)malloc(sizeof(Array));
    one->a=1;
    Array *two=(Array *)malloc(sizeof(Array));
    two->a=2;
    if (bin->next==NULL) {
        if (bin->a==0) {
            one->a=0;
        }
        power++;
        return one;
    }
    Array *before=Dec(bin->next);
    if (bin->a==1) {
        Array *this=DecHelp(power,one,two);
        
        before=Calculation(before, this, '+','+','+', 10);
    }
    power++;
    return before;
}
Array *DecHelp(int sizeChange,Array *one,Array *two){//2's power stand for
    if (sizeChange==0) {
        return one;
    }
    Array*new=DecHelp(sizeChange-1,one,two);
    Array*now=Calculation(two,new,'*','+','+' , 10);
    return now;
}












Array *Calculation(Array * number1, Array* number2,char cal,char num1,char num2,int base){
    /*this metho is my main method, which will contain both plus and time minus is actually
     *(number)+(negative number)*/
    Array * number=NULL;
    number2=ChangeSameSize(number2, number1);
    number1=ChangeSameSize(number1, number2);
    
    if (cal=='*') {
        zero=0;//innitialize the zero for every time I want to times
        number=Times(number1, number2, base);
        /*now consider the number is end by using plus method which will be undecide for the left most number if it is
         *not smaller than the base, so have to do the consideration of the left most node is not smaller than the base
         *now consider the 0 will just be 0*0, so it will not matter for this time*/
        while ((number->a)>=base){
            int carry=0;
            while ((number->a)>=base) {
                ((number->a))-=base;
                carry++;
            }
            Array * new=(Array *)malloc(sizeof(Array));
            new->a=carry;
            new->next=number;
            number=new;
        }
        /*then consider if the number is possitive or negative*/
        if (((num1=='+')&&(num2=='+'))||((num1=='-')&&(num2=='-'))) {
            number=ChangeSign(number,'+');
        }else {
            number=ChangeSign(number,'-' );
        }
    }else {//good!
        number1=ChangeSign(number1, num1);
        if (cal=='-'){
            if (num2=='+') {
                num2='-';
                number2=ChangeSign(number2, num2);
            }else{
                num2='+';
                number2=ChangeSign(number2, num2);
            }
        }else{
            number2=ChangeSign(number2, num2);
        }//good!
        int numsign1=number1->a;
        int numsign2=number2->a;
        //        int sum=0;
        number=Plus(number1, number2, base);
        // now number 1 and number 2 will have the same size
        //this time will not consider the sign, just the number, that's it
        /* now consider the number left most node might have the number that bigger than 1 so I will consider
         *if it is like 1-1, if it like 1-1, the carry is not zero, the number will be 0, elso I will add a node for left
         *most to make the carry 0, because consider 1= 000......1 and -1=111...1, right now I add them together,
         *it will be .....000.....0 and it will goes to infinity when carry is always 1;
         * and the carry will not bigger than 2 for the next node for example 11...1+11.....1 will equal to 111...0*/
                bool sign=true;
        if ((number->a)>=base) {
            if (((numsign1==1)&&(numsign2==0))||((numsign2==1)&&(numsign1==0))) {//just for binary
                while ((number->a)>base){
                    int carry=1;
                    while ((number->a)>base) {
                        ((number->a))-=base;
                        carry++;
                    }
                    Array * new=(Array *)malloc(sizeof(Array));
                    new->a=carry;
                    new->next=number;
                    number=new;
                }
                
                Array * new=(Array *)malloc(sizeof(Array));
                if ((number->a)==base){
                    number->a=0;
                    new->a=0;
                }else{
                    new->a=1;
                }
                new->next=number;
                                sign=false;
            }else{
                while ((number->a)>=base){
                    int carry=0;
                    while ((number->a)>=base) {
                        ((number->a))-=base;
                        carry++;
                    }
                    Array * new=(Array *)malloc(sizeof(Array));
                    new->a=carry;
                    new->next=number;
                    number=new;
                }
            }
        }
                if (!sign) {//singn will just own one digit
                int carry=0;
                    if ((number->a)>=base) {
                        ((number->a))-=base;
                        carry=1;
                    }
                    number->a=carry;
                }else{
                    Array * new=(Array *)malloc(sizeof(Array));
                    new->a=0;
                    new->next=number;
                    number=new;
                }
    
    }
    return number;
}



Array *Times(Array * number1, Array* number2,int base){
    /* this method is for when to number is times and right now, I will not consider the sign, after I finished the
     *calculate I will consider the sign in the caculation method because consier 101*101 will equal to 11001
     *and consider that 101 is a negative number, I will still get a negative number when I square them, so I will
     *consider the sign after this
     **For this method, I am thinking that if I can find the number2 right most and go to left most and after I find the number I will be able to find the times */
    /*?? think about the number that is not left most, what should I do? For example, if number is 10's number, the final answer will addd A zero to the end, and last calculation will or will not add the other zero to the left most(origional numer), so I think I will need the Same size method to comupte for the original number and just simply add zero[s] to the now's number
     first think about the add the zero to the right now's first
     */
    if (number2==NULL) {
        // now zero will equal to 0 but dont forgot I should say equal to 0 everytime before I use( in the calculation method)
        return NULL;
    }
    Array * number=NULL,*numm1=NULL;
    number=Times( number1,  number2->next, base);// find the right most node
    int num2;
    num2=number2->a;
    if (num2>0) {
        numm1=help(number1, num2, base,zero);
        //will return a number that times of a number and a Array with right have zeros
        //then make them have the same size, because in this method, I will not consider the sign so it does not matte
        if (number==NULL) {
            number=numm1;
        }else{
            numm1=ChangeSameSize(numm1, number);
            number=ChangeSameSize(number,numm1);
            //then plus the old and new array with the array have the same size
            number=Plus(number, numm1, base);
        }
    }
    zero++;
    return number;
}
Array *help(Array * number1,int num2,int base,int zero){
    /* this method is a help method that will return a number(array*) that times the single number*/
    if (number1==NULL) {// find how may zero should add to the end(right most)
        if (zero!=0) {
            int zer=0;
            while (zer<zero) {
                zer++;
                Array * new=(Array *)malloc(sizeof(Array));
                new->a=0;
                new->next=number1;
                number1=new;
            }
            return number1;
        }else{
            return NULL;
        }
    }
    Array * number= help(number1->next, num2, base,zero);// find the right most for number 1
    Array * new=(Array *)malloc(sizeof(Array));
    int carry=0;
    if (number!=NULL) {// consider the first situation
        while (number->a>=base) {
            carry++;
            (number->a)-=base;
        }
    }
    (new->a)=(number1->a)*num2+carry;
    new->next=number;
    number=new;
    return number;
}


Array * ChangeSameSize(Array * number1, Array* number2){
    /*this method will return a Array pointer which will be have the same size with number 1 if and
     *only if when number1's size is bigger than number 2*/
    int num2=Findsize(number1,number2);//number 2 bigger when !=0
    Array* ptr=NULL,* new=NULL;;
    if (num2>0) {
        ptr=number1;
        for (; num2>0; num2--) {
            new=(Array *)malloc(sizeof(Array));
            new->a=0;
            new->next=ptr;
            ptr=new;
        }
        return ptr;
    }else{
        return number1;
    }
}

int Findsize(Array * number1, Array* number2){
    /*find if number 2 bigger than number 1 see how much bigger*/
    if (number2->next==NULL) {
        return 0;
    }
    if (number1->next==NULL) {
        return  Findsize(number1, number2->next)+1;
    }
    return Findsize(number1->next, number2->next);
}


Array *Plus(Array * number1, Array* number2,int base){
    //this base will be undecided
    /*consider now number 1 and number 2 have the same size
     *also, since I already change the sign and the size and the sign, so minus will also calculate by this method
     * and considering I will use recursal that will return the number node for the next node so it will consider that
     *if the number is bigger than the base, so it will have the carry, and the carry will add to right now's
     *node(number)*/
    if (number1==NULL) {
        /* because right now, they have the same size, so no need consider others when number1=NULL
         *number2 =NULL*/
        return NULL;
    }
    Array * number= Plus(number1->next, number2->next, base);
    Array * new=(Array *)malloc(sizeof(Array));
    int carry=0;
    if (number!=NULL) {
        while (number->a>=base) {
            carry++;
            (number->a)-=base;
        }
    }
    (new->a)=(number1->a)+(number2->a)+carry;
    new->next=number;
    number=new;
    return number;
    /* this one will have the same size as number1 and number2, but have to consider if the left most node is
     *exceed or equal the base it will not be two base*/
}







int ChangeSignHelper(Array * number){//great! flip change a bit!!!!!
    /*this method is a helper method that will help to change from 0 to 1 or from 1 to 0
     * considering this function, the changesign function will only for changing the binary's sign, so I will say
     *that the base will always be 0*/
    int carry=0;
    if (number==NULL) {
        return 1;//for the right most +1
    }
    if (number->a==0) {
        number->a=1;
    }else if (number->a==1){
        number->a=0;
    }
    carry=ChangeSignHelper( number->next);
    number->a+=carry;
    carry=0;//have to set it back
    while (number->a>=2) {
        carry++;
        number->a-=2;
    }
    return carry;
}//great!
Array* ChangeSign(Array * number,char S){
    number=ChangeCal(number, 0,1);//add a sign number, and also change number's size
    if (S=='-') {
        ChangeSignHelper(number);
        /*it will change the number inside, but will not change the form, also considering it will not exceed the left
         *most number node if it exceed, in the other word when carry !=0, return 0 because it will be 0, becasue
         *when the number is not zero, there must be some where that number is 1 and when you flip, the number will
         *be 0 and it will not carry*/
    }else{
        return number;
    }
    return number;
}
