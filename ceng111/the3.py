#this function takes the deep copy of the part_list
def get_copy(part_list):
    part_list_copy = [ele[:] for ele in part_list]
    for p in range(len(part_list_copy)):
        if type(part_list_copy[p][1]) != float:
            for i in range(1, len(part_list_copy[p])):
                part_list_copy[p][i] = list(part_list_copy[p][i])
    return part_list_copy

#this function finds the root of the tree by looking at part_list_copy
def find_root(part_list_copy):
    node=[]
    queue=[]
    children=[]
    for i in part_list_copy:
        node.append(i[0])
        queue+=i[1:]
    while queue:
        first=queue[0]
        queue=queue[1:]
        if type(first)==list:
            queue+=first
        if type(first)==str:
            children.append(first)
    for n in node:
        if n not in children:
            for p in part_list_copy:
                if p[0]==n:
                    return p

#this function finds the child of a node from part_list and returns it as a node.
def find_child(part_list_copy,child):
    for p in part_list_copy:
        if child==p[0]:
            return p


#this function appends the children to their parent recursively.(does not contain the root of the tree)
def make_tree_recursive(root,part_list_copy):
    tree_without_root = []
    if len(part_list_copy)==1:
        return part_list_copy[0]

    else:
        for r in root[1:]:
            a = find_child(part_list_copy, r[1])
            if type(a) == list and type(a[1]) != float:
                r += make_tree_recursive(a, part_list_copy)
            else:
                r += a[1:]
            tree_without_root.append(r)
        return tree_without_root
#this function adds 1 and the root ([1,bike....]) to the tree to make recursion easier in other functions.
def make_tree(part_list):
    part_list_copy = get_copy(part_list)
    root=find_root(part_list_copy)
    t=make_tree_recursive(root,part_list_copy)
    if len(part_list_copy)==1:
        return t
    return [1,root[0]]+t

#this function finds the number of required parts by multiplying the numbers recursively.
def required_parts_helper(tree,count,required_parts):
   children=tree[2:]
   for child in children:
       if len(child)==3 and type(child[2])==float:
           required_parts+=[(count*child[0],child[1])]
       else:
           required_parts_helper(child,count*child[0],required_parts)
   return required_parts

#this function returns the required_parts.
def required_parts(part_list):
    tree=make_tree(part_list)
    if len(part_list)==1:
        return [(1,part_list[0][0])]
    return required_parts_helper(tree,1,[])

#this function takes two lists and finds the ones that are short in stock
#appends them to the short_list with required numbers
def stock_check(part_list,stock_list):
    stock_list_parts=[x[1] for x in stock_list]
    basic_parts=required_parts(part_list)
    short_list=[]
    for b in basic_parts:
        if b[1] not in stock_list_parts:
            short_list.append((b[1],b[0]))
        else:
            for s in stock_list:
                if s[1]==b[1] and b[0]>s[0]:
                    short_list.append((b[1],b[0]-s[0]))

    return short_list

#this function calculates the total price for each basic_part needed and appends them to the prices list.
def calculate_price_helper(tree,sum,prices):
    children = tree[2:]
    for child in children:
        if len(child) == 3 and type(child[2]) == float:
             prices+=[(sum*child[0]*child[2],child[1])]
        else:
            calculate_price_helper(child,sum*child[0],prices)
    return prices

#this function sums all the prices that comes from calculate_price_helper and returns the total price.
def calculate_price(part_list):
     tree=make_tree(part_list)
     basic_parts_prices=calculate_price_helper(tree,1,[])
     total=0
     if len(part_list)==1:
         return part_list[0][1]
     for basic in basic_parts_prices:
         total+=basic[0]
     return total
