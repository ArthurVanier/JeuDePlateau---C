/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: arthur.vanier
 *
 * Created on 10 janvier 2019, 12:47
 */

#include "plateau.h"

/*
 * 
 */
int main(int argc, char** argv) {
    char joueur1[TAILLENOM]="tut",joueur2[TAILLENOM]="tony";
    jeuPlateau(joueur1,joueur2);
    return (EXIT_SUCCESS);
}

