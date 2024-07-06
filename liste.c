#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "liste.h"

/*------------------Partie_0------------------*/

void creer_liste(struct liste* L)
{
    L->premier=NULL;
    L->dernier=NULL;
}

unsigned taille_liste(struct liste* L)
{
    int S=0;
    struct element *q;
    q=L->premier;
    while(q!=NULL)
    {
        S++;
        q=q->suivant;
    }
    return S;
}

unsigned recherche_tel(struct liste *L,long int num)
{
    struct element *q;
    q=L->premier;
    while(q!=NULL){
        if((q->cle).numero==num)
            return 1;
        q=q->suivant;
    }
    return 0;
}

void insere_tete_tel(struct liste*L ,struct client C)
{
    struct element*q;
    q=(struct element*)malloc(sizeof(struct element));
    q->cle=C;
    q->suivant=L->premier;
    L->premier=q;
    if (q->suivant==NULL)
        L->dernier=q;
}

void insere_queue_tel(struct liste*L ,struct client C)
{
    struct element*q;
    q=(struct element*)malloc(sizeof(struct element));
    q->cle= C;
    q->suivant=NULL;
    if (taille_liste(L)==0)
        L->premier=q;
    else
        L->dernier->suivant=q;
    L->dernier=q;
}

void insere_pos_tel(struct liste *L, struct client C, int pos)
{
    struct element *q;
    struct element* actu;
    struct element* suiv;
    int i;
    while (pos<1 || pos > (taille_liste(L)+1))
    {
        printf("position invalide\n");
        printf("donner une nouvelle position : ");
        scanf("%d",&pos);
    }
    if (pos==1)
        insere_tete_tel(L,C);
    else if (pos==(taille_liste(L)+1))
        insere_queue_tel(L,C);
    else
    {
        q=(struct element*)malloc(sizeof(struct element));
        i=1;
        actu=L->premier;
        suiv=actu->suivant;
        while(i!=pos-1)
            {
                i++;
                actu=actu->suivant;
                suiv=actu->suivant;
            }
        q->cle=C;
        q->suivant=suiv;
        actu->suivant=q;
    }
}

void supprimer_tete_tel(struct liste *L)
{
    struct element *q;
    if (taille_liste(L)==0)
        printf("Le repertoire est vide !\n");
    else
    {
        q=L->premier;
        L->premier=q->suivant;
        free(q);
        if(L->premier==NULL)
            L->dernier=NULL;
    }
}

void supprimer_queue_tel(struct liste *L)
{
    struct element *q;
    struct element *actu;
    if (taille_liste(L)==0)
        printf("Le repertoire est vide !\n");
    else
    {
        q=L->dernier;
        if (L->premier==q)
            {
                L->premier=NULL;
                L->dernier=NULL;
            }
        else
            {
                actu=L->premier;
                while(actu->suivant!=q)
                    actu=actu->suivant;
                L->dernier=actu;
            }
        free(q);
    }
}

void suppression_pos_tel(struct liste *L,int pos)
{
    struct element *q;
    struct element* actu;
    int i;
    while (pos<1 || pos > (taille_liste(L)))
    {
        printf("position invalide\n");
        printf("donner une nouvelle position : ");
        scanf("%d",&pos);
    }
    if (pos==1)
        supprimer_tete_tel(L);
    else if (pos==taille_liste(L))
        supprimer_queue_tel(L);
    else
    {
        i=1;
        actu=L->premier;
        while(i!=pos-1)
            {
                i++;
                actu=actu->suivant;
            }
        q=actu->suivant;
        actu->suivant=q->suivant;
        free(q);
    }
}

void suppression_tel_donne(struct liste *L,long int num)
{
    struct element *q;
    int pos=1;
    if (taille_liste(L)==0)
        printf("Le repertoire est vide !\n");
    else
    {
        if(!recherche_tel(L,num))
            printf("Ce numero n'existe pas dans le repertoire !\n");
        else
        {
            q=L->premier;
            while((q->cle).numero!=num)
            {
                q=q->suivant;
                pos++;
            }
            suppression_pos_tel (L , pos);
        }
    }
}

