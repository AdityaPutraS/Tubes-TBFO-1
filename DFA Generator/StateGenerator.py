#-----------------------------------#
#                                   #
#  Aditya Putra Santosa / 13517013  #
#          Informatika ITB          #
#                                   #
#-----------------------------------#

from copy import deepcopy

pilihan = (1,1)
k = '-'
o = 'O'
x = 'X' 
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
    if(win(board)==o): #ganti ini, set ke o untuk player duluan
        return 10-depth
    elif(win(board)==x): #ganti ini, set ke x untuk player duluan
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
            if(player==o): #ganti ini,set ke o untuk player duluan
                nilai = minmax(boardTemp,depth,x) #ganti ini, set ke x untuk player duluan
            else:
                nilai = minmax(boardTemp,depth,o) #ganti ini, set ke o untuk player duluan
            scores.append(nilai)
            moves.append(mov)

        if(player==o): #ganti ini, set ke o untuk player duluan
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
''' Fungsi yang tidak dipakai lagi :
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
'''
def genNomor(nomor):
    if(nomor<10):
        return '(00'+str(nomor)+')'
    else:
        if(nomor<100):
            return '(0'+str(nomor)+')'
        else:
            return '('+str(nomor)+')'
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
            boardTemp[mov[0]][mov[1]] = x #ganti ini, set ke x untuk player duluan
            if(not(gameOver(boardTemp))):
                minmax(boardTemp,0,o) #ganti ini, set ke o untuk player duluan
                awal = (mov[0]*3)+mov[1]+1
                nomor = (pilihan[0]*3)+pilihan[1]+1
                stateBaru = s+','+str(awal)+','+str(nomor)
                #cek apakah sudah ada sebelumnya
                #cek = [stateBaru] #cek = genAllRotFlip(stateBaru), untuk generate state setelah di rotate / flip / keduanya
                #for i in cek: #for dibiarkan, jaga jaga jika perlu mengenerate state rotate dan flip
                #    if(i in hasil):
                #        stateBaru = i
                #       break
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
#1Generate state untuk player mulai duluan
a = genState('5,1',{})
#ganti ke '5' untuk cpu mulai duluan, lalu ganti pula semua kode diatas yang ada #ganti ini
daftarState = []
#Modifikasi semua state di a agar isi nomor di depannya
cnt = 1
tempA = {}
for state in a:
    namaStateBaru = genNomor(cnt)+state
    daftarState.append(namaStateBaru)
    tempA[namaStateBaru] = a[state]
    cnt += 1
a = tempA
for state in a:
    for transisi in range(0,9):
        #Iter semua nama di a untuk nyari nomornya
        namaDicari = a[state][transisi]
        if(namaDicari != '-'):
            for iterState in a:
                namaIterState = iterState[5:]
                nomor = 0
                if(namaDicari == namaIterState):
                    nomor = int(iterState[1:4]) #mengambil angkanya dari format (###)#,#,#,...
                    break
            #Sudah ketemu nomornya
            a[state][transisi] = genNomor(nomor)+a[state][transisi]
#Save ke file eksternal statenya
file = open('daftarStatesPlayer.txt','w') #Ganti nama
cnt = 1
for i in daftarState:
    file.write(i)
    file.write('\n')
file.close()
#Save ke file eksternal finish statenya
finishState = []
file = open('finishStatePlayer.txt','w') #Ganti nama
for i in daftarState:
    strTest = i[5:]
    if(gameOver(genBoard(strTest))):
        file.write(i)
        file.write('\n')
file.close()
#5ave tabel transisi (a) ke file eksternal
file = open('statesPlayer.txt','w') #Ganti nama
for i in a:
    #s = i.ljust(23)
    s = ''
    for n in a[i]:
        s = s + n.ljust(23)
    file.write(s)
    file.write('\n')
file.close()
