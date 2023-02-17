void show(int n)
{
    println(n);
}
int cnt;
int check()
{
    cnt++;
    return cnt;
}

int factorial(int n)
{
    if(n==0)
    {
        return 1;
    }
    else
    {
        return n*factorial(n-1);
    }
}

void grade(int n)
{
    if(n<0||n>100)
    {
        show(-1);
    }
    else if(n>=80)
    {
        show(80);
    }
    else if(n>=70&&n<80)
    {
        show(70);
    }
    else if(n>=60&&n<70)
    {
        show(60);
    }
    else if(n>=50&&n<60)
    {
        show(50);
    }
    else if(n<50)
    {
        show(-100);
    }
}

int main(){
    grade(85);
    grade(75);
    grade(80);
    grade(69);
    grade(32);
    grade(49);
    grade(50);
    grade(71);
    grade(51);
    grade(-95);
    grade(200);
	show(factorial(5));
	show(factorial(6));
    return 0;
}