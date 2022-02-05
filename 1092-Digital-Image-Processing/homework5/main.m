% clear all;close all;clc
im=imread('lena.tif');
% gray=rgb2gray(im);
imagBW = kapur(im);
imshow(im)
figure;imshow(im)
[K] = otsu(gray); 
BW=im2bw(im,K/255);
imagBW = kapur(im);

%subplot(121)
figure, imshow(BW)
title('Otsu Threshold')
%subplot(122)
figure, imshow(imagBW)
title('Kapur Threshold')

imwrite(im, 'lena.jpg');
imwrite(imagBW, 'kabur.jpg');
