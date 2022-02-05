% % image segmentation using k-means
function [] = kmeans_segment(k,I)
%k = 3; % the number of clusters to be assigned

% % input image
% I = imread('ngc6543a.jpg');
%I = imread('coins.png');
% I = imread('cardiacMRI example.tiff');
% % you can replace the image here with the texture map that we generated in
% % previous exercise

% % initialize
[row,col,channel] = size(I);
I_arr = reshape(im2double(I),row*col,channel); % vectorize the image matrix

nonzero = all(I_arr~=0,2); % exclude zero points to remove redundant

%% clustering
% % using angle for calculating similarity. (This is particularly useful
% % while using feature map for clustering
% [idx1] = kmeans(I_arr(nonzero),k,'Distance','cosine'); 
% % using distance for calculating similarity
[idx1,C] = kmeans(I_arr(nonzero),k);

% % you can try to segment image array by assuming Gaussian Mixture Model via
% % EM algorithm.
% Estimate the initials using sample mean and sample variance
[idx_GMM] = EM_segmentation(I_arr,k);
% 
% initialize by given mean and varance
% [idx_GMM] = EM_segmentation(I_arr,k,C,sumd);


%%
label_kmeans = zeros(row*col,1);
label_kmeans(nonzero) = idx1; % place clustering result back


% % make segmentation result a color image
I_seg_kmeans = label2rgb(reshape(label_kmeans,row,col),'parula','k');
I_seg_GMM = label2rgb(reshape(idx_GMM,row,col),'parula','k');


% % display result
figure, montage({I(:,:,1:1),I_seg_kmeans,I_seg_GMM})