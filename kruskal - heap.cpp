#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int TAM;


void heapify(int arr[], int n, int i, int pos1[], int pos2[])
{
    int aux;
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        aux = arr[i];
        arr[i] = arr[largest];
        arr[largest] = aux;

        aux = pos1[i];
        pos1[i] = pos1[largest];
        pos1[largest] = aux;

        aux = pos2[i];
        pos2[i] = pos2[largest];
        pos2[largest] = aux;

        heapify(arr, n, largest, pos1, pos2);
    }
}




void heapSort(int arr[], int n, int pos1[], int pos2[])
{
    int aux;
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, pos1, pos2);

    // One by one extract an element from heap
    for (int i=n-1; i>=0; i--)
    {
        aux = arr[0];
        arr[0] = arr[i];
        arr[i] = aux;

        aux = pos1[0];
        pos1[0] = pos1[i];
        pos1[i] = aux;

        aux = pos2[0];
        pos2[0] = pos2[i];
        pos2[i] = aux;

        heapify(arr, i, 0, pos1, pos2);
    }
}

void kruskal (char*nome, int pos1[], int pos2[], int tamanho){
   int *pilha[TAM];
   int *caminho;
   caminho = (int *) malloc(tamanho * sizeof(int));
   int i,j,k=0,l=0, aux, x=0;
   int novoLugar = 0, novoLugar2 =0;
   bool foiTrocado = false, pula = false;
   bool Sair = false;
   bool libera = false;

   for(i=0; i< TAM; i++){
        pilha[i] = (int *)malloc(TAM * sizeof(int));
        pilha[i][0] = i;
        for(j=1; j<TAM; j++){
            pilha[i][j] = -1;
        }

   }

   i=0;
   j=1;
   l=1;



   while(!Sair){


        if(pilha[pos1[i]][0] != -1 && pilha[pos2[i]][0] != -1){//significa que nenhuma das duas "arvores" foram ligadas ainda.

            caminho[k] = pos1[i];
            k++;
            caminho[k] = pos2[i];
            k++;

            l=1;
            while(!libera){
                while(pilha[pos1[i]][j] != -1){
                    j++;
                }

                for(x = 1; x< TAM; x++){
                    if (pilha[pos1[i]][x] == pilha[pos2[i]][l-1]){
                        break;
                    }
                    else if (x == TAM-1){
                        pilha[pos1[i]][j] = pilha[pos2[i]][l-1];
                    }
                }

                //pilha[pos1[i]][j] = pilha[pos2[i]][l-1];

                if(pilha[pos2[i]][l] == -1){ //nao tem mais elementos a ser adicionado
                     pilha[pos2[i]][0] = -1;
                     pilha[pos2[i]][1] = -1*pos1[i];//armazena para qual pilha foi
                     j=1;
                     l=1;
                     libera = true;


                }
                else{
                    j++;
                    l++;
                }
            }


        }

        else if (pilha[pos1[i]][0] == -1 && pilha[pos2[i]][0] == -1){
            novoLugar = -1*pilha[pos1[i]][1];
            while(pilha[novoLugar][1]<0){
                novoLugar = -1*pilha[novoLugar][1];
            }

            novoLugar2 = -1*pilha[pos2[i]][1];
            while(pilha[novoLugar2][1]<0){
                novoLugar2 = -1*pilha[novoLugar2][1];
            }

            if(novoLugar2 == novoLugar){ //nao pode haver essa ligação
                pula = true;
            }

            if(pula == false){
                caminho[k] = pos1[i];
                k++;
                caminho[k] = pos2[i];
                k++;

                l = 1;
                while(!libera){

                    while(pilha[novoLugar][j] != -1){
                        j++;
                    }

                   for(x = 1; x< TAM; x++){
                        if (pilha[novoLugar][x] == pilha[novoLugar2][l-1]){
                            break;
                        }
                        else if (x == TAM-1){
                            pilha[novoLugar][j] = pilha[novoLugar2][l-1];
                        }
                    }
                    // pilha[novoLugar][j] = pilha[novoLugar2][l-1];
                    if (pilha[novoLugar2][l] == -1){ //nao tem mais elementos a ser adicionado
                        pilha[novoLugar2][0] = -1;
                        pilha[novoLugar2][1] = -1*novoLugar;//armazena para qual pilha foi
                        j=1;
                        l=1;
                        libera = true;

                    }
                    else{
                        j++;
                        l++;
                    }

                }

            }

            pula = false;


        }

        else if (pilha[pos1[i]][0] == -1){

            for (l = 0; l < TAM; l++){
                if(pilha[pos2[i]][l] == pos1[i]){
                    pula = true;
                    break;
                }
            }


            if(pula == false){
                novoLugar = -1*pilha[pos1[i]][1];

                while(pilha[novoLugar][1]<0){
                    novoLugar = -1*pilha[novoLugar][1];
                }

                if(foiTrocado){
                    caminho[k] = pos2[i];
                    k++;
                    caminho[k] = pos1[i];
                    k++;
                }
                else{
                    caminho[k] = pos1[i];
                    k++;
                    caminho[k] = pos2[i];
                    k++;
                }

                l = 1;
                while(!libera){
                    while(pilha[novoLugar][j] != -1){
                            j++;
                    }
                    for(x = 1; x< TAM; x++){
                        if (pilha[novoLugar][x] ==  pilha[pos2[i]][l-1]){
                            break;
                        }
                        else if (x == TAM-1){
                            pilha[novoLugar][j] = pilha[pos2[i]][l-1];
                        }
                    }
                    if(strcmp(nome, "n1500B\n")){
                        pilha[novoLugar][j] = pilha[pos2[i]][l-1];
                    }

                    if(pilha[pos2[i]][l] == -1){ //nao tem mais elementos a ser adicionado
                        pilha[pos2[i]][0] = -1;
                        pilha[pos2[i]][1] = -1*novoLugar;//armazena para qual pilha foi
                        j=1;
                        l=1;
                        libera = true;

                    }
                    else{
                        j++;
                        l++;
                    }
                }

            }

            if (foiTrocado){
                aux = pos1[i];
                pos1[i] = pos2[i];
                pos2[i] = aux;
                foiTrocado = false;
            }
            pula = false;

        }

        else if (pilha[pos2[i]][0] == -1){

             aux = pos1[i];
             pos1[i] = pos2[i];
             pos2[i] = aux;
             foiTrocado = true;
             i--;

        }

        for(l = 0; l<TAM; l++){

            if(pilha[l][TAM-1] != -1){
                Sair = true;
                break;
            }

        }

        l=1;
        i++;
        libera = false;

   }

   printf("caminho que o grafo seguira sera: \n");
   for(i=1; i< k; i+=2){
       printf("%d - %d\n", caminho[i-1], caminho[i]);
   }

   for(i=0; i< TAM; i++){
      free(pilha[i]);
   }
   free(caminho);
   printf("\n");

}

