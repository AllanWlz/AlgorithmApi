str='H:\DATA\waveform\非零积分信号输出\0.8_output\x_2_output'
fileRead = fopen(str,'rb');
A = fread(fileRead,[3,2000000],'float');
loc_v = zeros(25,25);
loc_m = zeros(25,25);
num = zeros(25,25);
%%
for i = 1 : length(A)
    x = A(1,i);
    y = A(2,i);
    var = (y - A(3,i))^2;
    mean = y - A(3,i);
    loc_v(x-2,y-2) = loc_v(x-2,y-2) + var;
    loc_m(x-2,y-2) = loc_m(x-2,y-2) + mean;
    num(x-2,y-2) = num(x-2,y-2) + 1;
end
%%
loc_v = loc_v ./ num;
loc_m = loc_m ./ num;
loc_v(isnan(loc_v)) = 0;
loc_m(isnan(loc_m)) = 0;
for i = 1 : 25
    for j = 1 : 25
        if loc_v(i,j) == 0
            loc_v(i,j) = (loc_v(i,j - 1) + loc_v(i,j + 1)) / 2;
            loc_m(i,j) = (loc_m(i,j - 1) + loc_m(i,j + 1)) / 2;
        end
    end
end
loc_v = loc_v .^ 0.5;
%%
[x,y]=meshgrid(1:1:25);
surf(x,y,loc_v)
surf(x,y,loc_m)