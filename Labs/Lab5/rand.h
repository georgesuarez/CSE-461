/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RAND_H_RPCGEN
#define _RAND_H_RPCGEN

#define RPCGEN_VERSION	199506

#include <rpc/rpc.h>


#define RADN_PROG ((rpc_uint)0x30000000)
#define RAND_VERS ((rpc_uint)1)

#ifdef __cplusplus
#define INITIALIZE_RANDOM ((rpc_uint)1)
extern "C" void * initialize_random_1(long *, CLIENT *);
extern "C" void * initialize_random_1_svc(long *, struct svc_req *);
#define GET_NEXT_RANDOM ((rpc_uint)2)
extern "C" double * get_next_random_1(void *, CLIENT *);
extern "C" double * get_next_random_1_svc(void *, struct svc_req *);

#elif __STDC__
#define INITIALIZE_RANDOM ((rpc_uint)1)
extern  void * initialize_random_1(long *, CLIENT *);
extern  void * initialize_random_1_svc(long *, struct svc_req *);
#define GET_NEXT_RANDOM ((rpc_uint)2)
extern  double * get_next_random_1(void *, CLIENT *);
extern  double * get_next_random_1_svc(void *, struct svc_req *);

#else /* Old Style C */
#define INITIALIZE_RANDOM ((rpc_uint)1)
extern  void * initialize_random_1();
extern  void * initialize_random_1_svc();
#define GET_NEXT_RANDOM ((rpc_uint)2)
extern  double * get_next_random_1();
extern  double * get_next_random_1_svc();
#endif /* Old Style C */

#endif /* !_RAND_H_RPCGEN */