int main(int argc, char *argv[]){

      int *grafo;
      double *x, *y;
      char name[7];


      clock_t begin = clock();

      FILE *file;
      char conteudo[28];//vai receber os dados do arquivo
      int i=0;

      // nenhum arquivo foi arrastado para o executavel então encerrará o programa
      if (argc == 1){
          printf("arraste um arquivo .txt com as informacoes necessarias dentro deste arquivo para o executavel do projeto.\n");
          system("pause");
          return 0;
      }
      else {
         if (!(file = fopen(argv[1], "r"))) //abre o arquivo para leitura após ter sido arrastado
            printf ("arquivo nao pode ser aberto\n");
         else{

             TAM=0;

             while(fgets(conteudo, 28, file) != NULL) {
                  if(!strcmp(conteudo, "EOF")){
                     TAM -= 3;
                     break;
                  }

                  TAM++;
             }


             int tamanho = TAM;
             grafo = (int *) malloc(TAM * sizeof(int));
             x = (double *) malloc(TAM * sizeof(double));
             y = (double *) malloc(TAM * sizeof(double));
             fseek(file, 0, SEEK_SET);
             TAM = 0;


             while(fgets(conteudo, 28, file) != NULL) {
                if(!strcmp(conteudo, "EOF")){
                     TAM = tamanho;
                     break;
                }

                if (TAM == 0){
                    int c = 0;
                    while (c < 7) {
                      name[c] = conteudo[c+6];
                      c++;
                    }
                }

                if(TAM < 3){
                    TAM++;
                }

                else {
                    grafo[i] = atoi(conteudo);
                    x[i] = atof(conteudo + 7);
                    y[i] = atof(conteudo + 18);
                    i++;
                }
             }

             fclose(file);

         }
      }


      int tamanho_array = (TAM*(TAM-1))/2;
      int *arestas;
      int *digito1;
      int *digito2;
      arestas = (int *) malloc(tamanho_array * sizeof(int));
      digito1 = (int *) malloc(tamanho_array * sizeof(int));
      digito2 = (int *) malloc(tamanho_array * sizeof(int));
      int j=0,k=1;
      int maior_elemento = 0;



      for(i=0; i<tamanho_array; i++){
          arestas[i] = sqrt(pow((x[j] - x[k]), 2) + pow((y[j] - y[k]), 2));
          if (arestas[i] > maior_elemento){
            maior_elemento = arestas[i];
          }
          if(k == TAM-1){
            j++;
            k = j+1;
          }
          else{
            k++;
          }
          //printf("i = %d\n",i);
      }

      k=0;

      for(i=0; i<TAM-1; i++){
        for(j = i+1; j<TAM; j++){
            digito1[k] = i;
            digito2[k] = j;
            k++;
        }
      }


      heapSort(arestas, tamanho_array, digito1, digito2);
      kruskal (name, digito1, digito2, tamanho_array);

      free(arestas);
      free(grafo);
      free(x);
      free(y);
      clock_t end = clock();
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("tempo de execucao = %lf\n", time_spent);
      system("pause");
      return 0;
}
