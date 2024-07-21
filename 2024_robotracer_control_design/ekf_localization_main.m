clc;
clear;                                  % 変数の初期化
clf;                                    % グラフの初期化

dt = 0.01;                              % サンプリングタイム

xt = [0,0,0]';                          % ロボットの位置と方位(rad)r
mu_t = [0,0,0]';                        % 推定した位置(m)，方位(rad)の平均値
Sigma_t = [0.005^2,0,0; 0,0.005^2,0; 0,0,0.05^2];	% 共分散行列
ut = [1,1];                             % 目標速度(m/s)と角速度(rad/s)
zt = [];                                % 計測
ct = [1];                               % 対応変数
m = [1.1,1];                            % ランドマークの位置
t = 0:dt:2;                             % 0.01s毎に0sから2sまで計算
i = 0;
%%mu_t1 = [0,0,0];

for n = t
  i = i + 1;

  % ロボットの軌道の計算
  vt = ut(1);                           % ロボットの速度
  wt = ut(2);                           % ロボットの角速度
  theta = xt(3);
  vtt = 1 * vt;                         % ロボットの位置（係数を変更して挙動を確認）
  wtt = 1.05 * wt;                      % ロボットの方位（係数を変更して挙動を確認）
  dxt = [-vtt/wtt*sin(theta)+vtt/wtt*sin(theta+wtt*dt), vtt/wtt*cos(theta)-vtt/wtt*cos(theta+wtt*dt), wtt*dt]';
  xt = xt + dxt;
  rx(i) = xt(1);
  ry(i) = xt(2);

  % カルマンフィルタ
  mu_t1 = mu_t;                         % 位置と方位の平均値
  Sigma_t1 = Sigma_t;                   % 共分散行列
  z = m - [xt(1), xt(2)];               % ランドマークの相対距離(x,y)
  zt = [sqrt(z(1)^2+z(2)^2), atan2(z(2), z(1)) - xt(3), 0]';    % ランドマークマークの距離，方位
  if (zt(1) > 0.3)
    zt = [];
  end
  [mu_t, Sigma_t, pzt]=ekf_localization(mu_t1, Sigma_t1, ut, zt, ct, m);    % 拡張カルマンフィルタ

  % カルマンフィルタの計算結果表示用
  mu_t_x    (i) = mu_t(1);              % x座標の平均値
  mu_t_y    (i) = mu_t(2);              % y座標の平均値
  mu_t_theta(i) = mu_t(3);              % 角度(rad)の平均値

  chi = 5.99;
  Sigma_t_x = Sigma_t(1,1);             % 共分散行列のx方向の値
  Sigma_t_y = Sigma_t(2,2);             % 共分散行列のy方向の値
  Sigma_t_xy = Sigma_t(1,2);            % 共分散行列のxy方向の値
  Sigma_t_u(i) = sqrt((Sigma_t_x+Sigma_t_y+sqrt((Sigma_t_x-Sigma_t_y)^2+4*Sigma_t_xy^2))/2*chi);    % 楕円体の長軸
  Sigma_t_v(i) = sqrt((Sigma_t_x+Sigma_t_y-sqrt((Sigma_t_x-Sigma_t_y)^2+4*Sigma_t_xy^2))/2*chi);    % 楕円体の短軸
  Sigma_t_t(i) = atan2((Sigma_t_u(i)^2 - Sigma_t_x*chi), Sigma_t_xy*chi);                                   % 楕円体の角度

end

plot(mu_t_x, mu_t_y);                   % 軌跡の表示
axis([-0.5,1.5,-0.5,1.5],"square");     % 座標系の表示
hold on;                                % この表示を保持したまま追加
plot(rx, ry,'r');                       % 軌跡の表示
for n = 1:10:i
  ellipse(mu_t_x(n), mu_t_y(n), Sigma_t_u(n), Sigma_t_v(n), Sigma_t_t(n));    % 楕円体の表示
end
ellipse(m(1), m(2), 0.05, 0.05, 0);     % ランドマークの表示
hold off;
