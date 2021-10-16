#include <bits/stdc++.h>
#include <x86intrin.h>
// https://github.com/sslotin/amh-code/blob/main/argmin/simdmin.cc
// szybkie ogarnięcie minów wielu elementów.
// can be useful for optimizing sq dps that need mins/maxs.
// "Argmin at the speed of memory (~3⋅1010 integer / float elements per second)"

const int B = 8;
typedef int vec __attribute__ (( vector_size(4 * B) ));

vec min(vec x, vec y) {
    return (x < y ? x : y);
}

const int n = (1<<16);
alignas(64) int a[n];

int argmin() {
    vec *v = (vec*) a;
    
    int m = INT_MAX, k = 0;
    vec t0, t1, p;
    t0 = t1 = p = m + vec{};

    for (int i = 0; i < n / B; i += 2) {
        t0 = min(t0, v[i]);
        t1 = min(t1, v[i + 1]);
        vec t = min(t0, t1);
        int mask = _mm256_movemask_epi8((__m256i) (p == t));
        if (mask != -1) { [[unlikely]]
            for (int j = B * i; j < B * i + 2 * B; j++)
                if (a[j] < m)
                    m = a[k = j];
            t0 = t1 = p = m + vec{};
        }
    }
    
    return k;
}
