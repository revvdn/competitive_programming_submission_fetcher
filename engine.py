
def check(s) :
    target = "Timur"

    return sorted(s) == sorted(target)

t = int(input())

for _ in range (t) :
    n = int(input())
    s = input()

    if (check(s)) :
        print("YES")
    else :
        print("NO")

    

    