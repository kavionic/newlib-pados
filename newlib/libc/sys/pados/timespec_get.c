
int timespec_get(struct timespec* ts, int base)
{
    if (base != TIME_UTC)
        return 0;
    clock_gettime(CLOCK_REALTIME, ts);
    return base;
}
