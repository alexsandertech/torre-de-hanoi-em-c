/**  Projeto: Jogo Torre de Hanoi                   *
  *  Curso: Engenharia de Computação                *
  *  Acadêmico: Alexsander Barbosa Siqueira        */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include "./conio.h"
#include "./conio.c"

typedef enum{false,true} bool;   //Definição de um tipo boleano, através do tipo enumerado;
/*Variaveis Globais*/
int torre[8][3];                //Matriz base do jogo, que conterá um numero correspondente a cada disco;
int tempo_menu = 0;             //Variável que armazena o tempo total de acesso ao menu durante o jogo;
int contador_movimentos = 0;    //Variável que conta a quantidade de movimentos realizados em uma partida;
int qtd_discos;                 //Variável que arnazena a quantidade de discos que o jogador deseja, quando necessario;
char nome_jogador[11];          //Variavel que armazena o nome do jogador quando necessario;
bool primeira_execucao = true;  //Verifica se é a primeira execução para impressão da animação de introdução;

typedef struct{                 //Definição de um tipo que armazena informações referentes a uma partida de um derminado jogador;
    float pontuacao;
    char nome[11];
    int tempo;
    int qtd_mov;
    int discos;
    char salvou_hist[4];
}dados_jogador;

int main(void);                              //HANOI/QUIZ/INFO: Escolha entre ir para o jogo torre de hanoi, ver detalhes e curiosidades sobre o jogo ou participar de um quiz sobre o jogo;
void Intro_Animacao(void);                   //                 Animação inicial antes do inicio do jogo;
void Hanoi_Detalhes_Quiz(int *);             //                 Imprime opcoes HANOI/QUIZ/INFO;
void Informacoes_Hanoi(void);                //INFORMAÇÕES DETALHADAS: Função que abre um arquivo contendo informações detalhadas sobre o jogo, com curiosidades etc..;
void Quiz(void);                             //QUIZ:                   Perguntas a respeito do jogo Torre de Hanoi;
void Quiz_Alternativa(int, int *, char, bool *);// QUIZ:               Verifica se a resposta esta correta, caso esteja é incrementado um ponto;
void Jogo_Hanoi(void);                        //JOGO HANOI:            Jogo torre de hanoi;
void Jogo_Hanoi_Opcoes(int *);                //JOGO HANOI:            Escolha de uma opção dentre: Iniciar, Ajuda/Instruções, Quantidade de Discos;
void Imprime_Ajuda(void);                     //OPCOES INICIO:[AJUDA]  Imprime regras, como joga, e explicações de casa modo de jogo;
void Escolha_Qtd_discos(void);                //OPCOES INICIO:[ESCOLHA QUANTIDADE DE DISCOS]    Pergunta a quantidade de discos desejada durante  jogo;
void Estatisticas(void);                      //OPCOES INICIO:[ESTATISTICA]
void Opcoes_Estatistica(int *);               //               ESTATISTICA:           Imprime opções dentre: Ranking, Historico de Movimentose Movimentos Otimos;
void Estatisticas_Ranking(void);              //               ESTATISTICA:[RANKING]
void Imprime_Opcoes_Ranking(int *);           //                            RANKING:               Escolha de uma opção entre: Consultar Ranking ou Resetar Ranking;
void Imprime_Ranking(void);                   //                            RANKING:               Imprime ranking de todos jogadores;
void Estatistica_Mov_Otimos(void);            //               ESTATISTICA:[MOVIMENTOS OTIMOS]
void Imprime_Mov_Otimos(int, int, int, int);  //                            MOVIMENTOS OTIMOS:     Imprime movimentos orimos de acordo com a escolha da quantidade de discos fornecido pelo jogadorr;
void Mov_Otimo(int, int);                     //                            MOVIMENTOS OTIMOS:     Auxilia impressão dos movimentos;
void Estatisticas_Consultar_Hist(void);       //               ESTATISTICA:[CONSULTAR HISTORICO DE MOVIMENTOS]     Imprime historico de movimentos do jogador selecionado;
void Inicio_Modo_Jogo(void);                  //OPCOES INICIO:[INICIO]     Escolha de um modo de jogo;
void Modo_Jogo_Opcoes(int *);                 //               INICIO      Retorna o modo de jogo escolhidoEscolha de um modo de jogo;
void Modo_Treinamento_Competicao(bool);       /*MODO TREINAMENTO/COMPETIÇÃO*///Jogo no modo Treinamento ou Competição conforme escolha do jogador;
void Menu_Treinamento_Competicao(int, bool, bool, float);//MODO TREINAMENTO/COMPETIÇÃO[MENU]
void Imprimir_Opcoes_Menu(bool, bool);                   //MENU: Imprime opções do menu;
void Tempo_Menu(bool, int);                              //MENU [TEMPO]: Imprime tempo de jogo;
void Iniciar_Nova_Partida(void);                         //MENU [INICIAR NOVA PARTIDA]: Inicia um novo jogo;
void Perguntar_Iniciar_Nova_Partida(int);                //      INICIAR NOVA PARTIDA: Pergunta se o jogador deseja iniciar uma nova partida;
void Resolver_Torre_Menu(void);                          //MENU [RESOLVER TORRE] Chama função que resolve de forma recursiva o jogo durante o jogo;
void Undo_Menu(bool, float);                             //MENU [UNDO] Chama função que desfaz a jogada e uma função que verifica se é possivel desfazer uma jogada;
bool Verificar_Undo(void);                               //      UNDO  Verifica se é possivel desfazer uma jogada;
void Undo(float);                                        //      UNDO  Desfaz a quantidade de jogadas determinada pelo jogador;
void Ver_Historico_Menu(void);                           //MENU [VER HISTORICO] Imprime os movimentos realizados pelo jogador até o momento da solicitação;
void Resolver_Torre(int, int, int, int, float);          //[RESOLVE RECURSIVO] Resolve de forma recursiva o jogo durante o jogo;
void Resolver_Move_Disco(int, int, float);               //                    Move o disco e realiza animacão de acordo com as coordenadas passadas pela função "Resolver_Torre";
void Modo_Desafio(void);                     /*MODO DESAFIO*///Jogo no modo Desafio;
void Verificar_Tempo_Desafio(clock_t, int); //[VERIFICA TEMPO MODO DESAFIO]
                                        /*          FUNÇÕES USADAS EM TODOS MODOS DE JOGO           */
void Criar_Arquivo_Historico(void);                 //Cria o arquivo Historico_mov que armazenara os movimentos realizados durante o jogo;
void Guardar_Movimento_Hist(int, int);              //Inprime no arquivo de historico de movimentos as coordenadas ja digitadas;
bool Possuir_Tempo_Opcao(void);                     //Pergunta ao jogador no modo Treinamento se deseja jogar com contagem de tempo;
bool Possuir_Animacao_Opcao(void);                  //Pergunta ao jogador se deseja animação nos movimentos;
float Tempo_Animacao(void);                         //Retorna o tempo de animação escolhido pelo jogador;
//FUNÇÕES DE IMPRESSAO EM TELA:
void Imprimir_Layout(bool);                         //Chama funções que imprimem os pilares, caixa de coordenadas;
void Imprimir_Pilares(void);                        //Imprime os pilares A, B, C;
void Imprimir_Topo_Pilares(void);                   //Imprime o topo dos pilares com sua referencia correta(A,B,C);
void Imprimir_Todos_Discos(void);                   //Chama funções que imprimem os discos contidos na matriz principal do jogo;
void Posicionar_Disco(int, int, int);               //Posiciona na tela corretamente o disco que será impresso;
void Desenha_Disco(int);                            //Função que recebe o numero do disco e imprime na tela uma quantidade de caracteres que é caculado de acordo com o numero do disco;
//Animação do movimento
void Realizar_Animacao_Mov(int, int, float);        //Reliza a animação vertical e chama função que realiza a animação horizontal;
void Apagar_Animacao_Vertical(int, int);            //Apaga rastro deixado na animação vertical;
void Animacao_Horizontal(int, int, int, float);     //Realiza a animação horizontal;
void Auxiliar_Animacao_Horizontal(int, int, int, float);//Imprime no local correto o disco na animação;
void Apagar_Animacao_Horizontal(int, int);          //Apaga rastro deixado na animação horizontal;
//FIM DE JOGO
bool Verifica_Ganhar(void);         //Verifica se o jogador ganhou, através das colunas A e B, sendo que se estiverem fazias o jogador venceu;
void Fim_de_Jogo(int, bool, bool);  //Chama funções que: exibe mensagem de fim de jogo, salvahistorico e salva ranking do jogador;
void Le_Nome(void);                 //Le o nome do jogador para salvar o Historico de Movimentos e o Ranking;
bool Verificar_Nome_Arquivo(void);  //Verifica se o nome digitado pelo jogador é valido;
void Salvar_Historico(char *);      //Salva o historico de movimentos com o nome do jogador
void Salvar_Ranking(int, char);     //Salva o Ranking do jogador com os dados de seu desempenho;
void Mensagem_Fim_de_Jogo(int);     //Exibe mensagem de fim de jogo com a quantidade de movimentos e o tempo de jogo;
//Funções de manipulação da matriz principal do jogo>
void Iniciar_Matriz(void);                           //Inicializa a matriz de inteiros principal com a quantidade de discos correspondente;
void Escolha_Movimento(int *, int *, bool, clock_t, int);//Determina as coordenadas validas fornecidas pelo jogador;
void Le_Coordenada(int *, int, bool, clock_t, int); //Lê a coordenada independente da origem ou destino;
bool Comparar_orig_dest(int *, int *);              //Compara o disco pilar de origem com o do pilar de de destino para saber se é valido o movimento [comparação menor ou maior]
void Move_Disco(int, int);                          //Move o numero na matriz principal para coluna selecionada;
//FUNÇÕES  DE USO GERAL
void Opcao_Numerica(int *, int, int, int, int); //Realiza a leitura de uma opção, de acordo com os parametros passado a função
void Refreshing_Cores(void);                    //Muda as cores para o fundo branco e as cores dos caracteres azu
void Refreshing_Tela(bool);                     //Imprime Layout novamente juntamente com os discos;
void Borda_Janela(int, int, int, int);          //Imprime a borda das janelas com o tamanho correspondente e na possição correspondente dependendo dos arqgumentos passados;

