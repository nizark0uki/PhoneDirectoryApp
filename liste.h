/*-------------------------------------------*/
struct adresse{
    char rue[10];
    char ville[10];
    unsigned code_pos;
};

struct client{
    long int numero;
    char nom[20];
    char prenom[20];
    struct adresse adresse;
    char date[10];
    char mail[30];
};

struct element{
    struct client cle;
    struct element *suivant;
};

struct liste{
    struct element *premier;
    struct element *dernier;
};

/*-------------------------------------------*/
void creer_liste(struct liste*);
unsigned taille_liste(struct liste*);
unsigned recherche_tel(struct liste*, long int );
void insere_tete_tel(struct liste *, struct client );
void insere_queue_tel(struct liste *, struct client );
void insere_pos_tel(struct liste *, struct client, int);
void supprimer_tete_tel(struct liste*);
void supprimer_queue_tel(struct liste*);
void suppression_pos_tel(struct liste*, int);
void suppression_tel_donne(struct liste *, long int);
void afficher_personne(struct client);
void afficher_liste(struct liste*);


/*-------------------------------------------*/
void CREATION(struct liste *);
void MISE_A_JOUR(struct liste*);
void RECH_AFF(struct liste *);
void ENRE_CHAR(struct liste*);


