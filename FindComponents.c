/*
 *
 * A program which uses the graph ADT to interpret a given input file
 * print an adjacency list representation of that graph to an output file
 * and then find a series of paths (if they exist) from one vertex in the
 * graph to another and prints these paths to the output file as well.
 *
 */

/*
 * FindPath.c
 * A program which uses Graph.c's ADT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 160

/*
 * helper methods
 */
void fileNULL(FILE* f,char* filename)
{
   if(f==NULL)
   {
      printf("unable to open file %s\n",filename);
      exit(1);
   }
}

/*
 * Pre-condition: two commandline arguements must be given
 * an input and output file respectively
 */
int main(int argc, char** argv)
{
   int no, no2,i,c;//u;
   char* firstLine;
   char line[MAX_LEN];
   FILE *in, *out;

   /*
 * check precondition
 */
   if(argc!=3)
   {
      printf("ERROR: %s accepts two commandline arguements\n",argv[0]);
      exit(1);
   }

   /*
 * open the input and output files
 * check that they aren't null
 */
   in=fopen(argv[1],"r");
   out=fopen(argv[2],"w");
   fileNULL(in,argv[1]);
   fileNULL(out,argv[2]);

   /*
 * get first line from the input file, cast it as an int and use this to create the graph
 */
   firstLine=fgets(line,MAX_LEN,in);
   no=atoi(firstLine);
   Graph G=newGraph(no);

   /*
 * close the file and open it again to reset it to read the first line
 */
   fclose(in);
   in=fopen(argv[1],"r");
   fileNULL(in,argv[1]);

   /*
 * scans each line of the file 
 * (skips the first for some reason, that was why we did the open/close earlier)
 *
 * the scanned line assumes the form "%d %d" so fscanf places the first %d in no, and the second in no2
 * 
 * if the line "0 0" is encountered, the scan breaks out of the loop
 */
   while(fgets(line,MAX_LEN,in)!=NULL)
   {
      fscanf(in,"%d %d",&no,&no2);//scan in the input line
      if((no==0)&&(no2==0))//if you encounter line "0 0"
         break;
      else
         addArc(G,no,no2);
   }

   /*
 * print the graph as an adjacency list to the output file
 */
   fprintf(out,"Adjacency list representation of G:\n");
   printGraph(out,G);
   fprintf(out,"\n");

   /*
 * create a list which will, after we run DFS, act as a stack and hold the verticies according to decreasing finish times
 */
   List S=newList();
   for(c=1;c<=getOrder(G);c++)
   {
      append(S,c);
   }

   /*
 * find the strongly connected components of G
 */
   DFS(G,S);//first run DFS so that List S contains the finish times of G
   Graph GT=transpose(G);
   DFS(GT,S);//now search G-transpose
   i=0;//stores the no of DFS trees in GT
   for(c=1;c<=getOrder(GT);c++)
   {
      if(getParent(GT,c)==NIL)//if the given vertex is a root of a tree in GT's DFS-forest
         i+=1;
   }
   fprintf(out,"G contains %d strongly connected components:\n",i);//this is equivalent to how many strongly connected components are in GT (and therefore G)
   moveTo(S,length(S)-1);
   List l=newList();
   for(c=1;c<=i;c++)//for each component in G
   {
      fprintf(out,"Component %d: ",c);
      for(;getParent(GT,getElement(S))!=NIL;movePrev(S))//tracking backwards through S until you encounter a root node
                                                        //this means that for each of the connected components in G (noted by i)
                                                        //the inner loop will place all of the verticies in that component (as each of the components are listed by S after the second DFS)
                                                        //in the List l, and print it out
      {
         prepend(l,getElement(S));//place in l in reverse order so that when it is printed out, it is printed in topologically sorted order
      }
      prepend(l,getElement(S));//prepend the vertex which has no parent (since the inner loop cuts out right before then)
      movePrev(S);// and move along the list S
      printList(out,l);//print out each component and proceed to the next
      clear(l);
      fprintf(out,"\n");
   }

   /*
 * free all the Graph and List objects
 */
   freeGraph(&G);
   freeGraph(&GT);
   freeList(&S);
   freeList(&l);

   /*
 * close the files
 */
   fclose(in);
   fclose(out);
   return(0);
}
