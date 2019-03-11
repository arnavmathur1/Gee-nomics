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
    t.dump();
    
}
