 // Questo è il programma per giocare a mastermind

  #include <time.h>
  #include <stdlib.h>
  #include <iostream>

 using namespace std;

const int massimo=50;
const char nul='y';
const int l=4; /*la lunghezza dell'array che contiene la combinazione*/
const int col=6;
const char colori [col] = { 'r' , 'b' , 'v' , 'g', 'f', 'a' } ;      


//questa funzione, quando viene richiesto, elenca i colori e i caratteri corrispondenti
void scrivi_colori()
{
   cout << "I colori di questo gioco sono:" << '\n' ;

	cout << "rosso     = " <<colori[0]<< '\n';
	cout << "blu       = " <<colori[1]<< '\n';
	cout << "verde     = " <<colori[2]<< '\n';
	cout << "giallo    = " <<colori[3]<< '\n';
        cout << "fucsia    = " <<colori[4]<< '\n';
	cout << "arancione = " <<colori[5]<< '\n';
}
// Questa funzione crea, casualmente, una combinazione
void crea_combinazione ( char comb [] )

{   srand (time (NULL) );

	for ( int i=0 ; i<l ; i++ )
    	comb [i] = colori [rand () % (col)] ; /* la funzione darà come resto sempre un numero tra 0 e 5, che corrispondono alle posizioni dell'array constante colori */

}

//Questa funzione scrive un array combinazione
void scrivi_combinazione ( char comb [] )
{   
    cout << "la combinazione e'" << '\n' ;

	for ( int i=0 ; i<l ; i++ )
            cout << comb [i] << " " ;
       cout << '\n' ;
}

// questa funzione controllo che non ci siano errori nel digitare una combinazione
bool confronto(char comb[])
{  int i, j=0;
   bool trovato;
     do
      {trovato=false;
         i=0;
     	 while ((i<col)&&!trovato)
    	  { if (comb[j]==colori[i])
            trovato=true;
     	    i++;}
        j++;
       }
      while((j<l)&&(trovato));  
        
   return trovato;    
}


// A questo punto, si richiede al giocatore di immettere la propria combinazione
void richiedi_comb ( char comb [] )

{  bool controllo= confronto(comb);       
 cout << "Dai la tua combinazione" << '\n' ;

	for ( int i=0 ; i<l ; i++ )

		cin >> comb [i] ;
      controllo=confronto(comb);
/*è un controllo che verifica che la combinazione sia corretta, cioé che abbia colori che appartengono all'array costante colori  */
      while (!controllo)
	{ 
        cout <<" Hai sbagliato colori!!"<<endl;
       
        scrivi_colori(); 

	cout << "Dai la tua combinazione" << '\n' ;

	for ( int i=0 ; i<l ; i++ )

		cin >> comb [i] ;
                      
           controllo= confronto(comb);                         
          }
  
}


// Ora si controllano se e quante posizioni di colori sono giuste

int controllo_ordine(char comb_i [] , char comb_j [] )

{

	int cont = 0 ;
	for ( int i=0 ; i<l ; i++ )
		if ( comb_i [i] == comb_j [i] )
			cont++ ;
	return cont ;

}


// Adesso questa funzione controlla quanti colori immessi dal giocatore sono giusti

int controllo_colore (char comb_i [] , char comb_j [] )

{       char temp[l];
	bool trovato ; 
	int j, conta=0;

        for(int i=0; i<l; i++)
            temp[i]=comb_j[i];	

	for (int i=0 ; i<l ; i++)
		{trovato=false;
                 j=0;
 
              while ((j<l) &&(!trovato)) 
			{if ( comb_i [i] == temp [j] )
				{ trovato = true;
				  conta++ ;
			            temp[j] = '*' ;
				  }
                               j++ ;}
		  	}
return conta;
}
//Booleana che serve a verificare che la combinazione soddisfi tutti i controlli precedenti
bool verifica(char pre_comb[50][l], int controlli[50][2],char comb[],int m )//m =numero di mosse precedenti
{
char temp[l];
bool ok=true;
int ordine, giusto;
while((ok)&&(m>=0))
{       for (int j=0; j<l; j++)
	temp[j]=pre_comb[m][j];
  ordine= controllo_ordine(temp, comb);
  giusto= controllo_colore(temp, comb)-ordine;
	if ((ordine==controlli[m][0])&&(giusto==controlli[m][1]))
            ok=true;
        else
           ok=false;
    m--;}
return ok;
}


bool rimanenti(char comb[])
{
bool rimasti=false;
int i=0; 
	while((i<l)&&(!rimasti))
		{if (comb[i]==nul)
			rimasti=true;	
		i++;	
		}
return rimasti;
}

bool esiste(char comb[], int posizione)
{
bool eccolo=false;
int i=0;
	while ((i<l)&&(!eccolo))
		{if (colori[posizione]==comb[i])
			eccolo=true;	
		i++;
		}	   
return eccolo;             
}

