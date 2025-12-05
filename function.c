#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#define alloc(t) (t*) malloc(sizeof(t))
#include "function.h"

tCell *adr_batiment = NULL;
tCellEq *adr_equipement = NULL;

tCell *InitCell (tCell *cell, Batiment elt, tCell *succ){

	cell->elt= elt ;
	cell->succ = succ;
	return cell;

}

tCell *InsereList(tCell *tete, Batiment elt){

	if(tete == NULL) {
        tCell *Nouveau = alloc(tCell);
        if(Nouveau == NULL) {
            printf("Erreur d'allocation mémoire\n");
            return NULL;
        }
        return InitCell(Nouveau, elt, NULL);
    }

    tCell *P = tete;
    tCell *prec = NULL;

    while(P != NULL){

        prec = P;
        P = P->succ;

    }

    tCell *NouveauBatiment = alloc(tCell);
    if(NouveauBatiment == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return tete;
    }

    tCell *Nouveau= InitCell(NouveauBatiment, elt, NULL);

    prec->succ = Nouveau;

	return tete;

}


// Recherche d'un batiment par ID

tCell* rechercheBatimentParId(int id) {
    tCell *cour = adr_batiment;

    if (adr_batiment == NULL) {
        return NULL;
    }

    while (cour) {
        if (cour->elt.id_batiment == id) {
            return cour;
        }
        cour = cour->succ;
    }

    return NULL;
}

// ajout d'un b�timent

void ajouterBatiment()
{

    Batiment b;
    do{
        printf("\n donner id_batiment :");
        scanf("%d",&b.id_batiment);
    }while ((int)b.id_batiment!=b.id_batiment);

    printf("Entrez le nom du b�timent: ");
    scanf(" %[^\n]s", b.nom_batiment);
    printf("Entrez la rue: ");
    scanf(" %[^\n]s", b.adresse.rue);
    printf("Entrez la ville: ");
    scanf(" %[^\n]s", b.adresse.ville);
    printf("Entrez le code postal: ");
    scanf("%d", &b.adresse.code_postal);
    b.nb_equipements = 0;

    adr_batiment=InsereList(adr_batiment,b);
    printf("B�timent ajout� avec succ�s ! ID: %d\n", b.id_batiment);

}


tCell* VerifierExistence_Element(tCell *tete , int val){

	if(tete == NULL) {
        return NULL; // Liste vide
    }
    
    while(tete){
		
        if(tete->elt.id_batiment==val){

            return tete;

		} else {
            
            tete = tete->succ;
        
        }

	}

	return NULL;
}


