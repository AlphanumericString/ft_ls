# FT_LS

## Table Of Content
(The project)[]
(Restrictions)[]
(Difficulties)[]
(Solutions)[]

## The Project

The project ft_ls is as its name would suggest a project that aims to re-implement the ls shell command in linux.
To be more precise the only the options 'l' 'R' 'a' 'r' and 't' are mandatory.
The other options eg 'u' 'f' 'g' 'd' and others are bonuses.

### option

#### mandatory
| short option | long option | effect|
| -------------- | ----- | --------------- |
| 'l' | | use the long format for display |
| 'R' | "recursive" | list subdirectories recursively |
| 'a' | "all" | do not ignore files starting with . |
| 'r' | "reverse"  | reverse the order after sorting |
| 't' | | sort by time (mtime), newest first |

#### bonuses
| short option | long option | effect|
| -------------- | -------------- | --------------- |
| 'A' | "almost-all" | same 'a' except ignores '.' and '..' |
| 'B' | "ignore-backups" | skip files ending with '~' |
| 'c' | | with lt: sort by ctime, show ctime; with l: show ctime, sort unchanged; with : sort by ctime |
| 'd' | "directory" | list directory themselves not their content |
| 'F' | | append indicator(*/=>@\|) to entries (eg: / at end of dir names) |
| | "file-type" | same as 'F' except do not append '*' to executables |
| 'g' | | same as 'l' but skips owner field |
| 'G' | "no-group" | skip any group fields |
| | "group-directories-first" | as its name implies |
| 'h' | "human-readable" | with -l and -s : print sizes like 1K, 235M, 32G |
|  | "si" | likewise but use multiples of 1000 instead of 1024 |
| 's' | "size" | print the allocated size of each files in blocks |
| 'S' | | sort by sizes, largest fisrt |
| | "help" | print help |


## TODO
cleanup main struct:
mandatory no bonus version:
    print_range = [ all, default (skip \..*) ]
    recursive = [ true, false (default) ]
    format_display = [ long, names (default)]
    sort_order = [ mtime, alpha (default)]
    order_modifier = [ reverse, none (default)]
bonuses:
    print_range = [ all, almost-all, default (skip \..*) ]
    skip_backups = [ true, false (default) ]
    recursive = [ true, false (default) ]
    format_display = [ long, sizes, names (default)]
    print_modifier = [ no_groups, append_all, append_skip_exe, ctime, human_sizes, power_sizes]
    sort_order = [ alpha, ctime, sizes, mtime]
    order_modifier = [ reverse, dir_first]

TODO:
[x] implement mandatory version of the struct
[x] implement parser for args
[x] implement recursive
[x] files - sort && print
[ ] replace printf's call
[x] norming
[ ] take correction on project
