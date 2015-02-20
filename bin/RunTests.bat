@echo off

set curFile=1
:loopStart

if %curFile%==1 (
	set searchString=@findStr
	set replaceString=@replaceStr
)
if %curFile%==2 (
	set searchString=""
	set replaceString=""
)
if %curFile%==3 (
	set searchString="@find str"
	set replaceString="@replace str"
)
if %curFile%==4 (
	set searchString=rep
	set replaceString=reprep
)

Replace.exe %curFile%.in %curFile%.tmp %searchString% %replaceString%
fc /b %curFile%.tmp %curFile%.out

if %curFile% lss 4 (
	set /a curFile=%curFile%+1
	goto loopStart
)

pause
