#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
using namespace std;



class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
    
    
private:
    int m_minSearchLength;
    Trie<DNAMatch>* t;
    vector<Genome> genomes;
    unordered_map<string, const Genome*> umap;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearchLength = minSearchLength;
    t = new Trie<DNAMatch>;
    genomes = {};
}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    
    genomes.push_back(genome);
    string name = genome.name();
    
    const Genome* gptr = &genome;
    
    umap[name] = gptr;
    
    for(int i = 0;;i++)
    {
        string fragment = "";
        bool result = genome.extract(i, m_minSearchLength, fragment);
        
        if (!result)
            return;
        DNAMatch toInsert;
        toInsert.genomeName = genome.name();
        toInsert.length = fragment.length();
        toInsert.position = i;
        t->insert(fragment, toInsert);
    }
    
    
    
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    if (fragment.length()<minimumLength || minimumLength<minimumSearchLength())
    {
        return false;
    }
    
    
    
    vector<DNAMatch> temp;
    string f = fragment.substr(0, minimumSearchLength());
    matches = t->find(f, exactMatchOnly);
    
    
    
    /*
    for (int i = 0; i+minimumLength<=fragment.length(); i++)
    {
        string f = fragment.substr(0, i+minimumLength);
        
        temp = t->find(f, exactMatchOnly);
        
        for (int i = 0; i<temp.size(); i++)
        {
            matches.push_back(temp[i]);
        }
    }*/
    
    int tempsize = matches.size();
    
    for (int i = 0; i<tempsize; i++)
    {
        unordered_map<string,Genome*>::const_iterator cur;

        
        string bigone = "";
        umap.find (matches[i].genomeName)->second->extract(matches[i].position, umap.find(matches[i].genomeName)->second->length()-matches[i].position, bigone);
        
        int len = 0;
        
        for (int j = 0; j<fragment.length(); j++)
        {
            if (bigone[j]!=fragment[j])
                break;
            
            len++;
        }
        
        //matches[i] = cur->second->extract(matches[i].position, len, bigone);
        
        matches[i].length = len;
    }
    
    
    for (vector<DNAMatch>::iterator it = matches.begin(); it!=matches.end(); it++)
    {
        if (it->length<minimumLength)
        {
            matches.erase(it);
            it--;
        }
        
    }
    
    if (matches.empty())
        return false;
    
    return true;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return false;  // This compiles, but may not be correct
}

//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
