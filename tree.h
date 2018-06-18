/*******************************************************************************
  Title          : tree.h
  Author         : Xiaoning Wang
  Created on     : March 15, 2018
  Instructor     : Stewart Weiss
  Course         : CSCI 33500
  Assignment     : Project 2
  Description    : The interface file for the Tree class
  Purpose        : Each tree class object represents a single tree on some street in New York City. 
*******************************************************************************/
#ifndef _TREE_H
#define _TREE_H

#include <iostream>
#include <string>
#include <limits.h>
using namespace std;
using std::string;

/*******************************************************************************   
                              Tree Class Interface
*******************************************************************************/

/** class Tree
 *  Each tree class object represents a single tree on some street in New York City. 
 */
class Tree{
public:
    //A constructor for the class that takes a string from a csv file.
    Tree (const string& treedata);

    //A constructor for creating a new tree. 
    Tree (int id, int diam, string status,
          string health, string spc, int zip,
          string addr, string boro, double
          latitude, double longitude );

    /** This compares the two trees using spc_common as the primary key and tree_id as the secondary key. 
     * It's case insensitive. 
     *  @param: two valid references to Tree objects as argument.
     *  @return true if and only if they have the same species common name (spc_common) and tree_id
     */
    friend bool operator == ( const Tree& t1, const Tree& t2);

     /** This compares the primary key denoted spc_common and secondary key denoted tree_id of the given two Tree objects. 
     * It's case insensitive. 
     *  @param: two valid references to Tree objects as argument.
     *  @return true if t1 is less than t2 in this ordering and false otherwise. 
     */
    friend bool operator < (const Tree& t1,const Tree& t2);

     /** This prints a Tree object onto the given ostream. Each of the members of the Tree object should be printed, 
     * in the exact same order as they are listed in the private members. 
     * Fields should be separated by commas in the output stream. 
     *  @param: a given ostream and a valid reference to a Tree object. 
     *  @return the ostream. 
     */
    friend ostream& operator<< (ostream & os,const Tree & t );

    /** This compares the spc_common of two given Tree objects. 
     * It's case insensitive. 
     *  @param:  two valid references to two Tree objects as argument.
     *  @return true if and only if the two trees have identical spc_common members. 
     */
    friend bool samename ( const Tree & t1, const Tree & t2);

    /** This compares the spc_common of two given Tree objects. 
     * It's case insensitive. 
     *  @param:  two valid references to two Tree objects as argument.
     *  @return true if and only if the two trees have identical spc_common members. 
     */
    friend bool islessname ( const Tree & t1, const Tree & t2);

    /** Below are accessor functions to get the member values accordingly. 
     */
    string common_name() const;
    string borough_name() const;
    string nearest_address() const;
    int diameter() const;
    int zip() const;
    void get_position(double & latitude, double & longitude) const;

    /** Below are public members. 
     */
    Tree *leftChild;
    Tree *rightChild;
    int height;

private:
    string spc_common;//the common name of the tree
    int tree_id ; //a non-negative integer that uniquely identifies the tree
    int  tree_dbh ;//a non-negative integer specifying tree diameter
    string status ; //a string, valid values: Alive ,Dead, Stump , or the empty string
    string health ; //a string, valid values:  Good , Fair,  Poor , or the empty string
    string address;//nearest estimated address to tree
    string boroname ;//valid values: Manhattan , Bronx , Brooklyn , Queens ,Staten Island
    int zipcode ;//a positive five digit integer
    double latitude; // a double floating point number to lacate the tree. 
    double longitude; // a double floating point number to lacate the tree. 
};
#endif //_TREE_H
