#include <iostream>
#include <fstream>
#include <string>
#include "TreeNode.h"
#include "AVLTree.h"
#include "PCTimer.h"
using namespace std;

const int numWords = 713038;

//inserts all words from specified input file to specified avl
template <typename KeyType, typename ElementType>
double insertAllWords(string fileName, AVLTree<KeyType, ElementType> &avl, int partition)
{
    ifstream in(fileName.c_str());
    if(!in.is_open())
    {
        cerr << "Could not open " << fileName << endl;
    }

    KeyType s;

    PCTimer t;
    int counter = 0;
    t.start();

    while(in >> s)
    {
        avl.insert(s, ElementType());
        avl[s]++;

        ++counter;
        if(counter == partition * numWords / 10)
            break;
    }

    t.stop();
    double time = t.elapsedTime();
    t.reset();
    in.close();
    return time;
}


//runs insert on 10 partitions
void measureAll(string fileName)
{
    for(int i = 1; i <= 10; ++i)
    {
        AVLTree<string, int> avl;

        double ins = insertAllWords(fileName, avl, i);
        cout << ins;
        cout << endl;
    }
}

int main()
{
    measureAll("../shuffled/xaj");
    return 0;
}
