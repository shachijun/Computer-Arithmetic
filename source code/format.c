
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
#include <stdio.h>
#include <string.h>
#include "format.h"

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
double powerNum(double num,int p);
int zero=0, power=0, size=0;
int printm(Array *b){
    /*this method will print out everything*/
    int a=0;
    do{
        a++;
        b=b->next;
    }while (b!=NULL);
    return a;
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










Array *ChangeFromBinary(Array * bin){
    /*this method is a main method that will help us find the number interms of what we want
     *consider if the first num is 1, the number will be negative, and we need to find the first node and move to
     *next node and make a new node suit for the type of the return type.In this case it will does not matter if
     *the input type is octal and outout type is a hex, and this will not include the binary*/
    Array * new=NULL;
    if (bin->next!=NULL) {
        new=bin;
        bin=bin->next;
    }
    Array *num=NULL;
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
        int sum=0;
        number=Plus(number1->next, number2->next, base);
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
        if (sign) {//singn will just own one digit
            sum=numsign1+numsign2;
            Array * new=(Array *)malloc(sizeof(Array));
            new->a=sum;
            new->next=number;
            number=new;
        }
        int carry=0;
        if ((number->a)>=base) {
            ((number->a))-=base;
            carry=1;
        }
        number->a=carry;
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
    int carry;
    number=ChangeCal(number, 0,1);//add a sign number, and also change number's size
    if (S=='-') {
        carry=ChangeSignHelper(number);
        /*it will change the number inside, but will not change the form, also considering it will not exceed the left
         *most number node if it exceed, in the other word when carry !=0, return 0 because it will be 0, becasue
         *when the number is not zero, there must be some where that number is 1 and when you flip, the number will
         *be 0 and it will not carry*/
    }else{
        return number;
    }
    if (carry!=0) {
        Array *sign=NULL;
        while (number->next!=NULL) {
            Array* new=(Array *)malloc(sizeof(Array));// when it is 0
            new->a=0;
            new->next=NULL;// if it is zero, have to change the size, so I will make a loop for this
            if (sign!=NULL) {
                sign->next=new;
            }else{
                sign=new;
            }
            return sign;
        }
    }
    return number;
}





//Checks to make the bit string is 32 bits
int isBinary(char* ptr) {
    if (*ptr=='\0') {
        return 0;
    }
    if ((*ptr != '0')&&(*ptr != '1')){
        escape(*ptr);
        return 1;
    }
    ptr++;
    return isBinary(ptr);
}

Array *ChangeToBinary(char *num,int length,int start){
    /*this method is the method we need call at the beginning, it will return a binary Array pointer*/
    Array *bin=NULL;
    int number=0;
    for ( ;length>0; length--) {
        int sum=start+length-1;
        number=num[sum]-'0';
        bin=ChangeCal(bin, number,1);
    }
    
    return bin;
}





double powerNum(double num,int p){
    //this method will just for oct and hex, will not conder if it bigger than int size
    if (p==0) {
        return 1;
    }
    double base=powerNum(num, p-1);
    
    return num*base;
}
double helpFindDouble(char* a){
    int length=0,pow=1,loca=9;
    double sum=0;
    for ( ;length<23; length++) {
        if(a[loca]=='1'){
            sum+=powerNum(0.5,pow);
        }
        pow++;
        loca++;
    }
    return sum;
}






int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Error: not enough arguments!");
        return 0;
    }
    
    if (argc > 3) {
        printf("Error:  too many arguments!");
        return 0;
    }
    
    //check if the first argument is in the correct format
    if (strlen(argv[1]) != 32) {
        printf("Error: The inputted sequence is not 32 bits\n");
        return 0;
    }
    if( isBinary(argv[1])==1){
        printf("Error: The inputted sequence contains digits other than 1 and 0\n");
        return 0;
    }
    
    // process the second argument and check if it is malformed
    
    if (strcasecmp(argv[2],"int")==0){
        int length=(int)strlen(argv[1]);
        Array*number=ChangeToBinary(argv[1], length,0);
        Array* Final=ChangeFromBinary(number);
        int a= printm(Final),i=0;
        char fin[a];
        for (; i<=a; i++) {
            if (i==(a)) {
                fin[i]='\0';
            }else{
                fin[i]=(Final->a)+'0';
                Final=Final->next;
            }
        }
        printf("Int: %s",fin);
    }else if(strcasecmp(argv[2],"float")==0){
        Array*findPower=ChangeToBinary(argv[1], 8,1);
        Array* new=(Array *)malloc(sizeof(Array));
        new->a=0;
        new->next=findPower;
        findPower=new;
        Array* Final=ChangeFromBinary(findPower);
        int sum=0;
        while (Final!=NULL) {
            sum*=10;
            sum+=Final->a;
            Final=Final->next;
        }
        sum=sum-127;
        double numForFirst=0;
        if (sum>127) {
            if (argv[1][0]=='1') {
                printf("ninf");
                return 0;
            }else{
                printf("pinf");
                return 0;
            }
        }else if (sum==-127) {
            sum=0;
        }else{
            if (sum>=0) {
                numForFirst=powerNum(2,sum);
            }else{
                sum*=-1;
                numForFirst=powerNum(0.5,sum);
            }
        }
        double num=helpFindDouble(argv[1]);
        num+=1;
        double final=num*numForFirst;
        int po=0;
        if (final!=0){
            while (final>10) {
                final/=10.0;
                po++;
            }
            while (final<1) {
                final*=10.0;
                po--;
            }
        }
        if (argv[1][0]=='1') {
            final*=-1.0;
        }
        double cal=final;
        int a=0,b=0,c=0,pow=po,pochar=0,nega=0;
        if (po<0) {
            po*=-1;
            nega=-1;
            pochar++;
            pow=po;
        }
        while (po!=0) {
            po/=10;
            pochar++;
        }
        po=pow;
        while (final!=0.0) {
            if (final<1) {
                final*=10;
            }
            a=(int)final;
            final-=a;
            b++;
        }
        final=cal;
        if (pochar==0) {
            pochar=1;
        }
        int len=((b+1)+1+pochar+1);
        char fin[len];
        while (c<len) {
            if (c==(len-1)) {
                fin[c]='\0';
            }else if (c==1){
                fin[c]='.';
            }else if (c<(b+1)){
                if (final<1) {
                    final*=10;
                }
                a=(int)final;
                fin[c]=a+'0';
                final-=a;
            }else if(c==(b+1)){
                fin[c]='e';
            }else{
                if (nega==-1) {
                    fin[c]='-';
                    nega=0;
                }else{
                    int p=po%10;
                    po/=10;
                    fin[c]=p+'0';
                }
            }
            c++;
        }
        printf("%s\n",fin);
    }else {
        printf("Error: Output entered is not valid form\n");
    }
    
    return 0;
    
}
