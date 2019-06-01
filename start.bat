@echo off
@CHOICE /C:1234 /m "1:Rafael 2:Gabriel 3:Felipe 4:Stefano"

IF ERRORLEVEL 4 GOTO ste
IF ERRORLEVEL 3 GOTO fel
IF ERRORLEVEL 2 GOTO jon
IF ERRORLEVEL 1 GOTO raf

GOTO end

:raf
start Relatorios/RELATORIO-RafaelDamazio.txt
goto end

:jon
start Relatorios/RELATORIO-GabrielMascheroni.txt
goto end

:fel
start Relatorios/RELATORIO-FelipeOliveira.txt
goto end

:ste
start Relatorios/RELATORIO-Stefano.txt

:end
exit