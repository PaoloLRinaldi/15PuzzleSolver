#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#define LMAX 10
#define HMAX 10
 
void titulo();
void numeriMan(int, int, int tavola[][LMAX], int grande);
void printTavola(int, int, int tavola[][LMAX], int grande);
void numeriRand(int, int, int tavola[][LMAX]);
int checkEnd(int, int, int tavola[][LMAX], int* err1, int* err2);
void giocaUser(int, int, int tavola[][LMAX], int grande);
int giocaComp(int, int, int tavola[][LMAX], float aspe, int grande);
void mossa(int, int, int tavola[][LMAX], int, int, char);
void avvicinaSpazio(int l, int h, int tavola[][LMAX], int* posl, int* posh, int nl, int nh, int nmosse, int arrl, int arrh, float aspe, int permin, int posto, int grande);
void mettiqui(int l, int h, int tavola[][LMAX], int quil, int quih, int nmosse, int* nl, int* nh, int* posl, int* posh, float aspe, int permin, int posto, int grande);
void mossaGen(int l, int h, int tavola[][LMAX], int* posl, int* posh, char c, int* nl, int* nh, float aspe, int posto, int grande);
void trovaNmosse(int l, int h, int tavola[][LMAX], int* nl, int* nh, int nmosse);
void switchTasselli(int l,int h,int tavola[][LMAX]);
char scanner();
int getch();
 
