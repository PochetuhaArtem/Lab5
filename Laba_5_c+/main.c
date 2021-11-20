#include <stdio.h>
#include <stdlib.h>

int writeToBin(int x1,int x2,int N,int delta)
{
    int i,y,n = 0;
    FILE *fPointer;
    fPointer = fopen("result.bin","wb");
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

void readFromBin(unsigned int n,int x1,int x2)
{
    int i,x,y;
    FILE *fPointer;
    printf("BIN FILE (result.bin) : \n");
    fPointer = fopen("result.bin","rb");
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

int writeToTxt(int x1,int x2,int N,int delta)
{
    int i,y,n = 0;
    FILE *fPointer;
    fPointer = fopen("result.txt","w");
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

void readFromTxt(unsigned int n,int x1,int x2)
{
    int i,x,y;
    FILE *fPointer;
    printf("TXT FILE (result.txt) : \n");
    fPointer = fopen("result.txt","r");
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

void saveResultToArray(int n)
{
   FILE *fPointer;
   fPointer = fopen("result.txt","r");
   n*=2;
   int* arr = malloc(n*sizeof(int));
   int i,j;
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
}

int main()
{
    //my func F(x) = x*2
    //Bin file size 88 byte
    //Txt file size 69 byte
    //To view the bin file, I used "BinaryViewer"
    unsigned int N,delta,n;
    int x1,x2;
    char group[255];
    FILE *fPointer;
    fPointer = fopen("input.dat","r");
    fscanf(fPointer,"%s%d%d%u%u",&group,&x1,&x2,&N,&delta);
    fclose(fPointer);

    if(N==0){N = delta;}

    printf("group = %s\n",group);
    printf("x1 = %d\n",x1);
    printf("x2 = %d\n",x2);
    printf("N = %u\n",N);
    printf("step = %u\n",delta);

    n = writeToTxt(x1,x2,N,delta);
    readFromTxt(n,x1,x2);

    n = writeToBin(x1,x2,N,delta);
    readFromBin(n,x1,x2);

    saveResultToArray(n);
    return 0;
}
