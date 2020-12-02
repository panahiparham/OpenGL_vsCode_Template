## Starting an OpenGL project in vsCode using msvc compiler

### First
<br />make sure you have visual studio with C++ build tools installed

<br /> open the "developer command prompt for vs" and navigate to the project folder and open vs code by `code .` remember to open vsCode in the same way each time you want to enter the project

<br /> make sure you have C++ extension for vsCode installed

<br /> Create a .cpp file in the project folder and save it. then open up the terminal and select "configure default build task" and choose `cl.exe`. then hit Ctrl+shift+P and choose "C/C++ : Edit Configurations(JSON)"

<br /> You now should have 2 new files under `.vscode` folder we will be modifying these two files to set compiler flags and link the program later

### Setting up some Compiler flags

<br> Inside `tasks.json` add these two lines inside the "args" variable `"/MD"` and `"/Link /NODEFAULTLIB:msvcrt.lib"`

### linking with proper windows libraries for window making and legacy opengl libraries

<br /> we will be using GLFW or GLUT for window making purposes, and they need access to windows libraries to do their job so we need to find these libraries and link with them, you can look around for them, for me they were here `"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\\` so i added these libraries to the "args" variable of `tasks.json` my `tasks.json` now looks like this:

```
{
	"version": "2.0.0",
	"tasks": [
		{
			"type": "cppbuild",
			"label": "C/C++: cl.exe build active file",
			"command": "cl.exe",
			"args": [
				"/Zi",
				"/EHsc",
				"/MD",
				"/Fe:",
				"${fileDirname}\\${fileBasenameNoExtension}.exe",
				"${file}",

				"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\\OpenGL32.Lib",

				"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\\User32.Lib",
				"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\\Gdi32.Lib",
				"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\\shell32.lib",


				"/Link /NODEFAULTLIB:msvcrt.lib"
			],
			"options": {
				"cwd": "${workspaceFolder}"
			},
			"problemMatcher": [
				"$msCompile"
			],
			"group": {
				"kind": "build",
				"isDefault": true
			},
			"detail": "compiler: cl.exe"
		}
	]
}

```

<br /> Now therer are 2 different Libraries for window making GLFW and GLUT

### Setting up GLUT

<br /> First you need prebuilt version of GLUT, you can find freeGlut online. then add a `GLUT/` folder to the project and copy the dll file tode root of the project where the executables will be.

<br /> then we need to add GLUT to the include path to do this add `"${workspaceFolder}\\GLUT"` to the "includePath" of `c_cpp_properties.json` and add `"/I${workspaceFolder}\\GLUT",` to the "args" of `tasks,json`

<br /> then we need to link with `glut32.lib` so add this line to the "args" of `tasks.json`. `"${workspaceFolder}\\GLUT\\glut32.lib"`.


<br /> now to see if glut is working fine create `testGlut.cpp` and add the following lines

```
/* simple.c */

#include <glut.h>

#include <stdio.h>


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.5);
        glVertex2f( 0.5, -0.5);
        glVertex2f( 0.5,  0.5);
        glVertex2f(-0.5,  0.5);
    glEnd();

    glFlush();
}

void main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutCreateWindow("simple");
    glutDisplayFunc(display);

    printf("%s", glGetString(GL_VERSION));

    glutMainLoop();
}
```

<br /> now build the project wiht ctrl+shift+B and if everything is fine u can run testGlut.exe too see the result.


### Setting up GLFW

<br /> to setup GLFW first download the windows binaries from [their website](https://www.glfw.org/download.html) and place the contents of glfw folder in  `GLFW/` in our project. we will only need `include/` and `lib-vc2019` or equivalent.

<br /> next we add the include path to the "includePath" of `c_cpp_properties.json` with `"${workspaceFolder}\\dependencies\\GLFW\\include"` and to "args" of `tasks,json` with `"/I${workspaceFolder}\\dependencies\\GLFW\\include"`. then link with `glfw3.lib` by adding `"C:\\DEV\\Graphics\\neelaGL\\dependencies\\GLFW\\lib-vc2019\\glfw3.lib"` to "args" of `tasks.json`.

<br /> to test if everything worked create `testGLFW.cpp` and copy the contents of [GLFW's quickstart guide](https://www.glfw.org/documentation.html) into it, then build and run


### Setting up GLEW

<br /> unlike GLUT, GLFW does not provide an OpenGL extension wrangler so we need to use one like [GLEW](http://glew.sourceforge.net/) download the windows binaries and unpack the filed into `GLEW/` folder we will need the `include/` and `lib/Release/Win32/glew32s.lib` once again we include the path in `tasks.json` and `c_cpp_properties.json` and link with `lib/Release/Win32/glew32s.lib` after everything is done `tasks.json` will look like

```
{
	"version": "2.0.0",
	"tasks": [
		{
			"type": "cppbuild",
			"label": "C/C++: cl.exe build active file",
			"command": "cl.exe",
			"args": [
				"/Zi",
				"/EHsc",
				"/MD",
				"/Fe:",
				"${fileDirname}\\${fileBasenameNoExtension}.exe",
				"${file}",

				"${workspaceFolder}\\GLFW\\lib-vc2019\\glfw3.lib",
				"${workspaceFolder}\\GLEW\\lib\\Release\\Win32\\glew32s.lib",

				"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\\OpenGL32.Lib",

				"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\\User32.Lib",
				"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\\Gdi32.Lib",
				"C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.18362.0\\um\\x86\\shell32.lib",

				"${workspaceFolder}\\GLUT\\glut32.lib",

				"/I${workspaceFolder}\\GLFW\\include",
				"/I${workspaceFolder}\\GLEW\\include",

				"/I${workspaceFolder}\\GLUT",


				"/Link /NODEFAULTLIB:msvcrt.lib"
			],
			"options": {
				"cwd": "${workspaceFolder}"
			},
			"problemMatcher": [
				"$msCompile"
			],
			"group": {
				"kind": "build",
				"isDefault": true
			},
			"detail": "compiler: cl.exe"
		}
	]
}
```

and `c_cpp_properties.json` will look like

```
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "${workspaceFolder}\\GLUT",
                "${workspaceFolder}\\GLFW\\include",
                "${workspaceFolder}\\GLEW\\include"

            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "windowsSdkVersion": "10.0.18362.0",
            "compilerPath": "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.27.29110/bin/Hostx64/x64/cl.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "msvc-x64"
        }
    ],
    "version": 4
}
```

<br /> finally lets modify `testGLFW.cpp` to see is GLEW works

```
#define GLEW_STATIC


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL cont"/LIBPATH:${workspaceFolder}\\dependencies\\GLFW\\lib",ext */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cout << glewGetErrorString(err) << std::endl;

    }

    std::cout << glGetString(GL_VERSION) << std::endl;



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);

        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.0f,  0.5f);
        glVertex2f( 0.5f, -0.5f);

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
```
<br /> we are now done with setting up GLFW and GLEW or setting up GLUT, we can use either of these in OpenGL projects

<br />