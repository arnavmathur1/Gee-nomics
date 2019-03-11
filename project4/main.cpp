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
    
    t.insert("a", 1);
    t.dump();
    
}
