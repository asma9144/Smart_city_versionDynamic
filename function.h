#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED


#include <stdio.h>
#include <string.h>
#include<time.h>

#define MAX_BATIMENTS 100
#define MAX_EQUIP_PAR_BATIMENT 300


// Structure représentant un bâtiment

typedef struct{
    int jour;
    int mois;
    int annee;
}Date;

typedef struct{
    char rue[100];
    char ville[50];
    int code_postal;
}Adresse;

typedef struct {
    int id_batiment;
    char nom_batiment[50];
    Adresse adresse;
    int equipements[MAX_EQUIP_PAR_BATIMENT];
    int nb_equipements;
}Batiment;


typedef struct sCell
{
    Batiment   elt;
	struct sCell *succ;
}tCell;
extern tCell *adr_batiment;
// Prototypes des fonctions de gestion des bâtiments
void ajouterBatiment() ;
void modifierBatiment();
void SupprimeList(tCell **adr_batiment, int id);
void afficherBatimentsListe(tCell *adr_batiment);
tCell* rechercheBatimentParIdListe(tCell *adr_batiment, int id);

// Structure représentant un équipement électrique

typedef struct {
    int id;                 // identifiant de l'équipement
    char nom[50];           // nom de l'équipement
    float conso_min;        // consommation par minute
    int idBatiment;         // identifiant du bâtiment associé
    int idType;             // identifiant du type d'équipement
    int etat;               // état : 0 = éteint, 1 = allumé
    time_t debut_utilisation;
} Equipement;

// Cellule pour la liste chaînée d'équipements
typedef struct sCellEq {
    Equipement elt;
    struct sCellEq *succ;
} tCellEq;
extern tCellEq *adr_equipement;


// Prototypes des fonctions équipements
void ajouterEquipement();
void modifierEquipement();
void supprimerEquipement();
void afficherEquipements();
void afficherEquipementsParBatiment();
void afficherEquipementsParType();
void changerEtatEquipement();


#endif // FUNCTION_H_INCLUDED
