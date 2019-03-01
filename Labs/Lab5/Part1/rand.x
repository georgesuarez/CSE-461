/* rand.x */

program RAND_PROG {
	version RAND_VERS {
		void INITIALIZE_RANDOM ( long ) = 1;	/* Service #1 */
		double GET_NEXT_RANDOM ( void ) = 2;    /* Service #2 */
	} = 1;
} = 123456789;	/* program # */
