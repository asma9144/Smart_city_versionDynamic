#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include<time.h>
#define alloc(t) (t*) malloc(sizeof(t))
#include "function.h"
// variables globales :
tCell *adr_batiment = NULL;
tCellEq *adr_equipement = NULL;
tCellType* adr_types =NULL;
tCellConsommation* adr_consommations =NULL  ;

// Vérifie si la chaine est formée par des lettres ou non
int estchaine(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') {
            return 0; // Ce n'est pas une lettre
        }
    }
    return 1; // Que des lettres
}

tCell *InitCell (tCell *cell, Batiment elt, tCell *succ){

	cell->elt= elt ;
	cell->succ = succ;
	return cell;

}

tCell *InsereList(tCell *tete, Batiment elt){
    // Créer la nouvelle cellule en une seule étape
    tCell *Nouveau = InitCell(alloc(tCell), elt, NULL);
    if(Nouveau == NULL) {
        printf("Erreur d'allocation memoire\n");
        return tete;
    }

    // Si la liste est vide
    if(tete == NULL) {
        return Nouveau;
    }

    // Trouver la fin de la liste
    tCell *cour = tete;
    while(cour->succ != NULL) {
        cour = cour->succ;
    }

    // Ajouter à la fin
    cour->succ = Nouveau;

    return tete;


}
// Vérifier si un bâtiment existe

int batimentExiste(int idBatiment) {
    tCell *cour = adr_batiment;
    while (cour) {
        if (cour->elt.id_batiment == idBatiment) {
            return 1;
        }
        cour = cour->succ;
    }
    return 0;
}
// Vérifier si un equipement existe
int equipementExiste(int id) {
    tCellEq *cour = adr_equipement;
    while (cour) {
        if (cour->elt.id == id ) {
            return 1;
        }
        cour = cour->succ;
    }
    return 0;
}
// Vérifier si un ID du type d'equipement existe déjà
int typeIdExiste(int id) {
    tCellType *cour = adr_types;
    while (cour != NULL) {
        if (cour->elt.id == id) {
            return 1;
        }
        cour = cour->succ;
    }
    return 0;
}
// ajout d'un batiment

void ajouterBatiment()
{

    Batiment b;
    do {
        printf("\nDonner id_batiment : ");

        // Essayer de lire l'ID
        if (scanf("%d", &b.id_batiment) != 1) {
            printf("Erreur : L'ID doit etre un entier.\n");
            // Nettoyer le buffer en cas d'erreur
            while (getchar() != '\n');
            continue; // Redémarrer la boucle
        }

        // Vérifier si l'ID est positif
        if (b.id_batiment <= 0) {
            printf("Erreur : L'ID doit etre positif.\n");
            continue;
        }

        // Vérifier si l'ID existe déjà
        if (batimentExiste(b.id_batiment)) {
            printf("Erreur : L'ID %d existe deja. Choisissez un autre ID.\n", b.id_batiment);
            continue;
        }

        break; // Sortir de la boucle si tout est bon

    } while (1);

    do {
        printf("Entrez le nom du batiment: ");
        scanf(" %[^\n]s", b.nom_batiment);
        if (estchaine(b.nom_batiment)==0 ) {
            printf("Erreur : Le nom doit etre une chaine de caractere formee par des lettres seulement.\n");
            while (getchar() != '\n');
            continue;

        }
    }while (!estchaine(b.nom_batiment));

    do {
        printf("Entrez la rue: ");
        scanf(" %[^\n]s", b.adresse.rue);
        if (estchaine(b.adresse.rue)==0 ) {
            printf("Erreur : Le nom du rue doit etre une chaine de caractere formee par des lettres seulement.\n");
        }
    }while (!estchaine(b.adresse.rue));
    do {
        printf("Entrez la ville: ");
        scanf(" %[^\n]s", b.adresse.ville);
        if (estchaine(b.adresse.ville)==0 ) {
            printf("Erreur : Le nom du ville doit etre une chaine de caractere formee par des lettres seulement.\n");
        }
    }while (!estchaine(b.adresse.ville));
    do {
        printf("Entrez le code postal: ");
        if (scanf("%d", &b.adresse.code_postal) != 1) {
            printf("Erreur : Le code postal doit etre un entier.\n");
            // Nettoyer le buffer en cas d'erreur
            while (getchar() != '\n');
            continue; // Redémarrer la boucle
        }
        // Vérifier si le code postal est positif
        if (b.adresse.code_postal <= 0) {
            printf("Erreur : Le code postal doit etre positif.\n");
            continue;
        }
        break;
    }while (1);
    b.nb_equipements = 0;

    adr_batiment=InsereList(adr_batiment,b);
    printf("Batiment ajoute avec succes ! ID: %d\n", b.id_batiment);

}


tCell* VerifierExistence_Element(tCell *tete , int val){

	if(tete == NULL) {
        return NULL; // Liste vide
    }

    while(tete){

        if(tete->elt.id_batiment==val){

            return tete;

		}
        else {

            tete = tete->succ;

        }

	}

	return NULL;
}


void modifierBatiment() {
    int id;
    tCell *bat;
    printf("Entrez l'ID du batiment à modifier: ");
    scanf("%d", &id);
    bat=VerifierExistence_Element(adr_batiment ,id);
    if (bat==NULL){
        printf("Batiment introuvable.\n");
    }
    printf("Nom actuel: %s\n", bat->elt.nom_batiment);
    printf("Nouveau nom: ");
    scanf(" %[^\n]s", bat->elt.nom_batiment);
    printf("Adresse actuelle: %s, %s %d\n", bat->elt.adresse.rue, bat->elt.adresse.ville, bat->elt.adresse.code_postal);
    printf("Nouvelle rue: ");
    scanf(" %[^\n]s", bat->elt.adresse.rue);
    printf("Nouvelle ville: ");
    scanf(" %[^\n]s", bat->elt.adresse.ville);
    printf("Nouveau code postal: ");
    scanf("%d", &bat->elt.adresse.code_postal);
    printf("Batiment modifie avec succes.\n");

    return;

}

