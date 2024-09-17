# Function to implement quicksort
def quick_sort(arr):
    if len(arr) <= 1:
        return arr
    else:
        pivot = arr[len(arr) // 2]
        left = [x for x in arr if x < pivot]
        middle = [x for x in arr if x == pivot]
        right = [x for x in arr if x > pivot]
        return quick_sort(left) + middle + quick_sort(right)

# Function to display sorted array and top 5 scores
def display_top_five(scores):
    sorted_scores = quick_sort(scores)
    print(f"Sorted array using Quick Sort: {sorted_scores}")
    
    # Get top 5 scores in descending order
    top_five = sorted_scores[-5:][::-1]  
    print(f"Top five scores are: {top_five}")

# Input from user
students_percentages = []

num_students = int(input("Enter the number of students: "))  # User inputs the number of students

# Enter percentages one by one
for i in range(num_students):
    percentage = float(input(f"Enter percentage for student {i + 1}: "))
    students_percentages.append(percentage)

# Display the sorted array and top 5 scores
display_top_five(students_percentages)