void afficher_personne(struct client C)
{
    printf("Numero: %ld\n",C.numero);
    printf("Nom: %s\n",C.nom);
    printf("Prenom: %s\n",C.prenom);
    printf("Adresse: %s, %s, %u\n",C.adresse.rue,C.adresse.ville,C.adresse.code_pos);
    printf("Date De Naissance: %s\n",C.date);
    printf("Email: %s\n",C.mail);
    printf("\n");
}


void afficher_liste(struct liste *L)
{
    struct element *q;
    q=L->premier;
    while(q!=NULL)
    {
        afficher_personne(q->cle);
        q=q->suivant;
    }
}


/*------------------Partie_1------------------*/

void CREATION(struct liste *L)
{
    int continuer=1,pos;
    if(taille_liste(L)!=0)
        printf("Un repertoire existe deja\n");
    else
    {
        while (continuer)
        {
            struct client C;
            printf("donner les informations de la personne :\n");
            printf("Numero du telephone : ");
            fflush(stdin);
            scanf("%ld",&C.numero);
            while(recherche_tel(L,C.numero))
            {
                printf("Ce numero de telephone existe deja\n");
                printf("Reecrir le numero : ");
                scanf("%ld",&C.numero);
            }
            printf("Nom : ");
            fflush(stdin);
            scanf("%s",&C.nom);
            printf("Prenom : ");
            fflush(stdin);
            scanf("%s",&C.prenom);
            printf("Ville : ");
            fflush(stdin);
            scanf("%s",&C.adresse.ville);
            printf("Rue : ");
            fflush(stdin);
            scanf("%s",&C.adresse.rue);
            printf("Code postale : ");
            fflush(stdin);
            scanf("%d",&C.adresse.code_pos);
            printf("Date de Naissance (jj//mm/aa) : ");
            fflush(stdin);
            scanf("%s",&C.date);
            printf("Email : ");
            fflush(stdin);
            scanf("%s",&C.mail);
            printf("donner la position du telephone : ");
            fflush(stdin);
            scanf("%d", &pos);
            insere_pos_tel(L,C,pos);
            printf("Voulez-vous ajouter un autre telephone ? (0 pour Non, 1 pour Oui) : ");
            fflush(stdin);
            scanf("%d", &continuer);
        }
    }
}

/*------------------Partie_2------------------*/

void Ajouter(struct liste *L)
{
    int choix,pos;
    struct client C;
    do {
        printf("Menu Ajouter \n\n");
        printf("1/ Ajout en tete \n");
        printf("2/ Ajout en queue \n");
        printf("3/ Ajout dans une position \n");
        printf("4/ Retour au menu MAJ \n\n");


        printf("Donner votre choix SVP : ");
        scanf("%d", &choix);
        printf("\n");
        if (choix!=4)
        {
            printf("donner les informations de la personne :\n");
            printf("Numero du telephone : ");
            fflush(stdin);
            scanf("%ld",&C.numero);
            while(recherche_tel(L,C.numero))
            {
                printf("Ce numero de telephone existe deja\n");
                printf("Reecrir le numero : ");
                scanf("%ld",&C.numero);
            }
            printf("Nom : ");
            fflush(stdin);
            scanf("%s",&C.nom);
            printf("Prenom : ");
            fflush(stdin);
            scanf("%s",&C.prenom);
            printf("Ville : ");
            fflush(stdin);
            scanf("%s",&C.adresse.ville);
            printf("Rue : ");
            fflush(stdin);
            scanf("%s",&C.adresse.rue);
            printf("Code postale : ");
            fflush(stdin);
            scanf("%d",&C.adresse.code_pos);
            printf("Date de Naissance (jj//mm/aa) : ");
            fflush(stdin);
            scanf("%s",&C.date);
            printf("Email : ");
            fflush(stdin);
            scanf("%s",&C.mail);

            switch(choix)
            {
                case 1:
                    insere_tete_tel(L,C);
                    printf("Ajout terminee !\n\n");
                    break;
                case 2:
                    insere_queue_tel(L,C);
                    printf("Ajout terminee !\n\n");
                    break;
                case 3:
                    printf("donner la position du telephone : ");
                    fflush(stdin);
                    scanf("%d", &pos);
                    insere_pos_tel(L,C,pos);
                    printf("Ajout terminee !\n\n");
                    break;
                default:
                    printf("CHOIX INVALIDE. \n\n\n");
            }



        }
    } while(choix != 4);
}

