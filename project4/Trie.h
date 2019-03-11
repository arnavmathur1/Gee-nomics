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
    std::vector<ValueType> find(const std::string& key, bool exactMatchOnly) const;

      // C++11 syntax for preventing copying and assignment
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;
    
    void dump();

private:
    
    struct Node
    {
        std::string label;
        std::vector<Node*> children;
        std::vector<ValueType> values;
    };
    
    void FreeTree (Node* cur); //Used to delete all nodes in the tree
    void findInsertionPoint(std::string &key);
    
    Node* root;
    
    std::vector<Node*> allNodes; //A vector containing all the nodes
    
    
    
    void printWord(char* str, int n);
    
    void printAllWords(Node* root, char* wordArray, int pos = 0);
};

template<typename ValueType>
Trie<ValueType>::Trie()
{
    root = new Node();
    allNodes.push_back(root);
}

template<typename ValueType>
void Trie<ValueType>::FreeTree(Node* cur)
{
    if (cur->children.empty())
    {
        return;
    }
    
    unsigned long size = cur->children.size();
    
    for (int i = 0; i<size; i++)
    {
        FreeTree(cur->children[i]);
    }
    
    delete cur;
    
}



template<typename ValueType>
Trie<ValueType>::~Trie()
{
    Node* p = root;
    FreeTree(root);
}

template<typename ValueType>
void Trie<ValueType>::reset()
{
    FreeTree(root);
    Trie();
}

template<typename ValueType>
void Trie<ValueType>::findInsertionPoint(std::string &key, Node* parent)
{
    for (int i = 0; i<this->Node.children.size(); i++)
    {
        if (this->label == key[0])
        {
            findInsertionPoint(key.substr(1));
        }
    }
    
    return ;
}


template<typename ValueType>
void Trie<ValueType>::insert(const std::string &key, const ValueType &value)
{
    Node* x = new Node();
    allNodes.push_back(x);
    root->children.push_back(x);
    x->values.push_back(value);
    
}




template<typename ValueType>
void Trie<ValueType>::dump()
{
    for (int i = 0; i<1; i++)
    {
        std::cout<<root->children[i]->values[i];
    }
}


template<typename ValueType>

void Trie<ValueType>::printWord(char* str, int n)
{
    std::cout<<std::endl;
    for(int i=0; i<n; i++)
    {
        std::cout<<str[i]<<" ";
    }
}
// Print all words in Trie
template<typename ValueType>
void Trie<ValueType>::printAllWords(Node* root, char* wordArray, int pos)
{
    if(root == NULL)
        return;
    
    if(root->isEndOfWord)
    {
        printWord(wordArray, pos);
    }
    for(int i=0; i<26; i++)
    {
        if(root->child[i] != NULL)
        {
            wordArray[pos] = i+'a';
            printAllWords(root->child[i], wordArray, pos+1);
        }
    }
    
    
    
}

#endif // TRIE_INCLUDED
