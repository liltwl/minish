
#include "minishell.h"

int main(int argc, char * argv[])
{  	decouper(getenv("PATH"), ":", dirs, MaxDirs);			
  	for(printf(PROMPT); fgets(ligne, sizeof ligne, stdin) != 0; printf(PROMPT))
	{	decouper(ligne, " \t\n", mot, MaxMot);				
		if (mot[0] == 0)            						
      	continue;	
		if (strcmp(mot[0], "moncd") == 0)					
		{	if (mot[1] == NULL)								
			{	dir = getenv("HOME");
				if (dir == 0)
				{	dir = "/tmp";
				}
			}
			else if (mot[2] != NULL)						
			{	fprintf(stderr, "usage: %s [dir]\n", mot[0]);
				continue;
			}	
			else dir = mot[1];								
			t = chdir(dir);
			if (t < 0)
			{	perror(dir);
			}	
			continue;
		}
		for (cmp = 0; mot[cmp]; cmp++)
		{	if(mot[cmp] != NULL && strcmp(mot[cmp], tube) == 0)
			{	mot[cmp] = NULL;
				mot2[0] = mot[cmp + 1];
				mot2[1] = NULL;
				if (pipe(pfd) == -1)
				{	perror("pipe");
					continue;
				}
				if ((tmp = fork()) < 0)
				{	perror("fork");
					continue;
				}
				if (tmp == 0)
				{	close(STDOUT_FILENO);
					dup(pfd[1]);
					close(pfd[0]);
					close(pfd[1]);
					for(i = 0; dirs[i] != 0; i++)
					{	snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
      					execv(pathname, mot);
					}
				}
				else
				{	close(STDIN_FILENO);
					dup(pfd[0]);
					close(pfd[0]);
					close(pfd[1]);
					for(i = 0; dirs[i] != 0; i++)
					{	snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot2[0]);
      					execv(pathname, mot2);
					}
				}
			}
		}
 
		verif_esperluette();						
		verif_redirection();						
 
		tmp = fork();               
    	if (tmp < 0)
		{	perror("fork");
      		continue;
    	}
 
 
		if ((tmp != 0) && (test == 1))
		{	while(wait(0) != tmp);
			continue;
		}
		if((tmp != 0) && (test == 0))
		{	continue;
		}
 
 
		if (fichier_1 == 1)
		{	out = freopen(path_out, "w+", stdout);
		}
		if ((fichier_1 == 1) && (fichier_2 == 1))
		{	in = freopen(path_in, "r", stdin);
			out = freopen(path_out, "w+", stdout);
		}
		if (fichier_2 == 1)
		{	in = freopen(path_in, "r", stdin);
		}
 
 
    	for(i = 0; dirs[i] != 0; i++)
		{	snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
      		execv(pathname, mot);
    	}
 
		fprintf(stderr, "%s: not found\n", mot[0]);
	    exit(1);
  	}
  	printf("Bye\n");
  	return 0;
}

int
main(int argc, char *argv[])
{
    int pfd[2];
    pid_t cpid;
    char buf;
    assert(argc == 2);
    if (pipe(pfd) == -1) { perror("pipe"); exit(EXIT_FAILURE); }
    cpid = fork();
    if (cpid == -1) { perror("fork"); exit(EXIT_FAILURE); }
    if (cpid == 0) {    /* Child reads from pipe */
        close(pfd[1]);          /* Close unused write end */
        while (read(pfd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1);
        close(pfd[0]);
        _exit(EXIT_SUCCESS);
    } else {            /* Parent writes argv[1] to pipe */
        close(pfd[0]);          /* Close unused read end */
        write(pfd[1], argv[1], strlen(argv[1]));
        close(pfd[1]);          /* Reader will see EOF */
        wait(NULL);             /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}
