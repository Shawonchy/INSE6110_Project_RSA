#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

int str_array[10];
int sign_array[10];

unsigned long long sqaurenmul(unsigned long long x,unsigned long long e,unsigned long long n)
{
    int bin_arry[100];
    int bin_count=0;

    while(e>0)
    {
        bin_arry[bin_count]=e%2;
        e=e/2;
        bin_count++;
    }
    unsigned long long res=1;
    for (int i=bin_count-1; i>=0; i--)
    {
        res=(res*res)%n;
        if (bin_arry[i]==1)
        {
            res=(res*x)%n;
        }
    }
    return res;
}

int gcd(int a, int b)
{
    while(b!=0)
    {
        int temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}


int mod_inverse(int a, int c)
{

    a = (a % c + c) % c;

    if (gcd(a, c) > 1)
    {
        printf("Inverse of this mod is not possible\n");
        return -1;
    }


    for (int i = 1; i < c; i++)
    {

        if (((long long)a * i) % c == 1)
        {
            return i;
        }
    }

    return -1;
}


bool prime_chk(int n)
{
    int c=0;
    for(int i=1; i<=n; i++)
    {
        if (n%i==0)
        {
            c++;
        }
    }
    if (c>2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int random_prime_num()
{
    int random_num;
    do
    {
        random_num = (rand() % 65536);
    }
    while (!prime_chk(random_num));
    return random_num;
}

int char_to_integer(char* str)
{
    int length = strlen(str);
    int i;

    char chunk[4];

    char hexString[7];

    int j=0;
    for (i = 0; i < length; i += 3)
    {

        strncpy(chunk, str + i, 3);
        chunk[3] = '\0';


        snprintf(hexString, sizeof(hexString), "%02X%02X%02X",
                 chunk[0] & 0xFF,
                 chunk[1] & 0xFF,
                 chunk[2] & 0xFF);


        int intValue = (unsigned int)strtol(hexString, NULL, 16);


        printf("Chunk: %s\n", chunk);
        //printf("Hexadecimal: %s\n", hexString);
        //printf("Integer: %u\n\n", intValue);

        str_array[j]=intValue;

        // printf("int string %d \n",str_array[j]);
        j++;
    }
    return j;
}

int char_to_integer_sign(char* str)
{
    int length = strlen(str);
    int i;

    char chunk[4];


    char hexString[7];

    int j=0;

    for (i = 0; i < length; i += 3)
    {

        strncpy(chunk, str + i, 3);
        chunk[3] = '\0';
        snprintf(hexString, sizeof(hexString), "%02X%02X%02X",
                 chunk[0] & 0xFF,
                 chunk[1] & 0xFF,
                 chunk[2] & 0xFF);
        int intValue = (unsigned int)strtol(hexString, NULL, 16);

        // Print results
        printf("Chunk: %s\n", chunk);
        printf("Hexadecimal: %s\n", hexString);
        printf("Integer: %u\n\n", intValue);

        sign_array[j]=intValue;

        // printf("int string %d \n",str_array[j]);
        j++;
    }
    return j;
}




void integerTo3Bytes(int i, char *o)
{
    o[0] = (i >> 16) & 0xFF;
    o[1] = (i >> 8) & 0xFF;
    o[2] = i & 0xFF;
    o[3] = '\0';
}


void convert_int_to_char(int *array, int size, char *result)
{
    char temp[4];
    result[0] = '\0';

    for (int i = 0; i < size; i++)
    {

        integerTo3Bytes(array[i], temp);

        strcat(result, temp);
    }
}

int main()
{
    srand(time(0));
    int p,q,e,n,phi_n;

    int encryption_arry[10];

    p=random_prime_num();
    q=random_prime_num();

    n=p*q;
    phi_n=(p-1)*(q-1);
    e=(rand() % 65536);

    if (e<phi_n && gcd(e,phi_n)==1)
    {
         printf("the velue of p:%d \n",p);
         printf("the value of q:%d \n",q);
         printf("the value of n:%d \n",n);
         printf("the value of phie of n:%d \n",phi_n);
         printf("the value of phie of e:%d \n",e);
    }
    else{
        printf("the p,q,N can not be generated as these dont follow rules");
    }


    int my_p=9187;
    int my_q=23567;
    int my_e=8959;
    int my_n=my_p*my_q;
    //printf("My N = %d \n",my_n);
    int my_phi_n=(my_p-1)*(my_q-1);
    //printf("My Phie of N = %d \n",my_phi_n);
    int my_d=mod_inverse(my_e,my_phi_n);
    printf("my d is:%d\n",my_d);

    int partner_n=279514199;
    int partner_e=117859447;

    //Encryption starts here

      char* text="Hi arman";
        int j1=char_to_integer(text);
        unsigned long long cipher;
         for (int i=0; i<j1; i++)
         {
             printf("the chunk int: %d \n",str_array[i]);
             cipher=sqaurenmul(str_array[i],partner_e,partner_n);
             printf("the cipher: %d\n",cipher);
         }


    //ENCRYPTION ENDS HERE

    //Decryption starts here

        int decrypt_msg[3];
        decrypt_msg[0]=55252079;
        decrypt_msg[1]=95335845;
        decrypt_msg[2]=208102917;

        int decrypted_text[3];
        for(int i=0; i<3; i++)
        {
            decrypted_text[i]=sqaurenmul(decrypt_msg[i],my_d,my_n);
            printf("the partner's decrypted integer chuk is:%d\n",decrypted_text[i]);
        }

        int size = sizeof(decrypted_text) / sizeof(decrypted_text[0]);


        char *result = malloc(size * 3 + 1);
        if (!result) {
            perror("malloc failed");
            return 1;
        }


        convert_int_to_char(decrypted_text, size, result);


        printf("Partner's decrepted test: %s\n", result);


       free(result);


    // Decryption ends here


//My signature starts from here..

     unsigned long long cipher1;
     char* sign_mgs="Dibakor";
     int j2=char_to_integer_sign(sign_mgs);

     for (int i=0; i<j2; i++)
     {
         printf("the sign chunk int: %d \n",sign_array[i]);
         cipher1=sqaurenmul(sign_array[i],my_d,my_n); // the number is N of the signer that is me
         printf("the sign cipher: %d\n",cipher1);
     }

    //my signature ends here


    // Signature verification of partner start from here..

    int partner_signature[5];
    partner_signature[0]=152563666;
    partner_signature[1]=177605840;
    partner_signature[2]=10138812;
    partner_signature[3]=105353730;
    partner_signature[4]=204272566;

    int partner_decrypt_sign[5];
//    int partner_n=279514199;
//    int partner_e=117859447;

    for(int i=0; i<5; i++)
    {
        partner_decrypt_sign[i]=sqaurenmul(partner_signature[i],partner_e,partner_n);
        printf("the partner's signed name is:%d\n",partner_decrypt_sign[i]);
    }


    int size1 = sizeof(partner_decrypt_sign) / sizeof(partner_decrypt_sign[0]);


    char *result1 = malloc(size1 * 3 + 1);
    if (!result1)
    {
        perror("malloc failed");
        return 1;
    }


    convert_int_to_char(partner_decrypt_sign, size1, result1);

    printf("Partner's signed text: %s\n", result1);


    free(result1);

//partner signature verification ends here

}
