#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//if the number of the matrix chain is n, the dimension is n+1
//when using a array or matrix in child function, better pass the dimension value to child function
//in child function, the m[i][i] could not be used, using *((int *)m + n*i +i) to replace m[i][i]
void matrix_chain_order(int *p, int n, int **m, int **s){
        int dimension = n+1;
        for(int i = 1; i <= n; i++)
                *((int *)m + dimension*i + i) = 0;
    
        //2 loops are used to traverse m[i][j]
        //1 loop is used to select 
        //time complexity is O(n^3)
        //space complexity is O(n^2)
    
        for(int l = 2; l <= n; l++){
                for(int i = 1; i <= (n-l+1);i++){
                        int j = i+l-1;
                        *((int *)m + dimension*i + j) = INT_MAX;
                        int k;
                        for(k = i; k <= (j-1); k++){
                                int tmp1 = *((int *)m + dimension*i + k); 
                                int tmp2 = *((int *)m + dimension*(k+1) + j); 
                                int tmp = tmp1 + tmp2 +p[i-1]*p[k]*p[j];
    
                                if(tmp < *((int *)m + dimension*i + j)){
                                        *((int *)m + dimension*i +j) = tmp;
                                        *((int *)s + dimension*i +j) = k;
                                }   
                        }   
                }   
        }   
}


void print_optimal_parens(int **s, int i, int j, int dimension){
        if(i == j)
                printf("A%d", i); 
        else{
                printf("(");
                print_optimal_parens(s, i, *((int *)s + dimension*i + j), dimension);
                print_optimal_parens(s, *((int *)s + dimension*i +j)+1, j, dimension);
                printf(")");
        }
}


int main()
{
        int n = 6;
        int p[] = {30, 35, 15, 5, 10, 20, 25};

        int m[n+1][n+1];
        int s[n+1][n+1];

        matrix_chain_order(p, n, (int **)m, (int **)s);

        for(int i = 1; i <= n; i++){
                for(int j = i; j <= n; j++)
                        printf("%d ,", m[i][j]);
                printf("\n");
        }
        print_optimal_parens((int **)s, 1, 6, 7);

        return 0;
}
                                                                                               67,1          Bot
