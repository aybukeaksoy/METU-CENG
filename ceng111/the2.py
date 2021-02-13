#
# WRITE YOUR CODE HERE AND SEND ONLY THIS FILE TO US.
#
# DO NOT DEFINE get_data() here. Check before submitting

import math
import random
from evaluator import *
    # get_data() will come from this import


initial_states = get_data()
# individual states in lists
individual_states = initial_states[6]
last_moves = [i[1] for i in initial_states[6]]
mask_statuses = [i[2] for i in initial_states[6]]
infection_statuses = [i[3] for i in initial_states[6]]
positions = [i[0] for i in initial_states[6]]
n = len(individual_states)
# defining system constants
mu = initial_states[5]
column = initial_states[1]
row = initial_states[0]
k = initial_states[3]
lambda1 = initial_states[4]
d = initial_states[2]
infection_statuses_copy = infection_statuses[:]

direction_dict = {0: [0, 1], 1: [-1, 1], 2: [-1, 0],3: [-1, -1], 4: [0, -1], 5: [1, -1], 6: [1, 0], 7: [1, 1]}
#defining the movement probabilites according to direction and color.
green = mu / 2
yellow = mu / 8
blue = (1 - mu - mu ** 2) / 2
purple = 2 * (mu ** 2) / 5
gray = (mu ** 2) / 5
color_list = [green, yellow, blue, purple, gray, purple, blue, yellow]

#returns the updated states of the individuals in a list.
def new_move():
    global positions, last_moves, mask_statuses, infection_statuses_copy
    movement()
    infection()
    result_list = []
    for i in range(n):
        last = [positions[i]] + [last_moves[i]] + [mask_statuses[i]] + [infection_statuses_copy[i]]
        result_list.append(last)
    return result_list


#this function decides the new coordinates and the movement randomly.
def decide_next_move(last_move, dd, cl):
    if last_move == 0:
        moves = [0, 1, 2, 3, 4, 5, 6, 7]
        movement_probability = random.choices(moves, cl)
        position_change = dd[movement_probability[0]]
        return [movement_probability[0], position_change]
    elif last_move == 1:
        moves = [1, 2, 3, 4, 5, 6, 7, 0]
        movement_probability = random.choices(moves, cl)
        position_change = dd[movement_probability[0]]
        return [movement_probability[0], position_change]
    elif last_move == 2:
        moves = [2, 3, 4, 5, 6, 7, 0, 1]
        movement_probability = random.choices(moves, cl)
        position_change = dd[movement_probability[0]]
        return [movement_probability[0], position_change]
    elif last_move == 3:
        moves = [3, 4, 5, 6, 7, 0, 1, 2]
        movement_probability = random.choices(moves, cl)
        position_change = dd[movement_probability[0]]
        return [movement_probability[0], position_change]
    elif last_move == 4:
        moves = [4, 5, 6, 7, 0, 1, 2, 3]
        movement_probability = random.choices(moves, cl)
        position_change = dd[movement_probability[0]]
        return [movement_probability[0], position_change]
    elif last_move == 5:
        moves = [5, 6, 7, 0, 1, 2, 3, 4]
        movement_probability = random.choices(moves, cl)
        position_change = dd[movement_probability[0]]
        return [movement_probability[0], position_change]
    elif last_move == 6:
        moves = [6, 7, 0, 1, 2, 3, 4, 5]
        movement_probability = random.choices(moves, cl)
        position_change = dd[movement_probability[0]]
        return [movement_probability[0], position_change]
    elif last_move == 7:
        moves = [7, 0, 1, 2, 3, 4, 5, 6]
        movement_probability = random.choices(moves, cl)
        position_change = dd[movement_probability[0]]
        return [movement_probability[0], position_change]

#this function updates the positions of each individual if the new coordinate
#is not already occupied and it is in with the borders of the coordinate system.
def movement():

    global last_moves, direction_dict, color_list, row, column, positions

    for i in range(n):
        positions[i] = list(positions[i])

    for i in range(n):
        x = positions[i][0]
        y = positions[i][1]
        # calling decide_next_move only once.
        result = decide_next_move(last_moves[i], direction_dict, color_list)
        a = result[1][0]
        b = result[1][1]
        # this if conditional checks if the cell is already occupied and if the cell is not in the coordinate system.
        if (0 <= x + a < column) and (0 <= y + b < row) and ([x + a, y + b] not in positions):
            positions[i][0] = x + a
            positions[i][1] = y + b
            last_moves[i] = result[0]

    for i in range(n):
        positions[i] = tuple(positions[i])


#this function calculates the euclidean distance
def calculate_distance(c1, c2):
    calc_dist = math.sqrt((c1[0] - c2[0]) ** 2 + (c1[1] - c2[1]) ** 2)
    return calc_dist

#this function returns the infection probability according to mask statuses of the individuals.
def compute_infection_probability(m1, m2, dist):
    global k, lambda1
    if m1 == "masked" and m2 == "masked":
        infection_probability = min(1, k / (dist ** 2)) / (lambda1 ** 2)
        return infection_probability
    if (m1 == "masked" and m2 == "notmasked") or (m1 == "notmasked" and m2 == "masked"):
        infection_probability = min(1, k / (dist ** 2)) / lambda1
        return infection_probability
    if m1 == "notmasked" and m2 == "notmasked":
        infection_probability = min(1, k / (dist ** 2))
        return infection_probability

#this functions decides the new infection status of the individuals randomly.
#will be called only when distance is less than d and one of the individuals is infected
def decide_infection_status(p):
    infection_status = random.choices(["infected", "notinfected"], [p, 1 - p])
    return infection_status[0]

#this function updates the new infection statuses of individuals
def infection():
    global n, infection_statuses, mask_statuses, infection_statuses_copy
    distances = []
    index_list = []
    for i in range(n - 1):
        for j in range(i + 1, n):
            distances.append(calculate_distance(
                list(positions[i]), list(positions[j])))
            index_list.append([i, j])
    for i in range(len(distances)):
        if distances[i] <= d:
            if (infection_statuses[index_list[i][0]] == "notinfected") and (infection_statuses[index_list[i][1]] == "infected"):
                inf_prob = compute_infection_probability(mask_statuses[index_list[i][0]], mask_statuses[index_list[i][1]], distances[i])
                new_infection_status = decide_infection_status(inf_prob)
                if new_infection_status == "infected":
                    infection_statuses_copy[index_list[i][0]] = "infected"
            elif (infection_statuses[index_list[i][0]] == "infected") and (infection_statuses[index_list[i][1]] == "notinfected"):
                inf_prob = compute_infection_probability(mask_statuses[index_list[i][0]], mask_statuses[index_list[i][1]], distances[i])
                new_infection_status = decide_infection_status(inf_prob)
                if new_infection_status == "infected":
                    infection_statuses_copy[index_list[i][1]] = "infected"

    for i in range(len(infection_statuses)):
        infection_statuses[i] = infection_statuses_copy[i]