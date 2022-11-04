/*-----------------------------------
CSCI 340 - Operating Systems
Erin Phillips
Fall 2022
p1.c file
Homework 2

Developing an http server that forkes child processes and uses signal handlers
to remove children from process table.

Revisions by Erin Phillips: completed sig_child_handler() TODO

I certify this work is entirely my own.
-----------------------------------
*/
#define DEBUG 0         // change to 0 when no longer debugging

#include <stdio.h>	// IO functions
#include <stdlib.h> 	// atof function
#include <sys/socket.h>	// listen function
#include <unistd.h>	// close function
#include <signal.h>	// signals
#include <wait.h>	// waitpid 
#include "server.h"	// our code :)

// -------------------------------------------------
// Global variables
static int server_socket_fd = 0;

// -------------------------------------------------
// Function prototypes
static void sig_child_handler(int sig);
static void sig_int_handler(int sig);

// Main
int main(int argc, char *argv[])
{
  unsigned int port_number = 0;

  // -------------------------------------------------
  // Register the signal handlers

  if (signal(SIGINT, sig_int_handler) == SIG_ERR) {
    perror("Unable to create signal interupt handler!");
    exit(FAIL);
  }

  if (signal(SIGCHLD, sig_child_handler) == SIG_ERR) {
    perror("Unable to create signal child handler!");
    exit(FAIL);
  }

  // -------------------------------------------------
  // Verify correct number of arguments are provided
  // when the server is executed.

  if (argc == 2) { 
    port_number = (unsigned int) atoi(argv[1]);
    server_socket_fd = bind_port(port_number);

    if (DEBUG) printf("server socket fd = %d\n", server_socket_fd);

    printf(" ------------------------------------------------\n");

    if (server_socket_fd == FAIL) {
      printf("Failed to bind socket to port %d\n", port_number);
      printf("Stopping http server!\n");
    } else {
      while (listen(server_socket_fd, 1) == 0) {
	printf("Server socket listening and accepting connections on port %d\n", port_number);
	accept_client(server_socket_fd);
      }
    }
  } else {
    printf("Port number is not specified!\n");
    printf("Example usage: %s %s\n", argv[0], "8888");
  }

  return OK;
} // end main function

static void sig_int_handler(int sig)
{
  printf("Unbinding server from port and exiting ... \n");
  close(server_socket_fd);
  exit(OK);
} // end sig_int_handler function

static void sig_child_handler(int sig)
{
  int pid;
  int status;
  while((pid = waitpid(-1, &status, 0)) > 0) 
  {
  printf("Child process [%d] terminated\n", pid);
  }

  // end sig_child_handler function
}
