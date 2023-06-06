@ECHO OFF
cd ..\Src
g++ Math\Vectors.cpp Math\Geometry.cpp Math\Matrices.cpp UnitTest\UnitTests.cpp Main\Main.cpp -o ..\Test\MathUnitTest.exe
cd ..\Test
start "" c:\Sources\RenderingEngine\Project\Test\MathUnitTest.exe