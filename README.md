## Bruon_motion
Для установки GLUT на Windows следуйте следующим инструкциям:
Скачайтте Glut c сайта OpenGL.
Скачиваем [GLUT](https://gcup.ru/go?http://www.opengl.org/resources/libraries/glut/).
В архиве: 
glut.def 
glut.h 
glut32.dll 
glut32.lib
README
Извлекаем файлы в любую из папок.

## Процесс установки

1.  Начнём с glut32.dll.Его мы должны перекинуть по этому адресу: 
C://Windows/System32 
2.  glut32.lib надо перекинуть по этому адресу: 
C://Program files/Microsoft Visual Studio/VC/lib 
3.  Для glut.h Мы создадим папку по адресу .../VC/include , назовём её GL.И в эту папку перекинем glut.h. 
(Таким же образом можно установить библиотеки gl.h и glu.h все файлы можно скачать по отдельности здесь) 
4.  Открываем Microsoft Visual C++.Создаём проект.(Win32->Консольное приложение(пустой проект)) 
5.  Правой кнопкой жмём на проект ->Cвойства->Открываем вкладку "Компоновщики".В "Дополнительных зависимостях"пишем: 
opengl32.lib glut32.lib glu32.lib 
