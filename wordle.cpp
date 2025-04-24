#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void backtrack(string current, int idx, string floating, const set<string>& dict, set<string>& results);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    string current = in;
    backtrack(current,0,floating,dict,results);
    return results;
}

// Define any helper functions here
void backtrack(string current, int idx, string floating, const set<string>& dict, set<string>& results) {
	int n = current.size();
	if(idx==n) {
		if(floating.empty() && dict.find(current) != dict.end()) results.insert(current);
		return;
	}
	if(current[idx] != '-') backtrack(current,idx+1,floating,dict,results);
	else {
		for(size_t i=0; i<floating.size(); ++i) {
			char c = floating[i];
			current[idx] = c;
			string newFloating = floating.substr(0,i) + floating.substr(i+1);
			backtrack(current, idx+1, newFloating, dict, results);
		}
		for(char c = 'a'; c <= 'z'; ++c) {
			if(floating.find(c) != string::npos) continue;
			current[idx] = c;
			backtrack(current, idx+1, floating, dict, results);
		}
	}
}
