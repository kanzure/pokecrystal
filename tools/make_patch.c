#define PROGRAM_NAME "make_patch"
#define USAGE_OPTS "constants.txt labels.sym patched.gbc original.gbc vc.patch.template vc.patch"

#include "common.h"

#include <ctype.h>

#define HIGH(x) (((x) >> 8) & 0xff)
#define LOW(x) ((x) & 0xff)

struct Symbol {
	struct Symbol *next;
	unsigned int value;
	int bank;
	int address;
	enum Addresstype {ROM, VRAM, SRAM, WRAM, HRAM} addresstype;
	char name[];
};

struct Patch {
	unsigned int offset;
	unsigned int size;
};

struct Buffer {
	size_t size;
	char buffer[];
};

void free_buffer(void *buf) {
	struct Buffer *buffer = (struct Buffer *)((char *)buf - sizeof(struct Buffer));
	free(buffer);
}

void *create_buffer(void) {
	struct Buffer *buffer = xmalloc(sizeof(struct Buffer) + 0x100);
	buffer->size = 0x100;
	return buffer->buffer;
}

void *expand_buffer(void *buf, const size_t size) {
	struct Buffer *buffer = (struct Buffer *)((char *)buf - sizeof(struct Buffer));
	size_t old_size = buffer->size;
	if (size > buffer->size) {
		buffer = xrealloc(buffer, old_size + 0x100);
	}
	buffer->size = old_size + 0x100;
	return buffer->buffer;
}

void free_symbols(struct Symbol *list) {
	while (list) {
		struct Symbol *next = list->next;
		free(list);
		list = next;
	}
}

void create_symbol_value(struct Symbol **tip, const int value, const char *name) {
	struct Symbol *symbol = xmalloc(sizeof(struct Symbol) + strlen(name) + 1);
	symbol->value = value;
	strcpy(symbol->name, name);
	symbol->next = *tip;
	*tip = symbol;
}

void create_symbol(struct Symbol **tip, const int bank, const int address, enum Addresstype addresstype, const char *name) {
	struct Symbol *symbol = xmalloc(sizeof(struct Symbol) + strlen(name) + 1);
	symbol->bank = bank;
	symbol->address = address;
	symbol->addresstype = addresstype;
	strcpy(symbol->name, name);
	symbol->next = *tip;
	*tip = symbol;
}

const struct Symbol *find_symbol(const struct Symbol *symbols, const char *name) {
	int namelen = strlen(name);
	for (const struct Symbol *symbol = symbols; symbol; symbol = symbol->next) {
		int symbolnamelen = strlen(symbol->name);
		if (namelen > symbolnamelen) {
			continue;
		}
		const char *symbolname = symbol->name;
		if (name[0] == '.') {
			// If `name` is a local label, compare it to the local part of `symbol->name`
			symbolname += symbolnamelen - namelen;
		}
		if (!strcmp(symbolname, name)) {
			return symbol;
		}
	}
	return NULL;
}

int parse_address_bank(char *buffer_input) {
	char *buffer = xmalloc(strlen(buffer_input) + 1);
	strcpy(buffer, buffer_input);

	char *buffer_address = strchr(buffer, ':');
	if (buffer_address) {
		*buffer_address++ = '\0';
	}

	char *endptr_bank;
	int bank = strtol(buffer, &endptr_bank, 16);
	if (bank > 0xff || bank < 0) {
		return -1;
	}
	if (endptr_bank != buffer + strlen(buffer)) {
		fprintf(stderr, "Error: Cannot parse bank %s: %s\n", buffer, buffer_address);
		return -1;
	}

	return bank;
}

int parse_address_address(char *buffer_input) {
	char *buffer = xmalloc(strlen(buffer_input) + 1);
	strcpy(buffer, buffer_input);

	char *buffer_address = strchr(buffer, ':');
	if (buffer_address) {
		*buffer_address++ = '\0';
	}

	// Parse the address part
	char *endptr_address;
	int address = strtol(buffer_address, &endptr_address, 16);
	if (address > 0xffff || address < 0) {
		return -1;
	}
	if (endptr_address != buffer_address + strlen(buffer_address)) {
		fprintf(stderr, "Error: Cannot parse address %s: %s\n", buffer, buffer_address);
		return -1;
	}

	return address;
}

