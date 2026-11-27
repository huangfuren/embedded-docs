#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("sqrt(2)      = %.10f\n", sqrt(2.0));
    printf("pow(2, 10)   = %.1f\n", pow(2.0, 10.0));
    printf("fabs(-3.5)   = %.1f\n", fabs(-3.5));
    printf("fmod(7.5, 2) = %.2f\n", fmod(7.5, 2.0));

    double a = 0.1 + 0.2;
    printf("0.1+0.2      = %.17f\n", a);
    printf("0.1+0.2==0.3 ? %d\n", a == 0.3);
    printf("fabs(a-0.3) < 1e-9 ? %d\n", fabs(a - 0.3) < 1e-9);
    return 0;
}