int verif_ville(struct liste *L, char v[])
{
    struct element *q;
    q=L->premier;
    while(q!=NULL)
    {
        if(strcmp((q->cle).adresse.ville,v)==0)
        {
            return 1;
        }
    }
    return 0;
}
void supprimer_ville_donnee(struct liste *L)
{
    struct element *q,*t;
    q=L->premier;

    char ville[10];
    printf("donner la ville : ");
    scanf("%s",ville);
    if(!verif_ville(L,ville))
        printf("Aucun numero de telephone n'est associe a cette ville\n");
    else
    {
        while(verif_ville(L,ville))
        {
            if(strcmp(L->premier->cle.adresse.ville,ville)==0)
            {
                L->premier=L->premier->suivant;
                free(q);
            }
            else
            {
                while(q->suivant!=NULL && strcmp(q->suivant->cle.adresse.ville,ville)!=0)
                {
                    q=q->suivant;
                }
                if(q->suivant!=NULL)
                {
                    t=q->suivant;
                    q->suivant=q->suivant->suivant;
                    free(t);
                }
            }
            q=L->premier;
        }
        printf("Suppression terminee !\n\n");
    }
}
void supprimer_indicatif(struct liste *l)
{
    char indication[20];
    int k=0;
    printf("\nEntrez une indication: ");
    scanf("%s", indication);
    struct element *q=l->premier,*prec=NULL;
    while (q != NULL) {
        char num[20];
        sprintf(num, "%ld", q->cle.numero);
        if(strncmp(num,indication,strlen(indication)) == 0) {
                k++;
            if (prec==NULL) {
                l->premier = q->suivant;
                free(q);
                q=l->premier;
            }
            else {
                prec->suivant=q->suivant;
                free(q);
                q=prec->suivant;
                }
        }
        else
            {
            prec = q;
            q = q->suivant;
            }
    }
    if(k>0)
        {printf("\nSuppression Avec Success !\n");
        if(l->premier==NULL)
            printf("\nLe repertoire est maintenant vide!\n");}
    else
        printf("\nAucun telephone contenant cette indication n'a ete trouve!\n");
}
void Suppression(struct liste *L)
{
    int choix,pos;
    long int num;
    do {
        printf("Menu Suppression \n\n");
        printf("1/ Suppression en tete \n");
        printf("2/ Suppression en queue \n");
        printf("3/ Suppression a partir d'une position \n");
        printf("4/ Suppression d'un telephone donne \n");
        printf("5/ Suppression des telephone d'une ville donnee \n");
        printf("6/ Suppression des telephones d'un indicatif donne \n");
        printf("7/ Retour au menu MAJ \n\n");

        printf("Donner votre choix SVP : ");
        scanf("%d", &choix);

        switch(choix)
        {
            case 1:
                supprimer_tete_tel(L);
                printf("Suppression terminee !\n\n");
                break;
            case 2:
                supprimer_queue_tel(L);
                printf("Suppression terminee !\n\n");
                break;
            case 3:
                printf("donner la position : ");
                scanf("%d",&pos);
                while (pos<1 || pos>taille_liste(L))
                {
                    printf("position invalide, veillez reessayer : ");
                    scanf("%d",&pos);
                }
                while(pos<=taille_liste(L))
                    supprimer_queue_tel(L);
                printf("Suppression terminee !\n\n");
                break;
            case 4:
                printf("donnez le numero de telephone : ");
                scanf("%ld",&num);
                if (!recherche_tel(L,num))
                    printf("Le numero n'existe pas dans la repertoire !\n");
                else
                {
                    suppression_tel_donne(L,num);
                    printf("Suppression terminee !\n\n");
                }
                break;
            case 5:
                supprimer_ville_donnee(L);
                printf("Suppression terminee !\n\n");
                break;
            case 6:
                supprimer_indicatif(L);
                printf("Suppression terminee !\n\n");
                break;
            case 7:
                break;
            default:
                printf("CHOIX INVALIDE. \n\n\n");
        }
    } while(choix != 7);
}

