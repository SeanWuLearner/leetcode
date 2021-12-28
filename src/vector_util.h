#ifndef VECTOR_UTIL_H
#define VECTOR_UTIL_H

template<typename T>
void printVec(vector<T> v){
    for(auto&& i: v)
        cout << i << ", ";
    cout << endl;
}

template<typename T>
void printVec(vector<vector<T>> v){
    for(auto&& i: v)
        printVec(i);
}

template<typename T1, typename T2>
void printVecPair(vector<pair<T1,T2>>& vs, bool add_linebreak=false){
    string newline = (add_linebreak)? "\n" : "";
    for(auto&& v : vs)
        cout << "(" << v.first << ": "<< v.second << ")" << newline;
    cout << endl;
}

template<typename T1, typename T2>
void printVecPair(vector<pair<T1,T2>>&& vs, bool add_linebreak=false){
    printVecPair(vs, add_linebreak);
}

template<typename T>
vector<T>& sortVec(vector<T>& v){
    sort(v.begin(), v.end());
    return v;
}

template<typename T>
vector<T> sortVec(vector<T>&& v){
    sortVec(v);
    return v;
}

template<typename T>
vector<vector<T>>& sortVec(vector<vector<T>>& v){
    for(auto &&i : v )
        sortVec(i);
    sort(v.begin(), v.end());
    return v;
}

template<typename T>
vector<vector<T>> sortVec(vector<vector<T>>&& v){
    sortVec(v);
    return v;
}

#endif //VECTOR_UTIL_H