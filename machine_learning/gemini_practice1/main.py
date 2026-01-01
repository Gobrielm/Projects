
from dotenv import load_dotenv
from google import genai
from pathlib import Path
import os

load_dotenv()

client = genai.Client(
    api_key=os.getenv("GEMINI_API_KEY")
)

def remove_temp_file(file_name: str):
    temp_file_path = Path(f"temp+{file_name}")
    if temp_file_path.exists():
        temp_file_path.unlink()

def merge_temp_file(file_name: str):
    original_file_path = Path(file_name)
    temp_file_path = Path(f"temp+{file_name}")

    if original_file_path.exists():
        original_file_path.unlink()
    
    if temp_file_path.exists():
        temp_file_path.rename(file_name)

def main():
    file_name = input("Enter File To Interpret: ")
    try:
        with open(file_name, "r", encoding="utf-8") as f:
            data = f.read()
    except FileNotFoundError:
        print(f"Error: File '{file_name}' not found.")
        return
    except Exception as e:
        print(f"Error reading file: {e}")
        return
    
    instruction = input("Enter Command for Gemini to interpret file with: ")

    try:
        response = client.models.generate_content(
            model="gemini-2.5-flash-lite",
            contents=[instruction, data],
            config={
                "system_instruction": "You are a professional computer scientist. Be concise. Additionally, you are writting real code, do not extra syntax or explanation that isn't code safe",
                "temperature": 0.3
            }
        )

        # Check if response.text is None or empty before writing
        if response.text:
            temp_file_path = Path(f"temp+{file_name}")
            with open(temp_file_path, "w", encoding="utf-8") as f_out:
                f_out.write(response.text)
            print(f"Analysis saved to {temp_file_path}")

            while True:
                user_input = input("Merge File In (y/n): ")
                if user_input.lower() == 'y': 
                    merge_temp_file(file_name)
                    break
                elif user_input.lower() == 'n': 
                    remove_temp_file(file_name)
                    break
                else:
                    print("Invalid input. Please enter 'y' or 'n'.")
        else:
            print("API returned no text content.")
            remove_temp_file(file_name) # Clean up temp file if no content
        
    except Exception as e:
        print(f"API Error: {e}")

if __name__ == "__main__":
    main()
