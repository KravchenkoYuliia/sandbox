#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>

int	count = 0;
int	max_fd = 0;
int	ids[ 65536 ];
char*	messages[ 65536 ];
fd_set	read_fd, write_fd, all_fd;
char	buffer_read[ 1001 ], buffer_write[ 42 ];

int	ft_strlen( char* str ) {

	if ( !str )
		return 0;

	int i = 0;
	while ( str[i] )
		i++;

	return i;
}

char *ft_strjoin( char *buf, char *add )
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

void	notify_other( int who, char* what ) {

	for ( int fd = 0; fd <= max_fd; fd++ ) {

		if ( FD_ISSET( fd, &write_fd ) && fd != who )
			send( fd, what, ft_strlen( what ), 0 );
	}
}

void	register_client( int client_fd ) {

	max_fd = client_fd > max_fd ? client_fd : max_fd;

	ids[ client_fd ] = count++;
	messages[ client_fd ] = NULL;
	FD_SET( client_fd, &all_fd );
	sprintf( buffer_write, "server: client %d just arrived\n", ids[ client_fd ] );
	notify_other( client_fd, buffer_write );
}

int	extract_message( char** buffer, char** message ) {

	int i = 0;
	char* new_buffer = NULL;

	*message = NULL;
	if ( buffer == NULL )
		return 0;

	while ( (*buffer)[i] ) {

		if ( (*buffer)[i] == '\n' ) {

			new_buffer = calloc( 1, sizeof( *new_buffer ) * ( strlen(*buffer + i + 1) + 1));
			if ( !new_buffer )
				return -1; //TODO: catch it or exit 
			
			strcpy( new_buffer, *buffer + i + 1 );
			*message = *buffer;
			(*message)[i + 1] = 0;
			*buffer = new_buffer;

			return 1;
		}
		i++;
	}
	return 0;
}

void	send_message( int client_fd ) {

	char* message;

	while ( extract_message( &(messages[client_fd]), &message ) ) {

		sprintf( buffer_write, "client %d: ", ids[ client_fd ] );
		notify_other( client_fd, buffer_write );
		notify_other( client_fd, message );
		free( message );
	}
}

void	remove_client( int client_fd ) {

	sprintf( buffer_write, "server: client %d just left\n", ids[ client_fd ] );
	notify_other( client_fd, buffer_write );
	free( messages[ client_fd ] );
	FD_CLR( client_fd, &all_fd );
	close( client_fd );

}

void	fatal_error() {

	write( STDERR_FILENO, "Fatal error\n", ft_strlen( "Fatal error\n" ) );
	exit( 1 );

}

int	create_socket() {

	// this select macro  clears (removes all file descriptors from) set
	FD_ZERO( &all_fd );
	
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if ( fd == -1 ) {
		 fatal_error();
	}
	FD_SET( fd, &all_fd );
	return fd;
}

/* //TO SEE LEAKS
#include <signal.h>

void handle_sigint(int sig) {
    (void)sig;
    for (int fd = 0; fd <= max_fd; fd++)
        if (FD_ISSET(fd, &all_fd)) {
            free(messages[fd]);
            close(fd);
        }
    exit(0);
}
// у main, до циклу:
signal(SIGINT, handle_sigint);
*/

int	main( int ac, char** av ) {

	if ( ac != 2 ) {
		write( STDERR_FILENO, "Wrong number of arguments\n", ft_strlen( "Wrong number of arguments\n" ) );
		return 1;
	}
	
	int	socket_fd = create_socket();
	max_fd = socket_fd;

	struct sockaddr_in server_address;
	bzero( &server_address, sizeof(server_address) );

	// assign IP, PORT
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	server_address.sin_port = htons( atoi(av[1]) );

	// Binding newly created socket to given IP and verification
	if ( (bind(socket_fd, (const struct sockaddr *)&server_address, sizeof( server_address ))) != 0)
		fatal_error();

	if ( listen(socket_fd, SOMAXCONN) != 0 )
		fatal_error();

	while ( true ) {

		read_fd = write_fd = all_fd;

		if ( select( max_fd + 1, &read_fd, &write_fd, NULL, NULL ) == -1 )
			fatal_error();
		for ( int fd = 0; fd <= max_fd; fd++ ) {

			// macro can be used to test if a file descriptor is still present in a set. If not ready for reading - skip
			if ( FD_ISSET( fd, &read_fd ) == 0 )
				continue;

			if ( fd == socket_fd ) {

				socklen_t addr_len = sizeof( server_address );
				int client_fd = accept( socket_fd, (struct sockaddr *)&server_address, &addr_len );
				if ( client_fd >= 0 ) {
					register_client( client_fd );
					break ;
				}
			}
			else {

				int read_bytes = recv( fd, buffer_read, 1000, 0 );
				if ( read_bytes <= 0 ) {
					remove_client( fd );
					break;
				}
				buffer_read[ read_bytes ] = '\0';
				messages[ fd ] = ft_strjoin( messages[ fd ], buffer_read );
				send_message( fd );
			}

		}

	}

}
