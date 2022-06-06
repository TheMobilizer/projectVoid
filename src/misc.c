float map(float value, float lower_dom1, float upper_dom1, float lower_dom2, float upper_dom2)
{
    float range_dom1 = upper_dom1 - lower_dom1;
    float range_dom2 = upper_dom2 - lower_dom2;
    return (((value/range_dom1)*range_dom2) + lower_dom2);
}
