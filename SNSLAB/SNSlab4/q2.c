#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include <time.h>

#define KEY_SIZE 12   
#define MSG_SIZE 150 

char Ka_as[KEY_SIZE], Ka_tgs[KEY_SIZE], Kas_tgs[KEY_SIZE];
char Kb_tgs[KEY_SIZE], Kb_as[KEY_SIZE], Ka_b[KEY_SIZE];

void generateKey(char *buffer) {
    srand(time(NULL) ^ clock());
    for (int i = 0; i < 5; i++) {
        buffer[i] = 'a' + (rand() % 26);  
    }
    buffer[5] = '\0';  
}

void encryptText(const char *message, const char *key, char *encrypted) {
    int n = strlen(message);
    int k = strlen(key);
    for (int i = 0; i < n; i++) {
        int enc = ((int)message[i] ^ (int)key[i % k]) % 26;
        encrypted[i] = 'A' + enc;
    }
    encrypted[n] = '\0';
}

void decryptText(const char *encrypted, const char *key, char *decrypted) {
    encryptText(encrypted, key, decrypted);
}

/**
 * TGS: Generates the service session key (Ka_b) and returns two tokens:
 *   1) aliceToken: Encrypted(Ka_b) using Ka_tgs
 *   2) bobToken:   Encrypted(Ka_b + "Alice") using Kb_tgs
 */
void generateTokens(const char *message, char *aliceToken, char *bobToken, int t) {
    printf("\n[Step 4] TGS: Processing Alice's request for a service ticket.\n");
    if (message[0] == 1) {
        // Extract the timestamp from the message
        char timestamp[KEY_SIZE];
        strncpy(timestamp, message + 1, t);
        timestamp[t] = '\0';

        // Generate the session key for Alice-Bob
        generateKey(Ka_b);
        printf("TGS: Generated session key Ka_b = %s\n", Ka_b);

        // Token for Alice: Ka_b encrypted with Ka_tgs
        encryptText(Ka_b, Ka_tgs, aliceToken);
        printf("TGS: Token for Alice (encrypted with Ka_tgs) = %s\n", aliceToken);

        // Token for Bob: (Ka_b + “Alice”) encrypted with Kb_tgs
        char temp[2 * KEY_SIZE];
        snprintf(temp, sizeof(temp), "%s%s", Ka_b, "Alice");
        encryptText(temp, Kb_tgs, bobToken);
        printf("TGS: Token for Bob (encrypted with Kb_tgs) = %s\n", bobToken);

    } else {
        printf("TGS: Request invalid. Could not validate the sender.\n");
    }
}

/**
 * Alice requests tokens from TGS by:
 *   1) Decrypting the AS message with Ka_as
 *   2) Extracting Ka_tgs and the TGS ticket
 *   3) Sending an encrypted timestamp + TGS ticket to the TGS
 *   4) Receiving the new session key (Ka_b) and Bob’s ticket
 *   5) Sending Bob’s ticket + encrypted timestamp to Bob
 */

