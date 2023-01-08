//
// Created by João Valentim on 23/11/2022.
//

#include "aed_lp1_2023_proj_part1_ints.h"
#include "aed_lp1_2023_proj_part1_chars.h"

void limpar_array_int(short* array){
    for (int i = 0; i < 20; ++i) {
        *(array+i)=-1;
    }
}

void limpa_matriz_int(short** mat,int lines){
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < 20; ++j) {
            *(*(mat+i)+j)=-1;
        }
    }
}

void print_matriz_ints(short** mat) {
    printf("\n-------MATRIZ------\n");
    for (int i = 0; *(mat + i) != NULL; ++i) {
        printf("[%d] ", i);
        for (int j=0; j < 20-1; j++){
            if (*(*(mat+i)+j)!=-1)
            {
                printf("%d", *(*(mat+i)+j));
            } else break;
        }
        printf("\n");
    }

    printf("\n-------MATRIZ------\n");
}

unsigned long long new_public_key_int(void){
    unsigned long long result =0;
    unsigned long long maximo = (250);//(ULLONG_MAX/100000000000000000)->184
    result = (rand() % (maximo - 0)) + 1;
    return result;
}

short* key_long_2_digits_int(unsigned long long key){
    int count = Count_digitos_char(key);
    int num=0,i=0;
    short* str = malloc( count *sizeof (int));
    str[count]=-1;
    for (i = count-1; key!=0 ; i--) {
        num=key%10;
        key=key/10;
        str[i]=num;
    }
    return str;
}

unsigned long long key_digits_2_long_int(short* keydigits){
    unsigned long long key=0;
    for (int i = 0; *(keydigits+i)!=-1 ; ++i) {
        key*=10;
        key+=*(keydigits+i);
    }
    return key;
}

unsigned long long calc_private_key_int(unsigned long long pubkey){
    return calc_private_key_char(pubkey);
}

unsigned long long calc_runlength_int(unsigned long long privkey){
    return calc_runlength_char(privkey);
}

unsigned long long private_key_from_runlength_int(unsigned long long runlengthkey){
    return private_key_from_runlength_char(runlengthkey);
}

short** alloc_matrix_int(int nlines, int ncolumns){
    short **mat ;

// aloca um vetor de LIN ponteiros para linhas
    mat = calloc (nlines+1, sizeof (short *)) ;

// aloca cada uma das linhas (vetores de COL inteiros)
    for (int i=0; i < nlines; i++){
        mat[i] = malloc(ncolumns * sizeof (int)) ;//sem problema
        for (int j = 0; j < ncolumns; ++j) {
            *(*(mat+i)+j)=-1;
        }
    }
    return mat;
}

short ** store_key_int(short **matrix, int *plines,int ncolumns, unsigned long long key){
    int length = Count_digitos_char(key);
    int n1=0,i=0,j=0,k=0;

    while(*(matrix+j)!=NULL && *(*(matrix+j)+0)!=-1){//    while(matrix[j]!=NULL && matrix[j][0]!='\0')
        j++;
    }
    if (j==*plines){
        //printf("Preciso fazer realloc j=%d\n",j);
        int oldSize=*plines;//10+1
        int newSize=*plines+15;//20
        matrix = realloc (matrix,(newSize+1)* sizeof (short*)) ;//o +1 corresponde a ultima posição a NULL
        for (k = oldSize; k < newSize; ++k) {
            *(matrix+k)= malloc(ncolumns * sizeof (int)) ;
            for (int j = 0; j < ncolumns; ++j) {
                *(*(matrix+k)+j)=-1;
            }
        }
        *(matrix+k)=NULL;
        *plines=newSize;

    }
    for (i = length-1; i != -1; --i) {
        n1=key%10;
        key/=10;
        *(*(matrix+j)+i)=n1;
    }

    return matrix;
}

int exists_key_int(short **matrix, int lines, unsigned long long key){

    int length = Count_digitos_char(key);
    char array[length];
    int n=0;
    for (int i = length-1; i != -1; --i) {
        n=key%10;
        key/=10;
        array[i]=n;
    }
    for (int i = 0; i < lines; ++i) {//linhas
        for (int j = 0; j < length; ++j) {//colunas
            if (matrix[i][j]!=array[j])
                break;
            if (j==length-1){
                //printf("%d\n",i);
                return i;
            }
        }
    }
    return -1;
}

