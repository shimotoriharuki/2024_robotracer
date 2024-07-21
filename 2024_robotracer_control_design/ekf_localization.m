% EKF_localization   Extended Kalman Filter for localization

function [mu_t, Sigma_t, pzt]=ekf_localization(mu_t1, Sigma_t1, ut, zt, ct, m) % t1はt-1の意味

dt = 0.01;                              % サンプリングタイム
alpha = [0.01, 0.01, 0.01, 0.01];       % 分散の係数 オドメトリの雑音
sigma_r = 0.1;                          % ランドマークの距離の計測ノイズ
sigma_phai = 0.5;                       % ランドマークの方位の計測ノイズ
sigma_s = 0.1;                          % ランドマークの対応の計測ノイズ（今回は１個だけなので関係ない）

theta = mu_t1(3);                       % ロボットの方位
vt = ut(1);                             % 速度
wt = ut(2);                             % 角速度
Gt = [1, 0, (-vt/wt)*cos(theta) + (vt/wt)*cos(theta+wt*dt); 0, 1, (-vt/wt)*sin(theta) + (vt/wt)*sin(theta+wt*dt); 0, 0, 1];
Vt = [(-sin(theta)+sin(theta+wt*dt))/wt,  vt*(sin(theta)-sin(theta+wt*dt))/(wt^2)+vt*cos(theta+wt*dt)*dt/wt; ...
      ( cos(theta)-cos(theta+wt*dt))/wt, -vt*(cos(theta)-cos(theta+wt*dt))/(wt^2)+vt*sin(theta+wt*dt)*dt/wt; ...
      0, dt];
Mt = [alpha(1) * vt^2 + alpha(2) * wt^2, 0; ...
      0, alpha(3) * vt^2 + alpha(4) * wt^2];
mu_tb = mu_t1 + [(-vt/wt)*sin(theta) + (vt/wt)*sin(theta+wt*dt), (vt/wt)*cos(theta) - (vt/wt)*cos(theta+wt*dt), wt*dt]'; % /tbはt_barの意味
Sigma_tb = Gt*Sigma_t1*Gt' + Vt*Mt*Vt';
Qt = [sigma_r^2, 0, 0; 0, sigma_phai^2, 0; 0, 0, sigma_s^2];

if (not(isempty(zt)))
  % ランドマークまでの距離と方位を計算（理論値）
  q = (m(1)-mu_tb(1))^2+(m(2)-mu_tb(2))^2;
  zth = [sqrt(q), atan2(m(2)-mu_tb(2), m(1)-mu_tb(1)) - mu_tb(3), 0]';
  Ht = [-(m(1) - mu_tb(1)) / sqrt(q), -(m(2) - mu_tb(2)) / sqrt(q), 0; (m(2) - mu_tb(2)) / q, -(m(1) - mu_tb(1)) / q, -1; 0, 0, 0];
  St = Ht * Sigma_tb * Ht' + Qt;
  Kt = Sigma_tb * Ht' * St^-1;                               %カルマンゲインの計算
  % 計測更新ステップ
  mu_tb = mu_tb + Kt * (zt - zth);
  Sigma_tb = (eye(3) - Kt*Ht)*Sigma_tb; % １じゃなくて３ｘ３の単位行列だった
end

mu_t = mu_tb;
Sigma_t = Sigma_tb;
pzt = 0;

end
