#include <stdlib.h>   
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "minishell.h"

#define MAX_CMD_LENGTH 100

#define MAX_NUM_PARAMS 10

char				**ft_free_split(char **d)
{
	int				i;

	i = 0;
	while (d[i])
	{
		free(d[i]);
		i++;
	}
	//free(d);
	return (NULL);
}

int parsecmd(char* cmd, char** params,char *x) { //split cmd into array of params
    int i,n=-1;
    for(i=0; i<MAX_NUM_PARAMS; i++) {
        params[i] = strsep(&cmd, x);
        n++;
        if(params[i] == NULL) break;
    }
    return(n);
};
static void	get_absolute_path(char **cmd)
{
	char	*path = NULL;
	char	*bin = NULL;
	char * path_split[MAX_NUM_PARAMS+1];

	if (path == NULL) // si le path est null, on cree un path
		path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	// si cmd n'est pas le chemin absolue, on cherche le chemin absolue du
	// binaire grace a la variable d'environment PATH
	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0) {

		// On split le path pour verifier ou ce trouve le binaire
		parsecmd(path,path_split ,  ":");
        //printf("\n%s\n",path_split[0]);
		//free(path);
		path = NULL;

		// On boucle sur chaque dossier du path pour trouver l'emplacement du binaire
		for (int i = 0; path_split[i]; i++) {
			// alloc len du path + '/' + len du binaire + 1 pour le '\0'
			bin = (char *)calloc(sizeof(char), (strlen(path_split[i]) + 1 + strlen(cmd[0]) + 1));
			if (bin == NULL)
				break ;

			// On concat le path , le '/' et le nom du binaire
			strcat(bin, path_split[i]);
			strcat(bin, "/");
			strcat(bin, cmd[0]);

			// On verfie l'existence du fichier et on quitte la boucle si access
			// renvoi 0
			if (access(bin, F_OK) == 0)
				break ;

			// Nous sommes des gens propre :D
			free(bin);
			bin = NULL;
		}
		//free_array(path_split);

		// On remplace le binaire par le path absolue ou NULL si le binaire
		// n'existe pas
		//free(cmd[0]);
		cmd[0] = bin;
	} else {
		free(path);
		path = NULL;
	}
}


void init_shell()
{
    //clear();
    printf("\n\n\n\n******************"
        "************************");
    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\t-USE AT YOUR OWN RISK-");
    printf("\n\n\n\n*******************"
        "***********************");
    char* username = getenv("USER");
    printf("\n\n\nUSER is: @%s", username);
    printf("\n");
    sleep(1);
    //clear();
}
int executecmd(char** params) {
    pid_t pid = fork(); //fork process

    get_absolute_path(params);
    if (pid == -1) { //error
        char *error = strerror(errno);
        printf("error fork!!\n");
        return 1;
    } else if (pid == 0) { // child process
        printf("%s\n" , params[1]);
        execve(params[0], params,NULL); //exec cmd
        char *error = strerror(errno);
        printf("unknown command\n");
        return 0;
    } else { // parent process
        int childstatus;
        waitpid(pid, &childstatus, 0);
        kill(pid, SIGTERM);   
        return 1;
    }
};

int execpipe (char ** argv1, char ** argv2) {
    int fds[2];
    pipe(fds);
    int i;
    get_absolute_path(argv1);
    get_absolute_path(argv2);
    pid_t pid1 = fork();
    if (pid1 == 0) 
    {
         pipe(fds);
        pid_t pid = fork();
        if (pid == -1) { //error
            char *error = strerror(errno);
            printf("error fork!!\n");
            return 1;
        } 
        if (pid == 0) { // child process
            close(fds[1]);
            i = dup(0);
            dup2(fds[0], 0);
            //close(fds[0]);
            executecmd(argv2); // run command AFTER pipe character in userinput
            close(fds[1]);
            /*close(0);
            dup2(i,0);*/
            exit(EXIT_SUCCESS);
            char *error = strerror(errno);
            //printf("unknown command\n");
            
            return 0;
        } else { // parent process
            close(fds[0]);
            i = dup(1);
            dup2(fds[1], 1);
            close(fds[1]);
            executecmd(argv1); // run command BEFORE pipe character in userinput
            close(fds[1]);
            /*close(1);
            dup2(i,1);
            waitpid(pid,&i,0);
            kill(pid, SIGTERM);*/
            //printf("unknown command\n");
            exit(EXIT_SUCCESS);
            return 0;
        }
        printf("unknown command\n");
    }
    else
    {
        waitpid(pid1,&i,0);
       // kill(pid1, SIGTERM);
    }
    return 1;
}

int ft_pipexe(char ** argv1, int k)
{
    char *tmp;
    int i;
    int j;

    i = 0;
    

}

int main() {    
    char cmd[MAX_CMD_LENGTH+1];    
    char * params[MAX_NUM_PARAMS+1];    
    char * argv1[MAX_NUM_PARAMS+1] = {0};    
    char * argv2[MAX_NUM_PARAMS+1] = {0};    
    int k, y, x,i;    
    int f = 1;    

    init_shell();
    while(1) {
        printf("$"); //prompt    
        if(fgets(cmd, sizeof(cmd), stdin) == NULL) break; //read command, ctrl+D exit       
        if(cmd[strlen(cmd)-1] == '\n') { //remove newline char    
            cmd[strlen(cmd)-1] = '\0';    
        }    
        f = 1;
        int j=parsecmd(cmd, params," "); //split cmd into array of params           
        if (strcmp(params[0], "exit") == 0) break; //exit   
        //add_history(cmd); 
        /*for (k=0; k <j; k++) { //elegxos gia uparksi pipes    
            if (strcmp(params[k], "|") == 0) {    
                f = 0; y = k;      
               printf("pipe found\n");
               break;
            }               
        }*/
        k=parsecmd(cmd, argv1,"|");
        if (k > 1) {
        /*if (f==0) {
            for (x=0; x<k; x++) {    
               argv1[x]=params[x];
            }     
            int z = 0;     
            for (x=k+1; x< j; x++) {     
                argv2[z]=params[x];
                z++;
            }  */   
        ft_pipexe(argv1, k);
        //ft_free_split(argv1);
        //ft_free_split(argv2);
         } else if (f==1) {     
             if (executecmd(params) == 0) break;
         }
        //ft_free_split(params);
        i = -1;
        while(cmd[++i]){
            cmd[i] = 0;
        }
    } // end while
    return 0;
}