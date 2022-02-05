im = imread('lena.tif');

for i = 1:8
    im2 = bitPlane(im,i);
    %figure, imshow(im2);
    imwrite(im2, "lena" + i + ".jpg");
end

function im2 = bitPlane(im,bit)
    [d1,d2] = size(im);
    im2 = zeros(d1,d2);
    for i = 1:d1
        for j = 1:d2
            im2(i,j) = bitget(im(i,j),bit) * (2 .^ bit);
        end
    end
end
