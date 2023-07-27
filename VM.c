#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "const.h"
#include "type.h"

typedef char * path;

#define BUF_SIZE (int)2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2-1 // Buffer size

#define min(a,b) ((a)<(b)?(a):(b))
#define genptr(sz,base) (byte*)(((sz)[1]<<8)+(sz)[0]+base-1)

static byte buf [BUF_SIZE];
static struct stat *file_stat;

int main(int argc, char **argv){
        byte *memory;
        unsigned long size;
        FILE *file;
        int mem_size;
        byte *ptr;
        assert(argc==2);
        { /* Read file */
                path filepath = argv[1];
                file = fopen(filepath, "rb");
                assert(stat(filepath, file_stat)==0);
                if (file == NULL){
                        perror("File not exist.");
                        abort();
                }
                size = fread(buf, sizeof(u8), BUF_SIZE, file);
                assert(size == min((unsigned long)file_stat->st_size, BUF_SIZE));
        }
        ptr = buf;
        if(*ptr != ACTION_START){
                perror(
                        "RUNTIME ERROR: HEADER ERROR\n"
                        "Send error report, please.\n"
                        "POS:VM.c:40"
                );
                abort();
        }
        mem_size = *++ptr;
        memory=malloc(*ptr);
        {
                byte args[4];
                for (; ptr<(buf+sizeof(buf)); ++ptr){
                        switch (*ptr){
                                case ACTION_READ:
                                        args[0] = *++ptr; /* memory_id */
                                        if (args[0] >= mem_size){
                                                perror(
                                                        "RUNTIME ERROR: MEM LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:56"
                                                );
                                                abort();
                                        }
                                        scanf("%s", memory+args[0]);
                                        break;
                                case ACTION_INC:
                                        args[0] = *++ptr; /* memory_id */
                                        if (args[0] >= mem_size){
                                                perror(
                                                        "RUNTIME ERROR: MEM LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:68"
                                                );
                                                abort();
                                        }
                                        ++memory[args[0]];
                                        break;
                                case ACTION_DEC:
                                        args[0] = *++ptr; /* memory_id */
                                        if (args[0] >= mem_size){
                                                perror(
                                                        "RUNTIME ERROR: MEM LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:80"
                                                );
                                                abort();
                                        }
                                        --memory[args[0]];
                                        break;
                                case ACTION_OUTPUT:
                                        args[0]=*++ptr;
                                        if (args[0] >= mem_size){
                                                perror(
                                                        "RUNTIME ERROR: MEM LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:92"
                                                );
                                                abort();
                                        }
                                        printf("%d", memory[args[0]]);
                                        break;
                                case ACTION_ASCII:
                                        args[0]=*++ptr;
                                        if (args[0] >= mem_size){
                                                perror(
                                                        "RUNTIME ERROR: MEM LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:104"
                                                );
                                                abort();
                                        }
                                        printf("%c", memory[args[0]]);
                                        break;
                                case ACTION_JMP:
                                        memcpy(args, ++ptr, 2);
                                        if (args[0] >= file_stat->st_size){
                                                perror(
                                                        "RUNTIME ERROR: RAP LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:116"
                                                );
                                                abort();
                                        }
                                        ptr = genptr(args, memory);
                                        break;
                                case ACTION_JLS:
                                        memcpy(args, ++ptr, 4);
                                        if (args[0] >= file_stat->st_size){
                                                perror(
                                                        "RUNTIME ERROR: RAP LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:128"
                                                );
                                                abort();
                                        }
                                        if (memory[args[2]]<memory[args[3]]){
                                                ptr = genptr(args, memory);
                                        }
                                        break;
                                case ACTION_JLE:
                                        memcpy(args, ++ptr, 4);
                                        if (args[0] >= file_stat->st_size){
                                                perror(
                                                        "RUNTIME ERROR: RAP LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:142"
                                                );
                                                abort();
                                        }
                                        if (memory[args[2]]<memory[args[3]]){
                                                ptr = genptr(args, memory);
                                        }
                                        break;
                                case ACTION_JGT:
                                        memcpy(args, ++ptr, 4);
                                        if (args[0] >= file_stat->st_size){
                                                perror(
                                                        "RUNTIME ERROR: RAP LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:156"
                                                );
                                                abort();
                                        }
                                        if (memory[args[2]]>memory[args[3]]){
                                                ptr = genptr(args, memory);
                                        }
                                        break;
                                case ACTION_JGE:
                                        memcpy(args, ++ptr, 4);
                                        if (args[0] >= file_stat->st_size){
                                                perror(
                                                        "RUNTIME ERROR: RAP LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:170"
                                                );
                                                abort();
                                        }
                                        if (memory[args[2]]<memory[args[3]]){
                                                ptr = genptr(args, memory);
                                        }
                                        break;
                                case ACTION_JEQ:
                                        memcpy(args, ++ptr, 4);
                                        if (args[0] >= file_stat->st_size){
                                                perror(
                                                        "RUNTIME ERROR: RAP LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:184"
                                                );
                                                abort();
                                        }
                                        if (memory[args[2]]==memory[args[3]]){
                                                ptr = genptr(args, memory);
                                        }
                                        break;
                                case ACTION_JNE:
                                        memcpy(args, ++ptr, 4);
                                        if (args[0] >= file_stat->st_size){
                                                perror(
                                                        "RUNTIME ERROR: RAP LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:198"
                                                );
                                                abort();
                                        }
                                        if (memory[args[2]]!=memory[args[3]]){
                                                ptr = genptr(args, memory);
                                        }
                                        break;
                                default:
                                        perror(
                                                "RUNTIME ERROR: ACTION ERROR\n"
                                                "Send error report, please.\n"
                                                "POS:VM.c:210"
                                        );
                                        abort();
                        }
                }
        }
}