void Supprimer_Noeud(tCell **adr_batiment, int id)
{
    tCell *pred = NULL, *cour = *adr_batiment;

    while (cour)
    {
        if (cour->elt.id_batiment == id)
            break;

        pred = cour;
        cour = cour->succ;
    }

    if (cour)
    {
        if (pred)
            pred->succ = cour->succ;
        else
            *adr_batiment = cour->succ;

        free(cour);

        printf("Batiment supprime avec succes !\n");
    }
    else
    {
        printf("L'ID que vous voulez supprimer n'est pas dans la liste.\n");
    }
}

void afficherBatimentsListe(tCell *adr_batiment) {

    if(adr_batiment == NULL) {
        printf("La liste des batiments est vide.\n");
        return;
    }

    tCell *cour = adr_batiment;
    int compte = 0;

    printf("\n=== Liste des batiments ===\n");

    if (!cour) {
        printf("Aucun batiment dans la liste.\n");
        return;
    }

    while (cour) {
        compte++;
        printf("%d. ID: %d | Nom: %s | Adresse: Rue %s \t| Ville %s \t| Code postal %d | Nb equipements: %d\n",
               compte,
               cour->elt.id_batiment,
               cour->elt.nom_batiment,
               cour->elt.adresse.rue,
               cour->elt.adresse.ville,
               cour->elt.adresse.code_postal,
               cour->elt.nb_equipements);
        cour = cour->succ;
    }
    printf("\nTotal: %d batiment(s)\n", compte);
}


tCell* rechercheBatimentParIdListe(tCell *adr_batiment, int id) {

    if (adr_batiment == NULL) {
        printf("La Liste des batiments est vide\n");
        return NULL;
    }

    if (id <= 0) {
        printf("Erreur : ID invalide (%d)\n", id);
        return NULL;
    }

    tCell *cour = adr_batiment;
    int compteur = 0;

    while (cour) {
        compteur++;
        if (cour->elt.id_batiment == id) {
            printf("Batiment trouve apres %d iteration(s)\n", compteur);
            return cour;
        }
        cour = cour->succ;
    }

    printf("Aucun batiment avec l'ID %d\n", id);
    return NULL;
}


// Initialisation d'une cellule équipement

tCellEq* InitCellEq(tCellEq *cell, Equipement elt, tCellEq *succ) {
    cell->elt = elt;
    cell->succ = succ;
    return cell;
}

// Insertion d'un équipement dans la liste

tCellEq* InsereListEq(tCellEq *tete, Equipement elt) {

    if(tete == NULL) {
        tCellEq *Nouveau = alloc(tCellEq);
        if(Nouveau == NULL) {
            printf("Erreur d'allocation memoire\n");
            return NULL;
        }
        return InitCellEq(Nouveau, elt, NULL);
    }

    tCellEq *cour = tete;
    tCellEq *pred = NULL;

    while(cour != NULL) {
        pred = cour;
        cour = cour->succ;
    }

    tCellEq *nouveau = alloc(tCellEq);
    if(nouveau == NULL) {
        printf("Erreur d'allocation memoire\n");
        return tete;
    }

    pred->succ = InitCellEq(nouveau, elt, NULL);

    return tete;

}

// Recherche d'un équipement par ID

tCellEq* rechercheEquipementParId(int id) {
    tCellEq *cour = adr_equipement;

    if (adr_equipement == NULL) {
        printf("La Liste des equipements est vide\n");
        return NULL;
    }

    while (cour) {
        if (cour->elt.id == id) {
            return cour;
        }
        cour = cour->succ;
    }

    return NULL;
}


//  Ajouter un equipement
void ajouterEquipement() {
    Equipement eq;

    // Saisie des données
    printf("\n=== Ajout d'un nouvel equipement ===\n");
    do {
        printf("ID de l'equipement: ");
        if ((scanf("%d", &eq.id)!=1)) {
            printf("Erreur : L'ID doit etre un entier.\n");
            while(getchar()!='\n');
            continue;
        }
        // Vérifier si l'ID est positif
        if (eq.id <= 0) {
            printf("Erreur : L'ID doit etre positif.\n");
            while(getchar()!='\n');
            continue;
        }
        if (rechercheEquipementParId(eq.id)!=NULL) {
            printf("Cet ID existe deja. Veuillez en choisir un autre.\n");
            while(getchar()!='\n');
            continue;
        }

        break;
    } while (1);
    do {
        printf("Entrez le nom de l'equipement: ");
        scanf(" %[^\n]s", eq.nom);
        if (estchaine(eq.nom)==0 ) {
            printf("Erreur : Le nom doit etre une chaine de caractere formee par des lettres seulement.\n");
        }
    }while (!estchaine(eq.nom));
    do {
        printf("Consommation par minute (kWh): ");
        if ((scanf("%f", &eq.conso_min)!=1)) {
            printf("Erreur : La consommation doit etre un float.\n");
            while(getchar()!='\n');
            continue;
        }
        // Vérifier si la consommation est positive
        if (eq.conso_min<= 0.0) {
            printf("Erreur : la consommation doit etre positive.\n");
            while(getchar()!='\n');
            continue;
        }

        break;
    } while (1);

    do {
        printf("ID du batiment associe: ");
        scanf("%d", &eq.idBatiment);
        if (!batimentExiste(eq.idBatiment)) {
            printf("Ce batiment n'existe pas. Veuillez entrer un ID valide.\n");
        }
    } while (!batimentExiste(eq.idBatiment));

    do {
        printf("ID du type d'equipement: ");
        if ((scanf("%d", &eq.idType))!=1) {
            printf("Erreur : La type doit etre un entier .\n");
            while(getchar()!='\n');
            continue;
        }
        if (eq.idType <= 0) {
            printf("Erreur : L'id du type doit etre positif.\n");
            while(getchar()!='\n');
            continue ;
        }
        if (!typeIdExiste(eq.idType)) {
            printf("Ce type n'existe pas. Veuillez entrer un ID valide.\n");
            while(getchar()!='\n');
            continue ;
        }
        break;
    }while (1);

    eq.etat = 0;  // Par défaut éteint
    eq.debut_utilisation = 0;

    // Ajouter à la liste
    adr_equipement = InsereListEq(adr_equipement, eq);

    // Mettre à jour le compteur d'équipements dans le bâtiment
    tCell *bat = rechercheBatimentParIdListe(adr_batiment, eq.idBatiment);
    if (bat) {
        bat->elt.nb_equipements++;
    }

    printf("Equipement ajoute avec succes !\n");
}

