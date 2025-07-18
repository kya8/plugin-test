#include <stdio.h>
#include <export.h>

/* ANSI color codes */
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define MAGENTA "\x1b[35m"
#define WHITE   "\x1b[37m"

static void print_color_cat(void) {
    puts(CYAN    "      |\\_/|        " RESET);
    puts(MAGENTA "     /     \\       " RESET);
    puts(WHITE   "    /  . .  \\      " RESET);
    puts(MAGENTA "   =\\   T   /=      " RESET);
    puts(CYAN    "     )     (        " RESET);
    puts(YELLOW  "    /       \\      " RESET);
    puts(RED     "   (         )      " RESET);
    puts(GREEN   "    \\  \\_/  /     " RESET);
    puts(WHITE   "     \\_____/       " RESET);
    puts(MAGENTA "    /       \\      " RESET);
    puts(CYAN    "   /         \\     " RESET);
    puts(YELLOW  "  (           )     " RESET);
    puts(RED     "   \\         /     " RESET);
    puts(GREEN   "    `-.___,-'       " RESET);
    // This cat has fluffy tail!
}

PLUGIN_API void plugin_func(void)
{
    print_color_cat();
}
