#include <stdio.h>
#include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

// Parsed command representation
#define EXEC  1
#define REDIR 2
#define PIPE  3
#define LIST  4
#define BACK  5

#define MAXARGS 10




typedef struct s_cmd
{
  int type;
}t_cmd;

typedef struct s_execcmd
{
  int type;
  char *argv[MAXARGS];
  char *eargv[MAXARGS];
}t_execcmd;

typedef struct s_redircmd {
  int type;
  t_cmd *cmd;
  char *file;
  char *efile;
  int mode;
  int fd;
}t_redircmd;

typedef struct s_pipecmd {
  int type;
  t_cmd *left;
  t_cmd *right;
}t_pipecmd;

typedef struct s_listcmd {
  int type;
  t_cmd *left;
  t_cmd *right;
}t_listcmd;

typedef struct s_backcmd {
  int type;
  t_cmd *cmd;
}t_backcmd;



//TODO:Os comando são ordenados dentro de cmd. Um nó para cada comando
typedef struct s_shell
{
	t_list *cmd;
	char	**env;
}	t_shell;


typedef struct s_mini
{
	int i;//para poupar algum espaço nas functions
	int j;
	int	infilefd;
	int	outfilefd;
	int errnumb;
	char **cmd_split;
	char *full_cmd;
	char *path;  // main path from getevn
	char **paths;  //split the path
	char *home;     //home dir
	char *username;        //user name
	t_list	*lpipes; //list of pipes
}	t_mini;

t_cmd* execcmd(void);
void panic(char *s);
void runcmd(t_cmd *cmd);

int fork1(void);
t_cmd* execcmd(void);
t_cmd* redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd);
t_cmd* pipecmd(t_cmd *left, t_cmd *right);
t_cmd* listcmd(t_cmd *left, t_cmd *right);
t_cmd* backcmd(t_cmd *subcmd);

int gettoken(char **ps, char *es, char **q, char **eq);;
int peek(char **ps, char *es, char *toks);;

t_cmd *parseline(char**, char*);
t_cmd *parsepipe(char**, char*);;
t_cmd *parseexec(char**, char*);;
t_cmd *nulterminate(t_cmd*);;
t_cmd *parsecmd(char *s);;
t_cmd *parseredirs(t_cmd *cmd, char **ps, char *es);;
t_cmd *parseblock(char **ps, char *es);;
t_cmd *parseexec(char **ps, char *es);;
t_cmd *nulterminate(t_cmd *cmd);;


static void	inthandler(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//init shell memory
void	ini_shell(t_mini *data)
{
	//int i;

	//i = 0;
	data->path  = getenv("PATH");
	data->username = getenv("USER");
	// data->paths = ft_split(data->path, ':');
	// data->home  = ft_strdup(getenv("HOME"));
	// while(data->paths[i])
	// {
	// 	printf(" %d %s \n",i,data->paths[i]);
	// 	i++;
	// }
}


// free shell memori
void free_shell(t_mini *data)
{
	//int i=0
	//while(data->paths[i])
	//{
	//	free(data->paths[i]);
	//	i++;
	//}
    rl_clear_history();
	free(data->paths);
	free(data->home);
	exit(0);
}

void  loop_shell(t_mini *data)
{
	char	*str;
	int status;
	t_cmd * cmd=NULL;

	str = NULL;
	while (1)
	{
		if (str)
			free(str);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, inthandler);
		str = readline("minishell$: ");
		if (str == NULL)
		{
			printf("exit, BY! By!\n");
			free_shell(data);
			return ;
		}
		if (!ft_strncmp("", str, 1))
			continue ;
		add_history(str);
	//	data->lpipes = NULL;

		 if(fork1() == 0)
         {
            cmd  = parsecmd(str);
            if (cmd)
            {
                runcmd(cmd);
                free(cmd);
                cmd=NULL;
            }


         }

        wait(&status);

		//ls -l | wc -l
	}
	free(str);
}


int main (int argc, char **argcv, char **envp)
{
	(void)argc;
	(void)argcv;
	(void)envp;



	t_mini data;
	ft_bzero(&data, sizeof(t_mini));
	ini_shell(&data);
	loop_shell(&data);
	free_shell(&data);
	return (0);
}

void panic(char *s)
{
  printf("%s\n", s);
  exit(1);
}

//********************************************************** constroi
t_cmd* execcmd(void)
{
  t_execcmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = EXEC;
  return (t_cmd*)cmd;
}


