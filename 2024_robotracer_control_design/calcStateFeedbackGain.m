% コード生成できない（lqrは対応していないらしい）

function [f, k] = calcStateFeedbackGain(Ab, Bb, Q, R)
    gain = lqr(Ab, Bb, Q, R);
    f = gain(1:4);
    k = -gain(5);
end