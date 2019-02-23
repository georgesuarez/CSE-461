/* rand x */
program RADN_PROG {
    version RAND_VERS {
        void INITIALIZE_RANDOM( long ) = 1;     /* service #1 */
        double GET_NEXT_RANDOM( void ) = 2;     /* serviec #2 */
    } = 1;
} = 0x30000000;     /* program # */
