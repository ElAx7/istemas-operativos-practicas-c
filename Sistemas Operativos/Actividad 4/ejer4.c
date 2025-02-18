#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void nietos(){ //Funcion para los 3 procesos hijos
	for (int i = 0; i < 3; i++){
	pid_t pid_nieto = fork();
	if (pid_nieto == 0){ //Codigo nietos
		printf("Nieto con PID %d y padre con PID %d\n", getpid(), getppid());
		sleep(20); //Cada nieto duerme 20 segundos
		exit(0);
		}else if (pid_nieto < 0){
			perror("Error al crear el nieto");
			exit(1);
		}
	}
}

int main(){
	pid_t pid_hijo1, pid_hijo2,
	
	//Hijo1
	pid_hijo1 = fork();
	if(pid_hijo == 0){
		printf("Hijo 1 con PID %d y padre con PID %d\n", getpid(), getppid());
		nietos();
		sleep(20);
		exit(0);
	}else if (pid_hijo1 < 0){
		perror("Error al crear al hijo1 ");
		exit(1);
	} 

	//Hijo2
        pid_hijo2 = fork();
        if(pid_hijo == 0){ 
                printf("Hijo 2 con PID %d y padre con PID %d\n", getpid(), getppid());
                nietos();
                sleep(20);
                exit(0);
        }else if (pid_hijo2 < 0){
                perror("Error al crear al hijo2");
                exit(1);
        } 
	
	printf("Padre con PID %d\n", getpid());
	sleep(5);

	kill(pid_hijo1, SIGKILL);
	kill(pid_hijo2, SIGKILL);

	printf("Padre a terminado los hijos y nietos\n");

	return 0; // Termina padre
}
