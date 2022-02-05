clear;
%B = imread('cardiacMRI.tiff');
%Bim= imread('cardiacMRI.tiff');
B = imread('BladderSono.bmp');
Bim= imread('BladderSono.bmp');
B=B(:,:,1:1);

%basic setting
offsets = [0 1];
numlevels=8;
windowsize=3;
[row,col] = size(B);

%window matrix
wm=zeros(windowsize,windowsize);
contrast=zeros(row,col);
energy=zeros(row,col);
correlation=zeros(row,col);
homogeneity=zeros(row,col);
entropy=zeros(row,col);
variance=zeros(row,col);

%create texture map
for i=1:row
    if i + windowsize > row
        break;
    end
    for j = 1:col
        if j + windowsize > col
            break;
        end
        n = i;
        for k = 1:windowsize
            if n + k - 1 > row
                break;
            end
            n = n + k - 1;
            m = j;
            for l = 1:windowsize
                wm(k,l) = B(n,m);
                if m + l > col
                    break;
                end
                m = m + 1;
                
            end
        end
        x = i + (windowsize - 1) / 2;
        y = j + (windowsize - 1) / 2;
        GLCM2 = graycomatrix(wm,'GrayLimits',[],'NumLevels',numlevels,'Offset',offsets);
        stats = GLCM_Features(GLCM2);
        contrast(x,y)=stats.contr;
        energy(x,y)=stats.energ;
        homogeneity(x,y)=stats.homop;
        correlation(x,y)=stats.corrp;
        entropy(x,y)=stats.entro;
        variance(x,y)=stats.svarh;
    end
end

%display texture map
%figure,
%subplot(1,4,1),    imshow(B),title('Original Image');
%subplot(1,4,2),imshow(contrast),title('Contrast');
%subplot(1,4,3),imshow(energy),title('Energy');
%subplot(1,4,4),imshow(correlation),title('Correlation');
%figure,
%subplot(1,4,1),imshow(homogeneity),title('Homogeneity');
%subplot(1,3,2),imshow(mean),title('Mean');
%subplot(1,4,2),imshow(variance),title('Variance');
%subplot(1,4,3),imshow(entropy),title('Entropy');

%texture map only
tm(:,:,1)=contrast;
tm(:,:,2)=energy;
tm(:,:,3)=homogeneity;
tm(:,:,4)=correlation;
tm(:,:,5)=entropy;
tm(:,:,6)=variance;

tm=uint8(tm);

%texture map cover on image
imc(:,:,1)=Bim(:,:,1);
imc(:,:,2)=Bim(:,:,2);
imc(:,:,3)=Bim(:,:,3);
imc(:,:,4)=contrast;
imc(:,:,5)=energy;
imc(:,:,6)=correlation;
imc(:,:,7)=homogeneity;
imc(:,:,8)=entropy;
imc(:,:,9)=variance;

%display kmeans
kmeans_segment(5,B);
kmeans_segment(5,tm);
kmeans_segment(5,imc);