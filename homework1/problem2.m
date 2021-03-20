I = imread('cat.jpg'); %% read picute
grayI = rgb2gray(I); %% to grayscale 
imwrite(grayI,'grayCat.jpg');

grayI = imread('grayCat.jpg'); 

S = ["nearest","bilinear","bicubic"]; % test method

for i = 1:3
    plotno = i;
    grayI2 = grayI;
    for j = 1:10
        for N = 1:j %% shrink the size of the image by two 6 times (recognize limit)
            grayI2 = imresize(grayI2,0.5, S(i));
        end

        for N = 1:j %% shrinking imagesback to its originalsize
            grayI2 = imresize(grayI2,2);
        end 
    
        % figure, imshow(grayI2)
        subplot(10, 3, plotno), imshow(grayI2), title(S(i) + j);
        plotno = plotno + 3;
        imwrite(grayI2,"grayCat"+ i + "_" + j + ".jpg");

    end
end


