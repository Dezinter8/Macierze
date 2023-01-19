#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std; 
 
class macierz 
{ 
    public: 
    	unsigned int wiersze;
      	unsigned int kolumny;  
      	double **tablica; 
      	
		macierz(); //konstruktor domyslny 
      	macierz(unsigned int wiersze, unsigned int kolumny); //konstruktor dwuparametrowy
      	~macierz() //destruktor
      	{
      		for( int i = 0; i < wiersze; i++ )                
      		{delete[]tablica[i];}        
      		delete[] tablica;
      	}
      	macierz(macierz const &m); //konstruktor kopiujacy 
      
      	//operatory przeciazenia
      	friend macierz operator+(const macierz &m1, const macierz &m2); 
      	friend macierz operator-(const macierz &m1, const macierz &m2);
      	friend macierz operator*(const macierz &m1, const macierz &m2);
      	
		//metody
      	void Wyswietl()const;
      	void WprowadzDane(unsigned int wiersze, unsigned int kolumny);
		void Transpozycja(unsigned int wiersze, unsigned int kolumny);
		void Wyznacznik(unsigned int wiersze, unsigned int kolumny);
		void Stopien(unsigned int wiersze, unsigned int kolumny);
		void readFromFile(string fileName);
		void Random(unsigned int wiersze, unsigned int kolumny);
		void Szukaj(unsigned int cos);
		void Zmien(unsigned int numer, unsigned int wartosc);
}; 



macierz::macierz ()  //konstruktor domyslny 
{          
    wiersze=kolumny=2;    
    tablica = new double *[wiersze]; 
    for (int i=0; i<wiersze;i++) 
        tablica[i]=new double[kolumny]; 
		          
    for ( int i = 0; i < wiersze; i ++ ) 
    { 
        cout<<"wiersz "<<i<<": "; 
        for (int j=0; j<kolumny; j++)  
            tablica[i][j] = 0;       
    } 
} 



macierz::macierz (unsigned int wier, unsigned int kol)  //konstruktor dwuparametrowy
{ 
    kolumny = kol; 
    wiersze = wier; 
    double wartosc; 
    tablica = new double *[wiersze]; 
    for (int i=0; i<wiersze;i++) 
        tablica[i]=new double[kolumny];    
} 



macierz::macierz(macierz const &m)  //konstruktor kopiujacy
{ 
    kolumny = m.kolumny; 
    wiersze = m.wiersze; 
    tablica = new double *[wiersze]; 
    for (int i = 0; i < wiersze; i ++ ) 
        tablica[i] = new double[kolumny];  
		   
    for (int i = 0; i < wiersze; i ++ ) 
        for (int j = 0; j < kolumny; j ++ ) 
            tablica[i][j] = m.tablica[i][j]; 
} 

void macierz::Wyswietl()const 
{ 
    for ( int i = 0; i < wiersze; i ++ ) 
    {  
    cout << endl;
        for (int j=0; j<kolumny; j++) 
        { 
            cout<<tablica[i][j]<<" "; 
        } 
    } 
    cout<<endl;  
} 


void macierz::WprowadzDane (unsigned int wiersze, unsigned int kolumny)
{
	for ( int i = 0; i < wiersze; i++ ) 
    {  
		for (int j = 0; j < kolumny; j++) 
        { 
			cout << "PODAJ [" << i << "]" << "[" << j << "] element macierzy: ";
            double wartosc;
            while(!(cin>>wartosc))//wykonuje sie dopoki uzytkownik bedzie wprowadzal bledne dane
            { 
              	cout << "BLAD! Wprowadz poprawna wartosc: ";
              	cin.clear(); //kasowanie flagi bï¿½ï¿½du strumienia
              	cin.sync(); //kasowanie zawartosci bufora obiektu cin
            }
        tablica[i][j] = wartosc; 
        } 
    }  
}



void macierz::Transpozycja (unsigned int wiersze, unsigned int kolumny)
{
	for ( int i = 0; i < wiersze; i++ ) 
    {  
		for (int j = 0; j < kolumny; j++)
		{
			if( i < j )
			{
				int temp;
				temp = tablica[i][j];
				tablica[i][j] = tablica[j][i];
				tablica[j][i] = temp;
			}
		}
    }  
}



