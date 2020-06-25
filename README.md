# ASCIIArt-CPlus-Plus
A Console based Pen/Canvas manipulator program that also features creating ASCII versions of given images along with video time-lapses of the image creation.

The commands from the original spec are all the same syntax from the original spec. Aside from removing all error checking and changing the program to line by line execution, the changes that have been made are to the loop command. The syntax for this command is now as follows: <br/> 
```
loop <count> 
...(statements) 
end loop 
```
Only upto two levels of nesting are permitted. <br/> 

3 new commands have been added. They do not take any parameters. They are as follows: <br/> 
```
display (prints the current state of the canvas) 
clear (clears the console) 
undo (reverts to the previous state of the pen/board, when used after a loop the last statement of the loop is undone) 
```

The final change was the addition of the ASCII image generator and accompanying time lapse video. This was accomplished with OpenCV and since this does not come pre installed on most environments, I have commented out the code that pertains to it. They exist as just functions which can be called. If OpenCV is installed, they will be easily runnable. <br/> 
That said, since it is somewhat a hassle to install OpenCV, I have included a video of these two features working as well as a sample image and video generated.
