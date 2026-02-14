Installing GLFW

Download glfw-3.4.bin.WIN64

1. Go to Solution Directory
2. Create folder called Dependencies
3. Create folder called Dependencies\GLFW
4. Within the glfw-3.4.bin.WIN64, copy include and lib-vc2022 and paste them into the new folder

Setting up the include directory

1. Open the properties on your project
2. Go to C/C++ -> General -> Additional Include Directories
4. Set to $(SolutionDir)Dependencies\GLFW\include
	- $(SolutionDir) is a macro to your solution directory
	
Set up library directory

1. Go to Linker -> General -> Additional Library Directories
2. Set $(SolutionDir)Dependencies\GLFW\lib-vc2022

Now we need to link the glfw3.lib file

1. Go to Linker -> Input -> Additional Dependencies
2. Add glfw3.lib
