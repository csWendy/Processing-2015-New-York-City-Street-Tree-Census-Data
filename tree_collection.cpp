/*******************************************************************************
  Title          : tree_collection.cpp
  Author         : Xiaoning Wang
  Created on     : March 18, 2018
  Instructor     : Stewart Weiss
  Course         : CSCI 33500
  Assignment     : Project 2
  Description    : The implementation for the TreeCollection class
  Purpose        : The TreeCollection class provides the functionality to the main 
                    program for sorting and accessing tree data. 
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <vector>
#include "tree_collection.h"

using namespace std;
using std::string;

/******************************************************************************************************
                              Constructors and destructor
******************************************************************************************************/

TreeCollection::TreeCollection():avlTree(),treeSpecies()
{
    BoroughTrees.insert(pair<string,int>("Bronx",0));
    BoroughTrees.insert(pair<string,int>("Staten Island",0));
    BoroughTrees.insert(pair<string,int>("Queens",0));
    BoroughTrees.insert(pair<string,int>("Manhattan",0));
    BoroughTrees.insert(pair<string,int>("Brooklyn",0));
}
TreeCollection::~TreeCollection() {

}


/******************************************************************************************************
                                         Counter Methods
******************************************************************************************************/
//return the # of nodes. 
int TreeCollection::total_tree_count() const 
{
    return TreeCollection::avlTree.GetNumber();
}

//return the number of Tree objects with the given species_name. 
int TreeCollection::count_of_tree_species(const string& species_name)  
{
    Tree *tempTree = new Tree(0, 0, "", "", species_name, 0,"", "",0, 0 );
    list<Tree> match_trees = TreeCollection::avlTree.findallmatches(*tempTree);
    if(!match_trees.empty())
        return (int)match_trees.size();
    return 0;
}

/******************************************************************************************************
                                Serching Methods for finding a given species_name
******************************************************************************************************/

//return a list<srting> of all the matching species_name.
list<string> TreeCollection::get_matching_species(const string &species_name) const 
{
    list<string> match_names = TreeCollection::treeSpecies.get_matching_species(species_name);
    return match_names;
}

//return a list<Tree> of all the matching Tree objects with the given species_name.
list<Tree> TreeCollection::get_all_match_trees(const string &species_name) 
{
    list <string> match_name = get_matching_species(species_name);
    list <Tree> all_match_trees;

    list <string>::iterator iter;
    iter = match_name.begin();

    while (iter!= match_name.end()){
//        cout<<*iter<<endl;
        Tree *node=new Tree(0, 0, "", "", *iter, 0,"", "",0, 0 );
        list<Tree> tempTrees = TreeCollection::avlTree.findallmatches(*node);
//        cout<<tempTrees.size()<<endl;
        all_match_trees.merge(tempTrees);
        iter ++;
    }

    return all_match_trees;
}

/******************************************************************************************************
                    Adding a new Tree object and update the tree species and boroughTrees. 
******************************************************************************************************/

//Add a Tree object to the colleciton 
void TreeCollection::add_tree(const string &lineStr) {
//  Add the node to the AVL tree. 
    Tree *node = new Tree(lineStr);
    TreeCollection::avlTree.Insert(*node);

    // Add the species_name to the container of tree_species. 
    string species_name = node -> common_name();
    string borough_name = node -> borough_name();
    TreeCollection::treeSpecies.add_species(species_name);
    // Add the number of trees to its coresponding borough. 
    if(TreeCollection::BoroughTrees.count(borough_name) > 0){
        TreeCollection::BoroughTrees[borough_name] ++ ;
    }else{
        TreeCollection::BoroughTrees.insert(pair<string,int>(borough_name,1));
    }

}

/********************************************************************************************************************
                         Serching Methods for species_names in a given zipcode or a given point and distance. 
*********************************************************************************************************************/

//finding a species_name by zipcode.
list<string> TreeCollection::get_all_in_zipcode(const int zipcode) const {
    list<Tree> newTrees;
    list<string> match_name;
    newTrees = TreeCollection::avlTree.findallmatchesbyzip(zipcode);
    list<Tree>::iterator iter;
    iter = newTrees.begin();
    while (iter != newTrees.end()){
        Tree tempTree = *iter++;
        string treeName = tempTree.common_name();
        match_name.push_back(treeName);
    }
    return match_name;
}


//get the total number of trees in each borough 
map<string,int> TreeCollection::get_borough_trees() const 
{
    return TreeCollection::BoroughTrees;
}

//get the nunber of trees in a specified zipcode. 
int TreeCollection::count_of_trees_in_boro(const string& boro_name)const  
{
    map<string,int> boro_trees = TreeCollection::BoroughTrees;
    if(boro_trees.count(boro_name) > 0)
     return boro_trees[boro_name];
    return 0;
}

//get a list<string> of all tree species_names within a given point and distance. 
list<string> TreeCollection::get_all_near(double latitude, double longitude,double distance)const 
{
    list<Tree> newTrees;
    list<string> match_name;
    newTrees = TreeCollection::avlTree.findallmatchesbyzero(latitude, longitude, distance);
    list<Tree>::iterator iter;
    iter = newTrees.begin();
    while (iter != newTrees.end()){
        Tree tempTree = *iter++;
        string treeName = tempTree.common_name();
        match_name.push_back(treeName);
    }
    return match_name;
}

/******************************************************************************************************
                              Print Methods for all tree species_names.
******************************************************************************************************/


void TreeCollection::print_common_tree_name(ostream& fout) const 
{
    TreeCollection::treeSpecies.print_all_species(fout);
}

//map<string,int> TreeCollection::get_near_trees(const double& latitude,const double& longitude,const double& distance) {
////    cout<<"cs"<<endl;
////    TreeCollection::avlTree.findallmatchesbyzero(latitude,longitude,distance);
//    get_all_near(latitude,longitude,distance);
//
//    return TreeCollection::NearTrees;
//}

