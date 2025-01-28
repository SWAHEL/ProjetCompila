#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef enum {
    ID_TOKEN, PROGRAM_TOKEN,
    CONST_TOKEN, VAR_TOKEN,
    BEGIN_TOKEN, END_TOKEN,
    IF_TOKEN, THEN_TOKEN,
    WHILE_TOKEN, DO_TOKEN,
    READ_TOKEN, WRITE_TOKEN,
    PV_TOKEN, PT_TOKEN,
    PLUS_TOKEN, MOINS_TOKEN,
    MULT_TOKEN, DIV_TOKEN,
    VIR_TOKEN, AFF_TOKEN,
    INF_TOKEN, INFEG_TOKEN,
    SUP_TOKEN, SUPEG_TOKEN,
    DIFF_TOKEN, PO_TOKEN,
    PF_TOKEN, FIN_TOKEN,
    NUM_TOKEN, ERREUR_TOKEN, EOF_TOKEN,EG_TOKEN,
    REPEAT_TOKEN, UNTIL_TOKEN,
    FOR_TOKEN, TO_TOKEN, DOWNTO_TOKEN,
    ELSE_TOKEN,
    CASE_TOKEN, OF_TOKEN,
    PROCEDURE_TOKEN, FUNCTION_TOKEN,
    REAL_TOKEN,ARRAY_TOKEN, RECORD_TOKEN,
    DP_TOKEN,AC_TOKEN,AO_TOKEN,real_TOKEN,
    IN_TOKEN,INTEGER_TOKEN, FLOAT_TOKEN,
    STRING_TOKEN, BOOLEAN_TOKEN, CHAR_TOKEN,
    WRITE_LN_TOKEN,QMARK_TOKEN

} CODES_LEX;

FILE * fichier;

char Car_Cour; //caractère courant

void Lire_Car() {
    Car_Cour = fgetc(fichier);
}

typedef struct { CODES_LEX CODE; char NOM[20]; } TSym_Cour;

TSym_Cour SYM_COUR;

