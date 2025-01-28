/*
<PROGRAM> ::= "program" <ID> ";" <BLOCK> "."

<BLOCK> ::= <CONSTS> <VARS> <PROCS_FUNCS> <INSTS>

<CONSTS> ::= "const" <ID> "=" <NUM> ";" { <ID> "=" <NUM> ";" } | ε

<VARS> ::= "var" <VAR_DECL> ";" { <VAR_DECL> ";" } | ε

<VAR_DECL> ::= <ID> ":" <TYPE> 
             | <ID> "[" <NUM> ".." <NUM> "]" "of" <TYPE> 
             | <ID> { "," <ID> } ":" <TYPE>

<TYPE> ::= "integer" 
         | "real" 
         | "char" 
         | "boolean" 
         | "array" "[" <NUM> ".." <NUM> "]" "of" <TYPE>
         | "record" { <FIELD> ":" <TYPE> ";" } "end"

<FIELD> ::= <ID>

<PROCS_FUNCS> ::= <PROC> | <FUNC> | ε

<PROC> ::= "procedure" <ID> "(" <PARAMS> ")" ";" <BLOCK>
<FUNC> ::= "function" <ID> ":" <TYPE> "(" <PARAMS> ")" ";" <BLOCK>

<PARAMS> ::= <ID> ":" <TYPE> { "," <ID> ":" <TYPE> } 
           | "var" <ID> ":" <TYPE> { "," "var" <ID> ":" <TYPE> }

<INSTS> ::= "begin" <INST> { ";" <INST> } "end"

<INST> ::= <AFFEC> 
         | <SI> 
         | <TANTQUE> 
         | <REPEAT> 
         | <ECRIRE> 
         | <LIRE> 
         | <POUR> 
         | <CAS> 
         | ε

<AFFEC> ::= <ID> ":=" <EXPR>

<SI> ::= "if" <COND> "then" <INST> [ "else" <INST> ]

<TANTQUE> ::= "while" <COND> "do" <INST>

<REPEAT> ::= "repeat" <INST> "until" <COND>

<ECRIRE> ::= "write" "(" <EXPR> { "," <EXPR> } ")"
<LIRE> ::= "read" "(" <ID> { "," <ID> } ")"

<POUR> ::= "for" <ID> ":=" <EXPR> "to" <EXPR> "do" <INST>
         | "for" <ID> ":=" <EXPR> "downto" <EXPR> "do" <INST>

<CAS> ::= "case" <EXPR> "of" <CLAUSE> { ";" <CLAUSE> } [ "else" <INST> ] "end"

<CLAUSE> ::= <EXPR> ":" <INST>

<COND> ::= <EXPR> <RELOP> <EXPR>
<RELOP> ::= "=" | "<>" | "<" | ">" | "<=" | ">="

<EXPR> ::= <TERM> { <ADDOP> <TERM> }
<ADDOP> ::= "+" | "-"
<TERM> ::= <FACT> { <MULOP> <FACT> }
<MULOP> ::= "*" | "/"
<FACT> ::= <ID> 
         | <ID> "[" <EXPR> "]" 
         | <NUM> 
         | "(" <EXPR> ")"

<ID> ::= <LETTRE> { <LETTRE> | <CHIFFRE> }
<NUM> ::= <CHIFFRE> { <CHIFFRE> }



*/

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
    WRITE_LN_TOKEN,QMARK_TOKEN,RANGE_TOKEN

} CODES_LEX;

