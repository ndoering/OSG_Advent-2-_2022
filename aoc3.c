#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

static int count;

void setup_persistent(const char *mmap_file);

int main(void)
{
	setup_persistent("mmap.persistent");
	printf("count = %d\n", count++);
	return 0;
}

void setup_persistent(const char *mmap_file)
{
	int mmap_fd = open(mmap_file, O_CREAT | O_RDWR);
	if (mmap_fd == -1){
		_exit(-1);
	}

	mmap(&count, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, mmap_fd, 0);

	close(mmap_fd);
}