int main() {
  int l, h, giocat, inputn, nuovo=0, r, f, appog, i1, i2, i, grande, quick;
  float aspe;
  int tavola[HMAX][LMAX] = {{0}}, tavolaprova[HMAX][LMAX], tavola2[HMAX][LMAX];
 
  srand48(time(0));
  titulo();
  do {
    system ("clear");
    printf ("Chi vuoi che risolva il puzzle?\n1: Tu\n2: Il computer\n");
    do {
      printf ("Scelta dell'utente: ");
      scanf("%d",&giocat);
      if (giocat!=1 && giocat!=2) printf ("Input errato, ripeti\n");
    } while (giocat!=1 && giocat!=2);
    
    printf ("\n\n1: Partita rapida\n2: Partita personalizzata\n");
    do {
    	printf ("Scelta dell'utente: ");
    	scanf("%d", &quick);
    	if (quick!=1 && quick!=2) printf ("Input errato, ripeti\n");
    } while (quick!=1 && quick!=2);
    
    if (quick==1) {
    	l=4;
    	h=4;
    	inputn=2;
    	grande=1;
    	aspe=2;
    	f=2;
    }
    
    if (quick==2) {
	    if (nuovo!=2) {
	      printf("\n");
	      printf ("Inserire il numero di tasselli per ogni riga (che sia compreso tra 2 e %d): ", LMAX);
	      do {
	    scanf("%d",&l);
	    if (l<2 || l>LMAX) printf ("Input errato, ripeti\n");
	      } while (l<2 || l>LMAX);
	 
	      printf ("Inserire il numero di tasselli per ogni colonna (che sia compreso tra 2 e %d): ", HMAX);
	      do {
	    scanf("%d",&h);
	    if (h<2 || h>HMAX) printf ("Input errato, ripeti\n");
	      } while (h<2 || h>LMAX);
	 
	      printf("\n");
	      printf ("Inserire scelta desiderata:\n");
	      printf ("1: L'utente inserisce manualmente i numeri nella tabella\n2: I numeri vengono inseriti casualmente\n");
	      do {
	    printf ("Scelta dell'utente: ");
	    scanf ("%d",&inputn);
	    if (inputn!=1 && inputn!=2) printf ("Input errato, ripeti\n");
	      } while (inputn!=1 && inputn!=2);
	    }
    }
    if (quick==2) {
	    printf ("\nVuoi che la tavola sia piccola o grande?\n1: Piccola\n2: Grande\n");
	    do {
	      printf ("Scelta dell'utente: ");
	      scanf ("%d",&grande);
	      if (grande!=1 && grande!=2) printf ("Input errato, ripeti\n");
	    } while (grande!=1 && grande!=2);
    }
    if (quick==2) {
	    if (giocat==2) {
	      printf ("\nQuanti decimi di secondo vuoi che passino tra una mossa e l'altra?\n");
	      do {
	    printf ("Scelta dell'utente: ");
	    scanf ("%f",&aspe);
	    if (aspe<0) printf ("Input errato, ripeti\n");
	      } while (aspe<0);
	    }
    }
    do{
      system ("clear");
      if (nuovo!=2) {
    if (inputn==1) numeriMan(l,h,tavola, grande);
    else numeriRand(l,h,tavola);
      }
      for (i=0; i<l*h; i++) {
    if (nuovo!=2) tavola2[i/l][i%l]=tavolaprova[i/l][i%l]=tavola[i/l][i%l];
    else tavola[i/l][i%l]=tavolaprova[i/l][i%l]=tavola2[i/l][i%l];
      }
      r=giocaComp(l, h, tavolaprova, -1, grande);
      if (r==1) {
		    if (quick==2) {
			    do {
			      printf ("Scelta dell'utente: ");
			      scanf ("%d",&f);
			      if (f!=1 && f!=2 && f!=3) printf ("Input errato, ripeti\n");
			    } while (f!=1 && f!=2 && f!=3);
		    }
		    if (f==2) {
		      do {
		        i1=lrand48()%(l*h);
		      } while (tavola[i1/l][i1%l]==-1);
		      do {
		        i2=lrand48()%(l*h);
		      } while (tavola[i2/l][i2%l]==-1 || i1==i2);
		      appog=tavola[i1/l][i1%l];
		      tavola[i1/l][i1%l]=tavola[i2/l][i2%l];
		      tavola[i2/l][i2%l]=appog;
		    }
		    if (f==3) {
		      switchTasselli(l, h, tavola);
		    }
      }
    
      system("clear");
      printf ("La tavola è:\n\n");
      printTavola(l, h, tavola, grande);
      usleep(2000000);
      if (giocat==1) giocaUser(l, h, tavola, grande);
      if (giocat==2) r=giocaComp(l, h, tavola, aspe, grande);
      printf ("\n\nNuova partita?\n1: Stesse impostazioni di prima, tavola diversa\n2: Stesse impostazioni di prima, stessa tavola\n3: Nuove impostazioni\n4: Esci\n");
      do {
    printf ("Scelta dell'utente: ");
    scanf("%d",&nuovo);
    if (nuovo!=1 && nuovo!=2 && nuovo!=3 && nuovo!=4) printf ("Input errato, ripeti\n");
      } while (nuovo!=1 && nuovo!=2 && nuovo!=3 && nuovo!=4);
      if (nuovo!=2 && nuovo!=4) {
    for (i=0; i<l*h; i++) {
      tavola[i/l][i%l]=0;
    }
      }
    } while (nuovo==1 || nuovo==2);
  } while (nuovo==3);
  exit(0);
}
/***************************************************************************************************/
void numeriMan(int l, int h, int tavola[][LMAX], int grande) {
  int i, j, s, k, spaz=0, q;
  for (i=0; i<=(l*h); i++) {
    system ("clear");
    printf ("Ricordo che il numero di colonne è %d e il numero di righe è %d\nDevi inserire, quindi, i numeri da 1 a %d\n", l, h, l*h-1);
    printf ("Per mettere lo spazio bianco inserire -1\n");
    printf ("Iserisci i numeri (premere \"Invio\" dopo ogni numero)\n\n");
    printTavola(l,h,tavola, grande);
    if (i!=l*h) {
      do {
    printf ("Numeri ancora da inserire:");
    q=0;
    for (j=0; j<(l*h-1); j++) {
      s=0;
      for (k=0; k<(l*h-1); k++) {
        if (j+1==tavola[k/l][k%l]) s++;
      }
      if (s==0) {
        if (q!=0) printf (",");
        printf (" %d", j+1);
        q=1;
      }
    }
    if (q!=0 && spaz==0) printf (",");
    if (spaz==0) printf (" (spazio vuoto)\n");
    else printf ("\n");
    printf ("%d° numero: ", i+1);
    scanf ("%d",&tavola[i/l][i%l]);
    if (tavola[i/l][i%l]==-1) spaz=1;
    s=0;
    for (j=0; j<i; j++) {
      if (tavola[j/l][j%l]==tavola[i/l][i%l]) s++;
    }
    if (s!=0) printf ("Numero già inserito, ripeti\n");
    if (tavola[i/l][i%l]<-1 || tavola[i/l][i%l]>l*h-1 || tavola[i/l][i%l]==0) printf ("Input errato, ripeti\n");
      } while (s!=0 || (tavola[i/l][i%l]<-1 || tavola[i/l][i%l]>l*h-1 || tavola[i/l][i%l]==0));
    }
  }
  usleep(1000000);
}
/***********************************************************************************************/
void printTavola(int l, int h, int tavola[][LMAX], int grande) {
  int i, j, k, nmax, cifremax=0, cifremen;      //in realtà cifremax-1
   
  nmax=l*h-1;
  if (grande==1) {
    for (i=10; i<(LMAX*HMAX*LMAX*HMAX); i*=10) if (nmax/i>0) cifremax++;
    for (i=0; i<h; i++) {
      printf ("\t\t");
      for (j=0; j<l; j++) {
    if (tavola[i][j]==-1) {
      printf ("  ");  //2 spazi
      for (k=0; k<cifremax; k++) printf (" ");
    }
    else if (tavola[i][j]!=0) {
      cifremen=0;
      printf (" ");
      for (k=10; k<(l*h); k*=10) if (tavola[i][j]/k>0) cifremen++;
      for (k=0; k<cifremax-cifremen; k++) printf (" ");
      printf ("%d",tavola[i][j]);
    }
    else {
      printf (" _");
      for (k=0; k<cifremax; k++) printf ("_");
    }
      }
      printf ("\n");
    }
  } else {
    for (i=0; i<h; i++) {
      printf ("\t\t");
      for (j=0; j<l; j++) {
    if (tavola[i][j]==-1) printf ("\t ");
    else if (tavola[i][j]!=0) printf ("\t%d",tavola[i][j]);
    else printf ("\t_");
      }
      printf ("\n\n\n");
    }
  }
  printf("\n\n");
}
 
