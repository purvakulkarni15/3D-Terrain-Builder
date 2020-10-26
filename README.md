# 3D-Terrain-Builder

This project generates 3D model out of the topographical contour maps by employing image processing 
and triangulation algorithms.

### Libraries
<pre>
1. OpenCV - For Image Generation
</pre>

### Installation

#### Windows

<pre>
1. Download latest compatible version of opencv
2. Extract and copy the opencv dlls into the program folder or in the windows/system32 directory.
3. Create a new Visual Studio project.
4. Copy and paste the path to the opencv include folder in the project properties->vc++ directories->Include.
5. Copy and paste the path to the opencv library folder in the project properties->vc++ directories->Libraries.
6. Add the necessary opencv libraries to the properties->linker->Input
7. Last but not the least, add the source files to the project...And the project is ready to run!
</pre>

### Results
<img src="https://github.com/purvakulkarni15/3D-Terrain-Builder/blob/master/ContourMap3D_1.bmp" width="40%" height="500"><img src="https://github.com/purvakulkarni15/3D-Terrain-Builder/blob/master/ContourMap3D_1_Mesh.PNG" width="40%" height="500"><img src="https://github.com/purvakulkarni15/3D-Terrain-Builder/blob/master/ContourMap3D_1.PNG" width="40%" height="500">
![Contour Map](https://github.com/purvakulkarni15/3D-Terrain-Builder/blob/master/ContourMap3D_2.bmp)

![3D Reconstruction](https://github.com/purvakulkarni15/3D-Terrain-Builder/blob/master/ContourMap3D_2.PNG)

![3D Reconstruction - Mesh](https://github.com/purvakulkarni15/3D-Terrain-Builder/blob/master/ContourMap3D_2_Mesh.PNG)
