#ifndef STLUTILITY_H
#define STLUTILITY_H

std::string toStlString(std::wstring source);
std::wstring toStdWString(std::string source);

inline int system(string s) { return system(s.c_str()); };

#endif
