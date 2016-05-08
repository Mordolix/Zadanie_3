/*
Autor: Jakubiec Jarosław
*/
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<stdio.h>
#include<fstream>

using namespace std;

bool what;
int sub_all[5][6]={{1,3,1,7,3,4},{3,-1,-1,5,4,2},{-1,2,0,5,3,3},{1,2,3,4,5,1},{6,4,2,-1,5,5}};
int person_feelings[6]={0,0,0,0,0,0};
int noot[9][3];
int oor[9][3];
int impl[9][3];
int andd[9][3];
string names[6]={"happiness:","excitement:","fear:","relax:","halucynations:","poisoning:"};

// expected - spodziewana wartosc odczucia
// t - wskaznik ktora to wartosc w tablicy
// sub_all - wszystkie wartosci odczuc
// x,y - wspolrzedne w tablicy odczuc 

bool wczytajPlik(string name,int A[][3],int y_n,int x_n)
{
	char a;
    ifstream file;
    file.open( name.c_str() );
    if( !file.good() )
         return false;
     
    for(int y=0 ; y< y_n ; y++)
    {   
      for(int x=0 ; x< x_n ; x++)		  
       if(file.good())
       {       
         file >> a ;
         if((a != '1')&&(a != '0'))
           A[y][x]=-1;
         else
         {
           A[y][x]=a;
           A[y][x]-=48;
         }  
      }
      else
      {
		//file.close();  
        return false;    
      }
    }   
    //file.close();
    return true;
}

void backup(int help[])
{
	for(int k=0;k<6;k++)
	help[k]=person_feelings[k];	
}

void backup_return(int help[])
{
	for(int k=0;k<6;k++)
	person_feelings[k]=help[k];
}

void alt(int y)
{
	int value;
	
	for(int k=0 ; k<5 ; k++)
	{
	   for(int w=0 ; w<9 ; w++)
	   {
	 	  if(sub_all[y][k] == -1)
		  {
			  if(person_feelings[k]%2==oor[w][0])
	 	       value=oor[w][2];
		  }
		  else
		  {
	 	     if((person_feelings[k]%2==oor[w][0])&&(sub_all[y][k]%2==oor[w][1]))
	 	       value=oor[w][2];
		  } 
	   }		
	if(value == -1)
	person_feelings[k]+=-1;
	
	if(value == 1)
	person_feelings[k]+=sub_all[y][k];		
   }
   
   person_feelings[5]+=sub_all[y][5]; 	 
}

void nott(int y)
{
	for(int w=0 ; w<5 ; w++)
	   {
		  if(sub_all[y][w]!=-1) 
	 	    person_feelings[w]+=-sub_all[y][w];
	 	  else
	 	    person_feelings[w]+=sub_all[y][w]; 	    
	   }	
	   
	person_feelings[5]+=-sub_all[y][5];    
}

void kon(int y)
{
	int value;
	
	for(int k=0 ; k<5 ; k++)
	{
	   for(int w=0 ; w<9 ; w++)
	   {
		  if(sub_all[y][k] == -1)
		  {
			  if(person_feelings[k]%2==andd[w][0])
	 	       value=andd[w][2];
		  }
		  else
		  {
	 	     if((person_feelings[k]%2==andd[w][0])&&(sub_all[y][k]%2==andd[w][1]))
	 	       value=andd[w][2];
		  } 
	   }	
	
	 if(value == -1)
	 person_feelings[k]+=-1;
	
	 if(value == 1)
	 person_feelings[k]+=sub_all[y][k];
		
   }	
   
   person_feelings[5]+=sub_all[y][5]; 
    
}

int possible(int expected,int x,int y,int overdose) 
{
	int help[6]={0};
	
	if((!what)&&(person_feelings[x] < expected)&&(person_feelings[5]<=overdose)&&(person_feelings[x]>-15))
    {  	
	   if(y+1 < 5){	
		  backup(help);   
		  alt(y);
	      possible(expected,x,y+1,overdose);
	      backup_return(help);
	      
	      backup(help);
	      kon(y);
	      possible(expected,x,y+1,overdose);
	      backup_return(help);
          
          backup(help);
          nott(y);
	      possible(expected,x,y+1,overdose);
	      backup_return(help);
	      
	      possible(expected,x,y+1,overdose);   
       }
	}else
	  if((person_feelings[x] == expected)&&(person_feelings[5]<=overdose))
	  what = true;
	  
	return what;  
}

void write(int expected, int t)
{
  for(int w=0 ; w<5 ; w++)
  {	
	cout << "Substancja" << "["<< w << "]" << ":"; 
    for(int k=0 ; k<6 ; k++)	
	   cout << names[k] <<"["<< sub_all[w][k]<<"]"<< " ";   
    cout << endl;
  }
  
  cout << "Aktualny stan:";
  
  for(int k=0;k<6;k++)
  cout << names[k] << "[" <<person_feelings[k]<<"]"<< " ";
  cout << endl;
  
  cout << names[t] <<" " <<"["<< expected <<"]" << endl;
  
  cout << "k - dodaj jak dla koniunkcji "<< endl;
  cout << "a - dodaj jak dla alternatywy "<< endl;
  cout << "n - zaneguj wartosc odczuc "<< endl;
}

