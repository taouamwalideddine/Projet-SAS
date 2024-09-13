#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ETUDIANTS 100
#define NOM_LONGUEUR 50
#define DEPT_LONGUEUR 30

typedef struct {
    int id;
    char prenom[NOM_LONGUEUR];
    char nom[NOM_LONGUEUR];
    char dateDeNaissance[11];
    char departement[DEPT_LONGUEUR];
    float noteGenerale;
} Etudiant;

Etudiant etudiants[MAX_ETUDIANTS];
int nombreEtudiants = 0;

void ajouterEtudiant() {
    if (nombreEtudiants >= MAX_ETUDIANTS) {
        printf("Nombre maximum d'etudiants atteint.\n");
        return;
    }

    Etudiant e;
    e.id = nombreEtudiants + 1;
    printf("Entrez le prenom: ");
    scanf("%s", e.prenom);
    getchar();
    printf("Entrez le nom: ");
    scanf("%s", e.nom);
    getchar();
    printf("Entrez la date de naissance (JJ-MM-YYYY): ");
    scanf("%s", e.dateDeNaissance);
    getchar();
    printf("Entrez le departement: ");
    scanf("%s", e.departement);
    getchar();
    printf("Entrez la note generale: ");
    scanf("%f", &e.noteGenerale);
    getchar();

    etudiants[nombreEtudiants++] = e;
    printf("Etudiant ajoute avec succes avec l'ID %d.\n", e.id);

}

void modifierEtudiant(int id) {
    for (int i = 0; i < nombreEtudiants; ++i) {
        if (etudiants[i].id == id) {
            printf("Modifier les details de l'etudiant ID %d\n", id);
            printf("Entrez le prenom: ");
            scanf("%s", etudiants[i].prenom);
            getchar();
            printf("Entrez le nom: ");
            scanf("%s", etudiants[i].nom);
            getchar();
            printf("Entrez la date de naissance (JJ-MM-YYYY): ");
            scanf("%s", etudiants[i].dateDeNaissance);
            getchar();
            printf("Entrez le departement: ");
            scanf("%s", etudiants[i].departement);
            getchar();
            printf("Entrez la note generale: ");
            scanf("%f", &etudiants[i].noteGenerale);
            getchar();
            printf("Details de l'etudiant modifies avec succes.\n");
            return;
        }
    }
    printf("Etudiant non trouve.\n");
}

void supprimerEtudiant(int id) {
    for (int i = 0; i < nombreEtudiants; ++i) {
        if (etudiants[i].id == id) {
            for (int j = i; j < nombreEtudiants - 1; ++j) {
                etudiants[j] = etudiants[j + 1];
            }
            nombreEtudiants--;
            printf("Etudiant supprime avec succes.\n");
            return;
        }
    }
    printf("Etudiant non trouve.\n");
}

void afficherEtudiant(int id) {
    for (int i = 0; i < nombreEtudiants; ++i) {
        if (etudiants[i].id == id) {
            printf("ID de l'etudiant: %d\n", etudiants[i].id);
            printf("Nom: %s %s\n", etudiants[i].prenom, etudiants[i].nom);
            printf("Date de naissance: %s\n", etudiants[i].dateDeNaissance);
            printf("Departement: %s\n", etudiants[i].departement);
            printf("Note generale: %.2f\n", etudiants[i].noteGenerale);
            printf("Statut: %s\n", etudiants[i].noteGenerale >= 10 ? "Admis" : "Non Admis");
            return;
        }
    }
}

float calculerMoyenneNote(const char *departement) {
    float total = 0.0;
    int count = 0;

    for (int i = 0; i < nombreEtudiants; ++i) {
        if (strcmp(etudiants[i].departement, departement) == 0) {
            total += etudiants[i].noteGenerale;
            count++;
        }
    }

    return count > 0 ? total / count : 0.0;
}

