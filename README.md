# Processing-2015-New-York-City-Street-Tree-Census-Data

Project2 version 1.0  3/29/2018 @ Hunter college

GENERAL INFORMATION:
---------------------------------------------------------------------------------------------------------------------
This project reads the NYC open data set, TreesCount!, the 2015 Street Tree Census, conducted by volunteers and organized by the NYC Department of Parks & Recreation as well as partner organizations. The data includes information about more than 680,000 trees on the streets of New York City. 

This project reads the data from that data set and save the data in an Avl tree. It allows a user to summarize certain aspects of the data, such as how many trees of a given species are growing, borough by borough, or which trees are within a given distance of a given GPS location. The user will be able to specify a fragment of a species common name, such as oak and the program will display the frequency of occurrence of all types of oak trees throughout the city, such as pin oaks, sawtooth oaks, scarlet oaks, and white oaks.

1. Project2 is designed to run under Linux lab.
2. tree_species class & command class & haversine function are written by Prof.Weiss.
3. The project started from creating the Tree class. Tree class was written on March 15 2018. 
4. Then, AVLtree class was created on March 16 2018. Testing AVLtree class costed a whole day.  
5. The TreeCollection class was created last. It is like a wapper of AVLtree class. It was created on March 18 2018.
6. main.cpp was created at last. It was firstly created on March 20 2018. 
7. The whole project is large. Testing and make each part of class together costed a long time. 
----------------------------------------------------------------------------------------------------------------------

Optimization that have been made. 
----------------------------------------------------------------------------------------------------------------------
1.The string parser method in Tree class was improved from project1. 
2.AVLtree class was first written by refering the information from lecture and text book. Then was revised by testing 
  with Tree class together. 
3.I didn't know how to choose the containers of borough in the TreeCollection class at first. At last I chose to use map.
  I want to know other optimized options.     
----------------------------------------------------------------------------------------------------------------------
