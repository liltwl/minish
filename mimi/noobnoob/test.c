void runPipedCommands(cmdLine* command, char* userInput) {
    int numPipes = countPipes(userInput);


    int status;
    int i = 0;
    pid_t pid;

    int pipefds[2*numPipes];

    for(i = 0; i < (numPipes); i++){
        if(pipe(pipefds + i*2) < 0) {
            perror("couldn't pipe");
            exit(EXIT_FAILURE);
        }
    }


    int j = 0;
    while(command) {
        pid = fork();
        if(pid == 0) {

            //if not last command
            if(command->next){
                if(dup2(pipefds[j + 1], 1) < 0){
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            //if not first command&& j!= 2*numPipes
            if(j != 0 ){
                if(dup2(pipefds[j-2], 0) < 0){
                    perror(" dup2");///j-2 0 j+1 1
                    exit(EXIT_FAILURE);

                }
            }


            for(i = 0; i < 2*numPipes; i++){
                    close(pipefds[i]);
            }

            if( execvp(*command->arguments, command->arguments) < 0 ){
                    perror(*command->arguments);
                    exit(EXIT_FAILURE);
            }
        } else if(pid < 0){
            perror("error");
            exit(EXIT_FAILURE);
        }

        command = command->next;
        j+=2;
    }
    /**Parent closes the pipes and wait for children*/

    for(i = 0; i < 2 * numPipes; i++){
        close(pipefds[i]);
    }

    for(i = 0; i < numPipes + 1; i++)
        wait(&status);
}

/* parent creates all needed pipes at the start */
int	execmlpipe(char **argv1, int i, char **env)
{
	int		fds[i * 2];
	pid_t	pid;
	int		x;

for( x = 0; x < i; x++ ){
    if( pipe(fds + x*2) < 0 ){
        perror("pipe");
    }
}
x = -1;
while( ++x < i ){
    pid = fork();
    if( pid == 0 ){
        /* child gets input from the previous command,
            if it's not the first command */
        if( x != 0 ){
            if( dup2(fds[(x-1)*2], 0) < 0 ){
                perror("dup");
            }
        }
        /* child outputs to next command, if it's not
            the last command */
        if( i - 1 != x){
            if( dup2(fds[x*2+1], 1) < 0 ){
                perror("dup");
            }
        }
       // close all pipe-fds
       exec_cmd(argv1[x], env);
		exit(0);
    } else if( pid < 0 ){
        perror("fork");
    }
}

/* parent closes all of its copies at the end */
for( x = 0; x < 2 * i; x++ ){
    close( fds[x] );
}
return (0);
}

int	exedcmlpipe(char **argv1, int i, char **env)
{
	int		fds[2];
	pid_t	pid;
	int		x;
	int		fd;

	x = -1;
	while (++x < i)
	{
		pipe(fds);
		pid = fork();
		if (pid == -1)
			ft_close("error : fork failed", 1);
		if (pid == 0)
		{
			execdup(i, fds, x, fd);
			exec_cmd(argv1[x], env);
		}
		else
		{
			wait(NULL);
			close(fds[1]);
			fd = fds[0];
		}
	}
	return (0);
}