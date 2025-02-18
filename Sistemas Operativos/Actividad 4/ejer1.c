#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main() {
    pid_t pid = fork(); // Crear un proceso hijo

    if (pid < 0) { // Si hay error al crear el proceso hijo
        perror("Error al crear el proceso hijo");
        return 1;
    } else if (pid == 0) { // Código del proceso hijo
        printf("Soy el proceso hijo con PID %d y voy a terminar al proceso padre con PID %d\n", getpid(), getppid());
        kill(getppid(), SIGKILL); // Matar al proceso padre
    } else { // Código del proceso padre
        printf("Soy el proceso padre con PID %d y he creado un hijo con PID %d\n", getpid(), pid);
        while(1); // Mantener al padre vivo hasta que sea terminado
    }

    return 0;
}