/********************************************************************************************/
void numeriRand(int l, int h, int tavola[][LMAX]) {
  int random[LMAX*HMAX], i, j, p;
   
  random[0]=-1;
  for (i=1; i<l*h; i++) {
    random[i]=i;
  }
 
  for (i=l*h-1; i>=0; i--) {
    p=lrand48()%(i+1);
    tavola[i/l][i%l]=random[p];
    for (j=p; j<l*h-1; j++) {
      random[j]=random[j+1];
    }
  }
 
  
}
/*********************************************************************************************/
int checkEnd(int l, int h, int tavola[][LMAX], int* err1, int* err2) {
  int i, s=0;
 
  for (i=0; i<l*h-1; i++) {
    if (tavola[i/l][i%l]!=i+1) {
      s++;              //non serve controllare anche il 16° numero ovviamente
      if (s==1) (*err1)=i+1;
      else (*err2)=i+1;
    }
  }
  if (s==2 && tavola[h-1][l-1]==-1) return 1;    //non risolvibile perchè 2 sono scambiati
  else if (s!=0) return -1;                      // non finito: coninua
  else return 0;                                 // finito
}
/***********************************************************************************************/
void giocaUser(int l, int h, int tavola[][LMAX], int grande) {
  char c;
  int i, posl, posh, r, err1, err2;
 
   
  while ((r=checkEnd(l, h, tavola, &err1, &err2))==-1) {
    system("clear");
    printf ("Vai!\n\n");
    printTavola(l, h, tavola, grande);
    printf ("Utilizzare i pulsanti, \"w\", \"a\", \"s\" e \"d\"\ (oppure rispettivamente 2, 4, 5, 6)n");
    printf ("per muovere i tasselli\n");
    printf ("\t  ^  \t\t  w\n");
    printf ("\t< v >\t\ta s d\n");
    do {
      printf ("\n\nMossa: ");
   //   scanf ("%c",&c);
   	 c=scanner();
      if (c==102) printf ("Mossa non valida, ripeti\n");
    } while (c==102);
    for (i=0; i<l*h; i++) {
      if (tavola[i/l][i%l]==-1) {
    posl=i%l;
    posh=i/l;
      }
    }
    mossa(l, h, tavola, posl, posh, c);
    }
  system ("clear");
  printf ("\n\n");
  printTavola(l, h, tavola, grande);
  if (r==1) printf ("Il puzzle è risolto (a meno di scambio tra %d e %d)\n", err1, err2);
  if (r==0) printf ("Puzzle risolto!\n");
}
/*****************************************************************************************************************/
void mossa(int l, int h, int tavola[][LMAX], int posl, int posh, char c) {
 
  if (c=='w' || c=='2') {
    if (posh==h-1) printf ("Mossa non valida, ripeti\n");
    else {
      tavola[posh][posl]=tavola[posh+1][posl];
      tavola[posh+1][posl]=-1;
    }
  }
  if (c=='a' || c=='4') {
    if (posl==l-1) printf ("Mossa non valida, ripeti\n");
    else {
      tavola[posh][posl]=tavola[posh][posl+1];
      tavola[posh][posl+1]=-1;
    }
  }
  if (c=='s' || c=='5') {
    if (posh==0) printf ("Mossa non valida, ripeti\n");
    else {
      tavola[posh][posl]=tavola[posh-1][posl];
      tavola[posh-1][posl]=-1;
    }
  }
  if (c=='d' || c=='6') {
    if (posl==0) printf ("Mossa non valida, ripeti\n");
    else {
      tavola[posh][posl]=tavola[posh][posl-1];
      tavola[posh][posl-1]=-1;
    }
  }
}
/***********************************************************************/
int giocaComp(int l, int h, int tavola[][LMAX], float aspe, int grande) {
  int i=0, posl, posh, r, nl, nh, nmosse=0, s=0, err1, err2;
  char c;
   
  do {
    if (i+1==tavola[i/l][i%l]) {
      i++;
      if ((i/l)==h-2 && (i%l)!=l-1 && tavola[h-1][i%l]!=i+l) i--;
    }
    s++;
  } while (i==s);
  nmosse=i;             // serve perchè potrebbe essere che dall'inizio dei numeri siano già a posto e aggiornio nmosse
  if (nmosse==l-1) nmosse--;
   
  while ((r=checkEnd(l, h, tavola, &err1, &err2))==-1) {
    nmosse++;                                 //nmosse in realta' è il numero di numeri messi a posto più 1, quindi il numero da mettere a posto
    for (i=0; i<l*h; i++) {
      if (tavola[i/l][i%l]==-1) {
    posl=i%l;
    posh=i/l;
      }                         // trova lo spazio
    }
    trovaNmosse(l, h, tavola, &nl, &nh, nmosse);             // trova la posizione del numero da mettere a posto
    if ((nmosse-1)/l<=h-3 && (nmosse-1)%l<=l-3 && h>2 && l>2) {     // il "-3" e non "-2" perché sono array e bisogna togliere 1
      mettiqui(l, h, tavola, (nmosse-1)%l, (nmosse-1)/l, nmosse, &nl, &nh, &posl, &posh, aspe, nmosse, nmosse, grande);
    }
    if ((nmosse-1)/l<=h-3 && (nmosse-1)%l==l-2 && h>2) {
      trovaNmosse(l, h, tavola, &nl, &nh, nmosse+1);
      mettiqui(l, h, tavola, nmosse%l, (nmosse/l)+2, nmosse+1, &nl, &nh, &posl, &posh, aspe, nmosse-1, nmosse, grande);
      trovaNmosse(l, h, tavola, &nl, &nh, nmosse);
      mettiqui(l, h, tavola, (nmosse-1)%l, ((nmosse-1)/l)+1, nmosse, &nl, &nh, &posl, &posh, aspe, nmosse, nmosse, grande);
      trovaNmosse(l, h, tavola, &nl, &nh, nmosse+1);
			  if(posl!=l-1 && tavola[posh][posl+1]!=nmosse+1 && nl==l-1) {
			    mossaGen(l, h, tavola, &posl, &posh, 'a', &nl, &nh, aspe, nmosse, grande);
				}
      mettiqui(l, h, tavola, (nmosse%l)-1, nmosse/l, nmosse+1, &nl, &nh, &posl, &posh, aspe, nmosse-1, nmosse, grande);
      trovaNmosse(l, h, tavola, &nl, &nh, nmosse);
      mettiqui(l, h, tavola, (nmosse-1)%l, ((nmosse-1)/l)+1, nmosse, &nl, &nh, &posl, &posh, aspe, nmosse, nmosse, grande);
			  printf("Go\n");
			  if (l>2 && posh==nh && posl<nl) {
				 mossaGen(l, h, tavola, &posl, &posh, 'w', &nl, &nh, aspe, nmosse, grande);
				 mossaGen(l, h, tavola, &posl, &posh, 'a', &nl, &nh, aspe, nmosse, grande);
				}
      avvicinaSpazio(l, h, tavola, &posl, &posh, nl, nh, nmosse+1, ((nmosse-1)%l)+1, (nmosse-1)/l, aspe, nmosse, nmosse, grande);
      c='d';
      mossaGen(l, h, tavola, &posl, &posh, c, &nl, &nh, aspe, nmosse, grande);
      c='w';
      mossaGen(l, h, tavola, &posl, &posh, c, &nl, &nh, aspe, nmosse, grande);
    }
    while ((nmosse-1)/l==h-2 && (nmosse-1)%l<=l-3 && l>2) {
      mettiqui(l, h, tavola, ((nmosse-1)%l)+2, (nmosse-1)/l, nmosse, &nl, &nh, &posl, &posh, aspe, nmosse, nmosse, grande);
      trovaNmosse(l, h, tavola, &nl, &nh, nmosse+l);
      mettiqui(l, h, tavola, ((nmosse-1)%l)+1, ((nmosse-1)/l)+1, nmosse+l, &nl, &nh, &posl, &posh, aspe, nmosse-1, nmosse, grande);
      trovaNmosse(l, h, tavola, &nl, &nh, nmosse);
      mettiqui(l, h, tavola, (nmosse-1)%l, ((nmosse-1)/l)+1, nmosse, &nl, &nh, &posl, &posh, aspe, nmosse, nmosse, grande);
      trovaNmosse(l, h, tavola, &nl, &nh, nmosse+l);
      mettiqui(l, h, tavola, ((nmosse-1)%l)+1, ((nmosse-1)/l)+1, nmosse+l, &nl, &nh, &posl, &posh, aspe, nmosse-1, nmosse, grande);
      avvicinaSpazio(l, h, tavola, &posl, &posh, nl, nh, nmosse+l, (nmosse-1)%l, (nmosse-1)/l, aspe, nmosse, nmosse, grande);
      c='w';
      mossaGen(l, h, tavola, &posl, &posh, c, &nl, &nh, aspe, nmosse, grande);
      c='a';
      mossaGen(l, h, tavola, &posl, &posh, c, &nl, &nh, aspe, nmosse, grande);
      nmosse++;
      trovaNmosse(l, h, tavola, &nl, &nh, nmosse);
    }
    if ((nmosse-1)/l==h-2 && (nmosse-1)%l==l-2) {
      trovaNmosse(l, h, tavola, &nl, &nh, (h*l)-1);
      mettiqui(l, h, tavola, l-2, h-1, (h*l)-1, &nl, &nh, &posl, &posh, aspe, (l*(h-1))-2, nmosse, grande);
      trovaNmosse(l, h, tavola, &nl, &nh, -1);
      if (nl==l-2) mossaGen(l, h, tavola, &posl, &posh, 'a', &nl, &nh, aspe, nmosse, grande);
      if (nh==h-2) mossaGen(l, h, tavola, &posl, &posh, 'w', &nl, &nh, aspe, nmosse, grande);
    }
  }
  system("clear");
  if (aspe>=0) {
    printTavola(l,h,tavola, grande);
    if (r==1) printf ("Il puzzle è risolto (a meno di scambio tra %d e %d)\n", err1, err2);
    if (r==0) printf ("Puzzle risolto!\n");
  } else {
    if (r==1) {
      printf ("Il puzzle generato non è risolvibile.\n");
      printf ("1: Prosegui ugualmente\n");
      printf ("2: Scambia casualmente due caselle per renderlo possibile e prosegui\n");
      printf ("3: Scambia manualmente due caselle\n");
    }
    if (r==0) {
      printf ("Il puzzle è risolvibile.\n");
      usleep(2000000);
    }
  }
  return r;
}
 
