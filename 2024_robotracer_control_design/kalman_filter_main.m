clear

%パラメータ
dt = 0.01;

init_P = [1*pi/180, 0; 0, 1e-2];
pre_P = init_P;

init_theta = 0;
pre_theta = init_theta;

for i = 1:100
    [theta, P] = kalmanFilter(dt, 0.001, pre_P, pre_theta, 1e-2, 1e-2, 0.01, 0.01)

    pre_P = P;
    pre_theta = theta;
end
