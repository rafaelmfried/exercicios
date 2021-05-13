#define TABLENUMBER 10     //NUMERO DE MESAS DA PIZZARIA
#define MAXITEMSPERBILL 10 //NUMERO MAXIMO DE PEDIDOS REGISTRADOS POR MESA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //Remover depois

typedef struct{
    float price;
    char *productName;
} item;

typedef struct{
    item *products;
    int count;
} table;

//Descricao das funcoes usadas.
void MenuRegister(item *targetProduct);

void MenuView(item *menu, int menuSize);

int SalesRegister(item menuProduct, table *tableTarget);

void TableView(table *loungeTarget, int tableCod);

int SalesCancel(table *tableTarget, int targetItem);

float MyBillIs(table tableTarget);

void ComandasView(void);

//Aplicacao
int main(int argc, char **argv){

    srand(time(NULL));
    // Leitura do menu e salvando no array menu.
    item *menu;
    int N; //Numero de items a serem cadastrados no menu
    scanf("%d%*c", &N);

    menu = (item *)malloc(N * sizeof(item));
    if (menu){
        for (int i = 0; i < N; i++){
            MenuRegister(menu + i);
        }
    }
    

    //Criacao da array lounge com 10 mesas e memoria de comanda maxima de 10 pedidos por mesa.
    table *lounge;
    lounge = (table *)malloc(TABLENUMBER * sizeof(table));
    for (int i = 0; i < TABLENUMBER; i++){
        lounge[i].products = (item *)malloc(MAXITEMSPERBILL * sizeof(item));
        lounge[i].count = 0;
    }
    
    int option=0;   

    do
    {        
        system("clear");
        printf("------------------BEM VINDO A PIZZARIA DE LAB I------------------\n");
        printf("PRINCIPAL\n\n");
        printf("1 - Consultar menu\n");
        printf("2 - Comandas\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        
        scanf("%d%*c", &option);
        
        switch (option){
            case 0:
                continue;
                break;
            case  1:
                MenuView(menu, N);
                break;
            case  2:
                ComandasView();
                break;
            case  3:
                return 0;
                break;
            default:
                printf("Digite uma opcao valida!");
                break;
        }
    }while(1);

    for(int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            int randomic = rand() % 5;
            SalesRegister(menu[randomic], (lounge + i));
        }
        TableView(lounge, i);
        printf("Valor da conta: R$ %.2f\n", MyBillIs(lounge[i]));
    }
    
    //Libera as variaveis alocadas
    for(int i=0; i<N; i++){ //Libera cada item do menu
        free(menu[i].productName);
    }   

    free(menu);

    for(int i=0; i<TABLENUMBER;i++){//Libera as mesas
        for(int j=0; i<MAXITEMSPERBILL; i++){//Libera os items das contas
            free(lounge[i].products[j].productName);
            free(lounge[i].products);
        }

        free(lounge);
    }

    return 0;
}

//Funcoes
void MenuRegister(item *targetProduct){
    targetProduct->productName = (char *)malloc(sizeof(char *));
    fgets(targetProduct->productName, 60, stdin);
    targetProduct->productName[strcspn(targetProduct->productName, "\n")] = '\0'; // Source: https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input/2693826#2693826
    scanf("%f%*c", &targetProduct->price);
}

void ProductList(item *menu, int menuSize){
    for (int i = 0; i < menuSize; i++)
        printf("COD= %d | %s -> R$ %.2f\n", i, menu[i].productName, menu[i].price);
}

void MenuView(item *menu, int menuSize){
    int menuViewOption;
    system("clear");
    printf("------------------BEM VINDO A PIZZARIA DE LAB I------------------\n");
    printf("MENU\n\n");

    ProductList(menu, menuSize);    
    printf("\n");
    printf("0 - Voltar para principal\n");
    
    printf("Opcao: ");

    do{
        scanf("%d%*c", &menuViewOption);
    }while(menuViewOption!=0);
}

int SalesRegister(item menuProduct, table *tableTarget){
    if (tableTarget->count < 10){
        tableTarget->products[tableTarget->count] = menuProduct;
        tableTarget->count++;
        return 1;
    }
    return 0;
}

void TableView(table *loungeTarget, int tableCod){
    system("clear");
    printf("------------------BEM VINDO A PIZZARIA DE LAB I------------------\n");
    printf("COMANDA MESA %d\n\n", tableCod);
    for (int i = 0; i < loungeTarget[tableCod].count; i++){
        printf("%s -> R$ %.2f\n", loungeTarget[tableCod].products[i].productName, loungeTarget[tableCod].products[i].price);
    }
}

int SalesCancel(table *tableTarget, int targetItem){
    item itemNull;
    itemNull.price = 0;
    itemNull.productName = "";

    if (tableTarget->count <= targetItem)
        return 0;
    else{
        for (int i = targetItem; i < tableTarget->count; i++){
            if (i == tableTarget->count - 1)
                tableTarget->products[i] = itemNull;
            else
                tableTarget->products[i] = tableTarget->products[i + 1];
        }
        tableTarget->count--;
        return 1;
    }
}

float MyBillIs(table tableTarget){
    float billSum = 0.0;

    for (int i = 0; i < tableTarget.count; i++)
        billSum += tableTarget.products[i].price;

    return billSum;
}

void ComandasView(void){
    system("clear");
    printf("------------------BEM VINDO A PIZZARIA DE LAB I------------------\n");
    printf("COMANDAS\n\n");
    printf("1 - Consultar comanda\n");
    printf("2 - Lancamento\n");
    printf("3 - Estorno\n");
    printf("4 - Fechar mesa\n");
    printf("0 - Voltar para principal\n");
    system("sleep 3");
}