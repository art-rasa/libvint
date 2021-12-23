#include "libvint.h"

vint vint_new(void)
{
    vint v = NULL;
    
    v = calloc(1, sizeof(vbyte));
    
    if (v != NULL)
    {
        v[0] |= END_MARKER;
    }
    
    return v;
}

vint vint_from_uint(uint64_t value)
{
    const int input_bits = sizeof(value) * 8;
    int num_bits = 0;
    vint v = vint_new();
    int num_vbytes = 1;
    int idx_vbit = 0;
    int idx_vbyte = 0;
    bool bit = false;
    
    if (v == NULL)
    {
        return NULL;
    }
    
    for (int idx = 0; idx < input_bits; idx++)
    {
        bit = value & (1UL << idx);
        
        idx_vbyte = idx / BITS_PER_VBYTE;
        idx_vbit  = idx % BITS_PER_VBYTE;
        
        if (bit)
        {
            /* Not enough vbytes. */
            if ((idx_vbyte + 1) > num_vbytes)
            {
                ++num_vbytes;
                vint_resize(&v, num_vbytes);
            }
            
            v[idx_vbyte] |= (1UL << idx_vbit);
        }
    }
    
    return v;
}

vint vint_from_str(char * value)
{
    size_t nchars = 0;
    vint v = NULL;
    size_t i = 0;
    char num[4] = "\0";
    int count = 0;
    
    if ((value == NULL) or true)
    {
        return NULL;
    }
    
    nchars = strlen(value);
    
    for (i = nchars; i > 0; i--)
    {
        //putchar(value[i - 1]);
        num[count] = value[i - 1];
        ++count;
        if (count >= 3)
        {
            count = 0;
        }
    }
}

int vint_get_size(vint vnum)
{
    int nbytes = 0;
    
    if (vnum == NULL)
    {
        return 0;
    }
    
    while ( !(vnum[nbytes] & END_MARKER) )
    {
        ++nbytes;
    };
    
    return nbytes + 1;
}


bool vint_erase(vint vnum)
{
    if (vnum != NULL)
    {
        free(vnum);
        return true;
    }
    
    return false;
}

vint vint_add(vint vnum_a, vint vnum_b)
{
    const int len_a = vint_get_size(vnum_a);
    const int len_b = vint_get_size(vnum_b);
    const int total_vbytes = (len_a > len_b) ? len_a : len_b;
    vint result = vint_new();
    int result_length = 1;
    int idx_vbyte = 0;
    bool carry = false;
    
    if (result == NULL)
    {
        return NULL;
    }
    
    carry = false;
    for (idx_vbyte = 0; idx_vbyte < total_vbytes; idx_vbyte++)
    {
        int vbyte_a = 0;
        int vbyte_b = 0;
        
        if (idx_vbyte < len_a)
        {
            vbyte_a = vnum_a[idx_vbyte] & ~END_MARKER;
        }
        if (idx_vbyte < len_b)
        {
            vbyte_b = vnum_b[idx_vbyte] & ~END_MARKER;
        }
        
        for (int nbit = 0; nbit < BITS_PER_VBYTE; nbit++)
        {
            bool a = vbyte_a & (1 << nbit);
            bool b = vbyte_b & (1 << nbit);
            
            if ((a or b or carry) and ((idx_vbyte + 1) > result_length))
            {
                ++result_length;
                vint_resize(&result, result_length);
            }
            
            if (not carry) 
            {
                if (a and b)
                {
                    carry = true;
                }
                else if ((a and not b) or (not a and b))
                {
                    result[idx_vbyte] |= (1 << nbit);
                } 
            }
            else
            {
                if (a and b)
                {
                    result[idx_vbyte] |= (1 << nbit);
                }
                else if ((a and not b) or (not a and b))
                {
                    carry = false;
                }
                else if (not a and not b)
                {
                    result[idx_vbyte] |= (1 << nbit);
                    carry = false;
                }
            }
        }
    }
    
    if (carry)
    {
        ++result_length;
        vint_resize(&result, result_length);
        result[result_length - 1] |= 1;
        result[result_length - 1] |= END_MARKER;
    }
    else
    {
        result[result_length - 1] |= END_MARKER;
    }
    
    return result;
}


