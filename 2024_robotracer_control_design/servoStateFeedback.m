function input = servoStateFeedback(xb, z, f, k)

    %状態フィードバック 
    input = -f*xb + k*z;

end