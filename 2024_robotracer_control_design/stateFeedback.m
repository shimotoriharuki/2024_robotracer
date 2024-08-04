function [input, target_theta, x] = stateFeedback(dt, target_omega, A, B, pre_target_theta, pre_x, pre_input, f)

    %状態フィードバック
    target_theta = pre_target_theta + target_omega * dt;
    dx = A * pre_x + B * pre_input;
    x = pre_x + dx * dt;
    input = -f*x;

end