void play_game()
{
	int expected,t,overdose,which_sub;
	char which;
	int w=5;
	
	while(w--)
	{
	  
	  for(int k=0;k<6;k++)
	  person_feelings[k]=0;
	  	
	  t = rand()%5;   // tutaj wybieram ktore odczucie mam tworzyc
      overdose = 15;   // tutaj jest na sztywno ustalone przedawkowanie, mozna je losowac ale to pozniej
     what = false;
     do{  // tutaj wybieram jaka oczekiwana wartosc ma miec modyfikowane odczucie
      expected = rand()%15+1;
     }while(!possible(expected,t,0,overdose)); // sprawdzam czy da sie zmodyfikowac wybrane odczucie do takiego poziomu
  
   	while(( person_feelings[5] < overdose )&&( person_feelings[t]!=expected ))
    {
	    write(expected,t);
	    cin >> which;
	    
	    cout << "Teraz podaj numer substancji:"<< endl;
	    
	    cin >> which_sub;
	    
	    if(which=='k')
		      kon(which_sub);
		    else
		if(which=='a')
		   	  alt(which_sub);
		   	else
		if(which=='n')
		   	  nott(which_sub); 
		   	else
		   	 cout << "Podales zly znak. Podaj inny! "<< endl  ;
	cout << "******************************************************************"<< endl;	   	 	
    } 
    
    if(person_feelings[5] > overdose)
    {
	    cout << "Przedawkowales!"<< endl;
	    cout << "******************************************************************"<< endl;	
    }
    
	if((person_feelings[t] == expected)&&(person_feelings[5] <= overdose ))
	  {
	   if(person_feelings[5] == overdose)
	   {
		 cout << "O ty ryzykancie ty... Byles na granicy przedawkowania, jednak sie udalo." << endl;
	     cout << "**********************************************************"<< endl;
	      } 
		    else 
		    {
	          cout << "Udalo Ci sie osiagnac wyznaczony stan bez zbednego ryzyka!"<< endl;		     
              cout << "**********************************************************"<< endl;
            }
      }
  }       
}

void rules()
{
  cout << "Gra polega na tym aby wprowadzic jednostke w odpowiedni stan i nie przedawkowac."<< endl ;	
  cout << "Dokonujemy tego za pomocą 5 substancji ktore mozemy podawac na 3 sposoby"<< endl;
  cout << "Kazda substancje mozemy zanegowac: działa to jak dodanie do organizmu " << endl;
  cout << "wartosci ujemnej danej substancji i odejmuje sie zatrucie naszej jednostki."<< endl;
  cout << "Mozemy takze ja dodac jak na zasadzie koniunkcji ale wtedy bierzemy modulo 2 z wartosci  "<< endl;
  cout << "ktora ma organizm i wartosci ktora chcemy dodac i postepujemy wedlug logiki trojwartosciowej"<< endl;
  cout << "czyli dodajemy jesli wynikiem jest 1, nie dodajemy jesli wynikiem jest 0 i dodajemy -1 jesli wynikiem jest -1."<< endl;
  cout << "Kazda substancja moze miec nieoznaczony wpływ na organizm co oznacza, ze w swoich wartosciach ma -1"<< endl;
  cout << "Mozemy także dodac substancje na zasadzie alternatywy i tutaj też działamy według logiki trojwartosciowej"<< endl;
  cout << "Kazda substancja ma okreslony parametr zatruwajacy i nie mozemy przekroczyc dopuszczalnej normy"<< endl;
  cout << "dla organizmu. Powodzenia!"<< endl;
  cout << "******************************************************************"<< endl;	
}

int main(int argc, char * argv[])
{
  srand(time(NULL));	
  
  
 rules(); 
  
 if(argc == 5) 
 {
  while(argc > 1)
  {
	  string tmp=argv[argc-1];
	  if(tmp=="not.txt")
	     wczytajPlik(argv[argc-1],noot,3,2);
	  else
	    if(tmp=="and.txt")
	    wczytajPlik(argv[argc-1],andd,9,3);
	  else
	    if(tmp=="impl.txt")
	    wczytajPlik(argv[argc-1],impl,9,3);
	  else
	    if(tmp=="or.txt")
	    wczytajPlik(argv[argc-1],oor,9,3);
	  else
	   {
	    cout << "Zla nazwa argumentu" << endl;
	    return 0;
	   }   	  
	  argc--;	     
  }
}
else
  {
    cout << "Zla liczba argumentow" << endl;
    return 0;
  }

  play_game();
             
  return 0;
}
