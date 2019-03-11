#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>


#include <iostream> //delete

template<typename ValueType>
class Trie
{
public:
    Trie();
    ~Trie();
    void reset();
    void insert(const std::string& key, const ValueType& value);
    std::vector<ValueType> find(const std::string key, bool exactMatchOnly) const;
    
    // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
    
    void dump();//REMOVE, I REPEAT: REMOVE
    
private:
    
    struct Node
    {
        Node();
        char label;
        std::vector<Node*> children;
        std::vector<ValueType> values;
        
    };
    
    void FreeTree (Node* cur); //Used to delete all nodes in the tree
    Node* findInsertionPoint(std::string &key, Node* parent, int pos);
    std::vector<ValueType> findHelper(std::string key, bool exactMatchOnly, Node* parent, std::vector<ValueType> &ir, int pos) const;
    
    Node* root;
    
    std::vector<Node*> allNodes; //A vector containing all the nodes
    
};

template<typename ValueType>
Trie<ValueType>::Trie()
{
    root = new Node();
    //root->label = 'r'; //DELETE
    allNodes.push_back(root);
}

template<typename ValueType>
Trie<ValueType>::Node::Node()
{
}

template<typename ValueType>
void Trie<ValueType>::FreeTree(Node* cur)
{
    
    
    unsigned long size = cur->children.size();
    
    for (int i = 0; i<size; i++)
    {
        FreeTree(cur->children[i]);
    }
    
    std::cout<<cur->label;
    delete cur;
    
}



template<typename ValueType>
Trie<ValueType>::~Trie()
{
    FreeTree(root);
}

template<typename ValueType>
void Trie<ValueType>::reset()
{
    FreeTree(root);
    Trie();
}

template<typename ValueType>
typename Trie<ValueType>::Node* Trie<ValueType>::findInsertionPoint(std::string &key, Node* parent, int pos)
{
    
    
    for (int i = 0; i<parent->children.size(); i++)
    {
        
        if (parent->children[i]->label == key[0])
        {
            key = key.substr(1);
            //std::cout<<parent->children[i]->label<<" has a parent label: "<<parent->label<<"in the loop \n";
            parent = findInsertionPoint(key, parent->children[i], pos+1);
        }
    }
    
    return parent;
}


template<typename ValueType>
void Trie<ValueType>::insert(const std::string &key, const ValueType &value)
{
    std::string keyPass = key;
    Node* parent = root;
    
    parent = findInsertionPoint(keyPass, parent, 0);
    
    while (keyPass.length()>0)
    {
        Node* nodeptr = new Node();
        nodeptr->label = keyPass[0];
        parent->children.push_back(nodeptr);
        allNodes.push_back(nodeptr);
        
        keyPass = keyPass.substr(1);
        unsigned long index = parent->children.size();
        parent = parent->children[index-1];
    }
    parent->values.push_back(value);
}




template<typename ValueType>
void Trie<ValueType>::dump()
{
    for (int i = 0; i<allNodes.size(); i++)
    {
        std::cout<<allNodes[i]->label;
    }
    
    
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::find(const std::string key, bool exactMatchOnly) const
{
    std::vector<ValueType> ir = {};
    return(findHelper(key, exactMatchOnly, root, ir, 0));
}

template<typename ValueType>
std::vector<ValueType> Trie<ValueType>::findHelper(std::string key, bool exactMatchOnly, Node* parent, std::vector<ValueType> &ir, int pos) const
{
    
    
    if(pos == key.length())
    {
        
        std::cout<<parent->label;
        
        for (int i = 0; i<parent->values.size(); i++)
        {
            std::cout<<parent->values[i]<<"\n";
            ir.push_back(parent->values[i]);
        }
    }
    
    for (int i = 0; i<parent->children.size(); i++)
    {
        Node* p = parent->children[i];
        
        if (parent->children[i]->label == key[pos])
        {
            //std::cout<<parent->children[i]->label<<" has a parent label: "<<parent->label<<" in the loop \n";
            
            //key = key.substr(1);
            //std::cout<<parent->children[i]->label<<" has a parent label: "<<parent->label<<"in the loop \n";
            ir = findHelper(key, exactMatchOnly, parent->children[i], ir, pos+1);
        }
        else
        {
            if (!exactMatchOnly)
            {
                
                //std::cout<<parent->children[i]->label<<" has a parent label: "<<parent->label<<" in the loop \n";
                
                
                
                if (parent->children[i]->label == 'x')
                    std::cout<<"Ye";
                
                //key = parent->children[i]->label;
                
                //key = key.substr(1);
                
                std::cout<<"key: "<<key<<" size:: "<<key.size()<<"\n";
                ir = findHelper(key, true, parent->children[i], ir, pos+1);
            }
        }
    }
    return (ir);
}


#endif // TRIE_INCLUDED
