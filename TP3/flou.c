#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void load_image(const char* filepath, unsigned char** image_data, size_t* width, size_t* height);
void save_image(const char* filepath, unsigned char* image, size_t width, size_t height);

int index_from_x_y(int x, int y, int L)
{
	int index;
	index = x*3 + y*3*L;
	return index;
}

void blur(unsigned char* image, unsigned char* out_image, int x, int y, size_t width, size_t height, int intensity) {
	int r = 0;
	int g = 0;
	int b = 0;
	int pixels_count = 0;
	for (int i = -intensity/2; i < (intensity/2)+1; i++) { // int i = -1; i < 2; i++ (for base intensity = 3)
		for (int j = -intensity/2; j < (intensity/2)+1; j++) { // int j = -1; j < 2; i++ (for base intensity = 3)
			if ((x+i < 0 || x+i > (int)width-1 || y+j > (int)height-1 || y+j < 0)) {
				continue;
			}
			int index = index_from_x_y(x+i, y+j, width);
			r = r + image[index];
			g = g + image[index+1];
			b = b + image[index+2];
			pixels_count++;
		}
	}
	
	int current_index = index_from_x_y(x, y, width);
	out_image[current_index] = r / pixels_count;
	out_image[current_index + 1] = g / pixels_count;
	out_image[current_index + 2] = b / pixels_count;
}

int main(void)
{
	unsigned char* image = NULL;
	unsigned char* out_image = NULL;
    const char* filename = "image.ppm";
    const char* output_filename = "output.ppm";
	size_t width = 0;
	size_t height = 0;
	
    load_image(filename, &image, &width, &height);
	out_image = malloc((width*height*3) * sizeof(unsigned char));
	memset(out_image, 255, (width*height*3) * sizeof(unsigned char));

	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			blur(image, out_image, j, i, width, height, 3);
		}
	}

	save_image(output_filename, out_image, width, height);
	free(image);
    free(out_image);
	return 0;
}

//Vous n'avez pas besoin de comprendre les lignes qui suivent

char* readline(int fd)
{
	int offset = 0;
	size_t size;
	char dummy;
	do {
		size = read(fd,&dummy,1);
		offset += size;
	} while(size != 0 && dummy != '\n' && dummy != EOF);

	char* line = malloc(offset * sizeof(char)+1);
	lseek(fd,-offset,SEEK_CUR);
	read(fd,line,offset);
	line[offset]='\0';
	return line;
}

void load_image(const char* filepath, unsigned char** image_data, size_t* width, size_t* height)
{
	int fd = open(filepath,O_RDONLY);
	if (fd == -1)
	{
		perror("Can't open input file");
		exit(-1);
	}
	char* line = readline(fd);
	if ( strncmp("P6", line, 2) != 0)
	{
		fputs("Input File is not a ppm file\n", stderr);
		free(line);
		exit(-1);
	}
	free(line);
	do {
		line = readline(fd);
		if (line[0] == '#')
		{
			free(line);
			continue;
		}
		int success = sscanf(line,"%lu %lu",width,height);
		if (success != 2)
		{
			fputs("Input File is not a valid ppm file\n", stderr);
			free(line);
			exit(-1);
		}
		free(line);
	} while(*width == 0);
	int dummy = 0;
	do {
		line = readline(fd);
		if (line[0] == '#')
		{
			free(line);
			continue;
		}
		int success = sscanf(line,"%d",&dummy);
		if (success != 1)
		{
			fputs("Input File is not a valid ppm file\n", stderr);
			free(line);
			exit(-1);
		}
		free(line);
	} while(dummy == 0);

	unsigned data_size = 3 * (*width) * (*height);
	*image_data = malloc(data_size * sizeof(unsigned char));

    read(fd,*image_data,3*(*width)*(*height));
}

void save_image(const char* filepath, unsigned char* image, size_t width, size_t height)
{
	int fd = open(filepath,O_CREAT|O_WRONLY,0644);
	if (fd == -1)
	{
		perror("Can't open output file");
		exit(-1);
	}
	write(fd,"P6\n",3);
	char* size = NULL;
	asprintf(&size,"%lu %lu\n",width, height);
	write(fd,size,strlen(size));
	free(size);
	write(fd,"255\n",4);
    usleep(500000);
    write(fd,image,3*width*height);
	write(fd,"\n",1);
	close(fd);

}

