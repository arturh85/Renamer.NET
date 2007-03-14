#pragma once

bool To_string( String^ source, string &target );
bool To_CharStar( String^ source, char*& target );
string toStdString(String^source);
String^ toClrString( string source );