// erreur types
typedef enum {
    ID_ERR,
    PROGRAM_ERR,
    CONST_ERR,
    VAR_ERR,
    BEGIN_ERR,
    END_ERR,
    IF_ERR,
    THEN_ERR,
    WHILE_ERR,
    DO_ERR,
    READ_ERR,
    WRITE_ERR,
    PV_ERR,
    PT_ERR,
    PLUS_ERR,
    MOINS_ERR,
    MULT_ERR,
    DIV_ERR,
    VIR_ERR,
    AFF_ERR,
    INF_ERR,
    INFEG_ERR,
    SUP_ERR,
    SUPEG_ERR,
    DIFF_ERR,
    PO_ERR,
    PF_ERR,
    FIN_ERR,
    NUM_ERR,
    ERREUR_ERR,
    EOF_ERR,
    EG_ERR,
    REPEAT_ERR,
    UNTIL_ERR,
    FOR_ERR,
    TO_ERR,           // ajout du TO_TOKEN
    DOWNTO_ERR,       // ajout du DOWNTO_TOKEN
    ELSE_ERR,
    CASE_ERR,
    OF_ERR,
    PROCEDURE_ERR,    // ajout du PROCEDURE_TOKEN
    FUNCTION_ERR,     // ajout du FUNCTION_TOKEN
    REAL_ERR,         // ajout du REAL_TOKEN
    ARRAY_ERR,        // ajout du ARRAY_TOKEN
    RECORD_ERR,       // ajout du RECORD_TOKEN
    DP_ERR,           // ajout du DP_TOKEN
    AC_ERR,           // ajout de AC_TOKEN
    AO_ERR,           // ajout de AO_TOKEN
    IN_ERR,           // ajout de IN_TOKEN
    INTEGER_ERR,      // ajout de INTEGER_TOKEN
    FLOAT_ERR,        // ajout de FLOAT_TOKEN
    STRING_ERR,       // ajout de STRING_TOKEN
    BOOLEAN_ERR,      // ajout de BOOLEAN_TOKEN
    CHAR_ERR,         // ajout de CHAR_TOKEN
    WRITE_LN_ERR,     // ajout de WRITE_LN_TOKEN
    QMARK_ERR,         // ajout de QMARK_TOKEN
    FOR_DIRECTION_ERR,VAR_BEGIN_ERR,CONST_VAR_BEGIN_ERR,RELOP_ERR
} CODES_ERR;

typedef struct
{
    CODES_LEX CODE;
    char NOM[20];
} TSym_Cour;

TSym_Cour SYM_COUR;

FILE *fichier;

char Car_Cour; // caractère courant

// functions declaration
// Déclarations des fonctions pour la grammaire

// Programme principal
void PROGRAM();   // programme ID ; BLOCK .

// Bloc principal
void BLOCK();     // CONSTS VARS INSTS

// Déclarations pour les constantes
void CONSTS();    // const ID = NUM ; { ID = NUM ; } | ε

// Déclarations pour les variables
void VARS();      // var ID [ NUM ] { , ID [ NUM ] } ; | var ID { , ID } ; | ε

// Instructions
void INSTS();     // begin INST { ; INST } end

// Instructions spécifiques
void INST();      // INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | REPEAT | FOR | CASE | PROC | FUNC | ε

// Affectation
void AFFEC();     // ID := EXPR

// Condition "if"
void SI();        // if COND then INST else INST | if COND then INST

// Boucle "while"
void TANTQUE();   // while COND do INST

// Boucle "repeat"
void REPETER();   // repeat INST until COND

// Instruction d'écriture
void ECRIRE();    // write ( EXPR { , EXPR } )

// Instruction de lecture
void LIRE();      // read ( ID { , ID } )

// Boucle "for"
void POUR();      // for ID := EXPR to EXPR do INST | for ID := EXPR downto EXPR do INST

// Instruction "case"
void CAS();       // case EXPR of CLAUSE { ; CLAUSE } end

// Paramètres de fonction/procédure
void PARAMS();    // ID : TYPE { , ID : TYPE } | var ID : TYPE { , var ID : TYPE }

// Condition logique
void COND();      // EXPR RELOP EXPR

// Expression (implémentation complète de EXPR)
void EXPR();      // TERM { ADDOP TERM }

// Terme dans une expression (implémentation de TERM)
void TERM();      // FACT { MULOP FACT }

// Facteurs dans les expressions (implémentation de FACT)
void FACT();      // ID | NUM | ( EXPR )

// Opérateurs arithmétiques
void MULOP();     // * | /

void ADDOP();     // + | -

// Relation logique pour les expressions
void RELOP();     // = | <> | < | > | <= | >=

// Lecture de caractère pour les tokens
void Lire_Car();  // Lecture d'un caractère du flux d'entrée

