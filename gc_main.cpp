// Dhruv Jain
// 4/16/21
// Graph Creator
//fully working without dikstra algorithm

#ifndef graph1_MAIN
#define graph1_MAIN

#include <iostream>
#include <cstring>
#include <fstream>
#include <string.h>
#include <math.h>
#include <iomanip>
#include <stdlib.h>

using namespace std;

class vertex //class for vertexs
{
  
 public:
  vertex(char *);
  ~vertex();
  char* get_label();
  void set_label(char *);
 

  char label [10];
  int index;
  vertex *next;
};

class edge //class for edges
{
  //add constructor {id = 1}
 
 public:
  edge(char *, char *, int);
  ~edge();
  
  char start[10];
  char end[10];
  int weight;
  edge *next;
  bool state;
};

vertex::vertex(char *label1){ //constructor for vertexs
 strcpy(label, label1);
 next = NULL;
}

vertex::~vertex(){ //destructor for vertexs
  index = -1;
  next = NULL;
}

char* vertex::get_label(){
  return label;
}

void vertex::set_label(char *l1) {
  strcpy(label, l1);
}

edge::edge(char*start1, char*end1, int w){ //constructor for edges
  strcpy(start, start1);
  strcpy(end, end1);
  weight = w;
  next = NULL;
  state = true;
}

edge::~edge(){ //destructor for edges
  weight = 0;
  next = NULL;
  state = false;
}

class graph1
{
  public:
    void add_vertex(char *);
    void remove_vertex(char *);
    void add_edge(char *, char *, int);
    void remove_edge(char *, char *);
    void print_adjacency();
    void find_shortest_path(char *, char *);
    int find_vertex_index(char *);

    
    vertex* vertex_l;
    edge* edge_l;
    int total_vertices;
    int total_edges;
    edge* last_edge;
    vertex* last_vertex;
    
};

void graph1::add_edge(char *start, char *end, int w){ //fuction to add an edge
  edge *e = new edge(start, end, w);
  if(edge_l == NULL)
  {
    //first edge
    edge_l = e;
    e->state = true;
  }
  if(last_edge != NULL) {
    last_edge->next = e; 
  }
  last_edge = e;
  total_edges++;
}
  
void graph1::remove_edge(char *start, char *end){ //function to remove an edge
  edge *previous = edge_l;
  edge *current = edge_l;
  if(edge_l == NULL)
    return;
  for (;;)
  {
      if((strcmp(current->start, start) == 0) && 
       (strcmp(current->end, end) == 0) && current->state == true){
        current->state = false;
        /* 
        if (current == previous){ //Single edge in the graph1 or asked to remove teh first edge
          if(current == edge_l){
              edge_l = current->next;
          }
          if(current == last_edge)
            last_edge = NULL;
            delete(current);
           
          if(edge_l == NULL)
                last_edge = NULL;
        } else {
           //fixup previous pointer and then delete current
           previous->next = current->next;
           if(current == last_edge)
             last_edge = previous;
           delete(current);
        }
        */
        total_edges--;
        //break;
    }
    previous = current;
    current = current->next;
    if(current == NULL)
      break;
  }
  cout << "total edges: " << total_edges << endl;
}

void graph1::add_vertex(char *label){ //function to add an edge

  // MAke sure this label does not exist in the graph, to avoid duplicates
  vertex *current = vertex_l;
  for (int i = 0; i < total_vertices; i++)
  {
    if(strcmp(current->label, label) == 0)
    {
      cout << "vertex already exists, pick another label" << endl;
      return;
    }
    current = current->next;
    if(current == NULL)
      break;
  }
  // NO duplication, so add anew one
  vertex *n = new vertex(label);
  if(vertex_l == NULL)
  {
    //first vertex
    vertex_l = n;
    n->index = 0;
  }
  if(last_vertex != NULL) {
    last_vertex->next = n;
    n->index = total_vertices; 
  }
  last_vertex = n;
  total_vertices++;
}

void graph1::remove_vertex(char *label){ //function to remove a vertex
  //remove the vertex
  vertex *previous = vertex_l;
  vertex *current = vertex_l;
  if(vertex_l == NULL)
    return;
  
  for (int i = 0; i < total_vertices; i++)
  {
    if((strcmp(current->label, label) == 0)){
         if (current == previous){ //Single vertex in the graph Or asked to delete the first vertex
            if(current == vertex_l) {
              vertex_l = current->next;
            }  
            if(current == last_vertex)
              last_vertex = NULL;
            delete(current);
            if (vertex_l == NULL)
              last_vertex = NULL;
         }else {
           //fixup previous pointer and then delete current
           previous->next = current->next;
           if(current == last_vertex)
            last_vertex = previous;
           delete(current);
         }
         total_vertices--;
         break;
    }
    previous = current;
    current = current->next;
  }
  cout << "done removing the vertex, total:" << total_vertices << endl;
  
  //fixup index of vertices
  current = vertex_l;
  for (int i = 0; i < total_vertices; i++)
  {
    current->index = i;
    current = current->next;
  }

  // remove all edges that have this vertex
  edge *current_edge = edge_l;
  edge *previous_edge = edge_l;
  if(current_edge == NULL)
    return;
  //int temp_total = total_edges;
  for (;;)
  {
    if((strcmp(current_edge->start, label) == 0) || 
       (strcmp(current_edge->end, label) == 0))
       {
        current_edge->state = false;
        /*
        if (current_edge == previous_edge){ //Single edge in the graph1 or the first edge matches
          if(current_edge == edge_l){
              edge_l = current_edge->next;
          }
          if(current_edge == last_edge)
            last_edge = NULL;
          delete(current_edge);
          if(edge_l == NULL)
              last_edge = NULL;
        } else {
           //fixup previous pointer and then delete current
           previous_edge->next = current_edge->next;
           if(current_edge == last_edge)
             last_edge = previous_edge;
           delete(current_edge);
         }
         */
         total_edges--;
         //need to continue, because there might be more edges
      }
      previous_edge = current_edge;
      current_edge = current_edge->next;
      if(current_edge == NULL)
        break;
  }
  cout << "total edges: " << total_edges << endl;
  cout << "total vertices: " << total_vertices << endl;
}

