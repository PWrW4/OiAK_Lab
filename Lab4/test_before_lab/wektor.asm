segment .text
 
; int suma(int a, int b)
; zwraca sumÄ a+b 
global suma
suma: 
  push rbp           ; zachowujemy starÄ wartoĹÄ ebp
  mov rbp, rsp     
  
  sub rsp, 4     ; przydzielenie pamiÄci na zmienna lokalna c
                 ; troche sztuczne w tej funkcji
  
  mov eax, edi   ; mov rax, [a]
  add eax, esi   ; add rax, [b]     
  mov [rbp-4], eax   ; mov [c], eax
                     ; wynik jest juz w eax
  
  mov rsp, rbp       ; zwolnienie pamiÄci na stosie
  pop rbp            ; przywrĂłcenie poprzedniej wartoĹci ebp
  ret                ; powrĂłt
