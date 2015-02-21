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
int main(int argc, const char * argv[]) {
    
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
    
    /*
    node = tree->root();
    while(node)
    {
        tree->remove(node);
        cout<<"Inorder Traversal"<<endl;
        tree->inOrder(tree->root());
        node = tree->root();
    }
    */
    cout<<"Print Levels"<<endl;
    tree->printLevel();
    
    return 0;
}
