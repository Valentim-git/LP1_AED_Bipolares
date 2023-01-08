//
// Created by João Valentim on 23/11/2022.
//

#include "aed_lp1_2023_proj_part1_chars.h"
#include "aed_lp1_2023_proj_part1_ints.h"
char* itoa(int num, char* buffer, int base){
    int current = 0;
    if (num == 0) {
        buffer[current++] = '0';
        buffer[current] = '\0';
        return buffer;
    }
    int num_digits = 0;
    if (num < 0) {
        if (base == 10) {
            num_digits ++;
            buffer[current] = '-';
            current ++;
            num *= -1;
        }
        else
            return NULL;
    }
    num_digits += (int)floor(log(num) / log(base)) + 1;
    while (current < num_digits)
    {
        int base_val = (int) pow(base, num_digits-1-current);
        int num_val = num / base_val;
        char value = num_val + '0';
        buffer[current] = value;
        current ++;
        num -= base_val * num_val;
    }
    buffer[current] = '\0';
    return buffer;
}

unsigned long long verifica_bipolar(char *text){
    char ultimo;
    int boolean=0;
    for (int i = 0; i < text[i]!='\0'; ++i) // verifica se e numero
        if(text [i] < '0' || text [i] > '9')return -2;
    for (int i = 0;text[i]!='\0'; ++i) {
        if (i==0)ultimo=text[i];
        if(boolean==0){
            if (text[i]==ultimo){
                continue;
            }else{
                boolean=1;
                ultimo=text[i];
            }
        }else if(text[i]!=ultimo)return -1;

    }
    if (boolean==0)return -1;
    return atoi(text);
}

unsigned long long calc_private_key_char_2(unsigned long long num){
    unsigned long long mult=0;
    char snum[100];
    unsigned long long retorno=0;
    int i=2;
    int chama =0;
    while (1) {
        mult=num*i;
        itoa(mult, snum, 10);
        retorno=verifica_bipolar(snum);
        if (retorno!=-1){
            //printf("%d * %d = %llu\n",num,i,mult);
            //printf("%llu\n",mult);
            return retorno;
        }
        i++;
    }
    return -1;

}
int isSorted(unsigned long long arr[], int size) {

    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return -1;
        }

    }
    return 1;
}

int merge(unsigned long long a[], unsigned long long aux[], int lo, int mid, int hi) {

    for (int k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    int i = lo;
    int j = mid + 1;

    for (int k = lo; k <= hi; k++) {
        if (i > mid) a[k] = aux[j++];
        else if (j > hi) a[k] = aux[i++];
        else if (aux[j] < aux[i]) a[k] = aux[j++];
        else a[k] = aux[i++];
    }

}

void sort(unsigned long long a[], unsigned long long aux[], int lo, int hi) {
    if (hi <= lo) return;
    int mid = lo + (hi - lo) / 2;
    sort(a, aux, lo, mid);
    sort(a, aux, mid + 1, hi);
    merge(a, aux, lo, mid, hi);
}

void mergeSort(unsigned long long a[],int size){
    unsigned long long aux[size];
    sort(a, aux, 0, size - 1);
}

void limpa_matriz_chars(char **matrix, int lines){
    for (int k = 0; k < lines; ++k) {
        *(matrix+k)= calloc(20,sizeof (char));
    }
}

int Count_digitos_char (unsigned long long key){///poderei usar apenas int
    unsigned long long count =0;
    while (key != 0){
        count++;
        key /= 10;
    }
    return count;
}

void print_matriz_chars(char **matrix) {
    printf("\n-------MATRIZ------\n");
    for (int i = 0; *(matrix + i) != NULL; i++) {//i < nlines

        printf("[%d] = %s\n", i, *(matrix + i));
    }
    printf("\n-------MATRIZ------\n");
}


char* key_long_2_digits_char(unsigned long long key){
    int length = Count_digitos_char(key);
    char* str = malloc( length + 1 );
    snprintf( str, length + 1, "%llu", key );//tinha %d e estava a correr mal
    /*if (str[length]=='\0'){
        printf("top\n");
    }*///analisar se tem caracter nulo \0; TEM!!!
    return str;
}

unsigned long long key_digits_2_long_char(char* keydigits){
    unsigned long long x = strtoul (keydigits, NULL, 10);//o atoi nao dava porque trata apenas numeros inteiros com sinal e estourava aos 9 digitos
    return x;
}

unsigned long long calc_private_key_char(unsigned long long pubkey){
    unsigned long long nmbip=0;
    for (int k = 2; k < 100; ++k) {
        int bipolar[k];
        for (int i = 1; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                for (int l = 0; l < k; ++l)
                    bipolar[l]=i;
                if (i!=j){
                    for (int l = k-1; l > 0; --l) {
                        bipolar[l]=j;
                        //array to unsigned long long
                        for(int m=0;m<k;m++){
                            nmbip= nmbip*10 + bipolar[m];
                        }
                        if (nmbip!=pubkey){
                            //verifica se e multiplo
                            if (nmbip%pubkey==0){
                                return nmbip;
                            }
                        }
                        nmbip=0;
                    }
                }
            }
        }
    }
    return 0;
}