// Gestion des erreurs
void Erreur(CODES_ERR code);  // Gestion des erreurs avec un code d'erreur spécifique

// Vérification d'un symbole attendu
void Test_Symbole(CODES_LEX cl, CODES_ERR COD_ERR);  // Tester si le symbole actuel correspond à un type attendu

// Fonction pour la lecture d'un mot
void lire_mot();  // Lire un mot (probablement pour un identifiant ou un mot-clé)

// Fonction pour la lecture d'un nombre
void lire_nombre();  // Lire un nombre (probablement pour NUM)

// Fonction spécifique pour les déclarations de variables
void DECLARATION_VAR();  // (si nécessaire pour gérer la déclaration de variables comme ID : TYPE)

// Fonction pour la gestion de "case"
void CLAUSE();  // EXPR : INST
// Déclaration d'une procédure
void PROC();   // procedure ID ( PARAMS ) ; BLOCK

// Déclaration d'une fonction
void FUNC();   // function ID : TYPE ( PARAMS ) ; BLOCK

void TYPE();



// functions definition

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

void lire_nombre()
{
    char nombre[11];
    int indice = 0;

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des chiffres suivants
    while (isdigit(Car_Cour))
    {
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
                printf("Debug: Detected ';' symbol\n");
                break;

            case '.':
                Lire_Car();
                if (Car_Cour == '.') {
                    SYM_COUR.CODE = RANGE_TOKEN; // Nouveau token pour '..'
                    Lire_Car();
                } else {
                    SYM_COUR.CODE = PT_TOKEN; // Token pour '.'
                }
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
           case '\'':
    Lire_Car(); // Lire le caractère après l'ouverture du guillemet simple
    int i = 0;
    while (Car_Cour != '\'' && Car_Cour != EOF && i < sizeof(SYM_COUR.NOM) - 1) {
        SYM_COUR.NOM[i++] = Car_Cour; // Stocker chaque caractère
        Lire_Car();
    }
    SYM_COUR.NOM[i] = '\0'; // Terminer la chaîne
    if (Car_Cour == '\'') {
        SYM_COUR.CODE = QMARK_TOKEN; // Marquer comme chaîne
        Lire_Car(); // Lire le guillemet fermant
    } else {
        Erreur(QMARK_ERR); // Gérer l'absence du guillemet fermant
    }
    break;


            default:
                SYM_COUR.CODE = ERREUR_TOKEN;
                Lire_Car(); 
        }
        printf("Debug: Detected symbol token: %d\n", SYM_COUR.CODE);
    }
    
}

void Lire_Car()
{
    Car_Cour = fgetc(fichier);
}

void Erreur(CODES_ERR code)
{
    printf("Erreur: %d\n", code);
    printf("Current Token: %d\n", SYM_COUR.CODE);
    printf("Current Lexeme: %s\n", SYM_COUR.NOM);
    exit(EXIT_FAILURE);
}


void Test_Symbole(CODES_LEX cl, CODES_ERR COD_ERR)
{
    if (SYM_COUR.CODE == cl)
    {
        Sym_Suiv();
        printf("Debug: Consumed symbol. New token: %d (%s)\n", SYM_COUR.CODE, SYM_COUR.NOM);
    }
    else
        Erreur(COD_ERR);
}

