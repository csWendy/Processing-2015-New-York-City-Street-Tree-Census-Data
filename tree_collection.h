/*******************************************************************************
  Title          : tree_collection.h
  Author         : Xiaoning Wang
  Created on     : March 18, 2018
  Instructor     : Stewart Weiss
  Course         : CSCI 33500
  Assignment     : Project 2
  Description    : The interface for the TreeCollection class
  Purpose        : The TreeCollection class provides th functionality to the main 
                    program for sorting and accessing tree data. 
*******************************************************************************/
#ifndef TREE_COLLECTION_H
#define TREE_COLLECTION_H

#include <iostream>
#include <string>
#include <list>
#include <map>
#include "tree_species.h"
#include "tree.h"
#include "avl.h"
using namespace std;
using std::string;

/*******************************************************************************   
                              TreeCollection Class Interface
*******************************************************************************/

class TreeCollection
{
public:
    TreeCollection(); //constructor
    ~TreeCollection(); //destructor

    /** total_tree_count() return the total number of Tree objects stored in the collection. 
     */
    int total_tree_count() const; 

    /**count_of_tree_species() returns the number of Tree objects in the collection whose spc_common species name matches 
    *the species_name specified by the parameter.
    * @param: a string of species_name 
    * @return the number of trees with the given name. return 0 if the species_name is non_existent. 
    */ 
    int count_of_tree_species ( const string & species_name ) ;

     /**count_of_trees_in_boro() returns the number of Tree objects located in the borough.
    * @param: a string of borough name 
    * @return the number of Tree objects located in the borough.  
    */ 
    int count_of_trees_in_boro(const string & boro_name )const;

   /**get_matching_species() returns a list<string> object containing a list of all of the actual tree species that match 
    * a given parameter string species_name.
    * @param: a string of species name 
    * @return a list of all of the actual tree species that match a given parameter string species_name.
    */ 
    list<string> get_matching_species(const string & species_name) const;

     /**get_all_in_zipcode() returns a list<string> object containing a list of all of the actual tree species that located
    * in the given zipcode.  
    * @param: a valid zipcode.
    * @return a list of all of the actual tree species that located in the given zipcode. 
    */ 
    list<string> get_all_in_zipcode(const int zipcode)const;


    /**get_all_near() returns a list<string> object containing a list of all of the actual tree species that located
    * within distance kilometers from the GPS position(latitude, longtitude).
    * @param: double latitude, double longitude,double distance
    * @return a list of all of the actual tree species that located within distance kilometers from the GPS position(latitude, longtitude).
    */ 
    list<string> get_all_near( double latitude, double longitude,double distance)const;

    /**add_tree() inserts a new Tree object to the AVL tree and add(no duplicate) its species_name to the species container and update the number 
    * of Tree objectsin the corresponding borough. 
    * @param: a string from the csv file. 
    * @return: N/A 
    */ 
    void add_tree(const string &lineStr);

    /**get_borough_trees() return the number of Tree objects in the specified borough. 
    */ 
    map<string,int> get_borough_trees()const;

     /**get_all_match_trees() returns a list<tree> object containing a list of all of the Tree objects that match a given string of species_name. 
    * @param: a string of a species_name. 
    * @return: a list of Tree objects. 
    */ 
    list<Tree> get_all_match_trees(const string & species_name);

    /**print_common_tree_name() prints all stored species names on the given ostream&. Just call the SpeciesName::print_all_species(ostream & out) const;    
    * @param: a valid ostream& 
    * @return:N/A
    */ 
    void print_common_tree_name(ostream&)const;

private:
    /** The encapsulated three containers
    */
    AVLTree avlTree;
    TreeSpecies treeSpecies;
    map <string,int> BoroughTrees;
};
#endif //TREE_COLLECTION_H