unsigned long long calc_runlength_char(unsigned long long privkey){
    unsigned long long retorno=0;
    int runpriv[4]={1,2,3,4};
    int count = 0,numero=0,numero2;
    numero=privkey%10;
    numero2=numero;
    while(numero2==numero){
        numero2=privkey%10;
        privkey/=10;
        count++;
    }
    runpriv[0]=count-1;
    count=1;
    runpriv[1]=numero;

    while(privkey!=0){
        numero2=privkey%10;
        privkey/=10;
        count ++;
    }
    runpriv[2]=count;
    runpriv[3]=numero2;

    retorno = runpriv[2];
    retorno *= 10;
    retorno += runpriv[3];
    retorno *= 10;
    retorno += runpriv[0];
    retorno *= 10;
    retorno += runpriv[1];

    return retorno;
}

unsigned long long private_key_from_runlength_char(unsigned long long runlengthkey){
    int array[4];
    unsigned long long Bipolar=0;
    array[3]=runlengthkey%10;
    runlengthkey /= 10;
    array[2]=runlengthkey%10;
    runlengthkey/=10;
    array[1]=runlengthkey%10;
    runlengthkey/=10;
    array[0]=runlengthkey;


    for (int i = 0; i < array[0]; ++i) {
        Bipolar+=array[1];
        Bipolar*=10;
    }
    for (int i = 0; i < array[2]; i++) {
        Bipolar+=array[3];
        if (i!=array[2]-1)
        Bipolar*=10;
    }
    return Bipolar;
}

char** alloc_matrix_char(int nlines, int ncolumns){
    char **mat ;

// aloca um vetor de LIN ponteiros para linhas
    mat = calloc (nlines+1, sizeof (char*)) ;
//10 0 1 2 3 4 5 6 7 8 9 NULL
// aloca cada uma das linhas (vetores de COL inteiros)
    for (int i=0; i < nlines; i++){
        mat[i] = calloc (ncolumns , sizeof (char)) ;//sem problema
    }
    return mat;
}

char ** store_key_char(char **matrix, int *plines,int ncolumns, unsigned long long key){
    int length = Count_digitos_char(key);
    int n1=0,i=0,j=0,k=0;

    while(*(matrix+j)!=NULL && *(*(matrix+j)+0)!='\0'){//    while(matrix[j]!=NULL && matrix[j][0]!='\0')
        j++;
    }
    if (j==*plines){
        printf("Preciso fazer realloc j=%d\n",j);
        int oldSize=*plines;//10+1
        int newSize=*plines+15;//20
        matrix = realloc (matrix,(newSize+1)* sizeof (char*)) ;//o +1 corresponde a ultima posição a NULL
        for (k = oldSize; k < newSize; ++k) {
            *(matrix+k)= calloc(ncolumns,sizeof (char));
        }
        *(matrix+k)=NULL;
        *plines=newSize;

    }
        for (i = length-1; i != -1; --i) {
            n1=key%10;
            key/=10;
            *(*(matrix+j)+i)='0'+n1;
        }

    return matrix;
}

int exists_key_char(char **matrix, int lines, unsigned long long key){
    int length = Count_digitos_char(key);
    char array[length];
    char digito[2];
    int n=0;
    for (int i = length-1; i != -1; --i) {
        n=key%10;
        key/=10;
        itoa(n,digito,10);
        array[i]=digito[0];
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

unsigned long long get_private_key_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long pubkey){
    unsigned long long retorno=0;
    int posicao= exists_key_char(matrix_kpub,lines,pubkey);
    if (posicao!=-1){
        retorno= key_digits_2_long_char(*(matrix_kpriv+posicao));
    }
    return retorno;
}

unsigned long long get_runlength_char(char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long privkey){
    unsigned long long retorno=0;
    int posicao= exists_key_char(matrix_kpriv,lines,privkey);
    if (posicao!=-1){
        retorno= key_digits_2_long_char(*(matrix_kcod+posicao));
    }
    return retorno;
}

unsigned long long delete_key_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char* pubkey){
    unsigned long long pubkeyint = key_digits_2_long_char(pubkey);
    printf("%llu ",pubkeyint);
    int posicao = exists_key_char(matrix_kpub, lines, pubkeyint);
    *(matrix_kpub+posicao)= calloc(20,sizeof (char));
    *(matrix_kpriv+posicao)= calloc(20,sizeof (char));
    *(matrix_kcod+posicao)= calloc(20,sizeof (char));
    return pubkeyint;
}

