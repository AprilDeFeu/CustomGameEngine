@echo off

setlocal
for /f "tokens=2,3,4 delims=/ " %%f in ('date /t') do set d=%%h%%g%%f
set dirPath = C:\Sources\RenderingEngine\Project\

C:\Sources\RenderingEngine\Project\Test\MathUnitTest.exe > C:\Sources\RenderingEngine\Project\Logs\UnitTest_Math_%d%_%TIME:~0,2%%TIME:~3,2%%TIME:~6,2%.log

