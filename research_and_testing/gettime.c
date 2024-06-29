#include <sys/time.h>
#include <stdio.h>

int main(void)
{
	int i = 0;
	int res = 0;
	int mres = 0;
	struct timeval	tv;
	struct timezone tz;

	printf("13\n");
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	printf("16\n");
	tz.tz_minuteswest = 12;
	tz.tz_dsttime = 10;
	printf("19\n");
	while (i++ < 5)
	{
		gettimeofday(&tv, &tz);
		res = tv.tv_sec;
		mres = tv.tv_usec;
		printf("result is %d\n and %d\n", res, mres);
	}
}