char ** bulk_populate_public_keys_char(char **matrix_kpub, int *plines){
    //gerar chaves aleatorias, guardar string dinamica fazer o copy
        unsigned long long random =new_public_key_int();
        matrix_kpub=store_key_char(matrix_kpub, plines,20, random);
    return matrix_kpub;
}

char ** bulk_compute_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int *plines){
    unsigned  long long number;
    unsigned  long long bipolar_number;
    for (int i = 0; i < *(matrix_kpub + i) != NULL; ++i) {
        if (*(*(matrix_kpub+ i) + 0) != '\0') {
            number=key_digits_2_long_char(*(matrix_kpub+ i));//converter de string para llu
            bipolar_number=calc_private_key_char(number);
            matrix_kpriv=store_key_char(matrix_kpriv, plines,20, bipolar_number);
        }
    }
    return matrix_kpriv;
}

char ** bulk_compute_runlengths_char(char **matrix_kpriv, char **matrix_kcod, int *plines){
    unsigned  long long number;
    unsigned  long long bipolar_run;
    for (int i = 0; i < *(matrix_kpriv + i) != NULL; ++i) {
        if (*(*(matrix_kpriv+ i) + 0) != '\0') {
            number = key_digits_2_long_char(*(matrix_kpriv + i));//converter de string para llu
            //number=key_digits_2_long_char(matrix_kpriv+ i);
            bipolar_run = calc_runlength_char(number);
            matrix_kcod = store_key_char(matrix_kcod, plines, 20, bipolar_run);
        }
    }
    return matrix_kcod;
}

char** search_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long partialpubkey){
    char *ret;
    int nd=0;
    int posicao=1;
    unsigned long long num=0;

    char* partialkey=key_long_2_digits_char(partialpubkey);

    for (int i = 0; i < lines; ++i) {
        ret = strstr(*(matrix_kpub+i), partialkey);
        if (ret!=NULL){
            nd++;
        }
    }
    unsigned long long  *arr = (unsigned long long *) calloc (nd, sizeof(unsigned long long));
    arr[0]=nd;
    for (int i = 0; i < lines; ++i) {
        ret = strstr(*(matrix_kpub+i), partialkey);
        if (ret!=NULL){
            //printf("%s\n",*(matrix_kpriv+i));
            num = key_digits_2_long_char(*(matrix_kpriv+i));
            arr[posicao]=num;
            posicao++;
        }
    }
    return arr;

}


void sort_matrix_char(char **matrix, int lines, int order){
    unsigned long long arr[lines];
    for (int i = 0; i < lines; ++i) {
        arr[i]=key_digits_2_long_char(*(matrix+ i));
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

    limpa_matriz_chars(matrix,lines);
    for (int i = 0; i < lines; ++i) {
        *(matrix+i)=key_long_2_digits_char(arr[i]);
    }

}

void sort_all_matrices_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int *plines, int order){
    sort_matrix_char(matrix_kpub,*plines,order);
    sort_matrix_char(matrix_kpriv,*plines,order);
    sort_matrix_char(matrix_kcod,*plines,order);
}

void list_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int *plines, int order){
    sort_matrix_char(matrix_kpub,*plines,order);
    limpa_matriz_chars(matrix_kpriv,*plines);
    limpa_matriz_chars(matrix_kcod,*plines);
    bulk_compute_private_keys_char(matrix_kpub, matrix_kpriv, &plines);
    bulk_compute_runlengths_char(matrix_kpriv, matrix_kcod, &plines);
}

