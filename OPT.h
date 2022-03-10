// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7

#ifndef OPT_hpp
#define OPT_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <iterator>
#include <queue>
#include "math.h"
#include "tgmath.h"

using namespace std;

struct Vert{
    int x;
    int y;
};

struct Prims{
    size_t c;
    size_t p;
    double d;
    bool v;
};

class OPT {
    
public:
    OPT();
    void get_OPT();
    void gen_distance_matrix();
    void genPerms(vector<size_t> &path, size_t permLength);
    bool promising(vector<size_t> & path, size_t permLength);
    double connection_cost(vector<size_t> &begin, vector<size_t> &end);
    void printOPT(vector<size_t> &path);
    
    //helpers
    void get_coords();
    double get_distance(size_t one, size_t two);
    double fast_distance(size_t one, size_t two);
    double partial_cost(vector<size_t> &P);
    
    //special MST
    void genMST(vector<size_t> &p);
    void update_adjacent();
    
    //special FAST
    void genFAST(vector<size_t> &p);
    size_t get_closest(vector<bool> &v);
    size_t find_insertion(size_t rand);
    double calculate_cost(vector<size_t> &T);
    
    
private:
    vector<vector<double> > matrix;
    vector<Prims> MST;
    vector<Vert> coords;
    vector<size_t> TSP;
    vector<size_t> nums;
    
    Prims current;
    
    size_t num_vert, now, coord;
    double MSTweight, TSPcost;

};



#endif /* OPT_hpp */
