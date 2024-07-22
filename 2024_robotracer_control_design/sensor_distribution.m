omega_data = load("sensor_data\robot_omega_x1.txt");
theta_data = load("sensor_data\robot_theta_from_acc1.txt");

subplot(2, 1, 1)
histogram(omega_data);

subplot(2, 1, 2)
histogram(theta_data);

var(omega_data) %角速度の分散
var(theta_data) %角度の分散