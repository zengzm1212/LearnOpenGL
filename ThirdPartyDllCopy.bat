set edition=%~1
set oldPath=%cd%

cd  /d %~dp0

:: 拷贝 Assimp 的 dll
call :copyfile "thirdParty\assimp\Assimp.redist.3.0.0\build\native\bin\Win32\Assimp32.dll" "bin\Win32Debug\"

cd  /d %oldPath%


::======================函数声明================================
:: 拷贝文件
:copyfile 
xcopy /y /f %~1 %~2
IF %ERRORLEVEL% GTR 0 (
    echo 不能拷贝 %~1 到 %~2
    exit %ERRORLEVEL%)
goto:eof

:: 拷贝文件夹
:copydirectory
xcopy /e /y %~1 %~2
IF %ERRORLEVEL% GTR 0 (
    echo 不能拷贝 %~1 到 %~2
    exit %ERRORLEVEL%)
goto:eof