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
bool inDictionary(const std::set<std::string>& dict, std::string& word);
bool hasFloating(const std::string& floating, char letter);
void formWord(const std::string& in, const std::string& floating,const std::set<std::string>& dict, std::string& word, unsigned int index, std::set<std::string>& validWords);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> validWords;
    std::string word;
    formWord(in, floating, dict, word, 0, validWords);
    return validWords;

}

// Define any helper functions here

//check if in dictionary 
bool inDictionary(const std::set<std::string>& dict, std::string& word){
    //std::set<std::string>::iterator it =dict.end() ;
    return dict.find(word) != dict.end();
}
// returns true if floating is present 
// bool hasFloating(const std::string& floating, char letter){
//     if(floating.find(letter) != std::string::npos){
//         return true;
//     }
//     return false;
// }

// add letters 
void formWord(const std::string& in, const std::string& floating,const std::set<std::string>& dict, std::string& word, unsigned int index, std::set<std::string>& validWords){
    if(in.length()-index < floating.length()){
        return;
    }
    if(index == in.length()){
        if(floating.length() == 0 && inDictionary(dict, word) ){
            validWords.insert(word);
        }
        return;
    }
    if(in[index] != '-'){
      word.push_back(in[index]);
      formWord(in, floating, dict ,word, index+1, validWords);
      word.pop_back();
    }
    else {
         for( char l = 'a'; l<='z'; ++l) {
            word.push_back(l);
            std::string temp = floating;
            if(temp.find(l) != std::string::npos){
                temp.erase(temp.find(l), 1);  
            }
            formWord(in, temp, dict ,word, index+1, validWords);
            word.pop_back();
        }
    }
    
}
