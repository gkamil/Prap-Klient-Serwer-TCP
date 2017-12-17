#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista
{
       struct lista *nastepny, *poprzedni;
       int wartosc;
}elementListy;

struct lista *pierwszy = NULL;
struct lista *ostatni  = NULL;

void wypiszListe()
{
     struct lista *element=pierwszy;
     while(element!=NULL)
     {
         printf("%d\n",element->wartosc);
         element = element -> nastepny;
     }
     return;
}

void zapiszListe(char *string)
{
     struct lista *element=pierwszy;
     while(element!=NULL)
     {
    	 sprintf((string+(int)strlen(string)-1), " %d\n",element->wartosc);
         element = element -> nastepny;
     }
     return;
}

void dodajElement(int liczba)
{
     if(ostatni == NULL)//pierwszy
     {
         pierwszy= malloc (sizeof(elementListy));
         ostatni = pierwszy;
         pierwszy-> wartosc = liczba;
         pierwszy-> nastepny = NULL;
         pierwszy-> poprzedni = NULL;
     }
     else
     {
         struct lista *stary, *nowy;
         stary=ostatni;
         nowy=malloc(sizeof(elementListy));

         nowy->wartosc = liczba;
         nowy->nastepny = NULL;
         nowy->poprzedni = stary;

         ostatni->nastepny=nowy;
         ostatni=nowy;
     }
     return;
}

void usunElement(struct lista *elementy)
{
     if(elementy!=NULL)
     {
        struct lista *poprzedni = elementy -> poprzedni;
        struct lista *nastepny  = elementy -> nastepny;

        if(poprzedni == NULL)//pierwszy
        {
           pierwszy = elementy -> nastepny;
        }
        else//niepierwszy
        {
           poprzedni -> nastepny = elementy -> nastepny;
        }

        if(nastepny == NULL)//ostatni
        {
           ostatni = elementy -> poprzedni;
        }
        else//nieostatni
        {
           nastepny -> poprzedni = elementy -> poprzedni;
        }
        free(elementy);
      }
      return;
}

int sumaListy(void)
{
     struct lista *element=pierwszy;
     int suma = 0;
     while(element!=NULL)
     {
         suma = suma + element->wartosc;
         element = element -> nastepny;
     }
     return suma;
}

int roznicaListy(void)
{
     struct lista *element = pierwszy;
     int roznica = 0;
     if(element!=NULL)
     {
         roznica = roznica + element->wartosc;
         element = element -> nastepny;
     }
     while(element!=NULL)
     {
         roznica = roznica - element->wartosc;
         element = element -> nastepny;
     }
     return roznica;
}

void sortujRosnaco(void)
{
     struct lista *poprzedni = NULL;
     struct lista *nastepny  = NULL;
     struct lista *element1  = pierwszy;
     struct lista *element2  = NULL;
     struct lista *element   = pierwszy;
     int dlugoscListy = 0, ostatniElement, i;
     while(element!=NULL)
     {
    	 dlugoscListy++;
    	 element = element -> nastepny;
     }
     ostatniElement = dlugoscListy-1;
     if(dlugoscListy < 2)//czy jest 1. element
    	 return;
     else
    	 element2  = element1 -> nastepny;

     while(ostatniElement > 0)
     {
    	 element1 = pierwszy;
    	 element2 = pierwszy->nastepny;
    	 for(i=0; i<ostatniElement; i++)
         {
    		if(element1->wartosc > element2->wartosc)
    		{
    			poprzedni = element1->poprzedni;
    			nastepny  = element2->nastepny;
    			element1->poprzedni = element2;
    			element2->nastepny  = element1;
    			element1->nastepny  = nastepny;
    			element2->poprzedni = poprzedni;
    			if(poprzedni == NULL)//pierwszy
    				pierwszy = element2;
    			else//niepierwszy
    				poprzedni->nastepny = element2;
    			if(nastepny == NULL)//ostatni
    			    ostatni = element1;
    			else
    				nastepny->poprzedni = element1;
    			element2 = element1->nastepny;
    		}
    		else
    		{
    			element1 = element1->nastepny;
    			element2 = element2->nastepny;
    		}
         }
    	 ostatniElement--;
     }
}

void sortujMalejaco(void)
{
     struct lista *poprzedni = NULL;
     struct lista *nastepny  = NULL;
     struct lista *element1  = pierwszy;
     struct lista *element2  = NULL;
     struct lista *element   = pierwszy;
     int dlugoscListy = 0, ostatniElement, i;
     while(element!=NULL)
     {
    	 dlugoscListy++;
    	 element = element -> nastepny;
     }
     ostatniElement = dlugoscListy-1;
     if(dlugoscListy < 2)//czy jest 1. element
    	 return;
     else
    	 element2  = element1 -> nastepny;

     while(ostatniElement > 0)
     {
    	 element1 = pierwszy;
    	 element2 = pierwszy->nastepny;
    	 for(i=0; i<ostatniElement; i++)
         {
    		if(element1->wartosc < element2->wartosc)
    		{
    			poprzedni = element1->poprzedni;
    			nastepny  = element2->nastepny;
    			element1->poprzedni = element2;
    			element2->nastepny  = element1;
    			element1->nastepny  = nastepny;
    			element2->poprzedni = poprzedni;
    			if(poprzedni == NULL)//pierwszy
    				pierwszy = element2;
    			else//niepierwszy
    				poprzedni->nastepny = element2;
    			if(nastepny == NULL)//ostatni
    			    ostatni = element1;
    			else
    				nastepny->poprzedni = element1;
    			element2 = element1->nastepny;
    		}
    		else
    		{
    			element1 = element1->nastepny;
    			element2 = element2->nastepny;
    		}

         }
    	 ostatniElement--;
     }
}


