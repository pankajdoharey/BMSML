//prompt ≺≻ → ◇ ψ ⇒
//Increment Repl prompt line count.
char prompt[] = "\n[0]≻ ";
int repl_line_count = 0;
char* read_token(char *stream);

void increment_prompt(){
    sprintf(prompt,"\n[%d]≻ ", ++repl_line_count);
}
