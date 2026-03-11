#include <dirent.h>
#include <stdio.h>
#include "ft_defs.h"
#include "ft_mem.h"
#include "ft_vector.h"
#include "ft_string.h"
#include "ft_ls.h"



static int	parse_opt(t_ls_state *ctx, char **args, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_strcmp(args[i], "--") == 0)
			break ;
		if (args[i][0] == '-' && args[i][1] == '-'){
			//	parse_long(args[i], args, ctx);
		} else if (args[i][0] == '-') {
			//	parse_shrt(args[i], args, ctx);
			size_t j = 1;
			for (; args[i][j]; j++)
				switch (args[i][j]) {
					case 'l':
						ctx->long_fmt = true;
						break;
					case 'R':
						ctx->recursive = true;
						break;
					case 'r':
						ctx->reverse = true;
						break;
					case 'a':
						ctx->all = true;
						break;
					case 't':
						ctx->sort_time = true;
						break;
					default:
						printf("unknown option :%c\n", args[i][j]);
						return (1);
				}
		}
		else {
			ft_vec_add(ctx->files_target, &args[i]);
		}
		i++;
	}

#ifdef DEBUG
	printf("options :\n");

	printf("skip_self_par:%s\n", ctx->skip_self_par ? "true" : "false");
	printf("skip_hiden:%s\n", ctx->skip_hiden ? "true" : "false");
	printf("skip_backups:%s\n", ctx->skip_backups ? "true" : "false");

	printf("only_dir_themselves:%s\n", ctx->only_dir_themselves ? "true" : "false");

	printf("append_type:%s\n", ctx->append_type ? "true" : "false");
	printf("skip_apend_exe:%s\n", ctx->skip_apend_exe ? "true" : "false");

	printf("long_fmt:%s\n", ctx->long_fmt ? "true" : "false");
	printf("skip_owner:%s\n", ctx->skip_owner ? "true" : "false");
	printf("skip_groups:%s\n", ctx->skip_groups ? "true" : "false");
	printf("size:%s\n", ctx->size ? "true" : "false");
	printf("ib_sizes:%s\n", ctx->ib_sizes ? "true" : "false"); // 1000 instead of 1024
	printf("hr_sizes:%s\n", ctx->hr_sizes ? "true" : "false");

	printf("dirs_first:%s\n", ctx->dirs_first ? "true" : "false");

	printf("sort_size:%s\n", ctx->sort_size ? "true" : "false");
	printf("sort_time:%s\n", ctx->sort_time ? "true" : "false"); // mtime

	printf("reverse:%s\n", ctx->reverse ? "true" : "false");
	printf("recursive:%s\n", ctx->recursive ? "true" : "false");
	printf("all:%s\n", ctx->all ? "true" : "false");
#endif

	return (0);
}

static int	ls_single_dir(const char *dir, const t_ls_state *ctx)
{
	DIR						*d = opendir(dir);
	struct dirent			*d_entry;
	struct dirent_stated    ds;
	t_vector				*vec_entries;

	if (!d)
		return (printf("%s: cannot access '%s': %m\n", "ft_ls", dir), 1);
	vec_entries = ft_vec_create(sizeof(struct dirent_stated));
	while ((d_entry = readdir(d)) != NULL) {
		ds.d = *d_entry;
		if (ds.d.d_name[0] == '.' && ctx->all != true)
			continue;
		ds.full_name = ft_strjoin(dir, ds.d.d_name);
		ds.name = ft_strdup(ds.d.d_name);
		if (stat(ds.full_name, &ds.s) < 0)
			ds.s = (struct stat){0};
		ft_vec_add(vec_entries, &ds);
	}
#ifdef DEBUG
	printf("before sort:\n");
	ft_vec_apply(vec_entries, dump_dirent);
#endif
	if (ctx->sort_time)
		ft_vec_sort(vec_entries, cmp_mtim);
#ifdef DEBUG
	printf("after sort:\n");
	ft_vec_apply(vec_entries, dump_dirent);
#endif
	ft_vec_apply(vec_entries, dump_only_name);
	ft_vec_apply(vec_entries, clear_entries);
	return (ft_vec_destroy(&vec_entries), closedir(d), 0);
}

static int	ft_cmp_iterator(void *a, void *b)
{
	return (ft_strcmp(*(char **)a, *(char **)b));
}

static bool	is_unreachable(void *a)
{
	DIR		*d;

	d = opendir(*(char **)a);
	if (!d)
		return (printf("%s: cannot access '%s': %m\n", "ft_ls", *(char **)a), 1);
	return (closedir(d), 0);
}

int main(int ac, char **av) {
	const char	*d_name = "./";
	t_ls_state	state;
	struct stat	s;
	size_t i;

	state = (t_ls_state){0};
	state.files_target = ft_vec_create(sizeof(const char *));
	if (parse_opt(&state, av, ac) != 0)
		return (ft_vec_destroy(&state.files_target), 1);
	if (!state.files_target->n_e)
		ls_single_dir(d_name, &state);
	ft_vec_sort(state.files_target, (t_data_cmp)ft_cmp_iterator);
	ft_vec_filterout(state.files_target, (t_data_is)is_unreachable, NULL);
	i = 0;
	while (i < state.files_target->n_e) {
		if (stat(*(char **)ft_vec_at(state.files_target, i), &s) != -1)
			printf("%s:\n", *(char **)ft_vec_at(state.files_target, i));
		ls_single_dir(*(char **)ft_vec_at(state.files_target, i++), &state);
		if (i < state.files_target->n_e)
			printf("\n");
	}
	return (ft_vec_destroy(&state.files_target), 0);
}
