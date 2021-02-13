def three_bucket(pool,b1,b2,b3):
    if pool<0:
        return 0
    if pool==0:
        return 1
    else:
        return three_bucket(pool-b1,b1,b2,b3)+three_bucket(pool-b2,b1,b2,b3)+three_bucket(pool-b3,b1,b2,b3)


print(three_bucket(19,4,5,10))



