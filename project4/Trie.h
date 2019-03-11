#ifndef TRIE_INCLUDED
#define TRIE_INCLUDED

#include <string>
#include <vector>


#include <iostream> //delete

int counter = 0;

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
    
    void dump();

private:
    
    struct Node
    {
        Node();
        char label;
        std::vector<Node*> children;
        std::vector<ValueType> values;
    };
    
    void FreeTree (Node* cur); //Used to delete all nodes in the tree
    Node* findInsertionPoint(std::string &key, Node* parent);
    
    Node* root;
    
    std::vector<Node*> allNodes; //A vector containing all the nodes
    
    
    
    void printWord(char* str, int n);
    
    void printAllWords(Node* root, char* wordArray, int pos = 0);
};

template<typename ValueType>
Trie<ValueType>::Trie()
{
    root = new Node();
    root->label = 'r';
    allNodes.push_back(root);
}

template<typename ValueType>
Trie<ValueType>::Node::Node()
{
    //std::cout<<"made";
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
    //std::cout<<"\n\ndelet\n";
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
typename Trie<ValueType>::Node* Trie<ValueType>::findInsertionPoint(std::string &key, Node* parent)
{
    
    
    std::cout<<"\n\n"<<parent->children.size()<<":size\n";
    for (int i = 0; i<parent->children.size(); i++)
    {
        
        if (parent->children[i]->label == key[0])
        {
            std::cout<<"KEY: "<<key<<"  LABEL: "<<parent->children[i]->label<<"\n";
            counter++;
            key = key.substr(1);
            std::cout<<parent->children[i]->label<<" has a parent label: "<<parent->label<<"in the loop \n";
            parent = findInsertionPoint(key, parent->children[i]);
        }
    }
    
    return parent;
}


template<typename ValueType>
void Trie<ValueType>::insert(const std::string &key, const ValueType &value)
{
    std::string keyPass = key;
    Node* parent = root;
    
    parent = findInsertionPoint(keyPass, parent);
    
    std::cout<<"keypass: "<<keyPass<<std::endl;
    
    //std::cout<<root<< " "<<parent;
    //std::cout<<"label:"<<parent->label<<"\n";
    while (keyPass.length()>0)
    {
        //std::cout<<"WHO";
        Node* nodeptr = new Node();
        nodeptr->label = keyPass[0];
        parent->children.push_back(nodeptr);
        std::cout<<nodeptr->label<<" has a parent label: "<<parent->label<<"\n";
        
        allNodes.push_back(nodeptr);
        
        keyPass = keyPass.substr(1);
        unsigned long index = parent->children.size();
        std::cout<<"index is: "<<index<<"\n";
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
    std::cout<<"\n";
    std::cout<<"\n!!!"<<allNodes[5]->values[0]<<" "<<allNodes[5]->values[0]<<"\n";
    
}



#endif // TRIE_INCLUDED
