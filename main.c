#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "function.h"

extern tCell *adr_batiment;
extern tCellEq *adr_equipement;

/* Menu de gestion des batiments */
void gestionBatiments() {
    int choix;
    do {
        printf("\n=== GESTION DES BATIMENTS ===\n");
        printf("1. Ajouter un batiment\n");
        printf("2. Modifier un batiment\n");
        printf("3. Supprimer un batiment\n");
        printf("4. Afficher la liste des batiments\n");
        printf("0. Retour au menu principal\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);
        switch (choix) {
            case 1: ajouterBatiment(); break;
            case 2: modifierBatiment(); break;
            case 3: {

                int id;
                printf("Entrez l'ID du bâtiment à supprimer: ");
                scanf("%d", &id);
                Supprimer_Noeud( &adr_batiment, id);
                break;

            }
            
            case 4: afficherBatimentsListe( adr_batiment); break;
            case 0: break;
            default: printf("Choix invalide. Veuillez réessayer.\n"); break;
        }
    } while (choix != 0);
}


/* Menu de gestion des équipements */
void gestionEquipements() {
    int choix;
    do {
        printf("\n=== GESTION DES EQUIPEMENTS ELECTRIQUES ===\n");
        printf("1. Ajouter un équipement\n");
        printf("2. Modifier un équipement\n");
        printf("3. Supprimer un équipement\n");
        printf("4. Afficher tous les équipements\n");
        printf("5. Afficher les équipements par bâtiment\n");
        printf("6. Afficher les équipements par type\n");
        printf("7.changer l'etat d'un equipement\n");
        printf("0. Retour au menu principal\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);
        switch (choix) {
            case 1: ajouterEquipement(); break;
            case 2: modifierEquipement(); break;
            case 3: supprimerEquipement(); break;
            case 4: afficherEquipements(); break;
            case 5: afficherEquipementsParBatiment(); break;
            case 6: afficherEquipementsParType(); break;
            case 7: changerEtatEquipement();break ;
            case 0: break;
            default: printf("Choix invalide. Veuillez réessayer.\n"); break;
        }
    } while (choix != 0);
}



int main() {
    int choix;
    do {
        printf("\n===== MENU PRINCIPAL - CITE INTELLIGENTE =====\n");
        printf("1. Gestion des batiments\n");
        printf("2. Gestion des equipements electriques\n");
        printf("3. Utilisation des equipements electriques\n");
        printf("4. Statistiques sur intervalle de temps\n");
        printf("5. Statistiques des consommations Triee : decroissante ou croissante\n");
        printf("6. Consommations\n");
        printf("0. Quitter\n");
        printf("Entrez votre choix:");
        scanf("%d", &choix);
        switch (choix) {
            case 1: gestionBatiments(); break;
            case 2: gestionEquipements(); break;
            //case 3: utilisationEquipements(); break;
            //case 4: statistiquesIntervalleTemps(); break;
            //case 5: MenuDeTrie(); break;
            //case 6: Consommations(); break;
            case 0: printf("Sortie de l'application...\n"); break;
            default: printf("Choix invalide. Veuillez reessayer.\n"); break;
        }
    } while (choix != 0);
    return 0;
}
