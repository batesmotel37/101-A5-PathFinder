/*
 *
 * A test Client for the Graph ADT
 * inputs data for a Graph and then tests
 * each method from the Graph.h to show that
 * these methods work without error or
 * memory leak
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc,char** argv)
{
   //test newGraph(), printGraph()
   Graph G=newGraph(6);
   printGraph(stdout,G);
   printf("\n");

   //test addEdge and get Size
   for(int c=1;c<getOrder(G);c++)
   {
      for(int c2=1;c+c2<getOrder(G);c2+=2)
         addEdge(G,c,c+c2);
   }
   printGraph(stdout,G);
   printf("%d\n",getSize(G));
   printf("\n");

   //test makeNull, retest getSize
   makeNull(G);
   printGraph(stdout,G);
   printf("%d\n",getSize(G));
   printf("\n");
   
   //test addArc and get Size
   for(int c=1;c<getOrder(G);c++)
   {
      for(int c2=1;c+c2<getOrder(G);c2+=2)
         addArc(G,c,c+c2);
   }
   printGraph(stdout,G);
   printf("%d\n\n",getSize(G));
   
   //test BFS, you need to do this before you can test getSource(),getParents(),or getDist(), so test those immediatly after
   BFS(G,1);
   printf("source:%d\n",getSource(G));
   printf("parent of 5:%d\n",getParent(G,5));
   printf("distance of 5:%d\n\n",getDist(G,5));

   //Finally test getPath()
   List L=newList();
   getPath(L,G,5);
   printList(stdout,L);
   printf("\n");

   //test copyGraph
   Graph n=copyGraph(G);
   printGraph(stdout,n);
   printf("\n");

   //test transpose
   Graph t=transpose(G);
   printGraph(stdout,t);
   printf("\n");

   //test DFS
   List S=newList();
   for(int c=1;c<=getOrder(G);c++)
   {
      append(S,c);
   }
   DFS(G,S);
   for(int i=1;i<=getOrder(G);i++)
   {
      printf("%d: %d %d %d\n",i,getDiscover(G,i),getFinish(G,i),getParent(G,i));
   }

   //test freeGraph
   freeGraph(&G);
   freeList(&L);
   freeList(&S);
   freeGraph(&n);
   freeGraph(&t);
   return(0);
}
/*output:
 * 1:
 * 2:
 * 3:
 * 4:
 * 5:
 * 6:
 *
 * 1: 2 4
 * 2: 1 3 5
 * 3: 2 4
 * 4: 1 3 5
 * 5: 2 4
 * 6:
 * 6
 *
 * 1:
 * 2:
 * 3:
 * 4:
 * 5:
 * 6:
 * 0
 *
 * 1: 2 4
 * 2: 3 5
 * 3: 4
 * 4: 5
 * 5:
 * 6:
 * 6
 *
 * source:1
 * parent of 5:2
 * distance of 5:2
 *
 * 1 2 5
 * 1: 2 4
 * 2: 3 5
 * 3: 4
 * 4: 5
 * 5:
 * 6:
 *
 * 1:
 * 2: 1
 * 3: 2
 * 4: 1 3
 * 5: 2 4
 * 6:
 *
 * 1: 1 10 -2
 * 2: 2 9 1
 * 3: 3 8 2
 * 4: 4 7 3
 * 5: 5 6 4
 * 6: 11 12 -2
 *
 */