void macierz::Wyznacznik (unsigned int wiersze, unsigned int kolumny)
{
	int wyznacznik = 0;
	
	if (wiersze == 2)
	{	
		wyznacznik = tablica[0][0] * tablica[1][1] - tablica[0][1] * tablica[1][0];	
		cout << wyznacznik << endl;
	}
	if (wiersze == 3)
	{	
		wyznacznik = tablica[0][0] * tablica[1][1] * tablica[2][2] + tablica[0][1] * tablica[1][2] * tablica[2][0] + tablica[0][2] * tablica[1][0] * tablica[2][1] - ( tablica[0][2] * tablica[1][1] * tablica[2][0] + tablica[0][0] * tablica[1][2] * tablica[2][1]  + tablica[0][1] * tablica[1][0] * tablica[2][2] );                 	
		cout << wyznacznik << endl;		                                                                                                                                                                                                                                                      
	}
}

void macierz::Stopien (unsigned int wiersze, unsigned int kolumny)
{
	int Stopien = 0;
    for (int i = 0; i < wiersze; i++) {
        int nonZeroElements = 0;
        for (int j = 0; j < wiersze; j++) {
            if (tablica[i][j] != 0) {
                nonZeroElements++;
            }
        }
        Stopien = max(Stopien, nonZeroElements);
    }
	cout << Stopien << endl;
}

/*
void macierz::readFromFile(string fileName) 
{
	ifstream file(fileName);
	for (int i = 0; i < wiersze; i++)
		for (int j = 0; j < kolumny; j++)
			file >> tablica[i][j];
	file.close();
}
*/


void macierz::Random (unsigned int wiersze, unsigned int kolumny)
{
	srand( time( NULL ) );
	int losowa;
	for ( int i = 0; i < wiersze; i++ ) 
    {  
		for (int j = 0; j < kolumny; j++) 
        { 
        losowa = (rand() % 9 );
        tablica[i][j] = losowa; 
        } 
    }  
}


void macierz::Szukaj (unsigned int cos)
{
	int ile = 0;
	int F = wiersze * kolumny;
	int tab[F];
	int temp = 1;
	for ( int i = 0; i < wiersze; i++ ) 
    {  
		for (int j = 0; j < kolumny; j++) 
        { 
        if(tablica[i][j] == cos)
        {
        	tab[ile] = temp;
        	ile++;
		}
        temp++;
    	}
    } 
    
    if(ile == 0)
    	cout << " NIE MA ELEMENTU o podanej wartosci w Macierzy!"<< endl;
    else
	{
		cout << " Liczba : |" << cos << "| wystepuje w macierzy: |" << ile << "| razy." << endl;  
		cout << " Liczba : |" << cos << "| wystepuje w macierzy na nastepujacych pozycjach: | ";
		for (int i = 0; i < ile; i++)
			cout << tab[i] << " | ";
		cout<< endl;
	}
}


void macierz::Zmien (unsigned int numer, unsigned int wartosc)
{
	int temp = 1;
	for ( int i = 0; i < wiersze; i++ ) 
    {  
		for (int j = 0; j < kolumny; j++) 
        { 
        if(temp == numer)
        {
        	tablica[i][j] = wartosc;
		}
        temp++;
    	}
    } 
}





macierz operator+(const macierz &m1, const macierz &m2) 
{ 

	  	macierz m3(m1);
      	for (int i=0; i<m3.wiersze; i++) 
          	for (int j=0; j<m3.kolumny; j++) 
          	{ 
              	m3.tablica[i][j] += m2.tablica[i][j]; 
          	} 
        return m3; 
  	
} 



macierz operator-(const macierz &m1, const macierz &m2) 
{ 

	  	macierz m3(m1); 
      	for (int i=0; i<m3.wiersze; i++) 
          	for (int j=0; j<m3.kolumny; j++) 
          	{ 
              	m3.tablica[i][j] -= m2.tablica[i][j]; 
          	}
        return m3; 
  	
}



