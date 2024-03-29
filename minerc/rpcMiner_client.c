/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpcMiner.h"
#include <openssl/sha.h>

int clientId = 0;

int get_transaction_id_client(CLIENT *clnt);
int get_challenge_client(CLIENT *clnt, int transactionId);
int get_transaction_status_client(CLIENT *clnt, int transactionId);
int submit_challenge_client(CLIENT *clnt, SubmitChallengeRequest *submitRequest);
int get_winner_client(CLIENT *clnt, int transactionId);
SeedResponse get_seed_client(CLIENT *clnt, int transactionId);
int calculate_seed(int challenge, int seed);

int get_transaction_id_client(CLIENT *clnt)
{

    int transactionId;

    int *result = get_transaction_id_100(NULL, clnt);
    if (result == (int *)NULL)
    {
        clnt_perror(clnt, "call failed");
        clnt_destroy(clnt);
        exit(1);
    }
    return *result;
}

int get_challenge_client(CLIENT *clnt, int transactionId)
{
    int *result = get_challenge_100(&transactionId, clnt);
    if (result == (int *)NULL)
    {
        clnt_perror(clnt, "call failed");
        clnt_destroy(clnt);
        exit(1);
    }
    return *result;
}

int get_transaction_status_client(CLIENT *clnt, int transactionId)
{
    int *result = get_transaction_status_100(&transactionId, clnt);
    if (result == (int *)NULL)
    {
        clnt_perror(clnt, "call failed");
        clnt_destroy(clnt);
        exit(1);
    }
    return *result;
}

int submit_challenge_client(CLIENT *clnt, SubmitChallengeRequest *submitRequest)
{
    int *result = submit_challenge_100(submitRequest, clnt);
    if (result == (int *)NULL)
    {
        clnt_perror(clnt, "call failed");
        clnt_destroy(clnt);
        exit(1);
    }
    return *result;
}

int get_winner_client(CLIENT *clnt, int transactionId)
{
    int *result = get_winner_100(&transactionId, clnt);
    if (result == (int *)NULL)
    {
        clnt_perror(clnt, "call failed");
        clnt_destroy(clnt);
        exit(1);
    }
    return *result;
}

SeedResponse get_seed_client(CLIENT *clnt, int transactionId)
{
    SeedResponse *result = get_seed_100(&transactionId, clnt);
    if (result == (SeedResponse *)NULL)
    {
        clnt_perror(clnt, "call failed");
        clnt_destroy(clnt);
        exit(1);
    }
    return *result;
}

void mine(CLIENT *clnt)
{
    int transactionId = get_transaction_id_client(clnt);
    int challenge = get_challenge_client(clnt, transactionId);

    printf("Transaction ID: %d\n", transactionId);

    int count = 0;
    int seed = 0;
    int found = FALSE;
    while (count < 5000000)
    {
        seed = rand() % 2000000000;
        int result = calculate_seed(challenge, seed);
        if (result == -1)
        {
            continue;
        }
        else
        {
            found = TRUE;
            break;
        }
        count++;
    }

    if (!found)
    {
        printf("Não foi possível gerar um seed válido em 5000000 tentativas");
        return;
    }

    SubmitChallengeRequest submitRequest;
    submitRequest.transactionId = transactionId;
    submitRequest.seed = seed;
    submitRequest.clientId = clientId;

    int result = submit_challenge_client(clnt, &submitRequest);
    if (result == -1)
    {
        printf("Não foi possível enviar o seed para o servidor");
        return;
    }
    SeedResponse seedResponse = get_seed_client(clnt, transactionId);
    printf("Seed gerado: %d\n", seedResponse.seed);
    printf("Status: %d\n", seedResponse.status);
    int winner = get_winner_client(clnt, transactionId);
    printf("Winner: %s\n", winner == clientId ? "você venceu" : "adversário venceu");
}

int calculate_seed(int challenge, int seed)
{
    char data[SHA_DIGEST_LENGTH];
    sprintf(data, "%d", seed);
    size_t length = strlen(data);
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(data, length, hash);
    // hash now contains the 20-byte SHA-1 hash
    for (int i = 0; i < challenge; i++)
    {
        if (hash[i] != '0')
        {
            return 0; // invalid seed
        }
    }
    return 1; // valid seed
}

enum Menu
{
    TRANSACTION = 1,
    CHALLENGE = 2,
    STATUS = 3,
    WINNER = 4,
    RESULT = 5,
    MINER = 6,
    EXIT = 99
};

int main(int argc, char *argv[])
{
    char *host;

    if (argc < 2)
    {
        printf("usage: %s server_host\n", argv[0]);
        exit(1);
    }
    host = argv[1];
    CLIENT *clnt = clnt_create(host, PROG, VERSAO, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }
    clientId = rand() % 100;
    while (TRUE)
    {
        int transactionId;
        int menu;
        printf("Menu:\n");
        printf("[1] - Transação Atual\n");
        printf("[2] - Desafio\n");
        printf("[3] - Status\n");
        printf("[4] - Vencedor\n");
        printf("[5] - Resultado\n");
        printf("[6] - Minerar\n");
        printf("[99] - Sair\n");
        scanf("%d", &menu);
        switch (menu)
        {
        case TRANSACTION:
            transactionId = get_transaction_id_client(clnt);
            printf("Transaction ID: %d\n", transactionId);
            break;
        case CHALLENGE:
            printf("Digite o ID da transação: ");
            scanf("%d", &transactionId);
            int challenge = get_challenge_client(clnt, transactionId);
            printf("Challenge: %d\n", challenge);
            break;
        case STATUS:
            printf("Digite o ID da transação: ");
            scanf("%d", &transactionId);
            int status = get_transaction_status_client(clnt, transactionId);
            printf("Status: %d\n", status);
            break;
        case WINNER:
            printf("Digite o ID da transação: ");
            scanf("%d", &transactionId);
            int winner = get_winner_client(clnt, transactionId);
            printf("Winner: %s\n", winner == clientId ? "você venceu" : "adversário venceu");
            break;
        case RESULT:
            printf("Digite o ID da transação: ");
            scanf("%d", &transactionId);
            SeedResponse seedResponse = get_seed_client(clnt, transactionId);
            printf("Seed gerado: %d\n", seedResponse.seed);
            printf("Status: %d\n", seedResponse.status);
            printf("Challenge: %d\n", seedResponse.challenge);
            break;
        case MINER:
            mine(clnt);
            break;
        case EXIT:
            printf("Saindo...\n");
            clnt_destroy(clnt);
            exit(0);
        }
    }
    clnt_destroy(clnt);
    exit(0);
}