int graph1::find_vertex_index(char * label)
{
  vertex * curr = vertex_l;
  for (int i = 0; i < total_vertices; i++ )
  {
      if(strcmp(label, curr->label) == 0)
        return curr->index;
      else
        curr = curr->next;
  }
  return -1;
}

void graph1::print_adjacency(){ //method to print adjecancy matrix
  // For a graph1 with n vertices print nxn matrix, with the columns and rows showing all the vertice label
  // Each postion in the matrix shows if teh column vertex has a route to the row vertex. 
  // IF it does, print T, if no print F
  char adjacency[20][20];

  for (int i = 0; i < total_vertices; i++){
    for (int j = 0; j < total_vertices; j++){
      adjacency[i][j] = 'F';
    }
  }

  // initialize the positions with T, if teh edge exits
  edge *curr = edge_l;
  int loc_x = -1;
  int loc_y = -1;
 
  cout << "total edges: " << total_edges << endl;
  //for (int k = 0; k < total_edges; k++)
  for (;;)
  {
    if(curr == NULL)
      break;
    loc_x = find_vertex_index(curr->start);

    loc_y = find_vertex_index(curr->end);

    if((loc_x > -1) && (loc_y > -1) && (curr->state == true))adjacency[loc_x][loc_y] = 'T';
    //if((loc_x > -1) && (loc_y > -1))adjacency[loc_x][loc_y] = 'T';
    curr = curr->next;
  }

  vertex *curr_v = vertex_l;
  //Now print
  cout << "\t";
  for (int i = 0; i < 20; i++){
    //print the label of the vertices for the first row
    if (curr_v != NULL){
      cout << curr_v->label;
      cout << "\t";
      curr_v = curr_v->next;
    }
  }
  cout << endl;
  //reinitialize the current vertex
  curr_v = vertex_l;
  for (int i = 0; i < total_vertices; i++){
    //print the label of the vertex in teh first column
    if (curr_v != NULL){
          cout << curr_v->label;
          cout << "\t";
        for (int j = 0; j < total_vertices; j++)
        {
          cout << adjacency[i][j];
          cout << "\t";
        }
      
      curr_v = curr_v->next;
      cout << endl;
    }
  }
}

void find_shortest_path(char * v_label1, char * v_label2)
{
  //frst find label 1
  // then use djikstar algorithm
  // keep track of all the routes
  //print the route with smallest weight , the node traversed and the total weight.
  //print all the routes
}

int main (){ //main method
  graph1 *g = new graph1();
  //ask the user how many vertices to create, no more than 20, say n
  //in a for loop ask the user to add vertices, create each new vertex and add initialize teh pointer in the graph1
  char input[100];
  char label1[10];
  char label2[10];
  int weight;
  while(true)
  {
    cout << "Please enter ADD, PRINT_ADJACENCY, FIND_S_PATH or DELETE. If you would like to close the application enter QUIT" << endl;
	  cin >> input;
	  if(strcmp(input,"ADD")==0){
      cout << "please enter: VERTEX or EDGE" << endl;
      //input = '\0';
      cin >> input;
      if(strcmp(input, "VERTEX") == 0) {
        cout << "enter a label character such as A, B etc" << endl;
        cin >> label1;
        g->add_vertex(label1);
      }
      if(strcmp(input, "EDGE") == 0) {
        cout << "type a start label character such as A, B etc" << endl;
        cin >> label1;
        cout << "type an end label character such as A, B etc" << endl;
        cin >> label2;
        cout << "Enter a weight greater than or equal to 1 " << endl;
        cin >> weight; 
        g->add_edge(label1, label2, weight);
      }

    }else if(strcmp(input,"DELETE")==0){
      cout << "please enter: VERTEX or EDGE" << endl;
      //input = '\0';
      cin >> input;
      if(strcmp(input, "VERTEX") == 0) {
        cout << "enter a label character such as A, B etc" << endl;
        cin >> label1;
        g->remove_vertex(label1);
      }
      if(strcmp(input, "EDGE") == 0) {
        cout << "type a start label character such as A, B etc" << endl;
        cin >> label1;
        cout << "type an end label character such as A, B etc" << endl;
        cin >> label2;
        g->remove_edge(label1, label2);
      }
    }else if(strcmp(input,"PRINT_ADJACENCY")==0){
      g->print_adjacency();
    }else if(strcmp(input,"FIND_S_PATH")==0){
	    cout << "Not implemented yet!";
    }else if(strcmp(input,"QUIT")==0){
      //TODO Delete the graph1 by calling the destructor
      //Otherwise this will cause lost memory
	      break;

    }
  }
    
}
#endif
