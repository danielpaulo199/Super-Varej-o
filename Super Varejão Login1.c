     /* Super Varejão: Projeto de Algoritmos I
        Desenvolvido por: Daniel Paulo, Alexandre Zatti e Kalyan Lucas Basso;
    */

    //Cadastro de no máximo 100 itens no estoque, para aumentar mudar o valor do array produtos[]


#include <stdio.h>      //Biblioteca padrão
#include <stdlib.h>     //Uso de ponteiros
#include <locale.h>  //Bilbioteca para usar acentos
#include <conio.h>  //Limpar a tela
#include <string.h>  //Biblioteca para manipular strings
#include <time.h>  //Biblioteca para pegar o tempo do computador


    //declaração de FUNÇÃO

void Menuatribuicao();
void MostrarDados();
void MenuHome();
void Vender();
void Conferencia();
void AutoCadastro();
void ReporEstoque();
void RelatorioGerencial();
void EditarProduto();
void Inventario();
void ProdutosZerados();
void MargemBaixa();
void MaisVendido();
void GeraCupom();
void curvaABC();
void Logout();




double CalculaEstoque();

int VerificaID();
int Login();

// ESTRUTURAS

struct Produto
    {
        char nome[30];
        double precoVenda,margemLucro,precoCusto,vendasAcumuladas,participacao;
        int id,qtdEstoque,vendas;
    };

time_t t; // Para guardar data e hora


    // variaveis globais
    int contProdutos = 0;
    double gastoEstoque=0;
    double totalBruto=0;
    double totalLiquido=0;
    int vendasTotais=0;
    int perfil=0;
    char passwd[4] = "1234";    // Variaveis de senha e login super seguras
    char gerente[20] = "daniel";
    char operador[20] = "kalyan";

