void println(int a)
{
    printf("%d\n", a);
}
int f(int a)
{
    println(a);
    return 7 > 2;
}
int main()
{
    int a, b[10], c, d;
    a = 7 > 2;
    println(a);
    a = (7 > 2);
    println(a);
    a = 7 - (7 > 2);
    println(a);
    a = (7 > 2) + 7;
    println(a);
    a = (7 > 2) + (7 > 2);
    println(a);
    a = 7 * (7 > 2);
    println(a);
    a = (7 > 2) % 7;
    println(a);
    a = (7 > 2) * (7 > 2);
    println(a);
    a = 7 && 2;
    println(a);
    a = (7 || 2);
    println(a);
    a = 7 + (7 && 2);
    println(a);
    a = (7 || 2) + 7;
    println(a);
    a = (7 && 2) + (7 || 2);
    println(a);
    a = f(7 > 2);
    println(a);
    if (0 && (7 || 2))
    {
        a = 10;
        println(a);
    }
    else if (7)
    {
        a = 11;
        println(a);
    }
    else if (7 + (7 > 2))
    {
        a = 12;
        println(a);
    }
    b[7 > 2] = 10;
    a = b[7 > 6];
    println(a);
    a = -(7 > 2);
    println(a);
    7 > 2;
    return 7 && 2;
}