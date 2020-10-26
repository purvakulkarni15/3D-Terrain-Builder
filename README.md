# 3D-Terrain-Builder

This project generates 3D model out of the topographical contour maps by employing image processing 
and triangulation algorithms.

### Methodology

<pre>
1. Command line interface is used to obtain the path of the contour map from the user.
2. findContours() API from OpenCV library is utilized to get the contours data from the map.
3. The heirarchy information about the contours provided by OpenCV is inadequate for contours touching the image boundary.
4. Hence, an algorithm is developed from scratch to establish heirarchy for the given set of contours.
5. Constrained Delaunay Triangulation is employed on the contour data points.
6. Elevation of data points is determined by contour heirarchy.
7. The 3D model is retained in .OBJ format.
</pre>

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
<pre>Contour Map and its 3D reconstruction:</pre>
<img src="https://github.com/purvakulkarni15/3D-Terrain-Builder/blob/master/ContourMap3D_1.bmp" width="50%" height="450"><img src="https://github.com/purvakulkarni15/3D-Terrain-Builder/blob/master/ContourMap3D_1.PNG" width="50%" height="450">

<img src="https://github.com/purvakulkarni15/3D-Terrain-Builder/blob/master/ContourMap3D_2.bmp" width="50%" height="450"><img src="https://github.com/purvakulkarni15/3D-Terrain-Builder/blob/master/ContourMap3D_2.PNG" width="50%" height="450">