//ho riscritto la funzione di mast4
void non_azzeccati(char temp[], char gioc[], int cont)
{
srand (time (NULL) );
int j=(rand ()+cont)%(l);
int i=(rand ()+cont)%(col);
	while(rimanenti(gioc))
		{
		while (gioc[j]!=nul)	
			j=(j+1)%l;
	
		 while(esiste(temp, i))
				i=(i+1)%col;
		
		gioc[j]=colori[i];
		 }

}

//forse questa funzione dà segmentation fault come errore.
void sistemazione_bianchi(char prec[], char gioc[], int giusti, int cont)
{
srand (time (NULL) );
int bianchi=giusti;
int j=(rand ()+cont) % (l);
int i=(rand ()+cont) % (l);
		
	while(bianchi>0)
	{	
		
		while(gioc[i]!=nul)
			i=(i+1)%l;
		while((prec[j]==nul)||(j==i))
			j=(j+1)%(l);
				
		gioc[i]=prec[j];
		prec[j]=nul;
		bianchi--;
	
	}
}

//Questa funzione crea una combinazione riprendendo la combinazione precedente
void cerca_comb(char prec[], char gioc[], int ordine, int giusti, int cont) 
{
//char temp[l];

srand (time (NULL) );
int p1, p2;
int sbagliati= l-(ordine+giusti);
int w=0;
int p= (rand ()+cont) % (l);	
//for (int i=0; i<l; i++)
  //temp[i]=prec[i];
for (int z=0; z<l; z++)
gioc[z]=nul;//mi serve un carattere per indentificare dove ancora non ho messo nessun colore

switch(ordine){ /*prende in considerazione quanti colori sono al posto giusto*/
case 1: { gioc[p]=prec[p];
          prec[p]= nul;
          
	  sistemazione_bianchi(prec, gioc, giusti, cont);
          non_azzeccati(prec, gioc, cont);
    	    break;}

case 2: { p1=(rand ()+cont) % (l);
	  p2= rand () % (l);	
          while (p2==p1)
          p2= rand () % (l);
          gioc[p1]=prec[p1];
          prec[p1]=nul;
          gioc[p2]=prec[p2];
          prec[p2]=nul;
        
  	 sistemazione_bianchi(prec, gioc, giusti,cont); 
	  non_azzeccati(prec, gioc,cont);
      
	  break;}
case 3:  {  while(w<3)  
		{
		 gioc[p]=prec[p];
	         prec[p]=nul;
                 p=(p+1)%l;
	           w++;

		  }

    	sistemazione_bianchi(prec, gioc, giusti,cont);
	non_azzeccati(prec, gioc,cont);
          break;}   
             
default: { 
          sistemazione_bianchi(prec, gioc, giusti,cont);  
	 non_azzeccati(prec, gioc,cont);                  
		break;}
  } 
} 


/*questa è la funzione dove il programma fa giocare*/
void fai_giocare()

{ char combinazione [l] ;
  char comb_giocatore [l] ;
  int  mosse=0, ordine, colore;

        crea_combinazione (combinazione) ;
	cout << "Ho elaborato la combinazione. Prova a indovinare!" << '\n' ;
   
	do
	{
 	   richiedi_comb (comb_giocatore  ) ;

           ordine=  controllo_ordine (combinazione , comb_giocatore );
           colore=controllo_colore (combinazione , comb_giocatore )-ordine;

	   cout << "I colori al posto giusto sono:" << ordine << '\n' ;
           cout << "I colori giusti, ma al posto sbagliato, sono:" << colore << '\n' ;
  
 	   mosse++ ;
	 }
	while (ordine != 4) ;

  cout << "Complimenti! Hai indovinato la combinazione giusta in" << mosse << "mosse" << '\n' ;
}


void alternativa(char comb[])
{
	int x=rand()%col;
        int y=rand()%col;
        int z=rand()%col;
        int w=rand()%col;
        for (int i=0; i<col ;x=(x+1)%col,i++) 
	{
    
           for (int j=0; j<col ;y=(y+1)%col,j++) 
        {
              	
              for (int k=0; k<col ;z=(z+1)%col,k++) 
		{
                 
                 for (int t=0; t<col ;w=(w+1)%col,t++) 
		    {
                        comb[0]=colori[x];
			comb[1]=colori[y];
 			comb[2]=colori[z]; 
			comb[3]=colori[w]; 	
                                                          
	         }
              }
           }
        }
}

//Questa è la funzione che dà problemi (dove si danno le istruzioni per far giocare il computer)
void gioca_pc ()

