#ifndef ERROR_H
#define ERROR_H

#include "globals.h"

class exFileLineDesc : public exception {
    string msModule;
    string msDescription;
    int miLine;

  public:
    exFileLineDesc(string sModule, int iLine, string sDescription): msModule(sModule), msDescription(sDescription), miLine(iLine)  {};
    ~exFileLineDesc() throw() {};
    virtual const char* what () const throw ();
};


class exString : public exception {
    string msClass;
    string msDescription;

  public:
    exString(string sDescription, string sClass);
    ~exString() throw() {};
    virtual const char* what () const throw ();

};

#define exAssert(expr) \
        if (!(expr)) exAssertFail (__FILE__, __LINE__, "" )

#define exAssertDesc(expr, desc) \
        if (!(expr)) exAssertFail (__FILE__, __LINE__, desc )
void exAssertFail(string sModule, int iLine, string sDescription);

#endif



