/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   plateau.h
 * Author: arthur.vanier
 *
 * Created on 10 janvier 2019, 12:51
 */
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<math.h>

#ifndef PLATEAU_H
#define PLATEAU_H

#define TAILLENOM 20
#define J1CAR 49
#define J2CAR 50
typedef struct Perso Perso;

typedef struct Coord{
    int x;
    int y;
}Coord;

struct Perso{
    int hp;
    int pm;
    int mana;
    int objet;
    char nom[TAILLENOM];
    char nSort1[TAILLENOM];
    char nSort2[TAILLENOM];
    char nSort3[TAILLENOM];
    char nomObjet[TAILLENOM];
    void (*ptr1)(Perso*,char**,char);
    void (*ptr2)(Perso*,char**,char);
    void (*ptr3)(Perso*,char**,char);
    void (*ptr4)(Perso*,char**,char);
};

void jeuPlateau(char joueur1[TAILLENOM],char joueur2[TAILLENOM]);
void plateauLeJeu(char joueur1[TAILLENOM],char joueur2[TAILLENOM]);
void affichePlateau(char **plateau,Perso J,char joueur[TAILLENOM]);
void selectionDesChampions(Perso tabJ[2],char joueur1[TAILLENOM] ,char joueur2[TAILLENOM]);
Coord positionJoueur(char **plateau,char joueur);
void deplacementJoueur(Coord maPos,char **plateau,Coord p);
void initPlateau(char** plateau);
void afficheScores();

//-----------------------------------------------------------------------------// CHAMPIONS

int varvick(Perso tabJ[2],int i);
void varvickS1(Perso tabJ[2],char** plateau,char joueurCible);
void varvickS2(Perso tabJ[2],char** plateau,char joueurCible);
void varvickS3(Perso tabJ[2],char** plateau,char joueurCible);

int zobalito(Perso tabJ[2],int i);
void zobalitoS1(Perso tabJ[2],char** plateau,char joueurCible);
void zobalitoS2(Perso tabJ[2],char** plateau,char joueurCible);
void zobalitoS3(Perso tabJ[2],char** plateau,char joueurCible);

//-----------------------------------------------------------------------------// OBJETS

int potionGuerisonInit(Perso tabJ[2],int i);
void potionGuerison(Perso tabJ[2],char** plateau,char joueurCible);

int potionManaInit(Perso tabJ[2],int i);
void potionMana(Perso tabJ[2],char** plateau,char joueurCible);
#endif /* PLATEAU_H */

