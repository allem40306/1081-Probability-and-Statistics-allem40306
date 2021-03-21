%% Marr-Hildreth edge detector example

im = im2double(imread('lena.tif')); % load image and convert to double

h_filter = create_mask(h_size,sigma); % filter design; LoG with the filter size and sigma
g = perform_filter(im,h_filter); % g(x,y) dervied by applying LoG


% apply different thresholds to get the edges

threshold1 = 0;
edge1 = zero_crossing(g, threshold1);

threshold2 = max(abs(g(:))) * 0.1; % set the threshold to 10% of maximal value of the g(x,y)
edge2 = zero_crossing(g, threshold2); 
