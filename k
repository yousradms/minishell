kkkkkk

> $a
Minishell: b: command not found

bash -> $a: ambiguous redirect




minishell🥶😁cd hello/
minishell🥶😁ls
minishell🥶😁pwd
/private/tmp/hello
minishell🥶😁pwd
getcwd() error: No such file or directory
minishell🥶😁



minishell🥶😁./minishell
minishell🥶😁echo $SHLVL
1
minishell🥶😁


cat < Makefiles
NO such file or directory
minishell🥶😁echo $?
0
minishell🥶😁


minishell🥶 usiuhs
Minishell: usiuhs: command not found
minishell🥶😁ls |  echo $? 
127


export a=" a $HOME"
minishell🥶😁echo $a
a /Users/ydoumas
minishell🥶😁< $a ls
Minishell: /Users/ydoumas: is a directory

export a="sjns sjnsjn sjsk"
bash-3.2$ > $a
bash: $a: ambiguous redirect




➜  finished git:(main) ✗ bash

The default interactive shell is now zsh.
To update your account to use zsh, please run `chsh -s /bin/zsh`.
For more details, please visit https://support.apple.com/kb/HT208050.
bash-3.2$ cat
^C
bash-3.2$ ecport a="a b"
bash: ecport: command not found
bash-3.2$ export a="a b"
bash-3.2$ > $a
bash: $a: ambiguous redirect
bash-3.2$ echo $?
1
bash-3.2$ < h
bash-3.2$ < h cat
bash-3.2$ < h cat >> h
^C^C^C^C^C^C^C^C
bash-3.2$ < h cat >> h
^C^C^C^C
bash-3.2$ 
bash-3.2$ rm h
bash-3.2$ ls -la
total 320
drwxr-xr-x  21 ydoumas  candidate    714 Sep 21 13:12 .
drwxr-xr-x  64 ydoumas  candidate   2176 Sep 20 15:41 ..
-rw-r--r--   1 ydoumas  candidate   6148 Sep 20 15:41 .DS_Store
drwxr-xr-x  12 ydoumas  candidate    408 Sep 20 15:41 .git
-rw-r--r--   1 ydoumas  candidate   2981 Sep 20 16:18 Makefile
-rw-r--r--   1 ydoumas  candidate      0 Sep 21 13:08 a
drwxr-xr-x   6 ydoumas  candidate    204 Sep 20 15:41 execution
-rw-r--r--   1 ydoumas  candidate   2981 Sep 21 13:12 h
-rw-r--r--   1 ydoumas  candidate     76 Sep 21 13:09 k
-rw-r--r--   1 ydoumas  candidate      7 Sep 20 16:46 l
drwxr-xr-x  35 ydoumas  candidate   1190 Sep 20 19:04 libft
-rw-r--r--   1 ydoumas  candidate   2275 Sep 20 15:41 main.c
-rw-r--r--   1 ydoumas  candidate   2604 Sep 20 19:56 main.o
-rwxr-xr-x   1 ydoumas  candidate  95016 Sep 20 19:56 minishell
-rw-r--r--   1 ydoumas  candidate   9164 Sep 20 16:35 minishell.h
-rw-r--r--   1 ydoumas  candidate      7 Sep 20 16:46 p
drwxr-xr-x  12 ydoumas  candidate    408 Sep 20 19:56 parsing
-rw-r--r--   1 ydoumas  candidate   2223 Sep 20 20:48 parsing_execute.c
-rw-r--r--   1 ydoumas  candidate   2580 Sep 20 19:56 parsing_execute.o
-rw-r--r--   1 ydoumas  candidate   1866 Sep 20 16:18 utils.c
-rw-r--r--   1 ydoumas  candidate   1868 Sep 20 19:56 utils.o
bash-3.2$ ls -la h
-rw-r--r--  1 ydoumas  candidate  2981 Sep 21 13:12 h
bash-3.2$ em h
bash: em: command not found
bash-3.2$ rm h
bash-3.2$ cd tmp
bash: cd: tmp: No such file or directory
bash-3.2$ cd /tmp
bash-3.2$ ls
com.apple.launchd.m9x1Mogi3K    powerlog
hello                           pymp-hfw6jy4y
last_fs_sync                    ydoumas
bash-3.2$ rm hello/
rm: hello/: is a directory
bash-3.2$ rm -rf hello/
bash-3.2$ mkdr hello
bash: mkdr: command not found
bash-3.2$ mkdir hello
bash-3.2$ pwd
/tmp
bash-3.2$ cd hello/
bash-3.2$ pwd
/tmp/hello
bash-3.2$ cd ..
bash-3.2$ pwd
/private/tmp
bash-3.2$ mkdir hello
bash-3.2$ rm -rf hello/
bash-3.2$ << hello
> 
bash-3.2$ export a="hello"
bash-3.2$ echo $$2151dduhd"$HOME"'hello'$a"$ $5854"
253322151dduhd/Users/ydoumashellohello$ 854
bash-3.2$ echo $84882151dduhd"$HOME"'hello'$a"$ $5854"
4882151dduhd/Users/ydoumashellohello$ 854
bash-3.2$ export 
declare -x COLORTERM="truecolor"
declare -x COMMAND_MODE="unix2003"
declare -x C_INCLUDE_PATH="/Users/ydoumas/.brew/include:"
declare -x GIT_ASKPASS="/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh"
declare -x HOME="/Users/ydoumas"
declare -x HOMEBREW_CACHE="/tmp/ydoumas/Homebrew/Caches"
declare -x HOMEBREW_TEMP="/tmp/ydoumas/Homebrew/Temp"
declare -x LANG="en_US.UTF-8"
declare -x LESS="-R"
declare -x LIBRARY_PATH="/Users/ydoumas/.brew/lib:/Users/ydoumas/.brew/lib:"
declare -x LOGNAME="ydoumas"
declare -x LSCOLORS="Gxfxcxdxbxegedabagacad"
declare -x LS_COLORS="di=1;36:ln=35:so=32:pi=33:ex=31:bd=34;46:cd=34;43:su=30;41:sg=30;46:tw=30;42:ow=30;43"
declare -x LaunchInstanceID="33C94D8A-0DB7-4649-B398-9FD86C3D0C55"
declare -x MallocNanoZone="0"
declare -x OLDPWD="/tmp/hello"
declare -x ORIGINAL_XDG_CURRENT_DESKTOP="undefined"
declare -x PAGER="less"
declare -x PATH="/Users/ydoumas/.brew/bin:/Users/ydoumas/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin"
declare -x PWD="/private/tmp"
declare -x SECURITYSESSIONID="186a7"
declare -x SHELL="/bin/zsh"
declare -x SHLVL="2"
declare -x SSH_AUTH_SOCK="/private/tmp/com.apple.launchd.m9x1Mogi3K/Listeners"
declare -x TERM="xterm-256color"
declare -x TERM_PROGRAM="vscode"
declare -x TERM_PROGRAM_VERSION="1.89.1"
declare -x TMPDIR="/var/folders/zz/zyxvpxvq6csfxvn_n000cltm0034yn/T/"
declare -x USER="ydoumas"
declare -x USER_ZDOTDIR="/Users/ydoumas"
declare -x VSCODE_GIT_ASKPASS_EXTRA_ARGS=""
declare -x VSCODE_GIT_ASKPASS_MAIN="/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js"
declare -x VSCODE_GIT_ASKPASS_NODE="/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin)"
declare -x VSCODE_GIT_IPC_HANDLE="/var/folders/zz/zyxvpxvq6csfxvn_n000cltm0034yn/T/vscode-git-6e5c5a902f.sock"
declare -x VSCODE_INJECTION="1"
declare -x XPC_FLAGS="0x0"
declare -x XPC_SERVICE_NAME="0"
declare -x ZDOTDIR="/Users/ydoumas"
declare -x ZSH="/Users/ydoumas/.oh-my-zsh"
declare -x __CF_USER_TEXT_ENCODING="0x193D5:0x0:0x0"
declare -x a="hello"
bash-3.2$ bash

