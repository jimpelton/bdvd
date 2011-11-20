README  
---------
Changelog:
  11-20-2011
  Created README_building.txt.

To build VolumeViewer you need a recent build of Qt and VTK.
The app is being developed with 64-bit versions VTK-5.8.0 and Qt 4.7.4, 
so for best results you should probably use those.

1. You need to set up Visual Studio 2010 to point to your 64-bit VTK and Qt libraries.
   
   **Note that you can also setup the 32-bit (Win32) project if you want, but really big 
   data sets might hit the max memory limit for a single 32bit app imposed by Windows 
   (I believe this is something like 2GB, it is not 4GB which is just the 
    max addressible memory space--very different from what the OS will actually give you!).
   
   Do these steps for both the Debug and Release configurations.
   (i)   Fire up VS.
   (ii)  Right click on the VolumeViewer project and select properties.
   (iii) Under C/C++->General->Additional Include Directories add the include directories for
         both the VTK and Qt builds. Keep the entries that are prepended with $(ProjectDir)\...!
   (iv)  Under Linker->General->Additional Library Directories add your VTK and Qt
         library directories.
		 Be sure you point to your *debug libs for Debug config*, and *release libs for Release*.
   (v)   Under Linker->Input->Additional Dependencies you need the following .lib files:
               qtmaind.lib
               QtCored4.lib
               QtGuid4.lib
               QVTK.lib
               vtkWidgets.lib
               vtkVolumeRendering.lib
               vtkIO.lib
               vtkRendering.lib
               vtkGraphics.lib
               vtkImaging.lib
               vtkFiltering.lib
               vtkCommon.lib
               vtksys.lib
		Note that the qt files appended with a "d". These are debug libs, for the release config
		you don't need the "d", just the name of the library. The VTK .libs are named the same.
	(vi) Done.
	  Select a .pro from the pro_examples directory.
	
2. Now you need to setup a .pro file for Qt's qmake.
	  1. Open it and add the paths to your includes directory to the INCLUDEPATH variable.
	  2. Add the paths to your lib directories to LIBS variable. 
	    a. If you have more than one each path needs to be
	       appended with a -L. Don't add both debug and release library paths to one .pro file. 
		   Just keep it simple. :)
	  3. After the -L options you need to add the library names (prepended with -l (lower case "ell")). 
	     These are the same .lib files as above but without the .lib extension.
	  4. The HEADERS and SOURCES should be good to go.
	  5. When you're done move the file into the VolumeViewer project directory (next to .vsxproj files).
	     Rename it to VolumeViewer.pro (maybe not required).

3. Now open up the VS Command prompt (remember to open the correct architechture 64/32 bit!)
     0. You might need to setup your Path.
     1. cd into the VolumeViewer project directory.
     2. Run qmake. (don't append any options, or at least -pro should *not* be there) This should create
	    some make files (3 of them, Makefile, Makefile.Release, Makefile.Debug)
	 3. Run nmake. nmake will create a *_moc.cpp files for the Qt gui and but them in a directory
	    called debug or release in the project directory.
	 4. You can now start the app from the command line.
	    The .exe files are in either ./debug or ./release folders.

4. Rebuild it in visual studio and you can start programming now!
   
