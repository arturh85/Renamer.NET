/************************************************************************
Copyright (c) 2008, Artur H., Lennart W.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided 
with the distribution.
* Neither the name of the authors nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.                                                                     */
/************************************************************************/


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



