#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAYOR   '>'
#define MENOR   '<'
#define ASIGNACION   '='

#define SUMA '+'
#define RESTA '-'
#define MULTIPLICACION '*'
#define DIVISION '/'

#define PUNTOYCOMA   ';'
#define COMA ','
#define PARI    '('
#define PARD ')'
#define CORI '['
#define CORD ']'
#define LLAVESI '{'
#define LLAVESD '}'
#define ID  256 
#define NUM 257
#define MAYORIGUAL  258
#define MENORIGUAL 263 
#define WHILE   259
#define IF  260
#define IGUAL 261
#define DIFERENTE 262

#define COUT 264
#define CIN 265
#define ENDL 266
#define FOR 267
#define ELSE 268
#define ELSEIF 269
#define DO 270
#define CONST 271
#define BREAK 272
#define CASE 273
#define NEW 274
#define SWITCH 275
#define INT 276
#define FLOAT 277
#define STRING 278
#define CHAR 279
int scaner();
void mostrar(int);
int espalres();

FILE *f;
char lexema[80];

int main()
{
    int token;
    f = fopen("file.txt", "rt");  // intenta abrir el archivo code.txt en modo lectura
    if (f == NULL)
    {
        f = stdin;  // si no se puede abrir, se usa la entrada estándar
        printf("No se pudo abrir code.txt, ingrese texto ........ termine con Ctrl z \n");
    }

    while (1)
    {
        token = scaner();
        if (token == EOF) break;
        mostrar(token);
    }

    if (f != stdin)   // si la entrada fue de un archivo
        fclose(f);    // entonces cerrar el archivo.
    return 0;
}//fin del main

int scaner()
{
    int c;
    int i;
    do c = fgetc(f); while (isspace(c));  //ignora blancos

    if (c == EOF) return EOF;

    // Ignorar comentarios en línea
    if (c == '/')
    {
        c = fgetc(f);
        if (c == '/')
        {
            while (c != '\n' && c != EOF) c = fgetc(f);
            return scaner();
        }
        else if (c == '*')
        {
            while (1)
            {
                c = fgetc(f);
                if (c == '*' && (c = fgetc(f)) == '/') break;
                if (c == EOF) return EOF;
            }
            return scaner();
        }
        else
        {
            ungetc(c, f);
            c = '/';
        }
    }

    if (isalpha(c))   //regla del ID
    {
        i = 0;
        do {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isalnum(c) || c == '_');

        lexema[i] = 0;
        ungetc(c, f);   //se devuelve c al flujo de entrada
        i = espalres();   // verifica si es palabra reservada 
                                //  WHILE , IF 
        if (i >= 0)
            return i;
        return ID;    // se trata de un ID
    }

    if (isdigit(c))   //regla del NUM
    {
        i = 0;
        do {
            lexema[i++] = c;
            c = fgetc(f);
        } while (isdigit(c));

        lexema[i] = 0;
        ungetc(c, f);
        return NUM;
    }

    //regla de PUNTOYCOMA y PARI
    if ((c == ';') || (c == '(')|| (c == ')')|| (c == '[')|| (c == ']')|| (c == '{')|| (c == '}')|| (c == ',')) return c;      //regla del ";" y "("
    
    if ((c == '+') || (c == '-')|| (c == '*')|| (c == '/')) return c; 
    
    if (c == '>') //regla de ">" o ">="
    {
        c = fgetc(f);
        if (c == '=')   //return MAYORIGUAL
        {
            lexema[0] = '>';  lexema[1] = '=';  lexema[2] = 0;
            return MAYORIGUAL;
        }
        ungetc(c, f);
        return MAYOR;  //return MAYOR
    }
    if (c == '<') //regla de "<" o "<="
    {
        c = fgetc(f);
        if (c == '=')   //return MENORIGUAL
        {
            lexema[0] = '<';  lexema[1] = '=';  lexema[2] = 0;
            return MENORIGUAL;
        }
        ungetc(c, f);
        return MENOR;  //return MENOR
    }
    
    if (c == '=') //regla de "=" o "=="
    {
        c = fgetc(f);
        if (c == '=')   //return IGUAL
        {
            lexema[0] = '=';  lexema[1] = '=';  lexema[2] = 0;
            return IGUAL;
        }
        ungetc(c, f);
        return ASIGNACION;  //return ASIGNACION
    }
    
    if (c == '!') //regla de "!="
    {
        c = fgetc(f);
        if (c == '=')   //return DIFERENTE
        {
            lexema[0] = '!';  lexema[1] = '=';  lexema[2] = 0;
            return DIFERENTE;
        }
        ungetc(c, f);
        return '!';  //return !
    }

    return c;  // Si el carácter no coincide con ninguna regla, retornarlo directamente
}//fin de scaner

