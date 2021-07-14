#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int m;
    double * ar;
    double * ar2;
    ar = (double *) malloc(1000 * sizeof(double));
    ar2 = (double *) malloc(1000 * sizeof(double));
    for (m = 1; m < 400; m ++)
    {
        double sum = 0;
        int i, j, k, n, i_squared, j_squared, n_squared, big_number;
        // цикл по n
        for (n = 0; n <= m + 2; n++)
        {
            n_squared = n * n;
            //цикл по i
            for (i = 0; i <= n; i++)
            {
                i_squared = i * i;
                //цикл по j
                for (j = 0; j + i <= n; j++)
                {
                    j_squared = j * j;
                    //чтобы не считать это число несколько раз, можно его запомнить
                    big_number = m -  n_squared + i_squared + j_squared;

                    //цикл по к
                    for (k = 0; (k  + i <= n) && (k  + j <= n); k++)
                    {
                        //Условие, что прямоугольник имеет нужную площадь
                        if (big_number == -k * k)
                        {
                            int number = 0;

                            //Вычисляем количество вырожденных сторон (длины 0)
                            if (i == 0)
                                number += 1;
                            if (j == 0)
                                number += 1;
                            if (k == 0)
                                number += 1;
                            if (i + j == n)
                                number += 1;
                            if (j + k == n)
                                number += 1;
                            if (i + k == n)
                                number += 1;

                            if (number == 0)
                                sum += 1;
                            if (number == 1)
                                sum += 0.5;
                            if (number == 2)
                                sum += 0.25;
                            if (number == 3)
                                sum += 0.125;

                            if (number > 3)
                                printf("bag\n");
                            // if (number == 0)
                            //     sum += 1;
                            // else
                            //     sum += 1;
                            // sum += 1;
                        }
                    }
                }
            }
        };
        ar[m] = sum;
        printf("%d %lf\n", m, sum);
    }

    //Усреднение по отрезку длины 50
    for (int l = 25; l < 375; l++)
    {
        double s = 0;
        s = ar[l];
        for (int p = -25; p < 25; p ++)
            s += ar[l + p];
        s /= 50;
        ar2[l] = s;
        printf("%d %lf\n", l, s);
    }
    free(ar);
    free(ar2);
    return 0;
}
