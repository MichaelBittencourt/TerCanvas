#!/bin/bash
#
# envsetup.sh
#
# Configura funções uteis para o shell script
#
# Versão 1: Seta as funções croot, gettop curi
# Versão 2: Setando métodos para ir direto para todas as pastas 
#           principais da estrutura do Repositório, Ainda não está
#           funcionando para ir direto para o diretório de um arquivo
# Versão 3: Ajustando informações na mensagem de ajuda e iniciando protótipo
#           da função de ajuda hgr()
# Versão 4: Adicionando demais informações em hgr
#
# Michael Bittencourt, Fevereiro de 2018
#

MENSAGEM_USO="
Uso $0 [-h | -v ] ou source $(basename "$0")

  -h, --help		 Mostra esta tela de ajuda e sai
  -v, --version		 Mostra a versão e saa

EX
  source $(basename "$0")   Dessa forma ele carrega o Script para o ambiente atual do shell
  $0 --help --version       Assim exibe o menu de ajuda e em seguida a versao atual so $(basename "$0")"


HELP_MESSAGE="\n\nMenu de Ajuda\n\n
\"Invoke\". envsetup.sh\" from your shell to add the following functions to your environment:"


if test -n "$1" 
then
	while test -n "$1"
	do
		case "$1" in
			-h | --help)
				echo "$MENSAGEM_USO"
				exit 0
			;;
			-v | --version)
				echo -n $(basename "$0")
				# Extrai versão diretamente dos cabeçalhos do programa
				grep '^# Versão ' "$0" | tail -1 | cut -d : -f 1 | tr -d \#
				exit 0
			;;
			*)
				if test -n "$1"
				then
					echo Opção inválida: $1
					echo "Tente $0 --help"
					exit 1
				fi
			;;
		esac
		shift
	done
	exit 0
else

	echo "Script Executado"
	echo "Execute hgr para exibir o menu de ajuda"
	echo "Veja a opcao --help caso nao esteja funcionando para entender o uso do script"
	
fi

function gettop
{
    local TOPFILE=envsetup.sh
    if [ -n "$TOP" -a -f "$TOP/$TOPFILE" ] ; then
        echo $TOP
    else
        if [ -f $TOPFILE ] ; then
            # The following circumlocution (repeated below as well) ensures
            # that we record the true directory name and not one that is
            # faked up with symlink names.
            PWD= /bin/pwd
        else
            local HERE=$PWD
	    #echo $PWD
	    #echo $T
	    #echo $TOPFILE
            T=
            while [ \( ! \( -f $TOPFILE \) \) -a \( $PWD != "/" \) ]; do
                \cd ..
                T=`PWD= /bin/pwd`
	#	echo $PWD
	#	echo $T
            done
            \cd $HERE
            if [ -f "$T/$TOPFILE" ]; then
                echo $T
            fi
        fi
    fi
}

HELP_MESSAGE="$HELP_MESSAGE\tcroot\t - Volta para a raiz do Repositorio\n"
function croot()
{
    T=$(gettop)
    if [ "$T" ]; then
        \cd $(gettop)
    else
        echo "Couldn't locate the top of the tree.  Try setting TOP."
    fi
	
}

HELP_MESSAGE="$HELP_MESSAGE\tcsubject - Vai para o assunto escolhido\n\t\t   Para mais informacoes tente csubject --help\n"
function csubject(){
	subject=""
	if [ ! "$1" = "" ]
	then
		case "$1" in
		"-u" | "--uri")
			subject="URI"		
		;;
		"-alg" | "--algorithm")
			subject="Algorithms"
		;;
		"-ds" | "--data-structures")
			subject="DataStructures"
		;;
		"-hr" | "--hacker-rank")
			subject="HackerRank"
		;;
		"-it" | "--information-theory")
			subject="InformationTheory"
		;;
		"-codt" | "--codility")
			subject="Codility"
		;;
		*)
			exit 1
		;;
		esac
	fi
	shift
	language=""
	if [ ! "$1" = "" ]
	then
		case "$1" in
		"-j" | "--java")
			language="Java"		
		;;
		"-c" | "--C")
			language="C"
		;;
		"-c++" | "--C++" | "-cpp" | "--CPP")
			language="C++"
		;;
		"-p" | "--python")
			language="Python"
		;;
		*)
			exit 1
		;;
		esac
	fi
	T=$(gettop)
    	if [ "$T" ]; then
        	\cd $(gettop)"/$subject/$language"
	else
	        echo "Couldn't locate the top of the tree.  Try setting TOP."
	fi

}

