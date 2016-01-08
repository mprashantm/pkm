#include <iostream.h>
#include<stdio.h>
#define NO_OF_TERMINAL
using namespace std;
int no_of_terminal;
int no_of_variable;
int no_of_production;
int start_variable;
char input[10];
//    int flag;//A->a or A->BC
struct grammer
{
    char *T;//array of terminal
    char *V;//array of no_of_terminal
    int **unit_production;//will become unit_production[NO_OF_VARIABLE][NO_OF_TERMINAL];
    int ***nonunit_production;//will become nonunit_production[NO_OF_VARIABLE][NO_OF_VARIABLE][NO_OF_VARIABLE];
    char start;// start variable
}*G;
void init()
{
  G=(struct grammer *)malloc(sizeof(struct grammer));
  G->T=(char *)malloc(sizeof(char)*no_of_terminal);
  G->V=(char *)malloc(sizeof(char)*no_of_variable);
  /**************************************/
  G->unit_production=(int **)malloc(sizeof(int *)*no_of_variable);
  int i,j;
  for(i=0;i<no_of_variable;i++)
  G->unit_production[i]=(int *)malloc(sizeof(int )*no_of_terminal);
 /***************************/
 /****************************************/
 G->nonunit_production=(int ***)malloc(sizeof(int **)*no_of_variable);
for(i=0;i<no_of_variable;i++)
    G->nonunit_production[i]=(int **)malloc(sizeof(int *)*no_of_variable);
for(i=0;i<no_of_variable;i++)
    for(j=0;j<no_of_variable;j++)
        G->nonunit_production[i][j]=(int *)malloc(sizeof(int )*no_of_variable);
/*****************************************/

G->start=start_variable;

}
int getindex(char ch)//get index of a variable
{
    int i=0;
    for(i=0;i<no_of_variable;i++)
    if(ch==G->V[i])return i;
}
int ***Mat;
void get3dmatrix(int m,int n,int p)//initializing a 3d matrix  which is used in cyk algo
{
    Mat=(int ***)malloc(sizeof(int **)*m);
    int i,j,k;
    for(i=0;i<m;i++)
        Mat[i]=(int **)malloc(sizeof(int *)*n);
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            Mat[i][j]=(int *)malloc(sizeof(int)*p);

    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            for(k=0;k<p;k++)
            Mat[i][j][k]=0;
}
int main()
{
   cout<<"enter no of terminal , variable ,and no of production , index of start variable ";
   cin>>no_of_terminal>>no_of_variable>>no_of_production>>start_variable;
   init();
   int i;
   for(i=0;i<no_of_terminal;i++)
   {
       cin>>G->T[i];
   }
   for(i=0;i<no_of_variable;i++)
   {
       cin>>G->V[i];
   }
   char L,R[3];//stores left and right part of  a production ;
   for(i=0;i<no_of_production;i++)
   {
       cout<<"enter production "<<i+1<<"(seperate both side by space)";
       cin>>L>>R;
       if(R[1]=='\0')//A->a
       {
           int a=getindex(L);
           int b=getindex(R[0]);
           G->unit_production[a][b]=1;
       }
       else//A->BC
       {
           int a=getindex(L);
           int b=getindex(R[0]);
           int c=getindex(R[1]);
           G->nonunit_production[a][b][c]=1;
       }

   }
   cout<<"enter starting variable";cin>>start;
   int length;
   cout<<"enter the input string length";cin>>length;
   cout<<"enter string";cin>>input;
   get3dmatrix(length,length,no_of_variable);//Mat[len][len][no_V];
   cin>>input;

}
/*let the input be a string S consisting of n characters: a1 ... an.
let the grammar contain r nonterminal symbols R1 ... Rr.
This grammar contains the subset Rs which is the set of start symbols.
let P[n,n,r] be an array of booleans. Initialize all elements of P to false.
for each i = 1 to n
  for each unit production Rj -> ai
    set P[1,i,j] = true
for each i = 2 to n -- Length of span
  for each j = 1 to n-i+1 -- Start of span
    for each k = 1 to i-1 -- Partition of span
      for each production RA -> RB RC
        if P[k,j,B] and P[i-k,j+k,C] then set P[i,j,A] = true
if any of P[n,1,x] is true (x is iterated over the set s, where s are all the indices for Rs) then
  S is member of language
else
  S is not member of language*/
