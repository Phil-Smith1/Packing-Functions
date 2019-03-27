void Derivatives_At_Pt ( double x1, double x3, double y1, double y2, double y3, double& first_deriv, double& second_deriv )
{
    double dx = x3 - x1, dy = y3 - y1;
    
    first_deriv = dy / (double)dx;
    
    double dx2 = (x3 - x1) * (x3 - x1) * 0.25, dy2 = y3 - 2 * y2 + y1;
    
    second_deriv = dy2 / (double)dx2;
}
