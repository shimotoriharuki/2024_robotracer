f5 = figure(1);
clf (f5, "reset")
clc
clear



% ---データをロード---
theta_p = load('workingDirectory/theta_p.txt');
dtheta_p = load('workingDirectory/dtheta_p.txt');
theta_w = load('workingDirectory/theta_w.txt');
dtheta_w = load('workingDirectory/dtheta_w.txt');


% --- データが有るところだけ抽出---
data_size = length(nonzeros(theta_p));

theta_p = theta_p(1 : data_size);
dtheta_p = dtheta_p(1 : data_size); 
theta_w = theta_w(1 : data_size);
dtheta_w = dtheta_w(1 : data_size);



% ---プロット---
t = linspace(0, data_size, data_size);
t = t .* 10; %msに変換

figure(5);
tiledlayout(2, 2);

nexttile
plot(t, theta_p);
title("theta_p")

nexttile
plot(t, dtheta_p);
title("dtheta_p")

nexttile
plot(t, theta_w);
title("theta_w")

nexttile
plot(t, dtheta_w);
title("dtheta_w")
