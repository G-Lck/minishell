#! /bin/bash

# Configuration

Minishell="./minishell-theo"
Total_tests=0
Passed_tests=0
details=none # output, error, all, or none
test=all # all for all
leak=false # true to check for leaks
TMP_DIR="/tmp/minishell_test_$$"
mkdir -p "$TMP_DIR"


# Colors

PINK='\033[38;2;242;131;209m'
TURQUOISE='\033[38;2;81;213;215m'
PURPLE='\033[38;2;182;127;208m'
RESET='\033[0m'

# Functions

test_debug(){

	local cmd="$1"
	local description="$2"

	local test_passed=false
	local error_passed=false

	# Exécute commande + echo $? + exit dans minishell
	printf "%s\necho EXIT_MARKER:\$?\nexit\n" "$cmd" | ${Minishell} > "$TMP_DIR/mini_full_output.tmp" 2> "$TMP_DIR/mini_error.tmp"

	echo "begin of mini_full_output"
	cat $TMP_DIR/mini_full_output.tmp
	echo "end of mini_full_output"

	mini_exit_code=$(grep -oP -a '(?<=EXIT_MARKER:)[0-9]+' "$TMP_DIR/mini_full_output.tmp" | tail -n 1)
	echo "mini_exit_code: " ${mini_exit_code}

	echo "begin of mini_cleaned_output"
	grep -v -a "Minishell>" "$TMP_DIR/mini_full_output.tmp" | grep -v "Force à toi" | grep -v 'EXIT_MARKER:' > "$TMP_DIR/cleaned_mini_output.tmp" 2>/dev/null || touch "$TMP_DIR/cleaned_mini_output.tmp"
	echo "end of mini_cleaned_output"
	rm -f *.tmp
	rm -f "$TMP_DIR"/*.tmp
}

test_command(){

	local cmd="$1"
	local description="$2"

	local test_passed=false
	local error_passed=false

	# Exécute commande + echo $? + exit dans minishell
	printf "%s\necho EXIT_MARKER:\$?\nexit\n" "$cmd" | ${Minishell} > "$TMP_DIR/mini_full_output.tmp" 2> "$TMP_DIR/mini_error.tmp"

	# Récupère l'exit code depuis le marqueur
	mini_exit_code=$(grep -oP -a '(?<=EXIT_MARKER:)[0-9]+' "$TMP_DIR/mini_full_output.tmp" | tail -n 1)

	# Enlève les lignes de prompt, marqueur, et message d'accueil
	grep -v -a "Minishell>" "$TMP_DIR/mini_full_output.tmp" | grep -v "Force à toi" | grep -v 'EXIT_MARKER:' > "$TMP_DIR/cleaned_mini_output.tmp" 2>/dev/null || touch "$TMP_DIR/cleaned_mini_output.tmp"

	eval "$cmd" > "$TMP_DIR/bash_output.tmp" 2> "$TMP_DIR/bash_error.tmp"
	bash_exit_code=$?

	# Normalise les messages d'erreur pour comparaison
    sed 's/^[^:]*: //' "$TMP_DIR/mini_error.tmp" > "$TMP_DIR/normalized_mini_error.tmp"
    sed 's/^.*line [0-9]*: //' "$TMP_DIR/bash_error.tmp" > "$TMP_DIR/normalized_bash_error.tmp"

	if diff -q "$TMP_DIR/cleaned_mini_output.tmp" "$TMP_DIR/bash_output.tmp" > /dev/null; then
		echo -e "${TURQUOISE}${description}${RESET}"
		echo -e "${TURQUOISE}${cmd}${RESET}"
		if [[ ${details} == all || ${details} == output ]]; then
			echo -ne "${TURQUOISE}" && cat -n "$TMP_DIR/cleaned_mini_output.tmp" && echo -e "==========" "" && cat -n "$TMP_DIR/bash_output.tmp" && echo -e "${RESET}"
		fi
		test_passed=true
	else
		echo -e "${PINK}${description}${RESET}"
		echo -e "${PINK}${cmd}${RESET}"
		if [[ ${details} == all || ${details} == output ]]; then
			echo -ne "${PINK}" && cat "$TMP_DIR/cleaned_mini_output.tmp" && echo -e "==========" "" && cat "$TMP_DIR/bash_output.tmp" && echo -e "${RESET}"
		fi
	fi

	# Compare les erreurs normalisées ET les exit codes
	if diff -q "$TMP_DIR/normalized_mini_error.tmp" "$TMP_DIR/normalized_bash_error.tmp" > /dev/null && [[ $mini_exit_code == $bash_exit_code ]]; then
		error_passed=true
	else
		echo -e "${PINK}error diff${RESET}"
		if [[ ${details} == all || ${details} == error ]]; then
			echo -ne "${PINK}" && cat "$TMP_DIR/mini_error.tmp" && echo -e "==========" "" && cat "$TMP_DIR/bash_error.tmp" && echo -e "${RESET}"
			echo "${mini_exit_code} VS ${bash_exit_code}"
		fi
	fi

	if [[ $test_passed == true && $error_passed == true ]]; then
		echo -e "${TURQUOISE}OK 🦄${RESET}"
		Total_tests=${Total_tests}+1

		# Leak check with valgrind
		if [[ $leak == true ]]; then
			printf "%s\nexit\n" "$cmd" | valgrind --leak-check=full --show-leak-kinds=all --suppressions=ignore_readline_leaks.supp --log-file="$TMP_DIR/valgrind.tmp" ${Minishell} > /dev/null 2>&1
			if grep -q "definitely lost: [^0]" "$TMP_DIR/valgrind.tmp" || grep -q "indirectly lost: [^0]" "$TMP_DIR/valgrind.tmp"; then
				echo -e "${PURPLE}!LEAKS!${RESET}"
			fi
		fi
	else
		echo -e "${PINK}KO 💩${RESET}"
	fi
	rm -f *.tmp
	rm -f "$TMP_DIR"/*.tmp
}

if [[ ${test} == all ]]; then
	# 42 Tests

	# classic and empty
	test_command "/bin/ls" "test with absolute path"
	test_command "" "test with nothing"
	test_command "   " "test with spaces"
	test_command "		" "test with tab"

	# echo with variables
	test_command "echo" "echo with nothing"
	test_command "echo a" "simple echo"
	test_command "echo -n a" "simple echo with option -n"
	test_command "echo $LANG and $HOME" "echo with variables"

	# ls and errors
	test_command "/bin/ls srcs" "ls with absolute path with one arg"
	test_command "/bin/ls srcs libft" "ls with absolute path with two args"
	test_command "/bin/ls notafile" "ls with absolute path with file doesn't exist"
	test_command "expr $?+$?" 'test with expr $?+$?'

	# ls, echo and quotes
	test_command 'ls "srcs"   "libft"' "ls with two args but single quotes and spaces"
	test_command 'ls "srcs"		"libft"' "ls with two args but single quotes and tabs"
	test_command "ls 'srcs'   'libft'" "ls with two args and double quotes and spaces"
	test_command "ls 'srcs'		'libft'" "ls with two args and double quotes and tabs"
	test_command 'echo "cat lol.c | cat > lol.c"' "echo with double quotes for args"
	test_command "echo ''" "echo with single quotes"
	test_command "echo 'cat lol.c | cat > lol.c'" "echo with single quotes for args"
	test_command "echo '$USER'" "echo with variable in single quotes"

	# env cd and pwd
	## hard to test
	## test_command 'env' "test env OK if not working"
	## test_command "cd" "cd only"
	## test_command "cd srcs" "cd to go to a directory"
	## test_command "cd lol" "cd with not a directory"
	## test_command "cd .." "cd .."
	## test_command "cd ." "cd ."
	test_command "pwd" "pwd only"
	test_command "pwd with args"

	# others external commands
	test_command " wc -l ./minishell-garance" "wc with args"
	test_command "awk -F: '{ print $1 }' /etc/passwd" "awk with stuff"

	# PATH
	echo -e ${PINK}"unset PATH && ls" "unset PATH and do a command, it shouldnt work but its working"${RESET}

	#redirections
	test_command "ls < test.tmp" "input redirection <"
	test_command "echo a > test.tmp" "output redirection >"
	test_command "echo a >> test.tmp" "output redirection append >>"
	##test_command "echo a << test.x" "heredoc <<"
	test_command "echo a >" "> with nothng"
	test_command "echo a <" "< with nothing"
	test_command "echo a >>" ">> with nothing"
	test_command "cat < /etc/passwd" "input from existing file"
	test_command "cat < nonexistentfile" "input from non existent file"
	test_command "echo hello > /dev/null" "output to /dev/null"
	test_command "echo test > /root/forbidden.txt" "to a forbidden file"
	test_command 'echo test > "file with spaces.tmp"' "output with quoted filename"
	test_command "echo test >nospaces.tmp" "output without spaces around >"

	# pipes
	test_command "echo Unicorn | cat" "simple pipe"
	test_command "cat Makefile | grep make | wc -c" "pipe with multiples external commands"
	test_command "ls noexist | grep Make | wc -c" "pipe with a wrong command at beggining"
	test_command "ls | grepppppp Make | wc -c" "pipe with a wrong command at middle"
	test_command "ls | grep Make | caaaat" "pipe with a wrong command at the end"
	test_command "cat /dev/urandom | head -c 100 | wc -c" "check if child close his pipe"
	test_command "seq 100000 | wc -l" "same with another test"

	# pipes and redirections

	test_command "pwd | cat > output.tmp" "pipe with output redirection"
	test_command "echo hello | cat >> append.tmp" "pipe with append redirection"
	test_command "cat Makefile | grep make > filtered.tmp" "pipe with grep and output redirection"
	test_command "cat /etc/passwd | head -3 > first3.tmp" "pipe with head and output"
	test_command "echo test | wc -c > count.tmp" "pipe to wc with output redirection"

	# env variables

	test_command "echo $" "echo only $"
	test_command "echo $USER" "echo with a variable"
	test_command 'echo "$USER"' "echo wih a variable and double quotes"

	# Operators

	test_command "echo a && echo b || echo c" "simple AST"
	test_command "echo a && ls | cat" "AST with pipe"
	test_command "pwd | cat && echo a || echo b" "pipe with AST"
	test_command "pwd | Miaou && echo a || echo b" "wrong pipe with AST"
	test_command "echo a || echo b && pwd | Miaou" "AST with wrong pipe"
	test_command "cd .. && pwd && cd minishell" "cd with ls"

	# Wildcards

	test_command "echo *" "only *"
	test_command "echo ***" "multiple ***"
	test_command "echo *a*" "with a char"
	test_command "echo M*ke**" "more and more"
	test_command "ls *a*" "with ls"


	# let's have some fun
	test_command "Miaou" "command not existing"
	#test_command 'echo "Processing files in directory:" && ls -la /usr/bin | head -20 | tail -10 | grep -v "total" | awk "{print \$9}" | sort | uniq | wc -l > count.tmp && cat count.tmp && echo "Files with permissions:" && find /usr/bin -type f -executable 2>/dev/null | head -5 | xargs ls -l | cut -d" " -f1,9 && echo "Current user info:" && whoami && echo "Current directory:" && pwd && echo "Date and time:" && date "+%Y-%m-%d %H:%M:%S" && echo "System info:" && uname -a | cut -d" " -f1-3 && echo "Memory usage:" && free -h 2>/dev/null | grep "Mem:" | awk "{print \$3\"/\"\$2}" && echo "PATH directories count:" && echo $PATH | tr ":" "\n" | wc -l && echo "Home directory contents:" && ls -1 $HOME | head -10 && echo "Process count:" && ps aux 2>/dev/null | wc -l && echo "Disk usage of current dir:" && du -sh . 2>/dev/null && echo "File types in current dir:" && file * 2>/dev/null | head -5 && echo "Environment variables count:" && env | wc -l && echo "Shell level:" && echo $SHLVL && echo "Terminal type:" && echo $TERM && echo "Language setting:" && echo $LANG && echo "Completed complex command execution"' "super complex long command with multiple pipes and redirections"

else
	test_command "/bin/ls" "test with absolute path"
fi

rm -rf "$TMP_DIR"
