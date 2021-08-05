xcopy /d /y   ..\..\..\lib\cuda\*.dll
xcopy /d /y   ..\..\..\lib\onnxruntime\*.dll
xcopy /d /y   ..\..\..\lib\sodium\*.dll
xcopy /d /y   ..\..\..\lib\opencv\release\*.dll
xcopy /d /y   ..\..\..\lib\camera\release\*.dll
xcopy /d /y   ..\..\..\lib\camera\basler\*.dll
xcopy /d /y   ..\..\..\lib\camera\mvs\*.dll
xcopy /d /y   ..\..\..\lib\libjpeg-turbo\*.dll

 set PATH = %PATH%;C:\Qt\Qt5.14.1\5.14.1\msvc2017_64\bin
 C:\Qt\Qt5.14.1\5.14.1\msvc2017_64\bin\windeployqt.exe  SCC_PCB_CaptureSoftware.exe