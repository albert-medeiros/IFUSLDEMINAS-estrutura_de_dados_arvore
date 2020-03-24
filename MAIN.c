#include <stdlib.h>
#include <stdio.h>

#include "arvores.h"
#define tam 25

int menu(){ 
 	int opc=-1;
 	A:
	system("cls");
	printf("\n\t --------------------- MENU -----------------------------");
	printf("\n\t -------     1. Insereir Aluno                    -------");
	printf("\n\t -------     2. Retirar Aluno                     -------");
	printf("\n\t -------     3. Pesquisar Aluno                   -------");
	printf("\n\t -------     4. Visualizar Dados                  -------");
	printf("\n\t -------     5. Insereir Aluno - Arquivo          -------");
	printf("\n\t -------     0. SAIR                              -------");
	printf("\n\t --------------------------------------------------------\n");
	printf("Opcao: "); scanf("%d",&opc);
	
	if (opc<0 || opc > 5){
		printf("\n\tSelecione uma opcao valida!\n");
		system("pause");
		goto A;
	}
	else{
		return opc;
	}	
}

void Leitura(TNo **ptr1,TNo **ptr2,TipoAluno alu){ //Inserir um novo aluno manualmente
	
	printf("\n\t -- INSERE --");
	printf("\nMatricula: "); 		scanf("%d",&alu.codigo);
	printf("Nome: "); 	  			scanf("%s",&alu.nome);
	printf("Data de Nascimento: "); scanf("%s",&alu.data);
	insere(ptr1,alu);	insereAVL(ptr2,alu);
}

void Apaga(TNo **ptr1,TNo **ptr2){ //Apagar algum  aluno pelo código de matrícula 
	int cod=-1,sor=-1;
	printf("\n\t -- Alunos Cadastrados --\n");
	in_ordem((*ptr1));
	printf("\n\t -- Alunos Cadastrados --\n\n");
	I:
	printf("\nDigite 1 para usar sucessor ou 2 para antecessor:");
	printf("\nOpcao: ");scanf("%d",&sor);
	
	if(sor<1||sor>2){
		printf("\n\tSelecione uma opcao valida!\n");
		system("pause");
		goto I;
	}
	
	printf("\nEscreva o Codigo do Aluno a ser retirado");
	printf("\nCodigo: ");scanf("%d",&cod);
	retira(ptr1,cod,sor); retiraAVL(ptr2,cod,sor);
}

void Pesquisar(TNo *ptr1,TNo *ptr2){ //Pesquisar algum aluno pelo código de matrícula 
	int chave=-1,ord=-1;
	while(ord != 0){
		B:
		system("cls");
		printf("\n\t -- PESQUISA --");
		printf("\n\t --------------------------------------------------------");
		printf("\n\t -------     1. Pesquisa Chave                    -------");
		printf("\n\t -------     2. Pesquisa irmao	                  -------");
		printf("\n\t -------     3. Pesquisa Pai         	          -------");
		printf("\n\t -------     0. VOLTAR                            -------");
		printf("\n\t --------------------------------------------------------\n");
		printf("Opcao: "); scanf("%d",&ord);
		
		if(ord != 0){
			if (((ord<1) || (ord > 3))){
				printf("\n\tSelecione uma opcao valida!\n");
				system("pause");
				goto B;
			}
			else{
				printf("\n\t -- Alunos Cadastrados --\n");
				in_ordem(ptr1);
				printf("\n\t -- Alunos Cadastrados --\n");
				printf("\n\n");
			}
		}
		
		
		switch(ord){
			case 1:
				printf("\nChave: "); scanf("%d",&chave);
				printf("\nABP:");
				pesquisa(ptr1,chave);
				printf("AVL:");
				pesquisa(ptr2,chave);
				
				system("pause");
			break;
			
			case 2:
				printf("\nChave: "); scanf("%d",&chave);
				printf("\nABP:");
				pIrmao(ptr1,chave);
				printf("AVL:");
				pIrmao(ptr2,chave);
				
				system("pause");
			break;
			
			case 3:
				printf("\nChave: "); scanf("%d",&chave);
				printf("\nABP:");
				pPai(ptr1,chave);
				printf("AVL:");
				pPai(ptr2,chave);
				system("pause");
			break;
		}
				
	}
}