//  Modifier un équipement
void modifierEquipement() {
    int id;
    tCellEq *eq;

    printf("\n=== Modification d'un equipement ===\n");
    printf("ID de l'equipement a modifier: ");
    scanf("%d", &id);

    eq = rechercheEquipementParId(id);
    if (eq == NULL) {
        printf("Equipement introuvable.\n");
        return;
    }

    printf("\n--- Informations actuelles ---\n");
    printf("1. Nom: %s\n", eq->elt.nom);
    printf("2. Consommation: %.2f kWh/min\n", eq->elt.conso_min);
    printf("3. ID Batiment: %d\n", eq->elt.idBatiment);
    printf("4. ID Type: %d\n", eq->elt.idType);
    printf("5. Etat: %s\n", eq->elt.etat ? "Allume" : "Eteint");

    int choix;
    printf("\nQue voulez-vous modifier ? (0 pour annuler): ");
    scanf("%d", &choix);

    switch(choix) {
        case 1:
            printf("Nouveau nom: ");
            scanf(" %[^\n]", eq->elt.nom);
            break;
        case 2:
            printf("Nouvelle consommation: ");
            scanf("%f", &eq->elt.conso_min);
            break;
        case 3:
            do {
                printf("Nouvel ID batiment: ");
                scanf("%d", &eq->elt.idBatiment);
                if (!batimentExiste(eq->elt.idBatiment)) {
                    printf("Batiment inexistant.\n");
                }
            } while (!batimentExiste(eq->elt.idBatiment));
            break;
        case 4:
            printf("Nouvel ID type: ");
            scanf("%d", &eq->elt.idType);
            break;
        case 5:
            printf("Nouvel etat (0=eteint, 1=allume): ");
            scanf("%d", &eq->elt.etat);
            break;
        default:
            printf("Modification annulee.\n");
            return;
    }

    printf("Equipement modifie avec succes.\n");
}

//  Supprimer un équipement
void supprimerEquipement() {
    int id;
    printf("\n=== Suppression d'un equipement ===\n");
    printf("ID de l'equipement à supprimer: ");
    scanf("%d", &id);

    tCellEq *pred = NULL, *cour = adr_equipement;

    // Recherche de l'équipement
    while (cour) {
        if (cour->elt.id == id) {
            break;
        }
        pred = cour;
        cour = cour->succ;
    }

    if (cour == NULL) {
        printf("Equipement introuvable.\n");
        return;
    }

    // Mettre à jour le compteur du bâtiment
    tCell *bat = rechercheBatimentParIdListe(adr_batiment, cour->elt.idBatiment);
    if (bat) {
        bat->elt.nb_equipements--;
    }

    // Suppression de la liste
    if (pred) {
        pred->succ = cour->succ;
    } else {
        adr_equipement = cour->succ;
    }

    free(cour);
    printf("Equipement supprime avec succes.\n");
}

//  Afficher tous les équipements
void afficherEquipements() {
    tCellEq *cour = adr_equipement;
    int compte = 0;

    printf("\n=== Liste de tous les equipements ===\n");

    if (!cour) {
        printf("Aucun equipement dans la liste.\n");
        return;
    }

    while (cour) {
        compte++;
        printf("\n[%d] ID: %d - %s\n", compte, cour->elt.id, cour->elt.nom);
        printf("    Consommation: %.2f kWh/min | Batiment ID: %d\n",
               cour->elt.conso_min, cour->elt.idBatiment);
        printf("    Type ID: %d | Etat: %s\n",
               cour->elt.idType, cour->elt.etat ? "Allume" : "Eteint");

        cour = cour->succ;
    }
    printf("\nTotal: %d equipement(s)\n", compte);
}

//  Afficher les équipements par bâtiment
void afficherEquipementsParBatiment() {
    int idBatiment;
    tCellEq *cour = adr_equipement;
    int compte = 0;

    printf("\n=== Equipements par batiment ===\n");
    printf("ID du batiment: ");
    scanf("%d", &idBatiment);

    // Vérifier si le bâtiment existe
    if (!batimentExiste(idBatiment)) {
        printf("Batiment inexistant.\n");
        return;
    }

    printf("\nEquipements du batiment ID %d:\n", idBatiment);
    while (cour) {
        if (cour->elt.idBatiment == idBatiment) {
            compte++;
            printf("%d. %s (ID: %d) - %s\n",
                   compte, cour->elt.nom, cour->elt.id,
                   cour->elt.etat ? "Allume" : "Eteint");
        }
        cour = cour->succ;
    }

    if (compte == 0) {
        printf("Aucun equipement dans ce batiment.\n");
    } else {
        printf("Total: %d equipement(s)\n", compte);
    }
}

//  Afficher les équipements par type
void afficherEquipementsParType() {
    int idType;
    tCellEq *cour = adr_equipement;
    int compte = 0;

    printf("\n=== Equipements par type ===\n");
    printf("ID du type: ");
    scanf("%d", &idType);

    printf("\nEquipements de type ID %d:\n", idType);
    while (cour) {
        if (cour->elt.idType == idType) {
            compte++;
            printf("%d. %s (ID: %d) - Batiment: %d - %s\n",
                   compte, cour->elt.nom, cour->elt.id,
                   cour->elt.idBatiment, cour->elt.etat ? "Allume" : "Eteint");
        }
        cour = cour->succ;
    }

    if (compte == 0) {
        printf("Aucun equipement de ce type.\n");
    } else {
        printf("Total: %d equipement(s)\n", compte);
    }
}

//  Fonction supplémentaire : Allumer/éteindre un équipement
void changerEtatEquipement() {
    int id;
    printf("\n=== Changer l'etat d'un equipement ===\n");
    printf("ID de l'equipement: ");
    scanf("%d", &id);

    tCellEq *eq = rechercheEquipementParId(id);
    if (eq == NULL) {
        printf("Equipement introuvable.\n");
        return;
    }

    printf("Equipement: %s (actuellement %s)\n",
           eq->elt.nom, eq->elt.etat ? "allume" : "eteint");
    printf("Nouvel etat (0=eteint, 1=allume): ");
    scanf("%d", &eq->elt.etat);

    if (eq->elt.etat) {
        eq->elt.debut_utilisation = time(NULL);
        printf("Equipement allume.\n");
    } else {
        eq->elt.debut_utilisation = 0;
        printf("Equipement eteint.\n");
    }
}
tCellType* InitCellType(tCellType *cell, TypeEquipement elt, tCellType *succ) {

    if (cell == NULL) {
        cell = alloc(tCellType);
        if (cell == NULL) {
            printf("Erreur d'allocation memoire\n");
            return NULL;
        }
    }

    cell->elt = elt;    // copie directe de toute la structure
    cell->succ = succ;

    return cell;
}

