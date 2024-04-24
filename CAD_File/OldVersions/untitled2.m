array = randi([0, 255], 100, 100);
normalized_array = double(array) / 255.0;
imshow(normalized_array, 'Colormap', gray);