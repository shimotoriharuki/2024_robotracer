% 楕円を描画する関数
% 中心座標(x,y), 半径(u,v), 傾き theta (rad)

function ellipse(x, y, u, v, theta)
t = linspace(0, 2*pi, 20);
xt = u * cos(t);
yt = v * sin(t);
theta
xtr = cos(theta) * xt - sin(theta) * yt + x;
ytr = sin(theta) * xt + cos(theta) * yt + y;
plot(xtr, ytr);
end