int parse_abs_offset(int bank, int address, enum Addresstype addresstype) {
	switch (addresstype) {
	case(WRAM):
		return bank ? bank * 0xd000 + (address - 0xd000) : address;
	case(SRAM):
		return bank ? bank * 0xc000 + (address - 0xc000) : address;
	case(HRAM):
		return address;
	default:
		return bank ? bank * 0x4000 + (address - 0x4000) : address;
	}

	return -1;
}

int parse_offset(int offset, enum Addresstype addresstype) {
	switch(addresstype) {
	case(WRAM):
		return offset > 0xd000 ? 0xd000 + offset % 0xd000 : offset;
	case(SRAM):
		return offset > 0xc000 ? 0xc000 + offset % 0xc000 : offset;
	case(HRAM):
		return offset;
	default:
		return offset > 0x4000 ? 0x4000 + offset % 0x4000 : offset;
	}

	return -1;
}

struct Symbol *parse_symfile(const char *filename) {
	FILE *file = xfopen(filename, 'r');

	struct Symbol *symbols = NULL;

	char *buffer = create_buffer();
	size_t buffer_index = 0;
	int bank = 0;
	int address = 0;
	int offset = -1;
	enum Addresstype addresstype = ROM;

	for (int c = getc(file); c != EOF; c = getc(file)) {
		buffer = expand_buffer(buffer, buffer_index);

		switch (c) {
		case ';':
		case '\r':
		case '\n':
			// If we encounter a newline or comment, we've reached the end of the label name
			buffer[buffer_index] = '\0';
			// This is the end of the parsable line
			buffer_index = SIZE_MAX;
			offset = parse_abs_offset(bank, address, addresstype);
			if (offset != -1) {
				if (address >= 0x8000 && address < 0xa000) {addresstype = VRAM;}
				if (address >= 0xa000 && address < 0xc000) {addresstype = SRAM;}
				if (address >= 0xc000 && address < 0xf000) {addresstype = WRAM;}
				if (address >= 0xff80 && address < 0xffff) {addresstype = HRAM;}
				create_symbol(&symbols, bank, address, addresstype, buffer);
				offset = -1;
			}
			break;

		case ' ':
			if (offset != -1) {
				// If we've just encountered a space, ignore this one
				if (buffer_index) {
					buffer[buffer_index++] = c;
				}
			} else {
				// If we encounter a space, we've reached the end of the address
				buffer[buffer_index] = '\0';
				bank = parse_address_bank(buffer);
				address = parse_address_address(buffer);
				buffer_index = offset ? 0 : SIZE_MAX;
			}
			break;

		default:
			buffer[buffer_index++] = c;
		}

		// We were requested to skip to the next line
		if (buffer_index == SIZE_MAX) {
			buffer_index = 0;
			offset = -1;
			while (c != '\n' && c != '\r' && c != EOF) {
				c = getc(file);
			}
		}
	}

	fclose(file);
	free_buffer(buffer);
	return symbols;
}

struct Symbol *parse_constfile(const char *filename, struct Symbol **symbols) {
	FILE *file = xfopen(filename, 'r');

	char *buffer = create_buffer();
	size_t buffer_index = 0;
	int value = -1;

	for (int c = getc(file); c != EOF; c = getc(file)) {
		buffer = expand_buffer(buffer, buffer_index);

		switch (c) {
		case ';':
		case '\r':
		case '\n':
			// If we encounter a newline or comment, we've reached the end of the label name
			buffer[buffer_index] = '\0';
			// This is the end of the parsable line
			buffer_index = SIZE_MAX;
			if (value != -1) {
				create_symbol_value(symbols, value, buffer);
				value = -1;
			}
			break;

		case ' ':
			if (value != -1) {
				// If we've just encountered a space, ignore this one
				if (buffer_index) {
					buffer[buffer_index++] = c;
				}
			} else {
				// If we encounter a space, we've reached the end of the value
				buffer[buffer_index] = '\0';
				char *endvalue;
				value = strtol(buffer, &endvalue, 10);
				if (endvalue != buffer + strlen(buffer)) {
					value = -1;
				}
				buffer_index = 0;
			}
			break;

		default:
			buffer[buffer_index++] = c;
		}

		// We were requested to skip to the next line
		if (buffer_index == SIZE_MAX) {
			buffer_index = 0;
			value = -1;
			while (c != '\n' && c != '\r' && c != EOF) {
				c = getc(file);
			}
		}
	}