void save_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    FILE * fp;
    fp=fopen(filename,"w");
    if(fp!=NULL){
        fprintf(fp,"Number of keys:%d\n",lines);
        fprintf(fp,"ID PUB\t\t PRIV\t\t\t RUN\n");
        for (int i = 0; *(matrix_kpub + i) != NULL; i++) {
            fprintf(fp,"%d %s\t\t %s\t\t\t %s\n",i,*(matrix_kpub + i),*(matrix_kpriv + i),*(matrix_kcod + i));
        }
        fclose(fp);
    }else{
        printf("ERRO FICHEIRO");
    }
}

void load_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int *plines, char filename[]){
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
            matrix_kpub=store_key_char(matrix_kpub, plines,20, numero);
            matrix_kpriv=store_key_char(matrix_kpriv, plines,20, numero1);
            matrix_kcod=store_key_char(matrix_kcod, plines,20, numero2);
        }
        fclose(fp);

    }
}

void save_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
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
        size=sizeof(*(matrix_kpub + i)+1);
        fwrite(&size, sizeof(int), 1, fp);
        fwrite(*(matrix_kpub + i) , 1 , size, fp );

        size=sizeof(*(matrix_kpriv + i)+1);
        fwrite(&size, sizeof(int), 1, fp);
        fwrite(*(matrix_kpriv + i) , 1 , size , fp );

        size=sizeof(*(matrix_kcod + i)+1);
        fwrite(&size, sizeof(int), 1, fp);
        fwrite(*(matrix_kcod + i) , 1 , size , fp );
    }

    fclose(fp);
}

void load_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int *plines, char filename[]){
    FILE *fp = fopen(filename, "rb");
    if(fp == NULL){
        printf("ERRO ABERTURA BIN LOAD\n");
        return;
    }
    int size = 0;
    char pub[100],priv[100],run[100];
    for (int i = 0; i < *plines; ++i) {//deveria ler o numero de chaves que vou ler
        fread(&size, sizeof(int), 1, fp);
        fread(pub, sizeof(char), size, fp);
        fread(&size, sizeof(int), 1, fp);
        fread(priv, sizeof(char), size, fp);
        fread(&size, sizeof(int), 1, fp);
        fread(run, sizeof(char), size, fp);
        unsigned long long numero = strtoul (pub, NULL, 10);
        unsigned long long numero1 = strtoul (priv, NULL, 10);
        unsigned long long numero2 = strtoul (run, NULL, 10);
        matrix_kpub=store_key_char(matrix_kpub, plines,20, numero);
        matrix_kpriv=store_key_char(matrix_kpriv, plines,20, numero1);
        matrix_kcod=store_key_char(matrix_kcod, plines,20, numero2);
    }
    fclose(fp);
}

