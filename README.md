# 🎥 CineManager 🍿  

Welcome to **CineManager**, a fun and interactive project for managing a **movie theater** with custom features like showing movies, selecting seats, and confirming purchases. This application is written in **C** and uses the **ncurses** library to provide a terminal-based interface.  

---

## 🚀 Features  

1. **Dynamic Movie Menu** 
   - Display a menu of movies with interactive options.  
   - Centered titles and ASCII art for a cinematic feel.  

2. **Seat Selection**  
   - Choose available seats for your favorite movies.  
   - Interactive grid to mark available and unavailable seats.  

3. **Progress Bar**
   - A fun loading bar to enhance user experience.  

4. **Purchase Confirmation** 
   - Confirmation boxes for finalizing your ticket purchase.  

5. **Receipt Generation** 
   - After purchase, a receipt is displayed with the total price.  

6. **File-Based Database**  
   - Stores seat availability and purchase data in a file-based system.  

---

## 🎉 Fun Fact  

I accidentally **messed up the `.gitignore` file**! Instead of `.gitignore`, I named it `.gitIgnore`. As a result, files like `Menu` and `animacion` that were supposed to be ignored are still tracked in the repository. I keep it that way because i think its a good memory. 

---

## 📂 File Structure  

- **`proyecto.c`**: Core logic and menu handling.  
- **`Menu.c`**: Handles the dynamic movie menu.  
- **`BarraDeCarga.c`**: Implements the loading/progress bar.  
- **`testAsientos.c`**: Seat selection logic.  
- **`recibo.c`**: Receipt generation.  
- **`cliente.c`**: Client-side operations for file handling.  
- **`servidor.c`**: Server-side logic for file sharing.  
- **`animacion.c`**: Fun animations for the terminal interface.  
- **`recibir_archivo.h`**: Header file for receiving files.  

---

## 🧑‍💻 How to Run  

1. Clone the repository:  
   ```bash  
   git clone https://github.com/LILE-Z/NcursesBUAP.git  
   ```  

2. Navigate to the directory:  
   ```bash  
   cd NcursesBUAP  
   ```  

3. Compile the code:  
   ```bash  
   gcc -o CineManager *.c -lncurses  
   ```  

4. Run the program:  
   ```bash  
   ./CineManager  
   ```  
