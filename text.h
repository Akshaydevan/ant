#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>

int getkey(void);
char **initmemory(void);
void setmem(char,int,int);
char getmem(int,int);
void shiftmem(int,int,int,int);
int len(char **);
int memlen(char *);
int linelen(int);
void meminc(char *,int);
void linesinc(void);
void insert_line(int);
int merge_line(int);
void split_line(int,int);
void memfree(char **);
void memclear();
void paint(int,int,int);
void initkey(void);
void exitkey(void);
void getbuff(void);
void resize(int);

int file_size;
int x,y;
char file_name[10];
int resized;

#define input_block_off   fcntl(1,F_SETFL,O_NONBLOCK)
#define input_block_on   fcntl(1,F_SETFL,2)
#define move(i,j)   printf("%c[%d;%dH",27,j,i)
#define DelKey 133
#define LeftKey 132
#define RightKey 131
#define DownKey 130
#define UpKey 129
#define EscKey 127
#define BackspaceKey 128
#define EnterKey 13
#define SaveShortcut 19
#define SpaceKey 32
#define OpenShortcut 15
#define ClipBoard 16

#define halt while(getchar()!='q'){}
