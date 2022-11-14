#include <stdio.h>
#include <string.h>

int palindrom(char *s,int p,int u)
{
    if (p==u || p>u) return 1;

    if (s[p]!=s[u]) return 0;
    return palindrom(s,p+1,u-1);

}

int main()
{
    char s[100];

    scanf("%s",s);

    if (palindrom(s,0,strlen(s)-1))
        printf("Palindrom\n");
    else printf("Nu e palindrom\n");

        return 0;
}