unsigned long long get_private_key_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long pubkey){
    unsigned long long retorno=0;
    int posicao= exists_key_int(matrix_kpub,lines,pubkey);
    if (posicao!=-1){
        retorno= key_digits_2_long_int(*(matrix_kpriv+posicao));
    }
    return retorno;
}

unsigned long long get_runlength_int(short **matrix_kpriv, short **matrix_kcod, int lines, unsigned long long privkey){
    unsigned long long retorno=0;
    int posicao= exists_key_int(matrix_kpriv,lines,privkey);
    if (posicao!=-1){
        retorno= key_digits_2_long_int(*(matrix_kcod+posicao));
    }
    return retorno;
}

unsigned long long delete_key_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, short* pubkey){
    unsigned long long pubkeyint = key_digits_2_long_int(pubkey);
    printf("%llu ",pubkeyint);
    int posicao = exists_key_int(matrix_kpub, lines, pubkeyint);
    limpar_array_int(*(matrix_kpub+posicao));
    limpar_array_int(*(matrix_kpriv+posicao));
    limpar_array_int(*(matrix_kcod+posicao));
    return pubkeyint;
}
short** bulk_populate_public_keys_int(short **matrix_kpub, int *plines){
    //gerar chaves aleatorias, guardar string dinamica fazer o copy
    unsigned long long random =new_public_key_int();
    matrix_kpub=store_key_int(matrix_kpub, plines,20, random);
    return matrix_kpub;
}

short** bulk_compute_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int *plines){
    unsigned  long long number;
    unsigned  long long bipolar_number;
    for (int i = 0;*(matrix_kpub + i) != NULL; ++i) {
        if (*(*(matrix_kpub+ i) + 0) != -1) {
            number=key_digits_2_long_int(*(matrix_kpub+ i));
            bipolar_number=calc_private_key_int(number);
            matrix_kpriv=store_key_int(matrix_kpriv, plines,20, bipolar_number);
        }
    }
    return matrix_kpriv;
}
short** bulk_compute_runlengths_int(short **matrix_kpriv, short **matrix_kcod, int *plines){
    unsigned  long long number;
    unsigned  long long bipolar_run;
    for (int i = 0;*(matrix_kpriv + i) != NULL; ++i) {
        if (*(*(matrix_kpriv+ i) + 0) != -1) {
            number = key_digits_2_long_int(*(matrix_kpriv + i));//converter de string para llu
            //number=key_digits_2_long_char(matrix_kpriv+ i);
            bipolar_run = calc_runlength_int(number);
            matrix_kcod = store_key_int(matrix_kcod, plines, 20, bipolar_run);
        }
    }
    return matrix_kcod;
}
/*
short** search_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long partialpubkey){
    short* array = key_long_2_digits_int(partialpubkey);
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; *(*(matrix_kpub+i)+j)!=-1; ++j) {
            if (*(*(matrix_kpub+i)+j)==*(array+0)){
                for (int k = 0; *(array+k)!=-1 ; ++k) {
                    if(*(*(matrix_kpub+i)+j+k) == *(array+k)){
                        printf("top");
                    }
                }
            }
        }
    }

}*/

void sort_matrix_int(short **matrix, int lines, int order){
    unsigned long long arr[lines];
    for (int i = 0; i < lines; ++i) {
        arr[i]=key_digits_2_long_int(*(matrix+ i));
    }
    if (order==1){
        mergeSort(arr,lines);
    }else{
        for ( int i = 0 ; i < lines; i++)
        {
            for ( int j = i; j < lines; j++)
            {
                if (arr[i] < arr[j])
                {
                    unsigned long long aux= arr[i];
                    arr[i] = arr[j];
                    arr[j] = aux;
                }
            }
        }
    }

    limpa_matriz_int(matrix,lines);
    for (int i = 0; i < lines; ++i) {
        *(matrix+i)=key_long_2_digits_int(arr[i]);
    }

}
void sort_all_matrices_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int *plines, int order){
    sort_matrix_int(matrix_kpub,*plines,order);
    sort_matrix_int(matrix_kpriv,*plines,order);
    sort_matrix_int(matrix_kcod,*plines,order);
}

