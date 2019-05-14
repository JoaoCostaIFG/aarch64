#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/stat.h>
#include <set>
#include <utility>
#include <map>

/*
struct cmp {
    bool operator() (const std::pair<int, std::string> &a, const std::pair<int, std::string> &b) const {
        return a.first < b.first;
    }
};*/

/*
typedef std::pair<int, std::string> dests_visits;
auto cmp_visits = [](dests_visits const a, dests_visits const b) { return a.first > b.first; };
std::set<dests_visits, decltype(cmp_visits)> set_visits(cmp_visits);
*/

//typedef std::set<A, decltype(cmp)> B(cmp);
typedef std::pair<std::string, int> A;
//auto cmp = [](A const c, A const d) { return c.second > d.second; };
struct cmp{
    bool operator() (const A &c, const A &d) const
    {return c.second > d.second;}
};
int main(){

    std::multiset<A, cmp> b;
    std::multiset<A, cmp> ::iterator it;
    
    A a = std::make_pair(std::string("AAA"), 3);
    b.insert(a);
    a = std::make_pair(std::string("BB"), 2);
    b.insert(a);
    a = std::make_pair(std::string("C"), 2);
    b.insert(a);
    int j = 3;
    if (b.find(std::make_pair(std::string(""), 4)) == b.begin()){
        std::cout << "AAAAAAAAAAAA\n";
    }
    //std::cout << (*b.find(std::make_pair(3, std::string("AA")))).first << '\n';
    //b.erase(b.find(std::make_pair(5, std::string(""))));
    std::cout << '\n';
    for(it = b.begin(); it != b.end(); it++){
        std::cout << ' ' << (*it).second;
    }

    /*
    for (A x : b)
        std::cout << x.first << ' ';*/
    
    /*
    set<int> a;
    a.insert(1);
    a.insert(-1);
    a.insert(3);
    a.insert(2);
    a.insert(0);
    a.erase(a.find(2));
    cout << *a.find(56);
    if (a.find(2) != a.end()){
        cout << "AAA\n";
    }
    //std::cout << *a.begin() << '\n';
    */
    return 0;
}