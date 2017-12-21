#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils {
    
public:

    /* unsigned int split
     * split a <txt> variable at each instance of a delimiter provided (char ch) 
     * and add each new string generated to
     * provided vector of strings (strs).
     * like python's string.split()
     * returns size of vector as an unsigned int
     */
    static unsigned int split( const std::string &txt, std::vector<std::string> &strs, char ch ) {
        int pos = txt.find( ch );
        int initialPos = 0;
        strs.clear();

        while ( pos != std::string::npos ) {
            strs.push_back(txt.substr( initialPos, pos - initialPos + 1));
            initialPos = pos + 1;
            pos = txt.find( ch, initialPos );
        }

        strs.push_back( txt.substr( initialPos, std::min<int>( pos, txt.size() - initialPos + 1 )));
        return strs.size();
    }

};

#endif
