/*******************************************************************************
  Title          : avl.h
  Author         : Xiaoning Wang
  Created on     : March 16, 2018
  Instructor     : Stewart Weiss
  Course         : CSCI 33500
  Assignment     : Project 2
  Description    : The interface file for the AVL class
  Purpose        : The AVL class represent an avl tree object that stores the real trees. 
  Modifications  :   
*******************************************************************************/
#ifndef _AVL_H
#define _AVL_H
#include <iostream>
#include <list>
#include "tree.h"
using namespace std;

/*******************************************************************************   
                              AVL Class Interface
*******************************************************************************/

class AVLTree
{

public:
    AVLTree(); //default constructor. 
    AVLTree(const AVLTree & tree); // copy constructor. 
    ~AVLTree(); //destructor. 

// The four functons below are search methods :
    /** find() searches for a given tree object according to the pair of keys (spc_common, tree_id) in the avl tree. 
  *  @param: a valid references to Tree objects is given. 
     @pre Avl tree is not empty and valid. Avl tree is not empty and valid. 
  *  @return the reference of the Tree object found on the avl tree with the same species common name (spc_common) and tree_id as the given tree object.
  */
    const Tree & find( const Tree& x ) const ;

    /** findMin() searches for the smallerst element in a particular part of the avl tree. 
  *  @pre Avl tree is not empty and valid. 
  *  @return the reference of the Tree object found on the avl tree with the smallest same species common name (spc_common).  
  *   If the tree objects have same common name, then return the one with a smaller tree_id. 
  */
    const Tree & findMin () const ;

    /** findMax() searches for the biggest element in a particular part of the avl tree. 
  *  @pre Avl tree is not empty and valid. 
  *  @return the reference of the Tree object found on the avl tree with the biggest same species common name (spc_common). 
  *   If the tree objects have same common name, then return the one with a bigger tree_id. 
  */
    const Tree & findMax () const ;

    /** findallmatch() searches the entire tree for all occurrences of Tree objects that match its Tree argument. 
  *  @param: a valid references to Tree objects is given. 
     @pre Avl tree is not empty and valid. 
  *  @return the reference to a list of Tree object found on the avl tree that matched according to the matching rule. 
  */
    list < Tree > findallmatches ( const Tree & x )  const;

//The function below is the Traversal function.
/** print() prints the Tree objects onto the ostream using inorder traversal.Each of the members of the Tree object is printed,
  * in the exact same order as they are above , e.g., with the tree spc_common name first , then the tree_id. 
  * Fields should be separated by commas in the output stream.
  *  @param:  ostream is open for writing. 
  *  @print the entire tree on to the open ostream. 
  */
    void print(ostream& out) const;

 //The three functions below are Tree modifiers:
    void Insert(Tree& x); // insert element x. 
    void remove(Tree& x); // remove element x.
    void clear(); // empty the tree. 

// The two functions below are methosd to adding- getting all trees in a zipcode, or near a given point. 
/** findallmatchesbyzero() find all nodes that near a given point within the given distance. Wrapper of the according private function. 
  *  @param: the given zipcode 
  *  @return a tree pointer that points to the node near the given point.  
  */
    list <Tree> findallmatchesbyzip (const int& zipcode)const;

 /** findallmatchesbyzero() find all nodes that near a given point within the given distance. Wrapper of the according private function. 
  *  @param: the given latitude and langitude of the point; the given distance. 
  *  @return a tree pointer that points to the node near the given point.  
  */
    list <Tree> findallmatchesbyzero (double&latitude,double& longitude, double& distance)const;

    int GetNumber() const; // get the total number of nodes in the tree. 
   // bool Updata(int,int);


private:
    Tree *root;

    /***********************************************************
     functons below are private helper functons. 
    ************************************************************/
    Tree *Search(const Tree&,Tree *)const ;

/** findallmatches() find all nodes that samename() and islessname() with the given Tree reference. 
 *  @Param:the Tree reference that we want to find; a list of tree(we will return this list of tree in the public function); the current node.
  *  @return a tree pointer that points to the node with samename() or islessname() with the given Tree refernce. 
  */
    Tree *findallmatches(const Tree &,list<Tree>&,Tree *)const;

/** findallmatchesbyzip() find all nodes that has the same zipcode as given. 
  *  @param: the given zipcode; a list of tree(we will return this list of tree in the public function); the current node. 
  *  @return a tree pointer that points to the node with the same zipcode as given. 
  */
    Tree *findallmatchesbyzip(const int&,list<Tree>&,Tree *)const;

/** findallmatchesbyzero() find all nodes that near a given point within the given distance. 
  *  @param: the given latitude and langitude of the point and the given distance; a list of tree(we will return this list of tree in the public function); the current node. 
  *  @return a tree pointer that points to the node near the given point.  
  */
    Tree *findallmatchesbyzero(double &, double &, double &,list<Tree>&,Tree *)const;

    //The four functions below are the rotation functions. 
    Tree *LeftRotate(Tree *);
    Tree *LeftAndRightRotate(Tree *);
    Tree *RightRotate(Tree *);
    Tree *RightAndLeftRotate(Tree *);

    int GetHeight(Tree *); // return the height of the tree. 
    int GetNumber(Tree *)const ; // get the total number of nodes in the tree. 
    void InOrderPrint(Tree *,ostream &)const;//InOrderPrint() prints all nodes in the tree in order. 
    void SufOrderDelete(Tree *);// delete the tree in post order. 
    //void RotatePrint(Tree *,int);
    Tree *Insert(Tree&,Tree *);//insert a node to the tree. 
    Tree *Delete(bool&,Tree&,Tree *); //delete a node from the tree. 
    double haversine(double,double,double,double)const; //computer the distance vetween two points on sphere. 

};
#endif //_AVL_H
