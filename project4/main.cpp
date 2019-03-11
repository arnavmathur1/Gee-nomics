//
//  main.cpp
//  project4
//
//  Created by Arnav Mathur on 3/8/19.
//  Copyright © 2019 Arnav Mathur. All rights reserved.
//
#include "Trie.h"
#include <iostream>

int main()
{
    Trie<int> t;
    
    t.insert("o", 1);
    //t.insert("ab", 2);
    t.insert("qax", 3);
    t.insert("qax", 5);
    t.insert("qaz", 22);
    //t.insert("qaz", 22);
    //t.insert("qaz", 22);
    //t.insert("qa", 19);
    t.insert("qbz", 21);
    t.insert("qaf", 20);
    
    //t.dump();
    
    std::vector<int> x = t.find("qaz", false);
    
    for (int i = 0; i<x.size(); i++)
        std::cout<<x[i]<<" ";
    
    std::cout<<"\n";
}
