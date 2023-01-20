#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <windows.h>
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


void macierz::WprowadzDane (unsigned int wiersze, unsigned int kolumny) //Uzupe³nianie RECZNE
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
              	cin.clear(); 
              	cin.sync(); 
            }
        tablica[i][j] = wartosc; 
        } 
    }  
}



void macierz::Transpozycja (unsigned int wiersze, unsigned int kolumny) //Wykonanie Transpozycji macierzy
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



void macierz::Wyznacznik (unsigned int wiersze, unsigned int kolumny) //Obliczenie Wyznacznika Macierzy(tylko dla 2x2 i 3x3)
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

void macierz::Stopien (unsigned int wiersze, unsigned int kolumny) //Obliczenie Stopnia Macierzy
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
void macierz::readFromFile(string fileName) //Wczytanie macierzy z pliku
{
	ifstream file(fileName);
	for (int i = 0; i < wiersze; i++)
		for (int j = 0; j < kolumny; j++)
			file >> tablica[i][j];
	file.close();
}
*/


void macierz::Random (unsigned int wiersze, unsigned int kolumny) //Uzupe³nienie automatyczne liczbami losowymi od 0 do 9
{
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


void macierz::Szukaj (unsigned int cos) //Przeszukanie macierzy o podana wartoœæ i zwrocenie wyniku
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


void macierz::Zmien (unsigned int numer, unsigned int wartosc) // Zmiana wartoœci podanego elementu
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





macierz operator+(const macierz &m1, const macierz &m2) //operator przeciazenia +
{ 

	  	macierz m3(m1);
      	for (int i=0; i<m3.wiersze; i++) 
          	for (int j=0; j<m3.kolumny; j++) 
          	{ 
              	m3.tablica[i][j] += m2.tablica[i][j]; 
          	} 
        return m3; 
  	
} 



macierz operator-(const macierz &m1, const macierz &m2) //operator przeciazenia -
{ 

	  	macierz m3(m1); 
      	for (int i=0; i<m3.wiersze; i++) 
          	for (int j=0; j<m3.kolumny; j++) 
          	{ 
              	m3.tablica[i][j] -= m2.tablica[i][j]; 
          	}
        return m3; 
  	
}



macierz operator*(const macierz &m1, const macierz &m2) //operator przeciazenia *
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
    cout << " 1. DODAWANIE Macierzy (U. LOSOWE)\n";
    cout << " 2. ODEJMOWANIE Macierzy (U. LOSOWE)\n";
    cout << " 3. MNOZENIE Macierzy (U. LOSOWE)\n";
    cout << " 4. TRANSPOZYCJA Macierzy (U. LOSOWE)\n";
    cout << " 5. WYZNACZNIK Macierzy(DLA 2x2 i 3x3) (U. LOSOWE)\n";
    cout << " 6. STOPIEN Macierzy (U. LOSOWE)\n";
	cout << " 7. IMPORT Macierzy\n";
    cout << " 8. SZUKANIE elementow Macierzy (U. LOSOWE)\n";
    cout << " 9. ZMIANA wartosci elementu Macierzy (U. LOSOWE)\n";
    cout << " 10. ZAMKNIECIE PROGRAMU!\n";
    cout << endl;
    cout << " Co chcesz zrobic? (wybierz odpowiednia liczbe) \n";
};



