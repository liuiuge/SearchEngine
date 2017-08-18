#pragma once
#ifndef __OLWEBPAGE_H__
#define __OLWEBPAGE_H__
#include "Configuration.h"
#include "WordSegment.h"

class OLWebpage
{
    const static int TOPK_NUMBER = 20;
    string _doc;
    int _docid;
    string _doctitle;
    string _docurl;
    string _doccontent;
    string _docsummary;
    vector<string> _topword;
    map<string,int> _wordMap;
    friend bool operator == (const OLWebpage & lhs, const OLWebpage & rhs);
    friend bool operator < (const OLWebpage & lhs, const OLWebpage & rhs);
    void processDoc(const string & doc, My_conf & conf, Word_segment & jieba);
    void calcTopk(vector<string> & wordsVec, int k, set<string> & stopwordlist);
public:
    OLWebpage(){}
    OLWebpage(string & doc, My_conf & conf,Word_segment & jieba);
    int getDocid() {return _docid;}
    map<string,int> & getwordmap() {return _wordMap;}
    string getDocUrl() {return _docurl;}
	string getDoc() {return _doc;}
    string getDocTitle() { return _doctitle; }
    string summary(const vector<string> & queryword);
};
#endif
