function [A, B, C] = getEquationOfStateParameters2(m_w, m_p, r_w, r_p, J_w, J_p, J_m, g, n, kt, kn, R)
    
    ke = 1 / (kn * 2*pi / 60); %起電力定数 [V/rpm]

    a11 = (m_w + m_p) * r_w^2 + 2 * m_p * r_w * r_p + m_p * r_p^2 + J_p + J_w;
    a12 = (m_w + m_p) * r_w^2 + m_p * r_w * r_p + J_w;
    a21 = 1;
    a22 = 1;
    delta = a11 * a22 - a12 * a21;
    

    A = [0, 1;
         a22 * m_p * g * r_p / delta, 0];
    
    B = [0;
         (-a12 * n * kt / R) / delta];
    
    C = [1, 1];

end