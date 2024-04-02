#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergeSort_intercala(int *vetor, int esq, int meio, int dir, int *iteracoes, int *trocas)
{
    int i, j, k;
    int a_tam = meio - esq + 1;
    int b_tam = dir - meio;
    int *a = (int *)malloc(sizeof(int) * a_tam);
    int *b = (int *)malloc(sizeof(int) * b_tam);
    for (i = 0; i < a_tam; i++)
        a[i] = vetor[i + esq];
    for (i = 0; i < b_tam; i++)
        b[i] = vetor[i + meio + 1];
    for (i = 0, j = 0, k = esq; k <= dir; k++)
    {
        (*iteracoes)++;
        if (i == a_tam)
            vetor[k] = b[j++];
        else if (j == b_tam)
            vetor[k] = a[i++];
        else if (a[i] < b[j])
            vetor[k] = a[i++];
        else
            vetor[k] = b[j++];
        (*trocas)++;
    }
    free(a);
    free(b);
}

void mergeSort(int *vetor, int n, int *iteracoes, int *trocas)
{
    int esq, dir;
    int salto = 1;
    while (salto < n)
    {
        esq = 0;
        while (esq + salto < n)
        {
            dir = esq + 2 * salto;
            if (dir > n)
                dir = n;
            mergeSort_intercala(vetor, esq, esq + salto - 1, dir - 1, iteracoes, trocas);
            esq = esq + 2 * salto;
        }
        salto = 2 * salto;
    }
}

void Bolha(int *vetor, int n, int *iteracoes, int *trocas)
{
    int i, j;
    int temp;
    char troca;

    troca = 1;
    for (i = n - 1; (i >= 1) && (troca == 1); i--)
    {
        troca = 0;
        for (j = 0; j < i; j++)
        {
            (*iteracoes)++;
            if (vetor[j] < vetor[j + 1])
            {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
                troca = 1;
                (*trocas)++;
                printf("%d",&trocas);
            }
        }
    }
}

void printArray(int vetor[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}

int *generateRandomArray(int size)
{
    int *vetor = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        vetor[i] = rand() % 1000; // Números aleatórios entre 0 e 999
    return vetor;
}

int main()
{
    srand(time(NULL));
    int sizes[] = {1000, 10000, 100000};
    int sizesCount = sizeof(sizes) / sizeof(sizes[0]);
    char *algorithms[] = {"Bubblesort", "Mergesort"};
    int algorithmsCount = sizeof(algorithms) / sizeof(algorithms[0]);

    printf("Vetor [1000]\tVetor [10.000]\tVetor [100.000]\n");

    for (int i = 0; i < algorithmsCount; i++)
    {
        printf("%s\t", algorithms[i]);
        for (int j = 0; j < sizesCount; j++)
        {
            int *vetor = generateRandomArray(sizes[j]);
            int iteracoes = 0, trocas = 0;
            clock_t begin, end;
            double time_spent;

            begin = clock();
            if (i == 0)
            {
                Bolha(vetor, sizes[j], &iteracoes, &trocas);
            }
            else
            {
                mergeSort(vetor, sizes[j], &iteracoes, &trocas);
            }
            end = clock();
            time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000; // Tempo em milissegundos
            printf("%.2f ms\t%d\t%d\t", time_spent, iteracoes, trocas);
            free(vetor);
        }
        printf("\n");
    }
    return 0;
}