The default interactive shell is now zsh.
To update your account to use zsh, please run `chsh -s /bin/zsh`.
For more details, please visit https://support.apple.com/kb/HT208050.
bash-3.2$ echo $SHLVL
3
bash-3.2$ echo $?
0
bash-3.2$ cat < Makefiles
bash: Makefiles: No such file or directory
bash-3.2$ echo $?
1
bash-3.2$ cast | echo $?
0
bash: cast: command not found
bash-3.2$ echo $/
$/
bash-3.2$ cast | echo $?
bash: cast: command not found
0
bash-3.2$ echo $?
0
bash-3.2$ sijijss
bash: sijijss: command not found
bash-3.2$ cast | echo $?
bash: cast: command not found
0
bash-3.2$ cast | echo $?
bash: cast: command not found
0
bash-3.2$ sijijss
bash: sijijss: command not found
bash-3.2$ cast | echo $?
bash: cast: command not found
0
bash-3.2$ sijijss
bash: sijijss: command not found
bash-3.2$ cast | echo $?
bash: cast: command not found
0
bash-3.2$ export a=" a $HOME"
bash-3.2$ < $a ls
bash: $a: ambiguous redirect
bash-3.2$ echo $?
1
bash-3.2$ < "a b"
bash: a b: No such file or directory
bash-3.2$ export a="sjns sjnsjn sjsk"
bash-3.2$ > $a
bash: $a: ambiguous redirect
bash-3.2$ > "a b"
bash-3.2$ 
bash-3.2$ > "a b"
bash-3.2$ echo $SHLVL
3
bash-3.2$ bash

