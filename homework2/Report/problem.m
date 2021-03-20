% read image and convert to grayscale
im = imread('lena.tif');
im(:,:,4) = [];
grayIm = rgb2gray(im);

for  windowSz = 3:2:7
    for sigma = 0.1:0.2:0.5
        for threshold = 0:10:40
            h_filter = Laplacian_mask(windowSz,sigma);
            grayIm2 = filter2(h_filter,grayIm);
            [Gmag,Gdir] = Gradient_magnitude(grayIm2);
            resIm = Zero_crossing(Gmag,Gdir,threshold);
            imwrite(resIm, "lena_" + windowSz + "_" + sigma + "_" + threshold + ".png");
        end
    end
end

% obtain gradient magnitude
function [Gmag,Gdir] = Gradient_magnitude(im)
    [Gmag,Gdir] = imgradient(im,'prewitt');
end

% returns a rotationally symmetric Gaussian lowpass filter
function h = Laplacian_mask(hsize,sigma)
    h = fspecial('gaussian',hsize,sigma);
end

function im = Zero_crossing(Gmag,Gdir,threshold)
    dir = [-1,0 ; 1 0 ; 0 1; 1 0];
    [sz1,sz2] = size(Gmag);
    im = zeros(sz1, sz2);
    for i = 1:sz1
        for j = 1:sz2
            cnt1 = 0; % the number of point has difference > threshold
            cnt2 = 0; % the number of point show different sign with (i,j)
            for k = 1:4
               x = i + dir(k,1);
               y = j + dir(k,2); 
               % test if (x,y) is out of boundary
               if x < 1 || x > sz1 || y < 1 || y > sz2
                   continue
               end
               if abs(Gmag(i,j) - Gmag(x,y)) > threshold
                  cnt1 = cnt1 + 1 ;
               end
               if Gdir(i,j) * Gdir(x,y) < 0
                  cnt2 = cnt2 + 1 ;
               end
            end
            if cnt1 >= 1 && cnt2 >= 2
                im(i,j) = 1;
            end
        end
    end
end