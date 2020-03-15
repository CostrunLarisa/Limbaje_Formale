#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <string>
using namespace std;
class NFA {
    set<int> F;
    set<char> Sigma;
    set<int> Q;
    set<int> q0;
    map<pair<int, char>, set<int> > Delta;
public:
    NFA() {
        q0.insert(0);
    }
    NFA(set<int> F, set<int> Q, set<char> Sigma, map < pair<int, char>, set<int> > Delta, set<int> q0)
    {
        this->F = F;
        this->Q = Q;
        this->q0 = q0;
        this->Delta = Delta;
        this->Sigma = Sigma;

    }
    set<int> getF() const { return this->F; }
    set<int> getQ() const { return this->Q; }
    set<char> getSigma() const { return this->Sigma; }
    set<int> getinitialstate() const { return this->q0; }
    map<pair<int, char>, set<int> > getDelta() const { return this->Delta; }
    friend istream& operator >> (istream&, NFA&);
    bool intersection(set<int>);
    set<int> DeltaStar(set<int>, string);
};

bool NFA::intersection(set<int> q)
{
    for (set<int>::iterator x = q.begin(); x != q.end(); x++)
        for (set<int>::iterator y = F.begin(); y != F.end(); y++)
            if (*x == *y)
                return true;
    return false;
}

set<int> NFA::DeltaStar(set<int> q, string w)
{
    int n = w.length();
    set <int> localfinalstates;
    for (set<int>::iterator j = Delta[{*q.begin(), w[0]}].begin(); j != Delta[{*q.begin(), w[0]}].end(); j++)
    {
        localfinalstates.insert(*j);
    }
    n--;
    if (n == 0) { return localfinalstates; }

    int contor = 0;
    while(n)
    {
        set<int> auxiliar;
            for (set<int>::iterator i = localfinalstates.begin(); i != localfinalstates.end(); i++)
            {
                for (set<int>::iterator j = Delta[{*i, w[contor + 1]}].begin(); j != Delta[{*i, w[contor + 1]}].end(); j++)
                {
                    auxiliar.insert(*j);
                }
            }
        n--;
        contor++;

        localfinalstates.clear();
            for (set<int>::iterator it = auxiliar.begin(); it != auxiliar.end(); it++)
            {
                localfinalstates.insert(*it);
            }
        auxiliar.clear();
    }
    return localfinalstates;
}

istream& operator >> (istream& f, NFA& M)
{
    int noOfStates;
    f >> noOfStates;
    for (int i = 0; i < noOfStates; ++i)
    {
        int x;
        f >> x;
        M.Q.insert(x);
    }

    int noOfLetters;
    f >> noOfLetters;
    for (int i = 0; i < noOfLetters; ++i)
    {
        char ch;
        f >> ch;
        M.Sigma.insert(ch);
    }

    int noOfTransitions;
    f >> noOfTransitions;
    for (int i = 0; i < noOfTransitions; ++i)
    {
        int s, d;
        char ch;
        f >> s >> ch >> d;
        M.Delta[{s, ch}].insert(d);
    }
    int x;
    f >> x;
    M.q0.insert(x);

    int noOfFinalStates;
    f >> noOfFinalStates;
    for (int i = 0; i < noOfFinalStates; ++i)
    {
        int q;
        f >> q;
        M.F.insert(q);
    }

    return f;
}

int main()
{
    NFA M;
    ifstream fin("nfa.txt");
    fin >> M;
    fin.close();

    set<int> lastState = M.DeltaStar(M.getinitialstate(), "aba");

    if (M.intersection(lastState) == true)
    {
        cout << "Cuvant acceptat";
    }
    else
    {
        cout << "Cuvant respins";
    }
    return 0;
}