/*********************************************************************************/
void avvicinaSpazio(int l, int h, int tavola[][LMAX], int* posl, int* posh, int nl, int nh, int nmosse, int arrl, int arrh, float aspe, int permin, int posto, int grande) {
  char c;
  int q;    //variabile d'appoggio
 
  do {
    if (arrh<(*posh) && (((q=tavola[(*posh)-1][(*posl)])>permin && q!=nmosse) || q==-1) && (*posh)-1>=0) { // se lo spazio deve andare in alto
      c='s';
      mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
    }
    if (arrl<(*posl) && (((q=tavola[(*posh)][(*posl)-1])>permin && q!=nmosse) || q==-1) && (*posl)-1>=0) { // spazio a sinistra
      c='d';
      mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
    }
    if (arrh>(*posh) && (((q=tavola[(*posh)+1][(*posl)])>permin && q!=nmosse) || q==-1) && (*posh)+1<=h-1) { // spazio in basso
      c='w';
      mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
    }
    if (arrl>(*posl) && (((q=tavola[(*posh)][(*posl)+1])>permin && q!=nmosse) || q==-1) && (*posl)+1<=l-1) { // spazio a destra
      c='a';
      mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
    }
    if (((nh<arrh && nh>(*posh)) || (nh>arrh && nh<(*posh))) && (nl==(*posl) && (*posl)==arrl)) {
      //ovvero schiacciato sopra e sotto
      if (arrh<(*posh)) {
    if ((arrl-1)>=0 && (((q=tavola[arrh][arrl-1])>permin && q!=nmosse) || q==-1)) c='d';   // qui lo spazio dopo aver deciso se
    else c='a';
    mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
    c='s';
    mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
      }
      if (arrh>(*posh)) {
    if ((arrl+1)<=l-1 && (((q=tavola[arrh][arrl+1])>permin && q!=nmosse) || q==-1)) c='a';
    else c='d';                                                             // va in basso
    mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
    c='w';
    mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
      }
    }
    if (((nl<arrl && nl>(*posl)) || (nl>arrl && nl<(*posl))) && (nh==(*posh) && (*posh)==arrh)) {
      //ovvero schiacciato a dx e sx
      if (arrl<(*posl)) {
    if ((arrh-1)>=0 && (((q=tavola[arrh-1][arrl])>permin && q!=nmosse) || q==-1)) c='s'; // poi va a sx
    else c='w';
    mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
    c='d';
    mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
      }
      if (arrl>(*posl)) {
    if ((arrh+1)<=h-1 && (((q=tavola[arrh+1][arrl])>permin && q!=nmosse) || q==-1)) c='w'; // poi va a dx
    else c='s';
    mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
    c='a';
    mossaGen(l, h, tavola, posl, posh, c, &nl, &nh, aspe, posto, grande);
      }
    }
    if (arrl>(*posl) && arrh<(*posh) && (q=tavola[(*posh)-1][(*posl)])<=permin && q!=-1  && tavola[(*posh)][(*posl)+1]==nmosse) {
      avvicinaSpazio(l, h, tavola, posl, posh, nl, nh, nmosse, (*posl)+2, (*posh)+1, aspe, permin, posto, grande);     // in caso lo spazio sia "circondato" e debba fare il giro
      avvicinaSpazio(l, h, tavola, posl, posh, nl, nh, nmosse, (*posl), (*posh)-1, aspe, permin, posto, grande);
    }
    if (arrl<(*posl) && arrh>(*posh) && (q=tavola[(*posh)][(*posl)-1])<=permin && q!=-1  && tavola[(*posh)+1][(*posl)]==nmosse) {
      avvicinaSpazio(l, h, tavola, posl, posh, nl, nh, nmosse, (*posl)+1, (*posh)+2, aspe, permin, posto, grande);
      avvicinaSpazio(l, h, tavola, posl, posh, nl, nh, nmosse, (*posl)-1, (*posh), aspe, permin, posto, grande);
    }
  } while ((*posh)!=arrh || (*posl)!=arrl); // fino a che non raggiunge il punto desiderato
}
/******************************************************************************************/
void mettiqui(int l, int h, int tavola[][LMAX], int quil, int quih, int nmosse, int* nl, int* nh, int* posl, int* posh, float aspe, int permin, int posto, int grande) {
  char c;
  int q;
      do {
    if ((*nh)>quih && (((q=tavola[(*nh)-1][(*nl)])>permin && q!=nmosse) || q==-1)) {
      avvicinaSpazio(l, h, tavola, posl, posh, (*nl), (*nh), nmosse, (*nl), (*nh)-1, aspe, permin, posto, grande); // dice di mettere lo spazio subito sopra
      c='w';
      mossaGen(l, h, tavola, posl, posh, c, nl, nh, aspe, posto, grande);
    }
    if ((*nl)>quil && (((q=tavola[(*nh)][(*nl)-1])>permin && q!=nmosse) || q==-1)) {
      avvicinaSpazio(l, h, tavola, posl, posh, (*nl), (*nh), nmosse, (*nl)-1, (*nh), aspe, permin, posto, grande);            // mette lo spazio a sinistra
      c='a';
      mossaGen(l, h, tavola, posl, posh, c, nl, nh, aspe, posto, grande);
    }
    if ((*nl)<quil && (((q=tavola[(*nh)][(*nl)+1])>permin && q!=nmosse) || q==-1)) {
      avvicinaSpazio(l, h, tavola, posl, posh, (*nl), (*nh), nmosse, (*nl)+1, (*nh), aspe, permin, posto, grande);      // a destra
      c='d';
      mossaGen(l, h, tavola, posl, posh, c, nl, nh, aspe, posto, grande);
    }
    if ((*nh)<quih) {
      avvicinaSpazio(l, h, tavola, posl, posh, (*nl), (*nh), nmosse, (*nl), (*nh)+1, aspe, permin, posto, grande);            // mette lo spazio sotto
      c='s';
      mossaGen(l, h, tavola, posl, posh, c, nl, nh, aspe, posto, grande);
    }
      } while ((*nh)!=quih || (*nl)!=quil);     // fino a che la casella non raggiunge la propria posizione
}
/****************************************************************************************/
void mossaGen(int l, int h, int tavola[][LMAX], int* posl, int* posh, char c, int* nl, int* nh, float aspe, int posto, int grande) {  //questa funzione premette che la mossa sia valida
  float perc;
   
  mossa(l, h, tavola, (*posl), (*posh), c);
  system("clear");
  if (c=='w') {
    (*posh)+=1;
    if (tavola[(*posh)][(*posl)]==tavola[(*nh)][(*nl)]) (*nh)-=1;
    if (aspe>=0) {
      printTavola(l, h, tavola, grande);
      printf ("\t     \t  ^  \t\t  w\n\tMossa\n");
    }
  }
  if (c=='a') {
    (*posl)+=1;
    if (tavola[(*posh)][(*posl)]==tavola[(*nh)][(*nl)]) (*nl)-=1;
    if (aspe>=0) {
      printTavola(l, h, tavola, grande);
      printf ("\n\tMossa\t<    \t\ta    \n");
    }
  }
  if (c=='d') {
    (*posl)-=1;
    if (tavola[(*posh)][(*posl)]==tavola[(*nh)][(*nl)]) (*nl)+=1;
    if (aspe>=0) {
      printTavola(l, h, tavola, grande);
      printf ("\n\tMossa\t    >\t\t    d\n");
    }
  }
  if (c=='s') {
    (*posh)-=1;
    if (tavola[(*posh)][(*posl)]==tavola[(*nh)][(*nl)]) (*nh)+=1;
    if (aspe>=0) {
      printTavola(l, h, tavola, grande);
      printf ("\n\tMossa\t  v  \t\t  s  \n");
    }
  }
  if (aspe>=0) {
    printf("\n");
    if ((posto-1)/l<=h-3 && (posto-1)%l<=l-3 && h>2 && l>2) {
      printf ("Sto mettendo a posto %d\n", posto);
    }
    if ((posto-1)/l<=h-3 && (posto-1)%l==l-2 && h>2) {
      printf ("Sto mettendo a posto %d e %d\n", posto, posto+1);
    }
    if ((posto-1)/l==h-2 && (posto-1)%l<=l-3 && l>2) {
      printf ("Sto mettendo a posto %d e %d\n", posto, posto+l);
    }
    if ((posto-1)/l==h-2 && (posto-1)%l==l-2) {
      printf ("Sto mettendo a posto %d, %d e %d\n", posto, posto+1, posto+l);
    }
  }
  perc=(100*(float)posto)/((l*h)-1);
  if (posto>(l*(h-2))) perc=(100*(float)posto)/(l*(h-1));
  if (perc>99) perc=99;
  if (aspe>=0) printf ("\nCompletamento");
  else printf ("\nControllando che il puzzle sia possibile");
  printf (": %.0f%c\n", perc, '%');
  if (aspe>=0) usleep(lrintf(aspe*10)*10000);
}
/***************************************************************************/
void trovaNmosse(int l, int h, int tavola[][LMAX], int* nl, int* nh, int nmosse) {
  int i;
 
  for (i=0; i<l*h; i++) {
    if (tavola[i/l][i%l]==nmosse) {
      (*nl)=i%l;
      (*nh)=i/l;
    }
  }
}
/****************************************************************************/
void titulo() {
  system("clear");
    printf("\n");
    usleep (400000);
    printf ("\t||    ||    \n");
    printf ("\t||    ||    \n");
    printf ("\t||    ||    \n");
    printf ("\t||    ||=== \n\n");
    usleep (400000);
    printf ("\t||====  ||   ||===||  ||====  ||===||\n");
    printf ("\t||      ||   ||   ||  ||      ||   ||\n");
    printf ("\t||  =|| ||   ||   ||  ||      ||   ||\n");
    printf ("\t||===|| ||   ||===||  ||====  ||===||\n\n");
    usleep (400000);
    printf ("\t||==\\\\  ||====  ||    \n");
    printf ("\t||   \\\\ ||      ||    \n");
    printf ("\t||   || ||====  ||    \n");
    printf ("\t||   // ||      ||    \n");
    printf ("\t||==//  ||====  ||====\n\n");
    usleep (400000);
    printf ("\t  //==   ||=====\n");
    printf ("\t // ||   ||     \n");
    printf ("\t    ||   ||====\\\\\n");
    printf ("\t    ||         ||\n");
    printf ("\t  ==||==  =====//\n");
    usleep (2000000);
}
/*************************************************************************************/
void switchTasselli(int l,int h,int tavola[][LMAX]) {
  int s=0, ind=0, bad1, bad2, bad3, bad4, bam, bam1, bam2, i;
  char muov=0, num[8]="primo", num2[8]="secondo";
  do{
    bam=-5;
    do{
      system("clear");
      if (s!=0) {
    for (i=0; i<8; i++) {
      num[i]=num2[i];
    }
    printf ("Primo numero selezionato: %d\n", tavola[bam1/l][bam1%l]);
      }
      printf ("Selezionare il %s tassello da sostituire muovendoti tra le caselle utilizzando w, a, s e d come freccette.\n", num);
      printf ("\t  ^  \t\t  w\n");
      printf ("\t< v >\t\ta s d\n");
      printf ("Il numero momentaneo lo riconosci perchè è moltiplicato per %d e lo spazio sarà -%d (nota: non puoi scambiare lo spazio)\n", LMAX*HMAX, LMAX*HMAX);
      printf ("Per selezionare il numero premere \"o\" seguito da Invio\n\n\n");
 
      tavola[ind/l][ind%l]=tavola[ind/l][ind%l]*LMAX*HMAX;
      printTavola(l, h, tavola, 2);
      do {
    bad1=bad2=bad3=bad4=0;
    scanf("%c",&muov);
    if ((bad1=(muov!='w' && muov!='a' && muov!='s' && muov!='d' && muov!='o'))) printf ("Input errato, ripeti\n");
    if ((bad2=(muov!='o' && ((muov=='w' && (ind/l)==0) || (muov=='a' && (ind%l)==0) || (muov=='s' && (ind/l)==h-1) || (muov=='d' && (ind%l)==l-1))))) {
      printf ("Non puoi superare i bordi! Ripeti\n");
    }
    if ((bad3=(muov=='o' && bam1==ind))) {
      printf ("Non puoi sostituire una casella con se stessa!\n");
    }
    if ((bad4=muov=='o' && tavola[ind/l][ind%l]==-LMAX*HMAX)) printf ("Non puoi sostituire lo spazio!\n");
    if (muov=='o' && !(bad4  || bad2 || bad3 || bad1)) {
      bad1=bad2=bad3=bad4=0;
      bam=ind;
    }
      } while (bad1 || bad2 || bad3 || bad4);
      tavola[ind/l][ind%l]/=LMAX*HMAX;
      if (muov=='w') {
    ind-=l;
      }
      if (muov=='a') {
    ind-=1;
      }
      if (muov=='s') {
    ind+=l;
      }
      if (muov=='d') {
    ind+=1;
      }
    } while (muov!='o');
    s++;
    if (s==1) bam1=bam;
    else {
      bam2=tavola[bam1/l][bam1%l];
      tavola[bam1/l][bam1%l]=tavola[bam/l][bam%l];
      tavola[bam/l][bam%l]=bam2;
    }
  } while (s<2);
}
 
 /**************************************************************/
 
