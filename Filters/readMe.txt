Task 1
Filters and histogram equalization
Write a program that loads the image provided (image.jpg) and shows it. 
It then converts the image to grayscale (cv::cvtColor() function) and saves it with the image_grayscale.jpg name. 
Consider this last image for the next tasks.

Task 2
Expand Task 1 implementing a max filter and a min filter in two dedicated functions (implemented by you in a separate source file) 
that manipulate the pixels directly. Such functions accept an integer representing the size of the kernel, and check that it is an odd number.
If it is even, the function does not process the image and prints an error message. Apply the filters using several kernel sizes and find 
the best option that removes the electric cables in the background without corrupting the image too much.

Task 3
Expand Task 2 using the median filter and the gaussian smoothing filter provided by OpenCV. Show the results.

Task 4
Expand Task 1 plotting the histogram of the image using 256 bins and range [0, 255]. 
Try also other values for the number of bins. You are free to evaluate the histogram using your code or the functions provided by OpenCV

Task 5
Expand Task 4 including histogram equalization using the dedicated OpenCV function and visualize the result.
