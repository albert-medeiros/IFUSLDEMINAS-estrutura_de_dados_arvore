#include <stdlib.h>
#include <stdio.h>

#define ALOCA (TNo*)malloc(sizeof(TNo))
//Utiliza-se um ponteiro duplo para que as modificações na árvore sejam mantidas após a chamada da função 

//----------------------------------------------------------------------- STRUCT / INICIALIZA ------------------------------------------------------------------------------------
typedef struct aluno{ // Dados dos alunos
	char nome[30],data[11];
	int codigo;
	
}TipoAluno;

typedef struct no{
	struct no *esq,*dir; // aponta para o proximo no
	TipoAluno aluno; //chave real
} TNo;

void inicializa(TNo **ptr){ //CRIA A RAIZ
	*ptr = NULL;
}
//----------------------------------------------------------------------- STRUCT / INICIALIZA ------------------------------------------------------------------------------------

//----------------------------------------------------------------------- Ambas ávores ------------------------------------------------------------------------------------

void antecessor(TNo *q,TNo **r){
	if((*r)->dir != NULL){ //recursivamente para ir no último na direita DA ESQUERDA
		antecessor(q,&(*r)->dir);
	}
	else{ //faz a troca e apaga o nó 
		q->aluno = (*r)->aluno; //copia do antecessor pro lugar da chave apagada
		q = (*r); //posição da chave
		
		(*r) = (*r)->esq; //passa a chave esquerda para o nó	
		
		free(q); //apaga o nó 
	}
}

void sucessor(TNo *q,TNo **r){
	if((*r)->esq != NULL){  //recursivamente para ir no último da esquerda
		sucessor(q,&(*r)->esq);
	}
	else{ //faz a troca e apaga o nó 
		q->aluno = (*r)->aluno;	//aluno recebe os dados dos da struct r
		q = (*r); //posição da chave
		(*r) = (*r)->dir; //passa a chave dir para o nó
		free(q);
	}
}

void pesquisa(TNo *ptr,int chave){
	int quant=1;
	while((ptr!= NULL)&&(ptr->aluno.codigo != chave)){
		quant++; //A cada ciclo soma 1 para saber o numero de comparações	
		if(chave > ptr->aluno.codigo){ //direção que a chave percorre
			ptr = ptr->dir;
		}
		else{
			ptr = ptr->esq;
		}
	}
	if(ptr==NULL){
		printf("O aluno #%d nao esta presente na arvore! Foram necessarias %d comparacoes\n\n",chave,quant);
	}
	else{
		printf("\n\tRA:#%d\n\tNome: %s\n\tData: %s\n\tForam necessarias %d comparacoes\n\n", ptr->aluno.codigo, ptr->aluno.nome, ptr->aluno.data,quant);
	}
}

void pIrmao(TNo *ptr,int chave){
	int quant=1;
	TNo *aux;
	while((ptr!= NULL)&&(ptr->aluno.codigo != chave)){
		quant++;
		aux=ptr;
		
		//Enquanto a chave ptr apota para a direita aux aponta pra esquerda 
		if(chave>ptr->aluno.codigo){
			ptr = ptr->dir;
			aux = aux->esq;
		}
		
		else{
			ptr = ptr->esq;
			aux = aux->dir;
		}
	}
	if(ptr==NULL){
		printf("\n\tO aluno #%d nao esta presente na arvore! Foram necessarias %d comparacoes\n\n",chave,quant);
	}
	else if(aux == NULL){
		printf("\n\tA chave %d nao tem Irmao\n\tForam necessarias %d comparacoes\n\n", chave, quant);
	}
	else{
		printf("\n	Irmao:\n\tRA:#%d\n\tNome: %s\n\tData: %s\n\tForam necessarias %d comparacoes\n\n",aux->aluno.codigo, aux->aluno.nome, aux->aluno.data,quant);
	}
}

void pPai(TNo *ptr,int chave){
	int quant=1;
	TNo *aux;
	if(ptr->aluno.codigo == chave){
		printf("A chave nao tem pai, eh a raiz da arvore!");	
	}
	else{	
		while((ptr!= NULL)&&(ptr->aluno.codigo != chave)){
			quant++;
			
			//aux armzena o nó raiz da sub arvore pesquisada ficando 1 atrasado 
			aux = ptr;
			if(chave>ptr->aluno.codigo){
				ptr=ptr->dir;
			}
			
			else{
				ptr = ptr->esq;
			}
		}
		if(ptr==NULL){
			printf("O aluno #%d nao esta presente na arvore! Foram necessarias %d comparacoes\n\n",chave,quant);
		}
		else{
			printf("\n	Pai:\n\tRA:#%d\n\tNome: %s\n\tData: %s\n\tForam necessarias %d comparacoes\n\n",aux->aluno.codigo, aux->aluno.nome, aux->aluno.data,quant);
		}
	}
}