void imprimerStatistiques() {


    printf("Le nombre total des etudiants dans l'universite: %d\n", nombreEtudiants);

    int deptCount[100] = {0};
    char departements[100][DEPT_LONGUEUR];
    int deptIndex = 0;

    for (int i = 0; i < nombreEtudiants; ++i) {
        int j;
        for (j = 0; j < deptIndex; ++j) {
            if (strcmp(etudiants[i].departement, departements[j]) == 0) {
                deptCount[j]++;
                break;
            }
        }
        if (j == deptIndex) {
            strcpy(departements[deptIndex], etudiants[i].departement);
            deptCount[deptIndex++] = 1;
        }
    }

    for (int i = 0; i < deptIndex; ++i) {
        printf("Nombre d'etudiants dans le departement %s: %d\n", departements[i], deptCount[i]);
    }


    float seuil;
    

    printf("Entrer les etudiants ayant une note supérieur à: ");
    scanf("%f", &seuil);

    for (int i = 0; i < nombreEtudiants; i++) {
        if (etudiants[i].noteGenerale >= seuil) {
            printf("ID de l'etudiant: %d\n", etudiants[i].id);
            printf("Nom: %s %s\n", etudiants[i].prenom, etudiants[i].nom);
            printf("Date de naissance: %s\n", etudiants[i].dateDeNaissance);
            printf("Departement: %s\n", etudiants[i].departement);
            printf("Note generale: %.2f\n", etudiants[i].noteGenerale);
        }
            
    }

    int notes[3] = {-1}, ind[3] = {-1};
    printf("Afficher les trois meilleurs notes:\n");
    for (int i = 0; i < nombreEtudiants; i++) {
        for (int j = 0; j < 3; j++) {
            if (etudiants[i].noteGenerale > notes[j]) {
                for (int k = 2; k > j; k--) {
                    notes[k] = notes[k - 1];
                    ind[k] = ind[k - 1];
                }
                notes[j] = etudiants[i].noteGenerale;
                ind[j] = i;
                break;
            }
        }
    }

    for (int i = 0; i < 3 && ind[i] != -1; i++) {
        printf("\tEtudiant %d:\n\t\tId: %d | Nom: %s | Prenom: %s | Date de naissance: %s | Departement: %s | Note generale: %.2f\n",
         i + 1, etudiants[ind[i]].id, etudiants[ind[i]].nom, etudiants[ind[i]].prenom, etudiants[ind[i]].dateDeNaissance, etudiants[ind[i]].departement, etudiants[ind[i]].noteGenerale);
    }

    printf("Les etudiants qui ont reussi: ");
    for (int i = 0; i < nombreEtudiants; i++) {
        if (etudiants[i].noteGenerale >= 10){
            printf("ID de l'etudiant: %d\n", etudiants[i].id);
            printf("Nom: %s %s\n", etudiants[i].prenom, etudiants[i].nom);
            printf("Date de naissance: %s\n", etudiants[i].dateDeNaissance);
            printf("Departement: %s\n", etudiants[i].departement);
            printf("Note generale: %.2f\n", etudiants[i].noteGenerale);
        }
    }

    printf("Les etudiants qui n'ont pas reussi: ");
    for (int i = 0; i < nombreEtudiants; i++) {
        if (etudiants[i].noteGenerale < 10)
            afficherEtudiant(i);
    }
    printf("Tous les etudiants ont reussi");
}

void rechercherEtudiantParNom() {
    int choix;
    Etudiant tempEtudiants[MAX_ETUDIANTS];
    int count = 0;

    // Ask for sorting order
    printf("Choisissez l'ordre de tri:\n");
    printf("1. De A a Z\n");
    printf("2. De Z a A\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choix);
    getchar();

    // Copy all students to a temporary array
    for (int i = 0; i < nombreEtudiants; ++i) {
        tempEtudiants[count++] = etudiants[i];
    }

    // Sort students based on chosen order
     if (choix == 1) {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = 0; j < count - i - 1; ++j) {
                if (strcmp(tempEtudiants[j].nom, tempEtudiants[j + 1].nom) > 0){
                    Etudiant temp = tempEtudiants[j];
                    tempEtudiants[j] = tempEtudiants[j + 1];
                    tempEtudiants[j + 1] = temp;
                }
                
            }
        }
   } else if (choix == 2) {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = 0; j < count - i - 1; ++j) {
                if (strcmp(tempEtudiants[j].nom, tempEtudiants[j + 1].nom) < 0 ) {
                    Etudiant temp = tempEtudiants[j];
                    tempEtudiants[j] = tempEtudiants[j + 1];
                    tempEtudiants[j + 1] = temp;
                }
            }
        }
    } else {
        printf("Choix invalide.\n");
        return;
    }

    printf("Liste des etudiants:\n");
    for (int i = 0; i < count; ++i) {
        printf("%d. %s %s\n", i + 1, tempEtudiants[i].prenom, tempEtudiants[i].nom);
    }

    int choixEtudiant;
    printf("Entrez le numero de l'etudiant pour voir les details: ");
    scanf("%d", &choixEtudiant);
    getchar();

    if (choixEtudiant < 1 || choixEtudiant > count) {
        printf("Numero d'etudiant invalide.\n");
        return;
    }

    Etudiant e = tempEtudiants[choixEtudiant - 1];
    printf("Details de l'etudiant choisi:\n");
    printf("ID: %d\n", e.id);
    printf("Nom: %s %s\n", e.prenom, e.nom);
    printf("Date de naissance: %s\n", e.dateDeNaissance);
    printf("Departement: %s\n", e.departement);
    printf("Note generale: %.2f\n", e.noteGenerale);
    printf("Statut: %s\n", e.noteGenerale >= 10 ? "Admis" : "Non Admis");
}