int main(void){
    int opcao;

    system("color F1");
    Refreshing_Cores();
    if(primeira_execucao)//Execução da animação de introdução apenas na primeira execução do programa, para caso o jogo seja reiniciado não execte novemente;
         Intro_Animacao();
    primeira_execucao = false;
    Refreshing_Cores();
    do{
        Hanoi_Detalhes_Quiz(&opcao);
        system("cls");
        switch(opcao){
            case(1)://OPCAO 1: Jogo Torre de Hano;
                Jogo_Hanoi();
            break;
            case(2)://OPCAO 2: Detalhes sobre jogo torre de Hanoi;
                Informacoes_Hanoi();
            break;
            case(3)://OPCAO 3: Quiz sobre o jogo;
                Quiz();
            break;

        }
        system("cls");
    }while(1);

    return 0;
}

void Intro_Animacao(void){
    int i, j;
    char nome_do_jogo[15] = {"Torre de Hanoi"};

    gotoxy(29,11); printf("+---------------+");//Caixa que envolve a string;
    gotoxy(29,13); printf("+---------------+");
    for(i=0; i<14; i++){
        gotoxy((31+i),12);
        for(j=10; j<50; j++){//Imprimindo caracteres da tabela ascii em sequencia d0 10 a 50;
            fflush(stdin);
            gotoxy((31+i),12); printf("%c", j);
            if(kbhit())//Ao apertar de qualquer tecla a animação de introdução é encerrada;
                return;
            Sleep(1);
        }
        gotoxy((31+i),12); printf("%c", nome_do_jogo[i]);//Imprimindo uma letra da string a cada repetição do for;
     }
    for(i=5; i>0; i--){//Imprimindo discos descendo e aproveitando as funções que são responsaveis pela impressao.
        for(j=7; j<10; j++){
            Posicionar_Disco(1, i, j+i);
            Posicionar_Disco(1, 15, j+i-1);
            Sleep(100);
        }
     }
    system("cls");
}

void Hanoi_Detalhes_Quiz(int *opcao){
    Borda_Janela(46, 15, 7, 13);
    gotoxy(33,5);  printf("Opcao: ");
    gotoxy(15,8);  printf("%c Jogo Torre de Hanoi                       1 %c", 179, 179);
    gotoxy(15,9);  printf("%c                                             %c", 179, 179);
    gotoxy(15,10); printf("%c Detalhes sobre jogo torre de Hanoi        2 %c", 179, 179);
    gotoxy(15,11); printf("%c                                             %c", 179, 179);
    gotoxy(15,12); printf("%c Quiz sobre o jogo                         3 %c", 179, 179);
    Opcao_Numerica(&*opcao, 1, 3, 40, 14);
}

void Informacoes_Hanoi(void){
    FILE* informacoes;
    char texto_info[2];

    system("cls");
    informacoes = fopen("Arquivos\\Informacoes.txt", "r");
    while(fgets(texto_info, 2, informacoes)!=NULL){
        printf("%s", texto_info);
        if(kbhit()){
        }else{
            Sleep(10);
        }
    }
    fclose(informacoes);
    system("pause");
    system("cls");
}

void Quiz(void){
    bool sair=false;
    int pontos=0, i=1;
    char imprime_perguntas[2], respostas_corretas[14] = {' ','a', 'c', 'c', 'd', 'a', 'd', 'b', 'b', 'c', 'd', 'b', 'd', 'a'};
    FILE *perguntas_arquivo;

    perguntas_arquivo = fopen("Arquivos\\Quiz.txt", "r");
    if (perguntas_arquivo == NULL){
    	printf("Arquivo Quiz.txt nao foi encontrado.\n\n");
    	system ("pause");
    	return;
	}
    while (fgets(imprime_perguntas, 2, perguntas_arquivo) != NULL){//Imprimindo todas questões armazenadas em um arquivo;
    	printf("%s", imprime_perguntas);
    	if(kbhit()){
    	}else
            Sleep(1);
    }
    fclose(perguntas_arquivo);
    printf("\n\t\t\t***Responda as Questoes***\n[s/S]: Sair\n\n");
    do{//Apos a impressai de todas as questoes eh solicitado as respostas;
        fflush(stdin);
        Quiz_Alternativa(i, &pontos, respostas_corretas[i], &sair);
        i++;
    }while(i!=14 && !sair);
    printf("\n\nTotal de acertos: %d de %d questoes respondidas\n\n", pontos, i-2);
    system("pause");
}

void Quiz_Alternativa(int num_questao, int *pontos, char resposta_correta, bool *sair){
    char opcao;
    do{
        fflush(stdin);
        printf("%d%c) R: ", num_questao, 166);
        scanf ("%c", &opcao);
        opcao = tolower(opcao);
        if(opcao=='s')//Verifica se o jogador digitou uma a tecla correspondente ao sair;
            *sair = true;
    }while(opcao != 'a' && opcao != 'b' && opcao != 'c' && opcao != 'd' && opcao != 's');
    if (opcao==resposta_correta)//Se a resposta estiver correta é adicionado um pondo;
        *pontos = *pontos + 1;
}

void Jogo_Hanoi(void){
    int opcao;
    int verifica_qtd=0;

    do{
        system("cls");
        Jogo_Hanoi_Opcoes(&opcao);
        switch(opcao){
        case(1)://OPCAO 1: Iniciar jogo;
            if(verifica_qtd==0){
                qtd_discos = 3;
                Iniciar_Matriz();
            }
            verifica_qtd = 0;
            Inicio_Modo_Jogo();
           break;
        case(2)://OPCAO 2: Ajuda/Instruções;
            Imprime_Ajuda();
           break;
        case(3)://OPCAO 3: Escolher quantidade de discos;
            Escolha_Qtd_discos();
            Iniciar_Matriz();
            verifica_qtd = 1;
           break;
        case(4)://OPCAO 4: Consultar Estatisticas;
            Estatisticas();
            break;
        case(5)://OPCAO 5: Voltar;
            break;
        }
        if(opcao!=5)
            opcao=0;
    }while(opcao<1 || opcao>5);
}

void Jogo_Hanoi_Opcoes(int *opcao){
    Borda_Janela(26, 20, 7, 17);
    gotoxy(20,8);  printf("%cIniciar                1 %c", 179, 179);
    gotoxy(20,9);  printf("%c                         %c", 179, 179);
    gotoxy(20,10); printf("%cAjuda/Instrucoes       2 %c", 179, 179);
    gotoxy(20,11); printf("%c                         %c", 179, 179);
    gotoxy(20,12); printf("%cQuantidade de Discos   3 %c", 179, 179);
    gotoxy(20,13); printf("%c                         %c", 179, 179);
    gotoxy(20,14); printf("%cEstatisticas           4 %c", 179, 179);
    gotoxy(20,15); printf("%c                         %c", 179, 179);
    gotoxy(20,16); printf("%cVoltar                 5 %c", 179, 179);
    gotoxy(30,5);  printf("Opcao: ");
    Opcao_Numerica(&*opcao, 1, 5, 37, 18);
}

