bool Discontinuity ( double prev, double trend, double current )
{
    double max_expected, min_expected;
    
    if (trend >= 0)
    {
        max_expected = prev + 2 * trend;
        min_expected = prev - 0.1;
    }
    
    else
    {
        max_expected = prev + 0.1;
        min_expected = prev + 2 * trend;
    }
    
    if (current > max_expected || current < min_expected) return true;
    
    else return false;
}
