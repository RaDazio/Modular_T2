@echo off
@CHOICE /C:123 /m "1:Rafael 2:Gabriel 3:Felipe  "

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

:end
exit