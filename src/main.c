#include <dirent.h>
#include <stdio.h>
#include "ft_vector.h"
#include "ft_string.h"
#include "ft_ls.h"

int main(void) {
	const char        *d_name = "./";
	DIR                *d = opendir(d_name);
	struct dirent    *d_entry;
	struct dirent_stated    ds;
	t_vector        *vec_entries;

	if (!d)
		return (1);
	vec_entries = ft_vec_create(sizeof(struct dirent_stated));
	while ((d_entry = readdir(d)) != NULL) {
		ds.d = *d_entry;
		ds.full_name = ft_strjoin(d_name, ds.d.d_name);
		ds.name = ft_strdup(ds.d.d_name);
		if (stat(ds.full_name, &ds.s) < 0)
			ds.s = (struct stat){0};
		ft_vec_add(vec_entries, &ds);
	}

	printf("%8s\t%25s\t%8s\t%10s\t%10s\t%30s\n", "d", "d_name", "d_ino", "st_mtim.tv_sec", "st_mtim.tv_nsec", "full_name");
	ft_vec_apply(vec_entries, dump_dirent);
	ft_vec_apply(vec_entries, dump_only_name);
	ft_vec_sort(vec_entries, cmp_mtim);

	printf("---\n");
	printf("%8s\t%25s\t%8s\t%10s\t%10s\t%30s\n", "d", "d_name", "d_ino", "st_mtim.tv_sec", "st_mtim.tv_nsec", "full_name");
	ft_vec_apply(vec_entries, dump_dirent);
	printf("---\n");
	ft_vec_apply(vec_entries, dump_only_name);
	ft_vec_apply(vec_entries, clear_entries);
	ft_vec_destroy(&vec_entries);
	closedir(d);
	return 0;
}
