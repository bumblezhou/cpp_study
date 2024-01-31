#include <stdio.h>
#include <string.h>

int main()
{
    int targetStrLen = 5;           // Target output length
    const char *myString="2357";   // String for output 
    const char *padding="...................................................";
    
    int padLen = targetStrLen - strlen(myString); // Calc Padding length
    if(padLen < 0) padLen = 0;    // Avoid negative length
    
    printf("%*.*s%s\n", padLen, padLen, padding, myString);  // LEFT Padding 
    printf("%s%*.*s\n", myString, padLen, padLen, padding);  // RIGHT Padding 
    return 0;
}
