int a, b;

float x, y;

int add_int(int, int);

float mul_float(float, float, float);

void print_global();

int main() {
    int list[5], another_list[5], i;

    a = 1+2*3-4/2+(7%3);
    x = 2.3*4.7;

    list[1] = a+list[0]+another_list[0];

    {
        int i, j;
    }

    for(i=0; i<5; i++) {
        list[1]++;
    }

    while(a<=0) {
        a--;
    }

    if(list[4]>10 || another_list[4]>=10) {
        i = !0;
    }

    if(a==0 && x!=3.9) {
        y = mul_float(1.2, 2.5*2.0, 2.4);
    } else {
        b = -add_int(4, 7);
    }

    print_global();

    return 0;
}

int add_int(int a, int b) {
    return a+b;
}

float mul_float(float x, float y, float z) {
    return x*y*z;
}

void print_global() {
    println(a);
    println(b);
    println(x);
    println(y);
}