	fclose(file);
	free_buffer(buffer);
	return *symbols;
}

void interpret_command(
	char *command, const struct Symbol *current_patch, const struct Symbol *symbols,
	struct Patch *patch, FILE *new_rom, FILE *orig_rom, FILE *output
) {
	// Count the arguments
	int argc = 0;
	for (char *c = command; *c; c++) {
		if (*c == ':') {
			argc++;
		}
	}

	// Get the arguments
	char *argv[argc]; // VLA
	char *arg = command;
	for (int i = 0; i < argc; i++) {
		arg = strchr(arg, ':');
		if (!arg) {
			break;
		}
		*arg++ = '\0';
		argv[i] = arg;
	}

	int offset = current_patch ? parse_abs_offset(current_patch->bank, current_patch->address, current_patch->addresstype) : -1;

	// Use the arguments
	if (!strcmp(command, "ADDREss")) {
		// This is only necessary to match the exact upper/lower casing in the original patch
		int high = offset >> 8;
		int low = offset & 0xFF;
		fprintf(output, "0x%X%x", high, low);
	} else if (!strcmp(command, "Address") || !strcmp(command, "address")) {
		if (argc > 0) offset += strtol(argv[0], NULL, 0);
		fprintf(output, "0x");
		if (argc > 1) {
			for (int i = strtol(argv[1], NULL, 0); i > 0; i--) {
				putc('0', output);
			}
		}
		fprintf(output, isupper((unsigned char)command[0]) ? "%X" : "%x", offset);
	} else if (!strcmp(command, "Patch") || !strcmp(command, "patch")) {
		if (argc > 0) offset += strtol(argv[0], NULL, 0);
		if (fseek(orig_rom, offset, SEEK_SET)) {
			fprintf(stderr, "Error: Could not seek to the offset of %s in the original ROM\n", current_patch->name);
			return;
		}
		if (fseek(new_rom, offset, SEEK_SET)) {
			fprintf(stderr, "Error: Could not seek to offset of %s in the new ROM\n", current_patch->name);
			return;
		}
		if (argc <= 1 || strcmp(argv[1], "big")) {
			int c = getc(new_rom);
			if (c == getc(orig_rom)) {
				fprintf(stderr, "Warning: %s doesn't actually contain any differences\n", current_patch->name);
			}
			patch->offset = offset;
			patch->size = 1;
			fprintf(output, "0x");
			fprintf(output, isupper((unsigned char)command[0]) ? "%02X" : "%02x", c);
		} else {
			char *searchend = xmalloc(strlen(current_patch->name) + strlen("_End") + 1);
			strcpy(searchend, current_patch->name);
			strcat(searchend, "_End");
			current_patch = find_symbol(symbols, searchend);
			if (!current_patch) {
				fprintf(stderr, "Error: Could not find symbol: %s", searchend);
			} else {
				// Figure out the length of the patch
				int length = parse_abs_offset(current_patch->bank, current_patch->address, current_patch->addresstype) - offset;
				memset(searchend, 0, (strlen(current_patch->name)));
				// We've got the length, now go back
				fseek(new_rom, offset, SEEK_SET);
				// Print out the patch
				patch->offset = offset;
				patch->size = length;
				fprintf(output, "a%d:", length);
				for (int i = 0; i < length; i++) {
					if (i) {
						putc(' ', output);
					}
					fprintf(output, isupper((unsigned char)command[0]) ? "%02X" : "%02x", getc(new_rom));
				}
			}
		}
	} else if (!strcmp(command, "Constant") || !strcmp(command, "constant")) {
		if (argc != 2) {
			fprintf(stderr, "Error: Missing argument for %s", command);
		}
		const struct Symbol *getsymbol = find_symbol(symbols, argv[1]);
		if (!getsymbol) return;
		int parsed_offset = parse_offset(getsymbol->value, getsymbol->addresstype);
		if (!strcmp(argv[0], "db")) {
			fprintf(output, isupper((unsigned char)command[0]) ? "%02X": "%02x",
				parsed_offset);
		} else {
			fprintf(output, isupper((unsigned char)command[0]) ? "%02X %02X": "%02x %02x",
				parsed_offset, HIGH(parsed_offset));
		}
	} else if (!strcmp(command, "findaddress")) {
		if (argc != 1) {
			fprintf(stderr, "Error: Missing argument for %s", command);
		}
		const struct Symbol *getsymbol = find_symbol(symbols, argv[0]);
		if (!getsymbol) return;
		fprintf(output, "0x%x", parse_abs_offset(getsymbol->bank, getsymbol->address, getsymbol->addresstype));
	} else if (!strcmp(command, "conaddress")) {
		if (argc != 2) {
			fprintf(stderr, "Error: Missing argument for %s", command);
		}
		const struct Symbol *getsymbol = find_symbol(symbols, argv[1]);
		if (!getsymbol) return;
		int parsed_offset = getsymbol->address;
		if (!strcmp(argv[0], "dw")) {
			fprintf(output, "%02x ", LOW(parsed_offset));
			fprintf(output, "%02x ", HIGH(parsed_offset));
			fprintf(output, "%02x ", LOW(parsed_offset + 1));
			fprintf(output, "%02x",  HIGH(parsed_offset + 1));
		} else {
			fprintf(output, "%02x ", LOW(parsed_offset));
			fprintf(output, "%02x",  HIGH(parsed_offset));
		}

	} else if (!strcmp(command, "==")) {
		fprintf(output, "00 00");
	} else if (!strcmp(command, ">")) {
		fprintf(output, "01 00");
	} else if (!strcmp(command, "<")) {
		fprintf(output, "02 00");
	} else if (!strcmp(command, ">=")) {
		fprintf(output, "03 00");
	} else if (!strcmp(command, "<=")) {
		fprintf(output, "04 00");
	} else if (!strcmp(command, "!=")) {
		fprintf(output, "05 00");
	} else {
		fprintf(stderr, "Error: Unknown command: %s\n", command);
	}
}

