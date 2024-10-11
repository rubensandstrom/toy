#ifndef BASE_H
#define BASE_H

// MACROS
#define KB          (1<<10)
#define MB          (1<<20)
#define GB          (1<<30)
#define TB          (1<<40)
#define PAGESIZE    (4*KB)

#define STRING(CP) (string){.data = CP, .length = sizeof(CP) - 1}

// TYPEDEFS
typedef struct {
    char *data;
    uint32_t length;
    uint32_t capacity;
} string_builder;

typedef struct string {
    char *data;
    uint32_t length;
} string;

typedef enum {
    INFO,
    WARN,
    ERROR,
    FATAL,
    TRACE,
    DEBUG,
} log_level;

// FUNCTIONS
void __stack_chk_fail(void);


void sb_write_string(string_builder *sb, string s);
#define sb_write(sb, cp) sb_write_string(sb, (string){.data = cp, .length = sizeof(cp) - 1})

string sb_string(string_builder *sb);

static void _sb_log(string_builder *sb, log_level level, string s);
#define sb_log(sb, level, cp) _sb_log(sb, level, (string){.data = cp, .length = sizeof(cp) - 1})

void print(string s);
#define cp_print(S) print((string){.items = (S), .count = sizeof((S)) - 1})
void panic(string s);
#define cp_panic(S) panic((string){.items = (S), .count = sizeof((S)) - 1})

bool sb_read_file(string_builder *sb, const char *path);

#define builder_to_iter(builder) {(builder)->items, 0, (builder)->count}
#define peek(iter, offset) (iter)->items[(iter)->count + (offset)]
#define eat(iter) (iter)->items[(iter)->count++]

string_builder sb_init();

bool string_eq(string *s1, string *s2);
#endif