The default interactive shell is now zsh.
To update your account to use zsh, please run `chsh -s /bin/zsh`.
For more details, please visit https://support.apple.com/kb/HT208050.
bash-3.2$ echo $SHLVL
4
bash-3.2$ unset PATH
bash-3.2$ ls
bash: ls: No such file or directory
bash-3.2$ echo $?
127
bash-3.2$ /bin/ls
LuiQMIHJETZIRzSbSsLm            powerlog
TfHHfWdbMzgmqugYhWOS            pymp-hfw6jy4y
a b                             vmzfRgaTEduoBRvZSqhf
com.apple.launchd.m9x1Mogi3K    ydoumas
fsEoVWtspnTPOVOFaMJo            zkVPcLTJpEmOnTTpGEiQ
last_fs_sync
bash-3.2$ ls
bash: ls: No such file or directory
bash-3.2$ ls
bash: ls: No such file or directory
bash-3.2$ unset path
bash-3.2$ minishel
bash: minishel: No such file or directory
bash-3.2$ minishell
bash: minishell: No such file or directory
bash-3.2$ ls
bash: ls: No such file or directory
bash-3.2$ pwd
/private/tmp
bash-3.2$ exit
bash-3.2$ exit
bash-3.2$ exit
➜  finished git:(main) ✗ bash

The default interactive shell is now zsh.
To update your account to use zsh, please run `chsh -s /bin/zsh`.
For more details, please visit https://support.apple.com/kb/HT208050.
bash-3.2$ ls
Makefile                minishell.h
execution               p
k                       parsing
l                       parsing_execute.c
libft                   parsing_execute.o
main.c                  utils.c
main.o                  utils.o
minishell
bash-3.2$ unset PATH
bash-3.2$ minishell
minishell🥶😁./minishell
minishell🥶😁
exit
minishell🥶😁
exit
bash-3.2$ ./minishell
minishell🥶😁


