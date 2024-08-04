function [Ab, Bb, C] = getServoEquationOfStateParameters(m_w, m_p, r_w, r_p, J_w, J_p, J_m, g, n, kt, kn, R)
    
    ke = 1 / (kn * 2*pi / 60); %起電力定数 [V/rpm]

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
    
    C = [1, 1, 1, 1];

    % 拡大系
    Ab = [A, zeros(4, 1);
          -C, 0];
    Bb = [B; 0];

end