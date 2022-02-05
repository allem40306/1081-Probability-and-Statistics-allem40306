im1 = imread('lena.tif');
im2 = imread('blurry-moon.tif');

histogram_equalization(im1);
homomorphic(im1);

histogram_equalization(im2);
homomorphic(im2);

function histogram_equalization(im)
    his = histeq(im);
    figure,imshow(im);
    figure,imhist(his,64);
end

function homomorphic(im)
    im = im2double(im);
    [m,n] = size(im);
    z = log(im+0.01);
    Z = fft2(z);
    H = ILPF(m,n,1.2);
    S = H.*Z;
    s = ifft2(S);
    g = exp(s);
    figure,imshow(g);
    figure,imhist(g,64);
end

function H = ILPF(m,n, D0)
    % Ideal Lowpass Filters [0.6,1.2]
    [f1,f2] = freqspace([m,n],'meshgrid');
    D = sqrt(f1.^2 + f2.^2);
    H = double(D<=D0);
    %figure, imshow(H);
end
