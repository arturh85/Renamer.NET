@echo off
del /S *.db  /AH
del /S *.log
del /S *.dmp
del /S *.opt
del /S *.suo
del /S *.ncb
del /S *.plg
del /S *.bak
del /S *.ilk
rmdir /S /Q dotnet\Debug
rmdir /S /Q dotnet\Release
rmdir /S /Q dotnet\Renamer\Debug
rmdir /S /Q dotnet\Renamer\Release
rmdir /S /Q dotnet\SQLite\Debug
rmdir /S /Q dotnet\SQLite\Release