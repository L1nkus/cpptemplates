from random import randint
q = 2000000
f = open('in.in', 'w')
# f.write("{}\n".format(q))
n = 57
f.write("{} ".format(n))
f.write("{} ".format(q))
while(q > 0):
    q -= 1
    mode = randint(1,2)
    f.write("{} ".format(mode))
    l = randint(0,n)
    r = randint(l,n)
    if mode == 1:
        f.write("{} {}\n".format(l,r))
    else:
        f.write("{} {} {}\n".format(l,r,randint(-100,100)))
f.close()
