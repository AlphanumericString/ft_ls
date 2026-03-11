#include <stdio.h>
#include <dirent.h>
#include <strings.h>
#include <sys/stat.h>

#include "ft_vector.h"
#include "ft_string.h"
#include "ft_mem.h"

#include "ft_ls.h"

void    dump_dirent(void *a){
    struct dirent_stated    *ds = (struct dirent_stated *)a;
    struct dirent        d = ds->d;
    struct stat            s = ds->s;

    printf("%p\t%25s\t%8lu\t%10lu\t%10lu\t%30s\n", (void *)ds, ds->name, d.d_ino, s.st_mtim.tv_sec, s.st_mtim.tv_nsec, ds->full_name);
}
void    dump_only_name(void *a){
    struct dirent_stated    *ds = (struct dirent_stated *)a;
    printf("%s\n", ds->name);
}
void    clear_entries(void *a){
    struct dirent_stated    *ds = (struct dirent_stated *)a;

    ft_free(ds->full_name);
    ft_free(ds->name);
}
int        cmp_mtim(const void *a, const void *b){
    struct dirent_stated    *ds_a = (struct dirent_stated *)a;
    struct dirent_stated    *ds_b = (struct dirent_stated *)b;
    const char                *name_a = ds_a->name;
    const char                *name_b = ds_b->name;

    if (ds_a->s.st_mtim.tv_sec != ds_b->s.st_mtim.tv_sec)
        return (ds_b->s.st_mtim.tv_sec - ds_a->s.st_mtim.tv_sec);
    if (ds_a->s.st_mtim.tv_nsec != ds_b->s.st_mtim.tv_nsec)
        return (ds_b->s.st_mtim.tv_nsec - ds_a->s.st_mtim.tv_nsec);
    if (name_a[0] == '.')
        name_a++;
    if (name_b[0] == '.')
        name_b++;
    return (strcasecmp(name_a, name_b));
}
