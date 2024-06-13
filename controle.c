#include <windows.h> //para coordenadas
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

char categorias[][15] = {"Social", "Tenis", "Salto", "Sandalia", "Chinelo", "Botas"}; // manipulação de vetores
void returnfunc(void);
void menuPrincipal(void);
void adicionarProduto(void);
void deletarProduto(void);
void editarProduto(void);
void visualizarProduto(void);
int getdata();
int checkid(int);
void Password();

FILE *fp, *ft;                                                       // ponteiros

COORD coord = {0, 0};

int s;
char password[10] = {"tads"};

void gotoxy(int x, int y) {
       coord.X = x;
       coord.Y = y; // coordenadas X e Y
       SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct produtos {                                                    // tipo definito pelo usuário
       int id;
       char modelo[20];
       char marca[20];
       int quantidade;
       float preco;
       int prateleira;
       char *cat;
};

struct produtos a;

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
void adicionarProduto(void) { // Funcao para adicionar produtos
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

       fp = fopen("lib.dat", "ab+");
       if (getdata() == 1) {
              a.cat = categorias[s - 1];
              fseek(fp, 0, SEEK_END);
              fwrite(&a, sizeof(a), 1, fp);
              fclose(fp);
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

void deletarProduto() { // funcao para deletar itens
       system("cls");
       int d;
       char existe;
       char inicio = 's';
       while (inicio == 's') {
              system("cls");
              gotoxy(10, 5);
              printf("Digite o ID do produto que deseja deletar:");
              scanf("%d", &d);

              fp = fopen("lib.dat", "rb+");
              rewind(fp);
              while (fread(&a, sizeof(a), 1, fp) == 1) {
                     if (a.id == d) {
                            gotoxy(10, 7);
                            printf("Registro existente");
                            gotoxy(10, 8);
                            printf("Modelo do produto: %s", a.modelo);
                            gotoxy(10, 9);
                            printf("Prateleira No.: %d", a.prateleira);
                            existe = 't';
                     }
              }
              if (existe != 't') {
                     gotoxy(10, 10);
                     printf("Nenhum registro encontrado");
                     fclose(fp);
                     if (getch())
                            menuPrincipal();
              }
              if (existe == 't') {
                     gotoxy(10, 9);
                     printf("Tem certeza que deseja deletar este produto? (S / N):");
                     if (getch() == 's') {
                            ft = fopen("test.dat", "wb+"); // arquivos temporarios que nao serao deletados
                            rewind(fp);
                            while (fread(&a, sizeof(a), 1, fp) == 1) {
                                   if (a.id != d) {
                                          fwrite(&a, sizeof(a), 1, ft); // escrever tudo em arquivo temporario exceto aqueles
                                   }                                    // que queremos deletar
                            }
                            fclose(ft);
                            fclose(fp);
                            remove("lib.dat");
                            rename("test.dat", "lib.dat");     // copiar todos os arquivos temporarios para fp exceto aqueles
                                                               // que queremos deletar
                                   gotoxy(10, 11);
                                   printf("Registro apagado com sucesso");
                                   gotoxy(10, 13);
                                   printf("Deletar outro registro? (S / N)");
                     }
                     else {
                            fclose(fp);
                            menuPrincipal();
                     }
                     fflush(stdin);
                     inicio = getch();
              }
       }
       gotoxy(10, 15);
       menuPrincipal();
}

void visualizarProduto(void) { // mostra a lista de produtos registrados
       int i = 0, j;
       system("cls");
       gotoxy(1, 1);
       printf("::::::::::::::::::::::::::Lista de Produtos:::::::::::::::::::::::::::");
       gotoxy(2, 2);
       printf(" CATEGORIA     ID      MODELO      MARCA       QTD     PRECO     PRATELEIRA ");
       j = 4;
       fp = fopen("lib.dat", "rb");
       while (fread(&a, sizeof(a), 1, fp) == 1)
       {
              gotoxy(3, j);
              printf("%s", a.cat);
              gotoxy(16, j);
              printf("%d", a.id);
              gotoxy(22, j);
              printf("%s", a.modelo);
              gotoxy(36, j);
              printf("%s", a.marca);
              gotoxy(50, j);
              printf("%d", a.quantidade);
              gotoxy(57, j);
              printf("%.2f", a.preco);
              gotoxy(69, j);
              printf("%d", a.prateleira);
              printf("\n\n");
              j++;
              i = i + a.quantidade;
       }
       fclose(fp);
       gotoxy(35, 25);
       returnfunc();
}
void editarProduto(void) { // editar informacoes sobre produtos
       system("cls");
       int c = 0;
       int d, e;
       gotoxy(20, 4);
       printf("****Edicao de produtos****");
       char inicio = 's';
       while (inicio == 's') {
              system("cls");
              gotoxy(15, 6);
              printf("Digite o ID do produto a ser editado:");
              scanf("%d", &d);
              fp = fopen("lib.dat", "rb+");
              while (fread(&a, sizeof(a), 1, fp) == 1) {
                     if (checkid(d) == 0) {
                            gotoxy(15, 7);
                            printf("Produto disponivel");
                            gotoxy(15, 8);
                            printf("ID do produto:%d", a.id);
                            gotoxy(15, 9);
                            printf("Digite novo modelo:");
                            scanf("%s", a.modelo);
                            gotoxy(15, 10);
                            printf("Digite a nova Marca:");
                            scanf("%s", a.marca);
                            gotoxy(15, 11);
                            printf("Digite nova quantidade:");
                            scanf("%d", &a.quantidade);
                            gotoxy(15, 12);
                            printf("Digite novo preco:");
                            scanf("%f", &a.preco);
                            gotoxy(15, 13);
                            printf("Digite nova prateleira:");
                            scanf("%d", &a.prateleira);
                            gotoxy(15, 14);
                            printf("Registro modificado com sucesso");
                            fseek(fp, ftell(fp) - sizeof(a), 0);
                            fwrite(&a, sizeof(a), 1, fp);
                            fclose(fp);
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
       a.id = t;

       gotoxy(21, 7);
       printf("Modelo:");
       gotoxy(29, 7);
       scanf("%s", a.modelo);

       gotoxy(21, 8);
       printf("Marca:");
       gotoxy(27, 8);
       scanf("%s", a.marca);

       gotoxy(21, 9);
       printf("Quantidade:");
       gotoxy(32, 9);
       scanf("%d", &a.quantidade);

       gotoxy(21, 10);
       printf("Preco:");
       gotoxy(27, 10);
       scanf("%f", &a.preco);

       gotoxy(21, 11);
       printf("Prateleira No:");
       gotoxy(36, 11);
       scanf("%d", &a.prateleira);
       return 1;
}
int checkid(int t) {            // checa se ja existe um produto com este ID   // algoritmo de busca
       rewind(fp);
       while (fread(&a, sizeof(a), 1, fp) == 1)
              if (a.id == t)
                     return 0; // retorna 0 se o produto exitir
       return 1;               // retorna 1 se não existir
}

void Password(void) {
       system("cls");
       char d[25] = "Digite sua senha";
       char ch, pass[10];
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

       while (ch != 13) {                                            // loop
              ch = getche();
              // ch = getch(); // esconder a senha
              if (ch != 13 && ch != 8) {
                     // putch('*'); // esconder a senha
                     pass[i] = ch;
                     i++;
              }
       }
       pass[i] = '\0';
       if (strcmp(pass, password) == 0) {               // compara a senha digitada (pass) com a senha definida (password)
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