int main_chars_part1(int argc, char *argv[]){
    printf("Caracteres\n");
    srand(time(NULL));
    PORTA_CHAVES_CHAR pchar = {NULL,
                       NULL,
                       NULL,
                       150,
                       20
    };


    //Mostra uam diferenca absurda 3383
    unsigned long long pubKey =3383;
    printf("-------------------------------\n");
    clock_t ini = clock(); // guardas o inicial
    printf("%llu -> %llu\n",pubKey,calc_private_key_char(pubKey));
    printf("%.1f Microsegundos pelos bipolares consecutivos\n", (((double)clock() - ini) / CLOCKS_PER_SEC)*1000000);
    clock_t ini1 = clock(); // guardas o inicial
    printf("%llu -> %llu\n",pubKey,calc_private_key_char_2(pubKey));
    printf("%.1f Microsegundos pela multiplicacao sucessiva\n", (((double)clock() - ini1) / CLOCKS_PER_SEC)*1000000);
    printf("-------------------------------\n");


    unsigned long long key =22222333333333;
    unsigned long long key22 =212;
    unsigned long long key222 =588;
    unsigned long long Runkey=0;
    unsigned long long newKey=0;

    key_long_2_digits_char(key);
    char *str= key_long_2_digits_char(key);
    char *str22= key_long_2_digits_char(key22);
    char *str222= key_long_2_digits_char(key222);
    printf("ULL INSERIDA: %llu\n",key);
    printf("ULL EM STRING: %s\n",str);

    unsigned long long key2= key_digits_2_long_char(str);
    printf("STRING EM ULL: %llu\n",key2);

    //printf("\n%llu\n",calc_private_key_char(2013));

    Runkey=calc_runlength_char(key);
    printf("RUNLENGHT DE %llu -> %llu\n",key,Runkey);

    newKey=private_key_from_runlength_char(Runkey);
    printf("PRIVKEY DE %llu -> %LLU\n",Runkey,newKey);
    printf("-------------------------------\n");


    pchar.matpubchar = alloc_matrix_char(pchar.lines, pchar.columns);

    for (int i = 0; i <pchar.lines; ++i) {
        pchar.matpubchar=bulk_populate_public_keys_char(pchar.matpubchar, &pchar.lines);
    }

    //printf("Matriz de chaves publicas");
    //print_matriz_chars(p.matpubchar);

    pchar.matprivchar = alloc_matrix_char(pchar.lines, pchar.columns);
    pchar.matrunchar = alloc_matrix_char(pchar.lines, pchar.columns);

    pchar.matprivchar=bulk_compute_private_keys_char(pchar.matpubchar, pchar.matprivchar, &pchar.lines);
    pchar.matrunchar=bulk_compute_runlengths_char(pchar.matprivchar, pchar.matrunchar, &pchar.lines);

    /*
    printf("Matriz de chaves publicas");
    print_matriz_chars(pchar.matpubchar);
    printf("Matriz de chaves privadas");
    print_matriz_chars(pchar.matprivchar);
    printf("Matriz de chaves runlenght");
    print_matriz_chars(pchar.matrunchar);
     */

    //get_private_key_char(p.matpubchar, p.matprivchar, p.lines, 6);

    //delete_key_char(pchar.matpubchar, pchar.matprivchar, pchar.matrunchar, pchar.lines, str22);
    //delete_key_char(pchar.matpubchar, pchar.matprivchar, pchar.matrunchar, pchar.lines, str222);

    /*
    printf("Matriz de chaves publicas");
    print_matriz_chars(pchar.matpubchar);
    printf("Matriz de chaves privadas");
    print_matriz_chars(pchar.matprivchar);
    printf("Matriz de chaves runlenght");
    print_matriz_chars(pchar.matrunchar);
     */

    //save_txt_keys_char(pchar.matpubchar, pchar.matprivchar, pchar.matrunchar, pchar.lines, "./Chaveiro_char_15.txt");
    //save_bin_keys_char(pchar.matpubchar, pchar.matprivchar, pchar.matrunchar, pchar.lines, "Chaveiro_char_15.bin");
    //load_txt_keys_char(pchar.matpubchar, pchar.matprivchar, pchar.matrunchar, &pchar.lines, "Chaveiro_char.txt");
    //load_bin_keys_char(pchar.matpubchar, pchar.matprivchar, pchar.matrunchar, &pchar.lines, "Chaveiro_char_15.bin");

    //sort_matrix_char(pchar.matpubchar, pchar.lines, 1);
    //sort_matrix_char(pchar.matprivchar, pchar.lines, 1);
    //sort_matrix_char(pchar.matrunchar, pchar.lines, 1);
/*
    printf("Matriz de chaves publicas");
    print_matriz_chars(pchar.matpubchar);
    printf("Matriz de chaves privadas");
    print_matriz_chars(pchar.matprivchar);
    printf("Matriz de chaves runlenght");
    print_matriz_chars(pchar.matrunchar);
*/

    //sort_all_matrices_char(pchar.matpubchar, pchar.matprivchar, pchar.matrunchar, &pchar.lines, 1);
    list_keys_char(pchar.matpubchar, pchar.matprivchar, pchar.matrunchar, &pchar.lines, 1);
    unsigned long long chave_publica=1;
    //printf("%d \n", exists_key_char(pchar.matpubchar,pchar.lines,chave_publica));
    unsigned long long chave_privada=get_private_key_char(pchar.matpubchar, pchar.matprivchar, pchar.lines, chave_publica);
    unsigned long long chave_codificada=get_runlength_char(pchar.matprivchar, pchar.matrunchar, pchar.lines, chave_privada);
    printf("%llu e a chave privada de %llu \n",chave_privada,chave_publica);
    printf("%llu e a chave codificada de %llu \n",chave_codificada,chave_privada);
    //unsigned long long get_private_key_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long pubkey);
    //unsigned long long get_runlength_char(char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long privkey);
    printf("Matriz de chaves publicas");
    print_matriz_chars(pchar.matpubchar);
    printf("Matriz de chaves privadas");
    print_matriz_chars(pchar.matprivchar);
    printf("Matriz de chaves runlenght");
    print_matriz_chars(pchar.matrunchar);

    unsigned long long* strsearch=search_private_keys_char(pchar.matpubchar, pchar.matprivchar, pchar.lines, 33);
    for (int i = 1; i < *(strsearch+0)+1; ++i) {
        printf("%llu \n", *(strsearch+i));
    }
    return 0;
}