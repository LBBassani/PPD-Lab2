/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpcMiner.h"


void
prog_100(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	char *get_transaction_id_100_arg;
	int  *result_2;
	int  get_challenge_100_arg;
	int  *result_3;
	int  get_transaction_status_100_arg;
	int  *result_4;
	SubmitChallengeRequest  submit_challenge_100_arg;
	int  *result_5;
	int  get_winner_100_arg;
	SeedResponse  *result_6;
	int  get_seed_100_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, PROG, VERSAO, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = get_transaction_id_100((void*)&get_transaction_id_100_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = get_challenge_100(&get_challenge_100_arg, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = get_transaction_status_100(&get_transaction_status_100_arg, clnt);
	if (result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_4 = submit_challenge_100(&submit_challenge_100_arg, clnt);
	if (result_4 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_5 = get_winner_100(&get_winner_100_arg, clnt);
	if (result_5 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_6 = get_seed_100(&get_seed_100_arg, clnt);
	if (result_6 == (SeedResponse *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	prog_100 (host);
exit (0);
}