t_cmd* redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd)
{
  t_redircmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = REDIR;
  cmd->cmd = subcmd;
  cmd->file = file;
  cmd->efile = efile;
  cmd->mode = mode;
  cmd->fd = fd;
  return (t_cmd*)cmd;
}

t_cmd* pipecmd(t_cmd *left, t_cmd *right)
{
  t_pipecmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = PIPE;
  cmd->left = left;
  cmd->right = right;
  return (t_cmd*)cmd;
}

t_cmd* listcmd(t_cmd *left, t_cmd *right)
{
  t_listcmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = LIST;
  cmd->left = left;
  cmd->right = right;
  return (t_cmd*)cmd;
}

t_cmd* backcmd(t_cmd *subcmd)
{
  t_backcmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = BACK;
  cmd->cmd = subcmd;
  return (t_cmd*)cmd;
}

//*******************************************************************************parser
char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>&;()";

int gettoken(char **ps, char *es, char **q, char **eq)
{
  char *s;
  int ret;

  s = *ps;
  while(s < es && strchr(whitespace, *s))
    s++;
  if(q)
    *q = s;
  ret = *s;
  switch(*s){
  case 0:
    break;
  case '|':
  case '(':
  case ')':
  case ';':
  case '&':
  case '<':
    s++;
    break;
  case '>':
    s++;
    if(*s == '>'){
      ret = '+';
      s++;
    }
    break;
  default:
    ret = 'a';
    while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
      s++;
    break;
  }
  if(eq)
    *eq = s;

  while(s < es && strchr(whitespace, *s))
    s++;
  *ps = s;
  return ret;
}

int peek(char **ps, char *es, char *toks)
{
  char *s;

  s = *ps;
  while(s < es && strchr(whitespace, *s))
    s++;
  *ps = s;
  return *s && strchr(toks, *s);
}




t_cmd* parsecmd(char *s)
{
  char *es;
  t_cmd *cmd;

  es = s + strlen(s);
  cmd = parseline(&s, es);
  peek(&s, es, "");
  if(s != es)
  {
    printf("syntax error leftovers: %s\n", s);
  }
  nulterminate(cmd);
  return cmd;
}

t_cmd* parseline(char **ps, char *es)
{
  t_cmd *cmd;

  cmd = parsepipe(ps, es);
  while(peek(ps, es, "&"))
  {
    gettoken(ps, es, 0, 0);
    cmd = backcmd(cmd);
  }
  if(peek(ps, es, ";"))
  {
    gettoken(ps, es, 0, 0);
    cmd = listcmd(cmd, parseline(ps, es));
  }
  return cmd;
}

t_cmd* parsepipe(char **ps, char *es)
{
  t_cmd *cmd;

  cmd = parseexec(ps, es);
  if(peek(ps, es, "|"))
  {
    gettoken(ps, es, 0, 0);
    cmd = pipecmd(cmd, parsepipe(ps, es));
  }
  return cmd;
}


t_cmd* parseredirs(t_cmd *cmd, char **ps, char *es)
{
  int tok;
  char *q, *eq;

  while(peek(ps, es, "<>"))
  {
    tok = gettoken(ps, es, 0, 0);
    if(gettoken(ps, es, &q, &eq) != 'a')
	{
     	 printf("missing file for redirection \n");
		 return NULL;
	}
    switch(tok)
	{
    case '<':
      cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
      break;
    case '>':
      cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT, 1);
      break;
    case '+':  // >>
      cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT, 1);
      break;
    }
  }
  return cmd;
}

t_cmd* parseblock(char **ps, char *es)
{
  t_cmd *cmd;

  	if(!peek(ps, es, "("))
    {
		printf("error parseblock \n");
		return NULL;
	}

  gettoken(ps, es, 0, 0);
  cmd = parseline(ps, es);
  if(!peek(ps, es, ")"))
  {
    printf("syntax - missing ) 	n");
	return NULL;
  }
  gettoken(ps, es, 0, 0);
  cmd = parseredirs(cmd, ps, es);
  return cmd;
}

