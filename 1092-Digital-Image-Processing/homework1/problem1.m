% load color image and display it
I = imread('lenna-RGB.tif');
figure,
subplot(3,2,1), imshow(I), title('Original image');
% convert it to grayscale if needed
grayI = rgb2gray(I);
subplot(3,2,2), imshow(grayI), title('Grayscale image')
% divide the image into 4 parts with the same size
[row,col] = size(grayI);
I1 = grayI(1:round(row/2), 1:round(col/2));
I2 = grayI(1:round(row/2), round(col/2)+1:end);
I3 = grayI(round(row/2)+1:end, 1:round(col/2));
I4 = grayI(round(row/2)+1:end, round(col/2)+1:end);
subplot(3,2,3), imshow(I1), title('UpperLeft')
subplot(3,2,4), imshow(I2), title('UpperRight')
subplot(3,2,5), imshow(I3), title('LowerLeft')
subplot(3,2,6), imshow(I4), title('LowerRight')