// MAIN
int main(){

    //uso de acentos
    setlocale(LC_ALL, "portuguese");

    //Array que guardara os produtos
    struct Produto produtos[100];

    //LOGIN

    perfil = Login(); // Define o perfil do usuario com base nas credenciais

//define um produto 0 para a posição 0 do array produtos[]
produtos[0].id = 0;
produtos[0].precoCusto = 0.0;
produtos[0].qtdEstoque = 0;
produtos[0].vendasAcumuladas = 0;
produtos[0].participacao = 0;
produtos[0].vendas = 0;
  contProdutos++;



    time(&t);//Armazena a data e a hora atual do sistema

//  Cadastra 3 iten automaticos para testes
    AutoCadastro(produtos);

// Menu HOME é o principal
    MenuHome(produtos);


return 0;
}

        // FUNÇÕES //

    void Menuatribuicao(struct Produto *produtos)
    {
        //Menu para realizar o cadastro de um novo produto

        int opcao=0;
        double margem=0;

        printf("=========== SUPER VAREJÃO ===========\n");

        printf("\nCodigo designado: %d\n",contProdutos);

        printf("\nDigite o nome do produto:");
        scanf(" %[^\t\n]s",&produtos[contProdutos].nome);
        fflush(stdin);

        printf("\nDigite a quantidade de unidades em estoque:");
        scanf("%d",&produtos[contProdutos].qtdEstoque);
        fflush(stdin);

        produtos[contProdutos].id = contProdutos;

        printf("\nDigite o preço de custo: R$");
        scanf("%lf",&produtos[contProdutos].precoCusto);
        fflush(stdin);

        printf("\nDigite a margem de lucro em %%: ");
        scanf("%lf",&produtos[contProdutos].margemLucro);
        fflush(stdin);

        produtos[contProdutos].vendas = 0;
        margem = produtos[contProdutos].margemLucro / 100;
        produtos[contProdutos].vendasAcumuladas = 0;
        produtos[contProdutos].participacao = 0;
        produtos[contProdutos].precoVenda = (produtos[contProdutos].precoCusto * margem) + produtos[contProdutos].precoCusto;

        printf("\nPreço de venda: R$%.2lf",produtos[contProdutos].precoVenda);

        printf("\n====================================\n");
        contProdutos++;


        getch();
        system("cls");

    }
    void MostrarDados(struct Produto *produtos, int id)
    {
        //Função para mostrar os dados de um ID digitado pelo usuário
            int dis=0,opcao=0;

                //Loop que verifica se o ID digitado é um produto cadastrado, e mostra seus dados.
        for(int i=1;i<=id;i++)
                {
                    if(id == produtos[i].id)
                    {

                    printf("\n       *Dados do produto*\n");
                    printf("\nNome: %s \n",produtos[i].nome);
                    printf("ID: %d \n",produtos[i].id);
                    printf("Estoque: %d UNDs \n",produtos[i].qtdEstoque);
                    printf("Preço de custo: R$%.2lf \n",produtos[i].precoCusto);
                    printf("Margem de lucro: %.2lf%%\n",produtos[i].margemLucro);
                    printf("Preço para venda: R$%.2lf\n",produtos[i].precoVenda);
                    dis = i;

                    }
                }

                //Se o ID digitado não for cadastrado
            if(dis == 0)
            {
                printf("\nNão ha produtos com este código!");
                getch();
                MenuHome(produtos);
            }


            //Opções para poder editar as informações do produto selecionado
            if(perfil == 1)
            {

                printf("\n\n1-Editar Produto");
                printf("\n2-Sair\n");

                fflush(stdin);
                scanf("%d",&opcao);

                  if(opcao == 1)
                  {
                      EditarProduto(produtos,id);
                      getch();
                  }

                  if(opcao == 2)
                  {
                      MenuHome(produtos);
                  }
          }
            printf("\nPressione qualquer tecla(do teclado) para sair\n");
                getch();
    }
    void MenuHome(struct Produto *produtos)
    {
      //Menu Principal onde fica as funcionalidades.

        int opcao;

            //Menu que sera exibido para quem tiver perfil de gerência (1)
        if(perfil == 1) //Verifica qul perfil do usuario
        {
        system("cls");
        printf("=========== SUPER VAREJÃO ===========\n\n");
        printf("1-Conferência / Edição de produtos\n");
        printf("2-Vender\n");
        printf("3-Repor estoque\n");
        printf("4-Cadastrar Produto\n");
        printf("5-Relatório Gerencial\n");
        printf("6-Inventario\n");
        printf("7-Curva ABC de mercadorias\n");
        printf("8-Logout\n");
        printf("0-Sair\n");

        printf("seu perfil: %d",perfil);
            scanf("%d",&opcao);


        switch(opcao)
            {

            case 1 : //Conferir Produtos ja cadastrados e mudar seus dados.
                system("cls");
                Conferencia(produtos);
                break;


           case 2 : //Abrir nova venda.
                system("cls");
                Vender(produtos);
                break;

           case 3:  //Adicionar produtos ja cadastrdos ao estoque da loja.
                system("cls");
                ReporEstoque(produtos);
                break;

           case 4:  //Cadastrar novo Produto.
                system("cls");
                Menuatribuicao(produtos);
                break;


           case 5:  //Gera os relatórios para gerenciar o andamento da loja.
                system("cls");
                RelatorioGerencial(produtos);
                break;

           case 6:  //Lista todos os produtos cadastrados com seu respectivo estoque.
                system("cls");
                Inventario(produtos);
                break;

           case 7:  //Relatório da participação de um produto na venda total.
                system("cls");
                curvaABC(produtos);
                break;

            case 8:  //Volta para o menu de login
                system("cls");
                Logout();
                break;

           case 0:  //Sair da aplicação.
                system("cls");
                exit(0);
                break;

           default :  //Se digitar uma opção que não existe.
                system("cls");
                MenuHome(produtos);

            }
        }

        //Menu que sera exibido para quem tiver perfil de usuario (2)
        if(perfil == 2) //Verifica qul perfil do usuario
        {
            system("cls");
            printf("=========== SUPER VAREJÃO ===========\n\n");
            printf("1-Conferir Produto\n");
            printf("2-Vender\n");
            printf("3-Logout\n");
            printf("0-Sair\n");

            printf("Seu perfil: %d\n",perfil);

            scanf("%d",&opcao);

            switch(opcao)
            {

            case 1 : //Conferir Produtos ja cadastrados e mudar seus dados.
                system("cls");
                Conferencia(produtos);
                break;


           case 2 : //Abrir nova venda.
                system("cls");
                Vender(produtos);
                break;

           case 3 : //Fazer logout
                system("cls");
                Logout();
                break;

           case 0 : //Sair.
                system("cls");
                exit(0);
                break;

           default :  //Se digitar uma opção que não existe.
                system("cls");
                MenuHome(produtos);
            }
        }
            MenuHome(produtos);

        }
    void Vender(struct Produto *produtos)
    {

            //Variaveis que irão guardar as informações da compra para serem repassadas
            //para a geração do cupom e para os relatórios.

        int id=0,quant=0,verificador=0,ids[20],quants[20],indexid=1;
        double totaliten=0,total=0,totalCusto=0,valoritens[20];
        int vwhile=1;


            //Caixa aberto onde usuario passara seus produtos até digitar 999 para finalizar
        while(vwhile == 1)
        {
            system("cls");
            printf("=========== VENDA ===========\n");
            printf("Digite 999 para finalizar a venda\n");
            printf("\nDigite o ID do item: ");
            id =0;
            scanf("%d",&id);

                if(id == 999)
                {
                    if(total <= 0) // Se abrir venda mas nao passar nenhum produto não gera o cupom
                    {
                        MenuHome(produtos);
                    }
                    else // Se houver produtos para gerar cupom
                    {
                        vwhile = 0;
                        vendasTotais += 1;
                        GeraCupom(produtos,ids,quants,valoritens,indexid,total);//Função com parametros que ira gerar o cupom fiscal
                    }
                }


            fflush(stdin);

            verificador = VerificaID(id); //Função que verifica se o ID digitado pertence a um produto

             if(verificador != 0)
                {
                    for(int i=1;i <= id;i++)
                        {

                            if(produtos[i].id == id)
                                {
                                   printf("\nProduto selecionado: %s\n",produtos[i].nome); //Quantidade que o cliente ira levar
                                   printf("\nDigite a quantidade: ");
                                   scanf("%d",&quant);
                                    if(quant <= 0)
                                        {
                                            printf("\nQuantidade inválida\n");
                                            system("cls");
                                            getch();
                                        }
                                        else  //Atribuição dos dados da compra para variaveis que serão usadas para gerar o cupom fiscal e os relatórios
                                        {
                                           totaliten = produtos[i].precoVenda * quant;
                                           total += totaliten;
                                           produtos[i].vendas += quant;
                                           produtos[i].qtdEstoque = produtos[i].qtdEstoque - quant;
                                           totalCusto = produtos[i].precoCusto * quant;
                                           totalLiquido += totalCusto;
                                           totalBruto += totaliten;
                                           produtos[i].vendasAcumuladas = produtos[i].precoVenda * produtos[i].vendas;

                                           ids[indexid] = i;
                                           valoritens[indexid] = produtos[i].precoVenda * quant;
                                           quants[indexid] = quant;
                                           indexid++;
                                           system("cls");
                                        }

                                }

                        }


                }

                }//fecha loop

        }
    void GeraCupom(struct Produto *produtos,int ids[],int quants[],double valoritens[],int indexid,double total)
    {
            system("cls");

            //variaveis para pegar os ids dos produtos comprados, e calcular taxas
                int usingid,itenscupom=0;
                double federal=0,estadual=0;

                //Cabeçalho do cupom fiscal

                printf("                Super Varejão S.A\n  ");
                printf("           Avenida Paulo Pinto, 501 D\n");
                printf("                  Chapecó-SC\n");
                printf(" CNPJ: 75.316.666/020104-06                  Nº Cupom:000%d\n",vendasTotais);
                printf("-----------------------------------------------------------------\n");
                printf("%s", ctime(&t));
                printf("\n                    CUPOM FISCAL\n\n");
                printf(" ID           DESCRIÇÃO                QUANT        VL.ITEN\n");


                for(int i=1;i<indexid;i++)
                {
                    //Variavel 'usingid' ira receber os IDs dos itens comprados para printar suas informações.
                    usingid = ids[i];
                    itenscupom += quants[i];
                    printf("\n%2.1d  %-30.30s   X %3.1d UNDs   R$%10.2lf",produtos[usingid].id,produtos[usingid].nome,quants[i],valoritens[i]);
                }

                federal = (0,03 * total) / 100; //Calculo ficticío das taxas.
                estadual = (0,05 * total) / 100; //Calculo ficticío das taxas.
                printf("\n-----------------------------------------------------------------");
                printf("\nvalor aproximado dos tributos: Federais(%.2lf)\n",federal);
                printf("valor aproximado dos tributos: Estaduais(%.2lf)\n",estadual);

                        //Gambiarra para mostrar o operador no cupom kkkk
                    if(perfil == 2)
                    {
                        printf("                                                  Operador: %s",operador);
                    }else printf("                                                  Operador: %s",gerente);


                printf("\n TOTAL: R$%.2lf       %d Itens comprados\n\n",total,itenscupom);
                getch();
                MenuHome(produtos); //Retorna para o menu inicial após final da compra
        }
    int VerificaID(int id)
    {
        if(id <= 0 || id > contProdutos) //Verifica se o id digitado pelo usuário é valido
        {
                //Caso ID inválido
            printf("\nCódigo Invalido do verificaID id\n");
            getch();
            system("cls");
            return 0;
        }
            //Caso ID válido
                return 1;
    }
    void Conferencia(struct Produto *produtos)
    {
        int id,verificador=0;

                printf("Digite o ID do item: ");
                scanf("%d",&id);  //Input do usuário com ID
                fflush(stdin);

                verificador = VerificaID(id); // Verifica se o ID é válido

                    if(verificador != 0)
                    {
                        //Caso id Valido executa a função que ira mostrar seus dados
                        MostrarDados(produtos,id);
                    }

                    else
                    {
                        MenuHome(produtos);
                    }
    }
    void AutoCadastro(struct Produto *produtos)
    {
        //Função para cadastrar itens automaticamente

        strcpy(produtos[contProdutos].nome, "Coca Cola 2l");
        produtos[contProdutos].precoCusto = 5.30;
        produtos[contProdutos].margemLucro = 3;
        produtos[contProdutos].id = contProdutos;
        produtos[contProdutos].qtdEstoque = 10;
        produtos[contProdutos].vendas = 0;
        produtos[contProdutos].vendasAcumuladas = 0;
        produtos[contProdutos].participacao = 0;
        produtos[contProdutos].precoVenda = ((produtos[contProdutos].margemLucro / 100) * produtos[contProdutos].precoCusto) + produtos[contProdutos].precoCusto;
    contProdutos++;

        strcpy(produtos[contProdutos].nome, "Alface Crespa");
        produtos[contProdutos].precoCusto = 2.59;
        produtos[contProdutos].margemLucro = 20;
        produtos[contProdutos].id = contProdutos;
        produtos[contProdutos].qtdEstoque = 3;
        produtos[contProdutos].vendas = 0;
        produtos[contProdutos].vendasAcumuladas = 0;
        produtos[contProdutos].participacao = 0;
        produtos[contProdutos].precoVenda = ((produtos[contProdutos].margemLucro / 100) * produtos[contProdutos].precoCusto) + produtos[contProdutos].precoCusto;
    contProdutos++;

        strcpy(produtos[contProdutos].nome, "Peru Sadia");
        produtos[contProdutos].precoCusto = 32.90;
        produtos[contProdutos].margemLucro = 21;
        produtos[contProdutos].id = contProdutos;
        produtos[contProdutos].qtdEstoque = 540;
        produtos[contProdutos].vendas = 0;
        produtos[contProdutos].vendasAcumuladas = 0;
        produtos[contProdutos].participacao = 0;
        produtos[contProdutos].precoVenda = ((produtos[contProdutos].margemLucro / 100) * produtos[contProdutos].precoCusto) + produtos[contProdutos].precoCusto;
    contProdutos++;

    }
    void ReporEstoque(struct Produto *produtos)
    {
        //Adicionar itens ao estoque atual

        int id=0,add=0,verificador=0;
        double total;

        printf("\nDigite o ID do produto que deseja repor: ");
        scanf("%d",&id);   //Recebe o IDdo produto a ser reposto

        verificador = VerificaID(id); //Verifica se é um ID válido

        if(verificador != 0)
        {
            for(int i=1;i<=id;i++) //Loop que ira buscar no array o id selecionado
            {
                if(id == produtos[i].id) //Mostra as informações do ID digitado.
                {
                    printf("\nIten Selecionado: %s",produtos[i].nome);
                    printf("\nEstoque atual: %d",produtos[i].qtdEstoque);
                    printf("\n\n Digite a quantidade que deseja adicionar ao estoque: ");
                    scanf("%d",&add);   //Input da quantidade a ser adicionad ao estoque

                    produtos[i].qtdEstoque += add;
                    total = produtos[i].precoCusto * add;
                    gastoEstoque += total;

                    printf("\nEstoque atualizado para: %d UNDs\n",produtos[i].qtdEstoque);
                    printf("\nEssa reposição custou: R$%.2lf",total);
                    printf("\n\nTotal de gastos com restoque este mês: R$%.2lf",gastoEstoque);
                    getch();
                }

            }
        }
    }
    void RelatorioGerencial(struct Produto *produtos)
    {
            //Gera os principais relatórios da loja
                double lucro=0,ticket=0;
                lucro = totalBruto - totalLiquido - gastoEstoque + totalBruto; //Calcula o lucro
                ticket = lucro / vendasTotais;  //Calcula o Ticket Médio

        //Printar as informações
        printf("============ Relatório Gerencial ============");
        printf("\nRelatório gerado em: %s", ctime(&t));
        printf("\n\nTotal de Cupoms fiscais emitidos: %d\n\n",vendasTotais);
        MaisVendido(produtos); //Função que ira comparar os produtos e mostrar o que mais foi vendido
        printf("\nTotal de produtos cadastrados: %d\n",contProdutos-1);
        printf("\nValor total do estoque: R$%.2lf",CalculaEstoque(produtos)); //Calcula o preço total de todos os iten do estoque
        printf("\nValor total gasto com reestoque de mercadorias: R$%.2lf",gastoEstoque);
        printf("\nTotal de vendas bruto: R$%.2lf",totalBruto);
        printf("\nTotal de vendas liquido: R$%.2lf",totalLiquido);
        printf("\nTotal de lucro: R$%.2lf",lucro);

            if(ticket > 0)printf("\nTicket Medio: R$%.2lf",ticket);

        MargemBaixa(produtos);  //Cria tabela de produtos com margem de lucro abaixo de 5%
        ProdutosZerados(produtos); //Cria tabel de produtos com estoque zerado ou negativo
        getch();

    }
    double CalculaEstoque(struct Produto *produtos)
    {
        double estoqueTotal=0.0,estoqueLocal=0.0;

            for(int i=1;i < contProdutos;i++) //Loop que ira somar o estoque de todos os produtos.
            {
                estoqueLocal = produtos[i].qtdEstoque * produtos[i].precoCusto;
                estoqueTotal += estoqueLocal;
            }

        return estoqueTotal;
    }
    void EditarProduto(struct Produto *produtos,int id)
    {
        double divide=0;
        //Editar as informações em um produto previamente cadastrado.

        printf("======= EDITAR PRODUTO =======\n");
        printf("\n\nEditando produto: %s\n",produtos[id].nome);
        printf("\nDigite novo preco de Custo: R$");
        fflush(stdin);
        scanf("%lf",&produtos[id].precoCusto);
        printf("\nDigite a nova margem de lucro em %%: ");
        fflush(stdin);
        scanf("%lf",&produtos[id].margemLucro);

        //Calculo automatico do preço de venda baseado na margem de lucro e preço de custo
        divide = produtos[id].margemLucro / 100;
        produtos[id].precoVenda = (produtos[id].precoCusto * divide) + produtos[id].precoCusto;
        printf("\nNovo preco de Venda: R$%.2lf",produtos[id].precoVenda);
    }
    void Inventario(struct Produto *produtos)
    {

        //Desenha tabela com as informações de todos os produtos cadastrados
        system("cls");
        printf("\n======================================= INVENTARIO ================================================\n");
        printf("Gerado em: %s", ctime(&t)); //Mostra data e hora atual
        printf("\nInventario: Listagem de todos os produtos da loja.\n");
        printf("\nID |          DESCRIÇÃO             |    ESTOQUE    | PRECO CUSTO  | PRECO VENDA  |  MARGEM LUCRO  |");
        printf("\n----------------------------------------------------------------------------------------------------");
            for(int i=1;i<contProdutos;i++) //Loop para printar as informações do array produtos[]
            {
                printf("\n%2.1d |%-30.30s  |%8.1d UNDs  |R$%9.2lf   |R$%9.2lf   |%9.2lf %%     |",produtos[i].id,produtos[i].nome,produtos[i].qtdEstoque,produtos[i].precoCusto,produtos[i].precoVenda,produtos[i].margemLucro);
                printf("\n---------------------------------------------------------------------------------------------------");
            }
            printf("\n\n=================================== Inventario finalizado ==========================================\n");
            printf("\nPressione qualquer tecla(do teclado) para sair\n");

            getch();
    }
    void ProdutosZerados(struct Produto *produtos)
    {
        int all=0; //variavel que verifica se existe algum produto sem estoque

            for(int i=1;i<contProdutos;i++)
        {

            if(produtos[i].qtdEstoque <= 0)
            {
                all = 1;
            }
        }

        if(all != 0) //Desenha a tabela
        {
                printf("\n\n============== PRODUTOS SEM ESTOQUE ================\n");
                printf("\nID |          DESCRIÇÃO             |    ESTOQUE    |");
                printf("\n-----------------------------------------------------");

            for(int i=1;i<contProdutos;i++)
            {

                if(produtos[i].qtdEstoque <= 0) //Loop que percore o array e printa somente itens com estoque igual ou menor que zero
                {
                    printf("\n%2.1d |%-30.30s  |%8.1d UNDs  |",produtos[i].id,produtos[i].nome,produtos[i].qtdEstoque);
                    printf("\n-----------------------------------------------------");
                }
            }
        }

        else
        {  //Caso não haja nenhum produto com estoque zerado ou negativo
            printf("\nProdutos com estoque zerado: 0 registros\n");
        }
    }
    void MargemBaixa(struct Produto *produtos)
    {

        int all=0; //variavel que verifica se existe algum produto com margem abaixo de 5%

            for(int i=1;i<contProdutos;i++)
            {

                if(produtos[i].margemLucro <= 5)
                {
                    all = 1;
                }
            }

        if(all != 0)  //Desenha tabela
        {
                printf("\n\n========= PRODUTOS COM MARGEM MENOR QUE 5%% =========\n");
                printf("\nID |          DESCRIÇÃO             |    MARGEM   |");
                printf("\n-----------------------------------------------------");

            for(int i=1;i<contProdutos;i++)
            {

                if(produtos[i].margemLucro <= 5)//Loop que percore o array e busca por produtos com margem abaixo de 5%
                {
                    printf("\n%2.1d |%-30.30s  |%9.2lf %%  |",produtos[i].id,produtos[i].nome,produtos[i].margemLucro);
                    printf("\n-----------------------------------------------------");

                }
            }

        }

        else
        {       //Caso não haja nenhum produto abaixo de 5%
            printf("\n\nProdutos com margem abaixo de 5%%: 0 registros\n");
        }
    }
    void MaisVendido(struct Produto *produtos)
    {
        int all=0; //Variavel para verificar se algum iten ja foi vendido

        for(int i=1;i<contProdutos;i++)
        {
            if(produtos[i].vendas >= 1)
            {
                all = 1;
            }
        }

        if(all != 0)
        {
                int top=0;

            for(int i=1;i<contProdutos;i++)
            {
                if(produtos[i].vendas > top) //Percore o array para verificar as quantias vendidas de cada produto e aplica o ID da maior para variavel top
                {
                    top = i;
                }
            }   //Printa o mais vendido e número de unidades

        printf("Produto mais Vendido:  %s    |%d unidades vendidas.",produtos[top].nome,produtos[top].vendas);
        }

        else
        {   //Caso nenhum produto tenha sido vendido
            printf("\nNenhum produto foi vendido!");
        }
    }
    void curvaABC(struct Produto *produtos)
    {
        struct Produto prod[contProdutos]; //Array que recebera o array de produtos para ser organizado
        struct Produto aux[contProdutos]; //Array auxiliar para fazer inversão de valores


            //Cabeçalho do relatório
        system("cls");
        printf("\n========================= Curva ABC de Mercadorias ==========================\n");
        printf("Gerado em: %s", ctime(&t));
        printf("\n Curva ABC: Porcentagem de participação de um produto na venda total da loja.\n");
        printf("\nID |          DESCRIÇÃO             |    VENDA ACUMULADA    | PARTICIPAÇÃO  |");
        printf("\n-----------------------------------------------------------------------------");

        //Copia o array produtos[] para o array prod[]
            for(int i=1;i<contProdutos;i++)
            {
                produtos[i].participacao = (produtos[i].vendasAcumuladas * 100) / totalBruto; // Calcula a % de participação do produto
                prod[i] = produtos[i];
            }



        //Organiza em ordem decrescente de participação em vendas o array prod[]
            for(int i=1;i<contProdutos;i++)
            {
                for(int j=i+1;j<contProdutos;j++)
                {
                    if(prod[i].vendasAcumuladas < prod[j].vendasAcumuladas)
                    {
                        aux[i] = prod[i];
                        prod[i] = prod[j];
                        prod[j] = aux[i];
                    }
                }
            }


             //Mostra na tela as invermações depois do sort no array[]
            for(int i=1;i<contProdutos;i++)
            {
                    if(prod[i].vendasAcumuladas > 0)
                    {
                        printf("\n%2.1d |%-30.30s  |    R$%8.2lf         |  %9.2lf%%   |",prod[i].id,prod[i].nome,prod[i].vendasAcumuladas,prod[i].participacao);
                        printf("\n-----------------------------------------------------------------------------");
                    }
                }
            printf("\n\n============================= Fim da curva ABC ==============================\n");
            printf("\nPressione qualquer tecla(do teclado) para sair\n");

            getch();
    }

    int Login()
    {
        char password[4]; // Variavel que armazena o input de senha
        char user[30];   //Variavel que armazena o input de login
        printf("======= LOGIN =======\n\n");
        printf("Digite seu login: ");
        scanf("%s",&user);
        printf("\nDigite sua senha de 4 letras: ");
        for(int i=0;i<4;i++)
        {                                //Loop que ira ler a senha e colocar * no lugar
            password[i] = getch();
                putch('*');
         }

            //Compara para ver se a senha e login digitado bate com as credenciais
            if(strcmp(gerente,user)==0 && password[0] == passwd[0] && password[1] == passwd[1] && password[2] == passwd[2] && password[3] == passwd[3])
            {
                getch();
                return 1; //Login de gerente aceito
            }
            if(strcmp(operador,user)==0 && password[0] == passwd[0] && password[1] == passwd[1] && password[2] == passwd[2] && password[3] == passwd[3])
            {
                getch();
                return 2; //Login de operador
            }


            printf("\nCredenciais Invalidas!");
            getch();
            system("cls");
            Login();
    }

    void Logout()
    {
        system("cls");
        perfil = Login();

    }

