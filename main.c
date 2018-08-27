#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

char			*ft_itoa_base(int num, int base)
{
	int			len;
	char		*str;
	long long	value;
	char		*tab;

	tab = "0123456789abcdef";
	value = num;
	len = (value < 0 && base == 10) ? 1 : 0;
	value = (value < 0) ? (-1 * value) : value;
	while (value /= base)
		len++;
	value = num;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (value < 0 && base == 10)
		str[0] = '-';
	if (value < 0)
		value = value * -1;
	while (value > 0)
	{
		str[len] = tab[value % base];
		value /= base;
		len--;
	}
	return (str);
}

typedef struct s_options
{
	int l;
	int R;
	int a;
	int r;
	int t;
	char *dir_name;
} t_options;

void reset_options(t_options *opt)
{
	opt->l = 0;
	opt->R = 0;
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->dir_name = NULL;
}

size_t ft_strlen(const char *str)
{
	int len;

	len = 0;
	while(str[len])
		len++;
	return (len);
}

char *ft_strdup(const char *str)
{
	int i;
	char *new;

	new = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	i = -1;
	while (str[++i])
	{
		new[i] = str[i];
	}
	new[i] = '\0';
	return (new);
}
char *preppend(char *tmp, char *to_insert)
{
	char *new;
	char *str;
	int len;
	int i;

	str = ft_strdup(tmp);
	len = ft_strlen(str) + ft_strlen(to_insert);
	new = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (*to_insert)
	{
		new[i] = *to_insert;
		i++;
		to_insert++;
	}
	while (*str)
	{
		new[i] = *str;
		str++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

void get_options(t_options *opt, char *str)
{
	int i;
	i = 0;

	if (*str == '-')
	{
		str++;
		while (*str)
		{
			if (*str == 'l')
				opt->l = 1;
			if (*str == 'R')
				opt->R = 1;
			if (*str == 'a')
				opt->a = 1;
			if (*str == 'r')
				opt->r = 1;
			if (*str == 't')
				opt->t = 1;
			str++;
		}
	}
	else
		opt->dir_name = ft_strdup(str);
}

int main(int argc, char **argv)
{
	int i;
	char *dir_name;
	DIR *dir;
	struct dirent *sd; //Stuff in the directory
	struct stat info;
	char *permission_str;

	struct passwd *pwd;
	struct group *group;

	char *str = argv[1];
	char *mtime;
	t_options options;

	i = 0;
	reset_options(&options);
	if (argc > 1)
		get_options(&options, str);

	/*--Getting the dir name---*/
	dir_name = (!options.dir_name) ? "." : options.dir_name;
	dir_name = (dir_name != ".") ? preppend(dir_name, "./") : dir_name;
	/*--Getting the dir name---*/
	dir = opendir(dir_name);
	if (dir == NULL)
	{
		printf("%s\n", "Error! Unable to find the directory");
		exit(1);
	}
	while ((sd = readdir(dir)) != NULL)
	{
		stat(sd->d_name, &info);
		lstat(sd->d_name, &info);
		time(&info.st_ctime); // Get the file time
		// printf("%s\n", ctime(&info.st_ctime)); // Get time
		// printf("%i\n", info.st_rdev);
		// if (S_ISDIR(info.st_mode))  //Check if is a directory
		// 	printf("%s is a DIR\n",sd->d_name);
		// if (S_ISREG(info.st_mode)) // Check if is a directory
		// 	printf("%s is a FILE\n",sd->d_name);
		// if (S_ISLNK(info.st_mode))  //Check if is a directory
		pwd = getpwuid(info.st_uid);
		group =  getgrgid(info.st_gid);
		permission_str = ft_itoa_base(info.st_mode, 10) + 2;

		// printf("%s %s %s\n",pwd->pw_name, group->gr_name, ctime(&info.st_ctime) );
		// if (S_ISDIR(info.st_mode))  //Check if is a directory
		printf("%i\n",S_IRWXU(info.st_mode));



			// printf("%ld\n",(long)info.st_uid);
			// printf("%s\n",pwd->pw_name);
			// printf("Group name: %s\n",group->gr_name);
	}
	closedir(dir);
	return (0);
}