tCellType *InsereListType(tCellType *tete, TypeEquipement elt) {

    // InitCellType fait l'allocation
    tCellType *Nouveau = InitCellType(NULL, elt, NULL);
    if (Nouveau == NULL) {
        printf("Erreur d'allocation memoire\n");
        return tete;
    }

    // Si liste vide
    if (tete == NULL) {
        return Nouveau;
    }

    // Trouver la fin
    tCellType *cour = tete;
    while (cour->succ != NULL) {
        cour = cour->succ;
    }

    // Ajouter à la fin
    cour->succ = Nouveau;

    return tete;
}
// Recherche d'un type par ID
tCellType* rechercheTypeParId(int id) {
    tCellType *cour = adr_types;

    if (adr_types == NULL) {
        return NULL;
    }

    while (cour != NULL) {
        if (cour->elt.id == id) {
            return cour;
        }
        cour = cour->succ;
    }

    return NULL;
}
// Ajouter un type d'équipement
void ajouterTypeEquipement() {
    TypeEquipement type;
    char choix;

    printf("\n=== AJOUT D'UN TYPE D'EQUIPEMENT ===\n");

    // Choix de l'ID
    printf("Voulez-vous saisir l'ID manuellement ? (o/n) : ");
    scanf(" %c", &choix);

    if (choix == 'o' || choix == 'O') {
        do {
            printf("ID du type : ");
            if (scanf("%d", &type.id)!=1) {
                printf("Erreur : L'ID doit etre un entier.\n");
                while(getchar()!='\n');
                continue;
            }
            // Vérifier si l'ID est positif
            if (type.id <= 0) {
                printf("Erreur : L'ID doit etre positif.\n");
                continue;
            }
            if (typeIdExiste(type.id)) {
                printf("Cet ID existe deja. Veuillez en choisir un autre.\n");
                while(getchar()!='\n');
                continue ;
            }
            break;
        } while (1);
    }
    else {
        // ID auto-incrémenté
        int maxId = 0;
        tCellType *cour = adr_types;
        while (cour != NULL) {
            if (cour->elt.id > maxId) {
                maxId = cour->elt.id;
            }
            cour = cour->succ;
        }
        type.id = maxId + 1;
        printf("ID attribue automatiquement : %d\n", type.id);
    }

    // Saisie du nom
    do {
        printf("Entrez le nom : ");
        scanf(" %[^\n]s", type.nom);
        if (estchaine(type.nom)==0 ) {
            printf("Erreur : Le nom du type doit etre une chaine de caractere formee par des lettres seulement.\n");
        }
    }while (!estchaine(type.nom));

    // Saisie de la description
    do {
        printf("Entrez la description du type: ");
        scanf(" %[^\n]s",type.description);
        if (estchaine(type.description)==0 ) {
            printf("Erreur : Le nom du ville doit etre une chaine de caractere formee par des lettres seulement.\n");
        }
    }while (!estchaine(type.description));
    // Insertion dans la liste
    adr_types = InsereListType(adr_types, type);
    printf("Type d'equipement ajoute avec succes !\n");
}

// Modifier un type d'équipement
void modifierTypeEquipement() {
    int id;
    tCellType *type;
    char nouveauNom[50];
    char nouvelleDescription[100];
    int choix;

    printf("\n=== MODIFICATION D'UN TYPE D'EQUIPEMENT ===\n");
    printf("ID du type a modifier : ");
    scanf("%d", &id);

    type = rechercheTypeParId(id);
    if (type == NULL) {
        printf("Type d'equipement introuvable.\n");
        return;
    }

    printf("\n--- Informations actuelles ---\n");
    printf("1. Nom : %s\n", type->elt.nom);
    printf("2. Description : %s\n", type->elt.description);
    printf("3. Annuler\n");

    printf("\nQue voulez-vous modifier ? ");
    scanf("%d", &choix);

    switch(choix) {
        case 1:
            printf("Nouveau nom : ");
            scanf(" %[^\n]", nouveauNom);
            strncpy(type->elt.nom, nouveauNom, sizeof(type->elt.nom) - 1);
            type->elt.nom[sizeof(type->elt.nom) - 1] = '\0';
            printf("Nom modifie avec succes.\n");
            break;

        case 2:
            printf("Nouvelle description : ");
            scanf(" %[^\n]", nouvelleDescription);
            strncpy(type->elt.description, nouvelleDescription, sizeof(type->elt.description) - 1);
            type->elt.description[sizeof(type->elt.description) - 1] = '\0';
            printf("Description modifiee avec succes.\n");
            break;

        case 3:
            printf("Modification annulee.\n");
            return;

        default:
            printf("Choix invalide.\n");
            return;
    }
}

// Supprimer un type d'équipement
void supprimerTypeEquipement() {
    int id;
    tCellType *cour = adr_types;
    tCellType *prec = NULL;
    char confirmation;

    printf("\n=== SUPPRESSION D'UN TYPE D'EQUIPEMENT ===\n");
    printf("ID du type a supprimer : ");
    scanf("%d", &id);

    // Recherche du type à supprimer
    while (cour != NULL && cour->elt.id != id) {
        prec = cour;
        cour = cour->succ;
    }

    if (cour == NULL) {
        printf("Type d'equipement introuvable.\n");
        return;
    }

    // Affichage des informations
    printf("\nType a supprimer :\n");
    printf("ID : %d\n", cour->elt.id);
    printf("Nom : %s\n", cour->elt.nom);
    printf("Description : %s\n", cour->elt.description);

    // Confirmation
    printf("\nVoulez-vous vraiment supprimer ce type ? (o/n) : ");
    scanf(" %c", &confirmation);

    if (confirmation != 'o' && confirmation != 'O') {
        printf("Suppression annulee.\n");
        return;
    }

    // Suppression
    if (prec == NULL) {
        // Suppression de la tête
        adr_types = cour->succ;
    } else {
        prec->succ = cour->succ;
    }

    free(cour);
    printf("Type d'equipement supprime avec succes.\n");
}

