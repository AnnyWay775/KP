#include <stdio.h>
void proc(struct complex** mtrx, int v, int a, int b);
void prsh(struct complex* a, int* ind1, int* ind2, int k);
void prf(struct complex** matrix, int v);
void shtof(struct complex* a1, int* ind1, int* ind2, int k, struct complex** mtrx, int m);

struct complex {
    float real;
    float img;
};

int main()
{
	struct complex **mtrx, *a1, *a3;

	int *ind1, *ind2, *ind31, *ind32, a, b, m, n, k, l, p, t, i, j, check, result;

	scanf("%d", &m);
	printf("Кол-во строк/столбцов матрицы: %d \n", m);

    mtrx = new struct complex*[m];
    for (i = 0; i < m; i++) {
        mtrx[i] = new struct complex[m];
    }

    scanf("%d", &k);
    printf("Кол-во ненулевых эл-тов = %d \n", k);
    check = k;
    a1 = new complex[k];
    ind1 = new int[k];
    ind2 = new int[k];

    for (i = 0; i < k+2; i++) {
    	scanf("%d", &l);
    	if (l==0) {
    		scanf("%d", &p);
    		if (p==0) break;
    		else {
    			ind1[i]=p-1;
    			scanf("%d", &t);
    			ind2[i]=t-1;
    			scanf("%f", &a1[i].real);
        		scanf("%f", &a1[i].img);
    		}    		
    	}
    	else {
    		ind1[i]=ind1[i-1];
    		ind2[i]=l-1;
    		scanf("%f", &a1[i].real);
        	scanf("%f", &a1[i].img);
    	}
    }

	shtof(a1, ind1, ind2, k, mtrx, m);
	prf(mtrx, m);
	prsh(a1, ind1, ind2, k);
	scanf("%d", &a);
	printf("Множитель а: %d \n", a);
	scanf("%d", &b);
	printf("Множитель b: %d \n", b);
	proc(mtrx, m,  a, b);

}


void prf(struct complex** mtrx, int v)
{
    int i, j;
    printf("\nПолное представление:\n");
    for (i = 0; i < v; i++) {
        printf("\n");
        for (j = 0; j < v; j++) {
            if (mtrx[i][j].real == 0 && mtrx[i][j].img == 0) {
                printf("%8d        ", 0);
            }
            else if (mtrx[i][j].img < 0) {
                mtrx[i][j].img *= -1;
                printf("%5.1f -%5.1fi   ", mtrx[i][j].real, mtrx[i][j].img);
                mtrx[i][j].img *= -1;
            }
            else
                printf("%5.1f +%5.1fi   ", mtrx[i][j].real, mtrx[i][j].img);
        }
         printf("\n");
    }
}

void shtof(struct complex* a, int* ind1, int* ind2, int k, struct complex** mtrx, int m)
{
    int i, j, l;
    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++) {
            mtrx[i][j].img = 0;
            mtrx[i][j].real = 0;
        }
    for (l = 0; l < k; l++) {
        i = ind1[l];
        j = ind2[l];
        mtrx[i][j].real = a[l].real;
        mtrx[i][j].img = a[l].img;
    }
}

void prsh(struct complex* a, int* ind1, int* ind2, int k)
{
    int i, t=0;
    printf("\nСокращенное представление:\n");
    printf("0 ");
    for (i = 0; i < k; i++) {
    	if(ind1[i]!=t) {
    		printf("0 %d ", ind1[i]+1); t++;
    	}
    	else if (ind1[i]==0) printf("%d ", ind1[i]+1);
    	printf("%d ", ind2[i]+1);
        if (a[i].img < 0) {
            a[i].img *= -1;
            printf("%4.1f-%2.1fi  ", a[i].real, a[i].img);
            a[i].img *= -1;
        }
        else
            printf("%4.1f+%2.1fi  ", a[i].real, a[i].img);
    }
    printf("0 0\n");
}

void proc(struct complex** mtrx, int v, int a, int b)
{
    int i, j;
    printf("\nПолное представление:\n");
    for (i = 0; i < v; i++) {
        printf("\n");
        for (j = 0; j < v; j++) {
        	        	if(i==j) {
        	        			mtrx[i][j].real *= a;
        	        		mtrx[i][j].real += b;
        						mtrx[i][j].img *= a;
        	        		
        	        		if (mtrx[i][j].real == 0 && mtrx[i][j].img == 0) {
                printf("%8d        ", 0);
            }
            else if (mtrx[i][j].img < 0) {
                mtrx[i][j].img *= -1;
                printf("%5.1f -%5.1fi   ", mtrx[i][j].real,mtrx[i][j].img);
                mtrx[i][j].img *= -1;
            }
            else
                printf("%5.1f +%5.1fi   ", mtrx[i][j].real, mtrx[i][j].img);

        	}
        	else
            if (mtrx[i][j].real == 0 && mtrx[i][j].img == 0) {
                printf("%8d        ", 0);
            }
            else if (mtrx[i][j].img < 0) {
                mtrx[i][j].img *= -1;
                printf("%5.1f -%5.1fi   ", a*mtrx[i][j].real+b, a*mtrx[i][j].img);
                mtrx[i][j].img *= -1;
            }
            else
                printf("%5.1f +%5.1fi   ", a*mtrx[i][j].real+b, a*mtrx[i][j].img);
        }
         printf("\n");
    }
}
