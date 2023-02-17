int a, b;

float x, y;

int add_int(int, int);

float mul_float(float, float, float);

void print_global();

int main() {
    int list[5], another_list[5], i;

    a - 1+2-3}4;  // Syntax Error
    x = 2.3,4.7;  // Syntax Error

    x = 1+2*3-4/2+(7.1%3);  // Type mismatch (Error/Warning): float = int, Operand of modulus is float (Error)
    a = 2.3*4.7;  // Type mismatch (Error/Warning): int = float

    list[1] = a+list[0.4]+another_list[0];  // Index of an array is not an integer (Error)

    {
        int i, j;
        int i;  // Same name of variables declared in the same scope (Error)
    }

    j = 7.5;  // Undeclared variable in this scope (Error)

    for(i=0; i<5; i++) {
        list[]++;  // No index provided for array (Error)
    }

  /*  while(a<=0) [  // Syntax Error
        a--;
    ]
  */
    i();  // Undeclared (or undefined) function called with an existing variable name (Error)

    if(list[4]>10 || another_list[4]>=10) {
        i = !0;
    }

    if(a==0 && x!=3.9) {
        y = mul_float(1.2, 2.5*2.0);  // Function called with improper number of arguments (Error)
        b = mul_float(1.2, 2.5, 2.0);  // Type mismatch (Error/Warning): float = return(int)
    } else {
        b = -add_int(4.1, 7);  // Argument type inconsistent with function declaration (Error)
    }

    list[2] = print_global();  // Void function calling is part of an assignment expression (Error)

    return 0;
}

int add_int(int a, int b, int c) {  // Inconsistent function definition with its declaration (Error)
    return a+b;
}

float mul_float(float x, float y, float z) {
    return x*y*z;
}

void print_global() {
    print(a);
    print(b);
    print(x);
    print(y);
}
