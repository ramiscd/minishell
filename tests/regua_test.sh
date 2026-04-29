#!/bin/bash
# Test script based on comandos_regua.md

SHELL_BIN="./minishell"
PASS=0
FAIL=0
SKIP=0

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
RESET='\033[0m'

# Captures only stdout; prompt goes to stderr (rl_outstream = stderr)
run_test()
{
	local label="$1"
	local input="$2"
	local expected="$3"

	actual=$(printf "%s\nexit\n" "$input" | $SHELL_BIN 2>/dev/null)
	if [ "$actual" = "$expected" ]; then
		echo -e "${GREEN}[PASS]${RESET} $label"
		PASS=$((PASS + 1))
	else
		echo -e "${RED}[FAIL]${RESET} $label"
		echo    "       expected: |$(echo "$expected" | head -5)|"
		echo    "       got:      |$(echo "$actual"   | head -5)|"
		FAIL=$((FAIL + 1))
	fi
}

run_multi()
{
	local label="$1"
	local cmds="$2"
	local expected="$3"

	actual=$(printf "%s\nexit\n" "$cmds" | $SHELL_BIN 2>/dev/null)
	if [ "$actual" = "$expected" ]; then
		echo -e "${GREEN}[PASS]${RESET} $label"
		PASS=$((PASS + 1))
	else
		echo -e "${RED}[FAIL]${RESET} $label"
		echo    "       expected: |$(echo "$expected" | head -5)|"
		echo    "       got:      |$(echo "$actual"   | head -5)|"
		FAIL=$((FAIL + 1))
	fi
}

skip_test()
{
	echo -e "${YELLOW}[SKIP]${RESET} $1 — $2"
	SKIP=$((SKIP + 1))
}

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== COMANDOS BÁSICOS ===${RESET}"
# ---------------------------------------------------------------------------

run_test  "/bin/ls executa sem erro"  "/bin/ls" "$(ls)"
run_test  "input vazio não quebra"    ""        ""
run_test  "só espaços ignorado"       "   "     ""

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== ARGUMENTOS ===${RESET}"
# ---------------------------------------------------------------------------

run_test  "/bin/ls com args"  "/bin/ls /bin/ls /bin/echo"  "$(ls /bin/ls /bin/echo)"

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== ECHO ===${RESET}"
# ---------------------------------------------------------------------------

run_test  "echo sem args"   "echo"        "$(echo)"
run_test  "echo hello"      "echo hello"  "$(echo hello)"
run_test  "echo -n hello"   "echo -n hello" "$(echo -n hello)"

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== STATUS CODE (\$?) ===${RESET}"
# ---------------------------------------------------------------------------

run_multi "\$? após sucesso é 0" \
	"/bin/ls
echo \$?" \
	"$(ls)
0"

run_multi "\$? após falha é != 0 (usa /bin/false)" \
	"/bin/false
echo \$?" \
	"1"

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== ASPAS ===${RESET}"
# ---------------------------------------------------------------------------

run_test  'aspas duplas: pipe literal'   'echo "cat lol.c | cat > lol.c"'  'cat lol.c | cat > lol.c'
run_test  "aspas simples: sem expansão"  "echo '\$USER'"                    '$USER'

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== VARIÁVEIS DE AMBIENTE ===${RESET}"
# ---------------------------------------------------------------------------

run_test  "echo \$USER expande"   "echo \$USER"   "$USER"
run_test  'echo "$USER" expande'  'echo "$USER"'  "$USER"

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== ENV / EXPORT / UNSET ===${RESET}"
# ---------------------------------------------------------------------------

run_multi "export cria variável" \
	"export _TESTVAR=42
env | grep _TESTVAR" \
	"_TESTVAR=42"

run_multi "export sobrescreve variável" \
	"export _TESTVAR=42
export _TESTVAR=99
env | grep _TESTVAR" \
	"_TESTVAR=99"

run_multi "unset remove variável" \
	"export _TESTVAR=42
unset _TESTVAR
env | grep _TESTVAR" \
	""

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== CD / PWD ===${RESET}"
# ---------------------------------------------------------------------------

run_multi "cd sem args vai para HOME" \
	"cd
pwd" \
	"$HOME"

run_multi "cd . permanece no mesmo dir" \
	"cd .
pwd" \
	"$(pwd)"

run_multi "cd .. sobe um nível" \
	"cd ..
pwd" \
	"$(cd .. && pwd)"

run_multi "cd caminho inválido dá erro (echo \$?)" \
	"cd /caminho_invalido_xyz_abc
echo \$?" \
	"1"

run_test  "pwd exibe diretório atual"  "pwd"  "$(pwd)"

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== PATH LOOKUP ===${RESET}"
# ---------------------------------------------------------------------------

run_test  "ls via PATH"   "ls"   "$(ls)"
run_test  "wc via PATH"   "/bin/echo -n | wc -c" "0"

run_multi "unset PATH desabilita comandos sem caminho" \
	"unset PATH
ls
echo \$?" \
	"127"

run_multi "export PATH reabilita comandos" \
	"unset PATH
export PATH=/bin:/usr/bin
ls /bin/ls" \
	"/bin/ls"

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== REDIRECIONAMENTO ===${RESET}"
# ---------------------------------------------------------------------------

TMP=$(mktemp)

run_multi "ls > file (overwrite)" \
	"ls > $TMP
cat $TMP" \
	"$(ls)"

run_multi "cat < file (input)" \
	"echo hello > $TMP
cat < $TMP" \
	"hello"

run_multi "echo >> file (append)" \
	"echo first > $TMP
echo second >> $TMP
cat $TMP" \
	"first
second"

run_multi "heredoc << EOF" \
	"cat << EOF
hello
world
EOF" \
	"hello
world"

rm -f "$TMP"

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== PIPES ===${RESET}"
# ---------------------------------------------------------------------------

run_test  "ls | grep Makefile" \
	"ls | grep Makefile" \
	"Makefile"

run_test  "pipeline 3 comandos" \
	"echo hello world | grep hello | wc -l" \
	"$(echo hello world | grep hello | wc -l)"

run_multi "pipe com erro no primeiro (echo \$?)" \
	"ls /naoexiste_xyz_abc | grep bla
echo \$?" \
	"1"

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== ERROS ===${RESET}"
# ---------------------------------------------------------------------------

run_multi "comando inexistente retorna 127" \
	"dsbksdgbksdghsd
echo \$?" \
	"127"

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== BONUS ===${RESET}"
# ---------------------------------------------------------------------------

skip_test "&& (AND lógico)"    "não implementado"
skip_test "|| (OR lógico)"     "não implementado"
skip_test "() agrupamento"     "não implementado"
skip_test "* wildcard"         "não implementado"

# ---------------------------------------------------------------------------
echo -e "\n${CYAN}=== SINAIS (manual) ===${RESET}"
# ---------------------------------------------------------------------------

skip_test "Ctrl+C interrompe cat"        "requer teste manual"
skip_test "Ctrl+D encerra shell"         "requer teste manual"
skip_test "Ctrl+\\ não termina o shell"  "requer teste manual"

# ---------------------------------------------------------------------------
echo ""
echo -e "${CYAN}========================================${RESET}"
echo -e "  ${GREEN}PASS: $PASS${RESET}  ${RED}FAIL: $FAIL${RESET}  ${YELLOW}SKIP: $SKIP${RESET}"
echo -e "${CYAN}========================================${RESET}"

[ $FAIL -eq 0 ] && exit 0 || exit 1
