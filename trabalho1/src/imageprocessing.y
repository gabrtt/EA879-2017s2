%{
#include <stdio.h>
#include "imageprocessing.h"
#include <FreeImage.h>
#include <stdlib.h>
#include <string.h>

void yyerror(char *c);
int yylex(void);

%}
%union {
  char    strval[50];
  int     ival;
  float   valor;
}
%token <strval> STRING STRINGX 
%token <ival> VAR IGUAL EOL ASPA OPE
%token <valor> NUM
%left SOMA

%%

PROGRAMA:
        PROGRAMA EXPRESSAO EOL
        |
        ;

EXPRESSAO:
    | STRING IGUAL STRING {
        printf("Copiando %s para %s\n", $3, $1);
        imagem I = abrir_imagem($3);
        printf("Li imagem %d por %d\n", I.width, I.height);
        salvar_imagem($1, &I);
        liberar_imagem(&I);
                          }
    | STRING IGUAL STRING OPE NUM{  
        imagem I = abrir_imagem($3);
        printf("Li imagem %d por %d\n", I.width, I.height);
        printf("Aplicando %.2f em %s\n", $5, $3);
        brilho(&I, $5, $4);
        salvar_imagem($1, &I);
        liberar_imagem(&I);
                                 }
   | STRINGX{
        imagem I = abrir_imagem($1);
        printf("Achando o valor máximo de %s\n", $1);
        busca(I);
              }
   ;
%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
  FreeImage_Initialise(0);
  yyparse();
  return 0;

}
