#include <stdlib.h>
#include <stdio.h>
#define MAX 1000

char *alocaVetor(long *tam){
	char *v = malloc((*tam) * sizeof(*v));
	return v;
}

char *realocaVetor (char *vet, long *tam){
	char *v = malloc(2* (*tam) * sizeof(*v));
	int i = 0;
	for (i = 0; i< *tam; i++){
		v[i] = vet[i];
	}
	free(vet);
	*tam = *tam * 2;
	return v;	
}


char *recebeTexto(long *cap){
	char nome[80] = "";
	char *texto;
	int tam = 0; 
	texto = alocaVetor(cap);
	printf("Digite o nome do arquivo que será criptografado: \n");
	if (scanf("%s", nome) == 0){printf("Erro na leitura do nome do arquivo.");}
	/*printf("\n");*/
	FILE *arq;
	arq = fopen(nome, "r");

	if(arq == NULL){
		printf("Não encontrei o arquivo %s\n",nome);		
		free(texto);
		fclose(arq);
		exit(1);
	}
	else{
		while (!feof(arq)){
			if(tam == *cap){
				texto = realocaVetor(texto, cap);
			}
			fscanf(arq, "%c", &texto[tam]);
			/*printf("%c", texto[tam]);*/
			tam ++;
		}
		/*
		printf("\n");
		printf("O texto %s foi copiado com sucesso!\n", nome);
		*/
		fclose(arq);
		return texto;
	}
}

int identifica(char caractere){
	if ((caractere >= 'a') && (caractere <= 'z')){
		return 2;
	}
	else{
		if ((caractere >= 'A') && (caractere <= 'Z')){
			return 1;
		}
		else{
			return 0;
		}
	}
	return 0;
}

char converte(int tipo, int codigo, char caractere){
	switch (tipo){
		case 0: 
		        if (caractere == ','){
				operacao(2,codigo,'v');
				operacao(2,codigo,'r');
			}
			if (caractere == '.') {    
                                operacao(2,codigo,'p');
                                operacao(2,codigo,'t');
			}
			if (caractere == ':'){
                                operacao(2,codigo,'d');
                                operacao(2,codigo,'p');
			}
			if (caractere == '!'){
                                operacao(2,codigo,'e');
                                operacao(2,codigo,'x');
			}
			if (caractere == '?'){
                                operacao(2,codigo,'i');
                                operacao(2,codigo,'n');
			}
			if (caractere == '\n'){
                                operacao(2,codigo,'n');
                                operacao(2,codigo,'l');		
			}
		break;
		case 1:
	      		operacao(tipo,codigo,caractere);
               	break;
		case 2:
		        operacao(tipo, codigo, caractere);
		break;
	}
	return 0;
}

void operacao(int tipo, int codigo, char caractere){
	char mod = 'e', novaL= 'e';
	switch(tipo){
		case 1:
                        mod = (('Z' - caractere) - codigo) % 26;
                        if (mod < 0){
                                mod = inversoModular(mod);
                        }
                        novaL = 'Z' - mod;
                        printf("%c", novaL);
		break;
		case 2:
                        mod = ('z' - caractere - codigo) % 26;
                        if(mod < 0){
                                mod = inversoModular(mod);
                        }
                        novaL = 'z' - mod;
                        printf("%c", novaL);
		break;
	}
}

int inversoModular(int i){
	int j = 0;
	for(j = 0; j < 26;j++){
		if (j-26 == i){return j;}
	}
	printf("Algo muito esquisito aconteceu.\n");
	return 0;
}

int main(){
	char *texto;
	long cap = MAX;
	int i = 0, d1 = 0, d2 = 0;
	texto = recebeTexto(&cap);
	printf("Insira d1 e d2 inteiros para indicar o deslocamento dos caracteres, respectivamente, minúsculos e maiúsculos:\n");
	if (scanf("%i %i", &d1,&d2) == 0){
		printf("Erro na leitura de d1 e d2.");
		return 0;
	}
	d1 = d1 % 26;
	d2 = d2 % 26;
	/*
	printf("Processo de criptografia nos valores d1 = %i e d2 = %i inicializado!\n",d1, d2);
	*/
	printf("\n");
	
	for(i = 0; i != cap; i++){
		if(texto[i] == '\0'){
		break;
		}
		switch (identifica(texto[i])){
			case 0: 
				converte(0, d2 , texto[i]);
			break;
			case 1: 
				converte(1, d1, texto[i]);	
			break;
			case 2: 
				converte(2, d2, texto[i]);
			break;
		}	
	}
	free(texto);
	printf("\n\n");	
	/*
	printf("Processo de criptografia nos valores d1 = %i e d2 = %i finalizado!\n",d1, d2);
	*/
	return 0;
}

