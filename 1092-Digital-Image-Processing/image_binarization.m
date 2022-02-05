im = imread('lena.tif');
im = imbinarize(im);
se = strel('line',3,45);
im2 = (imdilate(im,se));
figure, imshow(im2);