void Imprime_Ajuda(void){
    FILE *ajuda_arq;
    char imprime_ajuda[2];

    system("cls");
    ajuda_arq = fopen("Arquivos\\Ajuda_Instrucoes.txt", "r");
    while(fgets(imprime_ajuda, 2, ajuda_arq)!=NULL){
        printf("%s", imprime_ajuda);
        if(kbhit())
            Sleep(0);
        else
            Sleep(10);
    }
    printf("\n\n");
    fclose(ajuda_arq);
    system("pause");
}

void Escolha_Qtd_discos(void){
    system("cls");
    do{
        Borda_Janela(42, 17, 9, 12);
        gotoxy(17,10); printf("%c   Quantidade de discos desejada:[1 a 7] %c", 179, 179);
        gotoxy(17,11); printf("%cR:                                       %c", 179, 179);
        gotoxy(20,11); scanf("%d", &qtd_discos);
        system("cls");
        if(qtd_discos<1 || qtd_discos>7){
            gotoxy(17,14); printf("Quantidade de discos invalida!");
        }
    }while(qtd_discos<1 || qtd_discos>7);
}

void Estatisticas(void){
    int opcao;

    do{
        Opcoes_Estatistica(&opcao);
        switch(opcao){
        case(1)://OPCAO 4: Consultar Ranking;
            Estatisticas_Ranking();
            break;
        case(2)://OPCAO 4: Historico de Movimentos;
            system("cls");
            Estatisticas_Consultar_Hist();
            break;
        case(3)://OPCAO 4: Movimentos Otimos;
            Estatistica_Mov_Otimos();
            break;
        case(4)://OPCAO 4: Voltar;
            break;
        }
    }while(opcao!=4);
}

void Opcoes_Estatistica(int *opcao){
    system("cls");
    Borda_Janela(27, 20, 7, 15);
    gotoxy(20,8);  printf("%cRanking                 1 %c", 179, 179);
    gotoxy(20,9);  printf("%c                          %c", 179, 179);
    gotoxy(20,10); printf("%cHistorico de Movimentos 2 %c", 179, 179);
    gotoxy(20,11); printf("%c                          %c", 179, 179);
    gotoxy(20,12); printf("%cMovimentos Otimos       3 %c", 179, 179);
    gotoxy(20,13); printf("%c                          %c", 179, 179);
    gotoxy(20,14); printf("%cVoltar                  4 %c", 179, 179);
    gotoxy(30,5);  printf("Opcao: ");
    Opcao_Numerica(&*opcao, 1, 4, 37, 18);
}

void Estatisticas_Ranking(void){
    int opcao, i;
    FILE *resetar;
    do{
        Imprime_Opcoes_Ranking(&opcao);
        switch(opcao){
            case(1)://OPCAO 4: Consultar Ranking;
                system("cls");
                Imprime_Ranking();
                break;
            case(2)://OPCAO 4: Resetar Ranking;
                system("cls");
                gotoxy(30,11);printf("Resetando Ranking");
                for(i=0; i<3; i++){
                    gotoxy(47,11);printf("   ");
                    Sleep(300);
                    gotoxy(47,11);printf(".");
                    Sleep(300);
                    gotoxy(48,11);printf(".");
                    Sleep(300);
                    gotoxy(49,11);printf(".");
                    Sleep(300);
                }
                resetar = fopen("Arquivos\\Ranking.dat", "wb");
                fclose(resetar);
                break;
            case(3)://OPCAO 3: Voltar;
                break;
        }
    }while(opcao!=3);
}

void Imprime_Opcoes_Ranking(int *opcao){
    system("cls");
    Borda_Janela(26, 20, 7, 13);
    gotoxy(20,8);  printf("%cConsultar Ranking      1 %c", 179, 179);
    gotoxy(20,9);  printf("%c                         %c", 179, 179);
    gotoxy(20,10); printf("%cResetar Ranking        2 %c", 179, 179);
    gotoxy(20,11);  printf("%c                         %c", 179, 179);
    gotoxy(20,12); printf("%cVoltar                 3 %c", 179, 179);
    gotoxy(30,5);  printf("Opcao: ");
    Opcao_Numerica(&*opcao, 1, 3, 37, 13);
}

void Imprime_Ranking(void){
	FILE *ranking_arq;
	int contador = 1, i;
	int linha = 5;
	long int ultimo_byte;
	dados_jogador ler_arq;

	system("cls");
	ranking_arq = fopen("Arquivos\\Ranking.dat", "rb");
    fseek(ranking_arq, 0, SEEK_END);//Posicionando "cursor" na ultima posição;
    ultimo_byte = ftell(ranking_arq);
    rewind(ranking_arq);

    gotoxy(30,1);printf("RANKING JOGADORES");//Imprimindo Cabeçalho;
    gotoxy(5, 3);printf("%cPontuacao %c Nome       %c Tempo %c Qtd_mov %c Discos %c Salv_hist %c", 179, 179, 179, 179, 179, 179, 179);
    Borda_Janela(63,5,2,4);
    gotoxy(5, 5);printf("%c- - - - - | - - - - - -| - - - | - - - - | - - - -| - - - - - %c", 179, 179);

    while(ftell(ranking_arq)<ultimo_byte){
        fread(&ler_arq, sizeof(ler_arq), 1, ranking_arq);
        if(linha<25)
            gotoxy(1, linha);
        else
            gotoxy(1,26);
        printf("\n%-2d%c %c%-10.2f%c%-12s%c%-7d%c%-9d%c%-8d%c%-11s%c", contador, 167 , 179, ler_arq.pontuacao, 179, ler_arq.nome, 179,ler_arq.tempo, 179,ler_arq.qtd_mov, 179,ler_arq.discos, 179,ler_arq.salvou_hist, 179);
        linha++;
        contador++;
    }
    printf("\n");

    printf("    %c", 192);
    for(i=0; i<62; i++)
        printf("%c", 196);
    printf("%c", 217);

	fclose(ranking_arq);
    printf("\n\n");
	system("pause");
}

void Estatistica_Mov_Otimos(void){
    int i, cond_parada;

    Escolha_Qtd_discos();
    system("cls");
    printf("\t\t---Movimentos Torre de %d discos---\n", qtd_discos);
    Imprime_Mov_Otimos(qtd_discos,0, 2, 1);
    cond_parada = pow(2,qtd_discos)-1;
    for(i=1; i<=cond_parada; i++){
        textcolor(0);
        gotoxy(1, i+1); printf("\n%d%c:", i, 167);
        Sleep(1);
    }
    printf("\n\n");
    textcolor(1);
    system("pause");
}

void Imprime_Mov_Otimos(int qtd_discos, int orig, int dest, int aux){
    if(qtd_discos==1){//Imprimindo movimentos otimos de forma recursiva;
        Mov_Otimo(orig, dest);
    }else{
        Imprime_Mov_Otimos(qtd_discos-1, orig, aux, dest);
        Mov_Otimo(orig, dest);
        Imprime_Mov_Otimos(qtd_discos-1, aux, dest, orig);
    }
}

void Mov_Otimo(int orig, int dest){
    printf("\n\t%c  %c  %c  ", orig+65, 26, dest+65);
}

void Estatisticas_Consultar_Hist(void){
    int cont_hist=0;
    int i;
    char imprime_historico[6];
    char nome_arquivo[40];

    do{
        gotoxy(20, 1); printf("--Consultar Historico de Movimentos--");
        gotoxy(5, 9);  printf("Selecione o nome do Jogador informado anteriormente ao final");
        gotoxy(5, 10); printf("da partida para acessar seu respectivo historico de movimentos.");
        Le_Nome();
        if(!Verificar_Nome_Arquivo()){
            gotoxy(5, 20);
            printf("Jogador invalido!");
        }
    }while(!Verificar_Nome_Arquivo());

    strcpy(nome_arquivo, "Arquivos\\");
    strcat(nome_arquivo, "Historicos\\");
    strcat(nome_arquivo, nome_jogador);
    strcat(nome_arquivo, ".txt");

    FILE *consulta_historico;
    consulta_historico = fopen(nome_arquivo, "rt");
    system("cls");
    printf("\t\t---Historico do jogador: %s---\n", nome_jogador);
    while(fgets(imprime_historico, 6, consulta_historico)!=NULL){
        cont_hist++;
        printf("      %s", imprime_historico);
        Sleep(10);
    }
    cont_hist = cont_hist/2;
    for (i=1; i<=cont_hist; i++){
        textcolor(0);
        gotoxy(1, i); printf("\n%d%c:", i, 167);
        Sleep(10);
    }
    fclose(consulta_historico);
    textcolor(1);
    printf("\n\n");
    system("pause");
}