macierz operator*(const macierz &m1, const macierz &m2) 
{  
	  	macierz m3(m1); 
       	for (int i = 0; i <m1.wiersze; i++)        
           	{
			   for (int j = 0; j <m2.kolumny; j++) 
               {m3.tablica[i][j] = 0;}
			}            
               
       		for(int i = 0; i < m1.wiersze; i++)
               {for(int j = 0; j < m2.kolumny; j++){
                    for(int k = 0; k < m2.wiersze; k++){
       					m3.tablica[i][j] = m3.tablica[i][j] + m1.tablica[i][k] * m2.tablica[k][j];}}}
  			return m3;

}  



void wyswietlmenu()
{
	cout << endl;
    cout << " ||| PROGRAM WYKONUJACY DZIALANIA NA MACIERZACH [NxN] |||\n";
    cout << " 1. DODAWANIE Macierzy\n";
    cout << " 2. ODEJMOWANIE Macierzy\n";
    cout << " 3. MNOZENIE Macierzy\n";
    cout << " 4. TRANSPOZYCJA Macierzy\n";
    cout << " 5. WYZNACZNIK Macierzy(DLA 2x2 i 3x3)\n";
    cout << " 6. STOPIEN Macierzy\n";
	cout << " 7. IMPORT Macierzy\n";
    cout << " 8. SZUKANIE elementow Macierzy\n";
    cout << " 9. ZMIANA wartosci elementu Macierzy\n";
    cout << " 10. ZAMKNIECIE PROGRAMU!\n";
    cout << endl;
    cout << " Co chcesz zrobic? (wybierz odpowiednia liczbe) \n";
};



