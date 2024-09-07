function [estimated_robot_theta, P] = kalmanFilter(dt, omega_offset, pre_P, pre_theta, U, W, omega, theta)
    P = pre_P;
    theta_hat = [pre_theta; omega_offset];


    A_theta = [1, -dt;
               0, 1];
    B_theta = [dt;
               0];
    C_theta = [1, 0];

    %予測ステップ
    P_dash = A_theta * P * A_theta.' + B_theta * U * B_theta.';
    theta_tilde = A_theta * theta_hat + B_theta * omega;

    %更新ステップ
    G = P_dash * C_theta.' * (W + C_theta * P_dash * C_theta.')^(-1);
    P = (eye(2) - G * C_theta) * P_dash;
    theta_hat = theta_tilde + G * (theta - C_theta * theta_tilde);

    estimated_robot_theta = theta_hat(1);

end