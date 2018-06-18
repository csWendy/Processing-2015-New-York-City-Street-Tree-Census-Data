
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <cstring>
#include "command.h"

Command::Command() {}
bool Command::get_next(istream &in) {
    type = null_cmmd;
    if (!in.eof()) {
        string str;
        if (std::getline(in, str)) {

            stringstream ss(str);
            string item;
            vector<string> lineArray;
            vector<string> ::iterator iter;
            char *p = strtok(const_cast<char*>(str.c_str())," \t");
            while (p) {

                lineArray.push_back(p);
                p=strtok(NULL," \t");
            }

            if (lineArray.size() >= 1) {
                type = bad_cmmd;
                if (lineArray[0] == "tree_info") {
                    if (!lineArray[1].empty()) {
                        type = tree_info_cmmd;
                        tree_to_find = lineArray[1];
                    }
                } else if (lineArray[0] == "listall_names") {
                    type = listall_names_cmmd;

                } else if (lineArray[0] == "listall_inzip") {
                    if (!lineArray[1].empty()) {
                        type = listall_inzip_cmmd;;
                        zip = atoi(lineArray[1].c_str());
                    }

                } else if (lineArray[0] == "list_near") {

                    if (lineArray.size()>3&& (!lineArray[1].empty() && !lineArray[2].empty() && !lineArray[3].empty())) {
                        type = list_near_cmmd;
                        latitude = atof(lineArray[1].c_str());
                        longitude = atof(lineArray[2].c_str());
                        distance = atof(lineArray[3].c_str());
                    }

                }else{

                    return false;
                }
            } else {
                type = null_cmmd;
            }
        }

    }
    return true;

}


Command_type Command::type_of () const {

    return type;
}


void  Command::get_args  (
        string    & arg_tree_to_find,
        int       & arg_zip,
        double    & arg_latitude,
        double    & arg_longitude,
        double    & arg_distance,
        bool      & result
)const {
    switch (type_of()){
        case tree_info_cmmd:
            arg_tree_to_find= tree_to_find ;
            break;
        case listall_inzip_cmmd:
            arg_zip=zip;
            break;
        case list_near_cmmd:
            arg_latitude=latitude;
            arg_longitude=longitude;
            arg_distance= distance;
            break;
        case null_cmmd:
            break;
        case bad_cmmd:
            break;
        default:
            break;
    }
}