void Visualizar(TNo *ptr1,TNo *ptr2){ // menu para definir a forma como serão apresentados os dados
	int ord =-1;
	while(ord != 0){
		C:
		system("cls");
		printf("\n\t -- VISUALIZA --");
		printf("\n\t --------------------------------------------------------");
		printf("\n\t -------     1. In-Ordem                          -------");
		printf("\n\t -------     2. Pre-Ordem   	                  -------");
		printf("\n\t -------     3. Pos-Ordem        	          -------");
		printf("\n\t -------     0. VOLTAR                            -------");
		printf("\n\t --------------------------------------------------------\n");
		printf("Opcao: "); scanf("%d",&ord);
	
		if (ord<0 || ord > 3){
			printf("\n\tSelecione uma opcao valida!\n");
			system("pause");
			goto C;
		}
		else{
			switch(ord){
				case 1:
					printf("\n\t -- IN-ORDEM  ABP --\n");
					in_ordem(ptr1);
					printf("\n\n");
					
					printf("\n\t -- IN-ORDEM  AVL --\n");
					in_ordem(ptr2);
					printf("\n\n");
		
					system("pause");
				break;
						
				case 2:
					printf("\n\t -- PRE-ORDEM ABP--\n");
					pre_ordem(ptr1);
					printf("\n\n");
					
					printf("\n\t -- PRE-ORDEM AVL--\n");
					pre_ordem(ptr2);
					printf("\n\n");
					
					system("pause");
				break;
							
				case 3:
					printf("\n\t -- POS-ORDEM ABP --\n");
					pos_ordem(ptr1);
					printf("\n\n");
					
					printf("\n\t -- POS-ORDEM AVL --\n");
					pos_ordem(ptr2);
					printf("\n\n");
					
					system("pause");
				break;
			}
			
		}				
	}
	ord=-1;
}

void InsereArq(TNo **ptr1,TNo **ptr2,TipoAluno alu){ //Ler os dados do arquivo
	int i=0;
	FILE *entrada;
	entrada = fopen("dados.dat", "r"); //abertura do arquivo 
				
	if(entrada == NULL){
		printf("\t  -> Erro na abertura do arquivo");
		system("pause");
	}
	
	else{
		for(i=0;i<tam;i++){ //quantidade de dados no arquivo					
			fscanf(entrada, "%d",&alu.codigo); //lê os dados do arquivo
			fscanf(entrada, "%s",&alu.nome);   //lê os dados do arquivo
			fscanf(entrada, "%s",&alu.data); //lê os dados do arquivo
			
			insere(ptr1,alu);	insereAVL(ptr2,alu); //função que insere os dados nas árvores	
		}
		printf("\n\tDados Inseridos\n\n");
	}
	fclose(entrada);	
	system("pause");
}




main(){
	int opc=-1,i=0;
	TNo *ptr1,*ptr2; //poteiros
	TipoAluno alu;
	inicializa(&ptr1); inicializa(&ptr2); //gera um a raiz de toda a árvore
	
	while(opc!=0){
		opc= menu();
		
		switch(opc){
//----------------------------------------------------------------------
			case 1:
				Leitura(&ptr1,&ptr2,alu); //função para inserir
				system("pause");
			break;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
			case 2:
				printf("\n\t -- RETIRA --");
				Apaga(&ptr1,&ptr2); //função para apagar
				system("pause");
			break;
//----------------------------------------------------------------------			
			
//----------------------------------------------------------------------
			case 3:
				Pesquisar(ptr1,ptr2); //pesquisar aluno nas árvores
				system("pause");
			break;
//----------------------------------------------------------------------

//----------------------------------------------------------------------			
			case 4:
				Visualizar(ptr1,ptr2); //Mostrar árvore completa		
			break;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
			case 5:
				InsereArq(&ptr1,&ptr2,alu); //Inserir na árvore pelos arquivos
			break;
//----------------------------------------------------------------------
		}		
	}
}