void Inicio_Modo_Jogo(void){
    int opcao;
    bool modo_treinamento;

    Modo_Jogo_Opcoes(&opcao);
    switch(opcao){
    case(1)://OPCÃO: Jogo Modo Treinamento;
        modo_treinamento = false;
        Modo_Treinamento_Competicao(modo_treinamento);
        break;
    case(2)://OPCÃO: Jogo Modo Competicao;
        modo_treinamento = true;
        Modo_Treinamento_Competicao(modo_treinamento);
        break;
    case(3)://OPCÃO: Jogo Modo Desafio;
        Modo_Desafio();
        break;
    case(4)://OPCÃO: Voltar;
        break;
    }
}

void Modo_Jogo_Opcoes(int *opcao){
    system("cls");
    Borda_Janela(27, 20, 7, 15);
    gotoxy(20,8);  printf("%cModo Competicao         1 %c", 179, 179);
    gotoxy(20,9);  printf("%c                          %c", 179, 179);
    gotoxy(20,10); printf("%cModo Treinamento        2 %c", 179, 179);
    gotoxy(20,11); printf("%c                          %c", 179, 179);
    gotoxy(20,12); printf("%cModo Desafio            3 %c", 179, 179);
    gotoxy(20,13); printf("%c                          %c", 179, 179);
    gotoxy(20,14); printf("%cVoltar                  4 %c", 179, 179);
    gotoxy(30,5);  printf("Opcao: ");
    Opcao_Numerica(&*opcao, 1, 4, 37, 18);
}

void Modo_Treinamento_Competicao(bool modo_treinamento){
    int orig, dest, tempo_jogo=0;
    float tempo_ani=0;
    bool possuir_tempo=true, perguntar_nova_partida = true;
    clock_t tempo_inicial=0, tempo_final=0;

    Criar_Arquivo_Historico();
    if(Possuir_Animacao_Opcao())//Verificando se o jogador deseja animação;
        tempo_ani = Tempo_Animacao();

    if(modo_treinamento){//Verificando se o jogador deseja jogar com contagem de tempo no modo treinamento;
        possuir_tempo = Possuir_Tempo_Opcao();
        if(possuir_tempo){
            tempo_menu = 0;
            tempo_inicial = clock();
        }else{
            tempo_inicial = tempo_final = tempo_menu = -1;
        }
    }else{
        possuir_tempo = true;
        tempo_menu = 0;
        tempo_inicial = clock();
    }
    do{
        Refreshing_Tela(true);
        Escolha_Movimento(&orig, &dest, false, tempo_inicial, -1);//
        if(orig==12 || dest==12){//Acessando menu durante o jogo;
           Menu_Treinamento_Competicao(tempo_inicial, possuir_tempo, modo_treinamento, tempo_ani);
        }else{
            Guardar_Movimento_Hist(orig, dest);//Guardar movimento no arquivo de historico de movimentos;
            if(tempo_ani!=0)
                Realizar_Animacao_Mov(orig, dest, tempo_ani);//Realizando animação no movimento, caso o jogador tenha soliitado a animação;
            Move_Disco(orig, dest);//Realizando movimento na matriz principal de inteiros do jogo;
        }
    }while(Verifica_Ganhar());
    tempo_final = clock();
    system("cls");
    if(possuir_tempo){//Finalizando Contagem de Tempo e subtraindo o tempo de acesso ao menu;
        tempo_jogo = (tempo_final)/CLOCKS_PER_SEC - (tempo_inicial)/CLOCKS_PER_SEC;
        tempo_jogo = tempo_jogo - tempo_menu;
    }else
        tempo_jogo = -1;
    Fim_de_Jogo(tempo_jogo, perguntar_nova_partida, modo_treinamento);//Chamando função que exibe mensagem de fim de jogo e termina o jogo caso o jogador queira;
}

void Menu_Treinamento_Competicao(int tempo_inicial, bool possuir_tempo, bool modo_treinamento, float tempo_ani){
    char opcao;
    int auxi_tempo = 0;

    clock_t tempo_inicial_menu;
    clock_t tempo_final_menu;
    tempo_inicial_menu = clock();//Iniciando contagem de acesso ao tempo de menu;

    auxi_tempo = (tempo_inicial_menu - tempo_inicial)/CLOCKS_PER_SEC;
    auxi_tempo = auxi_tempo - tempo_menu;

    textcolor(7);
    Refreshing_Tela(false);
    textcolor(1);

    do{
        fflush(stdin);
        Imprimir_Opcoes_Menu(modo_treinamento, possuir_tempo);
        gotoxy(44,3); scanf("%c", &opcao);
        opcao = toupper(opcao);
        switch(opcao){
            case'A'://OPCAO A: AJUDA;
                Imprime_Ajuda();
                break;
            case'T'://OPCAO T: IMPRIMIR TEMPO DE JOGO;
                Tempo_Menu(possuir_tempo, auxi_tempo);
                break;
            case'I'://OPCAO I: INICIAR NOVA PARTIDA
                Iniciar_Nova_Partida();
                break;
            case'D'://OPCAO D: DESFAZER JOGADA;
                Undo_Menu(modo_treinamento, tempo_ani);
                break;
            case'R'://OPCAO R: RESOLVER JOGO;
                Resolver_Torre_Menu();
                Perguntar_Iniciar_Nova_Partida(auxi_tempo);
                break;
            case'H'://OPCAO H: EXIBIR HISTORICO DE MOVIMENTOS ATÉ O MOMENTO DE JOGO;
                Ver_Historico_Menu();
                break;
            case 'C'://OPCAO C: CONSULTAR RANKING;
                Imprime_Ranking();
                break;
            case'S'://OPCAO S: ENCERRAR O JOGO;
                Fim_de_Jogo(auxi_tempo, false, false);
                break;
            case'V'://OPCAO V: VOLTAR AO JOGO;
                break;

        }
        textcolor(7);
        Refreshing_Tela(false);
        textcolor(1);
    }while(opcao!='V');
    gotoxy(1,25);
    tempo_final_menu = clock();
    system("color F1");
    tempo_menu = tempo_menu + (tempo_final_menu - tempo_inicial_menu)/CLOCKS_PER_SEC;//Encerrando contagem de tempo de acesso ao  de menu;
}

void Imprimir_Opcoes_Menu(bool modo_treinamento, bool possuir_tempo){
    int i;

    Borda_Janela(21, 28, 2, 21);
    for(i=5; i<21; i=i+2){//Imprimindo espaços entre cada opcao;
        gotoxy(28,i); printf("%c                    %c", 179, 179);
    }
    gotoxy(28,6);
    if(possuir_tempo)//Imprimindo opção formatada de acordo com a opção do usuario decidida anteriormente;
        printf("%c Ver Tempo        T %c", 179, 179);
    else
        printf("%c-Tempo----------NULL%c", 179, 179);
    gotoxy(28,10);
    if(modo_treinamento)
        printf("%c Desfazer         D %c", 179, 179);
    else
        printf("%c-Desfazer-------NULL%c", 179, 179);//Imprimindo opções;
    gotoxy(28,3);  printf("%c        Menu:       %c", 179, 179);
    gotoxy(28,4);  printf("%c Ajuda            A %c", 179, 179);
    gotoxy(28,12); printf("%c Resolver         R %c", 179, 179);
    gotoxy(28,8);  printf("%c Iniciar/Novo     I %c", 179,179);
    gotoxy(28,14); printf("%c Historico[Mov]   H %c", 179, 179);
    gotoxy(28,16); printf("%c Consultar RankingC %c", 179, 179);
    gotoxy(28,18); printf("%c Sair             S %c", 179, 179);
    gotoxy(28,20); printf("%c Voltar ao Jogo   V %c", 179, 179);
    gotoxy(32,23);
    if(possuir_tempo){//Imprimindo opção formatada de acordo com a opção do usuario decidida anteriormente;
        printf("Tempo Pausado");
    }else{
        printf(" ");
    }
}

