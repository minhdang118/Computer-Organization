
int ncmp;

void x(int *a, int *b) {
    int c = a[0];
    a[0] = b[0];
    b[0] = c;
    return;
}

void s(int *a, int b) {
    int c = 1;
    while (c < b) {
        int d = c;
        while ((d > 0) && (a[d-1] < a[d])) {
            x(&a[d], &a[d-1]);
            ncmp++;
            d--;
        }
        c++;
    }
    return;
}