t_cmd* parseexec(char **ps, char *es)
{
  char *q, *eq;
  int tok, argc;
  t_execcmd *cmd;
  t_cmd *ret;

  if(peek(ps, es, "("))
    return parseblock(ps, es);

  ret = execcmd();
  cmd = (t_execcmd*)ret;

  argc = 0;
  ret = parseredirs(ret, ps, es);
  while(!peek(ps, es, "|)&;"))
    {
    if((tok=gettoken(ps, es, &q, &eq)) == 0)
       break;
    if(tok != 'a')
	{
      printf("syntax error \n");
	  return NULL;
	}
    cmd->argv[argc] = q;
    cmd->eargv[argc] = eq;
    argc++;
    if(argc >= MAXARGS)
	{
      printf("too many args \n");
	  return NULL;
	}
    ret = parseredirs(ret, ps, es);
  }
  free(cmd->argv[argc]);
  free(cmd->eargv[argc]);

  cmd->argv[argc] = NULL;
  cmd->eargv[argc] = NULL;
  return ret;
}


// NUL-terminate all the counted strings.
t_cmd* nulterminate(t_cmd *cmd)
{
  int i;
  t_backcmd *bcmd;
  t_execcmd *ecmd;
  t_listcmd *lcmd;
  t_pipecmd *pcmd;
  t_redircmd *rcmd;

  if (cmd == 0)
     return 0;

  switch(cmd->type)
  {
  case EXEC:
  {
    ecmd = (t_execcmd*)cmd;
    for(i=0; ecmd->argv[i]; i++)
    {
     //  free(ecmd->eargv[i]) ;
       ecmd->eargv[i] = NULL;
    }
    break;
  }
  case REDIR:
      {
        rcmd = (t_redircmd*)cmd;
        nulterminate(rcmd->cmd);
        free(rcmd->efile);
        break;
      }
  case PIPE:
    {
        pcmd = (t_pipecmd*)cmd;
        nulterminate(pcmd->left);
        nulterminate(pcmd->right);
        break;
    }


  case LIST:
      {
        lcmd = (t_listcmd*)cmd;
        nulterminate(lcmd->left);
        nulterminate(lcmd->right);
        break;
      }


  case BACK:
      {
        bcmd = (t_backcmd*)cmd;
        nulterminate(bcmd->cmd);
        break;
      }

  }
  return cmd;
}


int fork1(void)
{
  int pid;

  pid = fork();
  if(pid == -1)
    panic("fork");
  return pid;
}


void teste_exec(char *fname, char ** args)
{
    printf("EXECUTE : %s  \n",fname);
    int i=0;
    while(args[i])
    {
        printf("    Arg[%d] : %s  \n",i,args[i]);

        i++;
    }
    printf(" \n");

}


void runcmd(t_cmd *cmd)
{
//  int p[2];
  t_backcmd *bcmd;
  t_execcmd *ecmd;
  t_listcmd *lcmd;
  t_pipecmd *pcmd;
  t_redircmd *rcmd;
//  int status;

  if (cmd == 0)
        return;

  switch(cmd->type)
  {

  case EXEC:
  {
        ecmd = (t_execcmd*)cmd;
        if(ecmd->argv[0] == 0)
           return;
        teste_exec(ecmd->argv[0], ecmd->argv);

    }
    break;

  case REDIR:
    {
    rcmd = (t_redircmd*)cmd;
    close(rcmd->fd);
    if(open(rcmd->file, rcmd->mode) < 0)
    {
      printf("open %s failed\n", rcmd->file);
      return;
    }
    runcmd(rcmd->cmd);
    }
    break;

  case LIST:
   {
		int status;
        lcmd = (t_listcmd*)cmd;
        if(fork1() == 0)
          runcmd(lcmd->left);
        wait(&status);
        runcmd(lcmd->right);
    }
    break;

  case PIPE:
      {
            pcmd = (t_pipecmd*)cmd;
            runcmd(pcmd->left);
            runcmd(pcmd->right);


            /*
            if(pipe(p) < 0)
			{
              printf(" error pipe \n");
			  return;
			}
            if(fork1() == 0)
			{
              close(1);
              dup(p[1]);
              close(p[0]);
              close(p[1]);
              runcmd(pcmd->left);
            }
            if(fork1() == 0)
			{
              close(0);
              dup(p[0]);
              close(p[0]);
              close(p[1]);
              runcmd(pcmd->right);
            }
            close(p[0]);
            close(p[1]);
            wait(&status);
            wait(&status);
            */
      }
        break;
  case BACK:
    {

        bcmd = (t_backcmd*)cmd;
        if(fork1() == 0)
        {
          runcmd(bcmd->cmd);
        }

    break;
  }
  default:
      {
          printf("cmd not found \n");
          break;
      }
   }
}
