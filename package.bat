mkdir dist
copy "bin\Renamer .NET.exe" dist\
copy "bin\boost*.dll" dist\
del "dist\boost*-gd-*.dll"

copy "Documentation\licence.txt" dist\

mkdir dist\de-DE
copy "bin\de-DE" dist\de-DE

