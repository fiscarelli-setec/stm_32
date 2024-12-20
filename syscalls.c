#include <sys/stat.h>
#include <errno.h>

extern char _end; // Definito dal linker script
static char *heap_end;

void *_sbrk(ptrdiff_t incr) {
    char *prev_heap_end;

    if (heap_end == NULL) {
        heap_end = &_end;
    }

    prev_heap_end = heap_end;
    heap_end += incr;

    return prev_heap_end;
}

int _close(int file) {
    return -1;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _read(int file, char *ptr, int len) {
    return 0;
}

int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        // Implementa l'invio del carattere (ad esempio, tramite UART)
    }
    return len;
}

void _exit(int status) {
    while (1);
}

int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

int _getpid(void) {
    return 1;
}
