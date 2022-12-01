#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define STDOUT 1

char buffer[BUFFER_SIZE];

int print_file(const char *file_path);

int main(int argc, char **argv)
{
	// get the number of files to concatenate, error if none given
	unsigned num_of_files = (argc > 1) ? argc - 1 : 0;
	if (num_of_files == 0) {
		return -1;
	}


	// iterate of all files, shortcut on error
	for (unsigned file_index = 1; file_index <= num_of_files; ++file_index){
		int result = print_file(argv[file_index]);
		if(result < 0) {
			return -1;
		}
	}

	return 0;
}


int print_file(const char *file_path)
{
	int return_code = 0;

	// open file and create the necessary file descriptor
	const int file_desc = open(file_path, O_RDONLY);
	if(file_desc  == -1) {
		return_code = file_desc;
		goto error_open;
	}

	ssize_t read_size = 0;
	ssize_t write_size = 0;

	/* read bytes into buffer, write to stdout and repeat until file is
	   read completely. File is read completely if the read_size is smaller
	   than the buffer size.
	 */
	do{
		read_size = read(file_desc, buffer, BUFFER_SIZE);
		if(read_size == -1){
			goto close_file_on_error;
		}

		write_size = write(STDOUT, buffer, read_size);
		if(write_size == -1 && write_size != read_size){
			goto close_file_on_error;
		}
	} while(read_size == BUFFER_SIZE);

close_file_on_error:
	return_code = close(file_desc);

error_open:
	return return_code;
}