// Afficher tous les types d'équipement
void afficherTypeEquipements() {
    tCellType *cour = adr_types;
    int compte = 0;

    printf("\n=== LISTE DES TYPES D'EQUIPEMENT ===\n");

    if (cour == NULL) {
        printf("Aucun type d'equipement enregistre.\n");
        return;
    }

    while (cour != NULL) {
        compte++;
        printf("\n--- Type %d ---\n", compte);
        printf("ID : %d\n", cour->elt.id);
        printf("Nom : %s\n", cour->elt.nom);
        printf("Description : %s\n", cour->elt.description);

        cour = cour->succ;
    }

    printf("\nTotal : %d type(s) d'equipement\n", compte);
}
// Recherche par nom (fonction utilitaire)
tCellType* rechercheTypeParNom(const char* nom) {
    tCellType *cour = adr_types;

    if (adr_types == NULL || nom == NULL) {
        return NULL;
    }

    while (cour != NULL) {
        if (strcmp(cour->elt.nom, nom) == 0) {
            return cour;
        }
        cour = cour->succ;
    }

    return NULL;
}

void afficherDetailsType() {
    int id;
    tCellType *type;

    printf("\n=== DETAILS D'UN TYPE D'EQUIPEMENT ===\n");
    printf("ID du type : ");
    scanf("%d", &id);

    type = rechercheTypeParId(id);
    if (type == NULL) {
        printf("Type d'equipement introuvable.\n");
        return;
    }

    printf("\n--- Détails du type ---\n");
    printf("ID : %d\n", type->elt.id);
    printf("Nom : %s\n", type->elt.nom);
    printf("Description : %s\n", type->elt.description);
}


// Initialisation d'une cellule consommation
tCellConsommation* InitCellConsommation(tCellConsommation *cell, Consommation elt, tCellConsommation *succ) {
    cell->elt = elt;
    cell->succ = succ;
    return cell;
}

// Insertion d'une consommation dans la liste
tCellConsommation* InsereListConsommation(tCellConsommation *tete, Consommation elt) {

    if(tete == NULL) {
        tCellConsommation *Nouveau = alloc(tCellConsommation);
        if(Nouveau == NULL) {
            printf("Erreur d'allocation memoire\n");
            return NULL;
        }
        return InitCellConsommation(Nouveau, elt, NULL);
    }

    tCellConsommation *cour = tete;
    tCellConsommation *prec = NULL;

    while(cour != NULL) {
        prec = cour;
        cour = cour->succ;
    }

    // Allocation
    tCellConsommation *Nouveau = alloc(tCellConsommation);
    if(Nouveau == NULL) {
        printf("Erreur d'allocation memoire\n");
        return tete;
    }

    // Ici, prec ne sera jamais NULL car tete != NULL
    // et on a parcouru au moins une fois la boucle
    prec->succ = InitCellConsommation(Nouveau, elt, NULL);

    return tete;
}

// Recherche d'une consommation par ID
tCellConsommation* rechercheConsommationParId(int id) {
    tCellConsommation *cour = adr_consommations;

    if (adr_consommations == NULL) {
        printf("La Liste des consommations est vide\n");
        return NULL;
    }

    while (cour != NULL) {
        if (cour->elt.id == id) {
            return cour;
        }
        cour = cour->succ;
    }

    return NULL;
}

// Ajouter une consommation
void ajouterConsommation() {
    Consommation conso;

    printf("\n=== Ajout d'une nouvelle consommation ===\n");

    do {
        printf("ID de la consommation: ");
        if (scanf("%d", &conso.id)!=1) {
            printf("Erreur: l'id du  consommation doit etre un entier\n");
            while(getchar()!='\n');
            continue;
        }
        // Vérifier si l'ID est positif
        if (conso.id <= 0) {
            printf("Erreur : L'ID doit etre positif.\n");
            continue;
        }
        if (rechercheConsommationParId(conso.id) != NULL) {
            printf("Cet ID existe deja. Veuillez en choisir un autre.\n");
            while(getchar()!='\n');
            continue;
        }
        break ;
    } while (1);

    do {
        printf("ID de l'equipement: ");
        scanf("%d", &conso.idEquipement);
        if (!equipementExiste(conso.idEquipement)) {
            printf("Cet equipement n'existe pas. Veuillez entrer un ID valide.\n");
        }
    } while (!equipementExiste(conso.idEquipement));

    do {
        printf("Consommation par minute (kWh): ");
        if ((scanf("%f", &conso.consommation)!=1)) {
            printf("Erreur : La consommation doit etre un float.\n");
            while(getchar()!='\n');
            continue;
        }
        // Vérifier si la consommation est positive
        if (conso.consommation <= 0.0) {
            printf("Erreur : la consommation doit etre positive.\n");
            while(getchar()!='\n');
            continue;
        }
        break;
    }while (1);

    // Date/heure de début (actuelle)
    conso.debut = time(NULL);

    // Date/heure de fin (pour cet instant égale à début)
    conso.fin = conso.debut;

    // Ajouter à la liste
    adr_consommations = InsereListConsommation(adr_consommations, conso);

    printf("Consommation ajoutee avec succes !\n");
}

// Afficher toutes les consommations
void afficherConsommations() {
    tCellConsommation *cour = adr_consommations;
    int compte = 0;

    printf("\n=== Liste de toutes les consommations ===\n");

    if (!cour) {
        printf("Aucune consommation dans la liste.\n");
        return;
    }

    while (cour) {
        compte++;
        printf("\n[%d] ID: %d - Equipement ID: %d\n", compte, cour->elt.id, cour->elt.idEquipement);
        printf("    Consommation: %.2f kWh | Debut: %ld | Fin: %ld\n",
               cour->elt.consommation, cour->elt.debut, cour->elt.fin);

        cour = cour->succ;
    }
    printf("\nTotal: %d consommation(s)\n", compte);
}

