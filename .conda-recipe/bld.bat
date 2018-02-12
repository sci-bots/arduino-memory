@echo off
setlocal enableextensions
md "%PREFIX%"\Library\include\Arduino
endlocal
xcopy /S /Y /I /Q "%SRC_DIR%"\include\Arduino\Memory "%PREFIX%"\Library\include\Arduino\Memory
if errorlevel 1 exit 1
