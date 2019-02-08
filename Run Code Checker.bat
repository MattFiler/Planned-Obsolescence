@echo ///////////// EXECUTING CODE CHECK! /////////////
@echo To run this tool you must have CPPCheck installed.
@echo --------------------------------------------------
"C:\Program Files\Cppcheck\cppcheck.exe" --quiet --enable=all --std=c++14 --language=c++ --error-exitcode=1 --inline-suppr --force --suppressions-list=CI/datpak/Tools/Cppcheck/suppress.conf main.cpp Source/*
pause