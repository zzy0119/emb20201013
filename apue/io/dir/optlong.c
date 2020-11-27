#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	struct option opts[] = {
		{"help", 0, NULL, 'h'},
		{"test", 1, NULL, 't'},
		{"optional", 2, NULL, 'o'},
		{0, 0, 0, 0}
	};
	int ret;

	while (1) {
		ret = getopt_long(argc, argv, "-la", opts, NULL);
		if (ret == -1)
			break;
		switch (ret) {
			case 'l':
				printf("hello -l\n");
				break;
			case 'a':
				printf("hello -a\n");
				break;
			case 'h':
				printf("opt long help\n");
				break;
			case 't':
				printf("arg opt long test\n");
				puts(optarg);
				break;
			case 'o':
				printf("optional arg opt long\n");
				if (optarg) {
					puts(optarg);
				}
				break;
			case '?':
				printf("don't know\n");
				break;
			case 1:
				printf("非选项参数:%s\n", argv[optind-1]);
				break;
			default:
				break;
		}
	}

	return 0;
}

