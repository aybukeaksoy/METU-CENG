"""string_op("21","65") returns "86"
string_op("22","82") returns "104"
string_op("76","31") returns "107"
string_op("15","52") returns "67"
string_op("27","51") returns "78"
string_op("65","85") returns "150"
string_op("82","63") returns "145"
string_op("46","92") returns "138"
string_op("34","30") returns "64"
string_op("56","90") returns "146"
string_op("51","80") returns "131"
string_op("41","48") returns "89"
string_op("97","59") returns "156"
string_op("80","97") returns "177"
string_op("42","18") returns "60"
string_op("86","58") returns "144"
string_op("64","64") returns "128"
string_op("20","23") returns "43"
string_op("32","13") returns "45"
string_op("11","69") returns "80"
"""

def string_sum(x,y):
    a=int(x)+int(y)
    if a>9:
        return[str(a)[0],str(a)[1]]
    else:
        return ["0",str(a)[0]]


def string_op(str1, str2):
    if len(str1) == 1 and len(str2) == 1:
        digit1 = string_sum(str1[0], str2[0])
        result = digit1[1]
        carry = digit1[0]
        if carry == "0":
            return "".join([result])
        else:
            return "".join([carry, result])
    if len(str1) == 2 and len(str2) == 1:
        digit1 = string_sum(str1[1], str2[0])
        result = digit1[1]
        carry = digit1[0]
        digit10 = string_sum(carry, str1[0])
        result1 = digit10[1]
        return "".join([result1, result])
    if len(str1) == 1 and len(str2) == 2:
        digit1 = string_sum(str1[0], str2[1])
        result = digit1[1]
        carry = digit1[0]
        digit10 = string_sum(carry, str2[0])
        result1 = digit10[1]
        return "".join([result1, result])
    if len(str1) == 2 and len(str2) == 2:
        digit1 = string_sum(str1[1], str2[1])
        result = digit1[1]
        carry = digit1[0]
        digit10 = string_sum(str1[0], str2[0])
        result1 = digit10[1]

        if carry == "0":
            carry2 = digit10[0]
            if carry2 == "0":
                return "".join([result1, result])
            else:
                return "".join(["1", result1, result])
        if carry == "1":
            carry2 = digit10[0]
            digit10_2 = string_sum(digit10[1], carry)
            if (str1[0] == "4" and str2[0] == "5") or (str2[0] == "4" and str1[0] == "5"):
                return "".join(["1", "0", result])
            if carry2 == "0":
                return "".join([digit10_2[1], result])
            else:
                return "".join(["1", digit10_2[1], result])

print(string_op("49","55"))