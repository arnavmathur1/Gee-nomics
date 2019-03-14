#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
using namespace std;


class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_sequence;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_name = nm;
    m_sequence = sequence;
}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes) 
{
    int lineCounter = 0;
    string line;
    string name;
    string concat = "";
    bool lineAfterNameLine = false;
    while (getline(genomeSource, line))
    {
        if(line == "")
            return false;
        
        if (line[0] != '>' && lineCounter == 0)
        {
            return false;
        }

        if(line[0] == '>')
        {
            if(lineCounter!=0)
            {
                if (concat == "")
                    return false;
                if (lineAfterNameLine)
                    return false;
                genomes.push_back(*(new Genome(name, concat)));
                concat = "";
            }
            
            name = line.substr(1);

            if (name.length() == 0)
                return false;
            lineCounter++;
            lineAfterNameLine = true;
            continue;
        }
        for (int i = 0; i<line.size(); i++)
            if (line[i]!='A' &&line[i]!='C' &&line[i]!='T' &&line[i]!='G' &&line[i]!='N')
                return false;
        
        concat+=line;
        
        lineAfterNameLine = false;
    }
    if (name == "")
        return false;
    if (lineAfterNameLine)
        return false;
    genomes.push_back(*(new Genome(name, concat)));
    
    
    
    return true;  // This compiles, but may not be correct
}


int GenomeImpl::length() const
{
    //cout<<m_sequence;
    return m_sequence.size();  // This compiles, but may not be correct
}

string GenomeImpl::name() const
{
    return m_name;  // This compiles, but may not be correct
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (position<0 || length<1 || position+length>this->length())
        return false;
    
    fragment = m_sequence.substr(position, length);
    
    return true;
        
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes) 
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