// Afficher les consommations par équipement
void afficherConsommationsParEquipement() {
    int idEquipement;
    tCellConsommation *cour = adr_consommations;
    int compte = 0;
    float total = 0.0;

    printf("\n=== Consommations par equipement ===\n");
    printf("ID de l'equipement: ");
    scanf("%d", &idEquipement);

    printf("\nConsommations de l'equipement ID %d:\n", idEquipement);
    while (cour) {
        if (cour->elt.idEquipement == idEquipement) {
            compte++;
            total += cour->elt.consommation;
            printf("%d. Consommation ID: %d - %.2f kWh\n",
                   compte, cour->elt.id, cour->elt.consommation);
        }
        cour = cour->succ;
    }

    if (compte == 0) {
        printf("Aucune consommation pour cet equipement.\n");
    } else {
        printf("Total: %d consommation(s) - %.2f kWh\n", compte, total);
    }
}

// Tri par consommation (kWh) ascendant
tCellConsommation* trierConsommationsParValeurAsc(tCellConsommation *tete) {
    if (tete == NULL || tete->succ == NULL) {
        return tete;
    }

    int changement;
    tCellConsommation *cour;
    tCellConsommation *dernier = NULL;

    do {
        changement = 0;
        cour = tete;

        while (cour->succ != dernier) {
            if (cour->elt.consommation > cour->succ->elt.consommation) {
                // Échanger les données
                Consommation temp = cour->elt;
                cour->elt = cour->succ->elt;
                cour->succ->elt = temp;
                changement = 1;
            }
            cour = cour->succ;
        }
        dernier = cour;
    } while (changement);

    return tete;
}

// Tri par consommation (kWh) descendant
tCellConsommation* trierConsommationsParValeurDesc(tCellConsommation *tete) {
    if (tete == NULL || tete->succ == NULL) {
        return tete;
    }

    int changement;
    tCellConsommation *cour;
    tCellConsommation *dernier = NULL;

    do {
        changement = 0;
        cour = tete;

        while (cour->succ != dernier) {
            if (cour->elt.consommation < cour->succ->elt.consommation) {
                // Échanger les données
                Consommation temp = cour->elt;
                cour->elt = cour->succ->elt;
                cour->succ->elt = temp;
                changement = 1;
            }
            cour = cour->succ;
        }
        dernier = cour;
    } while (changement);

    return tete;
}

// Allumer un équipement
void allumerEquipement() {
    int id;
    tCellEq *eq;

    printf("\n=== ALLUMER UN EQUIPEMENT ===\n");
    printf("ID de l'equipement a allumer : ");
    scanf("%d", &id);

    eq = rechercheEquipementParId(id);
    if (eq == NULL) {
        printf("Equipement introuvable.\n");
        return;
    }

    if (eq->elt.etat == 1) {
        printf("L'equipement '%s' est deja allume.\n", eq->elt.nom);
        return;
    }

    eq->elt.etat = 1;
    eq->elt.debut_utilisation = time(NULL);

    printf("Equipement '%s' allume avec succes.\n", eq->elt.nom);
    printf("Heure de debut : %ld\n", eq->elt.debut_utilisation);
}

// Éteindre un équipement
void eteindreEquipement() {
    int id;
    tCellEq *eq;

    printf("\n=== ETEINDRE UN EQUIPEMENT ===\n");
    printf("ID de l'equipement a eteindre : ");
    scanf("%d", &id);

    eq = rechercheEquipementParId(id);
    if (eq == NULL) {
        printf("Equipement introuvable.\n");
        return;
    }

    if (eq->elt.etat == 0) {
        printf("L'equipement '%s' est deja eteint.\n", eq->elt.nom);
        return;
    }

    eq->elt.etat = 0;

    // Calculer la consommation si on a une date de début
    if (eq->elt.debut_utilisation > 0) {
        time_t maintenant = time(NULL);
        float duree = difftime(maintenant, eq->elt.debut_utilisation) / 60.0; // en minutes
        float consommation = duree * eq->elt.conso_min;

        printf("Equipement '%s' eteint avec succes.\n", eq->elt.nom);
        printf("Duree d'utilisation : %.2f minutes\n", duree);
        printf("Consommation estimee : %.2f kWh\n", consommation);

        // Optionnel : enregistrer cette consommation
        printf("Voulez-vous enregistrer cette consommation ? (o/n) : ");
        char choix;
        scanf(" %c", &choix);

        if (choix == 'o' || choix == 'O') {
            Consommation nouvelleConso;

            // Générer un ID unique
            int nouvelId = 1;
            tCellConsommation *cour = adr_consommations;
            while (cour != NULL) {
                if (cour->elt.id >= nouvelId) {
                    nouvelId = cour->elt.id + 1;
                }
                cour = cour->succ;
            }

            nouvelleConso.id = nouvelId;
            nouvelleConso.idEquipement = eq->elt.id;
            nouvelleConso.debut = eq->elt.debut_utilisation;
            nouvelleConso.fin = maintenant;
            nouvelleConso.consommation = consommation;

            adr_consommations = InsereListConsommation(adr_consommations, nouvelleConso);
            printf("Consommation enregistree (ID: %d).\n", nouvelId);
        }
    } else {
        printf("Equipement '%s' eteint avec succes.\n", eq->elt.nom);
    }

    eq->elt.debut_utilisation = 0;
}


// Afficher l'état de tous les équipements
void afficherEtatEquipements() {
    tCellEq *cour = adr_equipement;
    int compte = 0;
    int allumes = 0;
    int eteints = 0;
    float consoTotale = 0.0;

    printf("\n=== ETAT DES EQUIPEMENTS ===\n");

    if (cour == NULL) {
        printf("Aucun equipement enregistre.\n");
        return;
    }

    while (cour != NULL) {
        compte++;

        if (cour->elt.etat == 1) {
            allumes++;

            // Calculer la consommation en cours si l'équipement est allumé
            if (cour->elt.debut_utilisation > 0) {
                time_t maintenant = time(NULL);
                float duree = difftime(maintenant, cour->elt.debut_utilisation) / 60.0;
                float consoActuelle = duree * cour->elt.conso_min;
                consoTotale += consoActuelle;

                printf("[%d] %s (ID: %d) - ALLUME depuis %.2f min\n",
                       compte, cour->elt.nom, cour->elt.id, duree);
                printf("     Consommation actuelle : %.2f kWh\n", consoActuelle);
            } else {
                printf("[%d] %s (ID: %d) - ALLUME\n",
                       compte, cour->elt.nom, cour->elt.id);
            }
        } else {
            eteints++;
            printf("[%d] %s (ID: %d) - ETEINT\n",
                   compte, cour->elt.nom, cour->elt.id);
        }

        printf("     Batiment: %d | Type: %d | Conso/min: %.2f kWh\n",
               cour->elt.idBatiment, cour->elt.idType, cour->elt.conso_min);

        cour = cour->succ;
    }

    printf("\n--- STATISTIQUES ---\n");
    printf("Total equipements : %d\n", compte);
    printf("Equipements allumes : %d\n", allumes);
    printf("Equipements eteints : %d\n", eteints);
    printf("Consommation totale en cours : %.2f kWh\n", consoTotale);
}