void lire_mot() {
    char mot[20];
    int indice = 0;

    // Lecture du premier caractère (lettre)
    mot[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des caractères suivants (lettres ou chiffres)
    while (isalpha(Car_Cour) || isdigit(Car_Cour)) {
        mot[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caractère de fin de chaîne
    mot[indice] = '\0';

    // Vérifier si le mot est un mot-clé
    if (stricmp(mot, "program") == 0) {
        SYM_COUR.CODE = PROGRAM_TOKEN;
    } else if (stricmp(mot, "const") == 0) {
        SYM_COUR.CODE = CONST_TOKEN;
    } else if (stricmp(mot, "var") == 0) {
        SYM_COUR.CODE = VAR_TOKEN;
    } else if (stricmp(mot, "begin") == 0) {
        SYM_COUR.CODE = BEGIN_TOKEN;
    } else if (stricmp(mot, "end") == 0) {
        SYM_COUR.CODE = END_TOKEN;
    } else if (stricmp(mot, "if") == 0) {
        SYM_COUR.CODE = IF_TOKEN;
    } else if (stricmp(mot, "then") == 0) {
        SYM_COUR.CODE = THEN_TOKEN;
    } else if (stricmp(mot, "while") == 0) {
        SYM_COUR.CODE = WHILE_TOKEN;
    } else if (stricmp(mot, "do") == 0) {
        SYM_COUR.CODE = DO_TOKEN;
    } else if (stricmp(mot, "read") == 0) {
        SYM_COUR.CODE = READ_TOKEN;
    } else if (stricmp(mot, "write") == 0) {
        SYM_COUR.CODE = WRITE_TOKEN;
    } else if (stricmp(mot, "writeln") == 0)
    {
        SYM_COUR.CODE = WRITE_LN_TOKEN;
    }
    else if (stricmp(mot, "repeat") == 0) {
    SYM_COUR.CODE = REPEAT_TOKEN;
} else if (stricmp(mot, "until") == 0) {
    SYM_COUR.CODE = UNTIL_TOKEN;
} else if (stricmp(mot, "for") == 0) {
    SYM_COUR.CODE = FOR_TOKEN;
} else if (stricmp(mot, "to") == 0) {
    SYM_COUR.CODE = TO_TOKEN;
} else if (stricmp(mot, "downto") == 0) {
    SYM_COUR.CODE = DOWNTO_TOKEN;
} else if (stricmp(mot, "else") == 0) {
    SYM_COUR.CODE = ELSE_TOKEN;
} else if (stricmp(mot, "case") == 0) {
    SYM_COUR.CODE = CASE_TOKEN;
} else if (stricmp(mot, "of") == 0) {
    SYM_COUR.CODE = OF_TOKEN;
} else if (stricmp(mot, "procedure") == 0) {
    SYM_COUR.CODE = PROCEDURE_TOKEN;
} else if (stricmp(mot, "function") == 0) {
    SYM_COUR.CODE = FUNCTION_TOKEN;
}else if (stricmp(mot, "array") == 0) {
    SYM_COUR.CODE = ARRAY_TOKEN;
} else if (stricmp(mot, "record") == 0) {
    SYM_COUR.CODE = RECORD_TOKEN;
}else if (stricmp(mot, "real") == 0) {
    SYM_COUR.CODE = REAL_TOKEN;
}else if (stricmp(mot, "integer") == 0) {
    SYM_COUR.CODE = INTEGER_TOKEN;
} else if (stricmp(mot, "float") == 0) {
    SYM_COUR.CODE = FLOAT_TOKEN;
} else if (stricmp(mot, "string") == 0) {
    SYM_COUR.CODE = STRING_TOKEN;
} else if (stricmp(mot, "boolean") == 0) {
    SYM_COUR.CODE = BOOLEAN_TOKEN;
} else if (stricmp(mot, "char") == 0) {
    SYM_COUR.CODE = CHAR_TOKEN;
} else if (stricmp(mot, "in") == 0) {
    SYM_COUR.CODE = IN_TOKEN;
}
 else {
        // Si ce n'est pas un mot-clé, c'est un identifiant
        SYM_COUR.CODE = ID_TOKEN;
    }

    // Stockage du mot dans le jeton
    strcpy(SYM_COUR.NOM, mot);
}

void Retirer_Car() {
    ungetc(Car_Cour, fichier); // remettre le caractère dans le flux
}

/*void lire_nombre() {
    char nombre[20];
    int indice = 0;
    int isReal = 0;  // Indicateur pour déterminer si c'est un réel

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des chiffres suivants
    while (isdigit(Car_Cour)) {
        nombre[indice++] = Car_Cour;
        Lire_Car();
    }

    // Si on rencontre un point, on vérifie qu'il est suivi d'un chiffre
    if (Car_Cour == '.') {
        nombre[indice++] = '.';  // Ajouter le point au nombre
        Lire_Car();
        
        // Vérifier que le caractère suivant est un chiffre
        if (isdigit(Car_Cour)) {
            // Lire les chiffres après le point
            while (isdigit(Car_Cour)) {
                nombre[indice++] = Car_Cour;
                Lire_Car();
            }
            isReal = 1;  // Marquer comme nombre réel
        } else {
            // Si ce n'est pas suivi d'un chiffre, remettre le point dans le flux
            Retirer_Car();  // Remettre le caractère dans le flux
        }
    }

    // Ajouter le caractère de fin de chaîne
    nombre[indice] = '\0';

    // Déterminer si c'est un nombre réel ou entier
    if (isReal) {
        SYM_COUR.CODE = REAL_TOKEN;
    } else {
        SYM_COUR.CODE = NUM_TOKEN;
    }

    // Stocker le nombre dans le jeton
    strcpy(SYM_COUR.NOM, nombre);
}*/
void lire_nombre() {
    char nombre[11];
    int indice = 0;

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des chiffres suivants
    while (isdigit(Car_Cour)) {
        nombre[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caractère de fin de chaîne
    nombre[indice] = '\0';

    // Stockage du nombre dans le jeton
    SYM_COUR.CODE = NUM_TOKEN;
    strcpy(SYM_COUR.NOM, nombre);
}


void Sym_Suiv() {
    while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t') {
        Lire_Car();
    }
    if (isalpha(Car_Cour)) {
        lire_mot();
    } else if (isdigit(Car_Cour)) {
        lire_nombre();
    } else {
        switch (Car_Cour) {
            case ';':
                SYM_COUR.CODE = PV_TOKEN;
                Lire_Car();
                break;

            case '.':
                SYM_COUR.CODE = PT_TOKEN;
                Lire_Car();
                break;

            case '+':
                SYM_COUR.CODE = PLUS_TOKEN;
                Lire_Car();
                break;

            case '-':
                SYM_COUR.CODE = MOINS_TOKEN;
                Lire_Car();
                break;

            case '*':
                SYM_COUR.CODE = MULT_TOKEN;
                Lire_Car();
                break;

            case '/':
                SYM_COUR.CODE = DIV_TOKEN;
                Lire_Car();
                break;

            case ',':
                SYM_COUR.CODE = VIR_TOKEN;
                Lire_Car();
                break;

            case ':':
                Lire_Car();
                if (Car_Cour == '=') {
                    SYM_COUR.CODE = AFF_TOKEN;
                    Lire_Car();
                } else {
                    SYM_COUR.CODE = DP_TOKEN;
                }
                break;

            case '<':
                Lire_Car();
                if (Car_Cour == '=') {
                    SYM_COUR.CODE = INFEG_TOKEN;
                    Lire_Car();
                } else if (Car_Cour == '>') {
                    SYM_COUR.CODE = DIFF_TOKEN;
                    Lire_Car();
                } else {
                    SYM_COUR.CODE = INF_TOKEN;
                }
                break;

            case '>':
                Lire_Car();
                if (Car_Cour == '=') {
                    SYM_COUR.CODE = SUPEG_TOKEN;
                    Lire_Car();
                } else {
                    SYM_COUR.CODE = SUP_TOKEN;
                }
                break;

            case '(':
                SYM_COUR.CODE = PO_TOKEN;
                Lire_Car();
                break;
            case '=':
                SYM_COUR.CODE = EG_TOKEN;
                Lire_Car();
                break;

            case ')':
                SYM_COUR.CODE = PF_TOKEN;
                Lire_Car();
                break;

             case '"':
            SYM_COUR.CODE = QMARK_TOKEN;
            Lire_Car();
            break;    

            case '[':
                SYM_COUR.CODE = AO_TOKEN; // ou créez un nouveau code ARRAY_OPEN_TOKEN
                Lire_Car();
                break;

            case ']':
                SYM_COUR.CODE = AC_TOKEN; // ou créez un nouveau code ARRAY_CLOSE_TOKEN
                Lire_Car();
                break;

            case EOF:
                SYM_COUR.CODE = FIN_TOKEN;
                break;

            default:
                SYM_COUR.CODE = ERREUR_TOKEN;
                Lire_Car(); 
        }
    }
    
}


const char * codeToString(CODES_LEX code) {
    switch (code) {
        case EG_TOKEN: return "EG_TOKEN";
        case ID_TOKEN: return "ID_TOKEN";
        case PROGRAM_TOKEN: return "PROGRAM_TOKEN";
        case CONST_TOKEN: return "CONST_TOKEN";
        case VAR_TOKEN: return "VAR_TOKEN";
        case BEGIN_TOKEN: return "BEGIN_TOKEN";
        case END_TOKEN: return "END_TOKEN";
        case IF_TOKEN: return "IF_TOKEN";
        case THEN_TOKEN: return "THEN_TOKEN";
        case WHILE_TOKEN: return "WHILE_TOKEN";
        case DO_TOKEN: return "DO_TOKEN";
        case READ_TOKEN: return "READ_TOKEN";
        case WRITE_TOKEN: return "WRITE_TOKEN";
        case PV_TOKEN: return "PV_TOKEN";
        case PT_TOKEN: return "PT_TOKEN";
        case PLUS_TOKEN: return "PLUS_TOKEN";
        case MOINS_TOKEN: return "MOINS_TOKEN";
        case MULT_TOKEN: return "MULT_TOKEN";
        case DIV_TOKEN: return "DIV_TOKEN";
        case VIR_TOKEN: return "VIR_TOKEN";
        case AFF_TOKEN: return "AFF_TOKEN";
        case INF_TOKEN: return "INF_TOKEN";
        case INFEG_TOKEN: return "INFEG_TOKEN";
        case SUP_TOKEN: return "SUP_TOKEN";
        case SUPEG_TOKEN: return "SUPEG_TOKEN";
        case DIFF_TOKEN: return "DIFF_TOKEN";
        case PO_TOKEN: return "PO_TOKEN";
        case PF_TOKEN: return "PF_TOKEN";
        case FIN_TOKEN: return "FIN_TOKEN";
        case NUM_TOKEN: return "NUM_TOKEN";
        case ERREUR_TOKEN: return "ERREUR_TOKEN";
        case EOF_TOKEN: return "EOF_TOKEN";
        case REPEAT_TOKEN: return "REPEAT_TOKEN";
        case UNTIL_TOKEN: return "UNTIL_TOKEN";
        case FOR_TOKEN: return "FOR_TOKEN";
        case TO_TOKEN: return "TO_TOKEN";
        case DOWNTO_TOKEN: return "DOWNTO_TOKEN";
        case ELSE_TOKEN: return "ELSE_TOKEN";
        case CASE_TOKEN: return "CASE_TOKEN";
        case OF_TOKEN: return "OF_TOKEN";
        case PROCEDURE_TOKEN: return "PROCEDURE_TOKEN";
        case FUNCTION_TOKEN: return "FUNCTION_TOKEN";
        case ARRAY_TOKEN: return "ARRAY_TOKEN";
        case RECORD_TOKEN: return "RECORD_TOKEN";
        case REAL_TOKEN: return "REAL_TOKEN";
        case DP_TOKEN: return "DP_TOKEN";
        case AC_TOKEN: return "AC_TOKEN";
        case AO_TOKEN: return "AO_TOKEN";
        case real_TOKEN: return "real_TOKEN";
        case IN_TOKEN: return "IN_TOKEN";
        case INTEGER_TOKEN: return "INTEGER_TOKEN";
        case FLOAT_TOKEN: return "FLOAT_TOKEN";
        case STRING_TOKEN: return "STRING_TOKEN";
        case BOOLEAN_TOKEN: return "BOOLEAN_TOKEN";
        case CHAR_TOKEN: return "CHAR_TOKEN";
        case WRITE_LN_TOKEN: return "WRITE_LN_TOKEN";
        case QMARK_TOKEN: return "QMARK_TOKEN";
        default: return "UNKNOWN_TOKEN";
    }
}


int main() {
    fichier = fopen("program.p", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    printf("Resulat:\n");
    Lire_Car();


    do {
        Sym_Suiv();
        //printf("%d\n", SYM_COUR.CODE);
        printf("%s\n", codeToString(SYM_COUR.CODE));
    } while (SYM_COUR.CODE != FIN_TOKEN && SYM_COUR.CODE != EOF_TOKEN);

    fclose(fichier);

    return 0;
}