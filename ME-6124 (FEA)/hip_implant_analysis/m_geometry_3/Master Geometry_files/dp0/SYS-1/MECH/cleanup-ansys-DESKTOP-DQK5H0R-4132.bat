@echo off
set LOCALHOST=%COMPUTERNAME%
if /i "%LOCALHOST%"=="DESKTOP-DQK5H0R" (taskkill /f /pid 1816)
if /i "%LOCALHOST%"=="DESKTOP-DQK5H0R" (taskkill /f /pid 4132)

del /F cleanup-ansys-DESKTOP-DQK5H0R-4132.bat
