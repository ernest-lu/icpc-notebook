alias c='g++ -Wall -Wconversion -Wfatal-errors -g -DLOCAL -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -std=c++17 \
	-fsanitize=undefined,address'
alias gc='g++ -Wall -Wconversion -Wfatal-errors -g -std=c++17'
xmodmap -e 'clear lock' -e 'keycode 66=less greater' #caps = <>
