// -----------------------------------
// CSCI 340 - Operating Systems
// Fall 2022
// server.h header file
// Homework 2
//
// Revisions by Erin Phillips:
// Completed accept_client() TODOs
// - Spawn child process to handle clients
// - Process HTTP GET/POST requests
// - Write GET/POST response to client socket
//
// I certify this work is entirely my own.
// -----------------------------------

#include <string.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.h"


// ------------------------------------
// Function prototype that creates a socket and 
// then binds it to the specified port_number 
// for incoming client connections
// 
// Arguments:	port_number = port number server socket will be bound to.
//
// Return:      Socket file descriptor (or -1 on failure)
//
int bind_port(unsigned int port_number)
{
  // -------------------------------------
  // NOTHING TODO HERE :)
  // -------------------------------------
  // DO NOT MODIFY !

  int socket_fd;
  int set_option = 1;

  struct sockaddr_in server_address;
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&set_option,
	     sizeof(set_option));

  if (socket_fd < 0) return FAIL;

  bzero((char *) &server_address, sizeof(server_address));

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(port_number);

  if (bind(socket_fd, (struct sockaddr *) &server_address,
	     sizeof(server_address)) == 0) {
    return socket_fd;
  } else {
    return FAIL;
  }
} // end bind_port function

// ------------------------------------
// Function prototype that accepts a client
// socket connection
// 
// Arguments:	server file descriptor
//
// Return:      Termination status of client (0 = No Errors, -1 = Error)
//
int accept_client(int server_socket_fd)
{
  int exit_status = OK;
  int client_socket_fd = -1;
  socklen_t client_length; 
  struct sockaddr_in client_address;
  char request[2048];

  client_length = sizeof(client_address);

  client_socket_fd = accept(server_socket_fd,
			     (struct sockaddr *) &client_address,
			     &client_length);
  // -------------------------------------
  // TODO:
  // -------------------------------------
  // Modify code to fork a child process
  // -------------------------------------
  int p = fork();
  if (p == -1) { exit_status = FAIL; }
  else if (p == 0)
  {
    printf("Child [%d] executing\n", getpid());
    char *entityBody;
    char *token;
    char htmlResp[4096] = "<html><body><h1>CSCI 340 Operating Systems || Homework 2</h1><h2> "; // beginning of response

    if (client_socket_fd >= 0) {
      bzero(request, 2048);
      read(client_socket_fd, request, 2047);
      if (DEBUG) { printf("Here is the http message:\n%s\n\n", request); }

      if(request[0] == 'P') { // determine request is a POST
        strcat(htmlResp, "POST Operation</h2><table border=1 width=\"50%\">"); // append to html body
        entityBody = (char *)strchr(request, '?') + 4; // pointer to first char of key/value pairs
        while ((token = strsep(&entityBody, "&"))) { // split at & delimeter
            strcat(htmlResp, "<tr><td><b>");
            strcat(htmlResp, strsep(&token, "=")); // key
            strcat(htmlResp, "</b></td><td>");
            strcat(htmlResp, token); // value
            strcat(htmlResp, "</td></tr>");
        }
        strcat(htmlResp, "<table></body></html>"); // append rest of html body
      }

      if(request[0] == 'G') { // determine request is a GET
        strcat(htmlResp, "GET Operation</h2><table border=1 width=\"50%\">"); // append to html body
        entityBody = (char *)strchr(request, '?') + 1; // pointer to first char of key/value pairs
        char *cpy = strsep(&entityBody, " "); // isolate the key/value pairs
        while ((token = strsep(&cpy, "&"))) { // split at & delimeter
          strcat(htmlResp, "<tr><td><b>");
          strcat(htmlResp, strsep(&token, "=")); // key
          strcat(htmlResp, "</b></td><td>");
          strcat(htmlResp, token); // value
          strcat(htmlResp, "</td></tr>");
        }
        strcat(htmlResp, "<table></body></html>"); // append rest of html body
      }
      
      char response[4096];
      sprintf(response, "HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n%s",
         (int)strlen(htmlResp), htmlResp); // format response with header
      
      if (DEBUG) { printf("%s\n", response); }
      
      write(client_socket_fd, response, strlen(response));

    } else {
      exit_status = FAIL;
    }
  }
  else
  { // parent
    printf("Parent has forked child with pid of %d\n", p);

    if (DEBUG) { printf("Exit status = %d\n", exit_status); }
    sleep(2);
    close(client_socket_fd);
    return exit_status;
  }
} // end accept_client