#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <ctime>

#define TIME

using namespace std;


struct  strtab_cmp
{
    typedef  vector<char>::iterator  strtab_iterator;

    bool  operator()( const pair<strtab_iterator, strtab_iterator>& x,
                       const pair<strtab_iterator, strtab_iterator>& y ) const {
        return lexicographical_compare( x.first, x.second, y.first, y.second );
    }
};

struct  strtab_print
{
    typedef  vector<char>::iterator strtab_iterator;
    ostream& out;

    strtab_print(ostream&  os) : out (os) {}

    void  operator()( const pair<strtab_iterator, strtab_iterator>&  s ) const {
        copy( s.first, s.second, ostream_iterator<char>(cout) );
    }
};


int main()
{
    vector<char>  strtab;	   // Create string table
    char  c;
    
    clock_t t = clock();

    while (cin.get(c)) {
        strtab.push_back(c);
    }

    t = clock() - t;
    cout << "Input took " << t << " clicks (" << ((float) t)/CLOCKS_PER_SEC << " seconds).\n";
    t = clock();

    // Parse the string table into lines.
    typedef  vector<char>::iterator  strtab_iterator;
    vector<pair<strtab_iterator, strtab_iterator>> lines;
    strtab_iterator  start = strtab.begin();

    while (start != strtab.end()) {
        strtab_iterator  next = find( start, strtab.end(), '\n' );

        if (next != strtab.end())
            ++next;
        lines.push_back( make_pair( start, next ) );
        start = next;
    }

    t = clock() - t;
    cout << "Character Table Creation took " << t << " clicks (" << ((float) t)/CLOCKS_PER_SEC << " seconds).\n";
    t = clock();

    // Sort the vector of lines
    sort( lines.begin(), lines.end(), strtab_cmp() );

    t = clock() - t;
    cout << "Sorting took " << t << " clicks (" << ((float) t)/CLOCKS_PER_SEC << " seconds).\n";
    t = clock();

    // Write the lines to standard output
    for_each( lines.begin(), lines.end(), strtab_print(cout) );


    t = clock() - t;
    cout << "Output took " << t << " clicks (" << ((float) t)/CLOCKS_PER_SEC << " seconds).\n";

    return 0;
}