{ 
char combinazione [l] ; //Array in cui si inserisce la cmbinazione da indovinare
char comb_giocatore [l] ; //Array in cui il pc inserisce le sue ipotetiche combinazioni
char temp[l];//
char combinazioni[massimo][l] ;   //Matrice dove il pc scrive le sue combinazioni
int controllo [massimo][2];       //Matrice dove si scrivono i risultati dei controlli colore e ordine

int tentativo = 0 ;  //Inizializzazione del numero dei tentativi
bool vittoria=false; //Inizializzazine della variabile della vittoria, risulta vera quando il pc indovina la combinazione

   cout<<"Ora scrivi la tua combinazione e il pc la indovinerà"<<endl;	
     richiedi_comb(combinazione); //Si richiede di digitare la combinazione che il pc deve indovinare
    
//procedimento che vale solo per il primo tentativo    
    crea_combinazione(comb_giocatore);  //Ora è il pc che crea la sua prima combinazione CASUALE
    scrivi_combinazione(comb_giocatore);   

for(int i=0;i<l;i++)           /*La prima combinazione del pc viene salvata nella riga 0, cioè la prima riga, della matrice "combinazioni[50][l]"*/ 
  combinazioni[0][i]=comb_giocatore[i];

  controllo[0][0]= controllo_ordine(combinazione ,comb_giocatore); /*Qui si salvano i risultati del controllo ordine e del controllo colore nella matrice "controllo [50][2]" */
  controllo[0][1]= controllo_colore( combinazione ,comb_giocatore)-controllo[0][0];

  if (controllo[0][0]==4) //Banalmente, se i colori sono tutti al posto giusto, il pc ha già trovato la soluzione
        vittoria=true;

  cout << "I colori al posto giusto sono:" << controllo[0][0] << '\n' ;
  cout << "I colori giusti, ma al posto sbagliato, sono:" << controllo [0][1] << '\n' ;
                
while (!vittoria)    //Grazie a questo ciclo il pc DOVREBBE indovinare la combinazione
 {  
     //C'è bisogno dell'array temp[l] per visualizzare l'ultima combinazione del pc 

	int tent_migliore=0;
        int mass_giusti=0;
        int cont=0;
    do //Ora il pc cerca di trovare una diversa combinazione che soddisfi i risultati delle precedenti
    { for (int i=0;i<=tentativo;i++)
	 {
           if ((controllo[i][0]+controllo[i][1])>mass_giusti) 
           {
              tent_migliore=i;
              mass_giusti=controllo[i][0]+controllo[i][1];}}

	for (int i=0; i<l; i++)
        temp[i]=combinazioni[tent_migliore][i];
  //cerca_comb(temp, comb_giocatore , controllo[tent_migliore][0], controllo[tent_migliore][1], cont);  //Crea una combinazione basandosi sull'ultima creata
	
 alternativa(comb_giocatore);     	
	
	cont++;
      }
    while(!verifica(combinazioni, controllo, comb_giocatore, tentativo));  /*E' una booleana che diventa vera solo quando ha in comune i risultati di colore e ordine con tutte le combinazione create*/
    
     tentativo++;//è stato fatto un nuovo tentativo! 
    for (int i=0; i<l; i++)  
       combinazioni[tentativo][i]= comb_giocatore[i];  //Visto che abbiamo trovato la combinazione corretta la possiamo   immagazzinare nella matrice

         scrivi_combinazione(comb_giocatore);
  //Possiamo anche immagazzinare i risultati del controllo   
   controllo[tentativo][0]= controllo_ordine( combinazione ,comb_giocatore);
   controllo[tentativo][1]= controllo_colore( combinazione ,comb_giocatore)-controllo[tentativo][0];
  
    cout << "I colori al posto giusto sono:" << controllo[tentativo][0] << '\n' ;
    cout << "I colori giusti, ma al posto sbagliato, sono:" << controllo[tentativo][1] << '\n' ;
   
//Se tutti i colori sono al posto giusto allora la combinazione è  stata indovinata
   if (controllo[tentativo][0]==4)
        vittoria=true;
   }
cout<<"Ho scoperto la combinazione in "<<tentativo+1<<" tentativi"<<endl;
}

void prova()
{char comb1[l];
char comb2[l];
char comb3[l];
int c=0;
richiedi_comb(comb1);
richiedi_comb(comb2);

int ordine= controllo_ordine( comb1 ,comb2);
int giusto=controllo_colore( comb1 ,comb2)-ordine;


   cout << "I colori al posto giusto sono:" << ordine << '\n' ;
   cout << "I colori giusti, ma al posto sbagliato, sono:" << giusto << '\n' ;
scrivi_combinazione(comb1);
scrivi_combinazione(comb2);
  
cerca_comb(comb2, comb3, ordine, giusto, c);
cout<<"combinazione 1"<<endl;
scrivi_combinazione(comb1);
cout<<"combinazione 2 modificata"<<endl;
scrivi_combinazione(comb2);
cout<<"combinazione 3"<<endl;
scrivi_combinazione(comb3);
}

void intro()
{int scelta ;

   cout << "Benvenuti nel gioco di Mastermind!" << '\n' ;
        do
        {   cout<<"Vuoi giocare (premi1), vuoi fare giocare il computer (premi2) o vuoi uscire (premi 3)" <<endl;
        cin>>scelta;
        if ((scelta==1)||(scelta==2))
            scrivi_colori();
        if  (scelta==1)
	fai_giocare();
        else if (scelta==2)
        gioca_pc();
        else if (scelta >3)
          cout<<"scelta sbagliata"<<endl;
		}
        while(scelta!=3);
   cout<<"Ciao!!"<<endl;
}

int main ()
{
intro();
//prova(); //serve per provare la funzione cerca_comb
return 0;
} 
