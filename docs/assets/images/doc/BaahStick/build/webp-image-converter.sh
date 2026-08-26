#!/bin/bash

# Check if 'cwebp' command is available
if ! command -v cwebp &> /dev/null; then
    echo "Error: 'cwebp' command not found. Please make sure you have the 'webp' package installed."
    exit 1
fi

# Prompt user for source directory path
read -p 'Enter the absolute source directory path: ' source_directory

# Prompt user for target directory path where references need to be updated
read -p 'Enter the absolute target directory path for reference updates: ' target_directory

# Check if the source directory exists
if [ ! -d "$source_directory" ]; then
    echo "Error: Source directory does not exist."
    exit 1
fi

# Check if the target directory exists
if [ ! -d "$target_directory" ]; then
    echo "Error: Target directory does not exist."
    exit 1
fi

# Create a directory to store original files
original_directory="$source_directory/original"
mkdir -p "$original_directory"

# Initialize an array to store files to process
files_to_process=()

# Find image files and populate the array
while IFS= read -r file; do
    filename=$(basename -- "$file")
    extension="${filename##*.}"
    filename_without_extension="${filename%.*}"

    # Directory location of the file
    directory=$(dirname "$file")

    # Move original file to the "original" directory
    mv "$file" "$original_directory"

    # Convert image to WebP format
    cwebp -q 85 -mt "$original_directory/$filename" -o "$directory/$filename_without_extension.webp"

    # Define the text to search for and the text to replace it with
    replace_text="$filename_without_extension.webp"

    # Find and replace references in files
    find "$target_directory" \
        -type d \( -name "node_modules" -o -name "build" -o -name "apache" -o -name ".idea" -o -name ".husky" -o -name "vendor" -o -name ".git" -o -name ".vscode" \) -prune \
        -o -type f \( -name "package.json" -o -name "*.yaml" -o -name "*.yml" -o -name ".env" -o -name ".env.sample" -o -name "*.json" -o -name "*.sh" \) -prune \
        -o -type f -exec sed -i "s/$filename_without_extension.$extension/$replace_text/g" {} +

    # Add the file to the array
    files_to_process+=("$file")

    echo "Converted file: $filename"
done < <(find "$source_directory" -type f \( -iname "*.png" -o -iname "*.jpg" -o -iname "*.jpeg" \) \
        | grep -vE "node_modules|build|apache|\.idea|\.husky|vendor|\.git|package\.json|\.yaml|\.yml|\.env$|\.env\.sample|\.json$|assets|public|\.vscode|\.sh$")

# Initialize a counter for the converted files
converted_count=0

# Iterate through the array and increment the counter
for file in "${files_to_process[@]}"; do
    ((converted_count++))
done

echo "Image conversion and renaming completed. Moved original files to '$original_directory'. Converted $converted_count files and updated references."
