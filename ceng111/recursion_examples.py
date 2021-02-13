def reverse_list(lst):
    if lst==[]:
        return []
    else:
        return [lst[-1]]+reverse_list(lst[:-1])

#print(reverse_list([1,3,5,2,7]))

def nested_reverse(liste):
    if liste==[]:
        return []
    if type(liste[-1])==list:
        return [nested_reverse(liste[-1])]+nested_reverse(liste[:-1])
    else:
        return [liste[-1]]+nested_reverse(liste[:-1])

#print(nested_reverse([[3,4,[5]],[8],0,2,4]))

def flatten(liste):
    if liste==[]:
        return []
    if type(liste[0])==list:
        return flatten(liste[0])+flatten(liste[1:])
    else:
        return [liste[0]]+flatten(liste[1:])

#print(flatten([[3, 4, [5]], [8], 0, 2, 4]))

def sum_all(liste):
    if liste==[]:
        return 0
    if type(liste[0])==list:
        return sum_all(liste[0])+sum_all(liste[1:])
    else:
        return liste[0]+sum_all(liste[1:])

#print(sum_all([[3, 4, [5]], [8], 0, 2, 4]))

def branch(index,liste):
    if len(index)==1:
        return liste[index[0]]
    else:
        return branch(index[1:],liste[index[0]])

#print(branch([0,2,0],[[3, 4, [5]], [8], 0, 2, 4]))

def reverse_string(str1):
    if str1=="":
        return ""
    else:
        return str1[-1]+reverse_string(str1[:-1])

#print(reverse_string("aybuke"))

def reverse_string_list(n):
    if type(n)==str:
        if n=="":
            return ""
        else:
            return n[-1]+reverse_string_list(n[:-1])
    else:
        if n==[]:
            return []
        if type(n[-1])==list:
            return [reverse_string_list(n[-1])]+reverse_string_list(n[:-1])
        else:
            return [n[-1]]+reverse_string_list(n[:-1])

#print(reverse_string_list("aybuke"))

def palindrome(string):
    if string=="" or len(string)==1:
        return True
    if string[-1]==string[0]:
        return palindrome(string[1:-1])
    else:
        return False

#print(palindrome("elele"))