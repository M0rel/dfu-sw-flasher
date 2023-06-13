#include <stdio.h>
#include <stdarg.h>
#include <getopt.h>
#include <errno.h>

int main(int argc, char **argv)
{
        int ch = 0;

        static struct option longopts[] = {
                {"help", no_argument, NULL, 'h'},
                {NULL, 0, NULL, 0} // The last element must be all zeros.
        };

        while ((ch = getopt_long(argc, argv, "h", longopts, NULL)) != -1) {
                switch (ch) {
                case 'h':
                        break;
                case '?':
                default:
                        return EINVAL;
                }
        }

        return 0;
}
