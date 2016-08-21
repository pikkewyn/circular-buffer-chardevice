#include <assert.h>
#include <stdio.h>

#include "circularbuffer.h"

int main()
{
	struct CircularBuffer cb;
	
	{
		cbInit( &cb, 2 );
		assert( cbIsEmpty( &cb ) == 1 );
		assert( cbIsFull( &cb ) == 0 );
	}
	
	{
		cbWrite( &cb, 'a' );
		assert( cbIsEmpty( &cb ) == 0 );
		assert( cbIsFull( &cb ) == 0 );
		assert( cbRead( &cb ) == 'a' ); 
	}

	{
		cbWrite( &cb, 'a' );
		cbWrite( &cb, 'b' );
		assert( cbIsEmpty( &cb ) == 0 );
		assert( cbIsFull( &cb ) == 1 );
		assert( cbRead( &cb ) == 'a' );
		assert( cbRead( &cb ) == 'b' );
	}

	{
		cbWrite( &cb, 'a' );
		cbWrite( &cb, 'b' );
		cbWrite( &cb, 'c' );
		assert( cbIsEmpty( &cb ) == 0 );
		assert( cbIsFull( &cb ) == 1 );
		assert( cbRead( &cb ) == 'b' );
		assert( cbRead( &cb ) == 'c' );
	}
	
	cbFree( &cb );
	
	printf( "ok\n" );
	
	return 0;
}
