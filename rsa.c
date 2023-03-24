/*
 * C program to Implement the RSA Algorithm
 */
 
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
 
long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];
int prime(long int);
void encrypt();
void decrypt();
void rsa_encript();

void main()
{
    printf("\nENTER FIRST PRIME NUMBER\n");
    scanf("%d", &p);
    flag = prime(p);

    if (flag == 0)
    {
        printf("\nWRONG INPUT\n");
        getch();
        exit(1);
    }
    printf("\nENTER ANOTHER PRIME NUMBER\n");
    scanf("%d", &q);
    
    flag = prime(q);
    
    if (flag == 0 || p == q)
    {
        printf("\nWRONG INPUT\n");
        getch();
        exit(1);
    }
    printf("\nENTER MESSAGE\n");
    fflush(stdin);
    scanf("%s", msg);
    for (i = 0; msg[i] != NULL; i++)
        m[i] = msg[i];
    n = p * q;
    printf("n = p*q = %d \n", n);
    t = (p - 1) * (q - 1);
    printf("t = %d \n", t);

    rsa_encript(); // function for hardware acceleration
    
    decrypt();
}
int prime(long int pr)
{
    int i;//p
    j = sqrt(pr);//i
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}
void decrypt()
{
    long int pt, ct, key = d[0], k;
    i = 0;
    while (en[i] != -1)
    {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    printf("\nTHE DECRYPTED MESSAGE IS\n");
    for (i = 0; m[i] != -1; i++)
        printf("%c", m[i]);
}
/*
***********************************************
***********************************************
********FUNCTION FOR ACCELERATION IN HW********
***********************************************
***********************************************
*/
void rsa_encript()
{
    int u;
    int flag_1;
    u = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
       flag_1 = 1; //for prime number
       j = sqrt(i);
        for (int l = 2; l <= j; l++)
        {
            if (i % l == 0)
            {
                flag_1 = 0; //for non prime number
                break;
            }
        }
        if (flag_1 == 1) // i is prime number
        {
            flag = 1;
        }
        else            //i isn't prime number
            flag = 0;

        if (flag == 1 && i != p && i != q)
        {
            e[u] = i;
            printf("e[u] = %d \n",e[u]); // 11, 13, 17, 19, 23

            long int x = e[u];
            long int k = 1;
            while (k % x != 0)
            {
                k = k + t;
                if (k % x == 0)
                {
                    flag = k / x;
                }
            }
            printf("flag after cd = %d \n",flag);
            if (flag > 0)
            {
                d[u] = flag;
                u++;
            }
            if (u == 99)
                break;
        }
    }
    for (i = 0; i < j - 1; i++)
        printf("\n%ld\t%ld", e[i], d[i]);

    long int pt, ct, key = e[0], k, len;
    printf("key = %d\n", key);
    i = 0;
    len = strlen(msg);
    while (i != len)
    {
        pt = m[i];
        pt = pt - 96; 

        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    printf("\nTHE ENCRYPTED MESSAGE IS\n");
    for (i = 0; en[i] != -1; i++)
        printf("%c", en[i]);
}
