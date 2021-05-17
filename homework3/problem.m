im = imread('lena.tif');
im(:,:,4) = [];
im = rgb2gray(im);
[m,n] = size(im);

F = fft2(im);

for i = 0.2:0.2:1.4
    H = ILPF(m, i);
    Fout = F .* H;
    im2 = ifft2(Fout);
    %figure, imshow(im2); 
    imwrite(im2, "ILPF" + i + ".jpg");
end
 
for i = -0.5:0.1:0.5
    H = GLPF(m, i);
    Fout = F .* H;
    im2 = ifft2(Fout);
    %figure, imshow(im2); 
    imwrite(im2, "GLPF" + i + ".jpg");
end

for i = 0:10:50
    H = BLPF(m, i);
    Fout = F .* H;
    im2 = ifft2(Fout);
    %figure, imshow(im2); 
    imwrite(im2, "BLPF" + i + ".jpg");
end

function H = ILPF(Isize, D0)
    % Ideal Lowpass Filters [0.6,1.2]
    [f1,f2] = freqspace(Isize,'meshgrid');
    D = sqrt(f1.^2 + f2.^2);
    H = double(D<=D0);
    %figure, imshow(H);
end

function H = GLPF(Isize, D0)
    %        [-0.3,0.3]
    [f1,f2] = freqspace(Isize,'meshgrid');
    D = sqrt(f1.^2 + f2.^2);
    H = exp(-(D.^2)./(2*(D0^2)));
    %figure, imshow(H); 
end

function H = BLPF(Isize, D0)
    % Butterworth Lowpass Filters [10,30]
    [f1,f2] = freqspace(Isize,'meshgrid');
    D = sqrt(f1.^2 + f2.^2);
    H = 1./(1+(D0./D).^2); % n = 1
    %figure, imshow(H);
end
