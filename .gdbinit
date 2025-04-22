set follow-fork-mode child
set detach-on-fork off
break fork
break execve
break dup2