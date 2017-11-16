/*
 *
 * An ADT which store an adjacency list representation of a graph using an array of Lists
 * and then find a series of paths (if they exist) from one vertex in the
 * graph to another and prints these paths to the output file as well.
 *
 *
 */

/*
 * Grpah.c
 * A grpah ADT
 * employs List.c and List.h for a List ADT
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"

//create Graph type
typedef struct GraphObj
{
   //Fields
   int order;//holds the number of verticies
   int size;//the number of edges or arcs
   int* discover;//the times at which the given vertex is discovered during a DFS
   int* finish;//the times at which a given vertex is finished during a DFS
   char* colors;//the "color" of the corresponding verticies in adj; colors tell you wether or not a vertex has been checked by BFS()
   List* adj;//the adjacency list, the index of the list corresponds to the vertex of the graph
             //the contents of the list are all of the adjacent verticies to the index listed in increasing order
             //the 0 index is a dummy and will remain empty; just because this makes accessing the array easier if i don't have to -1 every time I access it
   int* parents;//contains the "parent" vertex of a vertex in a BFS(); corresponds to the verticics in adj
   int* distance;//contains the shortest number of edges between the source vertex and the given vertex; corresponds to adj
} GraphObj;

//creates a pointer for the Graph type
typedef GraphObj* Graph;

/*
 * Constructors/Deconstructors
 */

//constructor
Graph newGraph(int n)
{
   Graph G;
   G=malloc(sizeof(GraphObj));
   G->adj=calloc(n+1,sizeof(List));//allocate memory of n Lists, plus one dummy element (the zero index will remain empty; makes it easier to program)
   for(int c=1;c<=n;c++)
      G->adj[c]=newList();//create these Lists
   G->order=n;//n is the number of verticies in the eventual graph
   G->size=0;//there are initially no edges
   G->parents=calloc(n+1,sizeof(int));//allocate the same number of indicies for these arrays as for adj, since the indicies in these arays correspond to adj
   G->distance=calloc(n+1,sizeof(int));
   G->colors=calloc(n+1,sizeof(char));
   G->discover=calloc(n+1,sizeof(int));
   G->finish=calloc(n+1,sizeof(int));
   return (G);
}

//deconstructor- frees a Graph pG
void freeGraph(Graph* pG)
{
   if(pG!=NULL&&*pG!=NULL)
   {
      int o=getOrder(*pG);
      for(int c=0;c<=o;c++)//free each list in pG
      {
         freeList(&(*pG)->adj[c]);
      }
      free((*pG)->distance);//free the arrays distance, parents, colors, adj
      free((*pG)->parents);
      free((*pG)->discover);
      free((*pG)->finish);
/*
      for(int c=1;c<=o;c++)
      {
         free((*pG)->colors[c]);
      }
*/
      free((*pG)->colors);
      free((*pG)->adj);
      free(*pG);//free the pointer pG and set it to null
      *pG=NULL;
   }
}

/*
 *
 * Helper methods
 *
 */

//checks that a passed int is within the bounds 1>=i>=getOrder(G)
//used as pre-condition for many methods
void inOrder(Graph G,int i,char* method)
{
   //don't need to check nullGraph as any method that calls this check will have already called nullGraph on whichever Graph it passes
   int o=G->order;
   if(!(i>=1&&i<=o))
   {
      printf("ERROR: %s passed %d which lies oustide the graph's order(%d)\n",method,i,o);
      exit(1);
   }
}

//checks that a method is not passed a NULL Graph reference
void nullGraph(Graph G,char* method)
{
   if(G==NULL)
   {
      printf("Graph Error: called %s on NULL refernce\n",method);
      exit(1);
   }
}


/*
 *
 * Access Functions
 *
 */

//returns the number of verticies in G
//pre-condition: G!=NULL
int getOrder(Graph G)
{
   nullGraph(G,"getOrder()");
   return G->order;
}

//returns the number of edges in G
//pre-condition: G!=NULL
int getSize(Graph G)
{
   nullGraph(G,"getSize()");
   return G->size;
}

//returns the source node of the graph used in BFS()
//returns NIL if BFS() hasn't been called
//pre-condition: G!=NULL
int getSource(Graph G)
{
   nullGraph(G,"getSource()");
   return G->parents[0];//because the 0 index in all of the arrays (since its a dummy in adj), I'm just going to store the source vertex in parents[0], instead of creating a new variable for it
}

//returns the parent node of u in a BFS-tree
//pre-condition: G!=NULL && 1<=u<=getOrder(G)
int getParent(Graph G,int u)
{
   char* m="getParent()";
   nullGraph(G,m);
   inOrder(G,u,m);
   return G->parents[u];
}

//returns the distance from the source vertex to u
//uses BFS-tree to do this
//returns INF if BFS() hasn't been called
//or if there is no path from source to u
//pre-condition: G!=NULL && 1<=u<=getOrder(G)
int getDist(Graph G,int u)
{
   char* m="getDist()";
   nullGraph(G,m);
   inOrder(G,u,m);
   return G->distance[u];
}

