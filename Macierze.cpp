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
      	
		macierz();                                                      //konstruktor domyslny 
      	macierz(unsigned int wiersze, unsigned int kolumny);            //konstruktor dwuparametrowy
      	~macierz()                                                      //destruktor
      	{
      		for( int i = 0; i < wiersze; i++ )                
      		{delete[]tablica[i];}        
      		delete[] tablica;
      	}
      	macierz(macierz const &m);                                      //konstruktor kopiujacy 
      
      	//operatory przeciazenia
      	friend macierz operator+(const macierz &m1, const macierz &m2); 
      	friend macierz operator-(const macierz &m1, const macierz &m2);
      	friend macierz operator*(const macierz &m1, const macierz &m2);
      	
		//metody
      	void Wyswietl()const;
      	void WprowadzDane();
		void Transpozycja();
		void Wyznacznik();
		void Stopien();
		void readFromFile();
        void writeToFile();
		void Random();
		void Szukaj(unsigned int cos);
		void Zmien(unsigned int numer, unsigned int wartosc);
}; 



macierz::macierz ()                                                                 //konstruktor domyslny 
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



macierz::macierz (unsigned int wier, unsigned int kol)                             //konstruktor dwuparametrowy
{ 
    kolumny = kol; 
    wiersze = wier; 
    double wartosc; 
    tablica = new double *[wiersze]; 
    for (int i=0; i<wiersze;i++) 
        tablica[i]=new double[kolumny];    
} 



macierz::macierz(macierz const &m)                                                  //konstruktor kopiujacy
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


void macierz::WprowadzDane ()                               //Uzupelnienie RECZNE
{
	for ( int i = 0; i < wiersze; i++ ) 
    {  
		for (int j = 0; j < kolumny; j++) 
        { 
			cout << "PODAJ [" << i << "]" << "[" << j << "] element macierzy: ";
            double wartosc;
            while(!(cin>>wartosc))                                                  //wykonuje sie dopoki uzytkownik bedzie wprowadzal bledne dane
            { 
              	cout << "BLAD! Wprowadz poprawna wartosc: ";
              	cin.clear(); 
              	cin.sync(); 
            }
        tablica[i][j] = wartosc; 
        } 
    }  
}



void macierz::Transpozycja ()                            //Wykonanie Transpozycji macierzy
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



void macierz::Wyznacznik ()               //Obliczenie Wyznacznika Macierzy(tylko dla 2x2 i 3x3)
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

void macierz::Stopien ()                //Obliczenie Stopnia Macierzy
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


void macierz::readFromFile()              //Wczytanie macierzy z pliku
{
	ifstream file("macierz.txt");                       //nazwa pliku z ktorego pobieramy macierz
	for (int i = 0; i < wiersze; i++)
		for (int j = 0; j < kolumny; j++)
			file >> tablica[i][j];
	file.close();
}

void macierz::writeToFile()                             //Wczytanie macierzy do pliku
{
    cout << endl << "Eksportowanie macierzy: " << endl;
    ofstream file;
    file.open("macierz.txt");                           //nazwa tworzonego pliku do ktorego wpisujemy macierz
    for (int i = 0; i < wiersze; i++) {
        for (int j = 0; j < kolumny; j++) {
            file << tablica[i][j] << " ";
        }
        file << std::endl;
    }
    file.close();
    cout << "Zawartosc pliku macierz.txt\n";
    system("type macierz.txt");
}

void macierz::Random ()                               //Uzupelnienie automatyczne liczbami losowymi od 0 do 9
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


void macierz::Szukaj (unsigned int cos)                //Przeszukanie macierzy o podana wartosc i zwrocenie wyniku
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
    	cout << "NIE MA ELEMENTU o podanej wartosci w Macierzy!"<< endl;
    else
	{
		cout << "Liczba : |" << cos << "| wystepuje w macierzy: |" << ile << "| razy." << endl;  
		cout << "Liczba : |" << cos << "| wystepuje w macierzy na nastepujacych pozycjach: | ";
		for (int i = 0; i < ile; i++)
			cout << tab[i] << " | ";
		cout<< endl;
	}
}


void macierz::Zmien (unsigned int numer, unsigned int wartosc)                      // Zmiana wartosci podanego elementu
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





macierz operator+(const macierz &m1, const macierz &m2)                             //operator przeciazenia +
{ 

	  	macierz m3(m1);
      	for (int i=0; i<m3.wiersze; i++) 
          	for (int j=0; j<m3.kolumny; j++) 
          	{ 
              	m3.tablica[i][j] += m2.tablica[i][j]; 
          	} 
        return m3; 
  	
} 



