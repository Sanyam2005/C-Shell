# C-Shell
Mini Project 1 of Operating Systems and Networks Course. I have implemented a custom C shell from scratch
Here's a concise list of functions your shell performs with their formats and descriptions for the README file:

---

### Functions and Descriptions

1. **Shell Prompt**  
   - **Format:** `<Username@SystemName:~>`  
   - Displays a dynamic shell prompt with the current username, system name, and working directory. The home directory is denoted as `~`. Changes with directory navigation.

2. **Command Execution**  
   - **Format:** `<command> [args]`  
   - Executes standard system commands, with support for both foreground and background processes using `&`. Prints process details for background tasks.

3. **Custom Commands**  
   - **`hop`**  
     - **Format:** `hop [<path>]`  
     - Changes the current directory. Supports symbols like `~`, `.`, `..`, and `-`. Prints the full path after navigation.  
   - **`reveal`**  
     - **Format:** `reveal [-a | -l | -a -l] [<path>]`  
     - Lists files and directories with optional flags for hidden files (`-a`) and detailed info (`-l`). Uses color-coding for file types.  
   - **`log`**  
     - **Format:** `log`  
     - Displays the last 15 commands, excluding duplicates and `log` commands.  
     - **Subcommands:**  
       - `log purge`: Clears command history.  
       - `log execute <index>`: Executes a command from the log by its index.  
   - **`proclore`**  
     - **Format:** `proclore [<pid>]`  
     - Displays process details (PID, status, group, memory, executable path). Defaults to the shell process if no PID is given.  
   - **`seek`**  
     - **Format:** `seek [-d | -f | -e] <target> [<directory>]`  
     - Searches for files or directories matching the target in the specified directory. Supports flags for file-only (`-f`), directory-only (`-d`), and auto-navigation or display (`-e`).

4. **I/O Redirection**  
   - **Format:** `<command> [args] > <file>`  
   - Redirects output to a file, appending (`>>`) or overwriting (`>`). Accepts input from a file using `<`.

5. **Pipes**  
   - **Format:** `<command1> | <command2>`  
   - Chains commands by passing output of one as input to the next. Supports multiple pipes.

6. **Combined Redirection and Pipes**  
   - **Format:** `<command1> < <file1> | <command2> | ... > <file2>`  
   - Combines pipes and I/O redirection seamlessly.

7. **Activities**  
   - **Format:** `activities`  
   - Lists all processes spawned by the shell, showing PID, command name, and status (running/stopped).

8. **Signals**  
   - **Format:** `ping <pid> <signal_number>`  
   - Sends a signal to a process by its PID. Handles modulo 32 signal numbers.

9. **Custom Aliases**  
   - **Format:** Defined in `.myshrc`  
   - Enables custom command shortcuts, e.g., `alias home = hop ~`.

10. **Custom Functions**  
    - **Format:** Defined in `.myshrc`  
    - Example:  
      - `mk_hop`: Creates and navigates to a directory.  
      - `hop_seek`: Hops to a directory and searches for matching files/directories.

---
