//
//  main.cpp
//  BST
//
//  Created by Vinod Gupta on 2/18/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#include <iostream>
#include "BST.h"

using namespace std;

TreeNode<int,int>  *createMinimalBST(int ar[],unsigned int low,unsigned int high)
{
    if(low < high)
    {
        int mid = (low+high)/2;
        
        TreeNode<int,int> *node = new TreeNode<int,int>(ar[mid],0);
        
        node->setLeft(createMinimalBST(ar,low,mid));
        node->setRight(createMinimalBST(ar,mid+1,high));
        
        return node;
    }
    return NULL;
}

void testMinimalBSTCreation()
{
    int ar[]={0,1,2,3,4,5,6,7,8,9};
    int sizeofar = sizeof ar / sizeof(int);
    
    Tree<int,int> *tree2 = new Tree<int,int>(createMinimalBST(ar,0,sizeofar));
    
    cout<<"Print Levels 2"<<endl;
    tree2->printLevel();
    cout<<"Inorder 2"<<endl;
    
    tree2->inOrder(tree2->root());
}

void testTreeTraversals()
{
    Tree<int,int> *tree = new Tree<int,int>();
    
    tree->insert(5,0);
    tree->insert(29,0);
    tree->insert(6,0);
    tree->insert(4,0);
    tree->insert(3,0);
    tree->insert(7,0);
    tree->insert(32,0);
    tree->insert(2,0);
    tree->insert(19,0);
    tree->insert(11,0);
    
    cout<<"Inorder Traversal";
    tree->inOrder(tree->root());
    
    cout<<"PreOrder Traversal";
    tree->preOrder(tree->root());
    
}

void testTreeSuccessorAndDeletion()
{
    Tree<int,int> *tree = new Tree<int,int>();
    
    tree->insert(5,0);
    tree->insert(29,0);
    tree->insert(6,0);
    tree->insert(7,0);
    tree->insert(32,0);
    tree->insert(2,0);
    tree->insert(19,0);
    tree->insert(11,0);
    
    cout<<"Min element:";
    tree->min()->visit();
    cout<<endl;
    
    cout<<"Max element:";
    tree->max()->visit();
    cout<<endl;
    
    TreeNode<int,int>*node = tree->search(tree->root(),29);
    if(node)
    {
        cout<<"Successor of";
        node->visit();
        node = tree->successor(node);
        if(node)
            node->visit();
        else
            cout<<"No successor found"<<endl;
        
    }
    
    node = tree->root();
    while(node)
    {
        tree->remove(node);
        cout<<"Inorder Traversal"<<endl;
        tree->inOrder(tree->root());
        node = tree->root();
    }

}

void testLevelPrint()
{
    Tree<int,int> *tree = new Tree<int,int>();
    
    tree->insert(5,0);
    tree->insert(29,0);
    tree->insert(6,0);
    tree->insert(7,0);
    tree->insert(32,0);
    tree->insert(2,0);
    tree->insert(19,0);
    tree->insert(11,0);
    
    cout<<"Print Levels"<<endl;
    tree->printLevel();
}

int main(int argc, const char * argv[]) {
    
    testTreeTraversals();
    
    testTreeSuccessorAndDeletion();
    
    testLevelPrint();
    
    testMinimalBSTCreation();
    
    return 0;
}
