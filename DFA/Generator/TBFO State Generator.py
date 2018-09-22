#-----------------------------------#
#                                   #
#  Aditya Putra Santosa / 13517013  #
#          Informatika ITB          #
#                                   #
#-----------------------------------#

from copy import deepcopy
from icecream import ic
from math import *

pilihan = (1,1)
#Fungsi fungsi penting
def win(board):
    for i in range(0,3):
        if(board[i][0]==board[i][1]==board[i][2]):
            if(board[i][0]==x):
                return x
            else:
                if(board[i][0]==o):
                    return o
    for i in range(0,3):
        if(board[0][i]==board[1][i]==board[2][i]):
            if(board[0][i]==x):
                return x
            else:
                if(board[0][i]==o):
                    return o
    if(board[0][0]==board[1][1]==board[2][2]):
            if(board[0][0]==x):
                return x
            else:
                if(board[0][0]==o):
                    return o
    if(board[0][2]==board[1][1]==board[2][0]):
            if(board[0][2]==x):
                return x
            else:
                if(board[0][2]==o):
                    return o
    return k
def score(board,depth):
    if(win(board)==x): #ganti ini
        return 10-depth
    elif(win(board)==o): #ganti ini
        return depth-10
    else:
        return 0
def gameOver(board):
    if(win(board)==k):
        return not((k in board[0] or k in board[1])or k in board[2])
    else:
        return True
def moveTersedia(board):
    move = []
    for i in range(0,3):
        for j in range(0,3):
            if(board[i][j]==k):
                temp = (i,j)
                move.append(temp)
    return move
def minmax(board,depth,player):
    #print(board)
    if(gameOver(board)):
        return score(board,depth)
    else:
        global pilihan
        depth += 1
        scores = []
        moves = []
        for mov in moveTersedia(board):
            boardTemp = deepcopy(board)
            boardTemp[mov[0]][mov[1]] = player
            if(player==x): #ganti ini
                nilai = minmax(boardTemp,depth,o) #ganti ini
            else:
                nilai = minmax(boardTemp,depth,x) #ganti ini
            scores.append(nilai)
            moves.append(mov)

        if(player==x): #ganti ini
            maksIndeks = scores.index(max(scores))
            pilihan = moves[maksIndeks]
            return scores[maksIndeks]
        else:
            minIndeks = scores.index(min(scores))
            pilihan = moves[minIndeks]
            return scores[minIndeks]
def genBoard(s):
    li = s.split(',')
    acuan = [(-1,-1),(0,0),(0,1),(0,2),(1,0),(1,1),(1,2),(2,0),(2,1),(2,2)]
    giliran = x
    hasil = [[k,k,k],
             [k,k,k],
             [k,k,k]
    ]
    for a in li:
        gerakan = acuan[int(a)]
        hasil[gerakan[0]][gerakan[1]] = giliran
        if(giliran==x):
            giliran = o
        else:
            giliran = x
    return hasil
def printBoard(s):
    if(not(s=='-')):
        li = genBoard(s)
        print(li[0])
        print(li[1])
        print(li[2])
        print('\n')
def putarKanan(s):
    li = s.split(',')
    putar = ['0','3','6','9','2','5','8','1','4','7']
    hasil = []
    for i in li:
        hasil.append(putar[int(i)])
    return ','.join(hasil)
def flipVer(s):
    li = s.split(',')
    putar = ['0','3','2','1','6','5','4','9','8','7']
    hasil = []
    for i in li:
        hasil.append(putar[int(i)])
    return ','.join(hasil)
def genAllRotFlip(s):
    hasil = []
    gBoard = []
    for i in range(0,4):
        if(not(s in hasil) and not(genBoard(s) in gBoard)):
            hasil.append(s)
            gBoard.append(genBoard(s))
        s = putarKanan(s)
    s = flipVer(s)
    for i in range(0,4):
        if(not(s in hasil) and not(genBoard(s) in gBoard)):
            hasil.append(s)
            gBoard.append(genBoard(s))
        s = putarKanan(s)
    return hasil
def genState(s,hasil):
    #genState('5',{})
    global pilihan
    board = genBoard(s)
    if(gameOver(board)):
        hasil[s] = ['-' for i in range(0,9)]
        return hasil
    else:
        temp = ['-' for i in range(0,9)]
        for mov in moveTersedia(board):
            boardTemp = deepcopy(board)
            boardTemp[mov[0]][mov[1]] = o #ganti ini
            if(not(gameOver(boardTemp))):
                minmax(boardTemp,0,x) #ganti ini
                awal = (mov[0]*3)+mov[1]+1
                nomor = (pilihan[0]*3)+pilihan[1]+1
                stateBaru = s+','+str(awal)+','+str(nomor)
                #cek apakah sudah ada sebelumnya
                cek = genAllRotFlip(stateBaru)
                for i in cek:
                    if(i in hasil):
                        stateBaru = i
                        break
                #sudah ada state dengan kondisi yang sama tapi diputar/mungkin tidak
                temp[awal-1] = stateBaru
            else:
                awal = (mov[0]*3)+mov[1]+1
                stateBaru = s+','+str(awal)
                temp[awal-1] = stateBaru
        hasil[s] = temp
        for i in temp:
            if(i!='-'):
                hasil[i] = []
        for i in temp:
            if(i!='-'):
                hasil = genState(i,hasil)
        return hasil           

#Generate semua state untuk comp mulai duluan
a = genState('5',{})
#Save ke file eksternal
file = open('states.txt','w')
for i in a:
    s = i.ljust(18)
    for n in a[i]:
        s = s + n.ljust(18)
    file.write(s)
    file.write('\n')
file.close()