void Tempo_Menu(bool possuir_tempo, int auxi_tempo){
    if(possuir_tempo){
        gotoxy(3,20); printf("Tempo: %d seg\n", auxi_tempo);
        gotoxy(1,25); system("pause");
    }else{
        gotoxy(3,20); printf("Tempo: NULL");
        gotoxy(3,21);
    }
}

void Iniciar_Nova_Partida(void){
    contador_movimentos = 0;
    tempo_menu = 0;
    Jogo_Hanoi();
    system("cls");
    primeira_execucao = false;
    main();
}

void Perguntar_Iniciar_Nova_Partida(int auxi_tempo){
    char verifica_iniciar_novo;

    do{
        Borda_Janela(37, 22, 21, 23);
        gotoxy(22,22); printf("%c Deseja iniciar um novo jogo?[S/N]  %c", 179, 179);
        gotoxy(57,22); scanf("%c", &verifica_iniciar_novo);
        verifica_iniciar_novo = tolower(verifica_iniciar_novo);
    }while(verifica_iniciar_novo!='s' && verifica_iniciar_novo!='n');

    if(verifica_iniciar_novo=='s'){
        Iniciar_Nova_Partida();
    }else{
        Fim_de_Jogo(auxi_tempo, false, false);
    }
}

void Resolver_Torre_Menu(void){
    int aux_qtd_discos = qtd_discos;
    float tempo_anima_resolve;

    Iniciar_Matriz();
    contador_movimentos = 0;
    Refreshing_Tela(false);
    Borda_Janela(37, 22, 21, 23);
    do{
        gotoxy(22,22); printf("%c Tempo de movimento da animacao :   %c", 179, 179);
        gotoxy(56,22); scanf("%f", &tempo_anima_resolve);
    }while(tempo_anima_resolve<0);

    Resolver_Torre(aux_qtd_discos, 0, 2, 1, tempo_anima_resolve);
    Refreshing_Tela(false);
}

void Undo_Menu(bool modo_treinamento, float tempo_ani){
    if(modo_treinamento){
        Refreshing_Tela(false);
        if(Verificar_Undo())
            Undo(tempo_ani);
    }
}

bool Verificar_Undo(void){
    int i, j;

    for(j=1; j<3; j++){//Verifica de é possivel desfazer alguma jogada, pois não sera permitido desfazer jogada se o jogador anda não realizou uma jogada;
        for(i=0; i<8; i++){
            if(torre[i][j]!=8){
                return true;
            }
        }
    }
    return false;
}

void Undo(float tempo_ani){
    int desfazendo, qtd_desfazer=0;
    int orig_auxi, dest_auxi;
    char orig, dest;
    int cont, aux_cont;
    char aux;
    FILE *desfazer;
    FILE *desfazer_auxiliar;

    do{
        Borda_Janela(52, 12, 21, 23);
        gotoxy(12,22); printf("%c Quantidade de movimentos que deseja desfazer:     %c", 179, 179);
        gotoxy(61,22); scanf("%d", &qtd_desfazer);
    }while(qtd_desfazer<1 || qtd_desfazer>contador_movimentos);

    for(desfazendo=0; desfazendo<qtd_desfazer; desfazendo++){//for que repete a quantidade de jogadas que o jogador deseja desfazer;
        cont = aux_cont = 0;
        Imprimir_Todos_Discos();
        desfazer = fopen("Arquivos\\Historicos\\Historico_mov.txt", "rt");
        desfazer_auxiliar = fopen("Arquivos\\Historicos\\Auxiliar.txt", "wt");//Criando um arqivo auxiliar para passar todas jogadas menos a ultima;
        while(!feof(desfazer)){
            fscanf(desfazer ,"%c - %c\n", &orig, &dest);
        }
        orig_auxi = orig;//Convertendo os valores lidos para numeros para realizar o movimento na matriz de inteiros;
        dest_auxi = dest;
        orig_auxi-=65;
        dest_auxi-=65;

        Realizar_Animacao_Mov(dest_auxi, orig_auxi,tempo_ani);//Mostrando ao jogador o movimento sendo desfeito;
        Move_Disco(dest_auxi, orig_auxi);
        Imprimir_Todos_Discos();

        fseek(desfazer, sizeof(char), SEEK_SET);//Posicionando cursor no inicio para contagem de caracteres;
        while(!feof(desfazer)){
            fscanf(desfazer, "%c", &aux);
            cont++;//Contando a quantidade de caracteres armazenados no arquivo que por enquanto contem dodos movimentos;
        }
        freopen("Arquivos\\Historicos\\Auxiliar.txt", "a", desfazer_auxiliar);
        rewind(desfazer);
        fseek(desfazer, sizeof(char)*(-1), SEEK_SET);

        while(!feof(desfazer)){//Passando todos caracteres de um arquivo para outro menos a ultima jogada;
            fread(&aux, sizeof(char), 1, desfazer);
            if(aux_cont<cont-6)//Verifica se ainda não chegou na ultima jogada que não sera copiada;
                fwrite(&aux, sizeof(char), 1, desfazer_auxiliar);
            aux_cont++;
        }
        fclose(desfazer);
        fclose(desfazer_auxiliar);
        DeleteFile("Arquivos\\Historicos\\Historico_mov.txt");//Deletando arquivo que contem todos movimentos inclusive o movimento que foi desfeito;
        rename("Arquivos\\Historicos\\Auxiliar.txt", "Arquivos\\Historicos\\Historico_mov.txt");//Renomeando o arquivo auxiliar que contem os movimentos sem os movimentos que foram desfeitos;

        contador_movimentos--;
        gotoxy(3,18); printf("Mov.: %d   ", contador_movimentos);
    }
}

void Ver_Historico_Menu(void){
    int cont_hist=0;
    int i;
    char imprime_historico[6];
    FILE *historico;

    historico = fopen("Arquivos\\Historicos\\Historico_mov.txt", "rt");
    system("cls");
    printf("\t\t---Historico de movimentos---\n\n");
    while(fgets(imprime_historico, 6, historico)!=NULL){
        cont_hist++;
        printf("      %s", imprime_historico);
        Sleep(10);
    }
    cont_hist = cont_hist/2;
    for (i=1; i<=cont_hist; i++){
        textcolor(0);
        gotoxy(1, i+1); printf("\n%d%c:", i, 167);
        Sleep(10);
    }
    printf("\n");
    fclose(historico);
    system("pause");
}

void Resolver_Torre(int aux_qtd_discos, int orig, int dest, int aux, float tempo){

    if(aux_qtd_discos==1){//Resolvendo de forma recursiva o jogo;
        Resolver_Move_Disco(orig, dest, tempo);
    }else{
        Resolver_Torre(aux_qtd_discos-1, orig, aux, dest, tempo);
        Resolver_Move_Disco(orig, dest, tempo);
        Resolver_Torre(aux_qtd_discos-1, aux, dest, orig, tempo);
    }
}

void Resolver_Move_Disco(int orig, int dest, float tempo){
    system("cls");
    Imprimir_Layout(false);
    Imprimir_Todos_Discos();
    gotoxy(33,19); printf("  %c  %c  %c  ", orig+65, 26, dest+65);//Mostrando ao jogados os passos para resolução;
    Realizar_Animacao_Mov(orig, dest, tempo);//Mostrando a animação da resolução;
    Move_Disco(orig, dest);//Modificando matriz de inteiros pasa salvar os movimentos;
    contador_movimentos+=1;
}

void Modo_Desafio(void){
    int orig, dest;
    float tempo_ani=-1;
    int tempo_desafio;
    int tempo_jogo=0;
    clock_t tempo_inicial=0, tempo_final=0;

    Criar_Arquivo_Historico();

    tempo_desafio = pow(2,qtd_discos)-1;
    if(Possuir_Animacao_Opcao()){//Perguntando ao jogador se deseja animação nos movimentos que serão realizados;
        tempo_ani = Tempo_Animacao();//Determinando o tempoq que durará a animação;
    }
    tempo_menu = 0;
    tempo_inicial = clock();
    do{
        Refreshing_Tela(false);
        Verificar_Tempo_Desafio(tempo_inicial, tempo_desafio);//Verificando se o tempo limite foi atingido;
        Escolha_Movimento(&orig, &dest, true, tempo_inicial, tempo_desafio);//Lendo o movimento digitado pelo jogador;
        Guardar_Movimento_Hist(orig, dest);//Guardando no historico de movimentos o movimento realizado;
        if(tempo_ani!=-1){//Verificando se o jogador escolheu possuir animação para realiza-la;
            Realizar_Animacao_Mov(orig, dest, tempo_ani);
        }
        Verificar_Tempo_Desafio(tempo_inicial, tempo_desafio);
        Move_Disco(orig, dest);
    }while(Verifica_Ganhar());
    tempo_final = clock();
    system("cls");
    tempo_jogo = (tempo_final)/CLOCKS_PER_SEC - (tempo_inicial)/CLOCKS_PER_SEC;
    Fim_de_Jogo(tempo_jogo, true, false);//Chamando função que exibe mensagem de fim de jogo e termina o jogo caso o jogador queira;
}

