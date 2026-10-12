

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char T_Titre[100][100]={"harry potter","the one","bridge"};
int nbr_livre=3;
int T_NLivre[100]={1,2,3};
int T_Nbr_exp[100]={1,5,1};
int i,l;
int cin2;
char tit[100];
int nbr_ncin=5;
char choix;
int num,s=0;
int num2;
int nbex;
char nom[30];
char ncin[20],nlivre[20];
int j1,m1,a1;
int j2,m2,a2;
int j3,m3,a3;
int j4,m4,a4;
int j5,m5,a5;
int j6,m6,a6;
int T_hist[100][8] = {
    {12345678, 1, 10, 11, 2024, 17, 11, 2050},
    {17654321, 2, 05, 10, 2024, 12, 10, 2028},
    {11223344, 2, 01, 05, 2024, 27, 9, 2024},
    {15667788, 2, 01, 11, 2024, 8, 11, 2024},
    {19887766, 1, 15, 11, 2024, 22, 11, 2024}
};
int nb=5;

int T_emp[100][8] = {
    {12345678, 1, 10, 11, 2024, 17, 11, 2050},
    {17654321, 2, 5, 10, 2024, 12, 10, 2028},
    {11223344, 3, 1, 5, 2024, 27, 9, 2024},
    {15667788, 2, 1, 11, 2024, 8, 11, 2024},
    {19887766, 1, 15, 11, 2024, 22, 11, 2024}
};
int nb_emprunts=5;
char ncin1[20];

int bissextile(int annee){
    return (annee%400==0)||(annee%4==0&&annee%100!=0);
}

int jours_dans_mois(int m,int a){
    switch(m){
        case 1:case 3:case 5:case 7:case 8:case 10:case 12: return 31;
        case 4:case 6:case 9:case 11: return 30;
        case 2: if(bissextile(a)) return 29; else return 28;
    }
    return 0;
}

int date_en_jours(int j,int m,int a){
    int total=0;
    for(int an=1900; an<a; an++){
        if(bissextile(an)) total+=366;
        else total+=365;
    }
    for(int mm=1; mm<m; mm++) total+=jours_dans_mois(mm,a);
    total+=j;
    return total;
}

int date_valide(int j,int m,int a){
    if(a<1900||a>2100||m<1||m>12||j<1) return 0;
    int jours=jours_dans_mois(m,a);
    return j<=jours;
}

int numeric(char x[]){
    int s=0;
    for(int i=0;i<strlen(x);i++){
        if(x[i]>='0'&&x[i]<='9') s++;
    }
    return s==8;
}

int numeric1(char x){
    if(x>='0' && x<='9') return 0;
    return 1;
}

int verifcin(char x[]){
    int s=1;
    if(x[0]!='0' && x[0]!='1') s=0;
    else if(!numeric(x)) s=0;
    return s;
}

int trouver_num_livre(char titre[]){
    for(int i=0;i<nbr_livre;i++){
        if(strcmp(T_Titre[i],titre)==0) return T_NLivre[i];
    }
    return -1;
}

int compter_emprunts_cin(int cin){
    int c=0;
    for(int k=0;k<nb_emprunts;k++){
        if(T_emp[k][0]==cin) c++;
    }
    return c;
}

int cherche_cin(int cin){
    for(int k=0;k<nb_emprunts;k++){
        if(T_emp[k][0]==cin) return 1;
    }
    return 0;
}

void livre_rendre(int cin,int numliv){
    int pos=-1;
    for(int i=0;i<nb_emprunts;i++){
        if(T_emp[i][0]==cin && T_emp[i][1]==numliv){
            pos=i;
        }
    }
    if(pos==-1){
        printf("Aucun emprunt trouve pour ce CIN et ce livre.\n");
        return;
    }
    for(int i=pos;i<nb_emprunts-1;i++){
        for(int j=0;j<8;j++){
            T_emp[i][j]=T_emp[i+1][j];
        }
    }
    nb_emprunts--;
    for(int f=0;f<nbr_livre;f++){
        if(T_NLivre[f]==numliv){
            T_Nbr_exp[f]++;
        }
    }
    printf("Retour enregistre avec succes.\n");
}

void prochaine_date_retour(int numliv){
    int trouve=0;
    int min=999999999999999;
    int j=0,m=0,a=0;
    for(int i=0;i<nb_emprunts;i++){
        if(T_emp[i][1]==numliv){
            int d=date_en_jours(T_emp[i][5],T_emp[i][6],T_emp[i][7]);
            if(d<min){
                min=d;
                j=T_emp[i][5];
                m=T_emp[i][6];
                a=T_emp[i][7];
                trouve=1;
            }
        }
    }
    if(!trouve) printf("Aucun emprunt en cours pour ce livre.\n");
    else printf("Livre est disponible le : %d/%d/%d\n", j,m,a);
}

