function [input] = stateFeedback(x, f)

    %状態フィードバック

    input = -f*x;

end