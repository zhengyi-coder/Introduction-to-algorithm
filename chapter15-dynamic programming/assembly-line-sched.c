#include <stdio.h>
#include <stdlib.h>

//a1, a2 are the assemble time at station in line1 and line2
//t1, t2 are the transfer time between lines
//e is the time of entrying to the line
//x is the time of leaving from the line
//n is the number of stations in a line
//l1, l2 are to record path 
//value is the ultimate optimal time

int fastest_way(int *a1, int *a2, int *t1, int *t2, int *e, int *x, int n, int *l1, int *l2, int *value){
        int *f1 = (int *)malloc(n*sizeof(int));
        int *f2 = (int *)malloc(n*sizeof(int));

        //initial status of f1, f2
        f1[0] = e[0] + a1[0];
        f2[0] = e[1] + a2[0];

        //calculate subproblem 
        for(int i = 1; i < n; i++){
                if(f1[i-1] < (f2[i-1] + t2[i-1])){
                        f1[i] = f1[i-1] + a1[i];
                        l1[i-1] = 1;
                }else{
                        f1[i] = f2[i-1] + t2[i-1] + a1[i];
                        l1[i-1] = 2;
                }

                if(f2[i-1] < (f1[i-1] + t1[i-1])){
                        f2[i] = f2[i-1] + a2[i];
                        l2[i-1] = 2;
                }else{
                        f2[i] = f1[i-1] + t1[i-1] + a2[i];
                        l2[i-1] = 1;
                }
        }
		if((f1[n-1] + x[0]) < (f2[n-1]+ x[1])){
                *value = f1[n-1] + x[0];
                return 1;
        }else{
                *value = f2[n-1] + x[1];
                return 2;
        }
}

void print_stations(int *l1, int *l2, int way, int n){
        printf("line %d, station %d\n", way, n);
        for(int i = n-2; i >= 0; i--){
                if(way == 1)
                        way = l1[i];
                else
                        way = l2[i];
                printf("line %d, station %d\n", way, i+1);
        }
}

void print_stations_2(int *l1, int *l2, int way, int n){
        printf("line %d, station %d\n", way, n);
        if(n >= 2){
                if(way == 1)
                        way = l1[n-2];
                else
                        way = l2[n-2];//n-2 >= 0 should be ensured
                //if(n >= 2) //could be placed here
                print_stations_2(l1, l2, way, n-1);
        }
}




void reverse_print_stations(int *l1, int *l2, int way, int n){
        int tmp;
        if(n >= 2){
                if(way == 1)
                        tmp = l1[n-2];
                else
                        tmp = l2[n-2];
                reverse_print_stations(l1, l2, tmp, n-1);
        }
        printf("line %d, station %d\n", way, n);
}


int main()
{
        int n = 6;
        int e[2] = {2, 4};
        int x[2] = {3, 2};

        int t1[5] = {2, 3, 1, 3, 4};
        int t2[5] = {2, 1, 2, 2, 1};

        int a1[6] = {7, 9, 3, 4, 8, 4};
        int a2[6] = {8, 5, 6, 4, 5, 7};

        int value;
        int *l1 = (int *)malloc((n-1)*sizeof(int));
        int *l2 = (int *)malloc((n-1)*sizeof(int));
        int way = fastest_way(a1, a2, t1, t2, e, x, n, l1, l2, &value);
        printf("value = %d\n", value);
        reverse_print_stations(l1, l2, way, n);

        return 0;
}
