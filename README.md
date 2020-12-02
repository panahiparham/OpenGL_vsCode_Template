## Starting an OpenGL project in vsCode using msvc compiler

### First
<br />make sure you have visual studio with C++ build tools installed

<br /> open the "developer command prompt for vs" and navigate to the project folder and open vs code by `code .` remember to open vsCode in the same way each time you want to enter the project

<br /> make sure you have C++ extension for vsCode installed

<br /> Create a .cpp file in the project folder and save it. then open up the terminal and select "configure default build task" and choose `cl.exe`. then hit Ctrl+shift+P and choose "C/C++ : Edit Configurations(JSON)"

<br /> You now should have 2 new files under `.vscode` folder we will be modifying these two files to set compiler flags and link the program later