struct Patch *process_template(
	const char *template_filename, FILE *new_rom, FILE *orig_rom,
	const char *output_filename, const struct Symbol *symbols
) {
	FILE *file = xfopen(template_filename, 'r');
	FILE *output = xfopen(output_filename, 'w');

	struct Patch *patches = create_buffer();
	struct Patch *patch = patches;

	// The ROM checksum will always differ
	patch->offset = 0x14e;
	patch->size = 2;
	patch++;
	// The Stadium checksum will always differ
	patch->offset = 0x1FFDE0;
	patch->size = 0xFFFFFF - 0x1FFDE0;
	patch++;

	char *buffer = create_buffer();
	size_t buffer_index = 0;
	const struct Symbol *current_patch = NULL;
	int line_pos = 0;

	// Fill in the template
	for (int c = getc(file); c != EOF; c = getc(file)) {
		buffer = expand_buffer(buffer, buffer_index);

		switch (c) {
		case '\r':
		case '\n':
			// A newline simply resets the line_pos
			putc(c, output);
			line_pos = 0;
			break;

		case '{':
			// Check if we've found two of them
			c = getc(file);
			if (c != '{') {
				putc('{', output);
				line_pos++;
				ungetc(c, file);
				break;
			}
			// If we have, we store the contents before it ends into buffer
			buffer_index = 0;
			for (c = getc(file); c != EOF; c = getc(file)) {
				if (c == '}') {
					c = getc(file);
					if (c == EOF || c == '}') {
						break;
					}
				}
				buffer[buffer_index++] = c;
				buffer = expand_buffer(buffer, buffer_index);
			}
			buffer[buffer_index] = '\0';
			patch->offset = 0;
			interpret_command(buffer, current_patch, symbols, patch, new_rom, orig_rom, output);
			if (patch->offset) {
				patch++;
			}
			patches = expand_buffer(patches, (uintptr_t)patch - (uintptr_t)patches);
			break;

		case '[':
			// End immediately if this is not the beginning of the line
			if (line_pos) {
				putc(c, output);
				line_pos++;
				break;
			}
			// Try to read the label
			putc(c, output);
			buffer_index = 0;
			for (c = getc(file); c != EOF; c = getc(file)) {
				putc(c, output);
				if (c == ']') {
					// If we're at the end, we can get the symbol for the label
					buffer[buffer_index] = '\0';
					// Translate spaces to underscores
					for (char *p = buffer; *p != '\0'; p++) {
						if (*p == ' ') {
							*p = '_';
						}
					}
					// Look for the symbol starting with .VC_
					char *searchlabel = xmalloc(strlen(".VC_") + strlen(buffer) + 1);
					strcpy(searchlabel, ".VC_");
					strcat(searchlabel, buffer);
					current_patch = find_symbol(symbols, searchlabel);
					if (!current_patch) {
						fprintf(stderr, "Error: Cannot find symbol: %s\n", searchlabel);
					}
					free(searchlabel);
					// Skip until the next newline
					for (c = getc(file); c != EOF; c = getc(file)) {
						putc(c, output);
						if (c == '\n' || c == '\r') {
							break;
						}
					}
					buffer_index = 0;
					break;
				}
				buffer[buffer_index++] = c;
			}
			break;

		default:
			putc(c, output);
			line_pos++;
		}
	}

	patch->offset = 0;

	rewind(orig_rom);
	rewind(new_rom);

	fclose(file);
	fclose(output);
	free_buffer(buffer);
	return patches;
}

