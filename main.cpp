/*******************************************************************************
  Title          : main.cpp
  Author         : Xiaoning Wang
  Created on     : March 18, 2018
  Instructor     : Stewart Weiss
  Course         : CSCI 33500
  Assignment     : Project 2
  Description    : The main function for implement the commands
  Purpose        : call the TreeCollection class to implements the commands. 
*******************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <cstring>
#include <string>
#include "tree_collection.h"
#include "command.h"
//#define csv_file  "2015_trees_MH.csv"//data address

using namespace std;

/*****************************************************************************************
* @ param：a string of common name ，an object of TreeCollection 
* @ return: N/A
* purpose：output all the common names and number of the given string of common name.
*****************************************************************************************/
void tree_info(string &spc_command,TreeCollection& treeCollection)
{
    map<string,int> match_trees_borough;
    map<string,int> all_trees_borough;
    list<string> match_names;
    int all_match_trees_number = 0;
    int all_trees_number = treeCollection.total_tree_count();

    // find the number of the given species name. 
    list<Tree>::iterator iter;
    list<Tree> newTrees = treeCollection.get_all_match_trees(spc_command);
    if(!newTrees.empty()){
    all_match_trees_number = (int)newTrees.size();

    // find the number of the given species_name in each borough.  
     all_trees_borough = treeCollection.get_borough_trees();

    //Traversal all the finding trees and group them according to its located borough name. 
    iter = newTrees.begin();
    while (iter!=newTrees.end()){
        Tree tempTree = *iter++;
        string borough_name = tempTree.borough_name();
        if(match_trees_borough.count(borough_name) > 0){
            match_trees_borough[borough_name]++;
        }else{
            match_trees_borough.insert(pair<string,int> (borough_name,1));
        }
    }

    // output the matching species_name. 
    cout << spc_command << endl;
    cout<<"ALL matching species:"<<endl;
    list<string>all_match_tree_name = treeCollection.get_matching_species(spc_command);
    list<string>::iterator iter2;
    iter2 = all_match_tree_name.begin();
    while (iter2!=all_match_tree_name.end())
    {
        cout << *iter2++ << endl;
    }

    //output the frequency in total. 
        cout << std::left << setw(15) << "Total in NYC:"
        << std::right << setw(15) << all_match_trees_number << "(" << all_trees_number << ")"
        << std::right << setw(15) << setiosflags(ios::fixed) << setprecision(2) << (float)100 * all_match_trees_number/all_trees_number << "%"
        <<endl;

     //output the frequency in each borough:
        cout<<"Frequency by borough:"<<endl;

    //searching all the boroughs and output the number acoordingly. 
    map<string,int>::iterator iter3;
    iter3 = all_trees_borough.begin();
    while (iter3 != all_trees_borough.end()){
        int match_trees_number = 0;
        if(match_trees_borough.count(iter3 -> first) > 0 )
            match_trees_number = match_trees_borough[iter3 -> first];
        string match_borough_name = iter3 -> first;
        int total_trees_number = treeCollection.count_of_trees_in_boro(match_borough_name);
        float borough_percent = 0;
        if(total_trees_number != 0)
            borough_percent = (float)100 * match_trees_number/total_trees_number;

        cout << std::left << setw(15) << match_borough_name + ":"
            << std::right << setw(15) << match_trees_number << "("
            << std::right << setw(15) << total_trees_number<<")"
            << std::right << setw(15) << setiosflags(ios::fixed) << setprecision(2) << borough_percent <<"%"
            <<endl;
        iter3++;
    }
    }else{
        cout<<"No matching tree!"<<endl;
    }

}


/*********************************************
*@ param：TreeCollection objects
*@ return：N/A
*purpose ：output all the tree species_names
**********************************************/
void list_all_name(TreeCollection& treeCollection)
{
    treeCollection.print_common_tree_name(cout);
}

