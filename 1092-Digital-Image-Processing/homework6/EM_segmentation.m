function [idx] = EM_segmentation(I_arr,k,mu,sigma)
%% clustering using GMM via EM algorithm
% Input:
% % I_arr: vectorized image array
% % k: the number of clusters
% Output:
% % idx: clustering result array
%% Multivariate Gaussian Mixture Model (GMM) Estimation
if nargin == 2
    mu = mean(I_arr);
    sigma = std(I_arr);
elseif naragin == 3
    error('Not enough input arguments.')
end
P = mvnpdf(I_arr, mu, sigma); % multivariate Gaussian pdf

options = statset('Display','final','MaxIter',500);
gm = fitgmdist(P,k,'Options',options); % model fitting

%% Clustering based on the estimated GMM
idx = cluster(gm,P);

end