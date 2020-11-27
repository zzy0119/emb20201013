#include <stdio.h>
#include <unistd.h>

static void getl()
{
	printf("getopt -l...\n");
}

int main(int argc, char *argv[])
{
	int ret;

	while (1) {
		ret = getopt(argc, argv, "-lh:m::u");
		if (ret == -1)
			break;
		switch(ret) {
			case 'l':
				getl();
				break;
			case 'h':
				printf("getopt -h...\n");
				printf("argument:%s\n", optarg);
				break;
			case 'm':
				printf("getopt -m...\n");
				if (optarg)
					printf("argument:%s\n", optarg);
				break;
			case 'u':
				printf("getopt -u...\n");
				break;
			case '?':
				printf("i don't know\n");
				break;
			default:
				break;
		}
	}

	return 0;
}

