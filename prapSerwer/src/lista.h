/*
 * lista.h
 *
 *  Created on: 15 gru 2017
 *      Author: kamil
 */

#ifndef LISTA_H_
#define LISTA_H_

struct lista
{
       struct lista *nastepny, *poprzedni;
       int wartosc;
}elementListy;

void wypiszListe();
void zapiszListe(char *string);
void dodajElement(int liczba);
void usunElement(struct lista *elementy);
int sumaListy(void);
int roznicaListy(void);
void sortujRosnaco(void);
void sortujMalejaco(void);

#endif /* LISTA_H_ */
