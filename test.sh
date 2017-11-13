# **************************************************************************** #
#                                                                              #
#                                                             |\               #
#    test.sh                                            ------| \----          #
#                                                       |    \`  \  |  p       #
#    By: cshepard6055 <cshepard6055@floridapoly.edu>    |  \`-\   \ |  o       #
#                                                       |---\  \   `|  l       #
#    Created: 2017/11/13 17:05:46 by cshepard6055       | ` .\  \   |  y       #
#    Updated: 2017/11/13 17:05:52 by cshepard6055       -------------          #
#                                                                              #
# **************************************************************************** #

touch fi.c
cp Fibonacci.c fi.c
echo main.test >> fi.c
gcc -o fi fi.c
./fi

# Clean up. Comment this out if you do not want this to happen.
rm fi
