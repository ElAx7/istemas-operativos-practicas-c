#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main() {
	pid_t pid = fork(); //Proceso hijo

	if (pid < 0){ // Error al crear hijo
	perror("Error al crear hijo");
	return 1;
	} else if(pid == 0){ //Codigo hijo
	printf("Hijo iniciado con PID %d\n", getpid());
	sleep(20); // Sleep de 20
	printf("Hijo con PID %d ha terminado\n", getpid());
	exit(0); //Termina proceso
	}else { //Proceso padre
	printf("Padre iniciado con PID %d y hijo con PID %d\n", getpid(), pid);
	sleep(1); //Sleep 1
	printf("Padre con PID %d ha terminado\n", getpid());
	}
	return 0;
}
