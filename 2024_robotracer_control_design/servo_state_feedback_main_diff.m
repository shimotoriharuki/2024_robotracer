clear
clc

%設計上のパラメータ
m_w= 33e-3; % ホイールの重さ [kg]
m_p= 201e-3; % 振子の重さ [kg]
r_w= 33e-3; % ホイールの半径 [m]
r_p= 70e-3; % 振子の重心までの距離 [m]
J_w= 7.239e-6; % ホイールのイナーシャ[kg m^2]
J_p= 0.826e-3; % 振子のイナーシャの半分[kg m^2]
J_m= 1.51e-8; % モータの回転子のイナーシャ[kg m^2]
g= 9.8; % 重力加速度 [m/s^2]
n= 6; % 減速比
kt= 3.52e-3; %トルク定数 [Nm/A]
kn= 2710; % 回転数定数[rpm/V] 2710
ke= 1 / (kn* 2*pi / 60); %起電力定数 [V/(rad/s)]
R= 2.9; %内部抵抗 [Ω]
t_md = 0; % 摩擦トルク[Nm]
V_offset = R * t_md / kt;

%実機のパラメータ
m_w_actual = 33e-3; % ホイールの重さ [kg]
m_p_actual = 201e-3; % 振子の重さ [kg]
r_w_actual = 33e-3; % ホイールの半径 [m]
r_p_actual = 70e-3; % 振子の重心までの距離 [m]
J_w_actual = 7.239e-6; % ホイールのイナーシャ[kg m^2]
J_p_actual = 0.826e-3; % 振子のイナーシャの半分[kg m^2]
J_m_actual = 1.51e-8; % モータの回転子のイナーシャ[kg m^2]
g_actual = 9.8; % 重力加速度 [m/s^2]
n_actual = 6; % 減速比
kt_actual = 3.52e-3; %トルク定数 [Nm/A]
kn_actual = 2710; % 回転数定数[rpm/V]
ke_actual = 1 / (kn* 2*pi / 60); %起電力定数 [V/(rad/s)]
R_diff = 2.9; %内部抵抗 [Ω]
t_md_actual  = 1.1; % 摩擦トルク[Nm]
V_offset_actual  = R * t_md_actual / kt_actual;

% a11 = (m_w + m_p) * r_w^2 + 2 * m_p * r_w * r_p + m_p * r_p^2 + J_p + J_w;
% a12 = (m_w + m_p) * r_w^2 + m_p * r_w * r_p + J_w;
% a21 = (m_w + m_p) * r_w^2 + m_p * r_w * r_p + J_w;
% a22 = (m_w + m_p) * r_w^2 + J_w + n^2 * J_m;
% delta = a11 * a22 - a12 * a21;
% 
% A = [0, 1, 0, 0;
%      a22 * m_p * g * r_p / delta, 0, 0, (a21 * n^2 * kt * ke / R)/delta;
%      0, 0, 0, 1;
%      -a21 * m_p * g * r_p / delta, 0, 0, (-a11 * n^2 * kt * ke /R) / delta];
% 
% B = [0;
%      (-a12 * n * kt / R) / delta;
%      0;
%      (a11 * n * kt / R) / delta];
% 
% C = [1, 1, 1, 1];

[Ab, Bb, C] = getServoEquationOfStateParameters(m_w, m_p, r_w, r_p, J_w, J_p, J_m, g, n, kt, kn, R);
[Ab_actual, Bb_actual, C_actual] = getServoEquationOfStateParameters(m_w_actual, m_p_actual, r_w_actual, r_p_actual, J_w_actual, J_p_actual, J_m_actual, g_actual, n_actual, kt_actual, kn_actual, R_diff);

%可制御
Uc = [Bb, Ab*Bb, Ab^2*Bb, Ab^3*Bb, Ab^4*Bb];
if det(Uc) ~= 0
    disp('可制御である')
end

%状態フィードバック
Q = [0.01, 0, 0, 0, 0;
     0, 0.01, 0, 0, 0;
     0, 0, 0.05, 0, 0;
     0, 0, 0, 0.05, 0;
     0, 0, 0, 0, 0.01];
R = 8;
% gain = lqr(Ab, Bb, Q, R);
% f = gain(1:4);
% k = -gain(5);

[f, k] = calcServoStateFeedbackGain(Ab, Bb, Q, R);
disp(f)
disp(k)

%シミュレーション
dt = 0.001;
t = 0 : dt : 10;
xb0 = [0.01; 0; 0; 0]; % 初期値
z = 0; % 偏差の積分
v = [0; 0; 0; 0]; % 外乱
target_theta = 0; % 目標角度 [rad]
target_omega = 0; %目標角速度[rad/s]

u = 0; % 入力の初期値
xb = xb0;

s_x1 = []; %theta_p
s_x2 = []; %dtheta_p
s_x3 = []; %theta_w
s_x4 = []; %dtheta_w
s_z = [];
s_u = [];

pre_input = u;
pre_target_theta = 0;
pre_xb = xb0;
pre_z = z;

for i = t
    input =  servoStateFeedback(xb, z, f, k);

    target_theta = pre_target_theta + target_omega * dt;
    dxb = Ab_actual * [pre_xb; pre_z] + Bb_actual * pre_input + [v; target_theta];
    xb = pre_xb + dxb(1:4, 1) * dt;
    z = pre_z + dxb(5) * dt;

    pre_input = input - V_offset_actual;
    pre_target_theta = target_theta;
    pre_xb = xb;
    pre_z = z;
    
    s_x1 = [s_x1 xb(1)];
    s_x2 = [s_x2 xb(2)];
    s_x3 = [s_x3 xb(3)];
    s_x4 = [s_x4 xb(4)];
    s_z = [s_z z];
    s_u = [s_u input];
end

figure(1)
subplot(2, 2, 1)
plot(t, s_x1);
% legend('theta_p')
title('theta_p')

subplot(2, 2, 3)
plot(t, s_x2);
% legend('dtheta_p')
title('dtheta_p')

subplot(2, 2, 2)
plot(t, s_x3);
% legend('theta_w')
title('theta_w')

subplot(2, 2, 4)
plot(t, s_x4);
% legend('dtheta_w')
title('dtheta_w')

figure(2)
plot(t, s_z);
% legend('z')
title('z')

figure(3)
plot(t, s_u);
% legend('u')
title('u')

writematrix(f, 'servo_gain');