//
//  main.cpp
//  project4
//
//  Created by Arnav Mathur on 3/8/19.
//  Copyright © 2019 Arnav Mathur. All rights reserved.
//
//#include "Trie.h"
#include "provided.h"
#include <iostream>
#include    <fstream>     //    needed    to    open    files
using namespace std;

void    somefunc()
{
    
    //    Specify    the    full    path    and    name    of    the    gene    data    file    on    your    hard    drive.
    string filename    =    "/Users/arnavm/Documents/Xcode Projects/cs32/project4/data/Ferroplasma_acidarmanus.txt";
    //    Open    the    data    file    and    get    a    ifstream object    that    can    be    used    to    read    its
    //    contents.
    ifstream    strm(filename);
    if    (!strm)
    {
        cout    <<    "Cannot    open    "    <<    filename    <<    endl;
        return;
    }
    vector<Genome>    vg;
    bool    success    =    Genome::load(strm,    vg);        //    Load    the    data    via    the    stream.
    if    (success)
    {
        cout    <<    "Loaded "    <<    vg.size()    <<    " genomes successfully:" <<    endl;
        for    (int    k    =    0;    k    !=    vg.size();    k++)
            cout    <<    vg[k].name()    <<    endl;
    }
    else
        cout    <<    "Error    loading    genome    data" <<    endl;
    
}


int main()
{
    /*
    Trie<int> t;
    
    t.insert("o", 1);
    //t.insert("ab", 2);
    t.insert("qax", 3);
    t.insert("qax", 5);
    t.insert("qaz", 22);
    t.insert("qaz", 22);
    t.insert("qaz", 22);
    t.insert("qa", 19);
    t.insert("qbz", 21);
    t.insert("qaf", 20);
    
    //t.dump();
    
    std::vector<int> x = t.find("qbx", false);
    
    for (int i = 0; i<x.size(); i++)
        std::cout<<x[i]<<" ";
    */
    somefunc();
    
}
