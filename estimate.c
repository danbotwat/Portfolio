#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void multiplyMatrix(int nRx, int nCxRy, int nCy, double **result, double **x, double **y){
    for(int i =0; i < nRx; i++){
        for(int j =0; j<nCy; j++){
            result[i][j] = 0; //set result matrix equal to 0
            for(int h = 0; h< nCxRy; h++){
                result[i][j] += y[h][j] * x[i][h] ;
            }
        }
    }
}


void transposeMatrix(int n, int k, double **xTran, double **x){
    for(int i =0; i < n; i++){
    for(int j =0; j < k; j++){
            xTran[j][i] = x[i][j];
        }
    }
}

void createIdentityMatrix(int s, double **result) {
    for(int i =0; i < s; i++){
        for(int j =0; j < s; j++){
            if(i!=j){
                result[i][j] = 0.0;
            }
            else{
                result[i][j] = 1.0;
            }
        }
    }
}
void invertMatrix(int s, double **result, double **original){

    createIdentityMatrix(s,result);

    for(int h = 0; h<s; h++){
        double k = original[h][h];
        for(int i =0; i < s; i++){
            original[h][i]/=k;
            result[h][i]/=k;
        }

        for(int i =0; i < s; i++){
            if(h != i){
                k = original[i][h];
                for(int j =0; j < s; j++){
                    result[i][j] -= result[h][j] *k;
                    original[i][j] -= original[h][j] *k;
                }
            }
        }
    }
}
int main(int argc, char *argv[]){

    FILE *tfile = fopen(argv[1], "r");
    FILE *dfile = fopen(argv[2], "r");
    int k,n,m;
    char wrd[6]=""; 

    fscanf(tfile,"%5s", wrd);
    fscanf(dfile,"%5s", wrd);

    fscanf(dfile,"%d", &k);
    fscanf(dfile,"%d", &m); 

    fscanf(tfile, "%d", &k);
    fscanf(tfile, "%d", &n);

    double **X = malloc(n * sizeof(double *));
    double **Y = malloc(n * sizeof(double *));
        for (int i = 0; i < n; i++) {
            X[i] = malloc((k + 1) * sizeof(double));
            Y[i] = malloc((1)*sizeof(double));
            X[i][0] = 1.0;
            for(int j = 1; j <= k; j++){
                fscanf(tfile, "%lf", &X[i][j]);
            }
            fscanf(tfile, "%lf", &Y[i][0]);
        }
   
    double **transposeX = malloc((k+1) * sizeof(double *));
    double **squareResult = malloc((k+1) * sizeof(double *));
    double **invertedResult = malloc((k+1) * sizeof(double *));
    double **W = malloc((k+1) * sizeof(double *));
    double **invertbyTranspose = malloc((k+1) * sizeof(double *));

    for (int i = 0; i < k+1; i++) {
        transposeX[i] = malloc((n) * sizeof(double));
        squareResult[i] = malloc((k+1) * sizeof(double));
        invertedResult[i] = malloc((k+1) * sizeof(double));
        W[i] = malloc(sizeof(double));
        invertbyTranspose[i] = malloc((n) * sizeof(double));
    }

    double **newX = malloc(m * sizeof(double *));
    double **finalPrices = malloc(m * sizeof(double *));

    for (int i = 0; i < m; i++) {
        newX[i] = malloc((k + 1) * sizeof(double));
        finalPrices[i] = malloc(sizeof(double));
        newX[i][0] = 1.0;
        for(int j =1; j <= k; j++){
    
        fscanf(dfile,"%lf", &newX[i][j]);
        
        }

    }

    transposeMatrix(n, k+1, transposeX, X); 
    multiplyMatrix(k+1,n,k+1,squareResult,transposeX,X);   
    (invertMatrix(k+1,invertedResult,squareResult));
    multiplyMatrix(k+1,k+1,n,invertbyTranspose,invertedResult,transposeX);
    multiplyMatrix(k+1,n,1,W,invertbyTranspose,Y);
    multiplyMatrix(m,k+1,1,finalPrices,newX,W);

    for (int i = 0; i < m; i++) {
    printf("%.0f\n", finalPrices[i][0]);      
    }

    for (int i = 0; i < n; i++) {
    free(X[i]);
    free(Y[i]);
    }
    free(X);
    free(Y);

    for (int i = 0; i < k; i++) {
    free(transposeX[i]);
    }
    free(transposeX);

    for (int i = 0; i < m; i++) {
    free(newX[i]);
    free(finalPrices[i]);
    }
    free(newX);
    free(finalPrices);


    return 0;

}