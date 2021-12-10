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