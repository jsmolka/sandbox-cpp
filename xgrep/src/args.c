#include "args.h"

#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

Args *args_alloc()
{
    Args *this = (Args *)malloc(sizeof(Args));
    this->file = NULL;
    this->dir = NULL;
    this->ext = NULL;
    this->key = NULL;
    this->threads = 1;
    this->sensitive = true;
    this->help = false;

    return this;
}

void args_parse(Args *this, int argc, char *argv[])
{
    struct option options[] =
    {
        {"file",      required_argument, 0, 'f'},
        {"dir",       required_argument, 0, 'd'},
        {"extension", required_argument, 0, 'e'},
        {"threads",   required_argument, 0, 't'},
        {"cwd",       no_argument,       0, 'w'},
        {"case",      no_argument,       0, 'i'},
        {"help",      no_argument,       0, 'h'}
    };

    opterr = 0;
    int index = 0;
    int opt;
    while (optind < argc)
    {
        if ((opt = getopt_long(argc, argv, "f:d:e:t:wih", options, &index)) != -1)
        {
            switch (opt)
            {
            case 'f':
                this->file = strtowcs(optarg);
                break;

            case 'd':
                this->dir = strtowcs(optarg);
                break;

            case 'e':
                this->ext = strtowcs(optarg);
                break;

            case 't':
                this->threads = fmax(strtol(optarg, 0, 10), 1);
                break;

            case 'i':
                this->sensitive = false;
                break;

            case 'w':
                this->dir = getcwd();
                break;

            case 'h':
                this->help = true;
                break;

            case '?':
                break;

            default:
                break;
            }
        }
        else
        {
            this->key = argv[optind++];
        }
    }
}

bool args_valid(const Args *this, int argc, char *argv[])
{
    if (argc == 1 || this->help)
    {
        printf("Usage: %s [options] key\n", argv[0]);
        printf("\n");
        printf("Options:\n");
        printf("-f [str]: file\n");
        printf("-d [str]: directory\n");
        printf("-e [str]: file extension\n");
        printf("-t [int]: thread count\n");
        printf("-w: parse working directory\n");
        printf("-i: case insensitive matching\n");
        printf("-h: print (this) help\n");
        printf("\n");
        printf("%s requires at least one of -f, -d, -w and the key\n", argv[0]);
        return false;
    }
    if (!((this->file || this->dir) && this->key))
    {
        printf("Invalid argument combination, see '%s -h'\n", argv[0]);
        return false;
    }
    if (this->file && !isfile(this->file))
    {
        printf("\"%S\" is not a file\n", this->file);
        return false;
    }
    if (this->dir && !isdir(this->dir))
    {
        printf("\"%S\" is not a dir\n", this->dir);
        return false;
    }
    return true;
}

void args_free(Args *this)
{
    if (this->dir) 
        free(this->dir);
    if (this->file) 
        free(this->file);
    if (this->ext) 
        free(this->ext);
    if (this->key) 
        free(this->key);
    free(this);
}