//----------------------------------------------------------------------- Ambas ávores ------------------------------------------------------------------------------------

//----------------------------------------------------------------------- A B P ------------------------------------------------------------------------------------
void insere(TNo **ptr, TipoAluno alu){

	if (*ptr == NULL){ // entra na hora de criar um novo nó
		(*ptr) = ALOCA; //aloco dinamicamente um espaço pra "ptr"
		(*ptr)->esq = NULL;
		(*ptr)->dir = NULL;
		(*ptr)->aluno.codigo = alu.codigo; // o nó recebe o valor do codigo
		(*ptr)->aluno = alu; // o nó recebe os outros valores
	}
	
	else{
		if(alu.codigo<(*ptr)->aluno.codigo){ //verificação para saber em qual lado é inserido o valor
			insere(&(*ptr)->esq,alu); //passa o valor da esquerda se for menor
		}
		else if(alu.codigo>(*ptr)->aluno.codigo){ //verificação para saber em qual lado é inserido o valor
			insere(&(*ptr)->dir,alu); //passa o valor da direita se for maior
		}
	}
}



void retira(TNo **ptr, int chave, int sor){
	
	if((*ptr)==NULL){ //verifica se o valor está na árvore
		printf("\n O aluno #%d nao esta na arvore!\n",chave);
	}
	
	else if(chave<(*ptr)->aluno.codigo){ //verifica o lado que tem que seguir 
		retira(&(*ptr)->esq,chave,sor);
	}
	else if(chave>(*ptr)->aluno.codigo){
		retira(&(*ptr)->dir,chave,sor);
	}
	else{ //caso for a chave retirada
		TNo *aux = *ptr;	//copia o calor a ser retirado 
		if((*ptr)->dir == NULL){	//se a direita for NULL esq fica no lugar 
			(*ptr)=(*ptr)->esq;
			free(aux);
		}
		else if((*ptr)->esq==NULL){ //se a esq for NULL dir fica no lugar 
			(*ptr)=(*ptr)->dir;
			free(aux);
		}
		else{ // caso haja dois filhos
			if(sor == 1){
				sucessor((*ptr),&(*ptr)->dir);
			}
			else{
				antecessor((*ptr),&(*ptr)->esq);
			}
		}
	}
}



void in_ordem(TNo *ptr){
	if(ptr != NULL){
		in_ordem(ptr->esq);
		
		printf("\nRA: %d\t",ptr->aluno.codigo);	
		printf("Nome: %s\t",ptr->aluno.nome);
		printf("Data: %s\t\n",ptr->aluno.data);

		in_ordem(ptr->dir);
	}
}

void pre_ordem(TNo *ptr){
	if(ptr != NULL){
		printf("\nRA: %d",ptr->aluno.codigo);	
		printf("\tNome: %s",ptr->aluno.nome);
		printf("\tData: %s\n",ptr->aluno.data);
		
		pre_ordem(ptr->esq);
		pre_ordem(ptr->dir);
	}
}

void pos_ordem(TNo *ptr){
	if(ptr != NULL){
		pos_ordem(ptr->esq);
		pos_ordem(ptr->dir);
		
		printf("\nRA: %d",ptr->aluno.codigo);	
		printf("\tNome: %s",ptr->aluno.nome);
		printf("\tData: %s\n",ptr->aluno.data);
	}
}
//----------------------------------------------------------------------- A B P ------------------------------------------------------------------------------------


//----------------------------------------------------------------------- A V L ------------------------------------------------------------------------------------
int altura(TNo *ptr){  
	if (ptr == NULL){ //Caso não haja algum nó na árvore
		return -1; //return -1 - altura 
	}
	
	else{
		int he = altura(ptr->esq); //percorrer a esquerda
		int hd = altura(ptr->dir); //percorrer a direita
		if(he<hd){ 		//verifica qual das ramificações é maior
			return hd+1;	//conta os níveis das ramificações da direita
		}
		else{
			return he+1;	//conta os níveis das ramificações da esquerda
		}
	}
}

void rotacaoDir(TNo **ptr){
	
	TNo *q,*temp; //ponteiro
	
	q = (*ptr)->esq; //q vai receber a sub árvore a esquerda
	temp = q->dir; //sub árvore a direita de q 
	q->dir = (*ptr); //aponta pra raiz da sub árvore passada
	(*ptr)->esq = temp; //a raiz vai apontar pra temp
	(*ptr) = q; //defino que q vai ser a nov raiz
	
}

void rotacaoEsq(TNo **ptr){
	TNo *q,*temp; //ponteiro
	
	q = (*ptr)->dir; //q vai receber a sub árvore a direita
	temp = q->esq; //sub árvore a ESQUERDA de q 
	q->esq = (*ptr); //aponta pra raiz da sub árvore passada
	(*ptr)->dir = temp; //a raiz vai apontar pra temp
	(*ptr) = q; //defino que q vai ser a nov raiz
}

