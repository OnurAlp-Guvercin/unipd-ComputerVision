Task 1
Write a program that loads the image provided (robocup.jpg) and shows it.

Task 2
Expand Task 1 adding a callback function reacting to the mouse click. The callback prints the BGR color triplet of the pixel where the click occurred.

Task 3
Modify the callback in Task 2: the new version calculates the mean of the B, G and R values (separately) in a 9x9 neighborhood around the clicked pixel 
and prints such values.

Task 4
Expand Task 3 in order to segment (i.e., “select”) the T-shirts of the robot soccer players. Such selection operates by reading the average calculated 
in Task 3, taken as a reference color, setting a threshold T, and creating a new image, called mask, having:
● a white pixel if the corresponding pixel in the input image has all the three B, G and R values having a distance from the reference color not greater 
than T;
● a black pixel otherwise.
Visualize the mask on the screen. The mask is generated from scratch at every new click on the original image.

Task 5
Expand Task 4 by creating a new image whose pixels are:
● equal to the input image if the corresponding pixel in the mask is black;
● equal to a given color otherwise.
Choose the triplet (92, 37, 201) as the new color. This image is generated from scratch at every new click on the original image.
Are you able to change the color of the T-shirts?
Are you able to change the color of the ball?
