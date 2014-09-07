/* Your program is to use the brute-force approach in order to find the Answer to Life, 
 * the Universe, and Everything. More precisely... rewrite small numbers from input to 
 * output. Stop processing input after reading in the number 42. All numbers at input 
 * are integers of one or two digits.
 */

#include <stdio.h>


int main()
{
    int n;
    while (1) {
        scanf("%d", &n);
        if (n == 42)
            break;
        printf("%d\n", n);
    }
    return 0;
}