void modifer_adresse(struct liste *L)
{
    long int num;
    char Rue[10],Ville[10];
    unsigned code_pos;
    struct element *q;

    printf("Entrez le numero de telephone de la personne que vous voulez mettre a jour : ");
    fflush(stdin);
    scanf("%ld",&num);
    if (!recherche_tel(L,num))
        printf("Ce numero n'existe pas dans le repertoire !");
    else
    {
        printf("Entrez la nouvelle rue : ");
        fflush(stdin);
        gets(Rue);
        printf("Entrez la nouvelle ville : ");
        fflush(stdin);
        gets(Ville);
        printf("Entrez le nouveau code postal : ");
        fflush(stdin);
        scanf("%u",&code_pos);

        q=L->premier;
        while(q->cle.numero!=num)
            q=q->suivant;

        q->cle.adresse.code_pos=code_pos;
        strcpy(q->cle.adresse.rue, Rue);
        strcpy(q->cle.adresse.ville, Ville);
        printf("Mise a jour terminee !\n\n");
    }
}
void modifier_num(struct liste *L)
{
    long int num, nouveau_num;
    struct element *q;

    printf("Entrez le numero de telephone de la personne que vous voulez mettre a jour : ");
    fflush(stdin);
    scanf("%ld",&num);
    if (!recherche_tel(L,num))
        printf("Ce numero n'existe pas dans le repertoire !");
    else
    {
        printf("Entrez le nouveau numero : ");
        scanf("%ld",&nouveau_num);
        q=L->premier;
        while(q->cle.numero!=num)
            q=q->suivant;
        q->cle.numero=nouveau_num;
        printf("Mise a jour terminee !\n\n");
    }
}
void Modification(struct liste *L)
{
    int choix;
    do {
        printf("Menu Modification \n\n");
        printf("1/ Adressee \n");
        printf("2/ Telephone \n");
        printf("3/ Retour au menu MAJ \n\n");


        printf("Donner votre choix SVP : ");
        scanf("%d", &choix);
        printf("\n");

        switch(choix)
        {
            case 1:
                modifer_adresse(L);
                break;
            case 2:
                modifier_num(L);
                break;
            case 3:
                break;
            default:
                printf("CHOIX INVALIDE. \n\n\n");
        }
        printf("\n");
    } while(choix != 3);
}


void MISE_A_JOUR(struct liste *L)
{
    int choix;
    do {
        printf("MENU MAJ \n\n");
        printf("1/ Ajouter un nouvel telephone \n");
        printf("2/ Supprimer un telephone \n");
        printf("3/ Modifier les donnees d'un telephone \n");
        printf("4/ Retour au Menu General \n\n");


        printf("Donner votre choix SVP : ");
        scanf("%d",&choix);
        printf("\n");

        switch(choix)
        {
            case 1:
                Ajouter(L);
                break;
            case 2:
                Suppression(L);
                break;
            case 3:
                Modification(L);
                break;
            case 4:
                break;
            default:
                printf("CHOIX INVALIDE. \n\n\n");
        }
        printf("\n");
    } while(choix != 4);
}


/*------------------Partie_3------------------*/

void recherche_numero(struct liste *L)
{
    long int num;
    struct element *q;

    printf("Entrez le numero de telephone de la personne : ");
    scanf("%ld",&num);
    if (!recherche_tel(L,num))
        printf("Ce numero n'existe pas dans le repertoire !");
    else
    {
        q=L->premier;
        while(q->cle.numero!=num)
            q=q->suivant;
        afficher_personne(q->cle);
    }
}
void recherche_nom(struct liste *L)
{
    char nom[20];
    struct element *q;
    int test=1;

    printf("Donner le nom de la personne : ");
    gets(nom);
    q=L->premier;
    while(q!=NULL)
    {
        if(strcmp(q->cle.nom,nom)==0)
            {
                afficher_personne(q->cle);
                test=0;
            }
        q=q->suivant;
    }
    if (test)
        printf("Aucun numero de telephone n'est associe a ce nom !");
}
void recherche_indicatif(struct liste *L)
{
    char indication[20];
    char num[20];
    struct element *q;

    printf("\nEntrez une indication: ");
    scanf("%s", indication);

    q=L->premier;
    while (q != NULL)
    {
        sprintf(num, "%ld", q->cle.numero);
        if (strncmp(num, indication, strlen(indication)) == 0)
            afficher_personne(q->cle);
        q = q->suivant;
    }
}
void recherche_ville(struct liste *L)
{
    char ville[10];
    struct element *q;

    printf("Donner le nom de la ville : ");
    gets(ville);
    if(!verif_ville(L,ville))
        printf("Aucun numero de telephone n'est associe a cette ville !");
    else
    {
        q=L->premier;
        while(q!=NULL)
        {
            if(strcmp(q->cle.adresse.ville,ville)==0)
                afficher_personne(q->cle);
            q=q->suivant;

        }
    }
}
void tri(struct liste *L)
{
    struct element *q,*p;
    struct client aux;

    for(q=L->premier;q->suivant!=NULL;q=q->suivant)
    {
        for(p=q->suivant;p!=NULL;p=p->suivant)
        {
            if(p->cle.numero>q->cle.numero)
            {
                aux=p->cle;
                p->cle=q->cle;
                q->cle=aux;
            }
        }
    }
    printf("Tri terminee !");
}


