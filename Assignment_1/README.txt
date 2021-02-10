Name: Stephen Allegri
GTID: 903207717

OS: Windows 10
Compiler: MiniGW
IDE: CLion

How I run my program (using CLion):

1. Install MiniGW @ http://mingw-w64.org/doku.php/download/mingw-builds --> If this doesn't work, there are other open source versions and instructions online (at the official
CLion support site). 

2. create a new project --> settings --> Build, Execution, Deployment --> Toolchains --> MiniGW (find path and select- it should automaticall configure)

3. Copy and paste my code into the new project main.c file. If this doesn't run, refactor (right click main.c to find the option) the name to "powerlaw"