#define MAX_SAMPLES 2048;
#define DIM 5;
#define MAX_CLUS 128;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


int main(int argc, char *argv[])
{
	FILE *opFile;
	int numSamples;
	int dim;
	float **x;
	int i;
	int numClus;
	float *pos;
	float *dir;
	float *scale;
	float norm;

	/* Check correct number of input parameters */
	if (argc!=3)
	{
		printf("format: clus-dat opFileName numSamples\\n");
		exit(1);
	}

	/* set pointer to output data file */
	argv++;
	if ((opFile=fopen(*argv,"w"))==NULL)
	{
		printf("Error: can't open output file %s\\n",*argv);
		exit(1);
	}

	/* set pointer to number of samples */
	argv++;
	numSamples=atoi(*argv);
	printf("Number of samples = %d\\n",numSamples);

	/* set up */
	dim=5;
	scale=(float *)calloc(dim,sizeof(float));
	scale[0]=3;
	scale[1]=1;
	scale[2]=0.5;
	scale[3]=0.1;
	scale[4]=0.1;
	dir=(float *)calloc(dim,sizeof(float));
	numClus=6;
	pos=(float *)calloc(numClus,sizeof(float));
	pos[0]=0;
	pos[1]=10;
	pos[2]=-15;
	pos[3]=25;
	pos[4]=40;
	pos[5]=-45;
	dir[0]=1;
	dir[1]=3;
	dir[2]=8;
	dir[3]=5;
	dir[4]=6;
	/* allocate memory */
	x=(float **)calloc(numSamples,sizeof(float *));
	for (i=0; i<numSamples; i++) x[i]=(float *)calloc(dim,sizeof(float));

	/* create unit vector pointing same direction as dir */
	norm=0;
	for (i=0; i<dim; i++) norm+=(dir[i]*dir[i]);
	norm=sqrt(norm);
	for (i=0; i<dim; i++) dir[i]/=norm;

	/* write file header */
	fprintf(opFile,"# num rows=%d num columns=%d\\n",numSamples,dim);
	/* create data points */
	for (i=0; i<numSamples; i++)
	{
		float r;
		float y;
		int d;
		float pFact;
		int c;

		/* write label to file */
		/* fprintf(opFile,"sample=%d: ",i); */

		for (d=0; d<dim; d++)
		{
			int j;
			for (j=0; j<6; j++)
			{
			   int m;
			   m=rand();
			   /* printf("m=rand(); m=%d\\n",m);*/
			   y=m;
			   y/=RAND_MAX;
			   /* printf("y/=32767; y=%f\\n",y);*/
			   y-=0.5;
			   /* printf("y-=0.5; y=%f\\n",y);*/
			   y*=scale[d];
			   /* printf("y*=scale[d] (scale[%d]=%f); y=%f\\n",d,scale[d],y);*/
			   x[i][d]+=y;
			}
		}
		r=rand();
		r/=RAND_MAX;
		for (c=0;c<numClus; c++)
		{
			float p1;
			float p2;

			p1=c; p1/=numClus;
			p2=c+1; p2/=numClus;
			if ((r>p1)&&(r<=p2))
			{
				for (d=0; d<dim; d++)
				{
				/* printf("dir[%d]=%f\\n",d,dir[d]);*/
				x[i][d]+=dir[d]*pos[c];
				/* printf("c=%d, x[%d][%d]=%f\\n",c,i,d,x[i][d]);*/
				fprintf(opFile,"%f ",x[i][d]);
				}
       		fprintf(opFile,"\\n");
     		}
		}
    }
  	return(0);
}