#include <stdio.h>
#include "function.h"

//* Prototypes des fonctions des sous menu *//

void gestionBatiments();
void gestionEquipements();
void menuGestionTypesEquipement();
void menuUtilisationEquipements();
void menuConsommation();
void menuStatistiques();
void menuTriConsommations();
void menuSauvegardeTxt();

int main() {
    int choix;
    printf("\n");
    printf("**************************************************************\n");
    printf("* Bienvenue dans Smart City : Systeme de Gestion Intelligent *\n");
    printf("**************************************************************\n");
    do {
        printf("\n===== MENU PRINCIPAL - CITE INTELLIGENTE =====\n");
        printf("1. Gestion des batiments\n");
        printf("2. Gestion des equipements electriques\n");
        printf("3. Gestion des types  d'equipement \n");
        printf("4. Utilisation des equipements electriques\n");
        printf("5. Gestion Des Consommations\n");
        printf("6. Les Statistiques \n");
        printf("7. Statistiques des consommations Triee : decroissante ou croissante\n");
        printf("8. Menu de sauvegarde dans fichier .txt\n");
        printf("0. Quitter\n");
        printf("Entrez votre choix:");
        scanf("%d", &choix);
        switch (choix) {
            case 1: gestionBatiments(); break;
            case 2: gestionEquipements(); break;
            case 3: menuGestionTypesEquipement(); break;
            case 4: menuUtilisationEquipements(); break;
            case 5: menuConsommation(); break;
            case 6: menuStatistiques(); break;
            case 7: menuTriConsommations(); break ;
            case 8: menuSauvegardeTxt(); break;
            case 0: printf("Sortie de l'application...\n"); break;
            default: printf("Choix invalide. Veuillez reessayer.\n"); break;
        }
    } while (choix != 0);
    return 0;
}


/* Menu de gestion des batiments */
void gestionBatiments() {
    int choix;
    printf("\n");
    printf("****************************************\n");
    printf("*  SYSTEME DE GESTION DES BATIMENTS     *\n");
    printf("****************************************\n");
    do {
        printf("\n=== MENU DES BATIMENTS ===\n");
        printf("----------------------------\n");
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
                printf("Entrez l'ID du batiment a supprimer: ");
                scanf("%d", &id);
                Supprimer_Noeud(&adr_batiment, id);
                break;

            }

            case 4: afficherBatimentsListe( adr_batiment); break;
            case 0: break;
            default: printf("Choix invalide. Veuillez reessayer.\n"); break;
        }
    } while (choix != 0);
}


/* Menu de gestion des equipements */
void gestionEquipements() {
    int choix;
    printf("\n");
    printf("******************************************\n");
    printf("*  SYSTEME DE GESTION DES  EQUIPEMENTS   *\n");
    printf("*         ELECTRIQUES                    *\n");
    printf("****************************************\n");
    do {
        printf("\n=== MENU DES EQUIPEMENTS ELECTRIQUES ===\n");
        printf("-------------------------------------------\n");
        printf("1. Ajouter un equipement\n");
        printf("2. Modifier un equipement\n");
        printf("3. Supprimer un equipement\n");
        printf("4. Afficher tous les equipements\n");
        printf("5. Afficher les equipements par batiment\n");
        printf("6. Afficher les equipements par type\n");
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
            default: printf("Choix invalide. Veuillez reessayer.\n"); break;
        }
    } while (choix != 0);
}

void menuGestionTypesEquipement() {
    int choix;

    printf("\n");
    printf("****************************************\n");
    printf("*  SYSTEME DE GESTION DES TYPES        *\n");
    printf("*      D'EQUIPEMENT                    *\n");
    printf("****************************************\n");

    do {
        printf("\nMENU PRINCIPAL :\n");
        printf("----------------\n");
        printf("1. Ajouter un type d'equipement\n");
        printf("2. Modifier un type d'equipement\n");
        printf("3. Supprimer un type d'equipement\n");
        printf("4. Afficher tous les types d'equipement\n");
        printf("5. Rechercher un type par nom\n");
        printf("6. Afficher les details d'un type\n");
        printf("7. Quitter le programme\n");
        printf("\nSelectionnez une option (1-7) : ");
        scanf("%d",&choix);
        switch (choix) {
            case 1:
                printf("\n--- AJOUT D'UN TYPE ---\n");
                ajouterTypeEquipement();
                break;
            case 2:
                printf("\n--- MODIFICATION D'UN TYPE ---\n");
                modifierTypeEquipement();
                break;
            case 3:
                printf("\n--- SUPPRESSION D'UN TYPE ---\n");
                supprimerTypeEquipement();
                break;
            case 4:
                printf("\n--- LISTE DES TYPES ---\n");
                afficherTypeEquipements();
                break;
            case 5: {
                char nomRecherche[50];
                printf("\n--- RECHERCHE PAR NOM ---\n");
                printf("Entrez le nom du type : ");
                scanf(" %[^\n]", nomRecherche);

                tCellType* typeTrouve = rechercheTypeParNom(nomRecherche);
                if (typeTrouve) {
                    printf("\n>> RESULTAT :\n");
                    printf("   ID : %d\n", typeTrouve->elt.id);
                    printf("   Nom : %s\n", typeTrouve->elt.nom);
                    printf("   Description : %s\n", typeTrouve->elt.description);
                } else {
                    printf("\n>> Aucun type ne correspond a '%s'\n", nomRecherche);
                }
                break;
            }
            case 6:
                printf("\n--- DETAILS D'UN TYPE ---\n");
                afficherDetailsType();
                break;
            case 7:
                printf("\n>>> Fin du programme. Au revoir !\n");
                break;
            default:
                printf("\n!!! Erreur : veuillez entrer un nombre entre 1 et 7\n");
                break;
        }

    } while (choix != 7);  // la boucle continue tant que l'utilisateur n'a pas choisi 7
}