void listerEtudiantsParDepartement(const char *departement) {
    printf("Liste des etudiants dans le departement %s:\n", departement);
    for (int i = 0; i < nombreEtudiants; ++i) {
        if (strcmp(etudiants[i].departement, departement) == 0) {
            printf("ID: %d, Nom: %s %s, Note: %.2f\n", etudiants[i].id, etudiants[i].prenom, etudiants[i].nom, etudiants[i].noteGenerale);
        }
    }
}

void trierEtudiantsParNote() {
    int choix;

    printf("1. Ordre croissant\n2. Ordre decroissant\n");
    printf("Entrer votre choix");
    scanf("%d", &choix);
    getchar();

    if (choix == 1) {
        for (int i = 0; i < nombreEtudiants - 1; ++i) {
        for (int j = 0; j < nombreEtudiants - i - 1; ++j) {
            if (etudiants[j].noteGenerale > etudiants[j + 1].noteGenerale) {
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }
    }

    else if (choix == 2) {
        for (int i = 0; i < nombreEtudiants - 1; ++i) {
        for (int j = 0; j < nombreEtudiants - i - 1; ++j) {
            if (etudiants[j].noteGenerale < etudiants[j + 1].noteGenerale) {
                Etudiant temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }
    }

    else 
        printf("Choix invalide");

    printf("Etudiants classes par note:\n");
    for (int i = 0; i < nombreEtudiants; ++i) {
        printf("ID: %d, Nom: %s %s, Note: %.2f\n", etudiants[i].id, etudiants[i].prenom, etudiants[i].nom, etudiants[i].noteGenerale);
    }
}
int main() {
    int choix, id;
    char nom[NOM_LONGUEUR], departement[DEPT_LONGUEUR];

    while (1) {
        printf("\n______________Menu_____________:   |\n");
        printf("1. Ajouter Etudiant                |\n");
        printf("2. Modifier Etudiant               |\n");
        printf("3. Supprimer Etudiant              |\n");
        printf("4. Afficher Etudiant               |\n");
        printf("5. Calculer Moyenne Note           |\n");
        printf("6. Imprimer Statistiques           |\n");
        printf("7. Rechercher Etudiant par Nom     |\n");
        printf("8. Lister Etudiants par Departement|\n");
        printf("9. Trier Etudiants par Note        |\n");
        printf("10. Quitter                        |\n");
        printf("________________________________   |\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 1:
                ajouterEtudiant();
                break;
            case 2:
                printf("Entrez l'ID de l'etudiant a modifier: ");
                scanf("%d", &id);
                getchar();
                modifierEtudiant(id);
                break;
            case 3:
                printf("Entrez l'ID de l'etudiant a supprimer: ");
                scanf("%d", &id);
                getchar();
                supprimerEtudiant(id);
                break;
            case 4:
                printf("Entrez l'ID de l'etudiant a afficher: ");
                scanf("%d", &id);
                getchar();
                afficherEtudiant(id);
                break;
            case 5:
                printf("Entrez le departement pour calculer la moyenne des notes: ");
                scanf("%s", departement);
                getchar();
                printf("Moyenne des notes dans %s: %.2f\n", departement, calculerMoyenneNote(departement));
                break;
            case 6:
                imprimerStatistiques();
                break;
            case 7:
                rechercherEtudiantParNom();
                break;
            case 8:
                printf("Entrez le departement pour lister les etudiants: ");
                scanf("%s", departement);
                getchar();
                listerEtudiantsParDepartement(departement);
                break;
            case 9:
                trierEtudiantsParNote();
                break;
            case 10:
                printf("Au revoir!\n");
                exit(0);
            default:
                printf("Choix invalide.\n");
                break;
        }
    }

    return 0;
}
