/** Binary <--> Decimal conversion
 *
 * Martina Nunvarova
 * 2/10/2017
 */

///Includes
#include "stdlib.h"
#include "windows.h"
#include <iostream>

///Namespace
using namespace std;


///Binary to decimal conversion function
void bin2dec() {
    char input[255];
    int i,k;
    unsigned long int nr;

    do {
        nr=0;

        ///prompt the user
        system("cls");
        cout << "      Binary to Decimal Conversion"<<endl<<endl
            << "(At most the last 32 entered bits will be converted)"<<endl
            << "Please enter a binary number: ";
        cin >> input;

        ///I will use only the 32 least significant bits (the rightmost 32)
        i=strlen(input)-32;
        if (i<0)
            i=0;

        ///go from the 1 to be converted (which is not necessarily the 1st letter entered) all the way to the end, step by 1
        for ( ; (unsigned int)i < strlen(input) ; i++) {
            k=(input[i]-48);                /// '0' = 48 - converting char to int
            if (k<0 || k>1) {               /// did the user enter some nonsense? - LET THEM KNOW!
                cout <<"Binary numbers consist of 1 and 0 only. No EXCEPTION. Try again!";
                Sleep(2500);
                nr=0xffffffff+1;            ///32bit max + 1 (a preset "error" value)
                break;                      ///and ask the user for input again. (another iteration of do-while)
            } else
                nr=nr*2+k;                  ///build up the decimal number by multiplying by 2
        }
    } while (nr==0xffffffff+1);             ///exits only when valid binary number was entered (and converted)

    i=strlen(input)-32;                     ///which letter did we start converting from again?
    if (i<0)
        i=0;

    ///Print them out into the answer
    for ( ; (unsigned int)i < strlen(input) ; i++) {
        cout <<input[i];
    }
    cout << "(bin) = "<<nr<<"(dec)"<<endl<<"Enter 'x' to exit: "<<endl; ///Display the decimal value as well and ask user to enter 'x' to return to main menu
    cin >> input;                           ///and wait for user to enter something and press ENTER
}


///Decimal to binary conversion function
void dec2bin() {
    unsigned long int input,backup;
    char c,bnr[128];
    int i,j;

    ///Ppompt the user
    system("cls");
    cout << "      Decimal to Binary Conversion"<<endl<<endl
        <<endl
        << "Please enter a whole unsigned number (x<="<<0xffffffff<<"): ";

    ///get the input number
    cin >> input;

    backup=input;               ///remember the entered value for "answer"
    i=0;
    while (input >0) {          ///while there is still number to process, keep processing (produce LSB First)
        bnr[i++]=input%2 +48;   ///What is the reminder of div by 2 ? -> number to character 0 = 48 / 1 = 1+48 = 49
        input>>=1;              ///left shift == division by 2
    }
    bnr[i]=0;                   ///terminate the resulting string

    i--;                        ///DO NOT swap the terminating 0x00
    for (j=0;j<i/2;j++) {       ///swap the order of all other characters (bits) - need to be done "length/2" times
        c=bnr[j];
        bnr[j]=bnr[i-j];
        bnr[i-j]=c;
    }

    cout << backup <<"(dec) = ";    ///Answer the decimal value
    i++;
    c=(i/4+((i%4)>0))*4 - i;        ///the amount of un-displayed places (the leading zero padding to groups of 4)

    for (j=0;j<i;j++) {             ///print the binary number with spaces between 4 letter groups from right
        if ((c+j)>0 && !((c+j)%4))
            cout<<" ";
        cout<< bnr[j];
    }
                                    ///and finish the answer and tell user to enter something (i.e. 'x')
    cout <<"(bin)"<<endl<<"Enter 'x' to exit: "<<endl;

                                    ///wait for user to press ENTER to return to main menu
    cin >> bnr;
}

///Main function - "menu" driven program
int main()
{
    char choice[100];

    do {                            ///repeat
        ///Prompt the user
        system("cls");
        cout << "        Binary - Decimal :: Decimal - Binary" << endl <<endl;
        cout << "'b'     ::     to convert Binary to Decimal"<<endl
             << "'d'     ::     to convert Decimal to Binary"<<endl
             << "'q'     ::     to QUIT"<<endl<<endl
             << "Please Enter Your Choice: ";

        ///wait for the answer
        cin >> choice;

        ///Do what user wanted or tell them 'wrong choice'
        switch ( choice[0] ) {
            case 'b': bin2dec(); break;
            case 'd': dec2bin(); break;
            case 'q': break;
            default:
                cout << "Invalid choice, try again";
                Sleep(1500);

        }
    } while (choice[0] != 'q');     ///until the choice is 'q'
    ///back to OS, no errors.
    return 0;
}
