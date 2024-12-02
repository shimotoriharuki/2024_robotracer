@echo off

cd .

if "%1"=="" ("C:\PROGRA~1\MATLAB\R2024a\bin\win64\gmake"  -f getEquationOfStateParameters2_rtw.mk all) else ("C:\PROGRA~1\MATLAB\R2024a\bin\win64\gmake"  -f getEquationOfStateParameters2_rtw.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1