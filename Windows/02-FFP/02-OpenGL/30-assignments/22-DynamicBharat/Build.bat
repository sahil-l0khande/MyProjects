cl /c /EHsc /D UNICODE /I "C:\Program Files (x86)\OpenAL 1.1 SDK\include  OGL.c
rc.exe OGL.rc
link.exe OGL.obj OGL.res User32.lib GDI32.lib /LIBPATH:"C:\Program Files (x86)\OpenAL 1.1 SDK\libs\Win64" /SUBSYSTEM:WINDOWS