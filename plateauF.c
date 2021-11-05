/*
 * 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"plateau.h"

void jeuPlateau(char joueur1[TAILLENOM],char joueur2[TAILLENOM]){
    int b=0,n=0,m=0;
    srand(time(NULL));
    while(b==0){
        system("cls");
        printf("            RACAILLE ROYALE\n\n1- Jouer\n2- Historique des scores\n3- Regles\n4- Quitter\n");
        scanf("%d",&m);
        switch(m){
            case 1:
                plateauLeJeu(joueur1,joueur2);
                break;
            case 2:
                afficheScores();
                break;
                break;
            case 3:
                // REGLES
                break;   
            case 4:
                b=1;
                break;
            default:
                printf("ERREUR MENU PRINCIPALE");   
        }
    }
}

void plateauLeJeu(char joueur1[TAILLENOM],char joueur2[TAILLENOM]){
    int i=0,b=0,b2=0,inv=0,n=0,n2=0,t,temppm=0,tempmana;
    char **plateau=malloc(sizeof(char*)*7);
    char lettre=0;
    for(i=0;i<10;i++) plateau[i]=malloc(sizeof(char)*7);
    Coord p,maPos;
    Perso tabJ[2];
    FILE* fichierScores=NULL;
    initPlateau(plateau);
    selectionDesChampions(tabJ,joueur1,joueur2);
    inv=(rand()%2==1) ? 1 : 2;
    while(tabJ[0].hp>0 && tabJ[1].hp>0){
        b=0;
        if(inv==1){
            temppm=tabJ[0].pm;
            tempmana=tabJ[0].mana;
            while(b==0){
                system("cls");
                affichePlateau(plateau,tabJ[0],joueur1);
                printf("Menu :\n1- Sort     2- Deplacement\n3- Objet     4-Finir son tour\n");
                scanf("%d",&n);
                system("cls");
                affichePlateau(plateau,tabJ[0],joueur1);
                switch(n){
                    case 1:
                        b2=0;
                        printf("1- %s\n2- %s\n3- %s\n4-Quitter\n",tabJ[0].nSort1,tabJ[0].nSort2,tabJ[0].nSort3);
                        while(b2==0){
                            scanf("%d",&n2);
                            if(n2==1) (*tabJ[0].ptr1)(tabJ,plateau,J2CAR);
                            else if(n2==2) (*tabJ[0].ptr2)(tabJ,plateau,J2CAR);
                            else if(n2==3) (*tabJ[0].ptr3)(tabJ,plateau,J2CAR);
                            else if(n2==4) b2=1;
                            else printf("Erreur nombre saisi");                       
                        }
                        break;
                    case 2:
                        printf("Entrer une cellule Ligne puis colonne\n");
                        scanf("%d%d",&p.x,&p.y);
                        maPos=positionJoueur(plateau,J1CAR);
                        t=abs(maPos.x-p.x)+abs(maPos.y-p.y);
                        if(t<=tabJ[0].pm && plateau[p.x][p.y]!=J2CAR){
                            deplacementJoueur(maPos,plateau,p);
                            tabJ[0].pm-=t;
                            printf("\nDeplacement effectue\n");
                        }
                        else {
                            if(plateau[p.x][p.y]==J2CAR) printf("Deplacement impossible la cellule cible n'est pas vide !\n");
                            else printf("\nPm insuffisant !\n");    
                        }
                        fflush(stdin);
                        scanf("%c",&lettre);
                        break;
                    case 3:
                        printf("Objet equipe: %s\nQuantite restante: %d\n",tabJ[0].nomObjet,tabJ[0].objet);
                        printf("\n1- Utiliser\n0- Quitter\n");
                        scanf("%d",&n2);
                        if(n2==1){ 
                            if(tabJ[0].objet!=0) (*tabJ[0].ptr4)(tabJ,plateau,J2CAR);
                            else printf("Plus de %s !\n",tabJ[0].nomObjet);
                            fflush(stdin);
                            scanf("%c",&lettre);
                        }
                        
                        break;
                    case 4:
                        b=1;
                        inv=2;
                        tabJ[0].pm=temppm;
                        tabJ[0].mana=tempmana;
                        break;
                    default:
                        printf("Erreur nombre saisi\n");
                        break;
                }
            }
        }
        else{
            temppm=tabJ[1].pm;
            tempmana=tabJ[1].mana;
            while(b==0){
                system("cls");
                affichePlateau(plateau,tabJ[1],joueur2);
                printf("Menu :\n1- Sort     2- Deplacement\n3- Objet     4-Finir son tour\n");
                scanf("%d",&n);
                system("cls");
                affichePlateau(plateau,tabJ[1],joueur2);
                switch(n){
                    case 1:
                        b2=0;
                        printf("1- %s\n2- %s\n3- %s\n4-Quitter",tabJ[1].nSort1,tabJ[1].nSort2,tabJ[1].nSort3);
                        while(b2==0){
                            scanf("%d",&n2);
                            if(n2==1) (*tabJ[1].ptr1)(tabJ,plateau,J1CAR);
                            else if(n2==2) (*tabJ[1].ptr2)(tabJ,plateau,J1CAR);
                            else if(n2==3) (*tabJ[1].ptr3)(tabJ,plateau,J1CAR);
                            else if(n2==4) b2=1;
                            else printf("Erreur nombre saisi\n");                       
                        }
                        break;
                    case 2:
                        printf("Entrer une cellule Ligne puis colonne\n");
                        scanf("%d%d",&p.x,&p.y);
                        maPos=positionJoueur(plateau,J2CAR);
                        t=abs(maPos.x-p.x)+abs(maPos.y-p.y);
                        if(t<=tabJ[1].pm && plateau[p.x][p.y]!=J1CAR){
                            deplacementJoueur(maPos,plateau,p);
                            tabJ[1].pm-=t;
                            printf("\nDeplacement effectue\n");
                        }
                        else {
                            if(plateau[p.x][p.y]==J1CAR) printf("Deplacement impossible la cellule cible n'est pas vide !\n");
                            else printf("\nPm insuffisant !\n");
                        }
                        fflush(stdin);
                        scanf("%c",&lettre);
                        break;
                    case 3:
                        printf("Objet equipe: %s\nQuantite restante: %d\n",tabJ[1].nomObjet,tabJ[1].objet);
                        printf("\n1- Utiliser\n0- Quitter\n");
                        scanf("%d",&n2);
                        if(n2==1){ 
                            if(tabJ[1].objet!=0) (*tabJ[1].ptr4)(tabJ,plateau,J1CAR);
                            else printf("Plus de %s !\n",tabJ[1].nomObjet);
                            fflush(stdin);
                            scanf("%c",&lettre);
                        }
                        break;
                    case 4:
                        b=1;
                        inv=1;
                        tabJ[1].pm=temppm;
                        tabJ[1].mana=tempmana;
                        break;
                    default:
                        printf("Erreur nombre saisi\n");
                        break;
                }
            }
        }
    }
    system("cls");
    if(tabJ[0].hp<1){
        printf("%s l'emporte!\n",joueur1);
        fichierScores=fopen("Scores.txt","r+");
        fseek(fichierScores,0,SEEK_END);
        fprintf(fichierScores,"%s(%s) vs %s(%s) (1 : 0)\n",joueur1,tabJ[0].nom,joueur2,tabJ[1].nom);
        rewind(fichierScores);
        fclose(fichierScores);
    }
    else{
        printf("%s l'emporte!\n",joueur2);
        fichierScores=fopen("Scores.txt","r+");
        fseek(fichierScores,0,SEEK_END);
        fprintf(fichierScores,"%s(%s) vs %s(%s) (0 : 1)\n",joueur1,tabJ[0].nom,joueur2,tabJ[1].nom);
        rewind(fichierScores);
        fclose(fichierScores);
    }
    printf("Pour revenir au men principale appuyer sur une touche\n");
    fflush(stdin);
    scanf("%c",&lettre);
}

void selectionDesChampions(Perso tabJ[2],char joueur1[TAILLENOM],char joueur2[TAILLENOM]){
    int i=0,b=0,n=0;
    char lettre=0;
    char chaine[26];
    FILE *champions=NULL,*objet=NULL;
    champions=fopen("Champions.txt","r");
    objet=fopen("Objets.txt","r");
    for(i=0;i<2;i++){
        b=0;
        while(b==0){
            system("cls");
            if(i==0)printf("        %s a vous de choisir un champion !\n\n",joueur1);
            else printf("        %s a vous de choisir un champion !\n\n",joueur2);
            while(fgets(chaine,26,champions)!=NULL) printf("%s",chaine);
            printf("\n");
            rewind(champions);
            printf("Entrer un nombre :\n");
            scanf("%d",&n);
            system("cls");
            switch(n){
                case 1:
                    b=varvick(tabJ,i);
                    if(b==1) printf("Vous avez Selectionnez Varvick !\nAppuyez sur une touche pour continuer");
                    fflush(stdin);
                    scanf("%c",&lettre);
                    break;
                case 2:
                    b=zobalito(tabJ,i);
                    if(b==1) printf("Vous avez selectionnez Zobalito\nAppuyez sur uen touche pour continuer");
                    fflush(stdin);
                    scanf("%c",&lettre);
                default:
                    printf("Erreur nombre saisie!");
                    break;
            }
        }
        system("cls");
        b=0;
        while(b==0){
            if(i==0)printf("       et maintenant %s choisissez un Objet !\n\n",joueur1);
            else printf("        et maintenant %s choisissez un Objet !\n\n",joueur2);
            while(fgets(chaine,26,objet)!=NULL) printf("%s",chaine);
            printf("\n");
            rewind(objet);
            printf("Entrer un nombre :");
            scanf("%d",&n);
            system("cls");
            switch(n){
                case 1:
                    b=potionGuerisonInit(tabJ,i);
                    if(b==1) printf("Vous avez Selectionnez Potion de guerison!\nAppuyer sur une touche pour continuer\n");
                    fflush(stdin);
                    scanf("%c",&lettre);
                    break;
                case 2:
                    b=potionManaInit(tabJ,i);
                    if(b==1) printf("Vous avez selectionnez Potion de mana !\nAppuyer sur une touche pour continuer\n");
                    fflush(stdin);
                    scanf("%c",&lettre);
                default:
                    printf("Erreur nombre saisie!");
            }
        }
    }
    fclose(champions);
    fclose(objet);
}


void affichePlateau(char **plateau,Perso J,char joueur[TAILLENOM]){
    int i=0,j=0;
    printf("%10s %s   hp=%d Mana=%d Pm=%d\n",J.nom,joueur,J.hp,J.mana,J.pm);
    printf("\n\n      0   1   2   3   4   5   6\n");
    printf("    +---+---+---+---+---+---+---+\n");
    for(i=0;i<7;i++){
        printf("  %d |",i);
        for(j=0;j<7;j++) {
            printf(" %c |",plateau[i][j]);
        }
        printf("\n    +---+---+---+---+---+---+---+\n");
    }
    printf("\n");
}

Coord positionJoueur(char **plateau,char joueur){
    int i=0,j=0;
    Coord p;
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(plateau[i][j]==joueur){
                p.x=i;
                p.y=j;
            } 
        }
    }
    return p;
}

void deplacementJoueur(Coord maPos,char **plateau,Coord p){
    plateau[p.x][p.y]=plateau[maPos.x][maPos.y];
    plateau[maPos.x][maPos.y]=0;  
}

void initPlateau(char** plateau){
    int i=0,j=0,inv=0;
    inv=rand()%2;
    if(inv==0){
        for(i=0;i<7;i++){
            for(j=0;j<7;j++) plateau[i][j]=(i==6 && j==0) ? plateau[i][j]=J1CAR : (i==0 && j==6) ? J2CAR : 0;
        }
    }
    else{
        for(i=0;i<7;i++){
            for(j=0;j<7;j++) plateau[i][j]=(i==6 && j==0) ? plateau[i][j]=J2CAR : (i==0 && j==6) ? J1CAR : 0;
        }
    }
}

void afficheScores(){
    char lettre;
    char chaine[26];
    FILE* fichier=NULL;
    fichier=fopen("Scores.txt","r");
    system("cls");
    while(fgets(chaine,26,fichier)!=NULL) printf("%s",chaine);
    printf("Pour revenir au menu principale appuer sur une touche\n");
    fflush(stdin);
    scanf("%c",&lettre);
}

//-----------------------------------------------------------------------------//  CHAMPIONS

int varvick(Perso tabJ[2],int i){
    int n=0;
    printf("    Varvick :\n\nhp:23 | pm:4 |mana:6\n\n");
    printf("Sort 1: Coup de griffe(coute:2)(porte:1) infige 2 points de degats\n");
    printf("Sort 2: Morsure vampirique(coute:4)(Porte:1) inflige 2 de degats et vole 2 point de vies\n");
    printf("Sort 3: Saut eclair(coute:6)(porte:3)(En ligne seulement) se teleporte sur la case choisie\n"
            "si c'est un enemi il passe derriere lui et lui inflige 3 point de degats\n\n");
    printf("0- Retour a la selection d'un champion\n1- Selectionner ce champion\n");
    scanf("%d",&n);
    if(n==1){
        tabJ[i].hp=23;
        tabJ[i].pm=4;
        tabJ[i].mana=6;
        strcpy(tabJ[i].nom,"Varvick");
        strcpy(tabJ[i].nSort1,"Coup de griffe");
        strcpy(tabJ[i].nSort2,"Morsure vampirique");
        strcpy(tabJ[i].nSort3,"Saut eclair");
        tabJ[i].ptr1=varvickS1;
        tabJ[i].ptr2=varvickS2;
        tabJ[i].ptr3=varvickS3;
    }
    return n;
}

void varvickS1(Perso tabJ[2],char** plateau,char joueurCible){
    int joueurSelec;
    joueurSelec=(joueurCible==49) ? 1 : 0;
    Coord maPos,enemyPos;
    enemyPos=positionJoueur(plateau,joueurCible);
    joueurCible=(joueurCible==J1CAR) ? J2CAR : J1CAR;
    maPos=positionJoueur(plateau,joueurCible);
    joueurCible=(joueurCible==J1CAR) ? J2CAR : J1CAR;
    if(abs(maPos.x-enemyPos.x)+abs(maPos.y-enemyPos.y)==1 && tabJ[joueurSelec].mana>1){
        tabJ[joueurSelec].mana-=2;
        joueurSelec=(joueurSelec==0) ? 1 : 0;
        tabJ[joueurSelec].hp-=2;
        printf("Succefull hit, joueur %c -2 hp\n",joueurCible);
    }
    else {
        if(tabJ[joueurSelec].mana<2) printf("Mana insuffisant !\n");
        else printf("Coup rate,Coup en mana annule\n");
    }
}

void varvickS2(Perso tabJ[2],char** plateau,char joueurCible){
    int joueurSelec;
    joueurSelec=(joueurCible==49) ? 1 : 0;
    Coord maPos,enemyPos;
    enemyPos=positionJoueur(plateau,joueurCible);
    joueurCible=(joueurCible==J1CAR) ? J2CAR : J1CAR;
    maPos=positionJoueur(plateau,joueurCible);
    joueurCible=(joueurCible==J1CAR) ? J2CAR : J1CAR;
    if(abs(maPos.x-enemyPos.x)+abs(maPos.y-enemyPos.y)==1 && tabJ[joueurSelec].mana>3){
        tabJ[joueurSelec].mana-=4;
        tabJ[joueurSelec].hp+=2;
        joueurSelec=(joueurSelec==0) ? 1 : 0;
        tabJ[joueurSelec].hp-=4;
        joueurSelec=(joueurSelec==0) ? 1 : 0;
        printf("Succefull hit, joueur %c -4 hp et joueur%d +2 hp\n",joueurCible,joueurSelec+1);
    }
    else{
        if(tabJ[joueurSelec].mana<4) printf("Mana insuffisant !\n");
        else printf("Coup rate,Coup en mana annule\n");
    }
}

void varvickS3(Perso tabJ[2],char** plateau,char joueurCible){
    int joueurSelec;
    joueurSelec=(joueurCible==49) ? 1 : 0;
    Coord maPos,enemyPos,temp;
    enemyPos=positionJoueur(plateau,joueurCible);
    joueurCible=(joueurCible==J1CAR) ? J2CAR : J1CAR;
    maPos=positionJoueur(plateau,joueurCible);
    joueurCible=(joueurCible==J1CAR) ? J2CAR : J1CAR;
    if(abs(maPos.x-enemyPos.x)+abs(maPos.y-enemyPos.y)>=0 && abs(maPos.x-enemyPos.x)+abs(maPos.y-enemyPos.y)<4 && tabJ[joueurSelec].mana>5){
        if(maPos.x==enemyPos.x){
            if(maPos.y<enemyPos.y){
                if(enemyPos.y+1<7){
                    temp.x=enemyPos.x;
                    temp.y=enemyPos.y+1;
                    deplacementJoueur(maPos,plateau,temp);
                    tabJ[joueurSelec].mana-=6;
                    joueurSelec=(joueurSelec==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=3;
                    printf("Succefull hit , joueur%d -3 hp\n",joueurSelec)+1;
                }
                else{
                    
                    temp.x=enemyPos.x;
                    temp.y=enemyPos.y-1;
                    deplacementJoueur(maPos,plateau,temp);
                    tabJ[joueurSelec].mana-=6;
                    joueurSelec=(joueurCible==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=3;
                    printf("Succefull hit , joueur%d -3 hp\n",joueurSelec)+1;
                }
            }
            else{
                if(enemyPos.y-1>=0){
                    temp.x=enemyPos.x;
                    temp.y=enemyPos.y-1;
                    deplacementJoueur(maPos,plateau,temp);
                    tabJ[joueurSelec].mana-=6;
                    joueurSelec=(joueurCible==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=3;
                    printf("Succefull hit , joueur%d -3 hp \n",joueurSelec)+1;
                }
                else{
                    temp.x=enemyPos.x;
                    temp.y=enemyPos.y+1;
                    deplacementJoueur(maPos,plateau,temp);
                    tabJ[joueurSelec].mana-=6;
                    joueurSelec=(joueurCible==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=3;
                    printf("Succefull hit , joueur%d -3 hp\n",joueurSelec+1);
                }
            }
        }
        else if(maPos.y==enemyPos.y){
            if(maPos.x>enemyPos.x){
                if(enemyPos.x-1>=0){
                    temp.x=enemyPos.x-1;
                    temp.y=enemyPos.y;
                    deplacementJoueur(maPos,plateau,temp);
                    tabJ[joueurSelec].mana-=6;
                    joueurSelec=(joueurCible==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=3;
                    printf("Succefull hit , joueur%d -3 hp\n",joueurSelec+1);
                }
                else{
                    temp.x=enemyPos.x+1;
                    temp.y=enemyPos.y;
                    deplacementJoueur(maPos,plateau,temp);
                    tabJ[joueurSelec].mana-=6;
                    joueurSelec=(joueurCible==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=3;
                    printf("Succefull hit , joueur%d -3 hp\n",joueurSelec+1);
                }
            }
            else{
                if(enemyPos.x+1<7){
                    temp.x=enemyPos.x+1;
                    temp.y=enemyPos.y;
                    deplacementJoueur(maPos,plateau,temp);
                    tabJ[joueurSelec].mana-=6;
                    joueurSelec=(joueurCible==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=3;
                    printf("Succefull hit , joueur%d -3 hp\n",joueurSelec+1);
                }
                else{
                    temp.x=enemyPos.x-1;
                    temp.y=enemyPos.y;
                    deplacementJoueur(maPos,plateau,temp);
                    tabJ[joueurSelec].mana-=6;
                    joueurSelec=(joueurCible==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=3;
                    printf("Succefull hit , joueur%d -3 hp\n",joueurSelec+1);
                }
            }
        }
        else printf("Erreur ligne de vue\n");
    }
    else{
        if(tabJ[joueurSelec].mana<6) printf("Mana insuffisant !\n");
        else printf("Erreur porte\n");
    }
}

//                        -----------------------------                        //

int zobalito(Perso tabJ[2],int i){
    int n=0;
    printf("    Zobalito  :\n\nhp:28 | pm:3 |mana:6\n\n");
    printf("Sort 1: Chasse(coute: 2)(porte: 1) inflige 1 point de degat et repousse "
    "de une case, si le joueur est contre un mur il subit 3 point de degat supplementaire\n");
    printf("Sort 2: Detour(coute: 2)(porte: 2)Inverse les position des joueurs\n");
    printf("Sort 3: Attirance(coute: 4)(porte: 4)Attire le joueur adversaire au corp a corp\n\n");
    printf("0- Retour a la selection\n1- Choisir ce champion\n");
    scanf("%d",&n);
    if(n==1){
        tabJ[i].hp=26;
        tabJ[i].mana=6;
        tabJ[i].pm=3;
        strcpy(tabJ[i].nom,"Zobalito");
        strcpy(tabJ[i].nSort1,"chasse");
        strcpy(tabJ[i].nSort2,"Detour");
        strcpy(tabJ[i].nSort3,"Attirance");
        tabJ[i].ptr1=zobalitoS1;
        tabJ[i].ptr2=zobalitoS2;
        tabJ[i].ptr3=zobalitoS3;
    }
    return n;
}

void zobalitoS1(Perso tabJ[2],char** plateau,char joueurCible){
    int joueurSelec;
    Coord maPos,enemyPos,temp;
    joueurSelec=(joueurCible==49) ? 1 : 0;
    enemyPos=positionJoueur(plateau,joueurCible);
    joueurCible=(joueurCible==49) ? 50 : 49;
    maPos=positionJoueur(plateau,joueurCible);
    if(abs(maPos.x-enemyPos.x)+abs(maPos.y-enemyPos.y)==1 && tabJ[joueurSelec].mana>1){
        if(maPos.x==enemyPos.x){
            if(maPos.y-enemyPos.y<0){
                if(enemyPos.y+1<7){
                    temp.x=enemyPos.x;
                    temp.y=enemyPos.y+1;
                    deplacementJoueur(enemyPos,plateau,temp);
                    tabJ[joueurSelec].mana-=2;
                    joueurSelec=(joueurSelec==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=1;
                    printf("Succefull hit, joueur%d -1 hp\n",joueurSelec+1);
                }
                else{
                    tabJ[joueurSelec].mana-=2;
                    joueurSelec=(joueurSelec==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=4;
                    printf("Succefull hit, joueur%d -4 hp\n",joueurSelec+1);
                }
            }
            else{
                if(enemyPos.y-1>=0){
                    temp.x=enemyPos.x;
                    temp.y=enemyPos.y-1;
                    deplacementJoueur(enemyPos,plateau,temp);
                    tabJ[joueurSelec].mana-=2;
                    joueurSelec=(joueurSelec==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=1;
                    printf("Succefull hit, joueur%d -1 hp\n",joueurSelec+1);
                }
                else{
                    tabJ[joueurSelec].mana-=2;
                    joueurSelec=(joueurSelec==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=4;
                    printf("Succefull hit, joueur%d -4 hp\n",joueurSelec+1);
                }
            }
        }
        else{
            if(maPos.x-enemyPos.x<0){
                if(enemyPos.x+1<7){
                    temp.x=enemyPos.x+1;
                    temp.y=enemyPos.y;
                    deplacementJoueur(enemyPos,plateau,temp);
                    tabJ[joueurSelec].mana-=2;
                    joueurSelec=(joueurSelec==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=1;
                    printf("Succefull hit, joueur%d -1hp\n",joueurSelec+1);
                }
                else{
                    tabJ[joueurSelec].mana-=2;
                    joueurSelec=(joueurSelec==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=4;
                    printf("Succefull hit, joueur%d -4 hp\n",joueurSelec+1);
                }
            }
            else{
                if(enemyPos.x-1>=0){
                    temp.x=enemyPos.x-1;
                    temp.y=enemyPos.y;
                    deplacementJoueur(enemyPos,plateau,temp);
                    tabJ[joueurSelec].mana-=2;
                    joueurSelec=(joueurSelec==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=1;
                    printf("Succefull hit, joueur%d -1 hp\n",joueurSelec+1);
                }
                else{
                    tabJ[joueurSelec].mana-=2;
                    joueurSelec=(joueurSelec==0) ? 1 : 0;
                    tabJ[joueurSelec].hp-=4;
                    printf("Succefull hit, joueur%d -4 hp\n",joueurSelec+1);
                }
            }
        }
    }
    else{
        if(tabJ[joueurSelec].mana<2) printf("Mana insuffisant\n");
        else printf("Erreur porte\n");
    } 
        
}

void zobalitoS2(Perso tabJ[2],char** plateau,char joueurCible){
    int joueurSelec;
    Coord maPos,enemyPos;
    joueurSelec=(joueurCible==J1CAR) ? 1 : 0;
    enemyPos=positionJoueur(plateau,joueurCible);
    joueurCible=(joueurCible==J1CAR) ? J2CAR : J1CAR;
    maPos=positionJoueur(plateau,joueurCible);
    plateau[maPos.x][maPos.y]=plateau[enemyPos.x][enemyPos.y];
    if(abs(maPos.x-enemyPos.x)+abs(maPos.y-enemyPos.y)<3 && tabJ[joueurSelec].mana>1){
        if(plateau[maPos.x][maPos.y]==J1CAR) plateau[enemyPos.x][enemyPos.y]=J2CAR;
        else plateau[enemyPos.x][enemyPos.y]=J1CAR;
        tabJ[joueurSelec].mana-=2;
        printf("Detour effectue\n");
    }
    else {
        if(tabJ[joueurSelec].mana<2) printf("Mana insuffisant\n");
        else printf("Erreur porte\n");
    }
}

void zobalitoS3(Perso tabJ[2],char** plateau,char joueurCible){
    int joueurSelec;
    Coord maPos,enemyPos,temp;
    joueurSelec=(joueurCible==J1CAR) ? 1 : 0;
    enemyPos=positionJoueur(plateau,joueurCible);
    joueurCible=(joueurCible==J1CAR) ? J2CAR : J1CAR;
    maPos=positionJoueur(plateau,joueurCible);
    if(abs(maPos.x-enemyPos.x)+abs(maPos.y-enemyPos.y)<5){
        if(maPos.x==enemyPos.x){
            if(maPos.y-enemyPos.x<0){
                temp.x=maPos.x;
                temp.y=maPos.y+1;
                deplacementJoueur(enemyPos,plateau,temp);
                tabJ[joueurSelec].mana-=4;
                printf("Attire avec succes\n");
            }
            else{
                temp.x=maPos.x;
                temp.y=maPos.y-1;
                deplacementJoueur(enemyPos,plateau,temp);
                tabJ[joueurSelec].mana-=4;
                printf("Attire avec succes\n");
            }
        }
        else if(maPos.y==enemyPos.y){
            if(maPos.x-enemyPos.x<0){
                temp.x=maPos.x+1;
                temp.y=maPos.y;
                deplacementJoueur(enemyPos,plateau,temp);
                tabJ[joueurSelec].mana-=4;
                printf("Attire avec succes\n");
            }
            else{
                temp.x=maPos.x-1;
                temp.y=maPos.y;
                deplacementJoueur(enemyPos,plateau,temp);
                tabJ[joueurSelec].mana-=4;
                printf("Attire avec succes\n");
            }
        }
        else printf("Erreur ligne de vue\n");
            
        
    }
    else{
        if(tabJ[joueurSelec].mana<2) printf("Mana insuffisant\n");
        else printf("Erreur porte\n");
    }
}

//-----------------------------------------------------------------------------// OBJET

int potionGuerisonInit(Perso tabJ[2],int i){
    int n=0;
   printf("Potion de guerison : Soigne 3 point de vie\nQuantite : 2\n\n1- Selectionner cet objet\n0- Retourner a la selection des objets\n");
   scanf("%d",&n);
   if(n==1) {
       tabJ[i].ptr4=potionGuerison;
       strcpy(tabJ[i].nomObjet,"Potion de guerison");
       tabJ[i].objet=2;
   }
   return n;    
}

void potionGuerison(Perso tabJ[2],char** plateau,char joueurCible){
    int joueurSelec;
    joueurSelec=(joueurCible==49) ? 1 : 0;
    tabJ[joueurSelec].objet-=1;
    tabJ[joueurSelec].hp+=3;
    printf("Vous gagne 3hp\n");
}
//                       --------------------                                  //
int potionManaInit(Perso tabJ[2],int i){
    int n=0;
    printf("Potion de Mana : Regenere 2 points de mana\nQuantite : 2\n\n1- Selectionner cet objet\n0- Retourner a la selection d'objets\n");
    scanf("%d",&n);
    if(n==1){
        tabJ[i].ptr4=potionMana;
        strcpy(tabJ[i].nomObjet,"Potion de Mana");
        tabJ[i].objet=2;
    }
    return n;
}

void potionMana(Perso tabJ[2],char** plateau,char joueurCible){
    int joueurSelec;
    joueurSelec=(joueurCible==49) ? 1 : 0;
    tabJ[joueurSelec].objet-=1;
    tabJ[joueurSelec].mana+=2;
    printf("Vous gagne 2 Mana\n");
}