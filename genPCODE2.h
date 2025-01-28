
// Définition des tokens du langage
typedef enum {
    PROGRAM_TOKEN,     // Mot-clé 'program'
    VAR_TOKEN,         // Mot-clé 'var'
    CONST_TOKEN,       // Mot-clé 'const'
    TYPE_TOKEN,        // Mot-clé 'type'
    IF_TOKEN,          // Instruction 'if'
    THEN_TOKEN,        // Mot-clé 'then'
    ELSE_TOKEN,        // Mot-clé 'else'
    WHILE_TOKEN,       // Instruction 'while'
    DO_TOKEN,          // Mot-clé 'do'
    REPEAT_TOKEN,      // Instruction 'repeat'
    UNTIL_TOKEN,       // Mot-clé 'until'
    FOR_TOKEN,         // Instruction 'for'
    TO_TOKEN,          // Mot-clé 'to'
    DOWNTO_TOKEN,      // Mot-clé 'downto'
    CASE_TOKEN,        // Instruction 'case'
    OF_TOKEN,          // Mot-clé 'of'
    BEGIN_TOKEN,       // Début d'un bloc (mot-clé 'begin')
    END_TOKEN,         // Fin d'un bloc (mot-clé 'end')
    WRITE_TOKEN,       // Instruction 'write' pour afficher
    READ_TOKEN,        // Instruction 'read' pour lire
    PROCEDURE_TOKEN,   // Mot-clé 'procedure'
    FUNCTION_TOKEN,    // Mot-clé 'function'
    AFFECT_TOKEN,      // Symbole d'affectation ':='
    PV_TOKEN,          // Point-virgule ';'
    PT_TOKEN,          // Point '.'
    PLUS_TOKEN,        // Signe plus '+'
    MOINS_TOKEN,       // Signe moins '-'
    MULTI_TOKEN,       // Signe multiplication '*'
    DIV_TOKEN,         // Signe division '/'
    EGAL_TOKEN,        // Signe égal '='
    DIFF_TOKEN,        // Signe différence '<>'
    SUP_TOKEN,         // Signe supérieur '>'
    INF_TOKEN,         // Signe inférieur '<'
    SUPEG_TOKEN,       // Signe supérieur ou égal '>='
    INFEG_TOKEN,       // Signe inférieur ou égal '<='
    COLON_TOKEN,       // Deux-points ':'
    PRG_TOKEN,         // Parenthèse ouvrante '('
    PRD_TOKEN,         // Parenthèse fermante ')'
    VIR_TOKEN,         // Virgule ','
    NUM_TOKEN,         // Nombre entier
    REAL_TOKEN,        // Nombre réel
    ID_TOKEN,          // Identifiant (nom de variable)
    INT_TOKEN,         // Mot-clé 'int'
    BOOL_TOKEN,        // Mot-clé 'bool'
    STRING_TOKEN,      // Mot-clé 'string'
    DIEZE_TOKEN,       // Symbole '#' souvent utilisé pour marquer la fin
    ERREUR_TOKEN       // Token indiquant une erreur
} CODE_LEX;


// Déclaration des types de données du langage
typedef enum {
    TYPE_INT,    // Entier
    TYPE_REAL,   // Réel (nombre à virgule)
    TYPE_BOOL,   // Booléen (vrai ou faux)
    TYPE_STRING, // Chaîne de caractères
    TYPE_UNDEF   // Non défini
} DataType;

// Union pour stocker soit un entier, soit un réel dans une seule variable
typedef union {
    int   i;     // Stocke un entier
    float f;     // Stocke un nombre réel
} DataValue;   // Permet de garder soit un entier soit un réel

// Définition des instructions du P-code
typedef enum {
    ADD,               // Addition
    SUB,               // Soustraction
    MUL,               // Multiplication
    DIVI,              // Division entière
    EQL,               // Égalité (==)
    NEQ,               // Différence (!=)
    GTR,               // Plus grand que (>)
    LSS,               // Plus petit que (<)
    GEQ,               // Supérieur ou égal (>=)
    LEQ,               // Inférieur ou égal (<=)
    PRN,               // Instruction d'impression (print)
    INN,               // Instruction de saisie (input)
    LDI,               // Charger une valeur immédiate (literal)
    LDA,               // Charger une adresse
    LDV,               // Charger la valeur depuis une adresse
    STO,               // Stocker une valeur dans une adresse
    BRN,               // Branchement inconditionnel (jump)
    BZE,               // Branchement conditionnel si zéro (if zero, jump)
    HLT,               // Arrêter le programme (halt)
    CALL,              // Appel d'une procédure ou fonction (call)
    RET,               // Retour d'une procédure ou fonction (return)
    LDL,               // Charger une variable locale
    STL,               // Stocker dans une variable locale
    LDF,               // Charger une fonction
    STO_IND,           // Stocker via une adresse indirecte
    PUSH_PARAMS_COUNT  // Pousser le nombre de paramètres sur la pile
} Mnemoniques; 

void erreur(const char* msg);
static void parseParamList(int indexProcFunc);
static void parseArguments(int indexProcFunc);
void Program();
void Bloc();
void Insts();
void Inst();
void Cond();
void Exp();
void Term();
void Fact();
void RepeatInst();
void ForInst();
void CaseInst();
void ProcFuncPart();
void ProcDecl();
void FuncDecl();
void CallOrAssign();
int IDexists(const char *nom);
int isVar(const char *nom);
int isConst(const char *nom);
int getAdresse(const char *nom);
int getConstValue(const char *nom);
float getConstFValue(const char *nom);
int isProcedure(const char *nom);
int isFunction(const char *nom);
int getProcFuncIndex(const char *nom);
void TypeDecl();
void ConstDecl();
void VarDecl();
DataType parseBaseType();
static void initLocalParams();
static int addLocalParam(const char *nom, DataType t);
static int findLocalParamIndex(const char *nom);
void generer1(Mnemoniques M);
void generer2(Mnemoniques M, int arg);
void LireCar();
static void toLowerString(char *s);
static void lireNombre();
static void lireMot();
void SymSuiv();
void testSym(CODE_LEX t);
void afficherPCode();
void sauvegarderPCode(const char* filename);