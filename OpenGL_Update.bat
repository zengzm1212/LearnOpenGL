set edition=%~1
set oldPath=%cd%

cd  /d %~dp0
md bin\build
cd /d bin\build

REM call cmake ..\..\source -G "Visual Studio 14 Win64" -Wno-dev
call cmake ..\..\source -Wno-dev

exit

cd  /d %oldPath%