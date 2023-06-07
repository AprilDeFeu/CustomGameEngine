setlocal
for /f "tokens=2,3,4 delims=/ " %%f in ('date /t') do set d=%%h%%g%%f
for /f "tokens=1,2 delims=: " %%f in ('time /t') do set t=%%f%%g
set datetime = %d%_%TIME:~0,2%%TIME:~3,2%
set dirPath = C:\Sources\RenderingEngine\Project\

C:\Sources\RenderingEngine\Project\Test\MathUnitTest.exe > C:\Sources\RenderingEngine\Project\Logs\UnitTest_Math_%d%_%TIME:~0,2%%TIME:~3,2%.log