/************************************************************************
*@ param：zipcode, TreeCollection objedts
*@ return:N/A
*purpose：output the species_names and numbers according to the given zipcode. 
*************************************************************************/
void listall_inzip(const int &zipcode, TreeCollection &treeCollection) {
    list<string> match_trees_name;
    map<string, int> match_trees_number;
    if (zipcode / 100000 > 0) {
        cout << "error zip code！" << endl;

    } else {
        match_trees_name = treeCollection.get_all_in_zipcode(zipcode);
        list<string>::iterator iter;
        iter = match_trees_name.begin();
        while (iter != match_trees_name.end()) {
            string treeName = *iter++;
            if (match_trees_number.count(treeName) > 0) {
                match_trees_number[treeName]++;
            } else {
                match_trees_number.insert(pair<string, int>(treeName, 1));
            }
        }
        //output while traversal the tree. 
        map<string, int>::iterator iter2;
        iter2 = match_trees_number.begin();

        while (iter2 != match_trees_number.end()) {
            cout << std::left << setw(25) << iter2->first + ":"
                 << std::right << setw(15) << iter2->second
                 << endl;
            iter2++;
        }
    }
}

/************************************************************************************************
* @ param：langitude, latitude, distance, TreeCollection objects.
* @ return: N/A
* purpose ：output the species_names and numbers according to the given position and distance. 
*************************************************************************************************/
void list_near(double& latitude ,double & longitude, double &dist,TreeCollection& treeCollection){
    list<string> match_trees_name;
    map<string,int>match_trees_number;
    match_trees_name=treeCollection.get_all_near(latitude,longitude,dist);
    list<string>::iterator iter;
    iter = match_trees_name.begin();
    while (iter != match_trees_name.end()) {
        string treeName = *iter++;
        if (match_trees_number.count(treeName) > 0) {
            match_trees_number[treeName]++;
        } else {
            match_trees_number.insert(pair<string, int>(treeName, 1));
        }
    }
    //output while traversal the tree. 
    map<string, int>::iterator iter2;
    iter2 = match_trees_number.begin();

    while (iter2!= match_trees_number.end()){
        cout << std::left << setw(20) << iter2->first + ":"
             << std::right << setw(15) << iter2->second
             << endl;
        iter2++;
    }
}


void readCsv(TreeCollection& treeCollection,ifstream& inFile){
    string lineStr;
    string tempStr;

    while (!getline(inFile, lineStr).eof())
    {

        //insert to the avl tree
//        cout<<lineStr<<endl;
        treeCollection.add_tree(lineStr);
    }

}

int main( int argc,  char* argv[] )
{


        ifstream  fin_csv;
        ifstream  fin_command;
        TreeCollection treeCollection;
        Command   command;
        string    treename;
        int       zipcode;
        double    latitude, longitude, distance;
        bool      result;


        if ( argc < 3 ) {
            cerr << "Usage: " << argv[0] << " commandfile  outputfile\n";
            exit(1);
        }

        fin_csv.open( argv[1]);
        if ( !fin_csv ) {
            cerr << "Could not open" << argv[1] << " for reading.\n";
            exit(1);
        }
        //read csv file 
        readCsv(treeCollection,fin_csv);

        fin_command.open(argv[2]);
        if ( fin_command.fail() ) {
            cerr << "Could not open " << argv[2] << " for reading.\n";
            exit(1);
        }
//    treeCollection.avlTree.print(cout);
        while ( ! fin_command.eof() ) {
            if (!command.get_next(fin_command)) {
                if (!fin_command.eof())
                    cerr << "Could not get next command.\n";
                return 1;
            }

            command.get_args(treename, zipcode, latitude, longitude,
                             distance, result);


            switch (command.type_of())
            {
                case tree_info_cmmd:

                    cout << "tree_info  " << treename << endl;
                    tree_info(treename,treeCollection);
                    cout<<"---------------------------------------------------"<<endl;
                    break;
                case listall_names_cmmd:
                    cout << "command:listall_names  " << endl;
                    list_all_name(treeCollection);
                    cout<<"---------------------------------------------------"<<endl;
                    break;
                case list_near_cmmd:
                    cout << "command:list_near  " << latitude << " " << longitude
                         << " " << distance  << endl;
                    list_near(latitude,longitude,distance,treeCollection);
                    cout<<"---------------------------------------------------"<<endl;
                    break;
                case listall_inzip_cmmd:
                    cout << "command:listall_inzip  " << zipcode << endl;
                    listall_inzip(zipcode,treeCollection);
                    cout<<"---------------------------------------------------"<<endl;
                    break;
                case bad_cmmd:
                    cout << "command:bad command " << endl;
                    cout<<"---------------------------------------------------"<<endl;
                    break;
                default:
                    break;
            }
        }
    }

