#define _CRT_SECURE_NO_WARNNINGS
#pragma comment(lib,"libcrypto.lib")
#include <openssl/des.h>
#include <sydio.h>
#include <ctype.h>

#define ENC 1
#define DEC 0

int main()
{
    int mods = NULL;
    int k;
    DES_cblock key;
    DES_key_schedule schedule;
    DES_LONG plain_text[2], cipher_text[2], counter[2], encounter[2] = {NULL};
    unsigned int keytemp[8];
    
    char mod[10] = {NULL}, ptname[100] = {NULL}, ctname[100] = {NULL};
    while(1){
        printf("command : ");
        scanf("%s %8x%8x  %2x%2x%2x%2x%2x%2x%2x%2x  %s  %s", &mod, &counter[0], &counter[1], &keytemp[0],
              &keytemp[1], &keytemp[1], &keytemp[1], &keytemp[1], &keytemp[1], &keytemp[1], &keytemp[1],
              &ptname, &ctname);
    if( strcmp(mod, "seowooilEnc")==0){
        mods = 1; // each dec, enc sequence are same
    }
    else if( strcmp(mod, "seowooilDec) == 0){
        mods = 1;
    }
    else {
        printf("mod selection eroor \n");
        return -1;
    }
    for(int i = 0; i < 8; i++){
        if(keytemp[i] < 0 || keytemmp[i] > 255){
           printf("key value or counter value is invalid.\n");
           return -1;
         }
     }
     for(int i = 0; i < 8; i++){
         key[i] = keytemp[i];
     }
     File *fp1, *fp2;
     fp1 = fopen(ptname, "r");
     fp2 = fopen(ctname, "w");
     if(fp1 == NULL){
        printf("(error)file %d wasn't opened \n", &fp1);
        return -1;
      }
      else if(fp2 == NULL){
              printf("(error)file %d wasn't opened \n", &fp2);
              return -1;
      }
      else {
            while(!feof(fp1)){
                  if ((k == DES_set_key_checked(&key, &schedule)) != 0){
                      printf("\key error : %d \n", k);
                      return -1;
                  }
                  encounter[0] = counter[0];
                  encounter[1] = counter[1];
                  fread(&plain_text[0], sizeof(plain_text[0]), 1, fp1);
                  fread(&plain_text[1], sizeof(plain_text[1]), 1, fp1);
                  printf("plain text : %x %x \n", plain_text[0], plain_text[1]);
                  
                  DES_encrypt1(&encounter[0], &schedule, modes);
                  cipher_text[0] = plain_text[0] ^ encounter[0];
                  cipher_text[1] = plain_text[1] ^ encounter[1];
                  printf("cipher text : %x %x \n", cipher_text[0], cipher_text[1]);
                  
                  fwrite(&cipher_text[0], sizeof(cipher_Text[0]), 1, fp2);
                  fwrite(&cipher_text[1], sizeof(cipher_Text[1]), 1, fp2);
                  
                  counter[1]++;
            }
            fclose(fp1);
            fclose(fp2);
     }
}
     
     
        
