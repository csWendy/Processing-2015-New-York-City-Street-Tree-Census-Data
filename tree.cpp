/******************************************************************************
  Title          : tree.cpp
  Author         : Xiaoning Wang
  Created on     : March 15, 2018
  Instructor     : Stewart Weiss
  Course         : CSCI 33500
  Assignment     : Project 2
  Description    : The implementation of Tree class
  Purpose        : Each tree class object represents a single tree on some street in New York City. 
  Modifications  : 
*******************************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <cctype>
#include "tree.h"
using namespace std;
using std::string;

/******************************************************************************************************
                                               Constructors 
******************************************************************************************************/

//constructor
Tree::Tree (int id, int diam, string status, string health, string spc, int zip,
      string address, string boro, double latitude, double longitude ){
    Tree::tree_id = id;
    Tree::tree_dbh = diam;
    Tree::status = status;
    Tree::health = health;
    Tree::spc_common = spc;
    Tree::zipcode = zip;
    Tree::address = address;
    Tree::boroname = boro;
    Tree::latitude = latitude;
    Tree::longitude = longitude;
    Tree:: height = 0;
    Tree::leftChild = NULL;
    Tree::rightChild = NULL;
}

//constructor
Tree::Tree(const string &treedata) {
    stringstream ss(treedata);
    string str;
    vector<string> lineArray;
    string pre_str; // Temp string 
    short int flag = 0;// set a flag 
    while (getline (ss, str,',')){
        size_t position = str.find('\"'); //find the positon of "" in str.  
        if (position != string::npos || flag == 1) { 
//            cout << "Found! position is : " << position << endl;
            if (position == 0){ // find the first ". 
                pre_str = str; // assing str to pre_str in order to read every string seprated by comma inside the quotation mark. 
                flag = 1; // set the flag to 1. 
                continue; // continue the loop . 
            } 
            else { // find the second quotation mark. 
                str += "," + pre_str; // the strings inside the quotation mark is considered to be one long string. 
                if(position == string::npos) // find the second quotation mark. 
                    continue;
                else
                    flag = 0; // the second quotation mark is not found, reset the flag. 
            }
        }

        lineArray.push_back(str); //push str to the vector. 
    }

    if(lineArray.size() < 41){ // the case that the # of columns in the original data is not 41. 
        Tree::tree_id = -1;
        Tree::spc_common = "error data";
        Tree:: height = 0;
        Tree::leftChild = NULL;
        Tree::rightChild = NULL;
    }

    else {

    if(lineArray[9].empty())
        lineArray[9]="stump or dead tree"; // the 9th column in the original data is empty if the tree is dead or stump. 
    Tree::tree_id = atoi(lineArray[0].c_str());
    Tree::spc_common = lineArray[9];
    Tree::tree_dbh = atoi(lineArray[3].c_str());
    Tree::status = lineArray[6];
    Tree::health = lineArray[7];
    Tree::zipcode = atoi(lineArray[25].c_str());
    Tree::address = lineArray[24];
    Tree::boroname = lineArray[29];
    Tree::latitude = atof(lineArray[37].c_str());
    Tree::longitude = atof(lineArray[38].c_str());
    Tree::height = 0;
    Tree::leftChild = NULL;
    Tree::rightChild = NULL;
    }
}

/******************************************************************************************************
                              Overload operators and Comparing Methods.  
******************************************************************************************************/

bool operator == (const  Tree& t1, const Tree& t2) {
    string low_t1_name, low_t2_name;
    if(t1.spc_common !="" && t2.spc_common !="" ){
        transform(t1.spc_common.begin(), t1.spc_common.end(),back_inserter(low_t1_name), ::tolower);
        transform(t2.spc_common.begin(), t2.spc_common.end(),back_inserter(low_t2_name), ::tolower);
            if(low_t1_name == low_t2_name && t1.tree_id == t2.tree_id){
             return true;
        }
    }
    return false;
}

bool operator < (const  Tree& t1, const Tree& t2){
    string low_t1_name, low_t2_name;
    transform(t1.spc_common.begin(), t1.spc_common.end(),back_inserter(low_t1_name), ::tolower);
    transform(t2.spc_common.begin(), t2.spc_common.end(),back_inserter(low_t2_name), ::tolower);
    if(low_t1_name.compare(low_t2_name) < 0){
        return true;
    }
    else if(low_t1_name == low_t2_name ){
        if(t1.tree_id < t2.tree_id)
            return true;
    }
    return false;
}

ostream& operator<<(ostream &os, const Tree &t) {
    os<<t.spc_common<<","
      <<t.tree_id<<","
      <<t.tree_dbh<<","
      <<t.status<<","
      <<t.health<<","
      <<t.address<<","
      <<t.boroname<<","
      <<t.zipcode<<","
      <<t.latitude<<","
      <<t.longitude;
    return os;
}

// compare the spc_common_name only. 
 bool samename ( const Tree & t1, const Tree & t2){
//    cout<<t1.common_name()<<"$"<<t2.common_name()<<endl;
    string low_t1_name,low_t2_name;
    transform(t1.spc_common.begin(), t1.spc_common.end(),back_inserter(low_t1_name), ::tolower);
    transform(t2.spc_common.begin(), t2.spc_common.end(),back_inserter(low_t2_name), ::tolower);
    if(low_t1_name==low_t2_name)
        return true;
    return false;

}

// compare the spc_common_name only. 
 bool islessname ( const Tree & t1, const Tree & t2){
//     cout<<t1.common_name()<<"$"<<t2.common_name()<<endl;
     string low_t1_name,low_t2_name;
     transform(t1.spc_common.begin(), t1.spc_common.end(),back_inserter(low_t1_name), ::tolower);
     transform(t2.spc_common.begin(), t2.spc_common.end(),back_inserter(low_t2_name), ::tolower);
     if(low_t1_name.compare(low_t2_name) < 0)
         return true;
     return false;
}

/******************************************************************************************************
                                  Access Methods
******************************************************************************************************/

string Tree::common_name() const {
    return Tree::spc_common;
}

string Tree::borough_name() const {

    return Tree::boroname;
}

string Tree::nearest_address() const {
    return Tree::address;
}

int Tree::zip()const {
    return Tree::zipcode;
}

int Tree::diameter() const {
    return Tree::tree_dbh;
}

void Tree::get_position(double &latitude, double &longitude) const {
    latitude = Tree::latitude;
    longitude = Tree::longitude;
}