void modifierBatiment() {
    int id;
    tCell *bat;
    printf("Entrez l'ID du bâtiment à modifier: ");
    scanf("%d", &id);
    bat=ParcourList(adr_batiment ,id);
    if (bat==NULL){
        printf("Bâtiment introuvable.\n");
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
    printf("Bâtiment modifié avec succès.\n");

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

        printf("Batiment supprimé avec succès !\n");
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
        printf("%d. ID: %d | Nom: %s | Adresse: %s, %s %d | Nb �quipements: %d\n",
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
            printf("BBatiment trouvé après %d itération(s)\n", compteur);
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
        tCellEq *Nouveau = (tCellEq*)malloc(sizeof(tCellEq));
        if(Nouveau == NULL) {
            printf("Erreur d'allocation mémoire\n");
            return NULL;
        }
        return InitCellEq(Nouveau, elt, NULL);
    }

    tCellEq *cour = tete, *pred = NULL;

    while(cour) {
        pred = cour;
        cour = cour->succ;
    }

    tCellEq *nouveau = (tCellEq*)malloc(sizeof(tCellEq));
    if(nouveau == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return tete;
    }

    if(pred)
        pred->succ = InitCellEq(nouveau, elt, NULL);
    else
        tete = InitCellEq(nouveau, elt, NULL);

    return tete;

}

// Recherche d'un équipement par ID

tCellEq* rechercheEquipementParId(int id) {
    tCellEq *cour = adr_equipement;

    if (adr_equipement == NULL) {
        printf("La Liste des équipements est vide\n");
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

//  Ajouter un �quipement
void ajouterEquipement() {
    Equipement eq;

    // Saisie des données
    printf("\n=== Ajout d'un nouvel équipement ===\n");

    do {
        printf("ID de l'équipement: ");
        scanf("%d", &eq.id);
        if (rechercheEquipementParId(eq.id) != NULL) {
            printf("Cet ID existe d�j�. Veuillez en choisir un autre.\n");
        }
    } while (rechercheEquipementParId(eq.id) != NULL);

    printf("Nom de l'�quipement: ");
    scanf(" %[^\n]", eq.nom);

    printf("Consommation par minute (kWh): ");
    scanf("%f", &eq.conso_min);

    do {
        printf("ID du batiment associé: ");
        scanf("%d", &eq.idBatiment);
        if (!batimentExiste(eq.idBatiment)) {
            printf("Ce batiment n'existe pas. Veuillez entrer un ID valide.\n");
        }
    } while (!batimentExiste(eq.idBatiment));

    printf("ID du type d'équipement: ");
    scanf("%d", &eq.idType);

    eq.etat = 0;  // Par défaut éteint
    eq.debut_utilisation = 0;

    // Ajouter à la liste
    adr_equipement = InsereListEq(adr_equipement, eq);

    // Mettre à jour le compteur d'équipements dans le bâtiment
    tCell *bat = rechercheBatimentParIdListe(adr_batiment, eq.idBatiment);
    if (bat) {
        bat->elt.nb_equipements++;
    }

    printf("Équipement ajouté avec succès !\n");
}

//  Modifier un équipement
void modifierEquipement() {
    int id;
    tCellEq *eq;

    printf("\n=== Modification d'un équipement ===\n");
    printf("ID de l'équipement à modifier: ");
    scanf("%d", &id);

    eq = rechercheEquipementParId(id);
    if (eq == NULL) {
        printf("Équipement introuvable.\n");
        return;
    }

    printf("\n--- Informations actuelles ---\n");
    printf("1. Nom: %s\n", eq->elt.nom);
    printf("2. Consommation: %.2f kWh/min\n", eq->elt.conso_min);
    printf("3. ID Bâtiment: %d\n", eq->elt.idBatiment);
    printf("4. ID Type: %d\n", eq->elt.idType);
    printf("5. État: %s\n", eq->elt.etat ? "Allumé" : "Éteint");

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
                printf("Nouvel ID bâtiment: ");
                scanf("%d", &eq->elt.idBatiment);
                if (!batimentExiste(eq->elt.idBatiment)) {
                    printf("Bâtiment inexistant.\n");
                }
            } while (!batimentExiste(eq->elt.idBatiment));
            break;
        case 4:
            printf("Nouvel ID type: ");
            scanf("%d", &eq->elt.idType);
            break;
        case 5:
            printf("Nouvel état (0=éteint, 1=allumé): ");
            scanf("%d", &eq->elt.etat);
            break;
        default:
            printf("Modification annulée.\n");
            return;
    }

    printf("Équipement modifié avec succès.\n");
}

//  Supprimer un équipement
void supprimerEquipement() {
    int id;
    printf("\n=== Suppression d'un équipement ===\n");
    printf("ID de l'équipement à supprimer: ");
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
        printf("Équipement introuvable.\n");
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
    printf("Équipement supprimé avec succès.\n");
}

//  Afficher tous les équipements
void afficherEquipements() {
    tCellEq *cour = adr_equipement;
    int compte = 0;

    printf("\n=== Liste de tous les équipements ===\n");

    if (!cour) {
        printf("Aucun équipement dans la liste.\n");
        return;
    }

    while (cour) {
        compte++;
        printf("\n[%d] ID: %d - %s\n", compte, cour->elt.id, cour->elt.nom);
        printf("    Consommation: %.2f kWh/min | Bâtiment ID: %d\n",
               cour->elt.conso_min, cour->elt.idBatiment);
        printf("    Type ID: %d | État: %s\n",
               cour->elt.idType, cour->elt.etat ? "Allumé" : "Éteint");

        cour = cour->succ;
    }
    printf("\nTotal: %d équipement(s)\n", compte);
}

//  Afficher les équipements par bâtiment
void afficherEquipementsParBatiment() {
    int idBatiment;
    tCellEq *cour = adr_equipement;
    int compte = 0;

    printf("\n=== Équipements par bâtiment ===\n");
    printf("ID du bâtiment: ");
    scanf("%d", &idBatiment);

    // Vérifier si le bâtiment existe
    if (!batimentExiste(idBatiment)) {
        printf("Bâtiment inexistant.\n");
        return;
    }

    printf("\nÉquipements du bâtiment ID %d:\n", idBatiment);
    while (cour) {
        if (cour->elt.idBatiment == idBatiment) {
            compte++;
            printf("%d. %s (ID: %d) - %s\n",
                   compte, cour->elt.nom, cour->elt.id,
                   cour->elt.etat ? "Allumé" : "Éteint");
        }
        cour = cour->succ;
    }

    if (compte == 0) {
        printf("Aucun équipement dans ce bâtiment.\n");
    } else {
        printf("Total: %d équipement(s)\n", compte);
    }
}

//  Afficher les équipements par type
void afficherEquipementsParType() {
    int idType;
    tCellEq *cour = adr_equipement;
    int compte = 0;

    printf("\n=== Équipements par type ===\n");
    printf("ID du type: ");
    scanf("%d", &idType);

    printf("\nÉquipements de type ID %d:\n", idType);
    while (cour) {
        if (cour->elt.idType == idType) {
            compte++;
            printf("%d. %s (ID: %d) - Bâtiment: %d - %s\n",
                   compte, cour->elt.nom, cour->elt.id,
                   cour->elt.idBatiment, cour->elt.etat ? "Allumé" : "Éteint");
        }
        cour = cour->succ;
    }

    if (compte == 0) {
        printf("Aucun équipement de ce type.\n");
    } else {
        printf("Total: %d équipement(s)\n", compte);
    }
}

//  Fonction supplémentaire : Allumer/éteindre un équipement
void changerEtatEquipement() {
    int id;
    printf("\n=== Changer l'état d'un équipement ===\n");
    printf("ID de l'équipement: ");
    scanf("%d", &id);

    tCellEq *eq = rechercheEquipementParId(id);
    if (eq == NULL) {
        printf("Équipement introuvable.\n");
        return;
    }

    printf("Équipement: %s (actuellement %s)\n",
           eq->elt.nom, eq->elt.etat ? "allumé" : "éteint");
    printf("Nouvel état (0=éteint, 1=allumé): ");
    scanf("%d", &eq->elt.etat);

    if (eq->elt.etat) {
        eq->elt.debut_utilisation = time(NULL);
        printf("Équipement allumé.\n");
    } else {
        eq->elt.debut_utilisation = 0;
        printf("Équipement éteint.\n");
    }
}
