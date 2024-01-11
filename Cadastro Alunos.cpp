#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct aluno                                                                                               // / nome completo do aluno / nota 1 / nota 2 / media /
{
    char Nome[30];
    float Notas[3];
};

int MenuInicial(){ 
    
    int a;
    printf("\033c"); //limpa a tela
    printf("\nMenu Inicial:\n\n"

    "1: Cadastrar novo aluno.\n"
    "2: Excluir um cadastro.\n"
    "3: Pesquisar um cadastro.\n"
    "4: Apresentar listagem.\n"
    "5: Apresentar listagem por nota.\n"
    "6: Apresentar listagem por nome.\n"
    "7: Sair.\n\n");

    printf("Digite sua escolha: "); scanf("%d", &a);
    return(a);
};

int ProcurarAluno(int a, struct aluno b[20], char auxb[20]){
    int i;
    for(i=0;i<a;i++)
        if(strncmp(b[i].Nome,auxb, 30)==0)
            return(i);
    return(-1);
};

int CadastrarAluno(int a, struct aluno b[20]){   
    if(a<20){
        int flag=1;
        char continuar;
        while(flag>0 && a<5){                                                                      //repete a tela de cadastro enquanto flag>0
            printf("\033c");                                                                       //limpa a tela
            printf("\nMenu de Cadastros:\n");
            printf("\nNome do aluno: "); fflush(stdin); gets(b[a].Nome);

            int encontrado = ProcurarAluno(a, b, b[a].Nome);
            if(encontrado == -1)
            {
                printf("Primeira nota: "); fflush(stdin); scanf("%f", &b[a].Notas[0]);
                printf("Segunda nota: "); fflush(stdin); scanf("%f", &b[a].Notas[1]);
                b[a].Notas[2] = (b[a].Notas[0]+b[a].Notas[1])/2;    
                a++;
                printf("\nRealizado cadastro de numero %d.\n", a);
            }else{
                    printf("\nCadastro ja existente!\n");
                    printf("\nNome: %s\nMedia: %f", b[encontrado].Nome, b[encontrado].Notas[2]);
                    }
            do{                                                                                        //repete a pergunta enquanto não recebe S/s ou N/n como resposta
                printf("\nContinuar cadastrando?(s/n):"); fflush(stdin); scanf("%c", &continuar);
            if (continuar =='N' || continuar =='n'){
                flag=0;
            }else if (continuar =='S' || continuar =='s' || continuar =='\n' && a<5){
                flag++;
            }else{
                printf("\nComando invalido");
            }
            }while(continuar != 'N' && continuar != 'n' && continuar != 'S' && continuar != 's' && continuar != '\n');//fim do loop da pergunta
            };                                                                                                        //fim do loop do cadastro
            }else{
            printf("\nTurma Cheia!!!");
            }
    return(a);
    };

int ExcluirAluno(int a, struct aluno b[20]){
    int encontrado; struct aluno auxb;

    printf("Qual o cadastro a ser apagado? :"); fflush(stdin); gets(auxb.Nome);
    encontrado=ProcurarAluno(a,b, auxb.Nome);
    
    if(encontrado == -1)
        printf("Nome nao encontrado...\n");
    else{
        b[encontrado] = b[a-1];
        a--;
    };
    return(a);
};

int MostrarCadastro(int a, struct aluno b[20])
{   
    struct aluno auxb;      
    printf("Qual o nome a ser procurado? :"); fflush(stdin); gets(auxb.Nome);
    int encontrado=ProcurarAluno(a, b, auxb.Nome);
    if(encontrado == -1)
          printf("Nome nao encontrado...\n");
    else
    {
    printf("\nNome: %s\nMedia: %f", b[encontrado].Nome, b[encontrado].Notas[2]);
    }
}

void ListarAlunos(int a, struct aluno b[20]){
    int i;
    for(i=0;i<(a);i++){
        printf("\nNome: %s\nMedia: %f", b[i].Nome, b[i].Notas[2]);
    }
}

void ListaMedias(int a, struct aluno b[20], struct aluno auxb){
    int i, troca;
    do {
        troca=0;                                                                                   //garante que todas as trocas foram feitas
        for(i=0;i<(a-1);i++)
            if (b[i].Notas[2]>b[i+1].Notas[2]) 
            {
                auxb = b[i];                                                                      //efetua a troca da primeira nota
                b[i] = b[i+1];
                b[i+1] = auxb;
                troca = 1;                                                                        //avisa o do_while que ainda houve troca
            };
    }while(troca==1);
    ListarAlunos(a, b);
}

void ListaAlfabetica(int a, struct aluno b[20], struct aluno auxb){
    int i, troca;
    do {   
        troca=0;                                                                                           //garante que todas as trocas foram feitas
        for(i=0;i<(a-1);i++)
            if (strcmp(b[i].Nome,b[i+1].Nome)>0)
            {
                auxb = b[i];                                                                      
                b[i] = b[i+1];
                b[i+1] = auxb;
                troca = 1;                                                                        //avisa o do_while que ainda houve troca
            };
    }while(troca==1);
    ListarAlunos(a, b);
}

int main()
{
    struct aluno turma[20], auxturma; 
    int  t, opcao;
    
    t=0;
    for(;;){                                                                                               //loop infinito para o menu inicial, só é quebrado escolhendo 6 - exit(0)
        opcao=MenuInicial();
        switch(opcao){                                                                                     // Lê a escolha feita no menu inicial
    
        case 1:
            t = CadastrarAluno(t, turma);
        break;

        case 2:
            t = ExcluirAluno(t, turma);
        break;

        case 3:
            MostrarCadastro(t, turma);
        break;

        case 4:
            ListarAlunos(t, turma);
        break;
        
        case 5:
            ListaMedias(t, turma, auxturma);
        break;

        case 6:
            ListaAlfabetica(t, turma, auxturma);    
        break;

        case 7:
            printf("\033c");                                                                               //limpa a tela
            printf("\nProgrma encerrado...");
            exit(0);
        break;

        default:
            printf("\nComando invalido\n");
        break;
        }
        printf("\n\nDigite 'Enter' para continuar...");                                                    //da uma parada antes de limpar a tela
        fflush(stdin);                            
        getchar();
    }
}