int espalres()
{
    if (strcmp(lexema, "while") == 0) return WHILE;
    if (strcmp(lexema, "if") == 0) return IF;
    if (strcmp(lexema, "cout") == 0) return COUT;
    if (strcmp(lexema, "cin") == 0) return CIN;
    if (strcmp(lexema, "endl") == 0) return ENDL;
    if (strcmp(lexema, "for") == 0) return FOR;
    if (strcmp(lexema, "else") == 0) return ELSE;
    if (strcmp(lexema, "else if") == 0) return ELSEIF;
    if (strcmp(lexema, "do") == 0) return DO;
    if (strcmp(lexema, "const") == 0) return CONST;
    if (strcmp(lexema, "break") == 0) return BREAK;
    if (strcmp(lexema, "case") == 0) return CASE;
    if (strcmp(lexema, "new") == 0) return NEW;
    if (strcmp(lexema, "switch") == 0) return SWITCH;
    if (strcmp(lexema, "int") == 0) return INT;
    if (strcmp(lexema, "float") == 0) return FLOAT;
    if (strcmp(lexema, "string") == 0) return STRING;
    if (strcmp(lexema, "char") == 0) return CHAR;

    return -1;
}

void mostrar(int token)
{
    switch(token)
    {
        case ID: printf("token = ID [%s] \n",lexema); break;
        case NUM: printf("token = NUM [%s] \n",lexema); break;
        
        case MAYORIGUAL: printf("token = MAYORIGUAL [%s]\n",lexema); break;
        case MAYOR: printf("token = MAYOR [%c] \n",token); break;
        case MENORIGUAL: printf("token = MENORIGUAL [%s]\n",lexema); break;
        case MENOR: printf("token = MENOR [%c] \n",token); break;
        case IGUAL: printf("token = IGUAL [%s]\n",lexema); break;
        case ASIGNACION: printf("token = ASIGNACION [%c] \n",token); break;
        case DIFERENTE: printf("token = DIFERENTE [%s]\n",lexema); break;
        
        case SUMA: printf("token = SUMA [%c]\n",token); break;
        case RESTA: printf("token = RESTA [%c]\n",token); break;
        case MULTIPLICACION: printf("token = MULTIPLICACION [%c]\n",token); break;
        case DIVISION: printf("token = DIVISION [%c]\n",token); break;
        
        case WHILE: printf("token = WHILE [%s] \n",lexema); break;
        case IF: printf("token = IF [%s] \n",lexema); break;
        case COUT: printf("token = COUT [%s] \n",lexema); break;
        case CIN: printf("token = CIN [%s] \n",lexema); break;
        case ENDL: printf("token = ENDL [%s] \n",lexema); break;
        case FOR: printf("token = FOR [%s] \n",lexema); break;
        case ELSE: printf("token = ELSE [%s] \n",lexema); break;
        case ELSEIF: printf("token = ELSEIF [%s] \n",lexema); break;
        case DO: printf("token = DO [%s] \n",lexema); break;
        case CONST: printf("token = CONST [%s] \n",lexema); break;
        case BREAK: printf("token = BREAK [%s] \n",lexema); break;
        case CASE: printf("token = CASE [%s] \n",lexema); break;
        case NEW: printf("token = NEW [%s] \n",lexema); break;
        case SWITCH: printf("token = SWITCH [%s] \n",lexema); break;
        case INT: printf("token = INT [%s] \n",lexema); break;
        case FLOAT: printf("token = FLOAT [%s] \n",lexema); break;
        case STRING: printf("token = STRING [%s] \n",lexema); break;
        case CHAR: printf("token = CHAR [%s] \n",lexema); break;
        
        
        case PUNTOYCOMA: printf("token = PUNTOYCOMA [%c]\n",token); break;
        case COMA: printf("token = COMA [%c]\n",token); break;
        case PARI: printf("token = PARI [%c] \n",token); break;
        case PARD: printf("token = PARD [%c] \n",token); break;
        case CORI: printf("token = CORI [%c] \n",token); break;
        case CORD: printf("token = PARD [%c] \n",token); break;
        case LLAVESI: printf("token = LLAVESI [%c] \n",token); break;
        case LLAVESD: printf("token = LLAVESD [%c] \n",token); break;
        
        
        default: printf("token desconocido [%c] \n", token); break;
    }
}