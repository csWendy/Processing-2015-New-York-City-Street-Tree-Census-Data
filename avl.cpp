/******************************************************************************
  Title          : avl.cpp
  Author         : Xiaoning Wang
  Created on     : March 16, 2018
  Instructor     : Stewart Weiss
  Course         : CSCI 33500
  Assignment     : Project 2
  Description    : The implementation for AVL class
  Purpose        : The AVL class represent an avl tree object that stores the real trees.
  Modifications  : 
*******************************************************************************/
#include<iostream>
#include<algorithm>
#include <fstream>
#include <sstream>
#include"avl.h"
#include"tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

#define R 6372.8
#define TO_RAD (3.1415926536 / 180)
using namespace std;

/******************************************************************************************************
                              Constructors and destructor
******************************************************************************************************/

AVLTree::AVLTree()
{
    root = NULL;
}

AVLTree::AVLTree(const AVLTree & tree)
{
    root = NULL;
    if(NULL == tree.root)
        return ;
    AVLTree::Insert(*tree.root);
    SufOrderDelete(tree.root -> leftChild);
    SufOrderDelete(tree.root -> rightChild);
}

AVLTree::~AVLTree(){}

/******************************************************************************************************
                    Methods for getting tree heigh and nodes number 
******************************************************************************************************/

int AVLTree::GetHeight(Tree *tempNode)
{
    return NULL == tempNode ? -1 : tempNode -> height;
}

int AVLTree::GetNumber(Tree *tempNode)const
{
    if(NULL == tempNode)
        return 0;
    return GetNumber(tempNode -> leftChild) + GetNumber( tempNode -> rightChild) + 1;
}

int AVLTree::GetNumber()const
{
   return GetNumber(this -> root); // ‘this’ pointer is a constant pointer that holds the memory address of the current object.
}


/******************************************************************************************************
                                 Serch Methods
******************************************************************************************************/
Tree *AVLTree::Search(const Tree& searchNode,Tree *tempNode)const
{
    if(NULL == tempNode)
        return NULL;
    else if(searchNode == *tempNode)
        return tempNode;
    else if(searchNode < *tempNode)
        return Search(searchNode,tempNode -> leftChild);
    return Search(searchNode,tempNode -> rightChild);
}

const Tree& AVLTree::find(const Tree &searchNode) const
{
    Tree *node = Search(searchNode,root);
    return *node;
}

const Tree& AVLTree::findMin() const 
{
    Tree *TreeNode = root;
    if(TreeNode == NULL || TreeNode -> leftChild == NULL)
        return *TreeNode;
   do{
       TreeNode = root -> leftChild;

    }while (TreeNode -> leftChild != NULL);
    return *TreeNode;
}

const Tree& AVLTree::findMax() const {
    Tree *TreeNode = root;
    if(TreeNode == NULL || TreeNode -> rightChild == NULL)
        return *TreeNode;
    do{
        TreeNode = root-> rightChild;
    }while (TreeNode -> rightChild != NULL);
    return *TreeNode;
}


Tree *AVLTree::findallmatches(const Tree &searchNode, list<Tree> &trees, Tree *tempNode)const 
{
//    cout<<tempNode->common_name().empty()<<endl;
    if(NULL == tempNode){
        return NULL;
    } 
    else if(samename(searchNode,*tempNode)){
        trees.push_back(*tempNode);
        findallmatches(searchNode,trees,tempNode -> leftChild);
        findallmatches(searchNode,trees,tempNode -> rightChild);
        return tempNode;
    }
    else if(islessname(searchNode,*tempNode)){
        return findallmatches(searchNode,trees,tempNode -> leftChild);
    }
        return findallmatches(searchNode,trees,tempNode -> rightChild);
}

list <Tree > AVLTree::findallmatches(const Tree &searchNode) const 
{
    list<Tree>trees;
    findallmatches(searchNode,trees,this->root);
//        cout<< trees.size()<<endl;
    return trees;
}


