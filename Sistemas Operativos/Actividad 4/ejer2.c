#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork(); // proceso hijo

    if (pid < 0) { // error al crear el hijo
        perror("Error al crear el proceso hijo");
        return 1;
    } else if (pid == 0) { // Código proceso hijo
        printf("Hijo iniciado con PID %d\n", getpid());
        sleep(1); // El hijo duerme por 1 segundo
        printf("Hijo con PID %d ha terminado\n", getpid());
        exit(0); // Termina el proceso hijo
    } else { // Código del proceso padre
        printf("Padre iniciado con PID %d y hijo con PID %d\n", getpid(), pid);
        sleep(20); // El padre duerme por 20 segundos
        printf("Padre con PID %d ha terminado\n", getpid());
    }

    return 0;
}

