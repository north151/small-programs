@echo off
::MODE con: COLS=165 LINES=65
title 查看WIFI密码 %date% 
netsh wlan show profile
echo  ************************************************************************************
echo  提示:以上为本机所连接过WIFI信息,请右键复制到下面回车查看,(输入数字0直接退出)
echo  ***********************************************************************************
:menu
echo.
  set /p var=要查看密钥wifi，注意不要有空格:
if  "%var%"  equ  ""  goto  menu 
if  %var%    equ 0  exit
netsh wlan show profile name="%var%" key=clear >wifi.txt
cls
color 6
type wifi.txt | findstr 关键内容
echo.
pause&del wifi.txt
