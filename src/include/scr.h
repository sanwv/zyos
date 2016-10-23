#ifndef SCR_H
#define SCR_H  

#define MAX_LINES 25
#define MAX_COLUMNS 80
#define TAB_WIDTH 8

#define VIDEO_RAM 0x8000
/*一行占几个字节，两个字节表示一个字符*/
#define LINE_RAM (MAX_COLUMNS*2)

#define PAGE_RAM (MAX_LINES*MAX_COLUMNS)
/*空白字符属性，white fg,black bg = 0x07*/
#define BLANK_CHAR (' ')
#define BLANK_ATTR (0x07)

typedef enum COLOR_TAG {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, WHITE,
	GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_CYAN, 
	LIGHT_RED, LIGHT_MAGENTA, YELLOW, BRIGHT_WHITE
} COLOUR;

void set_cursor(int ,int);
void get_cursor(int *,int *);
void print_c(char, COLOUR, COLOUR);

#endif
