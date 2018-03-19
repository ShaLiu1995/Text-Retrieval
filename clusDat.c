{\rtf1\ansi\ansicpg1252\deff0\deflang2057{\fonttbl{\f0\fswiss\fcharset0 Courier New;}{\f1\fswiss\fcharset0 Arial;}}
{\*\generator Msftedit 5.41.15.1515;}\viewkind4\uc1\pard\tx0\tx959\tx1918\tx2877\tx3836\tx4795\tx5754\tx6713\tx7672\tx8631\f0\fs20 /*******************************************************/\par
/*                                                     */\par
/*                    clus-data.                       */\par
/*                    =========                        */\par
/*                                                     */\par
/*     C programme to create data for EE3J2 lab        */\par
/*                                                     */\par
/*          Written for EE3J2 Data Mining              */\par
/*                                                     */\par
/*        Version 1: Martin Russell 07/03/10           */\par
/*                                                     */\par
/* Dept. Electronic, Electrical & Computer Engineering */\par
/*            University of Birmingham                 */\par
/*                                                     */\par
/*    To compile under linux:                          */\par
/*                 gcc -lm clus-dat.c                  */\par
/*                 mv a.out clus-dat                   */\par
/*                                                     */\par
/*    To run:                                          */\par
/*                 clus-dat opFileName num_samples dim */\par
/*                                                     */\par
/*******************************************************/\par
\par
#define MAX_SAMPLES 2048;\par
#define DIM 5;\par
#define MAX_CLUS 128;\par
\par
#include <stdio.h>\par
#include <stdlib.h>\par
#include <math.h>\par
#include <string.h>\par
#include <math.h>\par
#include <ctype.h>\par
\par
\par
int main(int argc, char *argv[])\par
\{\par
  FILE *opFile;\par
  int numSamples;\par
  int dim;\par
  float **x;\par
  int i;\par
  int numClus;\par
  float *pos;\par
  float *dir;\par
  float *scale;\par
  float norm;\par
\par
  /* Check correct number of input parameters */\par
  if (argc!=3)\par
    \{\par
      printf("format: clus-dat opFileName numSamples\\n");\par
      exit(1);\par
    \}\par
\par
  /* set pointer to output data file */\par
  argv++;\par
  if ((opFile=fopen(*argv,"w"))==NULL)\par
    \{\par
      printf("Error: can't open output file %s\\n",*argv);\par
      exit(1);\par
    \}\par
\par
  /* set pointer to number of samples */\par
  argv++;\par
  numSamples=atoi(*argv);\par
  printf("Number of samples = %d\\n",numSamples);\par
\par
  /* set up */\par
  dim=5;\par
  scale=(float *)calloc(dim,sizeof(float));\par
  scale[0]=3;\par
  scale[1]=1;\par
  scale[2]=0.5;\par
  scale[3]=0.1;\par
  scale[4]=0.1;\par
  dir=(float *)calloc(dim,sizeof(float));\par
  numClus=6;\par
  pos=(float *)calloc(numClus,sizeof(float));\par
  pos[0]=0;\par
  pos[1]=10;\par
  pos[2]=-15;\par
  pos[3]=25;\par
  pos[4]=40;\par
  pos[5]=-45;\par
  dir[0]=1;\par
  dir[1]=3;\par
  dir[2]=8;\par
  dir[3]=5;\par
  dir[4]=6;\par
  /* allocate memory */\par
  x=(float **)calloc(numSamples,sizeof(float *));\par
  for (i=0; i<numSamples; i++) x[i]=(float *)calloc(dim,sizeof(float));\par
\par
  /* create unit vector pointing same direction as dir */\par
  norm=0;\par
  for (i=0; i<dim; i++) norm+=(dir[i]*dir[i]);\par
  norm=sqrt(norm);\par
  for (i=0; i<dim; i++) dir[i]/=norm;\par
\par
  /* write file header */\par
  fprintf(opFile,"# num rows=%d num columns=%d\\n",numSamples,dim);\par
  /* create data points */\par
  for (i=0; i<numSamples; i++)\par
    \{\par
      float r;\par
      float y;\par
      int d;\par
      float pFact;\par
      int c;\par
\par
      /* write label to file */\par
      /* fprintf(opFile,"sample=%d: ",i); */\par
\par
      for (d=0; d<dim; d++)\par
\tab\{\par
\tab   int j;\par
\tab   for (j=0; j<6; j++)\par
\tab     \{\par
\tab       int m;\par
\tab       m=rand();\par
\tab       /* printf("m=rand(); m=%d\\n",m);*/\par
\tab       y=m;\par
\tab       y/=RAND_MAX;\par
\tab       /* printf("y/=32767; y=%f\\n",y);*/\par
\tab       y-=0.5;\par
\tab       /* printf("y-=0.5; y=%f\\n",y);*/\par
\tab       y*=scale[d];\par
\tab       /* printf("y*=scale[d] (scale[%d]=%f); y=%f\\n",d,scale[d],y);*/\par
\tab       x[i][d]+=y;\par
\tab     \}\par
\tab\}\par
      r=rand();\par
      r/=RAND_MAX;\par
      for (c=0;c<numClus; c++)\par
\tab\{\par
\tab   float p1;\par
\tab   float p2;\par
\tab   \par
\tab   p1=c; p1/=numClus;\par
\tab   p2=c+1; p2/=numClus;\par
\tab   if ((r>p1)&&(r<=p2))\par
\tab     \{\par
\tab       for (d=0; d<dim; d++)\par
\tab\tab\{\par
\tab\tab   /* printf("dir[%d]=%f\\n",d,dir[d]);*/\par
\tab\tab   x[i][d]+=dir[d]*pos[c];\par
\tab\tab   /* printf("c=%d, x[%d][%d]=%f\\n",c,i,d,x[i][d]);*/\par
\tab\tab   fprintf(opFile,"%f ",x[i][d]);\par
\tab\tab\}\par
\tab       fprintf(opFile,"\\n");\par
\tab     \}\par
\tab\}\par
    \}\par
  return(0);\par
\}\par
\par
\pard\f1\par
}
 