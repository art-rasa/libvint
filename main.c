#include "libvint.h"
#include <stdint.h>
#include <stdio.h>

void spacer(char * title);
void test_allocation(void);
void test_addition(void);
void test_resize(void);
void test_deepcopy(void);
void test_print_bits(void);
void test_from_str(void);
void test_bitshift(void);

int main(int argc, char * argv[])
{
    test_allocation();
    test_addition();
    test_resize();
    test_deepcopy();
    test_print_bits();
    test_from_str();
    test_bitshift();
    return 0;
}

void test_allocation(void)
{
    uint64_t num = 654321;
    vint v = vint_from_uint(num);

    spacer("Allocation");
    
    printf("v (%lu) is %d vbytes long. \n", num, vint_get_size(v));
    vint_print_bits(v);
    puts("\n");
    
    vint_erase(v);
}

void test_addition(void)
{
    vint v1 = vint_from_uint(127);
    vint v2 = vint_from_uint(127);
    vint r = NULL;
    
    spacer("Addition");
    
    printf("v1 (127) is %d vbytes long. \n", vint_get_size(v1));
    vint_print_bits(v1);
    puts("\n");
    printf("v2 (127) is %d vbytes long. \n", vint_get_size(v2));
    vint_print_bits(v2);
    puts("\n");
    r = vint_add(v1, v2);
    printf("r (127 + 127) is %d vbytes long. \n", vint_get_size(r));
    vint_print_bits(r);
    puts("\n");
    vint_erase(v1);
    vint_erase(v2);
    vint_erase(r);
}

void test_resize(void)
{
    vint v = vint_from_uint(555);
    
    spacer("Resizing");
    
    printf("v (555) is %d vbytes long. \n", vint_get_size(v));
    vint_print_bits(v);
    puts("\n");
    
    vint_resize(&v, 7);
    printf("After resizing v to 7: %d vbytes. \n", vint_get_size(v));
    vint_print_bits(v);
    puts("\n");
    
    vint_resize(&v, 10);
    printf("After resizing v to 10: %d vbytes. \n", vint_get_size(v));
    vint_print_bits(v);
    puts("\n");
    
    vint_resize(&v, 5);
    printf("After resizing v to 5: %d vbytes. \n", vint_get_size(v));
    vint_print_bits(v);
    puts("\n");
    
    vint_resize(&v, 4);
    printf("After resizing v to 4: %d vbytes. \n", vint_get_size(v));
    vint_print_bits(v);
    puts("\n");
    
    vint_resize(&v, 2);
    printf("After resizing v to 2: %d vbytes. \n", vint_get_size(v));
    vint_print_bits(v);
    puts("\n");
    
    vint_resize(&v, 1);
    printf("After resizing v to 1: %d vbytes. \n", vint_get_size(v));
    vint_print_bits(v);
    puts("\n");
    
    vint_resize(&v, 0);
    printf("After resizing v to 0 (no effect): %d vbytes. \n", vint_get_size(v));
    vint_print_bits(v);
    puts("\n");
    
    vint_erase(v);
}

void test_deepcopy(void)
{
    vint v1 = vint_from_uint(123456789012);
    vint v2 = vint_new();
    
    spacer("Deep copy");
    
    printf("v1 (123456789012) is %d vbytes long. \n", vint_get_size(v1));
    vint_print_bits(v1);
    puts("\n");
    printf("v2 (0) is %d vbytes long. \n", vint_get_size(v2));
    vint_print_bits(v2);
    puts("\n");
    
    vint_deepcopy(&v1, &v2);
    
    puts("After deep copying v1 into v2:");
    printf("v2 (originally 0) is %d vbytes long. \n", vint_get_size(v2));
    vint_print_bits(v2);
    puts("\n");
    
    vint_erase(v1);
    vint_erase(v2);
}

void test_print_bits(void)
{
    vint v1 = vint_from_uint(213);
    vint v2 = vint_from_uint(10837);
    vint v3 = vint_from_uint(5581397);
    vint v4 = vint_from_uint(123456789012);
    vint v5 = vint_add(v4, v4);
    vint v6 = vint_from_uint(27);
    vint v7 = vint_new();
    vint v8 = vint_from_uint(1);
    vint v9 = vint_from_uint(2863311530);
    vint v10 = vint_from_uint(7);
    
    spacer("Printing bits");
    
    printf("v1 (213) is %d vbytes long: \n", vint_get_size(v1));
    vint_print_bits(v1);
    puts("\n");
    
    printf("v2 (10837) is %d vbytes long: \n", vint_get_size(v2));
    vint_print_bits(v2);
    puts("\n");
    
    printf("v3 (5581397) is %d vbytes long: \n", vint_get_size(v3));
    vint_print_bits(v3);
    puts("\n");
    
    printf("v4 (123456789012) is %d vbytes long: \n", vint_get_size(v4));
    vint_print_bits(v4);
    puts("\n");
    
    printf("v5 (123456789012 + 123456789012) is %d vbytes long: \n", vint_get_size(v5));
    vint_print_bits(v5);
    puts("\n");
    
    printf("v6 (27) is %d vbytes long: \n", vint_get_size(v6));
    vint_print_bits(v6);
    puts("\n");
    
    printf("v7 (0) is %d vbytes long: \n", vint_get_size(v7));
    vint_print_bits(v7);
    puts("\n");
    
    printf("v8 (1) is %d vbytes long: \n", vint_get_size(v8));
    vint_print_bits(v8);
    puts("\n");
    
    printf("v9 (2863311530) is %d vbytes long: \n", vint_get_size(v9));
    vint_print_bits(v9);
    puts("\n");
    
    printf("v10 (7) is %d vbytes long: \n", vint_get_size(v10));
    vint_print_bits(v10);
    puts("\n");
    
    vint_erase(v1);
    vint_erase(v2);
    vint_erase(v3);
    vint_erase(v4);
    vint_erase(v5);
    vint_erase(v6);
    vint_erase(v7);
    vint_erase(v8);
    vint_erase(v9);
    vint_erase(v10);
}

void test_from_str(void)
{
    spacer("Initializing from a numeric string");
    puts("(skipping)");
}

void test_bitshift(void)
{
    vint v1 = vint_from_uint(64677154575);
    vint v2 = vint_from_uint(1973790);
    vint v3 = vint_from_uint(1);
    
    spacer("Shifting bits");
    
    printf("v1 (64677154575) is %d vbytes long before shift: \n", vint_get_size(v1));
    vint_print_bits(v1);
    puts("");
    vint_bitshift(&v1, 1);
    printf("...after 1 left-shift v1 is %d vbytes long: \n", vint_get_size(v1));
    vint_print_bits(v1);
    puts("\n");
    
    printf("v2 (1973790) is %d vbytes long before shift: \n", vint_get_size(v2));
    vint_print_bits(v2);
    puts("");
    vint_bitshift(&v2, 1);
    printf("...after 1 left-shift v2 is %d vbytes long: \n", vint_get_size(v2));
    vint_print_bits(v2);
    puts("\n");
    
    printf("v3 (1) is %d vbytes long before shift: \n", vint_get_size(v3));
    vint_print_bits(v3);
    puts("");
    vint_bitshift(&v3, 142);
    printf("..after 142 left-shifts v3 is %d vbytes long: \n", vint_get_size(v3));
    vint_print_bits(v3);
    puts("\n");
    
    vint_erase(v1);
    vint_erase(v2);
    vint_erase(v3);
}

void spacer(char * title)
{
    puts("");
    puts("-------------------------------");
    if (title != NULL)
    {
        printf("test: %s \n", title);
    }
    puts("-------------------------------");
}













