#define _GNU_SOURCE
#include <sys/mman.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "string.h"

string_builder sb_init() {
	return (string_builder){
			.data = mmap(0, PAGESIZE, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0),
			.length = 0,
			.capacity = PAGESIZE,
	};
}

void sb_grow(string_builder *sb) {
	sb->data = mremap(sb->data, sb->capacity, sb->capacity * 2, 1);
	sb->capacity *= 2;
}

void sb_write_string(string_builder *sb, string *s) {
    if (sb->length + s->length >= sb->capacity) {
        sb->data = mremap(sb->data, sb->capacity, sb->capacity * 2, 1);
        sb->capacity *= 2;
    }
    for (int i = 0; i < s->length; i++) {
        sb->data[sb->length] = s->data[i];
        sb->length += 1;
    }
}

void sb_write_char(string_builder *sb, char c) {
	sb->data[sb->length] = c;
	sb->length++;
}

void sb_write_fmt(string_builder *sb, const char *format, ...) {
	
	int i = 0;

	va_list ap;
	va_start(ap, format);

	string s;
	int d;

	char buf[20] = {0};
	int bufindex = 0;
	while (format[i] != '\0') {
		if (format[i] == '%') {
			switch (format[i + 1]) {
				case 's':
					s = va_arg(ap, string);

					while (sb->length + s.length >= sb->capacity) {
						sb_grow(sb);
					}

					sb_write_string(sb, &s);
					i += 2;
					break;
				case 'd':
					d = va_arg(ap, int);
					if (d == 0) {
						sb_write_char(sb, '0');
					} else {
						while (d > 0) {
							buf[bufindex] = d % 10;
							d /= 10;
							bufindex++;
						}
						while (sb->length + bufindex >= sb->capacity) {
							sb_grow(sb);
						}

						while (bufindex > 0) {
							sb_write_char(sb, buf[bufindex - 1] + '0');
							bufindex--;
						}
					}
					bufindex = 0;
					buf[0] = 0;
					i += 2;
					break;
				default:
					panic(STRING("UNKNOWN FORMAT STRING\n"));
			}
		}
		sb_write_char(sb, format[i]);
		i++;
	}
	va_end(ap);
}

bool sb_read_file(string_builder *sb, const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return false;

    uint64_t bytes_read;
    while (1){
        bytes_read = read(fd, sb->data + sb->length, sb->capacity - sb->length);
        if (bytes_read == sb->capacity - sb->length) {
            sb->data = mremap(sb->data, sb->capacity, sb->capacity * 2, MREMAP_MAYMOVE);
            sb->capacity *= 2;
        } else break;
        sb->length += bytes_read;
    }
    sb->length += bytes_read;

    close(fd);
    return 1;
}

string sb_string(string_builder *sb) {
	return (string){
		.data = sb->data,
		.length = sb->length
	};
}

void _sb_log(string_builder *sb, log_level level, string s) {
    switch (level) {
        case INFO:
            sb_write(sb, "\e[34mINFO: \e[0m");
            break;
        case WARN:
            sb_write(sb, "\e[33mWARN: \e[0m");
            break;
        case ERROR:
            sb_write(sb, "\e[31mERROR: \e[0m");
            break;
        default:
            return;
    }
	sb_write_string(sb, &s);
}

void print(string s) {
    write(1, s.data, s.length);
}

void panic(string s) {
    write(2, s.data, s.length);
    exit(1);
}

bool string_eq(string *s1, string *s2) {
	if (s1->length != s2->length){
		return false;
	}
	for (int i = 0; i < s1->length; i++) {
		if (s1->data[i] != s2->data[i]) return false;
	}
	return true;
}
