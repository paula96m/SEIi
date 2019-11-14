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
#define N 21
#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)<(b)?(b):(a))
float E[5][3]={{-15,-2,-0.5},{-2,-0.5,0},{-0.5,0,0.5},{0,0.5,2},{0.5,2,15}};
float uE[5][3]={{1,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,1}};
int faE=5,npE=3;
float vE[3][3]={{-2,-0.5,0},{-0.5,0,0.5},{0,0.5,2}};
float uvE[3][3]={{1,1,0},{0,1,0},{0,1,1}};
int favE=3,npvE=3,ny=5;
float beta[5]={-2,-1,0,1,2};

float t[3][3] = {{15,18,20}, {18,22,28}, {24,35,40}};
float ut[3][3] = {{1,1,0}, {0,1,0}, {0,1,1}};
float y[]={0,2,4,5,6,8};                        //pt defuzzificare
float uy[]={0,0.4,0.4,0.7,0.7,0};               //pt defuzzificare
//int ny=6;                                       //pt defuzzificare , numar puncte y
float Cog(float *,float *,int);                 //
float yc;
float x[2][3]={{0,3,5},{3,5,8}};
float ux[2][3]={{0,1,0},{0,1,0}};
float I[N],uI[N];
float grad_apartenenta(float , float *, float *, int);
float Cog2(float *,float *,int);
int R[5][3]={{4,3,3},{4,3,2},{2,2,2},{2,1,0},{1,1,0}};  //tabela de reguli

void intersectie(float*,float*,int,float*,float*,int);     //prototipul functiei
int main(void)
{
	int i;	
	float tc,td,Ec,Eant,vEc,uEc[5],uvEc[3],y[5],S1,S2;
/*	float xc,utc[3];
	printf("temp_curenta:\n");
	scanf("%f",&xc);
	
	utc[0] = grad_apartenenta(xc,t[0],ut[0],3);
	printf ("grad_apartenenta: %f",utc[0]);
*/	
tc=23; td=22; Ec=tc-td; Eant=1.25; vEc=Ec-Eant;
for(int i=0;i<faE;i++)
uEc[i]=grad_apartenenta(Ec,E[i],uE[i],npE);
for(int i=0;i<favE;i++)
uvEc[i]=grad_apartenenta(vEc,vE[i],uvE[i],npvE);
for(i=0;i<ny;i++)
y[5]=0;

for(i=0;i<faE;i++)
	for(int j=0;j<favE;j++)
	y[R[i][j]]=max(y[R[i][j]],min(uEc[i],uvEc[j]));
	
	S1=S2=0;
	for(i=0;i<ny;i++)
	S1=S1+beta[i]*y[i];
	S2=S2+y[i];
	printf("Cog: %f",S1/S2);


	intersectie(x[0],ux[0],3,x[1],ux[1],3);
	for(i=0; i<N; i++)
		printf("(%.2f, %.2f)\n",I[i],uI[i]);\
	yc=Cog(y,uy,ny);
	printf ("Cog %.2f",yc);
	yc=Cog2(y,uy,ny);
	printf ("Cog2 %.2f",yc);
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

	for(xc=xmin;xc<=xmax;xc+=(xmax-xmin)/(N-1))
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

float Cog(float y[],float uy[],int ny)
{
	
	float s1=0,s2=0,arie,cg;
	int i;
	for(i=0;i<=ny-2;i++,s1+=arie*cg,s2+=arie)
	{
		printf("arie:%f cg:%f\n", arie,cg);
		if(uy[i]==0 || uy[i+1]==0)     //triunghi
		{ 
			arie=((y[i+1]-y[i])*((uy[i]>uy[i+1])?(uy[i]-uy[i+1]):(uy[i+1]-uy[i])))/2;    
			cg=(y[i]+y[i+1]+((uy[i]>uy[i+1])?y[i]:y[i+1]))/3;
			continue;
		}
		if(uy[i]==uy[i+1])
		{
			arie=(y[i+1]-y[i])*uy[i];
			cg=(y[i]+y[i+1])/2;
			continue;
		}
	//	if(uy[i]!=0 || uy[i+1]!=0)
		
			arie=((y[i+1]-y[i])*((uy[i]>uy[i+1])?(uy[i]-uy[i-1]):(uy[i+1]-uy[i])))/2;    
			cg=(y[i]+y[i+1]+((uy[i]>uy[i+1])?y[i]:y[i+1]))/3;
			cg=cg*arie + (y[i+1]-y[i])*min(uy[i],uy[i+1])*(y[i]+y[i+1])/2;
			arie=arie+(y[i+1]-y[i])*min(uy[i],uy[i+1]);
			cg=cg/arie;
	}
	printf("arie:%f cg:%f\n", arie,cg);
	return s1/s2;
}
float Cog2(float y[],float uy[],int ny)
{
		float yinf,ysup,d,yc,uyc,S1,S2;
		int i, np;
		S1=S2=0;
		ysup=y[ny-1];
		yinf=y[0];
		np=100;
		d=(ysup-yinf)/(np-1);
		for(yc=yinf;yc<=ysup;yc+=d)
		{
			uyc=grad_apartenenta(yc,y,uy,ny);
			S1+=uyc*yc;
			S2+=uyc;
		}
		return S1/S2;
}



	
