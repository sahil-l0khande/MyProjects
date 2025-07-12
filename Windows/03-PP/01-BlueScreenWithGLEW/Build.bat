cl.exe /c /EHsc OGL.c /I C:\glew-2.1.0\include
rc.exe OGL.rc
link.exe OGL.obj OGL.res User32.lib GDI32.lib /LIBPATH:"C:\glew-2.1.0\lib\Release\x64" /SUBSYSTEM:WINDOWS