void Verificar_Tempo_Desafio(clock_t tempo_inicial, int tempo_desafio){
    clock_t tempo_verifica;
    clock_t tempo_atual;

    tempo_atual = clock();
    tempo_verifica = (tempo_atual - tempo_inicial)/CLOCKS_PER_SEC;//Calculando a diferença de tempo desde o inicio do jogo;
    gotoxy(3,20); printf("Tempo restante: %ld seg.", (tempo_desafio - tempo_verifica));//Imprimindo na tela o tempo de jogo;
    if(tempo_verifica > tempo_desafio){//Verificando se o tempo limite determinado foi atingido;
        Fim_de_Jogo(tempo_desafio, true, false);
    }
}

void Criar_Arquivo_Historico(void){
    FILE *historico;
    historico = fopen("Arquivos\\Historicos\\Historico_mov.txt","w");
    fclose(historico);
}

bool Possuir_Tempo_Opcao(void){
    char auxi_possuir;

    system("cls");
    Borda_Janela(46, 15, 9, 12);
    gotoxy(15,10); printf("%c   Deseja jogar com contagem de tempo[S/N]   %c", 179, 179);
    gotoxy(15,11); printf("%cR:                                           %c", 179, 179);
    do{
        gotoxy(20,11); printf("  ");
        gotoxy(20,11); scanf("\n%c", &auxi_possuir);
        auxi_possuir = tolower(auxi_possuir);
    }while(auxi_possuir!='s' && auxi_possuir!='n');
    if(auxi_possuir=='s')
        return true;
    else
        return false;
}

bool Possuir_Animacao_Opcao(void){
    char auxi_possuir;

    system("cls");
    Borda_Janela(53, 15, 9, 11);
    gotoxy(21,12); printf("Obs.: A animacao interfere no tempo final");
    do{
        gotoxy(15,10); printf("%c Deseja animacao nos movimentos dos discos [S/N]:   %c", 179, 179);
        gotoxy(66,10); scanf("\n%c", &auxi_possuir);
        auxi_possuir = tolower(auxi_possuir);
    }while(auxi_possuir!='s' && auxi_possuir!='n');
    if(auxi_possuir=='s')
        return true;
    else
        return false;
}

float Tempo_Animacao(void){
    float auxi_tempo;
    Borda_Janela(53, 15, 15, 17);
    do{//Determinando o tempo da animação;
        gotoxy(15,16); printf("%c Velocidade da animacao  a qual deseja [em ms]:     %c", 179, 179);
        gotoxy(64,16); scanf("%f", &auxi_tempo);
    }while(auxi_tempo<=0);
    return auxi_tempo;
}

void Imprimir_Layout(bool modo_desafio){
    gotoxy(26,1); printf("+----Torre de Hanoi----+");
    Imprimir_Pilares();//Chamando funções que imprime os pilares;
    if(modo_desafio){//Como o modo desafio não permite acessar o menu não e necessario imprimir esta mensagem;
        gotoxy(1,22); printf("%c                       %c", 218,191 );
        gotoxy(1,23); printf("  Acessar menu digite    ");
        gotoxy(1,24); printf("  [M/m] nas coordenadas  ");
        gotoxy(1,25); printf("%c                       %c", 192, 217);

        /*
        gotoxy(i, 18); printf("%c", 218-j-n);
        gotoxy(i, 20); printf("%c", 192+j-n);*/
    }
    gotoxy(3,18); printf("Mov.: %d   ", contador_movimentos);//Imprimindo quantidade de movimentos realizados;
    gotoxy(5,25);
}

void Imprimir_Pilares(void){
    int i, j, n;

    for(i=7; i<=14; i++)
        for(j=20; j<55; j=j+17){//Imprimindo pilares;
            gotoxy(j,i); printf("%c %c", 179, 179);
        }
    for(i=10; i<63; i++)
        if(i==10){//Imprimindo base dos pilares;
            gotoxy(12, 15); printf("%c", 218);
            gotoxy(12, 16); printf("%c", 192);
            gotoxy(65, 15); printf("%c", 191);
            gotoxy(65, 16); printf("%c", 217);
        }else{
            gotoxy(2+i, 15); printf("%c", 196);
            gotoxy(2+i, 16); printf("%c", 196);
        }
    Imprimir_Topo_Pilares();
    n=j=0;
    for (i=33; i<44; i=i+10){//Imprimindo caixa das coordenadas;
        gotoxy(i, 18); printf("%c", 218-j-n);
        gotoxy(i, 20); printf("%c", 192+j-n);
        j=26;
        n=1;
    }
    gotoxy(33,19); printf("     %c     ", 26);
}

void Imprimir_Topo_Pilares(void){
    int i, j=65;
    for(i=20; i<55; i=i+17){
        gotoxy(i,5);   printf("%c%c%c", 218, 196, 191);
        gotoxy(i,6);   printf("%c%c%c", 179, j, 179);
        gotoxy(i, 15); printf("%c %c", 217, 192);
        j++;
    }
}

void Imprimir_Todos_Discos(void){
    int coluna;
    int linha;
    for(linha=0; linha<8; linha++)
        for(coluna=0; coluna<3; coluna++)
            if(torre[linha][coluna]!=8)//Identificando disco que sera impresso;
                Posicionar_Disco(coluna, torre[linha][coluna], linha);//Posicionando e imprimindo disco;
}

void Posicionar_Disco(int pilar, int n_disco, int linha){
    int tam_disco = (2*n_disco) + 3;//Calculo para o tamanho do disco em caracteres;
    int canvas=19;//Espaço em brando entre os pilares;
    int num_char_branco = (canvas-tam_disco);//Espaço em branco com o disco desenhado;
    int inicio_impressao = num_char_branco/2;//Posicionando o disco no meio;

    switch(pilar){//Dependendo do pilar em que o disco esta, ele será impresso em uma coordenada diferente;
    case 0:
        inicio_impressao+=12;
        break;
    case 1:
        inicio_impressao+=29;
        break;
    case 2:
        inicio_impressao+=46;
        break;
    }
    gotoxy(inicio_impressao, (linha+7)); Desenha_Disco(tam_disco);//Imprimindo o disco;
}

void Desenha_Disco(int tam_disco){
    int i, cor;
    cor = (tam_disco-3)/2;//Calculo para determinar uma cor;

    if(cor!=7)//A cor do disco tem que ser diferente de 7 pois esta é a cor do fundo;
        textcolor(cor);
    else
        textcolor(cor+3);
    printf("|");
    for (i=0; i<tam_disco-2; i++)//Imprimeindo diso;
        printf("%c", 219);
    printf("|");
    textcolor(1);//Voltando a imprimir ajul os caracteres;
    gotoxy(1,25);
}

void Realizar_Animacao_Mov(int orig, int dest, float tempo_ani){
    int i;
    int num_disco_mov;
    int linha_posicao_inicio, linha_posicao_termino;

    for(i=0; i<8; i++){//Determinando o disco que será posto em animação, sua posicão inicial e sua posicão final.
        if(torre[i][orig]!=8 && torre[i-1][orig]==8){
            num_disco_mov = torre[i][orig];
            linha_posicao_inicio = i;
        }
        if((torre[i][dest]!=8 && torre[i-1][dest]==8) || (i==7 && torre[i][dest]==8)){
            linha_posicao_termino = i;
        }
    }
    for(i=linha_posicao_inicio; i>=-3; i--){//Animação do disco subindo(vertical);
        Posicionar_Disco(orig, num_disco_mov, i);
        Sleep(tempo_ani);
        Apagar_Animacao_Vertical(orig, i-1);
        Imprimir_Topo_Pilares();
    }
    Animacao_Horizontal(num_disco_mov, orig, dest, tempo_ani);//Animação do disco horizontalmente;
    for(i=-3; i<linha_posicao_termino; i++){//Animação do disco descendo(vertical);
        Imprimir_Topo_Pilares();
        Posicionar_Disco(dest, num_disco_mov, i);
        Sleep(tempo_ani);
        Apagar_Animacao_Vertical(dest, i-1);
    }
}

