% コード生成できない（lqrは対応していないらしい）

function [f] = calcStateFeedbackGain(A, B, Q, R)
    gain = lqr(A, B, Q, R);
    f = gain;
end