void list_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int *plines, int order){
    sort_matrix_int(matrix_kpub,*plines,order);
    limpa_matriz_int(matrix_kpriv,*plines);
    limpa_matriz_int(matrix_kcod,*plines);
    bulk_compute_private_keys_int(matrix_kpub, matrix_kpriv, &plines);
    bulk_compute_runlengths_int(matrix_kpriv, matrix_kcod, &plines);
}

void save_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]){
    FILE * fp;
    fp=fopen(filename,"w");
    if(fp!=NULL){
        fprintf(fp,"Number of keys:%d\n",lines);
        fprintf(fp,"ID PUB\t\t PRIV\t\t\t RUN\n");
        for (int i = 0; *(matrix_kpub + i) != NULL; i++) {
            unsigned long long pub =key_digits_2_long_int(*(matrix_kpub + i));
            unsigned long long priv =key_digits_2_long_int(*(matrix_kpriv+ i));
            unsigned long long run=key_digits_2_long_int(*(matrix_kcod+ i));
            fprintf(fp,"%d %llu\t\t %llu\t\t\t %llu\n",i,pub,priv,run);
        }
        fclose(fp);
    }else{
        printf("ERRO FICHEIRO");
    }
}

void load_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int *plines, char filename[]){
    FILE *fp;
    fp=fopen(filename,"r");
    if(fp!=NULL){
        fscanf(fp,"%*s %*s %*s\n");
        fscanf(fp,"%*s %*s\t\t %*s\t\t\t %*s\t\t\t\n");

        char pub[100],priv[100],run[100];
        int i2=0;
        //for(int i=0;i<1500;i++){
        //fscanf(fp,"%d %s\t %s\t %s\n",&i2,pub,priv,run);
        while ((fscanf(fp,"%d %s\t\t %s\t\t\t %s\n",&i2,pub,priv,run))!=EOF){
            unsigned long long numero = strtoul (pub, NULL, 10);
            unsigned long long numero1 = strtoul (priv, NULL, 10);
            unsigned long long numero2 = strtoul (run, NULL, 10);
            //printf("[%d] %llu %llu %llu\n",i,numero,numero1,numero2);
            matrix_kpub=store_key_int(matrix_kpub, plines,20, numero);
            matrix_kpriv=store_key_int(matrix_kpriv, plines,20, numero1);
            matrix_kcod=store_key_int(matrix_kcod, plines,20, numero2);
        }
        fclose(fp);

    }
}

void save_bin_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]){
    FILE *fp = fopen(filename, "wb");
    int size=0;
    if(fp != NULL){
        //printf("Ficheiro Aberto com sucesso\n");
    }else{
        printf("Erro Abertura Ficheiro Binario\n");
    }
    //gravar no arquivo
    for (int i = 0; i < lines; ++i) {
        //fprintf(fp,"%d %s\t\t %s\t\t\t %s\n",i,*(matrix_kpub + i),*(matrix_kpriv + i),*(matrix_kcod + i));
        unsigned long long pub =key_digits_2_long_int(*(matrix_kpub + i));
        unsigned long long priv =key_digits_2_long_int(*(matrix_kpriv+ i));
        unsigned long long run=key_digits_2_long_int(*(matrix_kcod+ i));

        fwrite(&pub , sizeof(unsigned long long) , 1, fp );
        fwrite(&priv , sizeof(unsigned long long) , 1 , fp );
        fwrite(&run , sizeof(unsigned long long) , 1 , fp );
    }

    fclose(fp);
}

