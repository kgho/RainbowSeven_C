;�˴��������4����༭����EXE�ļ����ڵ�Ŀ¼
SET EDITOR_EXE_DIR=D:\_I\UE_4.24\Engine\Binaries\Win64
@echo off
SET UE_EXE=%EDITOR_EXE_DIR%\UE4Editor.exe

set var=0
rem ************ѭ����ʼ
:continue
set /a var+=1
echo ��%var%��ѭ��
start /B "Client" "%UE_EXE%" "%CD%\RainbowSeven_C.uproject" -game
if %var% lss 2 goto continue
rem ************ѭ������
echo ѭ��ִ�����

