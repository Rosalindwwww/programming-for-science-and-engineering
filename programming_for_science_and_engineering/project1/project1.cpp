//library includes go here
//program header goes here
//tingjie yu 9.17.2021
//project1: accure interest each month and print output

#include <iostream>
using namespace std;
//global constant declarations and initializations here


//global function prototypes and documentation here
bool accrueInterest(
              double &balanceAmt,
              const int numMonths,
              const bool doPrintEachMonth
            );

bool accrueOneMonthsInterest(
              double &balanceAmt,
              const bool doPrintInfo
            );

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else
int main()
{
//implementation of main function goes here
 double balanceAmt;
 int numMonths;
 char y;

//input datas
 cout << "Enter the initial balance of the account: ";
 cin >> balanceAmt;
 cout << "Enter the number of months to accrue interest: " ;
 cin >> numMonths;
 cout << "Show month-by-month results - 'y' for yes, any other for no: ";
 cin >> y;
 double initBalance = balanceAmt;

//error case
 if(!accrueInterest(balanceAmt, numMonths, y == 'y'))
 {
  return 0;
 }

//output datas
 cout << "Interest accrued for " << numMonths << " months!" << '\n' << '\n';
 cout << "Initial balance: " << initBalance << '\n';
 cout << "Total interest accrued: " << (balanceAmt - initBalance) << '\n';
 cout << "Final balance: " << balanceAmt << '\n';
 return 0;

}
#endif
//global function definitions go here

bool accrueInterest(
              double &balanceAmt,
              const int numMonths,
              const bool doPrintEachMonth
            )
{

//error case
 if(numMonths <= 0)
 {
  cout << "ERROR in accrueInterest: ";
  cout << "numMonths must be > 0, but the value " << numMonths;
  cout << " was provided!" << '\n';
  cout << "Sorry, an error was detected. Unable to provide results!" << '\n';
  return 0;
 }


//use for loop to call function for accrueOneMonthsInterest 
 for(int cnt = 0; cnt < numMonths; cnt = cnt + 1)
 {
  if (!accrueOneMonthsInterest(balanceAmt,doPrintEachMonth))
  {
   return 0;
  }
 }


 return 1;

}

bool accrueOneMonthsInterest(
              double &balanceAmt,
              const bool doPrintInfo
            )
{

 double rate;
 double initBalance;
 double interestAccru;

//error case
//calculate the rate
 if(balanceAmt < 0)
 {
  cout << "ERROR in accrueOneMonthsInterest: ";
  cout << "balanceAmt must be >= 0, but the value " << balanceAmt;
  cout << " was provided!" << '\n';
  cout << "Sorry, an error was detected.  Unable to provide results!" << '\n';
  return 0;
 }
 else if (balanceAmt < 1000)
 {
  rate = 0.0015;
 }
 else if(balanceAmt < 15000)
 {
  rate = 0.00225;
 }
 else if(balanceAmt >= 15000)
 {
  rate = 0.004;
 }

 initBalance = balanceAmt;
 interestAccru = rate * balanceAmt;
 balanceAmt = balanceAmt + interestAccru;

//print the results
  if(doPrintInfo)
  {
  cout << "Accruing interest for 1 month:" << '\n';
  cout << "  Initial balance: " << initBalance << '\n';
  cout << "  Initial rate: " << rate << '\n';
  cout << "  Interest accrued: " << interestAccru << '\n';
  cout << "  New balance: " << balanceAmt << '\n';
  }
  return 1;

}
