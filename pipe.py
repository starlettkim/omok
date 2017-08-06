import time
import os
import sys
from subprocess import Popen, PIPE, STDOUT

if len(sys.argv) < 4:
    sys.exit('Usage: python pipe.py ./refree ./player1 ./player2')

refree_pipe = Popen([sys.argv[1]], stdin = PIPE, stdout = PIPE, bufsize = 1)
player1_pipe = Popen([sys.argv[2]], stdin = PIPE, stdout = PIPE, bufsize = 1)
player2_pipe = Popen([sys.argv[3]], stdin = PIPE, stdout = PIPE, bufsize = 1)

x = 0
y = 0
format_str = str(x) + ' ' + str(y) + '\n'

loop = 1
while True:
    player1_pipe.stdin.write(format_str)
    player1_put = player1_pipe.stdout.readline()
    print('[' + str(loop) + '] player1: ' + player1_put),
    refree_pipe.stdin.write(player1_put + '1\n')
    judgement = refree_pipe.stdout.readline()
    if judgement != 'draw\n':
        break
    format_str = player1_put
    if loop == 19 * 19:
        break
    time.sleep(0.5)
    loop = loop + 1

    player2_pipe.stdin.write(format_str)
    player2_put = player2_pipe.stdout.readline()
    print('[' + str(loop) + '] player2: ' + player2_put),
    refree_pipe.stdin.write(player2_put + '2\n')
    judgement = refree_pipe.stdout.readline()
    if judgement != 'draw\n':
        break
    format_str = player2_put
    time.sleep(0.5)
    loop = loop + 1

print(judgement),

player1_pipe.kill()
player1_pipe.wait()
player2_pipe.kill()
player2_pipe.wait()
refree_pipe.kill()
refree_pipe.wait()

sys.exit()