void PROGRAM()
{
    Test_Symbole(PROGRAM_TOKEN, PROGRAM_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(PV_TOKEN, PV_ERR);
    BLOCK();
    // Vérification et message de débogage pour le point `.`
    if (SYM_COUR.CODE == PT_TOKEN) {
        printf("Debug: Detected program end with '.'\n");
    } else {
        printf("Debug: Expected '.', but found token: %d (%s)\n", SYM_COUR.CODE, SYM_COUR.NOM);
    }
    Test_Symbole(PT_TOKEN, PT_ERR);
    

}

void BLOCK() {
    CONSTS(); // Analyse les constantes
    VARS();   // Analyse les variables

    // Ajout pour analyser les procédures et fonctions
    while (SYM_COUR.CODE == PROCEDURE_TOKEN || SYM_COUR.CODE == FUNCTION_TOKEN) {
        if (SYM_COUR.CODE == PROCEDURE_TOKEN) {
            PROC(); // Analyse une procédure
        } else if (SYM_COUR.CODE == FUNCTION_TOKEN) {
            FUNC(); // Analyse une fonction
        }
    }

    INSTS(); // Analyse les instructions
    printf("Debug: Exiting BLOCK.\n");
}


void CONSTS()
{
    switch (SYM_COUR.CODE)
    {
    case CONST_TOKEN:
        Sym_Suiv();
        Test_Symbole(ID_TOKEN, ID_ERR);
        Test_Symbole(EG_TOKEN, EG_ERR);
        Test_Symbole(NUM_TOKEN, NUM_ERR);
        Test_Symbole(PV_TOKEN, PV_ERR);
        while (SYM_COUR.CODE == ID_TOKEN)
        {
            Sym_Suiv();
            Test_Symbole(EG_TOKEN, EG_ERR);
            Test_Symbole(NUM_TOKEN, NUM_ERR);
            Test_Symbole(PV_TOKEN, PV_ERR);
        };
        break;
    case VAR_TOKEN:
        break;
    case BEGIN_TOKEN:
        break;
    default:
        Erreur(CONST_VAR_BEGIN_ERR);
        break;
    }
}

void VARS() {
    printf("Debug: Starting VARS analysis\n");

    if (SYM_COUR.CODE == VAR_TOKEN) {
        Sym_Suiv(); // Consomme 'var'
        while (SYM_COUR.CODE == ID_TOKEN) {
            printf("Debug: Found variable: %s\n", SYM_COUR.NOM);

            Sym_Suiv(); // Consomme l'identifiant
            if (SYM_COUR.CODE == DP_TOKEN) { // Vérifie ':'
                printf("Debug: Detected ':'\n");
                Sym_Suiv(); // Consomme ':'
                TYPE(); // Analyse le type
                  
                
            } else if (SYM_COUR.CODE == AO_TOKEN) { // Vérifie '['
                printf("Debug: Detected array declaration\n");
                Sym_Suiv(); // Consomme '['
                Test_Symbole(NUM_TOKEN, NUM_ERR);
                Test_Symbole(RANGE_TOKEN, ERREUR_ERR);
                Test_Symbole(NUM_TOKEN, NUM_ERR);
                Test_Symbole(AC_TOKEN, AC_ERR); // ']'
                Test_Symbole(OF_TOKEN, OF_ERR); // 'of'
                TYPE(); // Analyse le type du tableau
            } else {
                Erreur(VAR_ERR); // Erreur si pas ':' ou '['
            }

            // Vérifie les variables multiples séparées par ','
            while (SYM_COUR.CODE == VIR_TOKEN) {
                printf("Debug: Detected additional variable\n");
                Sym_Suiv(); // Consomme ','
                Test_Symbole(ID_TOKEN, ID_ERR);
            }

            // Vérifie ';' en fin de déclaration
            Test_Symbole(PV_TOKEN, PV_ERR);
        }
    }

    printf("Debug: Finished VARS analysis\n");
}





void INSTS()
{
    //begin INST { ; INST } end
    if (SYM_COUR.CODE == BEGIN_TOKEN)
    {
        Sym_Suiv();
        INST();

        while (SYM_COUR.CODE == PV_TOKEN)
        {
            Sym_Suiv();
            INST();
        }

        if (SYM_COUR.CODE == END_TOKEN)
        {
            
            printf("rani wslt lhna");
            printf("Current Token: %d\n", SYM_COUR.CODE);
            printf("Current Lexeme: %s\n", SYM_COUR.NOM);
            Sym_Suiv();
             // Vérifie s'il y a un point après 'end'
            if (SYM_COUR.CODE == PT_TOKEN)
            {
                printf("Debug: Detected '.' after 'end'.\n");
                return; // Sort de la fonction car c'est la fin du programme
            }
            
            
        }
         // Vérifie et ignore un éventuel point-virgule après `end`
        if (SYM_COUR.CODE == PV_TOKEN) {
            printf("Debug: Ignoring semicolon after 'end'.\n");
            Sym_Suiv();
        }
        
        else
        {
            Erreur(FIN_ERR);
        }
    }
    else
    {
        Erreur(BEGIN_ERR);
    }
}

void INST()

{
    //INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
    switch (SYM_COUR.CODE)
    {
    case BEGIN_TOKEN:
        INSTS();
        break;
    case ID_TOKEN:
        AFFEC();
        break;
    case IF_TOKEN:
        SI();
        break;
    case WHILE_TOKEN:
        TANTQUE();
        break;
     case WRITE_TOKEN:
            printf("Debug: Found WRITE_TOKEN\n");
            ECRIRE();
            break;
    case READ_TOKEN:
        LIRE();
        break;
         
    case REPEAT_TOKEN:
        REPETER();
        break;
    case FOR_TOKEN:
        POUR();
        break;
    case CASE_TOKEN:
        CAS();
        break;
    case PROCEDURE_TOKEN:  // PROC
        PROC();
        break;
    case FUNCTION_TOKEN:  // FUNC
        FUNC();
        break;    
    default:
        break;
    }
}

void AFFEC() {
    Test_Symbole(ID_TOKEN, ID_ERR); // Vérifie l'identifiant
    if (SYM_COUR.CODE == AO_TOKEN) { // Vérifie si c'est un tableau
        Test_Symbole(AO_TOKEN, AO_ERR); // Consomme '['
        EXPR(); // Analyse l'expression d'index
        Test_Symbole(AC_TOKEN, AC_ERR); // Consomme ']'
    }
    Test_Symbole(AFF_TOKEN, AFF_ERR); // Vérifie ':='
    EXPR(); // Analyse l'expression de droite
}

void SI() {
    // Vérifie que le token actuel est "if"
    Test_Symbole(IF_TOKEN, IF_ERR);

    // Analyse de la condition
    COND();

    // Vérifie que le token suivant est "then"
    Test_Symbole(THEN_TOKEN, THEN_ERR);

    // Analyse de l'instruction après "then"
    INST();

    // Vérifie si un "else" est présent
    if (SYM_COUR.CODE == ELSE_TOKEN) {
        // Passe au token suivant
        Sym_Suiv();

        // Analyse de l'instruction après "else"
        INST();
    }
}

void TANTQUE()
{
    Test_Symbole(WHILE_TOKEN, WHILE_ERR);
    COND();
    Test_Symbole(DO_TOKEN, DO_ERR);
    INST();
}

void ECRIRE()
{
    Test_Symbole(WRITE_TOKEN, WRITE_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    EXPR();

    while (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        EXPR();
    }

    Test_Symbole(PF_TOKEN, PF_ERR);
    printf("Debug: ECRIRE analysis completed\n");
}

void LIRE()
{
    Test_Symbole(READ_TOKEN, READ_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);

    while (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        Test_Symbole(ID_TOKEN, ID_ERR);
    }

    Test_Symbole(PF_TOKEN, PF_ERR);
}

void POUR() {
    // Vérifie que le token actuel est "for"
    Test_Symbole(FOR_TOKEN, FOR_ERR);

    // Vérifie que le token suivant est un identifiant
    Test_Symbole(ID_TOKEN, ID_ERR);

    // Passe au symbole suivant pour vérifier ":="
    Test_Symbole(AFF_TOKEN, AFF_ERR);

    // Analyse l'expression initiale après ":="
    EXPR();

    // Vérifie si le mot-clé est "to" ou "downto" avec un switch
    switch (SYM_COUR.CODE) {
        case TO_TOKEN:
            Test_Symbole(TO_TOKEN, TO_ERR);
            break;
        case DOWNTO_TOKEN:
            Test_Symbole(DOWNTO_TOKEN, DOWNTO_ERR);
            break;
        default:
            Erreur(FOR_DIRECTION_ERR); // Erreur si ce n'est ni "to" ni "downto"
            return; // Stop l'exécution en cas d'erreur
    }

    // Analyse l'expression finale après "to" ou "downto"
    EXPR();

    // Vérifie que le token suivant est "do"
    Test_Symbole(DO_TOKEN, DO_ERR);

    // Analyse l'instruction à exécuter dans la boucle
    INST();
}
void CAS() {
    Test_Symbole(CASE_TOKEN, CASE_ERR);
    EXPR(); // Expression après "case"
    Test_Symbole(OF_TOKEN, OF_ERR);

    // Parcours des clauses
    while (SYM_COUR.CODE == QMARK_TOKEN || SYM_COUR.CODE == NUM_TOKEN || SYM_COUR.CODE == ID_TOKEN) {
        CLAUSE();
        if (SYM_COUR.CODE == PV_TOKEN) {
            Sym_Suiv(); // Consomme ";"
        }
    }

    // Gestion du mot-clé "else"
    if (SYM_COUR.CODE == ELSE_TOKEN) {
        printf("Debug: Detected 'else' clause\n");
        Sym_Suiv(); // Consomme "else"
        INST();     // Analyse l'instruction associée

         if (SYM_COUR.CODE == PV_TOKEN) {
            Sym_Suiv(); // Consomme ";"
        } else {
            printf("Warning: Missing semicolon after 'else' clause\n");
        }
    }

    Test_Symbole(END_TOKEN, END_ERR); // Fin du bloc case
}



void CLAUSE() {
    // Analyse l'expression de la clause
    if (SYM_COUR.CODE == QMARK_TOKEN || SYM_COUR.CODE == NUM_TOKEN || SYM_COUR.CODE == ID_TOKEN) {
        printf("Debug: Found case value: %s\n", SYM_COUR.NOM);
        Test_Symbole(SYM_COUR.CODE, ERREUR_ERR);  // Consomme le jeton (QMARK, NUM ou ID)
    } else {
        Erreur(ERREUR_ERR);
    }

    // Vérifie que le symbole ":" est présent
    Test_Symbole(DP_TOKEN, DP_ERR);

    // Analyse l'instruction associée à cette clause
    INST();
}


void PROC() {
    Test_Symbole(PROCEDURE_TOKEN, PROCEDURE_ERR); // Vérifie le mot-clé `procedure`
    Test_Symbole(ID_TOKEN, ID_ERR);              // Vérifie l'identifiant de la procédure

    // Gestion des paramètres facultatifs
    if (SYM_COUR.CODE == PO_TOKEN) {
        Test_Symbole(PO_TOKEN, PO_ERR); // Consomme '('
        PARAMS();                       // Analyse les paramètres
        Test_Symbole(PF_TOKEN, PF_ERR); // Consomme ')'
    }

    Test_Symbole(PV_TOKEN, PV_ERR); // Vérifie le point-virgule

    BLOCK(); // Analyse le bloc de la procédure
}

void FUNC() {
    Test_Symbole(FUNCTION_TOKEN, FUNCTION_ERR); // Vérifie le mot-clé `function`
    Test_Symbole(ID_TOKEN, ID_ERR);            // Vérifie l'identifiant de la fonction

    Test_Symbole(DP_TOKEN, DP_ERR);            // Vérifie `:`
    TYPE();                                    // Analyse le type de retour

    // Gestion des paramètres facultatifs
    if (SYM_COUR.CODE == PO_TOKEN) {
        Test_Symbole(PO_TOKEN, PO_ERR); // Consomme '('
        PARAMS();                       // Analyse les paramètres
        Test_Symbole(PF_TOKEN, PF_ERR); // Consomme ')'
    }

    Test_Symbole(PV_TOKEN, PV_ERR); // Vérifie le point-virgule

    BLOCK(); // Analyse le bloc de la fonction
}

void PARAMS() {
    // Vérifie si le premier paramètre est une variable par référence
    if (SYM_COUR.CODE == VAR_TOKEN) {
        // Passe au token suivant
        Test_Symbole(VAR_TOKEN, VAR_ERR);

        // Vérifie que le token suivant est un identifiant
        Test_Symbole(ID_TOKEN, ID_ERR);

        // Vérifie que le symbole ":" est présent
        Test_Symbole(DP_TOKEN, DP_ERR);

        // Vérifie le type du paramètre en appelant TYPE()
        TYPE();

        // Gestion des paramètres supplémentaires (séparés par ",")
        while (SYM_COUR.CODE == VIR_TOKEN) {
            Test_Symbole(VIR_TOKEN, VIR_ERR);
            Test_Symbole(ID_TOKEN, ID_ERR);
            Test_Symbole(DP_TOKEN, DP_ERR);
            TYPE();
        }
    }
    // Sinon, les paramètres sont des variables normales
    else if (SYM_COUR.CODE == ID_TOKEN) {
        // Vérifie que le token suivant est un identifiant
        Test_Symbole(ID_TOKEN, ID_ERR);

        // Vérifie que le symbole ":" est présent
        Test_Symbole(DP_TOKEN, DP_ERR);

        // Vérifie le type du paramètre en appelant TYPE()
        TYPE();

        // Gestion des paramètres supplémentaires (séparés par ",")
        while (SYM_COUR.CODE == VIR_TOKEN) {
            Test_Symbole(VIR_TOKEN, VIR_ERR);
            Test_Symbole(ID_TOKEN, ID_ERR);
            Test_Symbole(DP_TOKEN, DP_ERR);
            TYPE();
        }
    }
    // Sinon, aucune déclaration de paramètre (ε)
    else {
        // Aucun paramètre déclaré
        return;
    }
}


void COND() {
    printf("Debug: Starting condition analysis\n");
    EXPR();
    printf("Debug: First expression analyzed\n");
    RELOP();
    printf("Debug: Relational operator analyzed\n");
    EXPR();
    printf("Debug: Second expression analyzed\n");
}

void EXPR()
{
    //TERM { ADDOP TERM }
    TERM();

    while (SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN)
    {
        ADDOP();
        TERM();
    }
}

void TERM()
{
    FACT();

    while (SYM_COUR.CODE == MULT_TOKEN || SYM_COUR.CODE == DIV_TOKEN)
    {
        MULOP();
        FACT();
    }
}

void FACT() {
    switch (SYM_COUR.CODE) {
    case ID_TOKEN:
        Test_Symbole(ID_TOKEN, ID_ERR);
        if (SYM_COUR.CODE == AO_TOKEN) { // Vérifie si c'est un tableau
            Test_Symbole(AO_TOKEN, AO_ERR); // '['
            EXPR(); // Expression pour l'index
            Test_Symbole(AC_TOKEN, AC_ERR); // ']'
        }
        break;

    case NUM_TOKEN:
        Test_Symbole(NUM_TOKEN, NUM_ERR);
        break;

    case PO_TOKEN:
        Test_Symbole(PO_TOKEN, PO_ERR);
        EXPR();
        Test_Symbole(PF_TOKEN, PF_ERR);
        break;
    case QMARK_TOKEN:
    printf("Debug: Found character constant: %s\n", SYM_COUR.NOM);
    Test_Symbole(QMARK_TOKEN, QMARK_ERR); // Vérifie et consomme le jeton
    break;

    default:
        Erreur(ERREUR_ERR);
        break;
    }
}


void RELOP()
{
    switch (SYM_COUR.CODE)
    {
    case EG_TOKEN:        // "="
        Test_Symbole(EG_TOKEN, EG_ERR);
        break;
    case DIFF_TOKEN:      // "<>"
        Test_Symbole(DIFF_TOKEN, DIFF_ERR);
        break;
    case INF_TOKEN:       // "<"
        Test_Symbole(INF_TOKEN, INF_ERR);
        break;
    case INFEG_TOKEN:     // "<="
        Test_Symbole(INFEG_TOKEN, INFEG_ERR);
        break;
    case SUP_TOKEN:       // ">"
        Test_Symbole(SUP_TOKEN, SUP_ERR);
        break;
    case SUPEG_TOKEN:     // ">="
        Test_Symbole(SUPEG_TOKEN, SUPEG_ERR);
        break;
    default:
        // Si aucun des cas ne correspond, signaler une erreur
        Erreur(RELOP_ERR);
        break;
    }
}


void ADDOP()
{
    switch (SYM_COUR.CODE)
    {
    case PLUS_TOKEN:
        Test_Symbole(PLUS_TOKEN, PLUS_ERR);
        break;
    case MOINS_TOKEN:
        Test_Symbole(MOINS_TOKEN, MOINS_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

void MULOP()
{
    switch (SYM_COUR.CODE)
    {
    case MULT_TOKEN:
        Test_Symbole(MULT_TOKEN, MULT_ERR);
        break;
    case DIV_TOKEN:
        Test_Symbole(DIV_TOKEN, DIV_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}



/*
REPEAT_TOKEN,UNTIL_TOKEN,FOR_TOKEN,ELSE_TOKEN,CASE_TOKEN,OF_TOKEN*/

void REPETER() {
    Test_Symbole(REPEAT_TOKEN, REPEAT_ERR); // Vérifie "repeat"

    // Analyse une ou plusieurs instructions entre repeat et until
    INST();
    while (SYM_COUR.CODE == PV_TOKEN) { // Gère les instructions multiples séparées par ;
        Sym_Suiv();
        INST();
    }

    Test_Symbole(UNTIL_TOKEN, UNTIL_ERR); // Vérifie "until"
    COND(); // Analyse la condition après "until"
}


void TYPE() {
    switch (SYM_COUR.CODE) {
        case INTEGER_TOKEN:
            // Vérifie le type `integer`
            Test_Symbole(INTEGER_TOKEN, INTEGER_ERR);
            break;
         case CHAR_TOKEN:  // Ajoutez cette ligne
            Test_Symbole(CHAR_TOKEN, CHAR_ERR);
            break;

        case REAL_TOKEN:
            // Vérifie le type `real`
            printf("Debug: Detected type 'real'\n");
            Test_Symbole(REAL_TOKEN, REAL_ERR);
            printf("out: Detected type 'real'\n");
            break;

        case ARRAY_TOKEN:
            Test_Symbole(ARRAY_TOKEN, ARRAY_ERR);
            Test_Symbole(AO_TOKEN, AO_ERR); // '['
            Test_Symbole(NUM_TOKEN, NUM_ERR);
            Test_Symbole(RANGE_TOKEN, ERREUR_ERR); // '..'
            Test_Symbole(NUM_TOKEN, NUM_ERR);
            Test_Symbole(AC_TOKEN, AC_ERR); // ']'
            Test_Symbole(OF_TOKEN, OF_ERR);
            TYPE(); // Type des éléments du tableau
            break;

        case RECORD_TOKEN:
            // Vérifie le mot-clé `record`
            Test_Symbole(RECORD_TOKEN, RECORD_ERR);

            // Analyse des champs du record
            do {
                // Analyse le champ
                FIELD();

                // Vérifie le symbole `:`
                Test_Symbole(DP_TOKEN, DP_ERR);

                // Analyse le type du champ
                TYPE();

                // Vérifie et gère les champs supplémentaires séparés par `,`
            } while (SYM_COUR.CODE == VIR_TOKEN );

            // Vérifie le mot-clé `end`
            Test_Symbole(END_TOKEN, END_ERR);
            break;

        default:
            // Si aucun des cas n'est reconnu, une erreur de type est générée
            Erreur(ERREUR_ERR);
            break;
    }
}

void FIELD() {
    // Vérifie que le champ est un identifiant valide
    Test_Symbole(ID_TOKEN, ID_ERR);
}




int main()
{
    fichier = fopen("program.p", "r");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // PREMIER_SYM();
    Lire_Car();
    Sym_Suiv();

    PROGRAM();

    printf("Program execution completed.\n");

    if (SYM_COUR.CODE == FIN_TOKEN)
    {
        printf("BRAVO: le programme est correcte!!!\n");
    }
    else
    {
        printf("PAS BRAVO: fin de programme erronée!!!!\n");
        printf("Current Token: %d\n", SYM_COUR.CODE);
        printf("Current Lexeme: %s\n", SYM_COUR.NOM);
        
    }

    fclose(fichier);

    return 0;
}