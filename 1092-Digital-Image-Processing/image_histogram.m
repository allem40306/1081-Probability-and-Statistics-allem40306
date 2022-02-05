im = imread('lena.tif');
im(:,:,4) = [];
im = rgb2gray(im);
im2 = histeq(im);

figure, imshow(im);
figure, imshow(im2);
figure, imhist(im,64);
figure, imhist(im2,64);