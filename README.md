Quickstart Template
hdbeefup.github.io

# Troubleshooting:

# BUGS:

# Features:


# Known issues:

------------------------------------------------------------------------------------------------------------
# How To Compile:
if you want, edit premake5.lua, to add more games, rename HDBQuickstartTemplate to something else, credits, etc etc.. be careful tho, it's picky with syntax too!


You can compile this with these steps:

1) Firstly run premake5.bat
2) Open `build\HDBQuickstartTemplate.sln` with Microsoft Visual Studio 2015 or 2019 [Any Edition, can be Community or Enterprise]
(If you want to use it with an older version, just change the platform toolset setting.)
3) Right click on Solution 'HDBQuickstartTemplate' > Build or just CTRL+SHIFT+B. (Or, you can open its contents by clicking the triangle at left. dllmain.cpp is the main code. Make the edits you want, you're free!)
!Make sure you're building with Release and Win32 option. See the upper toolbar for them.
4) Look for the "Output" panel. If it says "Build: 1 succeeded, 0 failed," and stuff, your .asi file has been successfully built. (It will be built into `(Project folder)\Release` folder.)
5) Now, copy it to your `*GAME LOCATION*\scripts` folder. (Use Ctrl+C, Ctrl+V / Cmd+C, Cmd+V / Strg+C, Strg+V; Right-Click > Copy; via xcopy command on CMD; or how do you like it.)
6) Copy the swinehdbconfig.ini from main folder into `*GAME LOCATION*\scripts` folder, too.
7) Run Game and see what happens. :)
If not get this https://github.com/ThirteenAG/Ultimate-ASI-Loader/ and put into "GAME LOCATION" folder (main one near game launcher / exectutable) rename dll file to d3d8 And try again.
