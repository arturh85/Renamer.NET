#include "stdafx.h"
#include "error.h"


//-------------------------------------------------------------------------
//  Class exFileLineDesc

void exAssertFail(std::string sModule, int iLine, string sDescription) {
  throw exFileLineDesc(sModule,iLine, sDescription);
}

const char* exFileLineDesc::what () const throw () {
  stringstream  strReturn;
  strReturn << "\n\nexFileLineDesc\n"
            << msModule << ":"
            << miLine;

  if (msDescription.size() > 0)
    strReturn << "\n" << msDescription;

  return strReturn.str().c_str();
}