void load_bin_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int *plines, char filename[]){
    FILE *fp = fopen(filename, "rb");
    if(fp == NULL){
        printf("ERRO ABERTURA BIN LOAD\n");
        return;
    }
    int size = 0;
    unsigned long long pub,priv,run;
    for (int i = 0; i < *plines; ++i) {//deveria ler o numero de chaves que vou ler
        fread(&pub, sizeof(unsigned long long), 1, fp);
        fread(&priv, sizeof(unsigned long long), 1, fp);
        fread(&run, sizeof(unsigned long long), 1, fp);
        matrix_kpub=store_key_int(matrix_kpub, plines,20, pub);
        matrix_kpriv=store_key_int(matrix_kpriv, plines,20, priv);
        matrix_kcod=store_key_int(matrix_kcod, plines,20, run);
    }
    fclose(fp);
}
int main_ints_part1(int argc, char *argv[]){
    srand(time(NULL));
    unsigned long long key =1111111222222222222;
    unsigned long long key3 =33;
    unsigned long long key2=0;
    printf("Numeros\n");
    PORTA_CHAVES_INT pint = {NULL,
                             NULL,
                             NULL,
                             15,
                             20
    };

    short *str=key_long_2_digits_int(key);
    printf("ULL to Array: ");
    for (int i = 0; i < pint.columns; ++i) {
        //printf("%d ", str[i]);
        printf("%d", *(str+i));
    }

    key2=key_digits_2_long_int(str);
    printf("\nArray to ULL %llu",key2);

    printf("\n%llu ",calc_private_key_int(key));
    printf("\n%llu ",calc_runlength_int(key));
    printf("\n%llu ",private_key_from_runlength_int(calc_runlength_int(key)));


    pint.matpubint=alloc_matrix_int(pint.lines, pint.columns);
    /*
    for (int i = 0; i < pint.lines; ++i) {
        pint.matpubint=bulk_populate_public_keys_int(pint.matpubint, &pint.lines);
    }
     */

    //pint.matprivint=store_key_int(pint.matprivint, &pint.lines,pint.columns, key);
    pint.matprivint=alloc_matrix_int(pint.lines, pint.columns);
    pint.matrunint=alloc_matrix_int(pint.lines, pint.columns);
/*
    pint.matprivint=bulk_compute_private_keys_int(pint.matpubint, pint.matprivint, &pint.lines);
    pint.matrunint=bulk_compute_runlengths_int(pint.matprivint, pint.matrunint, &pint.lines);
*/

/*
    unsigned long long key333 =5;
    short *str333= key_long_2_digits_int(key333);
    delete_key_int(pint.matpubint, pint.matprivint, pint.matrunint, pint.lines, str333);
*/
    //sort_matrix_int(pint.matpubint, pint.lines, 1);
    //sort_matrix_int(pint.matprivint, pint.lines, 1);
    //sort_matrix_int(pint.matrunint, pint.lines, 1);
    //sort_all_matrices_int(pint.matpubint, pint.matprivint, pint.matrunint, &pint.lines, 1);
    //list_keys_int(pint.matpubint, pint.matprivint, pint.matrunint, &pint.lines, 1);


    //save_txt_keys_int(pint.matpubint, pint.matprivint, pint.matrunint, pint.lines,"Chaveiro_int_15.txt");
    //load_txt_keys_int(pint.matpubint, pint.matprivint, pint.matrunint, &pint.lines,"Chaveiro_int_15.txt");
    //save_bin_keys_int(pint.matpubint, pint.matprivint, pint.matrunint, pint.lines,"Chaveiro_int_15.bin");
    load_bin_keys_int(pint.matpubint, pint.matprivint, pint.matrunint, &pint.lines,"Chaveiro_int_15.bin");

    //exists_key_int(pint.matpubint, pint.lines, key);

    printf("\nMatriz de chaves publicas\n");
    print_matriz_ints(pint.matpubint);
    printf("\nMatriz de chaves privadas\n");
    print_matriz_ints(pint.matprivint);
    printf("\nMatriz de chaves runlenght\n");
    print_matriz_ints(pint.matrunint);

    //search_private_keys_int(pint.matpubint, pint.matprivint,  pint.lines, 17);
    unsigned long long num1=65;
    //printf("%d\n",exists_key_int(pint.matpubint, pint.lines, num1));
    unsigned long long num2=get_private_key_int(pint.matpubint, pint.matprivint, pint.lines, num1);
    unsigned long long num3=get_runlength_int(pint.matprivint, pint.matrunint, pint.lines, num2);

   // printf("%llu - %llu - %llu\n",num1,num2,num3);


    //printf("%llu\n",new_public_key_int());
    //key=new_public_key_int();
    //printf("%llu", calc_private_key_char(key));


    return 0;
}