#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "mod.h"
#include "version.h"
#include "ade32.h"

#define SPACE_PAD	10
#define NAME_LEN	80

typedef struct {
	unsigned long	size;
	unsigned char	*data;
} t_buffer;

t_buffer	fbuffer;

char	prefix_char	[NAME_LEN];
char	name_char	[NAME_LEN];
char	operand1_char	[NAME_LEN];
char	operand2_char	[NAME_LEN];
char	operand3_char	[NAME_LEN];


instr_name	name = {
	0,		// prefix_len
	0,		// name_len
	0,		// operand1_len
	0,		// operand2_len
	0,		// operand3_len
	prefix_char,
	name_char,
	operand1_char,
	operand2_char,
	operand3_char
};

void mod_usage (void) {
	printf ("Usage: mod [OPTION]\n");
	printf ("Example: mod -f file.dat -s 0x10\n\n");
	printf ("  -f file to disassemble\n");
	printf ("  -s skip first n bytes\n");
	printf ("  -c decode only n instructions\n");
	printf ("  -b decode only n bytes\n");
	printf ("\nReport bugs to <%s>\n", _CONTACT_);
}

unsigned long file_size (FILE *f) {
  unsigned long curpos, lenght;

  curpos = ftell(f);
  fseek(f, 0L, SEEK_END);
  lenght = ftell(f);
  fseek(f, curpos, SEEK_SET);
  return lenght;
}

int load_file (char *name) {
	FILE	*f;
	unsigned long	fsize;

	if ((f = fopen (name, "rb")) == NULL) {
		printf ("Unable to open file %s.\n", name);
		return 1;
	}

	fsize = file_size (f);
	if (!fsize) {
		printf ("File %s is empty.\n", name);
		return 1;
	}

	if ((fbuffer.data = (unsigned char*)malloc(fsize)) == NULL) {
		printf ("File %s does not fit in memory.\n", name);
		return 1;
	}

	if (fread (fbuffer.data, 1, fsize, f) != fsize) {
		printf ("Unable to read file %s.\n", name);
		return 1;
	}

	fclose (f);

	fbuffer.size = fsize;

	return 0;
}

void print_decoded (struct ade32_struct* s, unsigned long index, int length) {
	int	i;

	printf ("%2.8lx ", index);

	for (i = 0; i < length; i++) {
		printf ("%2.2x ", fbuffer.data[index + i]);
	}

	for ( ;i < SPACE_PAD; i++) {
		printf ("   ");
	}

	if (name.prefix_len) printf ("%s ", name.prefix);
	if (name.name_len) printf ("%s", name.name);
	if (name.operand1_len > 1) printf (" %s", name.operand1);
	if (name.operand2_len > 1) printf (", %s", name.operand2);
	if (name.operand3_len > 1) printf (", %s", name.operand3);

	printf ("\n");
}

void clean_name (void) {

	name.prefix_len = 0;
	name.name_len = 0;
	name.operand1_len = 0;
	name.operand2_len = 0;
	name.operand3_len = 0;
	memset (&prefix_char, 0, NAME_LEN);
	memset (&name_char, 0, NAME_LEN);
	memset (&operand1_char, 0, NAME_LEN);
	memset (&operand2_char, 0, NAME_LEN);
	memset (&operand3_char, 0, NAME_LEN);
}

void decode_loop (unsigned long	skip_index, unsigned long max_count, unsigned long max_index) {
	struct ade32_struct s = {4,4};	// prepare to disasm 32-bit code
	unsigned long	count = 0;	// count of decoded instructions
	unsigned long	index = 0;
	unsigned char	*pindex;
	int	quit = 0;
	int	length;			// instruction length

	pindex = fbuffer.data;

	if (skip_index && (skip_index < fbuffer.size)) {
		printf ("Skipping %ld bytes ... \n", skip_index);

		index += skip_index;
		pindex += index;
	} else
	if (skip_index >= fbuffer.size) {
		printf ("Can't skip over whole file (%ld >= %ld).\n", skip_index, fbuffer.size);
		return;
	}

	while (!quit) {

		clean_name ();
		length = ade32_disasm(pindex, &s);
		instr_decode (&s, &name, index + length);

		if (!length) {
			length++;
		}

		print_decoded (&s, index, length);

		index += length;
		pindex += length;

		if (max_count) {
			count++;
		}

		if (index >= fbuffer.size) {
			quit = 1;
		}

		if (max_count && (count >= max_count)) {
			quit = 1;
		}

		if (max_index && (index >= max_index)) {
			quit = 1;
		}
	}
}

int main (int argc, char **argv) {

	int next_opt = 0;
	char *file = NULL;
	unsigned long count = 0;
	unsigned long skip = 0;
	unsigned long bytes = 0;

	printf ("emmil's 32bit disassembler ver. %s %s\n\n", _VER_, _COPYRIGHT_);

	if (argc < 2) {
		mod_usage ();
		return 0;
	}

	while (next_opt != -1) {

		next_opt = getopt (argc, argv, "f:c:s:b:");

		switch (next_opt) {
			case 'f' : file = optarg; break;
			case 'c' : count = strtoul (optarg, NULL, 0); break;
			case 's' : skip = strtoul (optarg, NULL, 0); break;
			case 'b' : bytes = strtoul (optarg, NULL, 0); break;
		}
	}

	if (file == NULL) {
		printf ("File to disassemble required.\n\n");
		mod_usage ();
		return 0;
	}

	if (load_file (file)) {
		return 1;
	}

	decode_loop (skip, count, bytes);

	return 0;
}

