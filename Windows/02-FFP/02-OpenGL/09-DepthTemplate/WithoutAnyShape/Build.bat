cl.exe /c /EHsc OGL.c /I C:\glew-2.1.0\include
rc.exe OGL.rc
link.exe OGL.obj OGL.res /LIBPATH:C:\glew-2.1.0\lib\Release\x64 User32.lib GDI32.lib /SUBSYSTEM:WINDOWS