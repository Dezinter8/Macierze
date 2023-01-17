#include <iostream> 
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
              	cin.clear(); //kasowanie flagi b³êdu strumienia
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



macierz operator*(const macierz &m1, const double skalar) 
{ 
	macierz m2(m1); 
    for (int i = 0; i <m1.wiersze; i++)        
       for (int j = 0; j <m1.kolumny; j++) 
       		m2.tablica[i][j] = m1.tablica[i][j]*skalar;            
    return m2; 
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
    cout << " 6. ODWRACANIE Macierzy(DO ZROBIENIA?)\n";
    cout << " 6. STOPIEN Macierzy(DO ZROBIENIA?)\n";
    cout << " 7. DOPELNIENIE Macierzy(DO ZROBIENIA?)\n";
    cout << " 8. ZAMKNIECIE PROGRAMU!\n";
    cout << endl;
    cout << " Co chcesz zrobic? (wybierz odpowiednia liczbe) \n";
};






int main() 
{   
	int liczbaA;
	int liczbaB;
	int wybor;
 	
 	while(wybor != 8)
 	{
 		wyswietlmenu();
	    cin>>wybor;
	    
		if (wybor < 1 || wybor > 8)
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
		               
		        case 5:
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
		        
		        case 6:break;
		        
		        case 7:break;
		        
		        case 8:
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
