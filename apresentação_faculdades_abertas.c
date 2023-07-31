#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
/**
 * @<programador> Maykoll Rocha
 * @email maykoll.rocha422@academico.ufgd.edu.br
 * @<revisor_ortográfico> Rafael Costa Miguel
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
    //Cria o arquivo de solução com o tamanho base;
    int *solc = malloc(tam*sizeof(int));
    int carry = 0;//Um carry que começa com Zero, pois não tem nada para carregar.
    //Faz a conta bit a bit
    for(int i=0;i<tam;i++)
    {
        solc[i] = vet1[i]+vet2[i]+carry;//Soma os dois valores + o carry, que pode ser maior do que 0 em algum momento.
        carry = 0;
        if(solc[i]>=2)//Quando o valor for 2 ou 3 que são os possíveis, eles tiram -2, porque se for 3 continua 1 e o carry soma 1.
        {
            solc[i] -= 2;
            carry = 1;
        }
    }
    //Retorna a solução
    return solc;
}

int *complement_of_2(int *vet,int tam)
{
    int *compl = copy_vet(vet,tam);//Cópia de segurança
    for(int i=0; i<tam; i++) compl[i] = !(compl[i]);//Entrega o vetor todo negativado
    printf("            ");
    for(int i = tam-1; i>=0; i--)printf("\x1b[32m""%i""\x1b[0m",compl[i]);
    printf("\n");
    printf("  Após isso deve-se somar 1 no cálculo para assim ter a soma o valor negativo.\n");
    printf("  Vale lembrar também que para ter o negativo do valor positivo faz o mesmo com o valor negativo.\n");

    //Cria o vetor binário de valor 1
    int *bin1sum = dec_to_bin(1,tam);

    return bin_sum(compl,bin1sum,tam);
}

int *dec_to_bin(int num,int tam)
{
    int *bin;//Vetor auxilar para fazer a carregamento e depois a exportação de bits.
    bin = malloc(tam*sizeof(int));//Aloca dinamicamente um vetor de valor inteiro.

    int aux_comp = 0;//Auxiliar para saber se é negativo.
    //Checa se o número é negativo com o bit de sinal que está na última casa.
    if(num<0)
    {
        aux_comp = 1;
        num *=-1;
    }

    //Realiza o update no número.
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
    printf("    A conversão binária para decimal é uma conta básica que todo computador faz.\n"
           "    Existem 2 tipos de conversão, a da parte inteira para decimal e da\n"
           "parte flutuante, que seria a parte não inteira do cálculo\n"
           "    Irei apresentar a parte inteira do cálculo:\n"
           "    Para se ter uma ideia, base binária é tudo na base 2 e seus números são apenas\n 0 e 1\n"
           "    Os passos para fazer a conversão de binário para decimal são:\n"
           "        Dividir o número por 2, seu resto (0 ou 1) é preservado\n"
           "        O quociente continua para a próxima etapa até se tornar 0\n");
    int num;
    int comp;
    srand(time(NULL));
    num =  rand()%129;
    comp = rand()%2;
    if(num==128) comp = 1;
    printf("  (O valor em verde é o resto que será levado para mostrar o binário no final)\n  Transformando o número %i em binário:\n",(comp)?-1*num:num);
    int *bin;
    int tam;
    tam = 1;
    bin = malloc(tam*sizeof(int));
    int l=9;
    if(comp)
    {
        printf("  Números negativos tem que ter o último valor 1 \npara fazer a conversão desses números usamos complemento a dois \nfazemos a divisão como um inteiro sem sinal.\n");
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
        printf("  O complemento a dois se baseia em um inversão dos binários\nO que for 0 vira 1 e o que é 1 vira 0 e soma 1 byte no final.\n");
        bin = complement_of_2(bin,tam);
    }
    printf("  Após fazer toda a divisão pegamos seus restos \nna direção oposta e formamos o número binário.\n");
    if(comp)printf("Assim após o complemento temos o valor binário negativo.\n");
    printf("         ");
    for(int i = tam-1; i>=0; i--)
        printf("\x1b[32m""%i""\x1b[0m",bin[i]);

    Sleep(10000);
    system("cls");
    free(bin);
    }
    return 1;
}