//returns the discover time of a given vertex of graph G
//in a DFS-tree
//returns UNDEF if DFS hasn't been called
//Pre-Condition: G!=NULL && 1<=u<=getOrder(G)
int getDiscover(Graph G, int u)
{
   char* m="getDiscover()";
   nullGraph(G,m);
   inOrder(G,u,m);
   return G->discover[u];
}

//returns the finish time of a given vertex of graph G
//in a DFS-tree
//returns UNDEF if DFS hasn't been called
//Pre-Condition: G!=NULL && 1<=u<=getOrder(G)
int getFinish(Graph G,int u)
{
   char* m="getFinish()";
   nullGraph(G,m);
   inOrder(G,u,m);
   return G->finish[u];
}


//appends the shortest path from source to u in G to List L
//appends NIL if no path exists
//pre-condition: getSource(G)!=NULL;//BFS must be called before getPath()
void getPath(List L,Graph G,int u)
{
   if(getSource(G)==NULL)//no need to check nullGraph(), as getSource() already checks nullGraph()
   {
      printf("ERROR:called getPath() on a graph without a source vertex, remeber to run BFS before calling getPath()");
      exit(1);
   }
   inOrder(G,u,"getPath()");
   int p=getParent(G,u);
   if(u==getSource(G))//if u is the source, then the path is of length 0 and the source is the only vertex on it
      append(L,u);
   else if(p!=NIL)//if p==NIL, and u isn't the source then u doesn't have a parent and the path doesn't exist (since the parents are created due to edges and if there's no parent that means no edge, therefore no path)
   {
      getPath(L,G,p);//recursivly append the parent of u, so that the source will be first, then its child, then its child, and so on to u
      append(L,u);
   }
}

/*
 *
 * Manipulation Functions
 *
 */

//deletes all edges in G
//making in a Null Graph
//Pre-condition: G!=NULL
void makeNull(Graph G)
{
   nullGraph(G,"makeNull()");
   for(int c=1;c<=G->order;c++)//clear each list in adj (since edges are tracked via the adjacency matrix)
   {
      clear(G->adj[c]);
   }
   G->size=0;//set size to 0 b/c no edges
}

//creates an edge between u and v; increasing size by 1
//Pre-conditon: G!=NULL && 1>=u>=getOrder(G) && 1>=v>=getOrder(G)
void addEdge(Graph G,int u,int v)
{
   char* m="addEdge()";
   nullGraph(G,m);
   inOrder(G,u,m);
   inOrder(G,v,m);
   addArc(G,u,v);
   addArc(G,v,u);
   G->size--;//since each call of addArc invokes size++ for a total of size+2
             //we need to subtract that be one to get the size+1 that we want
}

//creates a directed edge from u to v; increasing size by 1
//Pre-conditon: G!=NULL && 1>=u>=getOrder(G) && 1>=v>=getOrder(G)
void addArc(Graph G,int u,int v)
{
   char* m="addArc()";
   nullGraph(G,m);
   inOrder(G,u,m);
   inOrder(G,v,m);
   List L=G->adj[u];
   if(L!=NULL)
   {
      //check all adjacencies to vertex u
      for(moveTo(L,0);getIndex(L)>=0;moveNext(L))
      {
         int adj=getElement(L);
         //maintain numerically increasing order while inserting
         if(adj>v)//if you encounter an adjacency larger than v
                            //insert v before it and exit the loop
         {
            insertBefore(L,v);
            break;
         }
         else if(adj==v)//if you encounter one equal to v
                                  //terminate the method as the adjacency 
                                  //already exists
            return;
      }
      if(getIndex(L)<0)//if you reached the end of the loop without inserting
                       //then append v to the end of that adjacency list
         append(L,v);
   }
   else
      append(L,v);
   G->size++;//increase size due to new edge
} 

//preforms a breadth first search on G with s as its source
//Pre-condition: G!=NULL && 1>=s>=getOrder(G)
void BFS(Graph G,int s)
{
   char* m="BFS()";
   nullGraph(G,m);
   inOrder(G,s,m);
   for(int c=1;c<=getOrder(G);c++)//assign every index in the adjacency graph the color white, no parent, and an infinate distance from the source
   {
      G->colors[c]='w';//"whit";
      G->parents[c]=NIL;
      G->distance[c]=INF;
   }
   G->parents[0]=s;//set the source in parent[0], since the 0 index is unused I'm just going to store the source here instead of creating a new variable
   G->colors[s]='g';//"gray";//set the source's color to gray, meaing that it is discovered, but not all of its adjacencies have been observed yet
   G->distance[s]=0;//it is 0 edges from itself
   List L=newList();//create a list to hold gray indicies (so that we don't have to scan colors for them everytime we want to do something)
   append(L,s);//add source to this list
   while(!isEmpty(L))//while the list isn't empty
   {
      int i=front(L);//take the first vertex it holds
      List A=G->adj[i];//and the list of verticies adjacent to it
      for(moveTo(A,0);getIndex(A)>=0;moveNext(A))//cycle through all the adjacencies
      {
         int u=getElement(A);
         if(G->colors[u]=='w')//strcmp(G->colors[u],"whit")==0)//if the adjacency is white
         {
            G->colors[u]='g';//"gray";//color it gray
            G->parents[u]=i;//assign its parent as the vertex from the list
            G->distance[u]=G->distance[i]+1;//make its distance one further from the source than its parent's
            append(L,u);//add it to the list, since we've yet to observe its adjacencies
         }
      }
      G->colors[i]='b';//"blac";//color the previous gray vertex black, so that we know it has been fully checked
      deleteFront(L);//delete it from the list
   }
   freeList(&L);//free L, you won't be using it anymore
}

