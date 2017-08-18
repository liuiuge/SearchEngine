#pragma once
#ifndef __WORDQUERY_H__
#define __WORDQUERY_H__



#include "OLWebPage.h"
#include "Configuration.h"
#include "WordSegment.h"
using std::unordered_map;
using std::pair;
using std::set;
class My_conf;
class OLWebpage;

class wordQuery{
    My_conf & _conf;
    Word_segment _jieba;
    unordered_map<int, OLWebpage> _pagelib;
    unordered_map<int,pair<int,int>> _offsetlib;
    unordered_map<string ,set<pair<int,double>>> 
        _invertIndexTable;
    void loadLibrary();
    vector<double> getQueryWordsWeightVector(vector<string> &);
    bool executeQuery(const vector<string> &, vector<pair<int,vector<double>>> &);
    string createJson(vector<int> & , const vector<string> &);
    string returnNoAnswer();
public:
    wordQuery(My_conf & conf);
    string doQeury(const string & str);
};

#endif