char scanner() {
	  char *frec, up[5]={0}, down[5]={0}, left[5]={0}, right[5]={0}, h=102;
	  int i, cond;

up[0]=down[0]=right[0]=left[0]=27;
up[1]=down[1]=right[1]=left[1]=91;
up[2]=65;
down[2]=66;
right[2]=67;
left[2]=68;

	frec =(char*)calloc(4, sizeof(char));
	for (i=0; i<3; i++) {
		frec[i]=getch();
		cond=(!i && (frec[0]=='w' || frec[0]=='a' || frec[0]=='s' || frec[0]=='d' || frec[0]==50 || frec[0]==52 || frec[0]==53 || frec[0]==54));
		if (cond) {
			if (frec[0]=='w' || frec[0]==50) h='w';
			else if (frec[0]=='a' || frec[0]==52) h='a';
			else if (frec[0]=='s' || frec[0]==53) h='s';
			else h='d';
			return h;
		}
		if (!i && frec[0]!=27) return 102;
	}
	
//	do {
//		scanf("%s", frec);
			if (!strcmp(frec, up)) h=119;
			else if (!strcmp(frec, down)) h=115;
			else if (!strcmp(frec, left)) h=97;
			else if (!strcmp(frec, right)) h=100;
			else h=102;
		
		return h;
//		printf ("frec= %s      h=%d    %c\n", frec, (int)h, h);
//		printf ("up=%s\ndown=%s\nleft=%s\nright=%s\nfrec=%s\n", up, down, left, right, frec);
//	} while (strcmp(frec, up) && strcmp(frec, down) && strcmp(frec, right) && strcmp(frec, left));
}

