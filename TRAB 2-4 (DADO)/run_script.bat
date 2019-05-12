@echo off

cd Release
echo Versoes disponiveis:
echo.
dir /b
echo.
set /p EXE_NAME= Nome do exectavel: 
cd ..
echo.

:teste
echo Testes disponiveis:
echo.

cd testes_scripts
dir /b
echo.
set /p SCRIPT_NAME= Nome do script: 
cd ..
echo.

set /p LOG_NAME= Nome do log: 
echo.

Release\%EXE_NAME% /stestes_scripts\%SCRIPT_NAME% /l>testes_log\%LOG_NAME%.log

start testes_log\%LOG_NAME%.log

@choice /m "Repetir com um novo script?"

IF ERRORLEVEL 2 GOTO eof
IF ERRORLEVEL 1 GOTO teste
