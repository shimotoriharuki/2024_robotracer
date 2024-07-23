clear
clc

omega_data = load("sensor_data\robot_omega_x1.txt");
theta_data = load("sensor_data\robot_theta_from_acc1.txt");

%パラメータ
dt = 0.001;

init_P = [1*pi/180, 0;
          0, 6.3e-06];
pre_P = init_P;

init_theta = 0;
pre_theta = init_theta;

U = 6.3e-06;
W = 2.2e-05;

data_size = length(omega_data);
store_theta = zeros(1, data_size);
for i = 1 : data_size
    [theta, P] = kalmanFilter(dt, 0, pre_P, pre_theta, U, W, omega_data(i), theta_data(i));

    pre_P = P;
    pre_theta = theta;

    store_theta(i) = theta;
end
