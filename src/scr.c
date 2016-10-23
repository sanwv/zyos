#include <scr.h>
#include <asm.h>

static int csr_x = 0;
static int csr_y = 0;
void set_cursor(int x, int y){
    csr_x = x;
    csr_y = y;
    outb(0x3d4, 0x0e);
    outb(0x3d5, csr_x+csr_y*MAX_COLUMNS);
    outb(0x3d4, 0x0f);
    outb(0x3d5, csr_x+csr_y*MAX_COLUMNS);
}
void print_c(char c, COLOUR fg, COLOUR bg){
    char *p;
    char attr;
    p = (char *) VIDEO_RAM + CHAR_OFF(csr_x, csr_y);
    attr = (char) (bg<<4|fg);
    switch ( c ){
        case '\r':
            csr_x = 0;
            break;
        case '\n':
            break;
        case '\t':
            break;
        case '\b':
            break;
        default:
            *p++ = c;
            *p =attr;
            ++csr_x;
            break;
    }
    if (csr_x>=MAX_COLUMNS){
        csr_x = 0;
        if (csr_y < MAX_LINES-1){
            ++csr_y;
        }
    }
    set_cursor(csr_x, csr_y);
}