void RECH_AFF(struct liste *L)
{
    int choix;
    do {
        printf("MENU RECHERCHE ET AFFICHAGE \n\n");
        printf("1/ Contenu de la liste des telephones \n");
        printf("2/ Recherche par numero telephone \n");
        printf("3/ Recherche par nom \n");
        printf("4/ Recherche par indicatif telephone \n");
        printf("5/ Recherche par ville \n");
        printf("6/ Tri 1 \n");
        printf("7/ Retour au Menu General \n\n");

        printf("Donner votre choix SVP: ");
        scanf("%d", &choix);
        printf("\n");

        switch(choix)
        {
            case 1:
                afficher_liste(L);
                break;
            case 2:
                recherche_numero(L);
                break;
            case 3:
                recherche_nom(L);
                break;
            case 4:
                recherche_indicatif(L);
                break;
            case 5:
                recherche_ville(L);
                break;
            case 6:
                tri(L);
                break;
            case 7:
                break;
            default:
                printf("CHOIX INVALIDE. \n\n\n");
        }
        printf("\n");
    } while(choix != 7);
}

/*------------------Partie_4------------------*/

void enregistrement(struct liste *L)
{
    char fichier[100]="repertoire.txt";
    struct element *q;

    q=L->premier;
    FILE *f=fopen(fichier,"w");
    while(q)
    {
        fprintf(f,"%ld | %s %s | %s %s %u | %s | %s\n",
                q->cle.numero,q->cle.nom, q->cle.prenom,q->cle.adresse.ville, q->cle.adresse.rue, q->cle.adresse.code_pos,q->cle.date,q->cle.mail);
        q=q->suivant;
    }
    printf("Enregistrement termine ! \n");
    fclose(f);
}

void inserer(struct liste *L,struct client C)
{
    struct element *q;
    q=(struct element*)malloc(sizeof(struct element));
    q->cle=C;
    if(taille_liste(L)==0)
    {
        q->suivant=L->premier;
        L->premier=L->dernier=q;
    }
    else
    {
        q->suivant=NULL;
        L->dernier->suivant=q;
        L->dernier=q;
    }
}
void chargement(struct liste *L)
{
    struct client p;
    FILE *f = fopen("repertoire.txt", "r");
    if(f==NULL)
        printf("\nLe fichier n'existe pas\n");
    else
    {
        while (fscanf(f, "%ld | %s %s | %s %s %u | %s | %s", &p.numero, p.nom, p.prenom, p.adresse.ville, p.adresse.rue, &p.adresse.code_pos, p.date, p.mail) == 8)
            inserer(L, p);

    printf("Chargement termine ! \n");
    fclose(f);
    }
}

void ENRE_CHAR(struct liste *L)
{
    int choix;
    do {
        printf("MENU ENREGISTREMENT ET CHARGEMENT \n\n");
        printf("1/ Enregistrement \n");
        printf("2/ Chargement \n");
        printf("3/ Retour au Menu General \n\n");

        printf("Donner votre choix SVP : ");
        scanf("%d", &choix);

        switch(choix)
        {
            case 1:
                enregistrement(L);
                break;
            case 2:
                chargement(L);
                break;
            case 3:
                break;
            default:;
                printf("CHOIX INVALIDE. \n\n\n");
        }
        printf("\n");
    } while(choix != 3);
}

