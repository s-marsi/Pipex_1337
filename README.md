# Pipex_1337 
This project aims to replicate the behavior of the shell pipe command using a custom C program. 

## Table of Contents
- [Subject](#subject)
- [Description](#description)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)

## Subject :
<ol style="margin-left: 15px;">
  <li style="font-size: 20px; font-weight: 600; color: red;">
     <a href="https://cdn.intra.42.fr/pdf/pdf/118145/en.subject.pdf" target="_blank" style="color: red; font-size: 15.5px; font-weight: 300; margin-left: 10px;"> subject.pdf </a>
  </li>
</ol>

## Description :
- Pipex : emulates the functionality of shell pipes through a custom C program. Designed to replicate the behavior of the pipe command, it offers a streamlined solution for inter-process communication. Enhance your understanding of system calls and process management with this project."

  
## Getting Started
### Prerequisites
- To use this program, you need a C compiler (e.g., GCC) and the make utility installed on your system.

### Installation
1. Clone the repository:
    ```bash
    git clone https://github.com/s-marsi/Pipex_1337.git Pipex
    cd Pipex
    ```
2. Compile the program:
    ```bash
    make all  # This will generate the pipex program.
    make clean      # This will remove object files.
    ```

<ol style="margin-left: 15px;">
  <li style="font-size: 20px; font-weight: 600;">
    Usage :
    <ul>
      <li>Execute in your bash terminal: <code>./pipex input_file cmd1 cmd2 output_file</code></li>
      <li> 
        - <code>./pipex</code>: the name of the program.
        - <code>input_file</code>: the file that serves as input for the program.
        - <code>cmd1</code>: the first command to apply to the input.
        - <code>cmd2</code>: the second command to apply to the output of cmd1.
        - <code>output_file</code>: the file to write the output to.
      </li>
      <li> For example : ```bash
        ./pipex Makefile cat "head -3" out_file.txt
        ```</li>
    </ul>
  </li>
</ol>
