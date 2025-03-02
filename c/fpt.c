#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

struct ieee754
{
    uint32_t frac : 23;
    uint32_t expon : 8;
    uint32_t sign : 1;
};

typedef union
{
    float f;
    uint32_t i;
    struct ieee754 iformat;
} FloatingPointObject;

int main(void)
{
    printf("=== Display the real float-point value stored in RAM. ===\n");
    printf("CPU clock/sec: %ld\n\n", CLOCKS_PER_SEC);
    float input_float;
    int extra_char;

    while (1)
    {
        printf("Please enter a float-point number (0 to exit): \n");
        if (scanf("%f", &input_float) != 1)
        {
            printf("Error: Invalid input! Please enter a valid number.\n\n");
            while ((extra_char = getchar()) != '\n' && extra_char != EOF);
            continue;
        }

        if ((extra_char = getchar()) != '\n')
        {
            printf("Error: Only one number is allowed!\n\n");
            while ((extra_char = getchar()) != '\n' && extra_char != EOF);
            continue;
        }

        if (input_float == 0)
        {
            printf("Execution terminated!\n\n");
            break;
        }
        else
        {
            clock_t t_start, t_end;
            double t_diff;
            FloatingPointObject fpt_input;
            t_start = clock();                  // start: access float
            fpt_input.f = input_float;
            t_end = clock();                    // end: access float
            printf(" - input value stored in RAM as 0x%X.\n", fpt_input.i);
            printf(" - the real floating-point value in program: %.23f\n", fpt_input.f);
            t_diff = ((double)(t_end-t_start))/CLOCKS_PER_SEC;
            printf(" ***duration of accessing float: %.10f\n\n", t_diff);

            t_start = clock();                  // start: translate ieee754
            int sign = fpt_input.iformat.sign;
            int exponent = fpt_input.iformat.expon - 127;
            uint32_t mantissa = fpt_input.iformat.frac | 0x800000;
            float real_value = (float)mantissa * (1.0f / (1 << 23));
            real_value = ldexpf(real_value, exponent);
            if (sign)
            {                
                real_value = -real_value;
            }
            t_end = clock();                    // end: translate ieee754
            t_diff = ((double)(t_end-t_start))/CLOCKS_PER_SEC;
            printf(" - sign: 0x%X\n", fpt_input.iformat.sign);
            printf(" - exponent: 0x%X\n", fpt_input.iformat.expon);
            printf(" - mantissa: 0x%X\n", fpt_input.iformat.frac);
            printf(" - translated from ieee754: %.23f\n", real_value);
            printf(" ***duration of translating IEEE754: %.10f\n\n", t_diff);
        }
    }

    return 0;
}
