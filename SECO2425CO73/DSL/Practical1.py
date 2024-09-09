def union(l1, l2):
    union_list = []
    for i in l1:
        union_list.append(i)
    for i in l2:
        if i not in union_list:
            union_list.append(i)
    return union_list

def diff(l1, l2):
    diff_list = []
    for i in l1:
        if i not in l2:
            diff_list.append(i)
    return diff_list

def inter(l1, l2):
    inter_list = []
    for i in l1:
        if i in l2:
            inter_list.append(i)
    return inter_list

def symm_diff(l1, l2):
    symm_diff_list = []
    for i in l1:
        if i not in l2:
            symm_diff_list.append(i)
    for i in l2:
        if i not in l1:
            symm_diff_list.append(i)
    return symm_diff_list

def get_students(game_name):
    count = int(input(f"How many students play {game_name}? "))
    students = []
    for _ in range(count):
        roll_number = int(input(f"Enter roll number for student {_ + 1}: "))
        students.append(roll_number)
    print("\n")
    return students

def menu():
    cricket = get_students("cricket")
    badminton = get_students("badminton")
    football = get_students("football")
    
    print("\n Menu ")
    print("\n 1. List of students who play both cricket and badminton")
    print("\n 2. List of students who play either cricket or badminton but not both")
    print("\n 3. Number of students who play neither cricket nor badminton")
    print("\n 4. Number of students who play cricket and football but not badminton.\n")
    
    while True:
        ch = int(input("Enter Your Choice: "))
        
        if ch == 1:
            print("Students who play both cricket and badminton:", inter(cricket, badminton))
        elif ch == 2:
            print("Students who play either cricket or badminton but not both:", symm_diff(cricket, badminton))
        elif ch == 3:
            u = union(cricket, badminton)
            print("Number of students who play neither cricket nor badminton:", len(diff(football, u)))
        elif ch == 4:
            cricket_and_football = inter(cricket, football)
            result = diff(cricket_and_football, badminton)
            print("Students who play cricket and football but not badminton:", result)
        else:
            break

menu()