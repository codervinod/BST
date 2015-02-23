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

    cout<<"PreOrder minimal BST"<<endl;
    
    tree2->preOrder(tree2->root());
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

TreeNode<int,int> *CreateTree(vector<pair<int,int>> &pre_ar,vector<pair<int,int>> &in_ar)
{
    if(pre_ar.empty())
        return NULL;
    
    TreeNode<int,int> *node = new TreeNode<int,int>(pre_ar[0].first,pre_ar[0].second);
    
    int pre_size = 0;
    for(vector<pair<int,int>>::iterator itr = in_ar.begin();
        itr!= in_ar.end();++itr,++pre_size)
    {
        if(itr->first == pre_ar[0].first)
        {
            vector<pair<int,int>> l_pre_ar=
                vector<pair<int,int>>(pre_ar.begin()+1,pre_ar.begin()+1+pre_size); //leave root element
            
            vector<pair<int,int>> l_in_ar=
                vector<pair<int,int>>(in_ar.begin(),itr); //leave root element
            
            vector<pair<int,int>> r_pre_ar=
                vector<pair<int,int>>(pre_ar.begin()+pre_size+1,pre_ar.end()); //remaining pre order array
            
            vector<pair<int,int>> r_in_ar=
                vector<pair<int,int>>(itr+1,in_ar.end());//remaining in order array
            
            //found root in inorder array
            node->setLeft(CreateTree(l_pre_ar,l_in_ar));
            node->setRight(CreateTree(r_pre_ar,r_in_ar));
        }
    }
    
    return node;
}

void UnserializeTree(vector<pair<int,int>> &pre_ar,vector<pair<int,int>> &in_ar)
{
    TreeNode<int,int> *root = CreateTree(pre_ar,in_ar);
    Tree<int,int> *tree = new Tree<int,int>(root);
    
    cout<<"New Inorder Traversal"<<endl;
    tree->inOrder(tree->root());
    
    cout<<"New PreOrder Traversal"<<endl;
    tree->preOrder(tree->root());
}

void SerializeTree()
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
    
    cout<<"Original Inorder Traversal"<<endl;
    tree->inOrder(tree->root());
    
    cout<<"Original PreOrder Traversal"<<endl;
    tree->preOrder(tree->root());
    
    vector<pair<int,int>> pre_ar,in_ar;
    
    tree->preOrderArray(tree->root(),pre_ar);
    tree->inOrderArray(tree->root(),in_ar);

    UnserializeTree(pre_ar,in_ar);
}

int main(int argc, const char * argv[])
{

#if 0
    testTreeTraversals();
    
    testTreeSuccessorAndDeletion();
    
    testLevelPrint();
    
    testMinimalBSTCreation();
    
#endif
    
    
    SerializeTree();
    
    return 0;
}
