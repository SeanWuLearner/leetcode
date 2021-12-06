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

#endif //VECTOR_UTIL_H