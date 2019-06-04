# VirtualKeyboard (<a href='https://qtcentre.org/threads/49181-virtual-keyboard-in-QT-Application'>qtcentre.org</a>)
virtual keyboard in QT Application

numpad layout:
<img src=numpad.png />
keyboard layout:
<img src=keyboard.png />

Virtual Keyboard for touch-screen devices written in C/C++ Qt, compatible with 5.x
The keyboard only works with QLineEdit.

the widget is written by (<a href='https://qtcentre.org/members/36463-StrikeByte'>StrikeByte</a>) 
I added a simple example to show the usage.

How to use:
* Build the library
* copy the library to platforminputcontexts in your application or to plugins/platforminputcontexts in your QtDir
* Add a custom property named "keyboard" (without the quotes) of the type bool to the QLineEdit and set it to enabled
* For text you can set the maxLength property
* For values you can add a QIntValidator to the QLineEdit


