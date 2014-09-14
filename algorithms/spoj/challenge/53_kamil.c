#include <stdio.h>
#include <string.h>
int main(){int t,i,j;char s[21];int cnt;char l[]="TDLF0";t=10;while(t--){scanf("%s", s);for(i=0,cnt=1;i<strlen(s);i++){j=0;l[4]=s[i];while(s[i]!=l[j++]);if(j!=5) cnt *=2;}printf("%d\n", cnt);} return 0;}
