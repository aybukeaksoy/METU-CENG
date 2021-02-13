def sequential(x,liste):
    if liste==[]:
        return False
    if liste[0]==x:
        return True
    else:
        return sequential(x,liste[1:])

print(sequential(0,[4,1,2,3,4]))

def binary_search(x,liste):
    liste=sorted(liste)
    if liste==[]:
        return False
    if liste[len(liste)//2]==x:
        return True
    elif x<liste[len(liste)//2]:
        return binary_search(x,liste[:len(liste)//2])
    else:
        return binary_search(x,liste[(len(liste)//2)+1:])

print(binary_search(5,[8,67,33,4,9]))

def insertion(x,liste):
    if liste==[]:
        return [x]
    if liste[0]>x:
        return [x]+liste
    else:
        return liste[:1]+insertion(x,liste[1:])

def insertion_sort(liste):
    if liste==[]:
        return []
    if len(liste)==1:
        return liste
    else:
        return insertion(liste[0],insertion_sort(liste[1:]))
print(insertion_sort([1,5,2,33,24,89]))