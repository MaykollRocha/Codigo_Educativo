#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
/**
 * @<programador> Maykoll Rocha
 * @email maykoll.rocha422@academico.ufgd.edu.br
 * @<revisor_ortogr�fico> Rafael Costa Miguel
 * @email rafael.miguel079@academico.ufgd.edu.br
 * @date  2023-07-30
**/
int *complement_of_2(int *vet,int tam);//Faz o complemento a dois dos bits
int *dec_to_bin(int num,int tam);
void gotoxy(int x, int y);

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

int *copy_vet(int *vet,int tam)
{
    int *newvet = malloc(tam*sizeof(int));

    for(int i = 0; i<tam; i++)
        newvet[i] = vet[i];

    return newvet;
}

int *bin_sum(int *vet1,int *vet2,int tam)
{
    //Cria o arquivo de solu��o com o tamanho base;
    int *solc = malloc(tam*sizeof(int));
    int carry = 0;//Um carry que come�a com Zero, pois n�o tem nada para carregar.
    //Faz a conta bit a bit
    for(int i=0;i<tam;i++)
    {
        solc[i] = vet1[i]+vet2[i]+carry;//Soma os dois valores + o carry, que pode ser maior do que 0 em algum momento.
        carry = 0;
        if(solc[i]>=2)//Quando o valor for 2 ou 3 que s�o os poss�veis, eles tiram -2, porque se for 3 continua 1 e o carry soma 1.
        {
            solc[i] -= 2;
            carry = 1;
        }
    }
    //Retorna a solu��o
    return solc;
}

int *complement_of_2(int *vet,int tam)
{
    int *compl = copy_vet(vet,tam);//C�pia de seguran�a
    for(int i=0; i<tam; i++) compl[i] = !(compl[i]);//Entrega o vetor todo negativado
    printf("            ");
    for(int i = tam-1; i>=0; i--)printf("\x1b[32m""%i""\x1b[0m",compl[i]);
    printf("\n");
    printf("  Ap�s isso deve-se somar 1 no c�lculo para assim ter a soma o valor negativo.\n");
    printf("  Vale lembrar tamb�m que para ter o negativo do valor positivo faz o mesmo com o valor negativo.\n");

    //Cria o vetor bin�rio de valor 1
    int *bin1sum = dec_to_bin(1,tam);

    return bin_sum(compl,bin1sum,tam);
}

int *dec_to_bin(int num,int tam)
{
    int *bin;//Vetor auxilar para fazer a carregamento e depois a exporta��o de bits.
    bin = malloc(tam*sizeof(int));//Aloca dinamicamente um vetor de valor inteiro.

    int aux_comp = 0;//Auxiliar para saber se � negativo.
    //Checa se o n�mero � negativo com o bit de sinal que est� na �ltima casa.
    if(num<0)
    {
        aux_comp = 1;
        num *=-1;
    }

    //Realiza o update no n�mero.
    for(int i =0; i<tam; i++)
    {
        bin[i] = num%2;
        num = num/2;
    }
    //Retorna em complemento a 2.
    if(aux_comp) return complement_of_2(bin,tam);

    return bin;
}

int main()
{
    setlocale(LC_ALL,"");
    while(1)
    {
    printf("    A convers�o bin�ria para decimal � uma conta b�sica que todo computador faz.\n"
           "    Existem 2 tipos de convers�o, a da parte inteira para decimal e da\n"
           "parte flutuante, que seria a parte n�o inteira do c�lculo\n"
           "    Irei apresentar a parte inteira do c�lculo:\n"
           "    Para se ter uma ideia, base bin�ria � tudo na base 2 e seus n�meros s�o apenas\n 0 e 1\n"
           "    Os passos para fazer a convers�o de bin�rio para decimal s�o:\n"
           "        Dividir o n�mero por 2, seu resto (0 ou 1) � preservado\n"
           "        O quociente continua para a pr�xima etapa at� se tornar 0\n");
    int num;
    int comp;
    srand(time(NULL));
    num =  rand()%129;
    comp = rand()%2;
    if(num==128) comp = 1;
    printf("  (O valor em verde � o resto que ser� levado para mostrar o bin�rio no final)\n  Transformando o n�mero %i em bin�rio:\n",(comp)?-1*num:num);
    int *bin;
    int tam;
    tam = 1;
    bin = malloc(tam*sizeof(int));
    int l=9;
    if(comp)
    {
        printf("  N�meros negativos tem que ter o �ltimo valor 1 \npara fazer a convers�o desses n�meros usamos complemento a dois \nfazemos a divis�o como um inteiro sem sinal.\n");
        l+=3;
    }
    printf("   %3d/ 2\n",num);
    l++;
    l++;
    int x=3;
    while(num!=0)
    {
        bin[tam-1] = num%2;
        num = num/2;
        gotoxy(x,l);
        if(bin[tam-1]==0)
        {
            printf("\x1b[32m""  %d""\x1b[0m",bin[tam-1]);
        }else{
            printf("\x1b[32m""%3.0d""\x1b[0m",bin[tam-1]);
        }

        if(num==0)
            printf("  %d/ 2\n",num);
        else
            printf("%3.0d/ 2\n",num);

        if(num!=0)
        {
            tam+=1;
            bin = realloc(bin,tam*sizeof(int));
            l++;
            x += 3;
        }else{
            tam+=1;
            bin = realloc(bin,tam*sizeof(int));
            bin[tam-1] = 0;
            l++;
            x += 3;
        }
    }
    gotoxy(x,l);
    printf("\x1b[32m""  %d""\x1b[0m",bin[tam-1]);
    printf("  %d\n",num);
    if(comp)
    {
        printf("  O complemento a dois se baseia em um invers�o dos bin�rios\nO que for 0 vira 1 e o que � 1 vira 0 e soma 1 byte no final.\n");
        bin = complement_of_2(bin,tam);
    }
    printf("  Ap�s fazer toda a divis�o pegamos seus restos \nna dire��o oposta e formamos o n�mero bin�rio.\n");
    if(comp)printf("Assim ap�s o complemento temos o valor bin�rio negativo.\n");
    printf("         ");
    for(int i = tam-1; i>=0; i--)
        printf("\x1b[32m""%i""\x1b[0m",bin[i]);

    Sleep(10000);
    system("cls");
    free(bin);
    }
    return 1;
}