HELP_MESSAGE="$HELP_MESSAGE\tcuri\t - Vai para o diretorio do URI\n\t\t   Para mais informacoes tente curi --help\n"
function curi(){
	if [ ! "$1" = "" ]
	then
		csubject --uri $1
	else
		csubject --uri
	fi
}

HELP_MESSAGE="$HELP_MESSAGE\tcalg\t - Vai para o diretorio Algorithm\n\t\t   Para mais informacoes tente calg --help\n"
function calg(){
	if [ ! "$1" = "" ]
	then
		csubject --algorithm $1
	else
		csubject --algorithm 
	fi
}

HELP_MESSAGE="$HELP_MESSAGE\tcds\t - Vai para o diretorio DataStructures\n\t\t   Para mais informacoes tente cds --help\n"
function cds(){
	if [ ! "$1" = "" ]
	then
		csubject --data-structures $1
	else
		csubject --data-structures
	fi
}

HELP_MESSAGE="$HELP_MESSAGE\tchr\t - Vai para o diretorio HackerRank\n\t\t   Para mais informacoes tente chr --help\n"
function chr(){
	if [ ! "$1" = "" ]
	then
		csubject --hacker-rank $1
	else
		csubject --hacker-rank
	fi
}

HELP_MESSAGE="$HELP_MESSAGE\tcit\t - Vai para o diretorio InformationTheory\n\t\t   Para mais informacoes tente cit --help\n"
function cit(){
	if [ ! "$1" = "" ]
	then
		csubject --information-theory $1
	else
		csubject --information-theory
	fi
}

HELP_MESSAGE="$HELP_MESSAGE\tcodt\t - Vai para o diretorio Codility\n\t\t   Para mais informacoes tente codt --help\n"
function ccodt(){
	if [ ! "$1" = "" ]
	then
		csubject --codility $1
	else
		csubject --codility
	fi
}


function godir () {
    if [[ -z "$1" ]]; then
        echo "Usage: godir <regex>"
        return
    fi
    T=$(gettop)
    if [[ ! -f $T/filelist ]]; then
        echo -n "Creating index..."
        (\cd $T; find . -wholename ./out -prune -o -wholename ./.repo -prune -o -type f > filelist)
        echo " Done"
        echo ""
    fi
    local lines
    lines=($(\grep "$1" $T/filelist | sed -e 's/\/[^/]*$//' | sort | uniq))
    if [[ ${#lines[@]} = 0 ]]; then
        echo "Not found"
        return
    fi
    local pathname
    local choice
    if [[ ${#lines[@]} > 1 ]]; then
        while [[ -z "$pathname" ]]; do
            local index=1
            local line
            for line in ${lines[@]}; do
                printf "%6s %s\n" "[$index]" $line
                index=$(($index + 1))
            done
            echo
            echo -n "Select one: "
            unset choice
            read choice
            if [[ $choice -gt ${#lines[@]} || $choice -lt 1 ]]; then
                echo "Invalid choice"
                continue
            fi
            pathname=${lines[$(($choice-1))]}
        done
    else
        pathname=${lines[0]}
    fi
    echo $pathname
    \cd $T/$pathname
}

HELP_MESSAGE="$HELP_MESSAGE\tjgrep\t - Greps on all local Java files.\n"
function jgrep()
{
    find . -name .repo -prune -o -name .git -prune -o  -type f -name "*\.java" -print0 | xargs -0 grep --color -n "$@"
}

HELP_MESSAGE="$HELP_MESSAGE\tcgrep\t - Greps on all local C/C++ files.\n"

function cgrep()
{
    find . -name .repo -prune -o -name .git -prune -o -type f \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.h' \) -print0 | xargs -0 grep --color -n "$@"
}

function hgr(){
	echo -e "$HELP_MESSAGE	

Look at the source to view more functions. The complete list is:"

    T=$(gettop)
    local A
    A=""
    for i in `cat $T/envsetup.sh | sed -n "/^function /s/function \([a-z_]*\).*/\1/p" | sort`; do
      A="$A $i"
    done
    echo $A
}

