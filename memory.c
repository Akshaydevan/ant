#include"text.h"

char **lines;
int buffersize =10;
char **initmemory(){
    int i = 0;
    char *line;
    lines = calloc(sizeof(char*),10);
    while(i<=0){
        line = calloc(sizeof(char),70+4);
        line[0] = 70;
        lines[i++] = line+4;
    }
    return lines;
}

void setmem(char c,int x,int y){
    if(memlen(lines[y])==x-5)
        meminc(lines[y],y);
    lines[y][x] = c;
}

char getmem(int x,int y){
    if(lines[y] == 0 || y<0)
        return -1;
    return lines[y][x];
}

void shiftmem(int sx,int sy,int dx,int dy){
    memmove(&lines[dy][dx],&lines[sy][sx],strlen(&lines[sy][sx])+1);
}

int len(char **a){
    int i = 0;
    while(*a++ != 0)
        i++;
    return i;
}

int memlen(char *a){
    a -= 4;
    //printf("%d\n",*((int*)a));
    return *((int*)a);
}

int linelen(int y){
    return strlen(&lines[y][0]);
}

void meminc(char *a,int pos){
    a -= 4;
    lines[pos] = realloc(a,memlen(a+4)+35);
    lines[pos][0] = (memlen(lines[pos]+4) + 35);
    lines[pos] += 4;
}

void linesinc(){
    char **temp = calloc(sizeof(char *),buffersize+20);
    memcpy(&temp[0],&lines[0],len(lines)*sizeof(char *));
    free(lines);
    lines = temp;
    buffersize += 20;
}

void memfree(char **a){
    char *b = *a - 4;
    free(b);
}

void memclear(){
    int j = 0;
    int k;
    while(getmem(0,j) != -1){
        memfree(&lines[j]);
        j++;
    }
    free(lines);
}


void insert_line(int pos){
    char *line;
    if(len(lines)%10 == 9)
        linesinc();
    memmove(&lines[pos+2],&lines[pos+1],len(&lines[pos+1])*sizeof(char *));
    line = calloc(sizeof(char),70+4);
    line[0] = 70;
    lines[pos+1] = line+4;
}

int merge_line(int curt){
    int prev = curt -1;
    int l1 = strlen(&lines[curt][0]);
    int l2 = strlen(&lines[prev][0]);
    if(l1+l2 > memlen(lines[prev])){
        meminc(lines[prev],prev);
    }
        memcpy(&lines[prev][l2],&lines[curt][0],l1);
        memfree(&lines[curt]);
        memcpy(&lines[curt],&lines[curt+1],(len(&lines[curt+1])+1)*sizeof(char *));
    return l2;
}

void split_line(int x,int y){
    int len = strlen(&lines[y][x]);
    insert_line(y);
    if(len > 70){
        meminc(lines[y+1],y+1);
    }
        memcpy(&lines[y+1][0],&lines[y][x],len);
        memcpy(&lines[y][x],"\0",len);
}
