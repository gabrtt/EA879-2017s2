
#include <stdlib.h>
#include <stdio.h>

#include "imageprocessing.h"

#include <FreeImage.h>

/*
imagem abrir_imagem(char *nome_do_arquivo);
void salvar_imagem(char *nome_do_arquivo);
void liberar_imagem(imagem *i);
 */

imagem abrir_imagem(char *nome_do_arquivo) {
  FIBITMAP *bitmapIn;
  int x, y;
  RGBQUAD color;
  imagem I;

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      idx = i + (j*x);

      I.r[idx] = color.rgbRed;
      I.g[idx] = color.rgbGreen;
      I.b[idx] = color.rgbBlue;
    }
   }
  return I;

}

void liberar_imagem(imagem *I) {
  free(I->r);
  free(I->g);
  free(I->b);
}

void salvar_imagem(char *nome_do_arquivo, imagem *I) {
  FIBITMAP *bitmapOut;
  RGBQUAD color;

  printf("Salvando imagem %d por %d...\n", I->width, I->height);
  bitmapOut = FreeImage_Allocate(I->width, I->height, 24, 0, 0, 0);

   for (int i=0; i<I->width; i++) {
     for (int j=0; j<I->height; j++) {
      int idx;

      idx = i + (j*I->width);
      color.rgbRed = I->r[idx];
      color.rgbGreen = I->g[idx];
      color.rgbBlue = I->b[idx];

      FreeImage_SetPixelColor(bitmapOut, i, j, &color);
    }
  }

  FreeImage_Save(FIF_JPEG, bitmapOut, nome_do_arquivo, JPEG_DEFAULT);
}


/*Função que aplica o valor do brilho na imagem*/
void brilho (imagem *I, float intensidade, char ope){
   float x, y;
  
   /*Aqui, pegamos as matrizes das cores através de alocação dinâmica e definimos o # de colunas e # de linhas da imagem */
   I->width = x;
   I->height = y;
printf("wid %f height %f", I->width, I->height);

	printf("passei aqui\n");
	printf("ope %c brilho %f \n", ope, intensidade);

   if(ope == 'd'){

for (int i=0; i<x; i++) 
	{
     
     	for (int j=0; j<y; j++) 
     	{
            
	      	int idx;

	      	idx = i + (j*I->width);

	      	/* para a parte vermelha do pixel */
		if((I->r[idx] + intensidade) <= 255)
	      	I->r[idx]	= (I->r[idx] + intensidade);
		else
		I->r[idx] = 255;

	      	/* para a parte verde do pixel */
		if((I->g[idx] + intensidade) <= 255)
	      	I->g[idx] 	= (I->g[idx] + intensidade);
		else
		I->g[idx] = 255;

	      	/* para a parte azul do pixel */
		if((I->b[idx] + intensidade) <= 255)
	      	I->b[idx] 	= (I->b[idx] + intensidade);
		else		
		I->b[idx] = 255;


            }
        }
       
    }

   if(ope == '/'){
printf("divisao\n");
	   for (int i=0; i<I->width; i++) 
	{
     	for (int j=0; j<I->height; j++) 
     	{
	      	int idx;

	      	idx = i + (j*I->width);

	      	/* para a parte vermelha do pixel */
		if((I->r[idx] + intensidade) <= 255)
	      	I->r[idx]	= (I->r[idx] + intensidade);
		else
		I->r[idx] = 255;

	      	/* para a parte verde do pixel */
		if((I->g[idx] + intensidade) <= 255)
	      	I->g[idx] 	= (I->g[idx] + intensidade);
		else
		I->g[idx] = 255;

	      	/* para a parte azul do pixel */
		if((I->b[idx] + intensidade) <= 255)
	      	I->b[idx] 	= (I->b[idx] + intensidade);
		else		
		I->b[idx] = 255;
	   }

   }
}
}

void busca (imagem I){
   float x, y;
   int i, j, max=0, soma;

   I.width = x;
   I.height = y;

   for( j = 0; j < x*y; j++){
	   soma = I.r[j] + I.g[j] + I.b[j];
		if (soma > max){
		   max = soma;
		}
   }
return max;
}