void menuUtilisationEquipements() {
    int choix;

    printf("\n");
    printf("****************************************\n");
    printf("*  UTILISATION DES EQUIPEMENTS ELECTRIQUES *\n");
    printf("****************************************\n");

    while (1) {
        printf("\nMENU UTILISATION :\n");
        printf("------------------\n");
        printf("1. Allumer un equipement\n");
        printf("2. Eteindre un equipement\n");
        printf("3. Afficher etat de tous les equipements\n");
        printf("4. Afficher equipements par batiment (avec etats)\n");
        printf("5. Retour au menu principal\n");
        printf("\nVotre choix (1-5) : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n");
                allumerEquipement();
                break;

            case 2:
                printf("\n");
                eteindreEquipement();
                break;

            case 3:
                printf("\n");
                afficherEtatEquipements();
                break;

            case 4:
                printf("\n");
                afficherEquipementsBatimentAvecEtats();
                break;

            case 5:
                printf("\nRetour au menu principal...\n");
                return;

            default:
                printf("\nChoix invalide ! Veuillez choisir 1 a 5.\n");
        }
    }
}

void menuStatistiques() {
    int choix;

    printf("\n");
    printf("****************************************\n");
    printf("*           MENU STATISTIQUES          *\n");
    printf("****************************************\n");

    while (1) {
        printf("\nSTATISTIQUES DISPONIBLES :\n");
        printf("--------------------------\n");
        printf("1. Statistiques par equipement\n");
        printf("2. Statistiques par batiment\n");
        printf("3. Statistiques par type d'equipement\n");
        printf("4. Statistiques sur intervalle de temps\n");
        printf("5. Retour au menu principal\n");
        printf("\nVotre choix (1-5) : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n");
                statistiquesParEquipement();
                break;

            case 2:
                printf("\n");
                statistiquesParBatiment();
                break;

            case 3:
                printf("\n");
                statistiquesParType();
                break;

            case 4:
                printf("\n");
                statistiquesIntervalle();
                break;

            case 5:
                printf("\nRetour au menu principal...\n");
                return;

            default:
                printf("\nChoix invalide ! Veuillez choisir 1 a 5.\n");
        }
    }
}

void menuConsommation() {
    int choix;

    printf("\n");
    printf("****************************************\n");
    printf("*      GESTION DES CONSOMMATIONS       *\n");
    printf("****************************************\n");

    while (1) {
        printf("\nMENU CONSOMMATION :\n");
        printf("-------------------\n");
        printf("1. Ajouter une consommation\n");
        printf("2. Afficher toutes les consommations\n");
        printf("3. Afficher consommations par equipement\n");
        printf("4. Retour au menu principal\n");
        printf("\nVotre choix (1-4) : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n");
                ajouterConsommation();
                break;

            case 2:
                printf("\n");
                afficherConsommations();
                break;

            case 3:
                printf("\n");
                afficherConsommationsParEquipement();
                break;

            case 4:
                printf("\nRetour au menu principal...\n");
                return;

            default:
                printf("\nChoix invalide ! Veuillez choisir 1 a 4.\n");
        }
    }
}

void menuTriConsommations() {
    int choix;

    printf("\n");
    printf("****************************************\n");
    printf("*   TRI DES CONSOMMATIONS             *\n");
    printf("****************************************\n");

    while (1) {
        printf("\nOPTIONS DE TRI :\n");
        printf("----------------\n");
        printf("1. Trier par valeur (croissant)\n");
        printf("2. Trier par valeur (decroissant)\n");
        printf("3. Afficher les consommations triees\n");
        printf("4. Retour au menu principal\n");
        printf("\nVotre choix (1-4) : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\nTri en cours...\n");
                adr_consommations = trierConsommationsParValeurAsc(adr_consommations);
                printf("Tri croissant termine.\n");
                break;

            case 2:
                printf("\nTri en cours...\n");
                adr_consommations = trierConsommationsParValeurDesc(adr_consommations);
                printf("Tri decroissant termine.\n");
                break;

            case 3:
                printf("\n");
                afficherConsommations();
                break;

            case 4:
                printf("\nRetour au menu principal...\n");
                return;

            default:
                printf("\nChoix invalide ! Veuillez choisir 1 a 4.\n");
        }
    }
}

void menuSauvegardeTxt() {
    int choix;
    char continuer;

    printf("\n");
    printf("****************************************\n");
    printf("*        MENU SAUVEGARDE TXT           *\n");
    printf("****************************************\n");

    do {
        printf("\nOPTIONS DE SAUVEGARDE :\n");
        printf("-------------------------\n");
        printf("1. Sauvegarder les batiments\n");
        printf("2. Sauvegarder les equipements\n");
        printf("3. Sauvegarder les types d'equipement\n");
        printf("4. Sauvegarder les consommations\n");
        printf("5. Retour au menu principal\n");
        printf("\nVotre choix (1-5) : ");
        scanf("%d", &choix);

        switch(choix) {
            case 1:
                printf("\n");
                sauvegarderBatimentsTxt("batiments.txt");
                break;
            case 2:
                printf("\n");
                sauvegarderEquipementsTxt("equipements.txt");
                break;
            case 3:
                printf("\n");
                sauvegarderTypesTxt("types_equipement.txt");
                break;
            case 4:
                printf("\n");
                sauvegarderConsommationsTxt("consommations.txt");
                break;
            case 5:
                printf("\nRetour au menu principal...\n");
                return;
            default:
                printf("\nChoix invalide ! Veuillez choisir 1 a 5.\n");
        }
    } while (choix != 5);
}