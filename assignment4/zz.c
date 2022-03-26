#include <stdio.h>

int main()
{
    FILE *fp = fopen("ssu_expr.txt", "w");

    fputs("123+456*789", fp);

    fclose(fp);

    return 0;
}