void Apagar_Animacao_Vertical(int pilar, int linha){
        if(pilar==0)//Determinando em qual posiçao será apragado o rastro do disco, de acordo com o pilar que se encontra;
            gotoxy(13, linha+8);
        else if(pilar==1)
            gotoxy(30, linha+8);
        else
            gotoxy(47, linha+8);

        printf("       %c %c       ",179, 179);
        gotoxy(20,4); printf("\t \t \t \t \t");
}

void Animacao_Horizontal(int num_disco_mov, int orig, int dest, float tempo_ani){
    int tam_disco = (2*num_disco_mov) + 3;
    int num_char_branco = (23-tam_disco);
    int inicio_impressao = num_char_branco/2;

    if(orig==0)//Determinando em qual posiçao o disco esta, de acordo com o pilar que se encontra;
        inicio_impressao+=11;
    else if(orig==1)
        inicio_impressao+=27;
    else
        inicio_impressao+=44;

    if((orig==0 && dest==1) || (orig==1 && dest==2)){//Animação horizontal pilar A-B ou B-C;
        Auxiliar_Animacao_Horizontal(tam_disco, inicio_impressao, 17, tempo_ani);
    }else if((orig==2 && dest==1) || (orig==1 && dest==0)){//Animação horizontal pilar B-A ou C-B;
        Auxiliar_Animacao_Horizontal(tam_disco, inicio_impressao, -17, tempo_ani);
    }else if(orig==0 && dest==2){//Animação horizontal pilar A-C;
        Auxiliar_Animacao_Horizontal(tam_disco, inicio_impressao, 34, tempo_ani);
    }else{//Animação horizontal pilar C-A;
        Auxiliar_Animacao_Horizontal(tam_disco, inicio_impressao, -35, tempo_ani);
    }
}

void Auxiliar_Animacao_Horizontal(int tam_disco, int inicio_impressao, int parada, float tempo_ani){
    int i;
    if(parada==17 || parada==34){
        for(i=inicio_impressao; i<inicio_impressao+parada; i++){//Animação horizontal sentido positivo;
            Apagar_Animacao_Horizontal(tam_disco, i);
            Sleep(tempo_ani);
        }
    }else
        for(i=inicio_impressao; i>inicio_impressao+parada; i--){//Animação horizontal sentido negativo;
            Apagar_Animacao_Horizontal(tam_disco, i);
            Sleep(tempo_ani);
        }
}

void Apagar_Animacao_Horizontal(int tam_disco, int i){
    gotoxy(i-5,4); printf("                       ");
    gotoxy(i,4);   Desenha_Disco(tam_disco);
    gotoxy(23,19);
}

void Guardar_Movimento_Hist(int orig, int dest){
    FILE *historico;
    historico = fopen("Arquivos\\Historicos\\Historico_mov.txt","a");
    fprintf( historico ,"%c - %c\n", orig+65, dest+65);
    fclose(historico);
}

void Le_Nome(void){
    char nome_aux[100];
    do{
        gotoxy(18,17); printf("Nome:              [MAX: 10 caracteres]\t\t");
        gotoxy(24,17); scanf("%s", nome_aux);
    }while(strlen(nome_aux)>10);
    strcpy(nome_jogador, nome_aux);
}

bool Verifica_Ganhar(void){
    int i, j;
    for(j=0; j<2; j++){//Verificando se o jogador venceu de acordo com as colunas A e B ou 0 e 1 da matriz;
        for(i=0; i<8; i++){
            if(torre[i][j]!=8){//Verificando se elas estão vazias;
                return true;
            }
        }
    }
    return false;
}

bool Verificar_Nome_Arquivo(void){
    char nome_arquivo[40];
    FILE *compara_existencia;
    //Verificando se o arquivo com o nome do jogador soicitado ja existe;
    strcpy(nome_arquivo, "Arquivos\\");
    strcat(nome_arquivo, "Historicos\\");
    strcat(nome_arquivo, nome_jogador);
    strcat(nome_arquivo, ".txt");

    compara_existencia = fopen(nome_arquivo, "r");
    if(compara_existencia==NULL){
        fclose(compara_existencia);
        return false;
    }else{
        fclose(compara_existencia);
        return true;
    }
}

void Salvar_Historico(char *salvar_hist){
    char nome_arquivo[40];

    Borda_Janela(50, 13, 11, 14);
    do{
        gotoxy(13,12); printf("%c   Deseja salvar o historico de movimentos?[S/N] %c", 179, 179);
        gotoxy(13,13); printf("%cR:                                               %c", 179, 179);
        gotoxy(18,13); scanf("%c", &*salvar_hist);
        *salvar_hist = tolower(*salvar_hist);
    }while(*salvar_hist!='s' && *salvar_hist!='n');//Verificando se o jogador deseja salvar historico;

    if(*salvar_hist=='s'){
        do{
            Le_Nome();
            if(Verificar_Nome_Arquivo()){//Verificando se o nome esta disponivel;
                gotoxy(5,20); printf("Nome nao disponivel!");
            }else{
                gotoxy(5,20); printf("                    ");
            }
        }while(Verificar_Nome_Arquivo());

        strcpy(nome_arquivo, "Arquivos\\");
        strcat(nome_arquivo, "Historicos\\");
        strcat(nome_arquivo, nome_jogador);
        strcat(nome_arquivo, ".txt");

        rename("Arquivos\\Historicos\\Historico_mov.txt", nome_arquivo);//Renomeando arquivo com o nome do jogador;
    }else{
        DeleteFile("Arquivos\\Historicos\\Historico_mov.txt");//Caso o jogador não queira salvar o historico de movimentos o jogo é reiniciado.
    }
    return;
}

void Salvar_Ranking(int tempo_jogo, char salvar_hist){
    long int i = 0;
	long int penultimo_byte;
	char salvar_rank;
    dados_jogador jogador;
    dados_jogador auxiliar[2];
    FILE * arquivo_ranking;

    Borda_Janela(50, 13, 11, 14);
    do{
        gotoxy(13,12); printf("%c       Deseja participar do ranking?[S/N]        %c", 179, 179);
        gotoxy(13,13); printf("%cR:                                               %c", 179, 179);
        gotoxy(18,13); scanf("%c", &salvar_rank);
        salvar_rank = tolower(salvar_rank);
    }while(salvar_rank!='s' && salvar_rank!='n');//Verificando se o jogador deseja salvar no ranking seu desempenho;

    if(salvar_rank=='s'){
        if(salvar_hist=='n')//Caso não tenha sido salvo o historico ainda não foi lido o nome do jogador, e como nesta situação jogador deseja salvar no ranking é necessario ler seu nome;
            Le_Nome();
        jogador.pontuacao = (pow(5, qtd_discos)/(contador_movimentos + tempo_jogo))*10;
        strcpy(jogador.nome, nome_jogador);//Atribuindo nome lido;
        jogador.tempo = tempo_jogo;//Atribuindo tempo de jogo;
        jogador.qtd_mov  = contador_movimentos;//Atribuindo quantidade de movimentos realizados;
        jogador.discos = qtd_discos;//Atribuindo quantidade de discos;
        if(salvar_hist=='s')
            strcpy(jogador.salvou_hist, "Sim");//Atribuindo a verificação se o jogador dalvou o historico de movimentos;
        else
            strcpy(jogador.salvou_hist, "Nao");

        arquivo_ranking = fopen("Arquivos\\Ranking.dat", "ab");//Atribuindo nome lido;
        fwrite(&jogador, sizeof(dados_jogador), 1,arquivo_ranking);
        penultimo_byte = ftell(arquivo_ranking) - sizeof(dados_jogador);
        freopen("Arquivos\\Ranking.dat", "r+b", arquivo_ranking);

        if(arquivo_ranking == NULL){
            printf("Ranking.bat inexistente.\n");
            getch();
        }else{//Inserindo informações do jogador na posicão do arquivo ordenado;
            for(i = 0; i<penultimo_byte; i=i+sizeof(dados_jogador)){
                fseek(arquivo_ranking, sizeof(dados_jogador)*(-1) , SEEK_END);//Posicionando cursor na "penultima posição";
                fread(&auxiliar[0], sizeof(dados_jogador), 1, arquivo_ranking);//Atribuindo a um auxiliar;
                fseek(arquivo_ranking, i, SEEK_SET);//;
                fread(&auxiliar[1], sizeof(dados_jogador), 1, arquivo_ranking);//Atribuindo outro auxiliar;
                if(auxiliar[1].pontuacao < auxiliar[0].pontuacao){//Ordenando de acordo com a pontuação direto no arquivo através da comparação dos valores atribuidos aos auxiliares;
                    fseek(arquivo_ranking, i, SEEK_SET);
                    fwrite(&auxiliar[0], sizeof(dados_jogador), 1, arquivo_ranking);
                    fseek(arquivo_ranking, sizeof(dados_jogador)*(-1), SEEK_END);
                    fwrite(&auxiliar[1], sizeof(dados_jogador), 1, arquivo_ranking);
                }
            }
        }
        fclose(arquivo_ranking);
    }
}