int menu(){
    do{
        printf("\n========================================\n");
        printf(" MENU BIBLIOTHEQUE \n");
        printf("========================================\n");
        printf(" 1. Afficher tous les livres\n");
        printf(" 2. Ajouter un livre\n");
        printf(" 3. Supprimer un livre\n");
        printf(" 4. Modifier le nombre d'exemplaires\n");
        printf(" 5. Rechercher un livre\n");
        printf(" 6. Livres disponibles\n");
        printf(" 7. Menu principal\n");
        printf("========================================\n");

        do{
            printf("Donner votre choix s'il vous plait : ");
            scanf(" %c",&choix);
        }while(numeric1(choix));

        if(choix=='1'){
            printf("\n--- liste des livres ---\n");
            for(int i=0;i<nbr_livre;i++){
                printf("Livre %d : %-20s | num=%d | exemplaires=%d\n", i+1, T_Titre[i], T_NLivre[i], T_Nbr_exp[i]);
            }
        }
        else if(choix=='2'){
            printf("\n--- ajouter un livre ---\n");
            printf("Donner le numero du livre : ");
            scanf("%d",&T_NLivre[nbr_livre]);
            printf("Donner le titre du livre : ");
            getchar();
            scanf("%[^\n]",T_Titre[nbr_livre]);
            do{
                printf("Donner le nombre d'exemplaires : ");
                scanf("%d",&T_Nbr_exp[nbr_livre]);
            }while(T_Nbr_exp[nbr_livre]<0 || T_Nbr_exp[nbr_livre]>100);
            nbr_livre++;
            printf("Livre ajoute avec succes !\n");
        }
        else if(choix=='3'){
            printf("Donner le numero du livre a supprimer : ");
            scanf("%d",&num);
            s=0;
            for(i=0;i<nbr_livre;i++){
                if(T_NLivre[i]==num){s=1; l=i; }
            }
            if(s==0) printf("Livre introuvable\n");
            else{
                for(int j=l;j<nbr_livre-1;j++){
                    strcpy(T_Titre[j],T_Titre[j+1]);
                    T_NLivre[j]=T_NLivre[j+1];
                    T_Nbr_exp[j]=T_Nbr_exp[j+1];
                }
                nbr_livre--;
                printf("Livre supprime avec succes.\n");
            }
        }
        else if(choix=='4'){
            printf("Donner le numero du livre a modifier : ");
            scanf("%d",&num);
            s=0;
            for(i=0;i<nbr_livre;i++){
                if(T_NLivre[i]==num){ s=1; l=i; }
            }
            if(s==0) printf("Le livre est introuvable\n");
            else{
                printf("Donner le nouveau nombre d'exemplaires : ");
                scanf("%d",&nbex);
                T_Nbr_exp[l]=nbex;
                printf("Modifie avec succes\n");
            }
        }
        else if(choix=='5'){
            printf("Veux-tu chercher avec les titres ou avec leur numero ?\n");
            printf("1. Avec titre\n");
            printf("2. Avec numero\n");
            int m;
            scanf("%d",&m);
            if(m==2){
                printf("Donner le numero de livre : ");
                scanf("%d",&num);
                s=0;
                for(i=0;i<nbr_livre;i++){
                    if(T_NLivre[i]==num){ s=1; l=i; }
                }
                if(s==0) printf("Introuvable\n");
                else printf("Livre : %s existe\n",T_Titre[l]);
            } else if(m==1){
                printf("Donner le titre du livre : ");
                getchar();
                scanf("%[^\n]",tit);
                s=0;
                for(i=0;i<nbr_livre;i++){
                    if(strcmp(T_Titre[i],tit)==0){ s=1; l=i; }
                }
                if(s==0) printf("Le livre est introuvable\n");
                else printf("Livre : %s existe\n",T_Titre[l]);
            }
        }
        else if(choix=='6'){
            printf("\n======   LIVRES DISPONIBLES   =======\n");
            for(i=0;i<nbr_livre;i++){
                if(T_Nbr_exp[i]>0)
                    printf("%s (%d exemplaires)\n",T_Titre[i],T_Nbr_exp[i]);
            }
        }

    }while(choix!='7');

    return 1;
}
void menu1(){
    do{
        printf("\n===============================================================================\n");
        printf(" GESTION DES EMPRUNTS \n");
        printf("===============================================================================\n");
        printf(" 1. Ajouter un emprunt\n");
        printf(" 2. Consulter les emprunts d'un adherent\n");
        printf(" 3. Enregistrer le retour d'un livre\n");
        printf(" 4. Afficher la liste des emprunts en cours\n");
        printf(" 5. Afficher les livres en retard de retour\n");
        printf(" 6. Afficher les emprunts relatifs a une date de retour prevue\n");
        printf(" 7. Supprimer un ensemble d'emprunts\n");
        printf(" 8. Menu principal\n");
        printf("===============================================================================\n");

        do{
            printf("Donner votre choix s'il vous plait : ");
            scanf(" %c",&choix);
        }while(numeric1(choix));

        if(choix=='1'){
            for(int i=0;i<nbr_livre;i++){
                if(T_Nbr_exp[i]>0)
                    printf("%s (%d exemplaires)\n",T_Titre[i],T_Nbr_exp[i]);
            }

            do{
                printf("Donner le numero de CIN : ");
                scanf("%s",ncin);
            }while(!verifcin(ncin));
            nbr_ncin++;
            int cin_int=atoi(ncin);
            int ok=1;

            if(compter_emprunts_cin(cin_int)>=7){
                printf("Ce CIN a deja 7 emprunts actifs. Ajout refuse.\n");
                ok=0;
            }

            do{
                printf("Donner le titre du livre : ");
                getchar();
                scanf("%[^\n]",nlivre);
                num2=trouver_num_livre(nlivre);
                if(num2==-1){
                    printf("Livre introuvable !\n");
                    ok=0;
                } else ok=1;
            }while(num2==-1);

            int dispo=0;
            for(int i=0;i<nbr_livre;i++){
                if(T_NLivre[i]==num2) dispo=T_Nbr_exp[i];
            }
            if(dispo==0){
                printf("Aucun exemplaire disponible.\n");
                prochaine_date_retour(num2);
                ok=0;
            }

            do{
                printf("Date emprunt (J/M/A) : ");
                scanf("%d/%d/%d",&j1,&m1,&a1);
            }while(!date_valide(j1,m1,a1));

            do{
                printf("Date retour (J/M/A) : ");
                scanf("%d/%d/%d",&j2,&m2,&a2);
            }while(!date_valide(j2,m2,a2));

            int diff=date_en_jours(j2,m2,a2)-date_en_jours(j1,m1,a1);
            if(diff<0){
                printf("Date de retour avant date d'emprunt.\n");
                ok=0;
            }
            if(diff>30){
                printf("Delai depasse 30 jours.\n");
                ok=0;
            }

            if(ok==1){
                for(int i=0;i<nbr_livre;i++){
                    if(T_NLivre[i]==num2) T_Nbr_exp[i]--;
                }
                T_emp[nb_emprunts][0]=cin_int;
                T_emp[nb_emprunts][1]=num2;
                T_emp[nb_emprunts][2]=j1;
                T_emp[nb_emprunts][3]=m1;
                T_emp[nb_emprunts][4]=a1;
                T_emp[nb_emprunts][5]=j2;
                T_emp[nb_emprunts][6]=m2;
                T_emp[nb_emprunts][7]=a2;
                nb_emprunts++;
                printf("Emprunt ajoute avec succes !\n");
                T_hist[nb][0]=cin_int;
                T_hist[nb][1]=num2;
                T_hist[nb][2]=j1;
                T_hist[nb][3]=m1;
                T_hist[nb][4]=a1;
                T_hist[nb][5]=j2;
                T_hist[nb][6]=m2;
                T_hist[nb][7]=a2;
                nb++;
            }
        }

        else if(choix=='2'){
            printf("Donner le CIN : ");
            scanf("%i",&cin2);
            if(cherche_cin(cin2)==0) printf("CIN inexistant\n");
            else{
                for(int i=0;i<nb_emprunts;i++){
                    if(T_emp[i][0]==cin2)
                        printf("Livre : %d | Emprunt : %d/%d/%d | Retour : %d/%d/%d\n",
                        T_emp[i][1],T_emp[i][2],T_emp[i][3],T_emp[i][4],
                        T_emp[i][5],T_emp[i][6],T_emp[i][7]);
                }
            }
        }

        else if(choix=='3'){
            printf("Donner le CIN : ");
            scanf("%s",ncin1);
            if(!verifcin(ncin1)) printf("CIN invalide\n");
            else{
                int cin_int=atoi(ncin1);
                printf("Donner le numero du livre retourne : ");
                scanf("%d",&num2);
                livre_rendre(cin_int,num2);
            }
        }

        else if(choix=='4'){
            printf("=========   LA LISTE DES EMPRUNTS EN COURS   =========== \n");
            if(nb_emprunts==0) printf("Aucun emprunt pour le moment\n");
            else{
                for(int i=0;i<nb_emprunts;i++)
                    printf("CIN : %-10d | Livre %-2d | Emprunt : %02d/%02d/%04d | Retour : %02d/%02d/%04d\n",
                    T_emp[i][0],T_emp[i][1],T_emp[i][2],T_emp[i][3],T_emp[i][4],
                    T_emp[i][5],T_emp[i][6],T_emp[i][7]);
            }
        }

        else if(choix=='5'){
            printf("======   AFFICHAGE DES LIVRES EN RETARD   ========= \n");
            printf("Donner la date courante (J/M/A) : ");
            scanf("%d/%d/%d",&j3,&m3,&a3);
            if(!date_valide(j3,m3,a3)) printf("Date courante invalide\n");
            else{
                int date3=date_en_jours(j3,m3,a3);
                for(int i=0;i<nb_emprunts;i++){
                    if(date3>date_en_jours(T_emp[i][5],T_emp[i][6],T_emp[i][7]))
                        printf("Livre : %d | Emprunt : %d/%d/%d | Retour : %d/%d/%d\n",
                        T_emp[i][1],T_emp[i][2],T_emp[i][3],T_emp[i][4],
                        T_emp[i][5],T_emp[i][6],T_emp[i][7]);
                    else printf("aucune livre en retard");
                }

            }
        }

        else if(choix=='6'){
            printf("Donner la date (J/M/A) : ");
            scanf("%d/%d/%d",&j4,&m4,&a4);
            if(!date_valide(j4,m4,a4)) printf("Date invalide\n");
            else{
                int date4=date_en_jours(j4,m4,a4);
                for(int i=0;i<nb_emprunts;i++){
                    if(date4==date_en_jours(T_emp[i][5],T_emp[i][6],T_emp[i][7]))
                        printf("ID : %d | Livre : %d | Emprunt : %d/%d/%d | Retour : %d/%d/%d\n",
                        T_emp[i][0],T_emp[i][1],T_emp[i][2],T_emp[i][3],T_emp[i][4],
                        T_emp[i][5],T_emp[i][6],T_emp[i][7]);
                }
            }
        }

        else if(choix=='7'){
            printf("Donner la date d'emprunt max (J/M/A) : ");
            scanf("%d/%d/%d",&j5,&m5,&a5);
            printf("Donner la date de retour max (J/M/A) : ");
            scanf("%d/%d/%d",&j6,&m6,&a6);
            int debut=date_en_jours(j5,m5,a5);
            int fin=date_en_jours(j6,m6,a6);
            int z=0;
            for(int i=0;i<nb_emprunts;i++){
                int d_emprunt=date_en_jours(T_emp[i][2],T_emp[i][3],T_emp[i][4]);
                int d_retour=date_en_jours(T_emp[i][5],T_emp[i][6],T_emp[i][7]);
                if(!(d_emprunt>=debut && d_retour<=fin)){
                    for(int k=0;k<8;k++) T_emp[z][k]=T_emp[i][k];
                    z++;
                }
            }
            nb_emprunts=z;
        }

    }while(choix!='8');
}
void stattotaux(){
    printf("Le nombre de Livres : %d\n", nbr_livre);
    printf("Le nombre d'Adherents : %d\n", nbr_ncin);
    printf("Le nombre d'Emprunts : %d\n", nb);
}