int main() 
{   
	int liczbaA;
	int liczbaB;
	int wybor;
 	
 	while(wybor != 10)
 	{
 		wyswietlmenu();
	    cin>>wybor;
	    
		if (wybor < 1 || wybor > 10)
 			cout << " BLAD! Podaj odpowiednia liczbe!" << endl;
 			
 		else
 		{
		    switch (wybor)
			{
		        case 1: 
				{
					cout << " TWORZENIE MACIERZY: " << endl;
					cout << endl;
					    
					cout << " Podaj WIELKOSC PIERWSZEJ macierzy [NxN]: ";
					cin>>liczbaA;                
					cout << " Stworzyles PIERWSZA MACIERZ: " << liczbaA << "x" << liczbaA << endl;
					cout << endl;       
						       
					cout << " Podaj WIELKOSC DRUGIEJ macierzy [NxN]: ";
					cin>>liczbaB;
					cout << " Stworzyles DRUGA MACIERZ: " << liczbaB << "x" << liczbaB << endl;
					cout << endl;
					
					macierz A (liczbaA,liczbaA);
					macierz B (liczbaB,liczbaB);
					
					if (A.wiersze==B.wiersze&&A.kolumny==B.kolumny)
		            {	
					   	cout << " Podaj WARTOSCI PIERWSZEJ Macierzy:"<< endl;	                     
			            A.WprowadzDane (liczbaA,liczbaA);
			            cout << " Pierwsza Macierz: ";
			            A.Wyswietl(); 
			            
			            cout << " Podaj wartosci DRUGIEJ Macierzy:"<< endl;   
			            B.WprowadzDane (liczbaB, liczbaB);
			            cout << " Druga Macierz: " ;
			            B.Wyswietl();
		
						macierz C=A+(B); 
			            cout << " Wynik DODAWANIA Macierzy: ";
			            C.Wyswietl();
					}
		            else 
		                cout << "BLAD! Nie mozna wykonac dzialania! \n" << endl;;
					break;
				}
			 
		        case 2: 
				{   
					cout << " TWORZENIE MACIERZY: " << endl;
					cout << endl;
					    
					cout << " Podaj WIELKOSC PIERWSZEJ macierzy [NxN]: ";
					cin>>liczbaA;                
					cout << " Stworzyles PIERWSZA MACIERZ: " << liczbaA << "x" << liczbaA << endl;
					cout << endl;       
						       
					cout << " Podaj WIELKOSC DRUGIEJ macierzy [NxN]: ";
					cin>>liczbaB;
					cout << " Stworzyles DRUGA MACIERZ: " << liczbaB << "x" << liczbaB << endl;
					cout << endl;
					
					macierz A (liczbaA,liczbaA);
					macierz B (liczbaB,liczbaB);
					
					if (A.wiersze==B.wiersze&&A.kolumny==B.kolumny)
		            {
					   	cout << " Podaj WARTOSCI PIERWSZEJ Macierzy:"<< endl;               
			            A.WprowadzDane(liczbaA, liczbaA);
			            cout << " Pierwsza Macierz: ";
			            A.Wyswietl();
			                
						cout << " Podaj WARTOSCI DRUGIEJ Macierzy:"<< endl;                    
			            B.WprowadzDane(liczbaB, liczbaB);
			            cout << " Druga Macierz: ";
			            B.Wyswietl();
			                
						macierz C=A-(B); 
						cout << " Wynik ODEJMOWANIA Macierzy: ";
			            C.Wyswietl();
					}
		            else 
		                cout << "BLAD! Nie mozna wykonac dzialania! \n" << endl;;
		            break;
				}
		                   
		        case 3: 
				{
					cout << " TWORZENIE MACIERZY: " << endl;
					cout << endl;
					    
					cout << " Podaj WIELKOSC PIERWSZEJ macierzy [NxN]: ";
					cin>>liczbaA;                
					cout << " Stworzyles PIERWSZA MACIERZ: " << liczbaA << "x" << liczbaA << endl;
					cout << endl;       
						       
					cout << " Podaj WIELKOSC DRUGIEJ macierzy [NxN]: ";
					cin>>liczbaB;
					cout << " Stworzyles DRUGA MACIERZ: " << liczbaB << "x" << liczbaB << endl;
					cout << endl;
					
					macierz A (liczbaA,liczbaA);
					macierz B (liczbaB,liczbaB);
					
					if (A.kolumny == B.wiersze)
		            {    	
						cout << " Podaj WARTOSCI PIERWSZEJ Macierzy:"<< endl;                     
			            A.WprowadzDane(liczbaA, liczbaA);
			            cout << " Pierwsza Macierz: ";
			            A.Wyswietl();
			            
						cout << " Podaj WARTOSCI DRUGIEJ Macierzy:"<< endl;    
			            B.WprowadzDane(liczbaB, liczbaB);
			            cout << " Druga Macierz: ";
			            B.Wyswietl();
		
						macierz C=A*(B); 
						cout << " Wynik MNOZENIA Macierzy: " ;
			            C.Wyswietl();
					}
		            else
		                cout << "BLAD! Nie mozna wykonac dzialania! \n" << endl;;
		            break;
				} 
		 
		        case 4: 
				{
					cout << " TWORZENIE MACIERZY: " << endl;
					cout << endl;
					    
					cout << " Podaj WIELKOSC macierzy [NxN]: ";
					cin>>liczbaA;                
					cout << " Stworzyles MACIERZ: " << liczbaA << "x" << liczbaA << endl;
					cout << endl;       
		
					cout << " Podaj WARTOSCI MACIERZY:"<< endl;                    
		            macierz A (liczbaA,liczbaA);
		            A.WprowadzDane(liczbaA, liczbaA);
		            cout << " MACIERZ: ";
		            A.Wyswietl();
	  
		            cout << " Wynik TRANSPOZYCJI Macierzy: " ;
		            A.Transpozycja(liczbaA, liczbaA);
		            A.Wyswietl();
		            break;
				}
		               
		        case 5: //Wyznacznik macierzy
		        {
		        	cout << " TWORZENIE MACIERZY: " << endl;
					cout << endl;
					    
					cout << " Podaj WIELKOSC macierzy [NxN]: ";
					cin>>liczbaA;                
					cout << " Stworzyles MACIERZ: " << liczbaA << "x" << liczbaA << endl;
					cout << endl; 
					
		        	if (liczbaA > 3)
						cout << " BLAD! Zaimplementowane tylko do MACIERZY 2x2 i 3x3 " << endl;
					else
					{
						cout << " Podaj wartosci MACEIRZY:"<< endl;                    
			            macierz A (liczbaA,liczbaA);
			            A.WprowadzDane(liczbaA, liczbaA);
			            cout << " MACIERZ: ";
			            A.Wyswietl();
		  
			            cout << " WYZNACZNIK Macierzy: " ;
			            A.Wyznacznik(liczbaA, liczbaA);
					}
		            break;
				}
		        
		        case 6: //Stopien macierzy
				{
		        	cout << " TWORZENIE MACIERZY: " << endl;
					cout << endl;
					    
					cout << " Podaj WIELKOSC macierzy [NxN]: ";
					cin>>liczbaA;                
					cout << " Stworzyles MACIERZ: " << liczbaA << "x" << liczbaA << endl;
					cout << endl; 
					
		        	
					cout << " Podaj wartosci MACEIRZY:"<< endl;                    
					macierz A (liczbaA,liczbaA);
					A.WprowadzDane(liczbaA, liczbaA);
					cout << " MACIERZ: ";
					A.Wyswietl();
		
					cout << " Stopien Macierzy: " ;
					A.Stopien(liczbaA, liczbaA);
		            break;
				}
		        
				case 7: //import z pliku
				{
					/*
					int n = 0;
					string fileName;
					cout << "Przykladowa zawartosc pliku:\n1 2 3 4\n4 5 6 6\n7 8 9 7\n4 6 6 6 " << endl;
					cout << "Podaj sciezke do pliku: ";
					cin >> fileName;
					cout << "Podaj WIELKOSC macierzy [NxN]: ";
					cin >> n;

					macierz m(n, n);
					m.readFromFile(fileName);
					cout << "Pobrana macierz:" << endl;
					m.Wyswietl();
					*/
					break;
				}
				
		        case 8: //Odnajdywanie elementów po podanej wartoœci
		        {
		        	cout << " TWORZENIE MACIERZY: " << endl;
					cout << endl;
					    
					cout << " Podaj WIELKOSC macierzy [NxN]: ";
					cin>>liczbaA;                
					cout << " Stworzyles MACIERZ: " << liczbaA << "x" << liczbaA << endl;
					cout << endl;       
		
					cout << " POGLADOWE uzupelnienie LOSOWE:"<< endl;                    
		            macierz A (liczbaA,liczbaA);
		            A.Random(liczbaA, liczbaA);
		            A.Wyswietl();
		            
		            cout << " Jakiej wartosci SZUKASZ w Macierzy? "<< endl;      
		            int cos;
		            cin >> cos;
		            A.Szukaj(cos);
	  
		            break;		
				}

				case 9: // Zamiana wartoœci elementu na podan¹.
				{
		        	cout << " TWORZENIE MACIERZY: " << endl;
					cout << endl;
					    
					cout << " Podaj WIELKOSC macierzy [NxN]: ";
					cin>>liczbaA;                
					cout << " Stworzyles MACIERZ: " << liczbaA << "x" << liczbaA << endl;
					cout << endl;       
		
					cout << " POGLADOWE uzupelnienie LOSOWE:"<< endl;                    
		            macierz A (liczbaA,liczbaA);
		            A.Random(liczbaA, liczbaA);
		            A.Wyswietl();
		            
		            int granica = liczbaA * liczbaA;
		            cout << " Podaj NUMER elementu do Zmiany? "<< endl;      
		            int numer;
		            cin >> numer;
		            if (numer < 1 || numer > granica)
		            {
		            	cout << " BLAD! NUMER poza zakresem badanej Macierzy!" << endl;
					}
					else
					{
						cout << " Podaj nowa WARTOSC elementu:  "<< endl;      
			            int wartosc;
			            cin >> wartosc;
			            A.Zmien(numer, wartosc);
			            cout << " MACIERZ po dokonaniu ZMIANY: "<< endl; 
		    			A.Wyswietl();
					}
					
		            break;		
				}	
		        
		        case 10:
				{
				 	cout << "Koniec programu!\n";
		            break; 
		        }       
	        }
    	} 
	}
    system ("PAUSE");
    return 0; 
}