void insereAVL(TNo **ptr, TipoAluno alu){
	int FB,fb;
	
	if (*ptr == NULL){ // entra na hora de criar um novo nó
		(*ptr) = ALOCA; //aloco dinamicamente um espaço pra "ptr"
		(*ptr)->esq = NULL;
		(*ptr)->dir = NULL;
		(*ptr)->aluno.codigo = alu.codigo; // o nó recebe o valor do codigo
		(*ptr)->aluno = alu; // o nó recebe os outros valores
	}
	
	else{
		if(alu.codigo<(*ptr)->aluno.codigo){ //verificação para saber em qual lado é inserido o valor
			insereAVL(&(*ptr)->esq,alu); //passa o valor da esquerda se for menor
		}
		else if(alu.codigo>(*ptr)->aluno.codigo){ //verificação para saber em qual lado é inserido o valor
			insereAVL(&(*ptr)->dir,alu); //passa o valor da direita se for maior
		}
	}
	
	//FB - Pai;  
	//fb - filho;
	//Após inserir o valor é verifica do Fator de balanceamento
	
	FB=(altura((*ptr)->dir))-(altura((*ptr)->esq)); //calcula a altura ao desempilhar
	
	if(FB == +2){ //caso o FB do nó seja 2 então tem que fazer alteração 
			
		fb = altura((*ptr)->dir->dir)-altura((*ptr)->dir->esq); //calcula a altura do filho da direita
		
		if(fb==1){ // se for igual a um então rotação simples 
			rotacaoEsq(ptr);
		}
			
		else if(fb == -1){ // se for igual a menos um então rotação dulpa
			rotacaoDir(&(*ptr)->dir);
			rotacaoEsq(ptr);
		}
	}
		
	else if(FB == -2){
		
		fb = (altura((*ptr)->esq->dir))-(altura((*ptr)->esq->esq)); //calcula a altura do filho da direita
		if(fb== -1){ // se for igual a um então rotação simples 
			rotacaoDir(ptr);
		}
	
		else if(fb== +1){ // se for igual a menos um então rotação dulpa
			rotacaoEsq(&(*ptr)->esq);
			rotacaoDir(ptr);
		}	
	}	
}



void retiraAVL(TNo **ptr, int chave,int sor){
	int FB,fb;
	if((*ptr)==NULL){ //verifica se o valor está na árvore
		printf("\n O aluno #%d nao esta na arvore!\n",chave);
	}
	
	else if(chave<(*ptr)->aluno.codigo){ //verifica o lado que tem que seguir 
		retiraAVL(&(*ptr)->esq,chave,sor);
	}
	else if(chave>(*ptr)->aluno.codigo){
		retiraAVL(&(*ptr)->dir,chave,sor);
	}
	else{ //caso for a chave retirada
		TNo *aux = *ptr;	//copia o calor a ser retirado 
		if((*ptr)->dir == NULL){	//se a direita for NULL esq fica no lugar 
			(*ptr)=(*ptr)->esq;
			free(aux);
		}
		else if((*ptr)->esq==NULL){ //se a esq for NULL dir fica no lugar 
			(*ptr)=(*ptr)->dir;
			free(aux);
		}
		else{ // caso haja dois filhos
			if(sor == 1){
				sucessor((*ptr),&(*ptr)->dir);
			}
			else{
				antecessor((*ptr),&(*ptr)->esq);
			}
		}
	}
	
	if((*ptr)!=NULL){ // Para não verificar o nó que foi retirado e esperar a recursividade voltar para assim entrar dentro do if
		FB=altura((*ptr)->dir)-altura((*ptr)->esq); //calcula a altura ao desempilhar
	//	printf("FB: %d\n",FB);	
		
		if(FB==2){ //caso o FB do nó seja 2 então tem que fazer alteração 
				
			fb = altura((*ptr)->dir->dir)-altura((*ptr)->dir->esq); //calcula a altura do filho da direita
			if((fb == 1) || (fb == 0)){ // se for igual a um então rotação simples 
				rotacaoEsq(ptr);
			}	
			else if(fb == -1){ // se for igual a menos um então rotação dulpa
				rotacaoDir(&(*ptr)->dir);
				rotacaoEsq(ptr);
			}
		}
			
		else if(FB == -2){
						
			fb = (altura((*ptr)->esq->dir))-(altura((*ptr)->esq->esq)); //calcula a altura do filho da direita
			if(fb == -1 || fb == 0){ // se for igual a um então rotação simples 
				rotacaoDir(ptr);
			}
			else if(fb == 1){ // se for igual a menos um então rotação dulpa
				rotacaoEsq(&(*ptr)->dir);
				rotacaoDir(ptr);
			}	
		}
	}
}

//----------------------------------------------------------------------- A V L------------------------------------------------------------------------------------



