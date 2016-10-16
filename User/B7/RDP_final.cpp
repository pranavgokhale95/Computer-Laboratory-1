/* The grammar on which recursive descent parser is implemented
 E->TE'
 E'->+TE'|epsilon
 T->FT'
 T'->*FT'|epsilon
 F->(E) | id		*/

#include<iostream>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

using namespace std;

char input[10];
int i,error;
void E();
void T();
void Edash();
void Tdash();
void F();
int match(char, char);

int main()
{
    i=0;
    error=0;
    cout<<"Enter the arithmatic expression: ";   //eg. a+a*a;
    cin>>input;
    E();
    if(strlen(input)==i &&(error==0))
        cout<<input<<"\tString is Accepted !!!\n";
    else
        cout<<input<<"\tString is not Accepted !!!!\n";    
    return 0;
}

void E()
{
    T();
    Edash();
}


void Edash()
{
    if(match(input[i], '+'))
    {
        i++;
        T();
        Edash();
    }

}

void T()
{
    F();
    Tdash();
}


void Tdash()
{
    if(match(input[i], '*'))
    {
        i++;
        F();
        Tdash();
    }
}

void F()
{
    if(isalnum(input[i]))
        i++;
    else if(match(input[i], '('))
    {
        i++;
        E();
        if(match(input[i], ')'))
            i++;
        else
        {
            cout<<"Terminating as no matching bracket";
            exit (EXIT_FAILURE);
        }
    }
    else
        {
            cout<<"Terminating as production for F incomplete";
            exit (EXIT_FAILURE);
        }
}

int match(char a, char b)
{
    if(a==b)
        return 1;
    else
        return 0;
}

