#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 256
#define SHIFT 5  /* Caesar shift */

typedef struct {
  char first[MAX];
  char last[MAX];
  char dob[9];      /* DDMMYYYY */
  char notes[1024];
} Patient;

/* --- helpers (duplicated to stay single-file) --- */
static void trim(char *s){ size_t n=strlen(s); while(n&& (s[n-1]=='\n'||s[n-1]=='\r')) s[--n]='\0'; }
static void lower(char *s){ for(;*s;++s)*s=(char)tolower((unsigned char)*s); }
static void caesar_encrypt(char *s,int k){
  for(;*s;++s){ unsigned char c=(unsigned char)*s;
    if(isprint(c)){ int base=32, span=95; *s=(char)(base+((c-base+k)%span)); }
  }
}
static void make_fname(char *out,size_t n,const char *last,const char *dob){
  snprintf(out,n,"%s%s_record.aow",last,dob); /* last should be lowercase */
}
static int check_login(const char *user,const char *pass_enc){
  /* demo creds (encrypted with SHIFT=5): user: "nurse", pass: "nursepass" */
  const char *U="nurse", *P="szwxjufxxx"; /* change to your own */
  return strcmp(user,U)==0 && strcmp(pass_enc,P)==0;
}

/* --- io --- */
static void ask(const char *msg,char *buf,size_t n){
  fputs(msg,stdout); fflush(stdout);
  if(!fgets(buf,(int)n,stdin)) buf[0]='\0'; trim(buf);
}

int main(void){
  char user[MAX], pass[MAX], pass_enc[MAX];
  printf("== Nurse Login ==\nUser: "); fgets(user,MAX,stdin); trim(user);
  printf("Pass: "); fgets(pass,MAX,stdin); trim(pass);
  strncpy(pass_enc,pass,MAX-1); pass_enc[MAX-1]='\0'; caesar_encrypt(pass_enc,SHIFT);
  if(!check_login(user,pass_enc)){ puts("Invalid credentials."); return 1; }

  Patient p={0};
  puts("\n== New Patient Entry ==");
  ask("First name: ", p.first, sizeof(p.first));
  ask("Last name:  ", p.last,  sizeof(p.last));
  do { ask("DOB (DDMMYYYY): ", p.dob, sizeof(p.dob)); } while(strlen(p.dob)!=8);
  ask("Initial notes: ", p.notes, sizeof(p.notes));

  char last_l[MAX]; strncpy(last_l,p.last,MAX-1); last_l[MAX-1]='\0'; lower(last_l);
  char fname[512]; make_fname(fname,sizeof(fname),last_l,p.dob);

  char payload[2048];
  snprintf(payload,sizeof(payload),
           "FIRST:%s\nLAST:%s\nDOB:%s\nNOTES:%s\n",
           p.first,p.last,p.dob,p.notes);
  caesar_encrypt(payload,SHIFT);

  FILE *fp=fopen(fname,"w");
  if(!fp){ perror("fopen"); return 1; }
  fputs(payload,fp); fclose(fp);

  printf("Saved encrypted record: %s\n", fname);
  return 0;
}
