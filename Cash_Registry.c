#import<stdio.h>
#import<cs50.h>
#import<math.h>
int main(void)
{
    /*checks the input in the range*/
    float k;
    do
    {
        k = get_float("Enter the exact change to be provided:\n");
    }
    while (k < 0);

    int n = round(k * 100);
    /*0.45*/
    int ret, count = 0;
    /*loop for repeated checks*/
    while (n > 0)
        /*checks for 25 cents*/
        if (n >= 25)
        {
            ret = n / 25;
            count = count + ret;
            n = (n - ret * 25);
        }
    /*checks for 10 cents*/
        else if (n >= 10)
        {
            ret = n / 10;
            count = count + ret;
            n = (n - ret * 10);
        }
    /*checks for 5 cents*/
        else if (n >= 5)
        {
            ret = n / 5;
            count = count + ret;
            n = (n - ret * 5);
        }
    /*checks for less than 5 cents*/
        else if (n < 5)
        {
            count += n;
            n = 0;
        }

    printf("%i\n", count);
}




