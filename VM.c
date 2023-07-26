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
                        "POS:VM.c:41"
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
                                                        "POS:VM.c:54"
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
                                                        "POS:VM.c:66"
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
                                                        "POS:VM.c:18"
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
                                                        "POS:VM.c:90"
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
                                                        "POS:VM.c:102"
                                                );
                                                abort();
                                        }
                                        printf("%c", memory[args[0]]);
                                        break;
                                case ACTION_JMP:
                                        memcpy(args, ++ptr, 2);
                                        if (args[0] >= file_stat->st_size){
                                                perror(
                                                        "RUNTIME ERROR: MEM LIMIT ERROR\n"
                                                        "Send error report, please.\n"
                                                        "POS:VM.c:102"
                                                );
                                                abort();
                                        }
                                        ptr = (byte*)((args[1]<<8)+args[0]+buf);
                                        break;
                                case ACTION_JLS:
                                        /* TODO */
                                        break;
                                case ACTION_JLE:
                                        /* TODO */
                                        break;
                                case ACTION_JGT:
                                        /* TODO */
                                        break;
                                case ACTION_JGE:
                                        /* TODO */
                                        break;
                                case ACTION_JEQ:
                                        /* TODO */
                                        break;
                                case ACTION_JNE:
                                        /* TODO */
                                        break;
                                default:
                                        perror(
                                                "RUNTIME ERROR: ACTION ERROR\n"
                                                "Send error report, please.\n"
                                                "POS:VM.c:???"
                                        );
                                        abort();
                        }
                }
        }
}
