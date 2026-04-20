# Verifica se o Makefile está usando as flags corretas sem compilar de fato
make -n

# ----------------------------
# COMANDOS BÁSICOS
# ----------------------------

# Executa comando com caminho absoluto (não depende do PATH)
# Valida execve básico
/bin/ls

# Comando vazio (pressionar enter)
# Não deve quebrar nem executar nada
<empty>

# Apenas espaços
# Deve ser ignorado corretamente
"   "

# ----------------------------
# ARGUMENTOS
# ----------------------------

# Comando com argumentos simples
# Testa parsing básico de argumentos
/bin/ls arg1 arg2

# ----------------------------
# ECHO
# ----------------------------

# echo sem argumentos (deve imprimir newline)
echo

# echo com string simples
echo hello

# echo com -n (sem newline no final)
echo -n hello

# ----------------------------
# EXIT
# ----------------------------

# Sai do shell com código padrão
exit

# Sai com código específico
# Testa parsing de argumento numérico
exit <arg>

# ----------------------------
# STATUS CODE ($?)
# ----------------------------

# Executa comando válido
/bin/ls

# Deve imprimir 0 (sucesso)
echo $?

# Executa comando inválido
/bin/ls arquivoquenaoexiste

# Deve imprimir código de erro (!= 0)
echo $?

# Usa resultado anterior em expressão
# Testa expansão de variável + execução
expr $? + $?

# ----------------------------
# COMANDOS BLOQUEANTES / SINAIS
# ----------------------------

# Fica aguardando input (testar CTRL+C, CTRL+D, CTRL+\)
cat

# Também bloqueia aguardando input
grep "qualquercoisa"

# ----------------------------
# ASPAS DUPLAS
# ----------------------------

# Conteúdo não deve ser interpretado como pipe
# Tudo vira argumento literal
echo "cat lol.c | cat > lol.c"

# ----------------------------
# ASPAS SIMPLES
# ----------------------------

# Nada dentro deve ser interpretado (nem variáveis)
echo '$USER'

# ----------------------------
# ENVIRONMENT
# ----------------------------

# Lista variáveis de ambiente
env

# Cria variável
export VAR=teste

# Verifica se foi criada
env

# Sobrescreve variável
export VAR=novo

# Verifica atualização
env

# Remove variável
unset VAR

# Verifica remoção
env

# ----------------------------
# CD / PWD
# ----------------------------

# Vai para HOME
cd

# Diretório atual (não muda nada)
cd .

# Volta um nível
cd ..

# Caminho válido
cd caminho

# Caminho inválido (deve dar erro)
cd caminho_invalido

# Mostra diretório atual
pwd

# ----------------------------
# CAMINHO RELATIVO
# ----------------------------

# Executa binário no diretório atual
./programa

# Sobe um nível e executa
../programa

# Caminho mais complexo
../../programa

# ----------------------------
# PATH
# ----------------------------

# Executa usando PATH
ls
wc
awk

# Remove PATH
# Agora comandos sem caminho devem falhar
unset PATH
ls

# Define PATH manualmente
export PATH=/bin:/usr/bin

# Deve voltar a funcionar
ls

# ----------------------------
# REDIRECIONAMENTO
# ----------------------------

# Redireciona saída para arquivo (overwrite)
ls > file

# Redireciona entrada
cat < file

# Cria arquivo com conteúdo
echo hello > file

# Append no arquivo
echo hello >> file

# Heredoc (input multi-linha)
cat << EOF
hello
EOF

# ----------------------------
# PIPES
# ----------------------------

# Pipeline com múltiplos comandos
cat arquivo | grep bla | more

# Pipe simples
ls | grep bla

# Pipeline com erro no primeiro comando
ls arquivoquenaoexiste | grep bla | more

# Pipe estranho mas válido
cat | cat | ls

# ----------------------------
# PIPE + REDIRECIONAMENTO
# ----------------------------

# Mistura pipe com output file
cat arquivo | grep bla > out

# ----------------------------
# ERROS
# ----------------------------

# Comando inexistente
# Deve mostrar erro e não crashar
dsbksdgbksdghsd

# ----------------------------
# VARIÁVEIS DE AMBIENTE
# ----------------------------

# Expansão simples
echo $USER

# Expansão dentro de aspas duplas
echo "$USER"

# ----------------------------
# BONUS (se implementado)
# ----------------------------

# AND lógico
ls && echo ok

# OR lógico
ls || echo fail

# Agrupamento
(ls && echo ok)

# Wildcard (expansão de arquivos)
echo *