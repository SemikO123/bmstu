# include  <stdio.h>

int time(int *h, int *m, int *s)
{
    int t = *s;
    *h = t/3600;
    *m = (t - 3600* *h)/60;
    *s = t - 3600* *h - 60* *m;
    return 0;
}

int main(void)
{
    int hour = 0;
    int min = 0;
    int sec = 4000;
    printf("%d Seconds\n",sec);
    time(&hour,&min,&sec);
    printf("%d Hours %d Minutes %d Seconds\n",hour,min,sec);
}