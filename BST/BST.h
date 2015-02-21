//
//  BST.h
//  BST
//
//  Created by Vinod Gupta on 2/18/15.
//  Copyright (c) 2015 vinodg. All rights reserved.
//

#ifndef BST_BST_h
#define BST_BST_h

#include <iostream>
#include <queue>
template <class K,class V>
class TreeNode
{
public:
    TreeNode(K key,V val)
    :_key(key),_val(val),
    _parent(NULL),_left(NULL),_right(NULL)
    {}
    
    virtual ~TreeNode()
    {
        if(_left)
            delete _left;
        
        if(_right)
            delete _right;
    }
    K key() {return _key;}
    V val() {return _val;}
    
    void setKey(K key) {_key = key;}
    void setVal(V val) {_val = val; }
    
    void setParent(TreeNode<K,V> *p) {_parent = p;}
    void setLeft(TreeNode<K,V> *l) {_left = l;}
    void setRight(TreeNode<K,V> *r) {_right = r;}
    
    TreeNode<K,V> *parent() {return _parent;}
    TreeNode<K,V> *left() {return _left;}
    TreeNode<K,V> *right() {return _right;}
    
    void visit()
    {
        std::cout<<"{"<<_key<<","<<_val<<"}"<<std::endl;
    }
private:
    K _key;
    V _val;
    TreeNode<K,V> *_parent;
    TreeNode<K,V> *_left;
    TreeNode<K,V> *_right;
};

template <class K,class V>
class Tree
{
public:
    Tree():_root(NULL){}
    virtual ~Tree()
    {
        if(_root)
            delete _root;
    }
    
    TreeNode<K,V> *root() {return _root;}
    
    void insert(K key,V val)
    {
        TreeNode<K,V> *new_node =new TreeNode<K,V>(key,val);
        if(!_root)
        {
            _root =new_node;
            return;
        }
        
        TreeNode<K,V> *itr = _root,*prev_itr = NULL;
        while(itr)
        {
            prev_itr = itr;
            V itr_key = itr->key();
            
            if(key <= itr_key)
            {
                itr = itr->left();
            }
            else if(key > itr_key)
            {
                itr = itr->right();
            }
        }
        
        new_node->setParent(prev_itr);
        if(key <= prev_itr->key())
        {
            prev_itr->setLeft(new_node);
        }
        else if(key > prev_itr->key())
        {
            prev_itr->setRight(new_node);
        }
    }
    
    void inOrder(TreeNode<K,V> *itr)
    {
        if(!itr)
            return;
        inOrder(itr->left());
        itr->visit();
        inOrder(itr->right());
    }
    void preOrder(TreeNode<K,V> *itr)
    {
        if(!itr)
            return;
        
        itr->visit();
        inOrder(itr->left());
        inOrder(itr->right());
    }

    void postOrder(TreeNode<K,V> *itr)
    {
        if(!itr)
            return;
        
        inOrder(itr->left());
        inOrder(itr->right());
        itr->visit();
    }

    TreeNode<K,V>* min(TreeNode<K,V> *itr = NULL)
    {
        if(!itr) itr = _root;
        while(itr->left())
        {
            itr = itr->left();
        }
        return itr;
    }
    
    TreeNode<K,V>* max()
    {
        TreeNode<K,V> *itr = _root;
        while(itr->right())
        {
            itr = itr->right();
        }
        return itr;
    }
    
    TreeNode<K,V>*search(TreeNode<K,V> *itr,K key)
    {
        if(!itr)
            return NULL;
        
        if(key < itr->key())
        {
            return search(itr->left(),key);
        }
        else if(key > itr->key())
        {
            return search(itr->right(),key);
        }
        return itr;
    }
    
    TreeNode<K,V>* successor(TreeNode<K,V> *node)
    {
        if(!node)
            return NULL;
        
        if(node->right())
        {
            return min(node->right());
        }
        
        TreeNode<K,V> *parent = node->parent();
        while(parent && parent->right() == node)
        {
            node = parent;
            parent = node->parent();
        }
        return parent;
    }
    void swapWithDelete(TreeNode<K,V> *node,TreeNode<K,V> *child)
    {
        TreeNode<K,V> *parent = node->parent();
        if(!parent)
        {
            _root = child;
            _root->setParent(NULL);
        }
        else if(parent->left() == node)
        {
            parent->setLeft(child);
            child->setParent(parent);
        }
        else if(parent->right() == node)
        {
            parent->setRight(child);
            child->setParent(parent);
        }
        else
        {
            std::cout<<"error case";
            return;
        }
        node->setLeft(NULL);
        node->setRight(NULL);
        delete node;
    }
    
    void remove(TreeNode<K,V> *node)
    {
        //case 1: No child
        //case 2: only one child
        //case 3: two child
        if(!node->left() && !node->right())
        {
            TreeNode<K,V> *parent = node->parent();
            if(!parent)
            {
                delete _root;
                _root = NULL;
                return;
            }
            
            if(parent->left() == node)
            {
                parent->setLeft(NULL);
            }
            else if(parent->right() == node)
            {
                parent->setRight(NULL);
            }
            else
            {
                std::cout<<"error case";
                return;
            }
        }
        else if(!node->left())
        {
            swapWithDelete(node,node->right());
        }
        else if(!node->right())
        {
            swapWithDelete(node,node->left());
        }
        else
        {
            TreeNode<K,V> *next = successor(node);
            node->setKey(next->key());
            node->setVal(next->val());
            remove(next);
        }
    }
    
    void printLevel()
    {
        typedef std::pair<int,TreeNode<K,V> *> LevelNodePair;
        std::queue<LevelNodePair> q;
        
        q.push(LevelNodePair(0,_root));
        
        while(!q.empty())
        {
            LevelNodePair &node = q.front();
            std::cout<<node.first<<"\t";
            node.second->visit();
            
            if(node.second->left())
            {
                q.push(LevelNodePair(node.first+1,node.second->left()));
            }
            
            if(node.second->right())
            {
                q.push(LevelNodePair(node.first+1,node.second->right()));
            }
            
            q.pop();
        }
    }
    
private:
    TreeNode<K,V> *_root;
};


#endif