// Afficher les équipements d'un bâtiment avec leurs états
void afficherEquipementsBatimentAvecEtats() {
    int idBatiment;
    tCellEq *cour = adr_equipement;
    int compte = 0;
    int allumes = 0;
    int eteints = 0;
    float consoTotale = 0.0;

    printf("\n=== EQUIPEMENTS PAR BATIMENT (AVEC ETATS) ===\n");
    printf("ID du batiment : ");
    scanf("%d", &idBatiment);

    // Vérifier si le bâtiment existe
    if (!batimentExiste(idBatiment)) {
        printf("Batiment ID %d inexistant.\n", idBatiment);
        return;
    }

    printf("\n--- Equipements du batiment ID %d ---\n", idBatiment);

    // Parcourir tous les équipements
    while (cour != NULL) {
        if (cour->elt.idBatiment == idBatiment) {
            compte++;

            printf("\n[%d] %s (ID: %d)\n", compte, cour->elt.nom, cour->elt.id);

            // Afficher l'état
            if (cour->elt.etat == 1) {
                allumes++;
                printf("   Etat : ALLUME\n");

                // Calculer la durée si l'équipement est allumé
                if (cour->elt.debut_utilisation > 0) {
                    time_t maintenant = time(NULL);
                    float duree = difftime(maintenant, cour->elt.debut_utilisation) / 60.0;
                    float consoActuelle = duree * cour->elt.conso_min;
                    consoTotale += consoActuelle;

                    printf("   Allume depuis : %.2f minutes\n", duree);
                    printf("   Consommation actuelle : %.2f kWh\n", consoActuelle);
                }
            } else {
                eteints++;
                printf("   Etat : ETEINT\n");
            }

            // Informations supplémentaires
            printf("   Type ID : %d\n", cour->elt.idType);
            printf("   Consommation/minute : %.2f kWh\n", cour->elt.conso_min);
        }

        cour = cour->succ;
    }
}
    // 1. Statistiques par équipement
void statistiquesParEquipement() {
    int id;
    printf("\n=== STATISTIQUES EQUIPEMENT ===\n");
    printf("ID equipement : ");
    scanf("%d", &id);

    tCellEq *eq = rechercheEquipementParId(id);
    if (eq == NULL) {
        printf("Equipement introuvable.\n");
        return;
    }

    printf("\n%s (ID: %d)\n", eq->elt.nom, eq->elt.id);
    printf("Batiment: %d | Type: %d\n", eq->elt.idBatiment, eq->elt.idType);
    printf("Etat: %s | Conso/min: %.2f kWh\n",
           eq->elt.etat ? "ALLUME" : "ETEINT", eq->elt.conso_min);

    // Consommations enregistrées
    tCellConsommation *cour = adr_consommations;
    int nb = 0;
    float total = 0.0;

    while (cour != NULL) {
        if (cour->elt.idEquipement == id) {
            nb++;
            total += cour->elt.consommation;
        }
        cour = cour->succ;
    }

    printf("\nSessions: %d\n", nb);
    printf("Consommation totale: %.2f kWh\n", total);
    if (nb > 0) printf("Moyenne/session: %.2f kWh\n", total/nb);
}

// 2. Statistiques par bâtiment
void statistiquesParBatiment() {
    int id;
    printf("\n=== STATISTIQUES BATIMENT ===\n");
    printf("ID batiment : ");
    scanf("%d", &id);

    tCell *bat = rechercheBatimentParIdListe(adr_batiment, id);
    if (bat == NULL) {
        printf("Batiment introuvable.\n");
        return;
    }

    printf("\n%s (ID: %d)\n", bat->elt.nom_batiment, bat->elt.id_batiment);
    printf("Capacite: %d/%d\n", bat->elt.nb_equipements, bat->elt.nb_equipements);

    // Compter équipements
    tCellEq *cour = adr_equipement;
    int nbEq = 0, nbAllumes = 0;
    float consoPot = 0.0, consoAct = 0.0;

    while (cour != NULL) {
        if (cour->elt.idBatiment == id) {
            nbEq++;
            consoPot += cour->elt.conso_min;

            if (cour->elt.etat == 1) {
                nbAllumes++;
                if (cour->elt.debut_utilisation > 0) {
                    float duree = difftime(time(NULL), cour->elt.debut_utilisation) / 60.0;
                    consoAct += duree * cour->elt.conso_min;
                }
            }
        }
        cour = cour->succ;
    }

    printf("\nEquipements: %d\n", nbEq);
    printf("Allumes: %d | Eteints: %d\n", nbAllumes, nbEq - nbAllumes);
    printf("Conso potentielle/min: %.2f kWh\n", consoPot);
    printf("Conso actuelle: %.2f kWh\n", consoAct);
}


// 3. Statistiques par type d'équipement
void statistiquesParType() {
    int id;
    printf("\n=== STATISTIQUES TYPE ===\n");
    printf("ID type : ");
    scanf("%d", &id);

    tCellType *type = rechercheTypeParId(id);
    if (type == NULL) {
        printf("Type introuvable.\n");
        return;
    }

    printf("\n%s (ID: %d)\n", type->elt.nom, type->elt.id);
    printf("Description: %s\n", type->elt.description);

    // Compter équipements de ce type
    tCellEq *cour = adr_equipement;
    int nb = 0, nbAllumes = 0;
    float consoPot = 0.0;

    while (cour != NULL) {
        if (cour->elt.idType == id) {
            nb++;
            consoPot += cour->elt.conso_min;
            if (cour->elt.etat == 1) nbAllumes++;
        }
        cour = cour->succ;
    }

    printf("\nEquipements: %d\n", nb);
    printf("Allumes: %d | Eteints: %d\n", nbAllumes, nb - nbAllumes);
    printf("Conso potentielle/min: %.2f kWh\n", consoPot);

    // Consommation historique
    tCellConsommation *c = adr_consommations;
    int nbConso = 0;
    float totalConso = 0.0;

    while (c != NULL) {
        tCellEq *eq = rechercheEquipementParId(c->elt.idEquipement);
        if (eq != NULL && eq->elt.idType == id) {
            nbConso++;
            totalConso += c->elt.consommation;
        }
        c = c->succ;
    }

    printf("Sessions historiques: %d\n", nbConso);
    printf("Conso historique: %.2f kWh\n", totalConso);
}

