# Primo Homework di ROS (Robot Operating System)

## Specifiche del progetto 

Si realizzi un package ROS contenente degli opportuni nodi 
per poter svolgere i compiti seguenti

* Un nodo pubblica, 1 volta al secondo, un messaggio 
contenente un nome, una età, e un corso di laurea

* Un nodo permette di selezionare da tastiera quale parte 
del messaggio verrà mostrata a video (si veda la pagina 
seguente per i dettagli)

* Un nodo mostra a video la parte del messaggio 
selezionata

Il nodo che permette di selezionare da tastiera quale parte 
del messaggio mostrare dovrà comportarsi nel modo seguente:

* Digitando ‘a’ verrà stampato tutto il messaggio
* ‘n’ mostrerà solo il nome
* 'e’ mostrerà solo l’età
* ‘c’ mostrerà solo il corso di laurea

## Modalità di esecuzione

Per eseguire il package ros eseguire i seguenti punti:

* accedere alla workspace.
* clonare con git la repository nella cartella src presente nella workspace:
	git clone https://github.com/NoeMurr/ros_homework_1.git
* eseguire i seguenti comandi:
	catkin_make
	roslaunch ros_homework_1 homework.launch 

## Scelte progettuali


