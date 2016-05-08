#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;

int main(int argc,char ** argv)
{
  cout << "W linii polecen podales argumenty! " << endl;
  cout << "Jesli podales litere lub ciag liter zostana zamienione na 0" << endl;
  cout << "Jeśli podales liczbe wieksza niz zakres int zostanie zameniona na -1" << endl;	
	
  if(argc>6)
  {
	 int tab[6]={0}; 
	 for(int w=0;w<6;w++)
	     tab[w]=atoi(argv[w+1]);  // zamiana na liczbe        
     
     if((tab[0]%tab[1]!=1)&&((tab[3]==0 && tab[2]==1) || (tab[4]<=tab[5]))) // negacja zgodnie z regułami Morgana
       cout << "1" << endl ;
     else
       cout << "0" << endl ;  
  }
  else
	  cout <<"Podales za malo argumentów" << endl;
  
return 0;
}
