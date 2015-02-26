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
if %curFile%==5 (
	set searchString=1231234
	set replaceString=ABCABCD
)
if %curFile%==6 (
	set searchString=1231234
	set replaceString=ABCABCD
)

del %curFile%.tmp >nul 2>&1
Replace.exe %curFile%.in %curFile%.tmp %searchString% %replaceString%
fc /b %curFile%.tmp %curFile%.out
del %curFile%.tmp

if %curFile% lss 6 (
	set /a curFile=%curFile%+1
	goto loopStart
)

pause
