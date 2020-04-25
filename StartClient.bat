;此处设置虚幻4引擎编辑器的EXE文件所在的目录
SET EDITOR_EXE_DIR=D:\_I\UE_4.24\Engine\Binaries\Win64
@echo off
SET UE_EXE=%EDITOR_EXE_DIR%\UE4Editor.exe

set var=0
rem ************循环开始
:continue
set /a var+=1
echo 第%var%次循环
start /B "Client" "%UE_EXE%" "%CD%\RainbowSeven_C.uproject" -game
if %var% lss 2 goto continue
rem ************循环结束
echo 循环执行完毕

