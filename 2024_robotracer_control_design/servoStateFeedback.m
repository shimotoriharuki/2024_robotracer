function [input, target_theta, xb, z] = servoStateFeedback(dt, target_omega, Ab, Bb, pre_target_theta, pre_xb, pre_z, pre_input, disturbance, f, k)


    %状態フィードバック
    target_theta = pre_target_theta + target_omega * dt;
    dxb = Ab * [pre_xb; pre_z] + Bb * pre_input + [disturbance; target_theta];
    xb = pre_xb + dxb(1:4, 1) * dt;
    z = pre_z + dxb(5) * dt;
    input = -f*xb + k*z;

end