void Mensagem_Fim_de_Jogo(int tempo_jogo){
    system("cls");
    textcolor(4);
    Borda_Janela(26, 25, 4, 10);
    gotoxy(25,5); printf("%c       Fim de Jogo       %c", 179, 179);
    gotoxy(25,6); printf("%c                         %c", 179, 179);
    gotoxy(25,7); printf("%c  Tempo de Jogo:         %c", 179, 179);
    gotoxy(25,8); printf("%c                         %c", 179, 179);
    gotoxy(25,9); printf("%c       Movimentos:       %c", 179, 179);
    gotoxy(43,7);
    if(tempo_jogo!=-1)
        printf("%d seg.", tempo_jogo);
    else
        printf("NULL");
    gotoxy(45,9); printf("%d", contador_movimentos);
    textcolor(1);
}

void Fim_de_Jogo(int tempo_jogo, bool perguntar_nova_partida, bool modo_treinamento){
    char salvar_hist;
    if(perguntar_nova_partida){//Se ja foi perguntado se desejaria iniciar uma nova partida onde "perguntar_nova_partida==false", logo o jogo terminará  direto;
        Mensagem_Fim_de_Jogo(tempo_jogo);//Exibindo mensagem de fim de jogo.
        if(!modo_treinamento){//No modo treinamento não é possivel salvar o historico de movimentos e entrar no ranking;
            Salvar_Historico(&salvar_hist);//Mesmo que o jogador perca é possivel salvar o historico, entretanto não entrará no tanking;
            if(!Verifica_Ganhar()){//É necessario verificar se o jogador ganhou pois é possivel entrar nesta função caso o jogador perca no modo desafio.
                Salvar_Ranking(tempo_jogo, salvar_hist);
            }
        }
        Perguntar_Iniciar_Nova_Partida(tempo_jogo);
    }else{
        Mensagem_Fim_de_Jogo(tempo_jogo);//Exibindo mensagem de fim de jogo.
        gotoxy(1,25); system("pause");
        exit(0);
    }
}

void Iniciar_Matriz(void){
    int i, j;
    int auxi_qtd= qtd_discos;

    for(i=0; i<8; i++)//Iniciando todo vetor com o numero 8;
        for(j=0; j<3; j++)
            torre[i][j] = 8;
    for(i=7; i>-1; i--)
        if(auxi_qtd!=0){//Iniciando 1ª coluna do vetor com o numero de discos solicitado sendo decrementado de baixo para cima;
            torre[i][0] = auxi_qtd;
            auxi_qtd-=1;
        }
}

void Escolha_Movimento(int *orig, int *dest, bool modo_desafio, clock_t tempo_inicial, int tempo_desafio){
    *orig = 1;
    do{
        Le_Coordenada(&*orig, 35, modo_desafio, tempo_inicial, tempo_desafio);
        if(*orig!=12){//Somente é lido a outra coordenada se não for solicitado acesso ao menu;
            do{
                Le_Coordenada(&*dest, 41, modo_desafio, tempo_inicial, tempo_desafio);
            }while(*dest==*orig);
        }else{
            *dest = 12;//Se for solicitado acesso ao menu, o dest é iniciado com o valor de acess ao menu também, pois se no primeiro movimento for solicitado acesso ao menu a variavel dest conterá apenas lixo;
        }
        if(Comparar_orig_dest(&*orig, &*dest) && *orig!=12 && *dest!=12){
            gotoxy(30,22); printf("Movimento invalido!");
            gotoxy(35,19); printf(" ");
            gotoxy(41,19); printf(" ");
        }else{//Iniciando todo vetor com o numero 8;
            gotoxy(30,22); printf("                   ");
        }
    }while(Comparar_orig_dest(&*orig, &*dest) && *orig!=12 && *dest!=12);
    if(*orig!=12 && *dest!=12)
        contador_movimentos+=1;

}

void Le_Coordenada(int *coordenada, int posicao, bool modo_desafio, clock_t tempo_inicial, int tempo_desafio){
    char auxi;

    gotoxy(41,19); printf(" ");
    do{
        gotoxy(posicao,19); auxi = getche();//Capturando caractere solicitado;
        auxi = tolower(auxi);
        *coordenada = auxi-97;//Convertendo para numeros que poderão ser usados na matriz principal de inteiros;

        if(modo_desafio){//Somente no modo desafio será verificado o tempo para termino do jogo;
            Verificar_Tempo_Desafio(tempo_inicial, tempo_desafio);
            if(auxi=='m'){//Como não é permitido acessar o menu no modo desafio é atribuido uma coordenada invalida;
                *coordenada = -1;
            }
        }else{
            if(auxi=='m')//Acessando menu;
                *coordenada = 12;
        }
        if(*coordenada<0 || (*coordenada>2 && *coordenada!=12)){
            gotoxy(30,22);      printf("Coordenada invalida!");
            gotoxy(posicao,19); printf(" ");
        }else{
            gotoxy(30,22); printf("                    ");
        }
    }while(*coordenada<0 || (*coordenada>2 && *coordenada!=12));
}

bool Comparar_orig_dest(int *orig, int *dest){
    int i;
    int destino, origem;

    for(i=0; i<8; i++){//Atribuindo o numero do disco na origem variavel origem;
        if(torre[i][*orig]!=8 && torre[(i-1)][*orig]==8)
            origem = torre[i][*orig];

        if((torre[i][*dest]!=8 && torre[(i-1)][*dest]==8) || (i==7 && torre[i][*dest]==8))
            destino = torre[i][*dest];//Atribuindo o numero do disco na destino variavel destino;
    }
    if(origem>destino)//Comparando o numero armazenado nas variaveis;
        return true;
    else
        return false;
}

void Move_Disco(int orig, int dest){
    int i;
    int auxiliar_troca=0;

    for(i=0; i<8; i++)
        if(torre[i][orig]!=8 && torre[i-1][orig]==8 && auxiliar_troca==0){
            auxiliar_troca = torre[i][orig];//Atribuindo o numero do disco que será movimentado a variavel auxiliar_troca;
            torre[i][orig] = 8;//"Apagando" esta variavel da matriz;
        }
    for(i=0; i<8; i++)
        if((torre[i][dest]!=8 && torre[i-1][dest]==8) || (i==7 && torre[i][dest]==8)){
            if(i==7 && torre[i][dest]==8){//Atribuindo o numero armazenado na torre destino;
                torre[i][dest] = auxiliar_troca;
            }else{
                torre[i-1][dest] = auxiliar_troca;
            }
        }
}

void Refreshing_Cores(void){
    textbackground(15);
    textcolor(1);
}

void Opcao_Numerica(int *opcao, int lim_inf, int lim_sup, int local_leitura, int local_erro){
    do{
       fflush(stdin);
       gotoxy(local_leitura,5); scanf("%d",&*opcao);
       if(*opcao<lim_inf || *opcao>lim_sup){
            gotoxy(27,local_erro); printf("Opcao Invalida.");
       }
        gotoxy(local_leitura,5); printf("\t\t\t\t");
    }while(*opcao<lim_inf || *opcao>lim_sup);
}

void Refreshing_Tela(bool modo_desafio){
    system("cls");
    Imprimir_Layout(modo_desafio);
    Imprimir_Todos_Discos();
}

void Borda_Janela(int i, int coluna_inicio, int linha_cima, int linha_baixo){
    int j;
    for (j=0;j<i ;j++){//Imprimindo borda superior e inferior;
        if(j==0){
            gotoxy(coluna_inicio,linha_cima);    printf("%c", 218);
            gotoxy(coluna_inicio+i,linha_cima);  printf("%c", 191);
            gotoxy(coluna_inicio,linha_baixo);   printf("%c", 192);
            gotoxy(coluna_inicio+i,linha_baixo); printf("%c", 217);
        }else{
            gotoxy(coluna_inicio+j,linha_cima);  printf("%c", 196);
            gotoxy(coluna_inicio+j,linha_baixo); printf("%c", 196);
        }
    }
}
