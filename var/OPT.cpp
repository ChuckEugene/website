// Project Identifier: 9B734EC0C043C5A836EA0EBE4BEFEA164490B2C7

#include "OPT.h"

OPT::OPT(){
    num_vert = 0;
}

//*************************************************//
//********************SPECIAL MST******************//
//*************************************************//

void OPT::get_OPT(){
    get_coords();
    gen_distance_matrix();
    genFAST(nums);
    
    vector<size_t> OPTpath;
    
    OPTpath = TSP;
    
    genPerms(OPTpath, 1);
    printOPT(TSP);
}

void OPT::gen_distance_matrix(){
    
    matrix.resize(num_vert);
    
    for (size_t i = 0; i < num_vert; i++){
        matrix[i].resize(num_vert);
        for (size_t k = 0; k < num_vert; k++){
            if (i != k) matrix[i][k] = get_distance(i, k);
            if (i == k) matrix[i][k] = INFINITY;
        }
    }
}

void OPT::genPerms(vector<size_t> &path, size_t permLength){
    if (permLength == path.size()) {
        double temp_cost = calculate_cost(path);
        if (temp_cost < calculate_cost(TSP)){
            TSP = path;
            TSPcost = temp_cost;
        }
        return;
    }
    
    if (!promising(path, permLength)){
        return;
    }
    for (size_t i = permLength; i < path.size(); ++i){
        swap(path[permLength], path[i]);
        genPerms(path, permLength + 1);
        swap(path[permLength], path[i]);
        
    }
}

bool OPT::promising(vector<size_t> &path, size_t permLength){
    vector<size_t> partial1(path.begin(), path.begin() + (int)permLength);
    vector<size_t> partial2(path.begin() + (int)permLength, path.end());
    double path_cost, path_MST, conn_cost;
    
    genMST(partial2);
    path_MST = MSTweight;
    path_cost = partial_cost(partial1);
    conn_cost = connection_cost(path, partial1);
    
    if (path_MST + path_cost + conn_cost >= TSPcost){
        return false;
    }
    
    return true;
}

double OPT::connection_cost(vector<size_t> &path, vector<size_t> &partial){
    double minBeg = INFINITY;
    double minEnd = INFINITY;
    
    for (size_t i = 0; i < path.size(); i++){
        
        if (matrix[partial[0]][path[i]] < minBeg
            && path[i] != partial.back()){
            minBeg = matrix[partial[0]][path[i]];
        }
        if (matrix[partial.back()][path[i]] < minEnd
            && partial.back() != path[i]){
            minEnd = matrix[partial.back()][path[i]];
        }
    }
    
    return minBeg + minEnd;
}


//*************************************************//
//**********************HELPERS********************//
//*************************************************//

void OPT::get_coords(){
    Vert temp;
    
    cin >> num_vert;
    coords.reserve(num_vert);
    nums.reserve(num_vert);
    
    for (size_t i = 0; i < num_vert; i++){
        cin >> temp.x >> temp.y;
        coords.push_back(temp);
        nums.push_back(i);
    }
}

double OPT::get_distance(size_t one, size_t two){
    double c2, a2, b2;
    
    a2 = coords[two].y - coords[one].y;
    b2 = coords[two].x - coords[one].x;
    a2 = a2 * a2;
    b2 = b2 * b2;
    c2 = sqrt(a2 + b2);
    
    return c2;
    
}

double OPT::fast_distance(size_t one, size_t two){
    double a2, b2;
    
    a2 = coords[two].y - coords[one].y;
    a2 = a2 * a2;
    b2 = coords[two].x - coords[one].x;
    b2 = b2 * b2;
    
    return a2 + b2;
}

double OPT::partial_cost(vector<size_t> &P){
    double cost = 0;
    
    if (P.size() < 2) return 0;
    
    for (size_t i = 0; i < P.size() - 1; i++){
        cost += matrix[P[i]][P[i + 1]];
    }
    return cost;
}

//*************************************************//
//********************SPECIAL MST******************//
//*************************************************//

void OPT::genMST(vector<size_t> &p){
    size_t temp_num = p.size();
    coord = 0;
    MSTweight = 0;
    
    MST.resize(temp_num, current);
    for (size_t j = 0; j < temp_num; j++){
        current.c = p[j];
        current.v = false;
        current.d = INFINITY;
        MST[j] = current;
    }
    MST[0].d = 0;
    current = MST[0];
    
    for (size_t i = 0; i < temp_num; i++){
        if (!current.v){
            MST[coord].v = true;
            MSTweight += current.d;
            update_adjacent();
        }
    }
}

void OPT::update_adjacent(){
    size_t c = current.c;
    current.d = INFINITY;
    vector<Prims>::iterator t;
    size_t count = 0;
    for (t = MST.begin();t != MST.end(); t++){
        if (!t->v){
            double d = matrix[c][t->c];
            if (d < t->d){
                t->d = d;
                t->p = c;
            }
            if (t->d < current.d){
                current = *t;
                coord = count;
            }
        }
        count++;
    }
}

//*************************************************//
//********************SPECIAL FAST*****************//
//*************************************************//

void OPT::genFAST(vector<size_t> &p){

    vector<bool> v(p.size() + 1, false);
    TSP.reserve(p.size() + 1);
    
    //find 3 closest vertices and make a cycle 0->1->2->0
    now = p[0];
    TSP.push_back(now);
    v[0] = true;
    
    now = p[1];
    TSP.push_back(now);
    v[now] = true;
    
    now = p[2];
    TSP.push_back(now);
    v[now] = true;
    
    TSP.push_back(p[0]);
    
    for (size_t i = 1; i < p.size(); i++){
        if (!v[i]){
            size_t insert = find_insertion(i);
            v[insert] = true;
        }
    }
    TSP.pop_back();
    TSPcost = calculate_cost(TSP);
}

size_t OPT::get_closest(vector<bool> &v){
    size_t closest = 0;
    double temp_dist = INFINITY;
    
    for (size_t i = 1; i < num_vert; i++){
        if (!v[i]){
            double now_dist = matrix[now][i];
            if (now_dist < temp_dist){
                temp_dist = now_dist;
                closest = i;
            }
        }
    }
    return closest;
    
}

size_t OPT::find_insertion(size_t rand){
    vector<size_t>::iterator it;
    double min = INFINITY;
    size_t insert_p = 0;
    
    for (size_t i = 0; i < TSP.size() - 1; i++){
        double temp = matrix[TSP[i]][rand] +
        matrix[rand][TSP[i + 1]] - matrix[TSP[i]][TSP[i + 1]];
        
        if (temp < min){
            min = temp;
            insert_p = i;
        }
    }
    it = TSP.begin();
    TSP.insert(it + (int)insert_p + 1, rand);
    
    return insert_p;
}

double OPT::calculate_cost(vector<size_t> &T){
    double tour_weight = 0;
    
    for (size_t i = 0; i < T.size() - 1; i++){
        tour_weight += matrix[T[i]][T[i + 1]];
    }
    
    tour_weight += matrix[0][T.back()];
    
    return tour_weight;
}

void OPT::printOPT(vector<size_t> &path){
    
    cout << TSPcost << endl;
    
    for (auto &i : path){
        cout << (int)i << " ";
    }
    cout << endl;
}
