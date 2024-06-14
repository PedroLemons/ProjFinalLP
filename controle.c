#include <windows.h> //para coordenadas COORD e SetConsoleCursorPosition()
#include <stdio.h>
#include <conio.h>   // getch() e gotoxy(x, y)
#include <stdlib.h>
#include <string.h>  // strcpy()

int s;
char password[10] = {"tads"};
char categorias[][15] = {"Social", "Tenis", "Salto", "Sandalia", "Chinelo", "Botas"};  // manipulação de vetores

void returnfunc(void);
void menuPrincipal(void);
void adicionarProduto(void);
void deletarProduto(void);
void editarProduto(void);
void visualizarProduto(void);
int getdata();
int checkid(int);
void Password();

FILE *arqProd, *arqTemp;  // ponteiros para manipulação de arquivos

COORD coord = {0, 0};

void gotoxy(int x, int y) {
       coord.X = x;
       coord.Y = y; // coordenadas X e Y
       SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// tipo definito pelo usuário
struct produtos {               
       int id;
       char modelo[20];
       char marca[20];
       int quantidade;
       float preco;
       int prateleira;
       char *cat;
};

struct produtos prod;

int main() {
       Password();
       getche();
       return 0;
}

void menuPrincipal() {
       system("cls");

       int i;
       gotoxy(20, 3);
       printf(":::::::::::::::::::::: SISTEMA DE GERENCIAMENTO DE ESTOQUE ::::::::::::::::::::::");
       gotoxy(20, 5);
       printf(":::::::::::: 1=> Adicionar Produto");
       gotoxy(20, 7);
       printf(":::::::::::: 2=> Deletar Produto");
       gotoxy(20, 9);
       printf(":::::::::::: 3=> Visualizar Produto");
       gotoxy(20, 11);
       printf(":::::::::::: 4=> Editar Produto");
       gotoxy(20, 13);
       printf(":::::::::::: 5=> Encerrar");

       gotoxy(20, 17);
       printf("Digite a opcao desejada:");
       switch (getch()) {                                            // switch-case
       case '1':
              adicionarProduto();
              break;
       case '2':
              deletarProduto();
              break;
       case '3':
              visualizarProduto();
              break;
       case '4':
              editarProduto();
              break;
       case '5':
       {
              system("cls");
              gotoxy(16, 3);
              printf("\tSistema de Gerenciamento de Estoque");
              gotoxy(16, 5);
              printf("\tProjeto final da disciplina de Linguagem de Programacao");
              gotoxy(16, 7);
              printf("\tFeito por");
              gotoxy(16, 9);
              printf("\tPedro A. Lemos");
              gotoxy(16, 11);
              printf(":::::::::::::::::::::::::\n\n\n");

              exit(0);
       }
       default:
       {
              gotoxy(10, 23);
              printf("\aOpcao nao encontrada!!Digite novamente:");
              if (getch())
                     menuPrincipal();
       }
       }

}

void adicionarProduto(void) { 
       system("cls");
       int i;
       gotoxy(20, 3);
       printf("::::::::::::::::::::::::::: SELECIONA A CATEGORIA :::::::::::::::::::::::::::");
       gotoxy(20, 5);
       printf(":::::::::::: 1=> Social");
       gotoxy(20, 7);
       printf(":::::::::::: 2=> Tenis");
       gotoxy(20, 9);
       printf(":::::::::::: 3=> Salto");
       gotoxy(20, 11);
       printf(":::::::::::: 4=> Sandalia");
       gotoxy(20, 13);
       printf(":::::::::::: 5=> Chinelo");
       gotoxy(20, 15);
       printf(":::::::::::: 6=> Botas");
       gotoxy(20, 17);
       printf(":::::::::::: 7=> Voltar ao menu principal");
       gotoxy(20, 21);
       printf("Qual a categoria do produto? ");
       scanf("%d", &s);
       if (s == 7)
              menuPrincipal();
       system("cls");

       arqProd = fopen("estoque.dat", "ab+");
       if (getdata() == 1) {
              prod.cat = categorias[s - 1];
              fseek(arqProd, 0, SEEK_END);
              fwrite(&prod, sizeof(prod), 1, arqProd);
              fclose(arqProd);
              gotoxy(21, 14);
              printf("Registro salvo com sucesso");
              gotoxy(21, 15);
              printf("Deseja registrar novos produtos?(S / N):");
              if (getch() == 'n')                                    // if-else
                     menuPrincipal();
              else
                     system("cls");
              adicionarProduto();
       }
}

void deletarProduto() { 
       system("cls");
       int d;
       char existe;
       char inicio = 's';
       while (inicio == 's') {
              system("cls");
              gotoxy(10, 5);
              printf("Digite o ID do produto que deseja deletar:");
              scanf("%d", &d);

              arqProd = fopen("estoque.dat", "rb+");
              rewind(arqProd);
              while (fread(&prod, sizeof(prod), 1, arqProd) == 1) { // Enquanto a leitura de um registro do arquivo arqProd for bem-sucedida
                     if (prod.id == d) {
                            gotoxy(10, 7);
                            printf("Registro existente");
                            gotoxy(10, 8);
                            printf("Modelo do produto: %s", prod.modelo);
                            gotoxy(10, 9);
                            printf("Prateleira No.: %d", prod.prateleira);
                            existe = 't';
                     }
              }
              if (existe != 't') {
                     gotoxy(10, 10);
                     printf("Nenhum registro encontrado");
                     fclose(arqProd);
                     if (getch())
                            menuPrincipal();
              }
              if (existe == 't') {
                     gotoxy(10, 9);
                     printf("Tem certeza que deseja deletar este produto? (S / N):");
                     if (getch() == 's') {
                            arqTemp = fopen("test.dat", "wb+");                            // arquivos temporarios que nao serao deletados
                            rewind(arqProd);
                            while (fread(&prod, sizeof(prod), 1, arqProd) == 1) {
                                   if (prod.id != d) {
                                          fwrite(&prod, sizeof(prod), 1, arqTemp);         // escrever tudo em arquivo temporario exceto aqueles
                                   }                                                       // que queremos deletar
                            }
                            fclose(arqTemp);
                            fclose(arqProd);
                            remove("estoque.dat");
                            rename("test.dat", "estoque.dat");
                                                                                           
                                   gotoxy(10, 11);
                                   printf("Registro apagado com sucesso");
                                   gotoxy(10, 13);
                                   printf("Deletar outro registro? (S / N)");
                     }
                     else {
                            fclose(arqProd);
                            menuPrincipal();
                     }
                     fflush(stdin);
                     inicio = getch();
              }
       }
       gotoxy(10, 15);
       menuPrincipal();
}

void visualizarProduto(void) { 
       int j;
       system("cls");
       gotoxy(1, 1);
       printf("::::::::::::::::::::::::::Lista de Produtos:::::::::::::::::::::::::::");
       gotoxy(2, 2);
       printf(" CATEGORIA    ID      MODELO      MARCA       QTD     PRECO     PRATELEIRA ");
       j = 4;
       arqProd = fopen("estoque.dat", "rb");
       while (fread(&prod, sizeof(prod), 1, arqProd) == 1)
       {
              gotoxy(3, j);
              printf("%s", prod.cat);
              gotoxy(16, j);
              printf("%d", prod.id);
              gotoxy(22, j);
              printf("%s", prod.modelo);
              gotoxy(36, j);
              printf("%s", prod.marca);
              gotoxy(50, j);
              printf("%d", prod.quantidade);
              gotoxy(57, j);
              printf("%.2f", prod.preco);
              gotoxy(69, j);
              printf("%d", prod.prateleira);
              printf("\n\n");
              j++;
       }
       fclose(arqProd);
       gotoxy(35, 25);
       returnfunc();
}

void editarProduto(void) { 
       system("cls");
       int c = 0;
       int d;
       gotoxy(20, 4);
       printf("****Edicao de produtos****");
       char inicio = 's';
       while (inicio == 's') {
              system("cls");
              gotoxy(15, 6);
              printf("Digite o ID do produto a ser editado:");
              scanf("%d", &d);
              arqProd = fopen("estoque.dat", "rb+");
              while (fread(&prod, sizeof(prod), 1, arqProd) == 1) {
                     if (checkid(d) == 0) {
                            gotoxy(15, 7);
                            printf("Produto disponivel");
                            gotoxy(15, 8);
                            printf("ID do produto:%d", prod.id);
                            gotoxy(15, 9);
                            printf("Digite novo modelo:");
                            scanf("%s", prod.modelo);
                            gotoxy(15, 10);
                            printf("Digite a nova Marca:");
                            scanf("%s", prod.marca);
                            gotoxy(15, 11);
                            printf("Digite nova quantidade:");
                            scanf("%d", &prod.quantidade);
                            gotoxy(15, 12);
                            printf("Digite novo preco:");
                            scanf("%f", &prod.preco);
                            gotoxy(15, 13);
                            printf("Digite nova prateleira:");
                            scanf("%d", &prod.prateleira);
                            gotoxy(15, 14);
                            printf("Registro modificado com sucesso");
                            fseek(arqProd, ftell(arqProd) - sizeof(prod), 0); // Move o ponteiro de posição do arquivo arqProd para a posição atual menos o tamanho de um registro 'prod'
                            fwrite(&prod, sizeof(prod), 1, arqProd); // Escreve o conteúdo do registro 'prod' no arquivo arqProd
                            fclose(arqProd);
                            c = 1;
                     }
                     if (c == 0) {
                            gotoxy(15, 9);
                            printf("Sem registros");
                     }
              }
              gotoxy(15, 16);
              printf("Editar outro registro? (S / N)");
              fflush(stdin);
              inicio = getch();
              gotoxy(15, 18);
       }
       returnfunc();
}

void returnfunc(void) {
       {
              printf(" Aperte a tecla ENTER para voltar ao menu principal");
       }
a:
       if (getch() == 13) // permite apenas a tecla ENTER
              menuPrincipal();
       else
              goto a;
}

int getdata() {
       int t;
       gotoxy(20, 3);
       printf("Digite as informacoes abaixo");

       gotoxy(21, 5);
       printf("Categoria:");
       gotoxy(31, 5);
       printf("%s", categorias[s - 1]);

       gotoxy(21, 6);
       printf("ID produto:\t");
       gotoxy(32, 6);
       scanf("%d", &t);
       if (checkid(t) == 0) {
              gotoxy(21, 13);
              printf("\aO ID deste produto ja existe\a");
              getch();
              menuPrincipal();
              return 0;
       }
       prod.id = t;

       gotoxy(21, 7);
       printf("Modelo:");
       gotoxy(29, 7);
       scanf("%s", prod.modelo);

       gotoxy(21, 8);
       printf("Marca:");
       gotoxy(27, 8);
       scanf("%s", prod.marca);

       gotoxy(21, 9);
       printf("Quantidade:");
       gotoxy(32, 9);
       scanf("%d", &prod.quantidade);

       gotoxy(21, 10);
       printf("Preco:");
       gotoxy(27, 10);
       scanf("%f", &prod.preco);

       gotoxy(21, 11);
       printf("Prateleira No:");
       gotoxy(36, 11);
       scanf("%d", &prod.prateleira);
       return 1;
}

int checkid(int t) {                // checa se ja existe um produto com este ID            // algoritmo de busca
       rewind(arqProd);
       while (fread(&prod, sizeof(prod), 1, arqProd) == 1) // lê cada registro de produto
              if (prod.id == t)     // compara o ID do produto com o ID fornecido
                     return 0;      // retorna 0 se o produto exitir
       return 1;                    // retorna 1 se não existir
}

void Password(void) {
       system("cls");
       char d[25] = "Digite sua senha";
       char ch, senha[10];
       int i = 0, j;

       gotoxy(10, 4);
       for (j = 0; j < 20; j++) {
              printf(":");
       }
       for (j = 0; j < 20; j++) {
              printf("%c", d[j]);
       }
       for (j = 0; j < 20; j++) {
              printf(":");
       }

       gotoxy(15, 7);
       printf("Digite sua senha:");

       while (ch != 13) {                                                     // loop
              ch = getche();
              // ch = getch();             // esconder a senha
              if (ch != 13 && ch != 8) {
                     // putch('*');        // esconder a senha
                     senha[i] = ch;
                     i++;
              }
       }
       senha[i] = '\0';                                          // caracter nulo para marcar o fim da string

       if (strcmp(senha, password) == 0) {                       // compara a senha digitada (senha) com a senha definida (password)
              gotoxy(15, 9);
              printf("Login realizado com sucesso!");
              gotoxy(17, 10);
              printf("\nPressione uma tecla para continuar...");
              getch();
              menuPrincipal();
       }
       else {
              gotoxy(15, 16);
              printf("\aSenha Incorreta!!!");
              getch();
              Password();
       }
}