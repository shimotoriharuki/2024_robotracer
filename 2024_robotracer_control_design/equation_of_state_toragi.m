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

a11 = (m_w + m_p) * r_w^2 + 2 * m_p * r_w * r_p + m_p * r_p^2 + J_p + J_w;
a12 = (m_w + m_p) * r_w^2 + m_p * r_w * r_p + J_w;
a21 = (m_w + m_p) * r_w^2 + m_p * r_w * r_p + J_w;
a22 = (m_w + m_p) * r_w^2 + J_w + n^2 * J_m;
delta = a11 * a22 - a12 * a21;

A = [0, 1, 0, 0;
     a22 * m_p * g * r_p / delta, 0, 0, (a21 * n^2 * kt * ke / R)/delta;
     0, 0, 0, 1;
     -a21 * m_p * g * r_p / delta, 0, 0, (-a11 * n^2 * kt * ke /R) / delta];

B = [0;
     (-a12 * n * kt / R) / delta;
     0;
     (a11 * n * kt / R) / delta];

C = [1, 0, 0, 0;
     0, 1, 0, 0;
     0, 0, 1, 0;
     0, 0, 0, 1];

% 可制御
Uc = [B, A*B, A^2*B, A^3*B];
if det(Uc) ~= 0
    disp('可制御である')
end

%シミュレーション
dt = 0.001;
t = 0 : dt : 0.1;
i = 0;
x = [0.1; 0; 0; 0];
u = 1;
x1 = []; %theta_p
x2 = []; %dtheta_p
x3 = []; %theta_w
x4 = []; %dtheta_w
for n = t
    i = i + 1;
    dx = A * x + B * u;
    x = x + dx * dt;
    
    x1 = [x1, x(1)];
    x2 = [x2, x(2)];
    x3 = [x3, x(3)];
    x4 = [x4, x(4)];
end

subplot(2, 2, 1)
plot(t, x1);
legend('theta_p')
title('状態方程式のシミュレーション')

subplot(2, 2, 2)
plot(t, x2);
legend('dtheta_p')
title('状態方程式のシミュレーション')

subplot(2, 2, 3)
plot(t, x3);
legend('theta_w')
title('状態方程式のシミュレーション')

subplot(2, 2, 4)
plot(t, x4);
legend('dtheta_w')
title('状態方程式のシミュレーション')