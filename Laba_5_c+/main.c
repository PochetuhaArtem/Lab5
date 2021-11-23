#include <stdio.h>
#include <stdlib.h>

int writeToBin(FILE *fPointer,int x1,int x2,int N,int delta)
{
    int i,y,n = 0;
    for(i = 0; i<=N; i++)
    {
        n++;
        y=x1*2;
        fwrite(&x1,sizeof(int),1,fPointer);
        fwrite(&y,sizeof(int),1,fPointer);
        if(x1==x2)
        {
            break;
        }
        x1+=delta;
    }
   fclose(fPointer);
   return n;
}

void readFromBin(FILE *fPointer,unsigned int n,int x1,int x2)
{
    int i,x,y;
    printf("BIN FILE (result.bin) : \n");
    printf("Start: %d\nFinish: %d\nCount of steps: %u\n",x1,x2,n);
    printf("*************************************************\n");
    printf("\t\t* N * X * F (X) *\t\n");
    printf("*************************************************\n");
    for(i = 1; i < n+1;i++)
    {
        fread(&x,sizeof(int),1,fPointer);
        fread(&y,sizeof(int),1,fPointer);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",i,x,y);
        printf("+---------------+---------------+---------------+\n");
    }
    fclose(fPointer);
}

int writeToTxt(FILE *fPointer,int x1,int x2,int N,int delta)
{
    int i,y,n = 0;
    for(i = 0; i<=N; i++)
    {
        n++;
        y=x1*2;
        fprintf(fPointer,"%d %d\n",x1,y);
        if(x1==x2)
        {
            break;
        }
        x1+=delta;
    }
    fclose(fPointer);
    return n;
}

void readFromTxt(FILE *fPointer,unsigned int n,int x1,int x2)
{
    int i,x,y;
    printf("TXT FILE (result.txt) : \n");
    printf("Start: %d\nFinish: %d\nCount of steps: %u\n",x1,x2,n);
    printf("*************************************************\n");
    printf("\t\t* N * X * F (X) *\t\n");
    printf("*************************************************\n");
    for(i = 1; i < n+1;i++)
    {
        fscanf(fPointer,"%d",&x);
        fscanf(fPointer,"%d",&y);
        printf("|\t%d\t|\t%d\t|\t%d\t|\t\n",i,x,y);
        printf("+---------------+---------------+---------------+\n");
    }
    fclose(fPointer);
}

void saveResultToArray(FILE *fPointer,int n)
{
   int i,j;
   n*=2;
   int *arr = (int *)malloc(n * sizeof(int));
   printf("Array content :\n");
   for(i = 0;i<n;i++)
   {
       fscanf(fPointer,"%d",&j);
       arr[i] = j;
   }
   for(i = 1;i<n+1;i++)
   {
       if(i%2!=0)
       {
           printf("x: %d \t",arr[i-1]);
       }
       if(i%2==0)
       {
           printf("y: %d\n",arr[i-1]);
       }
   }
   free(arr);
}

int main()
{
    //my func F(x) = x*2
    //Bin file size 88 byte
    //Txt file size 69 byte
    //To view the bin file, I used "BinaryViewer"
    unsigned int N,delta,n;
    int x1,x2;
    char group[50];
    FILE *fInput;
    FILE *fReadTxt, *fWriteTxt;
    FILE *fReadBin, *fWriteBin;

    fInput = fopen("input.dat","r");
    fscanf(fInput,"%s%d%d%u%u",&group,&x1,&x2,&N,&delta);
    fclose(fInput);

    if(N==0){N = delta;}
    printf("group = %s\n",group);
    printf("x1 = %d\n",x1);
    printf("x2 = %d\n",x2);
    printf("N = %u\n",N);
    printf("step = %u\n",delta);

    fWriteTxt = fopen("result.txt","w");
    n = writeToTxt(fWriteTxt,x1,x2,N,delta);
    fclose(fWriteTxt);

    fReadTxt  = fopen("result.txt","r");
    readFromTxt(fReadTxt,n,x1,x2);
    fclose(fReadTxt);

    fWriteBin = fopen("result.bin","wb");
    n = writeToBin(fWriteBin,x1,x2,N,delta);
    fclose(fWriteBin);

    fReadBin  = fopen("result.bin","rb");
    readFromBin(fReadBin,n,x1,x2);
    fclose(fReadBin);

    fReadTxt  = fopen("result.txt","r");
    saveResultToArray(fReadTxt,n);
    fclose(fReadTxt);
    return 0;
}

