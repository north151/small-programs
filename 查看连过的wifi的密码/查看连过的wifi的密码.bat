@echo off
::MODE con: COLS=165 LINES=65
title �鿴WIFI���� %date% 
netsh wlan show profile
echo  ************************************************************************************
echo  ��ʾ:����Ϊ���������ӹ�WIFI��Ϣ,���Ҽ����Ƶ�����س��鿴,(��������0ֱ���˳�)
echo  ***********************************************************************************
:menu
echo.
  set /p var=Ҫ�鿴��Կwifi��ע�ⲻҪ�пո�:
if  "%var%"  equ  ""  goto  menu 
if  %var%    equ 0  exit
netsh wlan show profile name="%var%" key=clear >wifi.txt
cls
color 6
type wifi.txt | findstr �ؼ�����
echo.
pause&del wifi.txt