// 4. Statistiques sur intervalle de temps
void statistiquesIntervalle() {
    int j1, m1, a1, j2, m2, a2;

    printf("\n=== STATISTIQUES INTERVALLE ===\n");
    printf("Date debut (JJ MM AAAA) : ");
    scanf("%d %d %d", &j1, &m1, &a1);
    printf("Date fin (JJ MM AAAA) : ");
    scanf("%d %d %d", &j2, &m2, &a2);

    struct tm tm1 = {0}, tm2 = {0};
    tm1.tm_year = a1 - 1900;
    tm1.tm_mon = m1 - 1;
    tm1.tm_mday = j1;
    tm2.tm_year = a2 - 1900;
    tm2.tm_mon = m2 - 1;
    tm2.tm_mday = j2;

    time_t debut = mktime(&tm1);
    time_t fin = mktime(&tm2);

    printf("\nDu %02d/%02d/%04d au %02d/%02d/%04d\n", j1, m1, a1, j2, m2, a2);

    // Analyser consommations dans l'intervalle
    tCellConsommation *c = adr_consommations;
    int nb = 0;
    float total = 0.0;

    while (c != NULL) {
        if (c->elt.debut >= debut && c->elt.debut <= fin) {
            nb++;
            total += c->elt.consommation;
        }
        c = c->succ;
    }

    printf("\nSessions: %d\n", nb);
    printf("Consommation totale: %.2f kWh\n", total);

    if (nb > 0) {
        float heures = difftime(fin, debut) / 3600.0;
        printf("Conso moyenne/heure: %.2f kWh\n", total/heures);
    }
}
// les fonctions d'ecrire les cordonnees dans un fichiers .txt
void sauvegarderBatimentsTxt(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    fprintf(fichier, "========== BATIMENTS ==========\n\n");
    tCell *cour = adr_batiment;
    int compte = 0;

    while (cour != NULL) {
        compte++;
        fprintf(fichier, "Batiment %d:\n", compte);
        fprintf(fichier, "  ID: %d\n", cour->elt.id_batiment);
        fprintf(fichier, "  Nom: %s\n", cour->elt.nom_batiment);
        fprintf(fichier, "  Adresse: %s\n", cour->elt.adresse);
        fprintf(fichier, "  Capacite: %d/%d\n", cour->elt.nb_equipements, cour->elt.equipements);
        fprintf(fichier, "\n");
        cour = cour->succ;
    }
    fprintf(fichier, "Total: %d batiment(s)\n", compte);

    fclose(fichier);
    printf("Batiments sauvegardes dans %s (%d batiment(s))\n", nomFichier, compte);
}

void sauvegarderEquipementsTxt(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    fprintf(fichier, "========== EQUIPEMENTS ==========\n\n");
    tCellEq *cour = adr_equipement;
    int compte = 0;

    while (cour != NULL) {
        compte++;
        fprintf(fichier, "Equipement %d:\n", compte);
        fprintf(fichier, "  ID: %d\n", cour->elt.id);
        fprintf(fichier, "  Nom: %s\n", cour->elt.nom);
        fprintf(fichier, "  Batiment ID: %d\n", cour->elt.idBatiment);
        fprintf(fichier, "  Type ID: %d\n", cour->elt.idType);
        fprintf(fichier, "  Consommation: %.2f kWh/min\n", cour->elt.conso_min);
        fprintf(fichier, "  Etat: %s\n", cour->elt.etat ? "Allume" : "Eteint");
        fprintf(fichier, "\n");
        cour = cour->succ;
    }
    fprintf(fichier, "Total: %d equipement(s)\n", compte);

    fclose(fichier);
    printf("Equipements sauvegardes dans %s (%d equipement(s))\n", nomFichier, compte);
}

void sauvegarderTypesTxt(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    fprintf(fichier, "========== TYPES D'EQUIPEMENT ==========\n\n");
    tCellType *cour = adr_types;
    int compte = 0;

    while (cour != NULL) {
        compte++;
        fprintf(fichier, "Type %d:\n", compte);
        fprintf(fichier, "  ID: %d\n", cour->elt.id);
        fprintf(fichier, "  Nom: %s\n", cour->elt.nom);
        fprintf(fichier, "  Description: %s\n", cour->elt.description);
        fprintf(fichier, "\n");
        cour = cour->succ;
    }
    fprintf(fichier, "Total: %d type(s)\n", compte);

    fclose(fichier);
    printf("Types sauvegardes dans %s (%d type(s))\n", nomFichier, compte);
}

void sauvegarderConsommationsTxt(const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    fprintf(fichier, "========== CONSOMMATIONS ==========\n\n");
    tCellConsommation *cour = adr_consommations;
    int compte = 0;

    while (cour != NULL) {
        compte++;
        fprintf(fichier, "Consommation %d:\n", compte);
        fprintf(fichier, "  ID: %d\n", cour->elt.id);
        fprintf(fichier, "  Equipement ID: %d\n", cour->elt.idEquipement);

        char debutStr[20], finStr[20];
        struct tm debut_tm;
        struct tm fin_tm;

        debut_tm = *localtime(&cour->elt.debut);
        fin_tm   = *localtime(&cour->elt.fin);

        strftime(debutStr, sizeof(debutStr), "%Y-%m-%d %H:%M", &debut_tm);
        strftime(finStr, sizeof(finStr), "%Y-%m-%d %H:%M", &fin_tm);

        fprintf(fichier, "  Debut: %s\n", debutStr);
        fprintf(fichier, "  Fin: %s\n", finStr);
        fprintf(fichier, "  Consommation: %.2f kWh\n", cour->elt.consommation);
        fprintf(fichier, "\n");
        cour = cour->succ;
    }
    fprintf(fichier, "Total: %d consommation(s)\n", compte);

    fclose(fichier);
    printf("Consommations sauvegardees dans %s (%d consommation(s))\n", nomFichier, compte);
}