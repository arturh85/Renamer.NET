#ifndef ERROR_H
#define ERROR_H

#include "globals.h"

//! thrown by exAssert
class exFileLineDesc : public exception {
    string msModule;
    string msDescription;
    int miLine;

  public:
    exFileLineDesc(string sModule, int iLine, string sDescription): msModule(sModule), msDescription(sDescription), miLine(iLine)  {};
    ~exFileLineDesc() throw() {};
    virtual const char* what () const throw ();
};


class exNoSuchId : public runtime_error {
	public:
		exNoSuchId() : runtime_error("no such id") {};
		virtual ~exNoSuchId() throw()  {};
	protected:

	private:

};


#define exAssert(expr) \
        if (!(expr)) exAssertFail (__FILE__, __LINE__, "" )

#define exAssertDesc(expr, desc) \
        if (!(expr)) exAssertFail (__FILE__, __LINE__, desc )
void exAssertFail(string sModule, int iLine, string sDescription);

#endif