void statplusemp(){
    int t[100]={0};
    for(int i=0;i<nb;i++){
        int n=T_hist[i][1];
        for(int j=0;j<nbr_livre;j++){
            if(T_NLivre[j]==n) t[j]++;
        }
    }
    int mx=0;
    for(int j=0;j<nbr_livre;j++) if(t[j]>mx) mx=t[j];
    for(int j=0;j<nbr_livre;j++){
        if(t[j]==mx && mx>0) printf("Le(s) livre(s) le(s) plus emprunte(s): %s (%d fois)\n", T_Titre[j], mx);
    }
}

void statjamais(){
    int t[100]={0};
    for(int i=0;i<nb;i++){
        int n=T_hist[i][1];
        for(int j=0;j<nbr_livre;j++){
            if(T_NLivre[j]==n) t[j]++;
        }
    }
    int ok=0;
    for(int j=0;j<nbr_livre;j++){
        if(t[j]==0){
            printf("le livre qui n'a jamais ete emprunte est %s\n", T_Titre[j]);
            ok=1;
        }
    }
    if(!ok) printf("Tous les livres ont deja ete emprunte\n");
}

void statperiode(){
    int jj1,mm1,aa1,jj2,mm2,aa2;
    do{
        printf("Date du debut (J/M/A) : ");
        scanf("%d/%d/%d",&jj1,&mm1,&aa1);
    }while(!date_valide(jj1,mm1,aa1));
    do{
        printf("Date du retour (J/M/A) : ");
        scanf("%d/%d/%d",&jj2,&mm2,&aa2);
    }while(!date_valide(jj2,mm2,aa2));
    int d1=date_en_jours(jj1,mm1,aa1);
    int d2=date_en_jours(jj2,mm2,aa2);
    int t[100]={0};
    for(int i=0;i<nb_emprunts;i++){
        int d=date_en_jours(T_emp[i][2],T_emp[i][3],T_emp[i][4]);
        if(d>=d1 && d<=d2){
            int n=T_emp[i][1];
            for(int j=0;j<nbr_livre;j++){
                if(T_NLivre[j]==n) t[j]++;
            }
        }
    }
    int mx=0;
    for(int j=0;j<nbr_livre;j++) if(t[j]>mx) mx=t[j];
    for(int j=0;j<nbr_livre;j++){
        if(t[j]==mx && mx>0) printf("Les livres les plus empruntes pendant cette periode sont %s (%d fois)\n", T_Titre[j], mx);
    }
}

