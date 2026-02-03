# Minishell 42
*This project has been created as part of the 42 curriculum by Thbouver and Glucken*
## Description

### Architecture
```mermaid
graph TD
    A[Initialise] --> B{Split}
    B --> C[A]
    B --> D[B]
    B --> E[C]
    C --> F[EOF]
    D --> F
    E --> F

style A,B fill:#bbdefb
style C fill:#c8e6c9
```
<details>
<summary> Intialisation</summary>
init_minishell()
copy envp
setup_signal???
read one line with read_line()
process the line with process_command()
<details>
<summary>Read and go to process</summary>


</details>

````

## Instruction

## Resources
