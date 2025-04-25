int i, j;

int main1()
{
    int k, ll, m, n, o, p;

    i = 1;
    println(i);
    j = 5 + 8;
    println(j);
    k = i + 2 * j;
    println(k);

    m = k % 9;
    println(m);

    n = m <= ll;
    println(n);

    o = i != j;
    println(o);

    p = n || o;
    println(p);

    p = n && o;
    println(p);

    p++;
    println(p);

    k = -p;
    println(k);

    return 0;
}
int main2()
{
    int i, j, k;

    i = 3;
    j = 8;
    k = 6;

    if (i == 3)
    {
        println(j);
    }

    if (j < 8)
    {
        println(i);
    }
    else
    {
        println(k);
    }

    if (k != 6)
    {
        println(k);
    }
    else if (j > 8)
    {
        println(j);
    }
    else if (i < 5)
    {
        println(i);
    }
    else
    {
        k = 0;
        println(k);
    }

    return 0;
}

int main3()
{
    int i, j, k, ll;

    for (i = 0; i < 6; i++)
    {
        println(i);
    }

    k = 4;
    ll = 6;
    while (k > 0)
    {
        ll = ll + 3;
        k--;
    }

    println(ll);
    println(k);

    k = 4;
    ll = 6;

    while (k--)
    {
        ll = ll + 3;
    }

    println(ll);
    println(k);
}

int a, b, c;

void func_a()
{
    a = 7;
}

int foo(int a)
{
    a = a + 3;
    return a;
}

int bar(int a, int b)
{
    c = 4 * a + 2 * b;
    return c;
}

int main4()
{

    int i, j, k, l;

    i = 5;
    j = 6;

    func_a();
    println(a);

    k = foo(i);
    println(k);

    l = bar(i, j);
    println(l);

    j = 6 * bar(i, j) + 2 - 3 * foo(i);
    println(j);

    return 0;
}

int f(int a)
{
    int k;
    k = 5;
    while (k > 0)
    {
        a++;
        k--;
    }
    return 3 * a - 7;
    a = 9;
}

int g(int a, int b)
{

    int x, i;
    x = f(a) + a + b;

    for (i = 0; i < 7; i++)
    {
        if (i % 3 == 0)
        {
            x = x + 5;
        }
        else
        {
            x = x - 1;
        }
    }

    return x;
}

int main5()
{
    int a, b, i;
    a = 1;
    b = 2;
    a = g(a, b);
    println(a);
    for (i = 0; i < 4; i++)
    {
        a = 3;
        while (a > 0)
        {
            b++;
            a--;
        }
    }
    println(a);
    println(b);
    println(i);
    return 0;
}

int foo6(int a, int b)
{
    if (a + b <= 5)
    {
        return 7;
    }
    return foo6(a - 2, b - 1) + 2 * foo6(a - 1, b - 2);
}

int main6()
{
    int i, j, k;
    i = 7;
    j = 3;

    k = foo6(i, j);
    println(k);

    return 0;
}

int func(int n)
{
    int i;
    if (n == 0)
        return 0;
    i = n;
    return func(n - 1) + i;
}

int func2(int n)
{
    int i;
    if (n == 0)
        return 0;
    i = n;
    return func(n - 1) + i;
}

int main7()
{
    int a;
    a = func(7);
    println(a);
    return 0;
}

int main()
{
    main1();
    main2();
    main3();
    main4();
    main5();
    main6();
    main7();
    return 0;
}
