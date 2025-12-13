#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

#define MAX_EQUIP_PAR_BATIMENT 300


// Structure representant un batiment
typedef struct{
    char rue[100];
    char ville[50];
    int code_postal;
}Adresse;
// Structure representant un batiment
typedef struct {

    int id_batiment;
    char nom_batiment[50];
    Adresse adresse;
    int equipements[MAX_EQUIP_PAR_BATIMENT];
    int nb_equipements;

}Batiment;


typedef struct sCell{

    Batiment  elt;
	struct sCell *succ;

}tCell;

extern tCell *adr_batiment;

// Prototypes des fonctions de gestion des batiments

void ajouterBatiment() ;
void modifierBatiment();
void Supprimer_Noeud(tCell **adr_batiment, int id);
void afficherBatimentsListe(tCell *adr_batiment);
tCell* rechercheBatimentParIdListe(tCell *adr_batiment, int id);

// Structure representant un equipement electrique

typedef struct {
    int id;                 // identifiant de l'equipement
    char nom[50];           // nom de l'equipement
    float conso_min;        // consommation par minute
    int idBatiment;         // identifiant du batiment associe
    int idType;             // identifiant du type d'equipement
    int etat;               // etat : 0 = eteint, 1 = allume
    time_t debut_utilisation;
} Equipement;

// Cellule pour la liste chainnee d'equipements

typedef struct sCellEq {

    Equipement elt;
    struct sCellEq *succ;

} tCellEq;
// variable globale :
extern tCellEq *adr_equipement;


// Prototypes des fonctions equipements
void ajouterEquipement();
void modifierEquipement();
void supprimerEquipement();
void afficherEquipements();
void afficherEquipementsParBatiment();
void afficherEquipementsParType();
void changerEtatEquipement();




// Structure de base du type d'équipement
typedef struct {
    int id;
    char nom[50];
    char description[100];
} TypeEquipement;

// Structure de cellule pour la liste chaînée
typedef struct CellType {
    TypeEquipement elt;
    struct CellType* succ;
} tCellType;

// variable globale :
extern tCellType* adr_types ;


// Prototypes des fonctions TypeEquipements
void ajouterTypeEquipement();
void modifierTypeEquipement();
void supprimerTypeEquipement();
void afficherTypeEquipements();
tCellType* rechercheTypeParNom(const char* nom);
void afficherDetailsType();

// Structure de base du consommation
typedef struct {
    int id;                     // identifiant de la consommation
    int idEquipement;           // identifiant de l'équipement utilisé
    time_t debut;         // date/heure de début
    time_t fin;           // date/heure de fin
    float consommation;         // consommation calculée
} Consommation;

// Structure de cellule pour la liste chaînée
typedef struct CellConsommation {
    Consommation elt;               // Donnée de consommation
    struct CellConsommation* succ;  // Pointeur vers la cellule suivante
} tCellConsommation;
// variable globale :
extern tCellConsommation* adr_consommations  ;

// Prototypes des fonctions du consommation
void ajouterConsommation() ;
void afficherConsommations() ;
void afficherConsommationsParEquipement();
tCellConsommation* trierConsommationsParValeurAsc(tCellConsommation *tete);
tCellConsommation* trierConsommationsParValeurDesc(tCellConsommation *tete);


// Utilisation des équipements électriques
void allumerEquipement();
void eteindreEquipement();
void afficherEtatEquipements();
void afficherEquipementsBatimentAvecEtats();


// Prototypes des fonctions du statistique

void statistiquesParEquipement();
void statistiquesParBatiment();
void statistiquesParType() ;
void statistiquesIntervalle();

// Prototypes des fonctions du Sauvegarde .txt
void sauvegarderBatimentsTxt(const char* nomFichier);
void sauvegarderEquipementsTxt(const char* nomFichier);
void sauvegarderTypesTxt(const char* nomFichier);
void sauvegarderConsommationsTxt(const char* nomFichier) ;

#endif // FUNCTION_H_INCLUDED
