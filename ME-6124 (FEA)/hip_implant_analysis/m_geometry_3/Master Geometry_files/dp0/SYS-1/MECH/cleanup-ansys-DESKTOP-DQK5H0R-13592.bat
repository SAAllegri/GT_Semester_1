@echo off
set LOCALHOST=%COMPUTERNAME%
if /i "%LOCALHOST%"=="DESKTOP-DQK5H0R" (taskkill /f /pid 6364)
if /i "%LOCALHOST%"=="DESKTOP-DQK5H0R" (taskkill /f /pid 13592)

del /F cleanup-ansys-DESKTOP-DQK5H0R-13592.bat
