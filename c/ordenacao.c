/**
 * @Author: reinaldo
 * @Date:   2014-09-03 19:28:12
 * @Last Modified by:   reinaldo
 * @Last Modified time: 2014-09-07 20:56:32
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TAM 100000


int array[TAM], tamHeap, scratch[TAM];

/**
 * Gera os valores para o array
 */
void generateValues() {

    int i;

    srand(time(NULL));

    for (i = 0; i < TAM; i++)
    {
        array[i] = rand();
    }

}

/**
 * Verifica se o array está ordenado
 * @return 1 para sim e 0 para não
 */
int isSorted() {
    int i;

    for (i = 0; i < (TAM - 1); i++)
        if(array[i] > array[i + 1])
            return 0;

    return 1;
}

/**
 * Algoritmo de ordenação Bubble Sort
 */
void bubbleSort() {

    int pass = 1, sorted = 0, aux, i;

    while(!sorted && pass < TAM) {
        sorted = 1;

        for (i = 0; i < TAM - pass; i++)
        {
            if(array[i] > array[i + 1]) {
                aux  = array[i];
                array[i] = array[i + 1];
                array[i + 1] = aux;
                sorted = 0;
            }
        }

        pass++;
    }

}

/**
 * Algoritmo de ordenação Insertion Sort
 */
void insertionSort() {

    int i, aux, j, found = 0, base;

    for (i = 1; i < TAM; i++) {
        aux = array[i];
        j = i - 1;
        found = 0;
        while (!found && j >= 0)
            if(array[j] > aux) {
                base = array[j];
                array[j] = array[j + 1];
                array[j + 1] = base;
                j--;
            } else
                found = 1;
    }

}

/**
 * Algoritmo de ordenação Selection Sort
 */
void selectionSort() {

    int i, j, atual, aux;

    for (i = 0; i < (TAM - 1); i++)
    {
        atual = i;
        for (j = i + 1; j < TAM; j++)
            if(array[atual] > array[j])
                atual = j;

        aux = array[atual];
        array[atual] = array[i];
        array[i] = aux;
    }

}

/**
 * Gera uma heap no vetor
 * @param i raiz da heap
 */
void heapify(i) {
    int l = 2 * i + 1,
        r = 2 * i + 2,
        m = 0,
        t = 0;

    if (l < tamHeap && array[l] > array[i])
        m = l;
    else
        m = i;

    if (r < tamHeap && array[r] > array[m])
        m = r;

    if (m != i) {
        t = array[i];
        array[i] = array[m];
        array[m] = t;

        heapify(m);
    }
}

/**
 * Algoritmo de ordenação heap sort
 */
void heapSort() {
    int i = 0, t = 0;
    tamHeap = TAM;
    for (i = ((TAM / 2) - 1); i >= 0; i--)
        heapify(i);

    for (i = (TAM - 1); i > 0; i--)
    {
        t = array[0];
        array[0] = array[i];
        array[i] = t;

        tamHeap--;
        heapify(0);
    }
}

/**
 * Algoritmo de ordenação merge sort
 * @param i início do vetor
 * @param j final do vetor
 */
void mergeSort(i, j) {
    int m = 0, l = 0, n = 0, k = 0;

    if(i < j) {
        m  = (i + j) / 2;

        mergeSort(i, m);
        mergeSort(m + 1, j);

        l = i;
        n = m + 1;

        for (k = i; k <= j; k++)
            if ((l <= m) && ((n > j) || (array[l] < array[n])))
                scratch[k] = array[l++];
            else
                scratch[k] = array[n++];

        for (k = i; k <= j; k++)
            array[k] = scratch[k];
    }
}

/**
 * Gera o ponto de divisão da partição
 * @param  p inicio do array
 * @param  r final do array
 * @return   ponto de divisão da partição
 */
int partition(int p, int r) {

    int piv = array[p], i = (p - 1), j = (r + 1), temp = 0;

    while(1) {

        while(array[--j] > piv);
        while(array[++i] < piv);

        if(i < j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        } else
            return j;

    }

}

/**
 * Implementação do quicksort
 * @param p início do vetor
 * @param r fim do vetor
 */
void quickSort(int p, int r) {

    int q = 0;

    if(p < r) {
        q = partition(p, r);
        quickSort(p, q);
        quickSort(q + 1, r);
    }

}

int main() {

    /**
     * Bubble sort
     */
    clock_t start = clock();

    generateValues();

    bubbleSort();

    printf("Ordenação com bubble sort: %13li\n", ((clock() - start) / CLOCKS_PER_SEC));
    printf("O vetor está ordenado? %s\n", isSorted() ? "Sim" : "Não");

    /**
     * Insertion sort
     */
    start = clock();

    generateValues();

    insertionSort();

    printf("Ordenação com insertion sort: %10li\n", ((clock() - start) / CLOCKS_PER_SEC));
    printf("O vetor está ordenado? %s\n", isSorted() ? "Sim" : "Não");


    /**
     * Selection sort
     */
    start = clock();

    generateValues();

    selectionSort();

    printf("Ordenação com selection sort: %10li\n", ((clock() - start) / CLOCKS_PER_SEC));
    printf("O vetor está ordenado? %s\n", isSorted() ? "Sim" : "Não");


    /**
     * Heapsort sort
     */
    start = clock();

    generateValues();

    heapSort();

    printf("Ordenação com heap sort: %15li\n", ((clock() - start) / CLOCKS_PER_SEC));
    printf("O vetor está ordenado? %s\n", isSorted() ? "Sim" : "Não");


    /**
     * Merge sort
     */
    start = clock();

    generateValues();

    mergeSort(0, TAM - 1);

    printf("Ordenação com merge sort: %14li\n", ((clock() - start) / CLOCKS_PER_SEC));
    printf("O vetor está ordenado? %s\n", isSorted() ? "Sim" : "Não");


    /**
     * quick sort
     */
    start = clock();

    generateValues();

    quickSort(0, TAM - 1);

    printf("Ordenação com quick sort: %14li\n", ((clock() - start) / CLOCKS_PER_SEC));
    printf("O vetor está ordenado? %s\n", isSorted() ? "Sim" : "Não");


    return 0;
}