int compare_patch(const void *patch1, const void *patch2) {
	unsigned int patch1_offset = ((const struct Patch *)patch1)->offset;
	unsigned int patch2_offset = ((const struct Patch *)patch2)->offset;
	return patch1_offset > patch2_offset ? 1 : patch1_offset < patch2_offset ? -1 : 0;
}

bool verify_completeness(FILE *orig_rom, FILE *new_rom, struct Patch *patches) {
	struct Patch *patch = patches;
	while (patch->offset) {
		patch++;
	}
	qsort(patches, patch - patches, sizeof(struct Patch), compare_patch);
	patch = patches;

	int orig_byte, new_byte;

	for (size_t offset = 0; ; offset++) {
		orig_byte = getc(orig_rom);
		new_byte = getc(new_rom);
		if (orig_byte == EOF || new_byte == EOF) {
			break;
		}
		if (patch->offset && patch->offset == offset) {
			if (fseek(orig_rom, patch->size, SEEK_CUR)) {
				return false;
			}
			if (fseek(new_rom, patch->size, SEEK_CUR)) {
				return false;
			}
			offset += patch->size;
			patch++;
			continue;
		}
		if (orig_byte != new_byte) {
			fprintf(stderr, "Value mismatch at decimal offset: %li\n", offset - 1);
			fprintf(stderr, "Original ROM value: %x\n", orig_byte);
			fprintf(stderr, "Patched ROM value: %x\n", new_byte);
			fprintf(stderr, "Current patch start address: %x\n", patch->offset);
			return false;
		}
	}

	return orig_byte == new_byte;
}

int main(int argc, char *argv[]) {
	if (argc != 7) {
		usage_exit(1);
	}

	struct Symbol *symbols = parse_symfile(argv[2]);
	symbols = parse_constfile(argv[1], &symbols);

	FILE *new_rom = xfopen(argv[3], 'r');
	FILE *orig_rom = xfopen(argv[4], 'r');
	struct Patch *patches = process_template(argv[5], new_rom, orig_rom, argv[6], symbols);

	free_symbols(symbols);

	if (!verify_completeness(orig_rom, new_rom, patches)) {
		fprintf(stderr, "Warning: Not all ROM differences are defined by \"%s\"\n", argv[6]);
	}

	fclose(new_rom);
	fclose(orig_rom);
	free_buffer(patches);

	return 0;
}
