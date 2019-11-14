/*sisteme fuzzy - functie de calcul temperatura
scazut: 15 18 22;
         1 1 1
mediu:  18 22 28;
        0  1   0
crescut: 24 35 40;
        0  1   1
		np=numar de puncte existente;				  */
		
#include<stdio.h>
#include<conio.h>
#define N 10
float t[3][3] = {{15,18,20}, {18,22,28}, {24,35,40}};
float ut[3][3] = {{1,1,0}, {0,1,0}, {0,1,1}};
float x[2][3]={{0,3,5},{3,5,8}};
float ux[2][3]={{0,1,0},{0,1,0}};
float I[N],uI[N];
float grad_apartenenta(float , float *, float *, int);

void intersectie(float*,float*,int,float*,float*,int);     //prototipul functiei
int main(void)
{
	int i;
/*	float xc,utc[3];
	printf("temp_curenta:\n");
	scanf("%f",&xc);
	
	utc[0] = grad_apartenenta(xc,t[0],ut[0],3);
	printf ("grad_apartenenta: %f",utc[0]);
*/	
	intersectie(x[0],ux[0],3,x[1],ux[1],3);
	for(i=0; i<N; i++)
		printf("(%.2f, %.2f)",I[i],uI[i]);
getch();
}

float grad_apartenenta(float xc, float x[], float y[], int np)
   {
   	int i;
   	if(xc<x[0]) return y[0];
   	for(i=0; i<np-1;i++)
   	{
   		if (xc>=x[i] && xc<=x[i+1])
   		{
   		   if(y[i] < y[i+1])
			  return (xc-x[i])/(x[i+1]-x[i])*(y[i+1]-y[i])+y[i];
		   if(y[i] > y[i+1])
		      return (x[i+1]-xc)/(x[i+1]-x[i])*(y[i]-y[i+1])+y[i+1];
		    if(y[i]==y[i+1])
		       return y[i];
		}
	}	 
//	   if (xc>x[np-1]) return y[np-1];
	    return y[np-1]; 
}
	
	void intersectie(float A[],float uA[],int nA,float B[],float uB[],int nB)   //descriere functie
{ 
	float xmin,xmax,xc,uxcA,uxcB;
	int i=0,n=nA;
	if (A[0]<B[0]) xmin=A[0]; else xmin=B[0];	
	if (A[nA-1]>B[nB-1]) xmax=A[nA-1]; else xmax=B[nB-1];

	for(xc=xmin;xc<=xmax;xc+=(xmax-xmin)/N)
	{
		uxcA=grad_apartenenta(xc,A,uA,nA);
		uxcB=grad_apartenenta(xc,B,uB,nB);
		I[i]=xc;
		if(uxcA<uxcB) 
			uI[i]=uxcA;
		else
			uI[i]=uxcB;
		i++;
		
	}
}


	
