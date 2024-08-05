clear
clc

%パラメータ
m_w= 33e-3; % ホイールの重さ [kg]
m_p= 193e-3; % 振子の重さ [kg]
r_w= 33e-3; % ホイールの半径 [m]
r_p= 70e-3; % 振子の重心までの距離 [m]
J_w= 0.477e-4; % ホイールのイナーシャ
J_p= 6.498e-4; % 振子のイナーシャ ??
J_m= 0.151e-7; % モータの回転子のイナーシャ
g= 9.8; % 重力加速度 [m/s^2]
n= 3; % 減速比
kt= 3.52e-3; %トルク定数 [Nm/A]
kn= 2710; % 回転数定数[rpm/V]
ke= 1 / (kn* 2*pi / 60); %起電力定数 [V/(rad/s)]
R= 2.9; %内部抵抗 [Ω]
t_md = 0; % 摩擦トルク[Nm]
V_offset = R * t_md / kt;

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

[A, B, C] = getEquationOfStateParameters(m_w, m_p, r_w, r_p, J_w, J_p, J_m, g, n, kt, kn, R);

%可制御
Uc = [B, A*B, A^2*B, A^3*B];
if det(Uc) ~= 0
    disp('可制御である')
end

%状態フィードバック
Q = [0.01, 0, 0, 0;
     0, 0.01, 0, 0;
     0, 0, 0.05, 0;
     0, 0, 0, 0.05];
R = 5;

f = calcStateFeedbackGain(A, B, Q, R);

%シミュレーション
dt = 0.001;
t = 0 : dt : 10;
x0 = [0.1; 0; 0; 0]; % 初期値
z = 0; % 偏差の積分
target_theta = 0; % 目標角度 [rad]
target_omega = 0; %目標角速度[rad/s]

u = 0; % 入力の初期値
x = x0;

s_x1 = []; %theta_p
s_x2 = []; %dtheta_p
s_x3 = []; %theta_w
s_x4 = []; %dtheta_w
s_u = [];

pre_input = u;
pre_target_theta = 0;
pre_x = x0;

for i = t
    input =  stateFeedback(x, f);

    dx = A * pre_x + B * pre_input;
    x = pre_x + dx * dt;

    pre_input = input;
    pre_x = x;
    
    s_x1 = [s_x1 x(1)];
    s_x2 = [s_x2 x(2)];
    s_x3 = [s_x3 x(3)];
    s_x4 = [s_x4 x(4)];
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
plot(t, s_u);
% legend('u')
title('u')

writematrix(f, 'gain');