//preforms a depth first search on G with List S used to both tell the
//order by which the verticies of G should be searched
//and then storing the verticies in it according to their finish times
//S should be returned with the verticies ordered by decreasing finishing times
//Pre-Condition: G!=NULL && getLength(S)==getOrder(G)
//
//Other, unimplemented Pre-Condition: the contents of S are exactly the verticies of G
void DFS(Graph G,List S)
{
   /*
 * check preconditions
 */
   char* m="DFS()";
   nullGraph(G,m);
   if(length(S)!=getOrder(G))
   {
      printf("Error: called %s on a List of length that is not equal to the order of the graph\n",m);
      exit(1);
   }
   int time=0;//used to track discover time and finish time
   List otherS=newList();//used as an interum storage place for the verticies of the graph ordered by finish times
                         //needed because I can't store these verticies without messing up the List S that I need to order my verticies for the DFS
   /*
 * when the DFS method finds an undiscovered ("white") vertex in G it is passes here to be explored
 * Visit() is nested inside DFS because that way it can refer to the variable time
 */
   void Visit(int vertex)
   {
      G->colors[vertex]='g';
      G->discover[vertex]=(++time);//advance time one step, note the event of discovering a node
      List A=G->adj[vertex];
      if(!isEmpty(A))//if a given vertex is adjacent to any other verticies
      {
         for(moveTo(A,0);getIndex(A)>=0;moveNext(A))//for each vertex adjacent to the one being searched
         {
            int nextVertex=getElement(A);
            if(G->colors[nextVertex]=='w')//if it has yet to be discovered
            {
               G->parents[nextVertex]=vertex;//make this vertex its parent
               Visit(nextVertex);//and search it
            }
         }
      }
      G->colors[vertex]='b';//now that all adjacencies to the vertex have been finished, we finish this vertex
      G->finish[vertex]=(++time);//increment time, and record finishing
      prepend(otherS,vertex);//prepend, as any priorly stored vertex will have had a lower finishing time (since it finished earlier and was stored)
   }
   /*
 * set the whole graph to "white", no parents, and undefined discover/finish time
 */
   for(int c=1;c<=getOrder(G);c++)
   {
      G->colors[c]='w';
      G->parents[c]=NIL;
      G->discover[c]=UNDEF;
      G->finish[c]=UNDEF;
   }
   for(moveTo(S,0);getIndex(S)>=0;moveNext(S))//check each vertex in the graph, in the order given by S
   {
      int i=getElement(S);
      if(G->colors[i]=='w')//if it's white, pass it to Visit
         Visit(i);
   }//Graph should now be completely searched (since every vertex will have been passed to Visit() at least once)
   clear(S);//clear S
   for(moveTo(otherS,0);getIndex(otherS)>=0;moveNext(otherS))
   {
      append(S,getElement(otherS));//and pass each element from the storage List to S
   }
   freeList(&otherS);//free the storage list to prevent memory leak
}

/*
 *
 * Other Functions
 *
 */

//returns a transpose of G
//a transpose of a directed graph reverses the direction
//of all edges in the graph
Graph transpose(Graph G)
{
   nullGraph(G,"transpose()");
   int o=getOrder(G);
   Graph rtn=newGraph(o);//create a new graph with the same number of verticies as G
   for(int c=1;c<=o;c++)//for each vertex in graph G, (c)
   {
      List A=G->adj[c];
      for(moveTo(A,0);getIndex(A)>=0;moveNext(A))//for each vertex adjacent to vertex (c)
         append(rtn->adj[getElement(A)],c);//create an arc in the new graph from each adjacent vertex to the vertex (c)
   }
   return rtn;
}

//returns a copy of the Graph G
Graph copyGraph(Graph G)
{
   nullGraph(G,"copyGraph()");
   int o=getOrder(G);
   Graph rtn=newGraph(o);//create a new graph with the same number of verticies as G
   for(int c=1;c<=o;c++)//for each vertex in G
   {
      List A=G->adj[c];
      for(moveTo(A,0);getIndex(A)>=0;moveNext(A))
         append(rtn->adj[c],getElement(A));//replacate each of its edges in the new graph
   }
   return rtn;
}

//prints Graph to file out, in adjacency list form
void printGraph(FILE* out, Graph G)
{
   nullGraph(G,"printGraph()");
   for(int c=1;c<=getOrder(G);c++)//for each index (except the dummy) in adj
   {
      fprintf(out,"%d: ",c);//print the vertex (ie: the index)
      List L=G->adj[c];//then print all of the adjacent verticies (ie: the list)
      if(L!=NULL)//if it's not null (that would send an error)
         printList(out,L);
      fprintf(out,"\n");
   }
}