/****************************************************************************************************
                 Search methods for the given zipcode and position & distance. 
*****************************************************************************************************/
Tree* AVLTree::findallmatchesbyzip(const int&zipcode, list<Tree> &trees, Tree *tempNode)const 
{
    if(NULL == tempNode)
        return NULL;
    findallmatchesbyzip(zipcode,trees,tempNode -> leftChild);
    int tempzip = tempNode -> zip();
    if(zipcode == tempzip){
//        cout<<tempNode->common_name()<<endl;
        trees.push_back(*tempNode);
    }
    findallmatchesbyzip(zipcode,trees,tempNode->rightChild);
    return NULL;
}

list <Tree> AVLTree::findallmatchesbyzip(const int& zipcode)const {
    list<Tree>trees;
    findallmatchesbyzip(zipcode,trees,root);
//    cout<< trees.size()<<endl;
    return trees;
}

Tree* AVLTree::findallmatchesbyzero( double &latitude,double &longitude, double &distance, list<Tree> &trees, Tree *tempNode) const
{
    double latitude2,longitude2,distance2;
    if(NULL == tempNode)
        return NULL;
    findallmatchesbyzero(latitude,longitude,distance,trees,tempNode->leftChild);

    tempNode -> get_position(latitude2,longitude2);
    distance2 = haversine(latitude,longitude,latitude2,longitude2);
//    cout<<"distance"<<distance2<<endl;
    if(distance2 <= distance){
//        cout<<tempNode->common_name()<<endl;
        trees.push_back(*tempNode);
    }
    findallmatchesbyzero(latitude,longitude,distance,trees,tempNode -> rightChild);
    return NULL;
}

list <Tree> AVLTree::findallmatchesbyzero(double &latitude,double &longitude, double &distance)const{
    list<Tree>trees;
    findallmatchesbyzero(latitude,longitude,distance,trees,root);
    return trees;
}


/******************************************************************************************************
                                   Tree Traversals
******************************************************************************************************/
void AVLTree::print(ostream &out) const 
{
    InOrderPrint(root,out);
}

void AVLTree::InOrderPrint(Tree *tempNode,ostream &out)const
{
    if(NULL == tempNode)
        return ;
    InOrderPrint(tempNode->leftChild,out);
    out << *tempNode << endl;
    InOrderPrint(tempNode->rightChild,out);
}

/*******************************************************************************************
                                 Tree modifiers 
********************************************************************************************/
Tree *AVLTree::LeftRotate(Tree *tempNode)
{
    Tree *lChildNode=tempNode -> rightChild -> leftChild,*newRoot = tempNode -> rightChild;
    tempNode-> rightChild-> leftChild = tempNode;
    tempNode-> rightChild = lChildNode;
    tempNode-> height = max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild)) + 1;
    if(NULL != tempNode-> rightChild)
        tempNode->rightChild->height = max(GetHeight(tempNode->rightChild->leftChild),GetHeight(tempNode->rightChild->rightChild)) + 1;
    return newRoot;
}


Tree *AVLTree::RightRotate(Tree *tempNode)
{
    Tree *rChildNode=tempNode->leftChild->rightChild,*newRoot=tempNode->leftChild;
    tempNode->leftChild->rightChild=tempNode;
    tempNode->leftChild=rChildNode;
    tempNode->height = max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild))+1;
    if(NULL!=tempNode -> leftChild)
        tempNode -> leftChild -> height = max(GetHeight(tempNode->leftChild->leftChild),GetHeight(tempNode->leftChild->rightChild)) + 1;
    return newRoot;
}


Tree *AVLTree::LeftAndRightRotate(Tree *tempNode)
{
    tempNode->leftChild = LeftRotate(tempNode->leftChild);
    return RightRotate(tempNode);
}


Tree *AVLTree::RightAndLeftRotate(Tree *tempNode)
{
    tempNode->rightChild = RightRotate(tempNode->rightChild);
    return LeftRotate(tempNode);
}