int main() 
{   
	int liczbaA;
	int liczbaB;
	int wybor;
 	srand( time( NULL ) );
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
		        case 1: //Dodawanie Macierzy (uzupe³nianie rêczne)
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
					
					if (liczbaA == liczbaB) //warunek niezbêdny do wykonania dzia³an na macierzach
		            {	
		            	macierz A (liczbaA,liczbaA); //stworzenie pierwszej macierzy - konstruktor dwuparametrowy
					   	cout << " POGLADOWE uzupelnienie LOSOWE:"<< endl;	                     
			            A.Random (liczbaA,liczbaA); //uzupe³nianie automatyczne - losowe wartoœci pierwszej macierzy
			            cout << " Pierwsza Macierz: ";
			            A.Wyswietl(); // wyœwietlenie zawartoœci pierwszej macierzy
						Sleep(1000); //OPÓ¯NIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
			            macierz B (liczbaB,liczbaB); //stworzenie drugiej macierzy - konstruktor dwuparametrowy
			            cout << " POGLADOWE uzupelnienie LOSOWE:"<< endl;   
			            B.Random (liczbaB, liczbaB); //uzupe³nianie automatyczne - losowe wartoœci drugiej macierzy
			            cout << " Druga Macierz: " ;
			            B.Wyswietl(); // wyœwietlenie zawartoœci drugiej macierzy
						Sleep(1000); //OPÓ¯NIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
						macierz C=A+(B); // utworzenie macierzy C która jest wynikiem dodania macierzy A i B
			            cout << " Wynik DODAWANIA Macierzy: ";
			            C.Wyswietl(); // wyœwietlenie zawartoœci trzeciej macierzy
					}
		            else 
		                cout << "BLAD! Nie mozna wykonac dzialania! \n" << endl;;
					break;
				}
			 
		        case 2: //Odejmowanie Macierzy (uzupe³nianie rêczne) funkcjonowanie analogiczne do Dodawania Macierzy
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
					
					if (liczbaA == liczbaB)
		            {
		            	macierz A (liczbaA,liczbaA);
					   	cout << " POGLADOWE uzupelnienie LOSOWE:"<< endl;               
			            A.Random(liczbaA, liczbaA);
			            cout << " Pierwsza Macierz: ";
			            A.Wyswietl();
			            Sleep(1000); //OPÓ¯NIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
			            macierz B (liczbaB,liczbaB);			                
						cout << " POGLADOWE uzupelnienie LOSOWE:"<< endl;                    
			            B.Random(liczbaB, liczbaB);
			            cout << " Druga Macierz: ";
			            B.Wyswietl();
			            Sleep(1000); //OPÓ¯NIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////    
						macierz C=A-(B); 
						cout << " Wynik ODEJMOWANIA Macierzy: ";
			            C.Wyswietl();
					}
		            else 
		                cout << "BLAD! Nie mozna wykonac dzialania! \n" << endl;;
		            break;
				}
		                   
		        case 3: //Mno¿enie Macierzy (uzupe³nianie rêczne) funkcjonowanie analogiczne do Dodawania Macierzy
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
					
					if (liczbaA == liczbaB)
		            {  
						macierz A (liczbaA,liczbaA);  	
						cout << " POGLADOWE uzupelnienie LOSOWE:"<< endl;                     
			            A.Random(liczbaA, liczbaA);
			            cout << " Pierwsza Macierz: ";
			            A.Wyswietl();
			            Sleep(1000); //OPÓ¯NIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
			            macierz B (liczbaB,liczbaB);
						cout << " POGLADOWE uzupelnienie LOSOWE:"<< endl;  
			            B.Random(liczbaB, liczbaB);
			            cout << " Druga Macierz: ";
			            B.Wyswietl();
						Sleep(1000); //OPÓ¯NIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
						macierz C=A*(B); 
						cout << " Wynik MNOZENIA Macierzy: " ;
			            C.Wyswietl();
					}
		            else
		                cout << "BLAD! Nie mozna wykonac dzialania! \n" << endl;;
		            break;
				} 
		 
		        case 4: //Transpozycja Macierzy (uzupe³nianie automatyczne losowe)
				{
					cout << " TWORZENIE MACIERZY: " << endl;
					cout << endl;
					    
					cout << " Podaj WIELKOSC macierzy [NxN]: ";
					cin>>liczbaA;                
					cout << " Stworzyles MACIERZ: " << liczbaA << "x" << liczbaA << endl;
					cout << endl;       
		                 
		            macierz A (liczbaA,liczbaA);  //stworzenie macierzy - konstruktor dwuparametrowy
		            cout << " POGLADOWE uzupelnienie LOSOWE:"<< endl;                    
		            A.Random(liczbaA,liczbaA); //uzupe³nianie macierzy wartoœciami losowymi
		            cout << " MACIERZ: ";
		            A.Wyswietl(); // wyœwietlenie zawartoœci macierzy
	  
		            cout << " Wynik TRANSPOZYCJI Macierzy: " ;
		            A.Transpozycja(liczbaA, liczbaA); // wykonanie dzia³añ TRANSPOZYCJI na macierzy
		            A.Wyswietl(); // wyœwietlenie zawartoœci macierzy po TRANSPOZYCJI
		            break;
				}
		               
		        case 5: //Wyznacznik Macierzy (uzupe³nianie automatyczne losowe)
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
			            macierz A (liczbaA,liczbaA); //stworzenie macierzy - konstruktor dwuparametrowy
			            cout << " POGLADOWE uzupelnienie LOSOWE:"<< endl;                    
		            	A.Random(liczbaA,liczbaA); //uzupe³nianie macierzy wartoœciami losowymi
			            cout << " MACIERZ: ";
			            A.Wyswietl(); // wyœwietlenie zawartoœci macierzy
		  
			            cout << " WYZNACZNIK Macierzy: " ;
			            A.Wyznacznik(liczbaA, liczbaA); //obliczenie i wyœwietlenie WYZNACZNIKA Macierzy
					}
		            break;
				}
		        
		        case 6: //Stopieñ Macierzy (uzupe³nianie automatyczne losowe)
				{
		        	cout << " TWORZENIE MACIERZY: " << endl;
					cout << endl;
					    
					cout << " Podaj WIELKOSC macierzy [NxN]: ";
					cin>>liczbaA;                
					cout << " Stworzyles MACIERZ: " << liczbaA << "x" << liczbaA << endl;
					cout << endl; 
					
		        	                   
					macierz A (liczbaA,liczbaA);
					cout << " POGLADOWE uzupelnienie LOSOWE:"<< endl;                    
		            A.Random(liczbaA,liczbaA);
					cout << " MACIERZ: ";
					A.Wyswietl();
		
					cout << " Stopien Macierzy: " ;
					A.Stopien(liczbaA, liczbaA); //obliczenie i wyœwietlenie STOPNIA Macierzy
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
				
		        case 8: //Odnajdywanie elementów po podanej wartoœci (uzupe³nianie automatyczne losowe)
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
		            A.Szukaj(cos); //Przeszukanie Macierzy i wyœwietlenie wyniku
	  
		            break;		
				}

				case 9: // Zamiana wartoœci elementu na podan¹ (uzupe³nianie automatyczne losowe)
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
		            if (numer < 1 || numer > granica) //zabezpieczenie przed wyjœciem poza badany zakres
		            {
		            	cout << " BLAD! NUMER poza zakresem badanej Macierzy!" << endl;
					}
					else
					{
						cout << " Podaj nowa WARTOSC elementu:  "<< endl;      
			            int wartosc;
			            cin >> wartosc;
			            A.Zmien(numer, wartosc); //Zamiana zawartoœci elementu na podan¹, wed³ug numeru elementu w Macierzy od 1 do....
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
