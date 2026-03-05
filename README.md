# Minishell 42
*This project has been created as part of the 42 curriculum by Thbouver and Glucken*
## Description

### Architecture
```mermaid
graph TD
    A(0_Initialize) --> B(1_tokenizer)
    B --> C(2_create_ast)
    C --> D(3_expansion_and_wildcards)
    D --> E(4_execute_ast)
    E --> F(5_execute_pipeline)
    F --> G(6_execute_cmd)
    G --> H(7_clean)

```
<details>
<summary> Intialisation</summary>
init_minishell()
copy envp
setup_signal???
read one line with read_line()
process the line with process_command()
<details>
<summary>1_tokenizer</summary>
All the command line is split into tokens separate by space and operators (&&, ||, |) and parenthesis.
here we check if the parenthesis, quotes or double quotes are well closed.
<summary>2_create_ast</summary>
the ast is created respecting the priorities, such as | is prioritise on || and &&. a node is wether an opreator or a link list of strings.
<summary>3_expansion and  wildcards</summary>
We detect all variables with the $ and expand them to the value knonw in the environnement.



</details>

````

## Instruction

## Resources