void vint_bitshift(vint * vnum, int amount)
{
    bool is_ovf = false;
    bool is_end = false;
    int n_vbytes = 0;
    int idx_vbyte = 0;
    int current_length = 0;
    vbyte current_vbyte = 0;
    
    if ((vnum == NULL) or (*vnum == NULL))
    {
        return;
    }
    
    n_vbytes = vint_get_size(*vnum);
    
    current_length = n_vbytes;
    idx_vbyte = n_vbytes - 1;
    while (amount > 0)
    {
        current_vbyte = (*vnum)[idx_vbyte];
        
        is_end = current_vbyte & END_MARKER;
        current_vbyte <<= 1;
        is_ovf = current_vbyte & END_MARKER;
        
        if (is_ovf and is_end)
        {
            (*vnum)[idx_vbyte] = current_vbyte & ~END_MARKER;
            (*vnum)[idx_vbyte] |= END_MARKER;
            ++current_length;
            vint_resize(vnum, current_length);
            
            (*vnum)[current_length - 1] |= 1;
            (*vnum)[current_length - 1] |= END_MARKER;
        }
        else if (is_ovf and not is_end)
        {
            (*vnum)[idx_vbyte] = current_vbyte & ~END_MARKER;
            (*vnum)[idx_vbyte + 1] |= 1;
        }
        else if (not is_ovf and is_end)
        {
            (*vnum)[idx_vbyte] = current_vbyte & ~END_MARKER;
            (*vnum)[idx_vbyte] |= END_MARKER;
        }
        else
        {
            (*vnum)[idx_vbyte] = current_vbyte;
            (*vnum)[idx_vbyte] &= ~END_MARKER;
        }
        
        --idx_vbyte;
        
        if (idx_vbyte < 0)
        {
            idx_vbyte = current_length - 1;
            --amount;
        }
    }
}


int vint_deepcopy(vint * from, vint * to)
{
    int idx = 0;
    int len = 0;
    
    if ((from == NULL) or (*from == NULL) or (to == NULL))
    {
        return 0;
    }
    
    len = vint_get_size(*from);
    vint_resize(to, len);
    
    idx = 0;
    do
    {
        (*to)[idx] = (*from)[idx];
        ++idx;
    } while ( !((*from)[idx] & END_MARKER) );
    
    return idx;
}

/* Resizes *vnum so that it will become req_vbytes long. */
void vint_resize(vint * vnum, int req_vbytes)
{
    vint new = NULL;
    int vbytes = 0;
    int num_to_copy = 0;
    
    if ((vnum == NULL) or (*vnum == NULL) or (req_vbytes < 1))
    {
        return;
    }
    
    vbytes = vint_get_size(*vnum);
    
    /* Nothing to do... */
    if (vbytes == req_vbytes)
    {
        return;
    }
    
    new = calloc(req_vbytes, sizeof(vbyte));
    
    if (new == NULL)
    {
        return;
    }
    
    num_to_copy = vbytes;
    
    /* If shrinking, must only copy up to new length. */
    if (req_vbytes < vbytes)
    {
        num_to_copy = req_vbytes;
    }
    
    /* Copying all data vbytes. */
    for (int idx = 0; idx < num_to_copy; idx++)
    {
        new[idx] = (*vnum)[idx] & ~END_MARKER;
    }
    
    /* Marking the end. */
    new[req_vbytes - 1] |= END_MARKER;
    
    free(*vnum);
    *vnum = new;
}

void vint_print_bits(vint vnum)
{
    int vbytes = 0;
    int vbits = 0;
    bool bit = false;
    
    if (vnum == NULL)
    {
        return;
    }
    
    vbits = sizeof(vnum[0]) * 8;
    vbytes = vint_get_size(vnum);
    
    printf("MSB ");
    for (int idx_vbyte = vbytes - 1; idx_vbyte >= 0; idx_vbyte--)
    {
        for (int idx_bit = vbits - 1; idx_bit >= 0; idx_bit--)
        {
            bit = vnum[idx_vbyte] & (1 << idx_bit);
            printf("%d", bit);
        }
        printf(" ");
    }
    printf("LSB");
}





