void sendRequestForTokens(const char *asMessageEncrypted, char *aliceToken, char *bobToken) {
    printf("[Step 3] Alice: Decrypting message from AS with Ka_as...\n");
    char decrypted[MSG_SIZE];
    decryptText(asMessageEncrypted, Ka_as, decrypted);

    // Extract Ka_tgs (the first part) from the decrypted message
    int len_Ka_tgs = strlen(Ka_tgs);  // We generated Ka_tgs with 5 chars, so length is 5
    char extracted_Ka_tgs[KEY_SIZE];
    strncpy(extracted_Ka_tgs, decrypted, len_Ka_tgs);
    extracted_Ka_tgs[len_Ka_tgs] = '\0';

    // The remainder is the TGS ticket
    char ticket[MSG_SIZE];
    strcpy(ticket, decrypted + len_Ka_tgs);

    printf("Alice: Extracted Ka_tgs = %s\n", extracted_Ka_tgs);
    printf("Alice: Received TGS ticket (encrypted with Kas_tgs) = %s\n", ticket);

    // Alice creates an authenticator: an encrypted timestamp using Ka_tgs
    char timestamp[KEY_SIZE];
    generateKey(timestamp);  // a random “timestamp”
    char encTimestamp[KEY_SIZE];
    encryptText(timestamp, Ka_tgs, encTimestamp);

    printf("Alice: Generated an encrypted timestamp (using Ka_tgs) = %s\n", encTimestamp);

    // Construct the message to TGS
    char new_message[MSG_SIZE];
    int idx = 0;
    new_message[idx++] = 1;  // indicates a valid request
    strcpy(new_message + idx, encTimestamp);
    idx += strlen(encTimestamp);
    strcpy(new_message + idx, ticket);

    // Now request tokens from TGS
    generateTokens(new_message, aliceToken, bobToken, strlen(encTimestamp));

    // Next, simulate sending Bob’s token + encrypted timestamp to Bob
    char timestampBob[KEY_SIZE];
    generateKey(timestampBob);
    char encTimestampBob[KEY_SIZE];
    encryptText(timestampBob, Ka_b, encTimestampBob);

    printf("\n[Step 5] Alice: Sending Bob’s token + encrypted timestamp.\n");
    printf("Alice -> Bob: Token = %s, Encrypted Timestamp = %s\n", bobToken, encTimestampBob);

    // Bob decrypts the token with Kb_tgs
    printf("\nBob: Decrypting the received token with Kb_tgs...\n");
    char decryptedToken[KEY_SIZE];
    decryptText(bobToken, Kb_tgs, decryptedToken);

    // The first 5 characters in decryptedToken is Ka_b; the remainder is “Alice”
    int len_Ka_b = strlen(Ka_b);
    char extracted_Ka_b[KEY_SIZE];
    strncpy(extracted_Ka_b, decryptedToken, len_Ka_b);
    extracted_Ka_b[len_Ka_b] = '\0';

    // Bob now uses Ka_b to decrypt Alice’s timestamp
    char decryptedTimestamp[KEY_SIZE];
    decryptText(encTimestampBob, extracted_Ka_b, decryptedTimestamp);

    printf("Bob: Decrypted token yields Ka_b = %s\n", extracted_Ka_b);
    printf("Bob: Decrypted timestamp = %s\n", decryptedTimestamp);

    // Bob sends a response back to Alice, e.g., timestamp - 1
    int ts = atoi(decryptedTimestamp) - 1;  // trivially parse int
    char response[KEY_SIZE];
    if (snprintf(response, sizeof(response), "%d", ts) >= (int)sizeof(response)) {
        fprintf(stderr, "Error: response buffer overflow!\n");
        return;
    }
    char encResponse[KEY_SIZE];
    encryptText(response, extracted_Ka_b, encResponse);

    printf("Bob: Sending back encrypted response to Alice: %s\n", encResponse);
    printf("\n[Step 6] Mutual authentication completed between Alice and Bob.\n\n");
}

/**
 * Full Kerberos simulation:
 *   Step 1: Alice -> AS (plaintext request)
 *   Step 2: AS -> Alice (Ka_tgs + TGS ticket, encrypted with Ka_as)
 *   Step 3: Alice -> TGS (TGS ticket + authenticator)
 *   Step 4: TGS -> Alice (Ka_b + Bob ticket)
 *   Step 5: Alice -> Bob (Bob ticket + authenticator)
 *   Step 6: Bob -> Alice (confirmation)
 */

 
void kerberos() {
    printf("[Step 1] Alice sends request to AS (plaintext)\n\n");

    // Generate keys used by AS, TGS, Bob
    generateKey(Ka_as);
    generateKey(Ka_tgs);
    generateKey(Kas_tgs);
    generateKey(Kb_as);
    generateKey(Kb_tgs);

    printf("[Key Generation]\n");
    printf("AS: Ka_as   = %s\n", Ka_as);
    printf("AS: Ka_tgs  = %s\n", Ka_tgs);
    printf("AS: Kas_tgs = %s\n", Kas_tgs);
    printf("AS: Kb_as   = %s\n", Kb_as);
    printf("AS: Kb_tgs  = %s\n\n", Kb_tgs);

    // Hardcode or simulate a ticket from AS to TGS
    // For example: “A + Kas_tgs” to represent “Alice + session key with TGS”
    char ticket[MSG_SIZE];
    snprintf(ticket, sizeof(ticket), "A%s", Ka_tgs);
    printf("[Step 2] AS: Creating TGS ticket = %s\n", ticket);

    // Encrypt that ticket with Kas_tgs (only TGS can decrypt it)
    char encTicket[MSG_SIZE];
    encryptText(ticket, Kas_tgs, encTicket);
    printf("AS: Encrypted TGS ticket (with Kas_tgs) = %s\n", encTicket);

    // Combine Ka_tgs + TGS ticket into one message
    char asMessage[MSG_SIZE];
    if (snprintf(asMessage, sizeof(asMessage), "%s%s", Ka_tgs, encTicket) >= (int)sizeof(asMessage)) {
        fprintf(stderr, "Warning: asMessage truncated!\n");
    }

    // Encrypt asMessage with Ka_as (so only Alice can decrypt)
    char encryptedASMessage[MSG_SIZE];
    encryptText(asMessage, Ka_as, encryptedASMessage);
    printf("AS: Sending to Alice -> (Ka_tgs + TGS ticket) encrypted with Ka_as = %s\n\n", encryptedASMessage);

    // Now let Alice request tokens from TGS
    char tokenAlice[KEY_SIZE], tokenBob[KEY_SIZE];
    sendRequestForTokens(encryptedASMessage, tokenAlice, tokenBob);

}

int main() {
    printf("===== Kerberos Simulation Start =====\n\n");
    kerberos();
    printf("===== Kerberos Simulation End =====\n");
    return 0;
}
