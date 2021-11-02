#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

void swap(long int * ar, int n1, int n2)
{
    int tmp = ar[n1];
    ar[n1] = ar[n2];
    ar[n2] = tmp;
    return;
}

long int norm(long int x, long int y)
{
    return (x * x - x * y + y * y);
}

int q_0(int a, int b, int c,  int d)
{
    return a * b + a * c + a * d + b * c + b * d + c * d;
}

int q_1(int a, int b, int c, int d)
{
    return 9 * q_0(a, b, c, d) + 6 + 12 * ( a + b + c + d);
}

int q_2(int a, int b, int c, int d)
{
    return 9 * q_0(a, b, c, d) + 24 + 24 * ( a + b + c + d);
}

int farey_sequence(int n, long int * ans, int mod)
{
    long int a[4] = {0, 1, 1, n};
    long int k, counter = 0;
    while (a[2] <= n)
    { 
        if ((mod == 0) && norm(a[0], a[1]) < n && norm(a[0], a[1]) > 0)
        {
            ans[2 * counter] = a[0];
            ans[2 * counter + 1] = a[1];
            counter++;
        }
        else
        {
            if ((a[0] % 3 + a[1] % 3 == mod) && norm(a[0], a[1]) < n && norm(a[0], a[1]) > 0)
            {
                ans[2 * counter] = a[0];
                ans[2 * counter + 1] = a[1];
                counter++;
            }
        }

        k = (n + a[1]) / a[3];
        a[0] = k * a[2] - a[0];
        a[1] = k * a[3] - a[1];
        swap(a, 0, 2);
        swap(a, 1, 3);    
    };

    return counter + 1;
}

int weight(int a, int b, int c, int d)
{
    if (a != b && b != c && c != d) 
        return 24;
    if ((a == b && b != c && c != d) || (a != b && b == c && c != d) || (a != b && b != c && c == d))
        return 12;
    if (a == b && c == d && b != c)
        return 6;
    if ((a != b && b == c && c == d) || (a == b && b == c && c != d))
        return 4;
    return 1;
}

int main()
{   
    int n = 10000;

    //Блок выделений памяти и объявления переменных
    long int * q0; long int * q1; long int *q2; long int * ar;
    q0 = (long int *)malloc(n * sizeof(long int));
    q1 = (long int *)malloc(n * sizeof(long int));
    q2 = (long int *)malloc(n * sizeof(long int));

    ar = (long int *)malloc(n * sizeof(long int));
    long int mod_z = 0;
    
    int C = 2;

    long int * ans0; long int * ans1; long int * ans2;
    ans0 = (long int *)malloc(C * sizeof(long int)  * n);
    ans1 = (long int *)malloc(C * sizeof(long int)  * n);
    ans2 = (long int *)malloc(C * sizeof(long int)  * n);
    for (int i = 0; i <  n; i++) { q0[i] = 0; q1[i] = 0; q2[i] = 0; ar[i] = 0;}
    for (int i = 0; i < C * n ; i++){ ans0[i] = 0; ans1[i] = 0; ans2[i] = 0;}

    int len0 = farey_sequence(n, ans0, 0);
    int len1 = farey_sequence(n, ans1, 1);
    int len2 = farey_sequence(n, ans2, 2);


    for (int a = 1; a < n / 3; a++)
        for (int b = 1; (b <= n / a + 1) && (b <= a); b++)
            for (int c = 1; (c <= (n - a * b) / (a + b)) && (c <= b); c++)
                for (int d = 1;(d <= (n - a * b - a * c - b * c) / (a + b + c) )&& (d <= c); d++)
                    if (3 * q_0(a, b, c, d) < n)
                        q0[3 * q_0(a, b, c, d)] += weight(a, b, c, d);
        

    for (int a = 1; a < n / 3; a++)
        for (int b = 1; (b <= n / a + 1) && (b <= a); b++)
            for (int c = 1; (c <= (n - a * b) / (a + b)) && (c <= b); c++)
                for (int d = 1;(d <= (n - a * b - a * c - b * c) / (a + b + c) )&& (d <= c); d++)
                    if (q_1(a, b, c, d) < n)
                        q1[q_1(a, b, c, d)] += weight(a, b, c, d);

    for (int a = 1; a < n / 3; a++)
        for (int b = 1; (b <= n / a + 1) && (b <= a); b++)
            for (int c = 1; (c <= (n - a * b) / (a + b)) && (c <= b); c++)
                for (int d = 1;(d <= (n - a * b - a * c - b * c) / (a + b + c) )&& (d <= c); d++)
                    if (q_2(a, b, c, d) < n)
                        q2[q_2(a, b, c, d)] += weight(a, b, c, d);

    for (int i = 0; i < len0; i++)
    {
        mod_z = norm(ans0[2 * i], ans0[2 * i + 1]);
        for (long int j = 0; j < n; j++)
        {
            if (mod_z * j < n)
            ar[mod_z * j] += q0[j];
        }
    }

    //mod = 1 q1

    for (long int i = 0; i < len1; i++)
    {
        mod_z = norm(ans1[2 * i], ans1[2 * i + 1]);
        for (long int j = 0; j < n; j++)
        {
            if (mod_z * j < n)
            {
                ar[mod_z * j] += q1[j];
            }
        }
    }

    //mod = 2 q1

    for (long int i = 0; i < len2; i++)
    {
        mod_z = norm(ans2[2 * i], ans2[2 * i + 1]);
        for (long int j = 0; j < n; j++)
        {
            if (mod_z * j < n)
            {
                ar[mod_z * j] += q1[j];
            }
        }
    }
    
    //mod  = 2 q2

    for (long int i = 0; i < len2; i++)
    {
        mod_z = norm(ans2[2 * i], ans2[2 * i + 1]);
        for (long int j = 0; j < n; j++)
        {
            if (mod_z * j < n)
            ar[mod_z * j] += q2[j];
        }
    }

    //mod = 1 q2
    for (long int i = 0; i < len1; i++)
    {
        mod_z = norm(ans1[2 * i], ans1[2 * i + 1]);
        for (long int j = 0; j < n; j++)
        {
            if (mod_z * j < n)
            ar[mod_z * j] += q2[j];
        }
    }

    for (long int i = 2; i < n; i++)
    {
        ar[i] += ar[i - 1];
    }
                

    printf("coefficient = %lf", ((double)ar[n-2] / (n - 2)) / (n - 2));

    
return 0;
}             