Tree *AVLTree::Insert(Tree& NewNode,Tree *tempNode)
{
    if(NULL == tempNode){
        return tempNode = &NewNode;
    }else{

        if(NewNode == *tempNode)
            return tempNode;
        else if(NewNode <*tempNode)
            tempNode-> leftChild = Insert(NewNode,tempNode -> leftChild);
        else tempNode -> rightChild = Insert(NewNode,tempNode -> rightChild);
    }

    if(2 == GetHeight(tempNode->leftChild) - GetHeight(tempNode -> rightChild))
    {
        if(NewNode <*tempNode -> leftChild)
            tempNode = RightRotate(tempNode);
        else tempNode = LeftAndRightRotate(tempNode);
    }
    else if(-2 == GetHeight(tempNode->leftChild) - GetHeight(tempNode->rightChild))
    {
        if(*tempNode -> rightChild<NewNode)
            tempNode = LeftRotate(tempNode);
        else tempNode = RightAndLeftRotate(tempNode);
    }

    tempNode -> height = max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild)) + 1;
    return tempNode;
}

void AVLTree::Insert(Tree& NewNode)
{
    root = Insert(NewNode,root);
}


Tree *AVLTree::Delete(bool &isDelSucceed,Tree& delNode,Tree *tempNode)
{
    if(NULL == tempNode)
        return NULL;
    else
    {
        if(delNode ==*tempNode)
        {
            if(NULL == tempNode -> rightChild)
            {
                Tree *cur = tempNode;
                tempNode = tempNode->leftChild;
                delete cur;
                isDelSucceed = true;
                return tempNode;
            }
            else// findMin on the right subtree. 
            {
                Tree *cur = tempNode -> rightChild;
                while(cur -> leftChild != NULL)
                    cur = cur->leftChild;
                tempNode = cur;
                tempNode -> rightChild = Delete(isDelSucceed,*cur,tempNode -> rightChild);
            }
        }
        else if(delNode < *tempNode)
            tempNode -> leftChild = Delete(isDelSucceed,delNode,tempNode -> leftChild);
        else tempNode -> rightChild = Delete(isDelSucceed,delNode,tempNode -> rightChild);

        if(-2 == GetHeight(tempNode->leftChild) - GetHeight(tempNode->rightChild))//the node in left subtree was deleted. 
        {
            if(GetHeight(tempNode -> rightChild -> rightChild)>= GetHeight(tempNode->rightChild->leftChild))
                tempNode = LeftRotate(tempNode);
            else tempNode = RightAndLeftRotate(tempNode);
        }
        else if(2 == GetHeight(tempNode -> leftChild) - GetHeight(tempNode -> rightChild))
        {
            if(GetHeight(tempNode ->leftChild->leftChild) >= GetHeight(tempNode->leftChild->rightChild))
                tempNode = RightRotate(tempNode);
            else tempNode = LeftAndRightRotate(tempNode);
        }
        tempNode -> height = max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild)) + 1;
    }
    return tempNode;
}

void AVLTree::remove(Tree& delNode)
{
    bool isDelSucceed = false;
    root = Delete(isDelSucceed,delNode,root);

}

void AVLTree::SufOrderDelete(Tree *tempNode)
{
    if(NULL == tempNode)
        return ;
    SufOrderDelete(tempNode -> leftChild);
    SufOrderDelete(tempNode -> rightChild);
    delete tempNode;
}

void AVLTree::clear() {
    if(root == NULL)
        return;
    SufOrderDelete(root);
    root = NULL;
}

/*******************************************************************************************
                                Computer distance on the sophere. 
********************************************************************************************/
double AVLTree::haversine(double lat1, double lon1, double lat2, double lon2)const
{
    lat1        = TO_RAD * lat1;
    lat2        = TO_RAD * lat2;
    lon1        = TO_RAD * lon1;
    lon2        = TO_RAD * lon2;
    double dLat = (lat2 - lat1)/2;
    double dLon = (lon2 - lon1)/2;
    double a    = sin(dLat);
    double b    = sin(dLon);
    return 2*R * asin(sqrt(a*a + cos(lat1) * cos(lat2) * b*b));
}