/***********************************************/

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

 
/* Legenda:
Variabili principali:
nmosse: il numero della casella che devo mettere a posto
posl: coordinata x della posizione dello spazio
posh: coordinata y della posizione dello spazio
nl: coordinata x della posizione del numero da mettere a posto
nh: coordinata y della posizione del numero da mettere a posto
l: larghezza della tavola
h: altezza della tavola
arrl: coordinata x di dove voglio lo spazio
arrh: coordinata y di dove voglio lo spazio
aspe: decimi di secondo della mossa
permin: è l'ultimo numero che non può essere mosso durante una serie di mosse (diverso da nmosse)
posto: mi serve per printare "Sto mettendo a posto..."
err1: il primo numero che non è al suo posto
err2: il secondo numero che non è al suo posto
 
Funzioni:
titulo: stampa il titolo all'inizio
numeriMan: per inserire manualmente i numeri
printTavola: stampa la tavola
numeriRand: inserisce i numeri casualmente
checkEnd: controlla che il gioco sia finito o se non è risolvibile (riconoscendo le 2 caselle scambiate)
giocaUser: gioca l'utente
giocaComp: gioca il computer
mossa: principalmente riceve in input il carattere (w, a, s o d) e modifica la tavola (o avverte che la mossa non è possibile)
avvicinaSpazio: prende in input la posizione di dove si vuole lo spazio e fa le mosse giuste per arrivarci stando attento a non spostare i tasselli che non deve muovere
mettiqui: prende in input la posizione di dove si vuole un preciso tassello e fa le mosse giuste per arrivarci stando attento a non spostare i tasselli che non deve muovere
mossaGen: simile a "mossa" ma in più stampa che cosa sta mettendo a posto in quel momento, la percentuale di completamento, ecc.
trovaNmosse: trova le coordinate x e y di un tassello nella tavola
switchTasselli: l'utente scambia manualmente due tasselli (quando il puzzle non è risolvibile)
*/
