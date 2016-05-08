#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;

int main(int argc,char ** argv)
{
  if(argc>6)
  {
	 int tab[6]={0}; 
	 for(int w=0;w<6;w++)
	     tab[w]=atoi(argv[w+1]);  // zamiana na liczbe        
     
     if((tab[0]%tab[1]==1)||(((tab[3]!=0)&&(tab[2]!=1))&&(tab[4]>tab[5])))
     {
       cout << "1" << endl ;
       return 1;
     }
     else
     {
       cout << "0" << endl ;  
       return 0;
     }
  }
  else
	  cout <<"Podales za malo argumentów" << endl;
  
return 0;
}