void statadh(){
    if(nb==0){
        printf("Aucun emprunt.\n");
        return;
    }
    int cinList[500];
    int count[500]={0};
    int n=0;
    for(int i=0;i<nb;i++){
        int cin=T_hist[i][0];
        int existe=0;
        for(int j=0;j<n;j++){
            if(cinList[j]==cin){ existe=1; }
        }
        if(!existe){ cinList[n]=cin; n++; }
    }
    for(int i=0;i<n;i++){
        int cin=cinList[i];
        for(int e=0;e<nb ;e++){
            if(T_hist[e][0]==cin) count[i]++;
        }
    }
    int mx=0;
    for(int i=0;i<n;i++) if(count[i]>mx) mx=count[i];
    for(int i=0;i<n;i++){
        if(count[i]==mx) printf("CIN : %d | Emprunts: %d \n", cinList[i], count[i]);
    }
}

void menu3(){
    do{
        printf("\n===============================================================================\n");
        printf(" STATISTIQUES \n");
        printf("===============================================================================\n");
        printf(" Veuillez choisir :\n");
        printf(" 1. Afficher le nombre total de livres, d'adherents et d'emprunts\n");
        printf(" 2. Afficher le(s) livre(s) le(s) plus emprunte(s)\n");
        printf(" 3. Afficher le(s) livre(s) jamais emprunte(s)\n");
        printf(" 4. Afficher le(s) livre(s) le(s) plus emprunte(s) dans une periode donnee\n");
        printf(" 5. Afficher le(s) emprunteur(s) le(s) plus frequent(s)\n");
        printf(" 6. Menu principal\n");
        printf("===============================================================================\n");
        printf("Donner votre choix s'il vous plait : ");
        scanf(" %c", &choix);
        if(choix=='1') stattotaux();
        else if(choix=='2') statplusemp();
        else if(choix=='3') statjamais();
        else if(choix=='4') statperiode();
        else if(choix=='5') statadh();
    }while(choix!='6');
}
int main(){
    char k;
    do{
        printf("\n================================================================================\n");
        printf(" BIENVENUE DANS LE MENU PRINCIPAL \n");
        printf("================================================================================\n");
        printf(" 1. Gestion de la bibliotheque\n");
        printf(" 2. Gestion des emprunts\n");
        printf(" 3. Statistiques\n");
        printf(" 4. Quitter l'application\n");
        printf("================================================================================\n");

        do{
            printf("Donner votre choix s'il vous plait : ");
            scanf(" %c",&k);
        }while(numeric1(k));
        if(k=='1') menu();
        else if(k=='2') menu1();
        else if(k=='3') menu3();
    }while(k!='4');

    printf("\n==============================================================\n");
    printf("                        AU REVOIR !                           \n");
    printf("==============================================================\n");

    return 0;
}
