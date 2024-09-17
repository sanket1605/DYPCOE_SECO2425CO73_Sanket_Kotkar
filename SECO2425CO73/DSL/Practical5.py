# Function to implement Selection Sort
def selection_sort(arr):
    n = len(arr)
    for i in range(n):
        min_index = i
        for j in range(i + 1, n):
            if arr[j] < arr[min_index]:
                min_index = j
        # Swap the found minimum element with the first element
        arr[i], arr[min_index] = arr[min_index], arr[i]
    return arr

# Function to implement Bubble Sort
def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                # Swap if the element found is greater than the next element
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        # If no elements were swapped, the array is sorted
        if not swapped:
            break
    return arr

# Function to display top five scores
def display_top_five(arr):
    # Display the top five highest scores in descending order
    print("Top five scores are:", arr[-5:][::-1])

# Take user input for the number of students
n = int(input("Enter the number of students: "))

# Input: List of student percentages (entered one by one)
percentages = []
for i in range(n):
    percent = float(input(f"Enter percentage for student {i+1}: "))
    percentages.append(percent)

# Sorting using Selection Sort
sorted_selection = selection_sort(percentages.copy())
print("\nSorted array using Selection Sort:", sorted_selection)
display_top_five(sorted_selection)

# Sorting using Bubble Sort
sorted_bubble = bubble_sort(percentages.copy())
print("\nSorted array using Bubble Sort:", sorted_bubble)
display_top_five(sorted_bubble)