macierz operator-(const macierz &m1, const macierz &m2)                             //operator przeciazenia -
{ 

	  	macierz m3(m1); 
      	for (int i=0; i<m3.wiersze; i++) 
          	for (int j=0; j<m3.kolumny; j++) 
          	{ 
              	m3.tablica[i][j] -= m2.tablica[i][j]; 
          	}
        return m3; 
  	
}



macierz operator*(const macierz &m1, const macierz &m2)                             //operator przeciazenia *
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



int main() 
{   
	int liczbaA;
	int liczbaB;
 	srand( time( NULL ) );


					cout << "Utworzenie PIERWSZEJ Macierzy 3x3 " << endl;
					liczbaA = 3;
					macierz A (liczbaA,liczbaA);                                    //stworzenie pierwszej macierzy - konstruktor dwuparametrowy
					cout << "Automatyczne UZUPELNIENIE LOSOWE: " ;
					A.Random (); 
					A.Wyswietl();
			        

		  			Sleep(1000);                                                    //OPӯNIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
		  			cout << endl;
			        cout << "WYZNACZNIK Macierzy: " ;
			        A.Wyznacznik();                                                 //obliczenie i wyswietlenie WYZNACZNIKA Macierzy

			        
					Sleep(1000);                                                    //OPӯNIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
					cout << endl;
					cout << "Stopien Macierzy: " ;
					A.Stopien();                                                    //obliczenie i wyswietlenie STOPNIA Macierzy

					Sleep(1000);                                                    //OPӯNIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////  
					cout << endl;      
		            cout << "SZUKANIE liczby 5 w Macierzy "<< endl;      
		            int cos = 5;
		            A.Szukaj(cos);                                                  //Przeszukanie Macierzy i wyswietlenie wyniku


					Sleep(1000);                                                    //OPӯNIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
					cout << endl;
		            cout << " ZAMIANA wartosci elementu numer 3 na 99. "<< endl;      
		            int numer = 3;
			        int wartosc = 99;
			        A.Zmien(numer, wartosc);                                        //Zamiana zawartosci elementu na podany, wedlug numeru elementu w Macierzy od 1 do....
			        cout << "MACIERZ po dokonaniu ZMIANY: "<< endl; 
		    		A.Wyswietl();	
					Sleep(1000);                                                    //OPӯNIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////			
					cout << endl;				
					cout << "Utworzenie  DRUGIEJ Macierzy 3x3 " << endl;
					liczbaB = 3;
					macierz B (liczbaB,liczbaB);                                    //stworzenie drugiej macierzy - konstruktor dwuparametrowy
					cout << "Automatyczne UZUPELNIENIE LOSOWE: " ;
					B.Random ();                                                    //uzupelnianie automatyczne - losowe warto�ci drugiej macierzy
					B.Wyswietl();
					
					Sleep(1000);                                                    //OPӯNIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
					cout << endl;
					macierz C=A+(B);                                                // utworzenie macierzy C ktora jest wynikiem dodania macierzy A i B
			        cout << "Wynik DODAWANIA Macierzy: ";
			        C.Wyswietl();                                                   // wyswietlenie zawartosci trzeciej macierzy
					
					Sleep(1000);                                                    //OPӯNIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
					cout << endl;    
					macierz D=A-(B); 
					cout << "Wynik ODEJMOWANIA Macierzy: ";
			        D.Wyswietl();

					Sleep(1000);                                                    //OPӯNIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
					cout << endl;
					macierz E=A*(B); 
					cout << "Wynik MNOZENIA Macierzy: " ;
			        E.Wyswietl();
			        
			        Sleep(1000);                                                    //OPӯNIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
			        macierz F=A;
                    macierz G=A;
                    cout << endl;
		            cout << "Wynik TRANSPOZYCJI Macierzy: " << endl ;
		            F.Transpozycja();                                               // wykonanie dzialan TRANSPOZYCJI na macierzy
		            G.Transpozycja();
		            cout << "PIERWSZA Macierzy: " ;
		            F.Wyswietl();                                                   // wyswietlenie zawartosci macierzy po TRANSPOZYCJI
		            cout << "DRUGA Macierzy: " ;
		            G.Wyswietl();
		            
					Sleep(1000);                                                    //OPӯNIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////					
                    A.writeToFile();
					Sleep(1000);                                                    //OPӯNIENIE WYSWIETLENIA   1000ms = 1s //////////////////////////////////////////////////////////////
                    
					macierz m(liczbaA,liczbaA);
					m.readFromFile();
					cout << endl << "Pobrana macierz:";
					m.Wyswietl();
					
    system ("PAUSE");
    return 0; 
}